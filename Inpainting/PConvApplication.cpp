#include"PConvApplication.h"
#include<iostream>
#include"opencv2/opencv.hpp"
#include"opencv2/core/core.hpp"
#include"opencv2/opencv.hpp"
#include"opencv2/imgproc.hpp"
#include"opencv2/imgcodecs.hpp"
#include"opencv2/imgproc/types_c.h" // using CV_RGB2BGR
#include<chrono>
#include<vector>
#include<memory>
#include<string>
#include<type_traits>
#include<windows.h>

namespace wheels
{
torch::Tensor normalize(torch::Tensor& img)
{
	img[0][0].sub_(0.485).div_(0.229);
	img[0][1].sub_(0.456).div_(0.224);
	img[0][2].sub_(0.406).div_(0.225);
	return img;
}

torch::Tensor denormalize(torch::Tensor& img)
{
	img[0][0].mul_(0.229).add_(0.485);
	img[0][1].mul_(0.224).add_(0.456);
	img[0][2].mul_(0.225).add_(0.406);
	return img;
}

decltype(auto) binary2RGB(cv::Mat x)//x是单通道图像
{
	cv::Mat out_3channel = cv::Mat::zeros(x.rows, x.cols, CV_8UC3);
	std::vector<cv::Mat> channels;
	for (int i = 0; i < 3; i++)
		channels.emplace_back(x);
	cv::merge(channels, out_3channel);
	return out_3channel;
}

torch::Tensor preporcess(cv::Mat& img, bool is_normalize = true)
{
	cv::Mat new_img;
	if (img.channels() == 1)
	{
		new_img = binary2RGB(img);
		assert(new_img.channels() == 3);
	}
	else if (img.channels() == 3)
	{
		cv::cvtColor(img, new_img, CV_BGR2RGB);
	}

	torch::Tensor img_tensor = torch::from_blob(new_img.data, { 1,img.rows,img.cols,3 }, torch::kByte);
	img_tensor = img_tensor.permute({ 0,3,1,2 });
	img_tensor = img_tensor.toType(torch::kFloat);
	img_tensor = img_tensor.div(255);
	if (is_normalize)
	{
		auto normalize = [&img_tensor] {
			img_tensor[0][0].sub_(0.485).div_(0.229);
			img_tensor[0][1].sub_(0.456).div_(0.224);
			img_tensor[0][2].sub_(0.406).div_(0.225);
		}; //必须有调用的()才行
		normalize();
	}
	img_tensor = img_tensor.to(torch::kCUDA);
	return img_tensor;
}

decltype(auto) postprocess(torch::Tensor& x_tensor)
{
	auto img_tensor = x_tensor.clone();
	auto denormalize = [&img_tensor] {
		img_tensor[0][0].mul_(0.229).add_(0.485);
		img_tensor[0][1].mul_(0.224).add_(0.456);
		img_tensor[0][2].mul_(0.225).add_(0.406);;
	}; //必须有调用的()才行
	denormalize();
	img_tensor = img_tensor.squeeze().detach().permute({ 1,2,0 }).contiguous().to(torch::kCPU);
	//img_tensor = img_tensor.mul(255.0).clamp(0,255).to(torch::kCPU);
	int img_h = img_tensor.size(0);
	int img_w = img_tensor.size(1);
	cv::Mat img(cv::Size(img_h, img_w), CV_32FC3, img_tensor.data_ptr());
	cv::Mat img_mat;
	img.convertTo(img_mat, CV_8U, 255.0);
	cv::cvtColor(img_mat, img_mat, CV_RGB2BGR);
	return img_mat;
}

PConvApplication::PConvApplication():weight_name("mask_lightest")
{
	torch::jit::getProfilingMode() = false;
	torch::jit::getExecutorMode() = false;
	torch::jit::setGraphExecutorOptimize(false);

	try
	{
		pconvnet = torch::jit::load("./model/partialconv_16.8.pt");
	}
	catch (const c10::Error& e)
	{
		std::cerr << "torch model load failed, " << e.what() << '\n';
		exit(1);
	}
	pconvnet.to(at::kCUDA);
	pconvnet.eval();
}

void PConvApplication::regenerate(std::string& cur_weight_name)
{
	if (cur_weight_name == weight_name) return;
	std::string weight_path;
	if (cur_weight_name == "mask_lightest")
		weight_path = "./model/partialconv_16.8.pt";
	else if (cur_weight_name == "mask_light")
		weight_path = "./model/partialconv_23.55.pt";
	else
		weight_path = "./model/partialconv_35.5.pt";
	try
	{
		pconvnet = torch::jit::load(weight_path);
	}
	catch (const c10::Error& e)
	{
		std::cerr << "torch model load failed, " << e.what() << '\n';
		exit(1);
	}
	pconvnet.to(at::kCUDA);
	pconvnet.eval();
}

//std::tuple<cv::Mat,cv::Mat> PConvApplication::run(std::string& origin_path, std::string& mask_path)
//{
//	cv::Mat x = cv::imread(origin_path);
//	cv::Mat mask = cv::imread(mask_path, 0);//二值读入图像
//	auto tensor_x = preporcess(x);
//	auto tensor_mask = preporcess(mask, false);
//	auto mask_x = tensor_x * tensor_mask; //element-wise multiply
//
//	std::vector<torch::jit::IValue> inputs;
//	inputs.emplace_back(mask_x);
//	inputs.emplace_back(tensor_mask);
//	torch::NoGradGuard no_grad;
//	auto t1 = std::chrono::steady_clock::now();
//	auto out = pconvnet.forward(inputs).toTensor();
//	auto t2 = std::chrono::steady_clock::now();
//	std::cerr << "time elapsed: " << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() / 1000.0 << "ms\n";
//
//	auto out_mat = postprocess(out);
//	auto mask_img_mat = postprocess(mask_x);
//	return std::tuple<cv::Mat,cv::Mat>(mask_img_mat, out_mat);
//}

std::tuple<cv::Mat, cv::Mat> PConvApplication::run(cv::Mat& original_mat, cv::Mat& mask_mat)
{
	auto tensor_x = preporcess(original_mat);
	auto tensor_mask = preporcess(mask_mat, false);
	auto mask_x = tensor_x * tensor_mask; //element-wise multiply

	std::vector<torch::jit::IValue> inputs;
	inputs.emplace_back(mask_x);
	inputs.emplace_back(tensor_mask);
	torch::NoGradGuard no_grad;
	auto t1 = std::chrono::steady_clock::now();
	auto out = pconvnet.forward(inputs).toTensor();
	auto t2 = std::chrono::steady_clock::now();
	std::cerr << "time elapsed: " << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() / 1000.0 << "ms\n";

	auto out_mat = postprocess(out);
	auto mask_img_mat = postprocess(mask_x);
	return std::tuple<cv::Mat, cv::Mat>(mask_img_mat, out_mat);
}
}