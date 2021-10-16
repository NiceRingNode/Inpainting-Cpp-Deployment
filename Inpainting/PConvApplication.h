#pragma once

#ifndef _PCONVAPPLICATION_H_
#define  _PCONVAPPLICATION_H_

#undef slots
#include"torch/torch.h"
#include"torch/script.h"
#define slots Q_SLOTS

#include"opencv2/highgui.hpp"
#include<string>
#include<tuple>

namespace wheels
{
class PConvApplication
{
public:
	PConvApplication();
	~PConvApplication() = default;
	
	void regenerate(std::string& cur_weight_name);
	std::tuple<cv::Mat, cv::Mat> run(cv::Mat& original_mat, cv::Mat& mask_mat);

private:
	torch::jit::script::Module pconvnet;
	std::string weight_name;
};
}
#endif // _PCONVAPPLICATION_H_
