#include"InpaintingSubWindow.h"
#include<QtCore/QDir>
#include<QtCore/QFile>
#include<QtWidgets/QFileDialog>
#include<QtWidgets/QMessageBox>
#include<QtCore/QDebug>

InpaintingSubWindow::InpaintingSubWindow(QWidget* parent)
	: QWidget(parent),
	  ui(new Ui::InpaintingSubWindowWidget),
	  img_w(0),
	  img_h(0),
	  type("original")
{
	ui->setupUi(this);
	ui->originsize_rb->setChecked(true);
	ui->screensize_rb->setChecked(false);
}

InpaintingSubWindow::~InpaintingSubWindow()
{
	delete ui;
}

void InpaintingSubWindow::paintEvent(QPaintEvent* event)
{
	if (ui->screensize_rb->isChecked() && !ui->originsize_rb->isChecked())
		set_screensize_image();
	QWidget::paintEvent(event);
}

void InpaintingSubWindow::mouseDoubleClickEvent(QMouseEvent* event)
{
	if (isMaximized()) showNormal();
	else showMaximized();
}

void InpaintingSubWindow::set_img(QPixmap& pixmap)
{
	img_pixmap = pixmap;
	ui->output_image->setPixmap(img_pixmap);
	ui->output_image->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

void InpaintingSubWindow::set_pixmap(QLabel* label_ptr, QPixmap& pixmap)
{
	label_ptr->setPixmap(pixmap);
	label_ptr->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

void InpaintingSubWindow::set_originalsize_image()
{
	set_pixmap(ui->output_image, img_pixmap);
	ui->originsize_rb->setChecked(true);
	ui->screensize_rb->setChecked(false);
}

void InpaintingSubWindow::set_screensize_image()
{
	//肯定是两个都存在的，所以不需要判断
	/*auto zoom = [this](QPixmap& pixmap) {
		int screen_w = ui->masked_image->width();
		int screen_h = ui->masked_image->height();
		float image_h = static_cast<float>(pixmap.width());
		float image_w = static_cast<float>(pixmap.height());
		float scale_w = static_cast<float>(screen_w) / image_w;
		float scale_h = static_cast<float>(screen_h) / image_h;
		int new_w = static_cast<int>(scale_w * image_w);
		int new_h = static_cast<int>(scale_h * image_h);
		auto scaled_pixmap = pixmap.scaled(new_w, new_h);
		return scaled_pixmap;
	};
	auto scaled_masked_img = zoom(masked_img_pixmap);
	auto scaled_output_img = zoom(output_img_pixmap);*/
	int screen_w = ui->output_scroll->width() - 30;
	int screen_h = ui->output_scroll->height() - 30;
	auto scaled_output_img = img_pixmap.scaled(screen_w, screen_h, Qt::KeepAspectRatio);
	set_pixmap(ui->output_image, scaled_output_img);
	ui->screensize_rb->setChecked(true);
	ui->originsize_rb->setChecked(false);
}

void InpaintingSubWindow::on_originsize_rb_toggled(bool checked)
{
	//点击才会触发，触发之后就发现如果checked了的话就可以了
	if (ui->originsize_rb->isChecked()) //没有点，现在点了，原尺寸显示
	{
		ui->originsize_rb->setChecked(true);
		ui->screensize_rb->setChecked(false);
		//有图片，一开始又没有点，所以肯定不是original size；无图片，没有点，证明没上传，不用管
		set_originalsize_image();
	}
	else
	{
		ui->originsize_rb->setChecked(false);
		ui->screensize_rb->setChecked(true);
		set_screensize_image();
	}
}

void InpaintingSubWindow::on_screensize_rb_toggled(bool checked)
{
	if (ui->screensize_rb->isChecked())
	{
		ui->screensize_rb->setChecked(true);
		ui->originsize_rb->setChecked(false);
		set_screensize_image();
	}
	else
	{
		ui->screensize_rb->setChecked(false);
		ui->originsize_rb->setChecked(true);
		set_originalsize_image();
	}
}