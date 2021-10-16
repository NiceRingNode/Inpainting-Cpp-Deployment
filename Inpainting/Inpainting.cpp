#include"Inpainting.h"
#include"InpaintingSubWindow.h"
#include<QtCore/QFile>
#include<QtCore/QDir>
#include<QtCore/QMimeData>
#include<QtCore/QtMath>
#include<QtWidgets/QFileDialog>
#include<QtWidgets/QMessageBox>
#include<QtWidgets/QGraphicsDropShadowEffect>
#include<QtWidgets/QStyleOption>
#include<QtGui/QDragEnterEvent>
#include<QtGui/QDropEvent>
#include<QtGui/QPixmap>
#include<QtGui/QImage>
#include<QtGui/QPainter>
#include<QtGui/QColor>
#include<QtGui/QBrush>
#include<QMouseEvent>
#include"opencv2/opencv.hpp"
#include"opencv2/imgproc/types_c.h"
#include<QDebug>
#include<iostream>
#include<windows.h>

namespace wheels
{
QImage Mat2QImage(cv::Mat& x)
{
	switch (x.type())
	{
	case CV_8UC1:
	{
		QImage y(x.data, x.cols, x.rows, static_cast<int>(x.step),
			QImage::Format_Grayscale8);
		static QVector<QRgb> color_table;
		if (color_table.isEmpty())
		{
			color_table.resize(256);
			for (int i = 0; i < 256; i++)
				color_table[i] = qRgb(i, i, i);
		}
		y.setColorTable(color_table);
		//这个的意思就是把所有的像素颜色都设置好，需要用的时候就用
		return y;
	}
	case CV_8UC3:
	{
		QImage y(x.data, x.cols, x.rows, static_cast<int>(x.step),
			QImage::Format_RGB888);
		return y.rgbSwapped();
		//rgbSwapped是将r和b的通道调换，因为这里本来就是bgr，换过来就是rgb
	}
	case CV_8UC4:
	{
		QImage y(x.data, x.cols, x.rows, static_cast<int>(x.step),
			QImage::Format_ARGB32);
		return y;
	}
	default:
	{
		qWarning() << "In Mat2Image(): unhandled cv::Mat type" << x.type() << '\n';
	}
	}
	return QImage();
}

cv::Mat QImage2Mat(const QImage& x)
{
	switch (x.format())
	{
	case QImage::Format_Indexed8:
	case QImage::Format_Grayscale8: //8 bits,1 channel
	{
		cv::Mat y(x.height(), x.width(), CV_8UC1, const_cast<uchar*>(x.bits()),
			static_cast<size_t>(x.bytesPerLine()));
		return y.clone();
	}
	case QImage::Format_RGB32:
	case QImage::Format_RGB888: //8 bits，3 channels
	{
		QImage temp = x;
		if (x.format() == QImage::Format_RGB32)
			temp = temp.convertToFormat(QImage::Format_RGB888);
		temp = temp.rgbSwapped();//rgb转bgr
		return cv::Mat(temp.height(), temp.width(), CV_8UC3,
			const_cast<uchar*>(temp.bits()),
			static_cast<size_t>(temp.bytesPerLine())).clone();
	}
	case QImage::Format_ARGB32:
	case QImage::Format_ARGB32_Premultiplied:
	{
		cv::Mat y(x.height(), x.width(), CV_8UC4, const_cast<uchar*>(x.bits()),
			static_cast<size_t>(x.bytesPerLine()));
		return y.clone();
	}
	default:
	{
		qWarning() << "In Image2Mat(): unhandled QImage format" << x.format() << '\n';
	}
	}
	return cv::Mat();
}

QPixmap Mat2Pixmap(cv::Mat x)
{
	return QPixmap::fromImage(Mat2QImage(x));
}

cv::Mat Pixmap2Mat(QPixmap x)
{
	return QImage2Mat(x.toImage());
}
}

Inpainting::Inpainting(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::InpaintingWidget),
	  partialconv(new wheels::PConvApplication),
	  postfixs({ ".png",".jpg","jpeg" }),
	  mouse_direct(wheels::Directs::None),
	  original_w(0),
	  original_h(0),
	  border(10),
	  light_mode(true),
	  dark_mode(false)
{
    ui->setupUi(this);
	init_ui();
	//connect(ui->inpaint_clear, SIGNAL(clicked()), this, SLOT(subwindow->sub_clear_images()));
	//connect(ui->inpaint_originsize_rb, SIGNAL(toggled()), this, SLOT(subwindow->set_originalsize_image()));
	//connect(ui->inpaint_screensize_rb, SIGNAL(toggled()), this, SLOT(subwindow->set_screensize_image()));
}

Inpainting::~Inpainting()
{
    delete ui;
	delete partialconv;
}

void Inpainting::init_ui()
{
	setMinimumSize(1400, 800);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	//layout()->setContentsMargins(QMargins(border, border, border, border));
	ui->inpaint_originsize_rb->setChecked(true);
	ui->inpaint_screensize_rb->setChecked(false);
	ui->originsize_SR_rb->setChecked(true);
	ui->screensize_SR_rb->setChecked(false);
	ui->lightmode_rb->setChecked(true);
	ui->darkmode_rb->setChecked(false);
	//这一段代码是拿来设置黑夜模式下的QLabel颜色
	ui->inpaint_origin->setStyleSheet("\
		QLabel{background-repeat:no-repeat;\
			background-position:center;}\
		QLabel:hover{background-repeat:no-repeat;\
			 background-position:center;\
			 background-color:#f0f0f0;");
	ui->inpaint_mask->setStyleSheet("\
		QLabel{background-repeat:no-repeat;\
			background-position:center;}\
		QLabel:hover{background-repeat:no-repeat;\
			 background-position:center;\
			 background-color:#f0f0f0;");
	ui->inpaint_masked->setStyleSheet("\
		QLabel{background-repeat:no-repeat;\
			background-position:center;}\
		QLabel:hover{background-repeat:no-repeat;\
			 background-position:center;\
			 background-color:#f0f0f0;");
	ui->inpaint_output->setStyleSheet("\
		QLabel{background-repeat:no-repeat;\
			background-position:center;}\
		QLabel:hover{background-repeat:no-repeat;\
			 background-position:center;\
			 background-color:#f0f0f0;");
	ui->SR_origin->setStyleSheet("\
		QLabel{background-repeat:no-repeat;\
			background-position:center;}\
		QLabel:hover{background-repeat:no-repeat;\
			 background-position:center;\
			 background-color:#f0f0f0;");
	ui->SR_output->setStyleSheet("\
		QLabel{background-repeat:no-repeat;\
			background-position:center;}");

	ui->inpaint_origin->installEventFilter(this);
	ui->inpaint_mask->installEventFilter(this);
	ui->closewindow->installEventFilter(this);
	ui->maximize->installEventFilter(this);
	ui->minimize->installEventFilter(this);
	setAcceptDrops(true);
	ui->inpaint_origin->setAcceptDrops(true);
	ui->inpaint_mask->setAcceptDrops(true);
	set_frameless();
	set_shadow();
}

void Inpainting::set_frameless()
{
	setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	setMouseTracking(true);
	ui->inpaint_origin->setMouseTracking(false);
	ui->inpaint_mask->setMouseTracking(false);
	ui->SR_origin->setMouseTracking(false);
	ui->SR_output->setMouseTracking(false);//好像没用，点了之后释放还是有点问题
	ui->inpaint_origin_scroll->setMouseTracking(false);
	ui->inpaint_mask_scroll->setMouseTracking(false);
	pressed_state.mouse_pressed = false;
	pressed_state.border_pressed = false;
}

void Inpainting::set_shadow()
{
	QGraphicsDropShadowEffect* shadow_effect = new QGraphicsDropShadowEffect(this);
	shadow_effect->setOffset(0, 0);
	shadow_effect->setColor(QColor(32, 101, 165, 120));
	shadow_effect->setBlurRadius(20);
	setGraphicsEffect(shadow_effect);
}

bool Inpainting::eventFilter(QObject* watched, QEvent* event)
{
	bool is_ip_org = watched == ui->inpaint_origin;
	bool is_ip_mask = watched == ui->inpaint_mask;
	if (is_ip_org || is_ip_mask)
	{
		if (event->type() == QEvent::MouseButtonPress)
		{
			QMouseEvent* mouse_event = (QMouseEvent*)event;
			if (mouse_event->button() == Qt::LeftButton)
			{
				if (is_ip_org && !is_ip_mask) upload_origin_img();
				else if (is_ip_mask && !is_ip_org) upload_origin_img("mask");
			}
		}
	}
	else if (watched == ui->closewindow)
	{
		if (event->type() == QEvent::MouseButtonPress)
		{
			QMouseEvent* mouse_event = (QMouseEvent*)event;
			if (mouse_event->button() == Qt::LeftButton)
				close();
		}
	}
	else if (watched == ui->maximize)
	{
		if (event->type() == QEvent::MouseButtonPress)
		{
			QMouseEvent* mouse_event = (QMouseEvent*)event;
			if (mouse_event->button() == Qt::LeftButton)
			{
				if (!isMaximized()) showMaximized();
				else showNormal();
			}
		}
	}
	else if (watched == ui->minimize)
	{
		if (event->type() == QEvent::MouseButtonPress)
		{
			QMouseEvent* mouse_event = (QMouseEvent*)event;
			if (mouse_event->button() == Qt::LeftButton)
				//setWindowState(Qt::WindowMinimized);
				showMinimized();
		}
	}
	return QWidget::eventFilter(watched, event);
}

void Inpainting::paintEvent(QPaintEvent* event)
{
	if (ui->inpaint_screensize_rb->isChecked() && !ui->inpaint_originsize_rb->isChecked())
		set_screensize_image();
	
	QPainter painter = QPainter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(Qt::transparent);
	QRect window_rect = rect();
	if (light_mode && !dark_mode)
		painter.setBrush(QBrush(QColor(255, 255, 255)));
	else if(dark_mode && !light_mode)
		painter.setBrush(QBrush(QColor(21, 26, 30)));
	if (!isMaximized())
	{
		window_rect.setLeft(7);
		window_rect.setTop(7);//数字越小就越宽，这个只是设置初始的左边和上边的坐标而已
		window_rect.setWidth(window_rect.width() - 7);//就是将这个窗口自己的rect弄出来
		window_rect.setHeight(window_rect.height() - 7);
		painter.drawRoundedRect(window_rect, 12, 12);
	}
	else
	{
		window_rect.setLeft(0);
		window_rect.setTop(0);
		window_rect.setWidth(window_rect.width() + 1);//就是将这个窗口自己的rect弄出来
		window_rect.setHeight(window_rect.height() + 1);
		painter.drawRoundedRect(window_rect, 12, 12);
	}
	
	/*
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);//反锯齿;
	painter.setPen(Qt::transparent);

	QPainterPath path;//绘制阴影
	path.setFillRule(Qt::WindingFill);
	if (light_mode)
		painter.fillPath(path, QBrush(QColor(236, 236, 236)));
	else
		painter.fillPath(path, QBrush(QColor(21, 26, 30)));
	QColor color(150, 150, 150, 120);
	for (int i = 0; i < 5; i++)
	{
		QPainterPath path;
		path.setFillRule(Qt::WindingFill);
		path.addRoundedRect(QRect(5 - i, 5 - i, width() - (5 - i) * 2, height() - (5 - i) * 2), 10, 10);
		color.setAlpha(220 - qSqrt(i) * 60);
		painter.setPen(color);
		painter.drawPath(path);
	}
	*/	
	QWidget::paintEvent(event);
}

void Inpainting::set_border(int _border) { border = _border; }

void Inpainting::resize_window(const QPoint& cur_pos)
{
	if (!pressed_state.border_pressed)
	{
		if (cur_pos.x() < border && cur_pos.y() < border)//左上角
		{
			mouse_direct = wheels::Directs::TopLeft;
			setCursor(Qt::SizeFDiagCursor);
		}
		else if (cur_pos.x() > width() - border && cur_pos.y() > height() - border)//右下角
		{
			mouse_direct = wheels::Directs::BottomRight;
			setCursor(Qt::SizeFDiagCursor);
		}
		else if (cur_pos.x() < border && cur_pos.y() > height() - border)//左下角
		{
			mouse_direct = wheels::Directs::BottomLeft;
			setCursor(Qt::SizeBDiagCursor);
		}
		else if (cur_pos.x() > width() - border && cur_pos.y() < border)//右上角
		{
			mouse_direct = wheels::Directs::TopRight;
			setCursor(Qt::SizeBDiagCursor);
		}
		else if (cur_pos.x() < border && border < cur_pos.y() < height() - border)//左
		{
			mouse_direct = wheels::Directs::Left;
			setCursor(Qt::SizeHorCursor);
			pressed_state.mouse_pressed = false;
		}
		else if (cur_pos.x() > width() - border && border < cur_pos.y() < height() - border)//右
		{
			mouse_direct = wheels::Directs::Right;
			setCursor(Qt::SizeHorCursor);
		}
		else if (cur_pos.y() < border && border < cur_pos.x() < width() - border)//上
		{
			mouse_direct = wheels::Directs::Top;
			setCursor(Qt::SizeVerCursor);
			pressed_state.mouse_pressed = false;
		}
		else if (cur_pos.y() > height() - border && border < cur_pos.x() < width() - border)//下
		{
			mouse_direct = wheels::Directs::Bottom;
			setCursor(Qt::SizeVerCursor);
		}
		else
		{
			mouse_direct = wheels::Directs::None;
			setCursor(Qt::ArrowCursor);
		}
	}
	else
	{
		switch (mouse_direct)
		{
		case wheels::Directs::TopLeft:
		{
			int cur_x = QCursor::pos().x();
			int cur_y = QCursor::pos().y();
			int cur_w = pos().x() + width() - cur_x;
			int cur_h = pos().y() + height() - cur_y;
			int total_w = pressed_state.window_pos.x() + pressed_state.pressed_size.width();
			int total_h = pressed_state.window_pos.y() + pressed_state.pressed_size.height();
			if (total_w - cur_x >= maximumWidth())
			{
				cur_x = total_w - maximumWidth();
				cur_w = maximumWidth();
			}
			if (total_w - cur_x <= minimumWidth())
			{
				cur_x = total_w - minimumWidth();
				cur_w = minimumWidth();
			}
			if (total_h - cur_y >= maximumHeight())
			{
				cur_y = total_h - maximumHeight();
				cur_h = maximumHeight();
			}
			if (total_h - cur_y <= minimumHeight())
			{
				cur_y = total_h - minimumHeight();
				cur_h = minimumHeight();
			}
			setGeometry(cur_x, cur_y, cur_w, cur_h);
			break;
		}
		case wheels::Directs::BottomRight:
		{
			int cur_w = QCursor::pos().x() - x();
			int cur_h = QCursor::pos().y() - y();
			setGeometry(pressed_state.window_pos.x(), pressed_state.window_pos.y(), cur_w, cur_h);
			break;
		}
		case wheels::Directs::TopRight:
		{
			int cur_h = y() + height() - QCursor::pos().y();
			int cur_w = QCursor::pos().x() - x();//x()是最左边的点的位置，减去就是w了
			int cur_y = QCursor::pos().y();
			if (cur_h > maximumHeight())
			{
				cur_y = pressed_state.window_pos.y() + pressed_state.pressed_size.height() - height();
				cur_h = maximumHeight();
			}
			setGeometry(pressed_state.window_pos.x(), cur_y, cur_w, cur_h);
			break;
		}
		case wheels::Directs::BottomLeft:
		{
			int cur_w = x() + width() - QCursor::pos().x();
			int cur_h = QCursor::pos().y() - pressed_state.window_pos.y();
			int cur_x = QCursor::pos().x();
			int total_w = pressed_state.window_pos.x() + pressed_state.pressed_size.width();
			if (total_w - cur_x >= maximumWidth())
			{
				cur_x = total_w - maximumWidth();
				cur_w = maximumWidth();
			}
			if (total_w - cur_x <= minimumWidth())
			{
				cur_x = total_w - minimumWidth();
				cur_w = minimumWidth();
			}
			setGeometry(cur_x, pressed_state.window_pos.y(), cur_w, cur_h);
			break;
		}
		case wheels::Directs::Left:
		{
			int cur_w = x() + width() - QCursor::pos().x();
			int cur_x = QCursor::pos().x();
			if (minimumWidth() <= cur_w <= maximumWidth())
				setGeometry(cur_x, y(), cur_w, height());
			pressed_state.mouse_pressed = false;
			break;
		}
		case wheels::Directs::Right:
		{
			int cur_w = QCursor::pos().x() - x();
			if (minimumWidth() <= cur_w <= maximumWidth())
				setGeometry(x(), y(), cur_w, height());
			break;
		}
		case wheels::Directs::Top:
		{
			int cur_h = y() + height() - QCursor::pos().y();
			if (minimumWidth() <= cur_h <= maximumWidth())
				setGeometry(x(), QCursor::pos().y(), width(), cur_h);
			pressed_state.mouse_pressed = false;
			break;
		}
		case wheels::Directs::Bottom:
		{
			int cur_h = QCursor::pos().y() - y();
			if (minimumHeight() <= cur_h <= maximumHeight())
				setGeometry(x(), y(), width(), cur_h);
			break;
		}
		case wheels::Directs::None:
		default:
			break;
		}
	}
}

void Inpainting::mousePressEvent(QMouseEvent* event)
{
	pressed_state.pressed_size = size();
	pressed_state.border_pressed = false;
	pressed_state.mouse_pressed = false;
	setFocus();//应该是focus鼠标点击事件 
	if (event->button() == Qt::LeftButton)
	{
		pressed_state.window_pos = pos();//保存点击的位置
		if (QRect(border + 2, border + 2, width() - (border + 2) * 2, height() - (border + 2) * 2).contains(QPoint(event->globalX() - x(), event->globalY() - y())))
		//这个就是在点击的时候，如果在那个框里面，才设置为true
		{
			pressed_state.mouse_pos = event->globalPos();
			pressed_state.mouse_pressed = true;
		}
		else
			pressed_state.border_pressed = true;
	}
}

void Inpainting::mouseMoveEvent(QMouseEvent* event)
{
	resize_window(mapFromGlobal(event->globalPos()));
	if (pressed_state.mouse_pressed)
	{
		setCursor(Qt::PointingHandCursor);
		move(pressed_state.window_pos + (event->globalPos() - pressed_state.mouse_pos));
	}
}

void Inpainting::mouseReleaseEvent(QMouseEvent* event)
{
	pressed_state.border_pressed = false;
	if (event->button() == Qt::LeftButton)
		pressed_state.mouse_pressed = false;
	setCursor(Qt::ArrowCursor);
}

void Inpainting::mouseDoubleClickEvent(QMouseEvent* event)
{
	if (!isMaximized()) showMaximized();
	else showNormal();
	QWidget::mouseDoubleClickEvent(event);
}

void Inpainting::dragEnterEvent(QDragEnterEvent* event)
{
	if (event->mimeData()->hasUrls())
	{
		QString filename = event->mimeData()->urls()[0].path();
		QString cur_postfix = filename.mid(filename.length() - 5);//获取后缀
		if(postfixs.contains(cur_postfix))
			event->acceptProposedAction();
	}
	QWidget::dragEnterEvent(event);
}

void Inpainting::dropEvent(QDropEvent* event)
{
	QString filename = event->mimeData()->urls()[0].path();
	
	event->accept();
	QMessageBox::critical(this, "error", filename);	
}

void Inpainting::set_pixmap(QLabel* label_ptr, QPixmap& pixmap)
{
	label_ptr->setPixmap(pixmap);
	label_ptr->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

void Inpainting::set_originalsize_image()
{
	if (!original_pixmap.isNull()) set_pixmap(ui->inpaint_origin, original_pixmap);
	if (!mask_pixmap.isNull()) set_pixmap(ui->inpaint_mask, mask_pixmap);
	if (!masked_img_pixmap.isNull()) set_pixmap(ui->inpaint_masked, masked_img_pixmap);
	if (!output_pixmap.isNull()) set_pixmap(ui->inpaint_output, output_pixmap);
}

void Inpainting::set_screensize_image()
{
	//缩放原则，如果图片的长宽比比当前屏幕长寸的长宽比小，保持图片的长宽比，就是高为屏幕尺寸，宽就乘以图像的比例；如果图片的长宽比更大，就用屏幕的尺寸直接resize
	/*auto calc = [this, &pixmap](int& new_w, int& new_h) {
		float screen_w = static_cast<float>(ui->inpaint_origin->width());
		int screen_h = static_cast<float>(ui->inpaint_origin->height());
		float image_w = static_cast<float>(pixmap.width());
		float image_h = static_cast<float>(pixmap.height());
		float screen_ratio = screen_w / screen_h;
		float image_ratio = image_w / image_h;
		if (screen_ratio > image_ratio)
		{
			new_w = static_cast<int>(image_ratio * screen_h) - 5;
			new_h = static_cast<int>(screen_h) - 5;
		}
		else
		{
			new_w = screen_w - 5;
			new_h = screen_h - 5;
		}
	};
	calc(new_w, new_h);*/
	int screen_w = ui->inpaint_origin_scroll->width() - 30;
	int screen_h = ui->inpaint_origin_scroll->height() - 30;
	//qDebug() << "screen width: " << screen_w << ' ' << "screen height: " << screen_w << '\n';
	if (!original_pixmap.isNull())
	{
		//opencv这个要自己计算长宽比例，麻烦
		/*auto scaled_org_mat = wheels::Pixmap2Mat(original_pixmap);
		cv::resize(scaled_org_mat, scaled_org_mat, cv::Size(screen_w, screen_h), CV_INTER_LANCZOS4);
		auto scaled_org_pixmap = wheels::Mat2Pixmap(scaled_org_mat);*/
		auto scaled_org_pixmap = original_pixmap.scaled(screen_w, screen_h, Qt::KeepAspectRatio, Qt::SmoothTransformation);
		set_pixmap(ui->inpaint_origin, scaled_org_pixmap);
	}
	if (!mask_pixmap.isNull())
	{
		/*auto scaled_mask_mat = wheels::Pixmap2Mat(mask_pixmap);
		cv::resize(scaled_mask_mat, scaled_mask_mat, cv::Size(screen_w, screen_h), CV_INTER_LANCZOS4);
		auto scaled_mask_pixmap = wheels::Mat2Pixmap(scaled_mask_mat);*/
		auto scaled_mask_pixmap = mask_pixmap.scaled(screen_w, screen_h, Qt::KeepAspectRatio, Qt::SmoothTransformation);
		set_pixmap(ui->inpaint_mask, scaled_mask_pixmap);
	}
	if (!masked_img_pixmap.isNull())
	{
		/*auto scaled_masked_mat = wheels::Pixmap2Mat(masked_img_pixmap);
		cv::resize(scaled_masked_mat, scaled_masked_mat, cv::Size(screen_w, screen_h), CV_INTER_LANCZOS4);
		auto scaled_masked_pixmap = wheels::Mat2Pixmap(scaled_masked_mat);*/
		auto scaled_masked_pixmap = masked_img_pixmap.scaled(screen_w, screen_h, Qt::KeepAspectRatio, Qt::SmoothTransformation);
		set_pixmap(ui->inpaint_masked, scaled_masked_pixmap);
	}
	if (!output_pixmap.isNull())
	{
		/*auto scaled_output_mat = wheels::Pixmap2Mat(output_pixmap);
		cv::resize(scaled_output_mat, scaled_output_mat, cv::Size(screen_w, screen_h), CV_INTER_LANCZOS4);
		auto scaled_output_pixmap = wheels::Mat2Pixmap(scaled_output_mat);*/
		auto scaled_output_pixmap = output_pixmap.scaled(screen_w, screen_h, Qt::KeepAspectRatio, Qt::SmoothTransformation);
		set_pixmap(ui->inpaint_output, scaled_output_pixmap);
	}
}

void Inpainting::on_lightmode_rb_toggled(bool checked)
{
	QFile qss_file(":/stylesheets/stylesheets/style_light.qss");
	qss_file.open(QFile::ReadOnly);
	if (qss_file.isOpen())
	{
		QString qss_str = QLatin1String(qss_file.readAll());
		qApp->setStyleSheet(qss_str);
		qss_file.close();
		light_mode = true;
		dark_mode = false;
		resize(size() + QSize(1, 1));
		resize(size() - QSize(1, 1));
		//这个是为了强行调用paintEvent，切换效果
	}
}

void Inpainting::on_darkmode_rb_toggled(bool checked)
{
	QFile qss_file(":/stylesheets/stylesheets/style_dark.qss");
	qss_file.open(QFile::ReadOnly);
	if (qss_file.isOpen())
	{
		QString qss_str = QLatin1String(qss_file.readAll());
		qApp->setStyleSheet(qss_str);
		qss_file.close();
		dark_mode = true;
		light_mode = false;
		resize(size() + QSize(1, 1));
		resize(size() - QSize(1, 1));
	}
}

void Inpainting::on_inpaint_originsize_rb_toggled(bool checked)
{
	//点击才会触发，触发之后就发现如果checked了的话就可以了
	if (ui->inpaint_originsize_rb->isChecked()) //没有点，现在点了，原尺寸显示
	{
		ui->inpaint_originsize_rb->setChecked(true);
		ui->inpaint_screensize_rb->setChecked(false);
		//有图片，一开始又没有点，所以肯定不是original size；无图片，没有点，证明没上传，不用管
		set_originalsize_image();
	}
	else
	{
		ui->inpaint_originsize_rb->setChecked(false);
		ui->inpaint_screensize_rb->setChecked(true);
		set_screensize_image();
	}
}

void Inpainting::on_inpaint_screensize_rb_toggled(bool checked)
{
	//点击才会触发，触发之后就发现如果checked了的话就可以了
	if (ui->inpaint_screensize_rb->isChecked()) //没有点，现在点了，屏幕尺寸显示
	{
		ui->inpaint_screensize_rb->setChecked(true);
		ui->inpaint_originsize_rb->setChecked(false);
		//有图片，一开始又没有点，所以肯定不是original size；无图片，没有点，证明没上传，不用管
		set_screensize_image();
	}
	else
	{
		ui->inpaint_screensize_rb->setChecked(false);
		ui->inpaint_originsize_rb->setChecked(true);
		set_originalsize_image();
	}
}

void Inpainting::on_inpaint_weights_select_currentTextChanged(QString text)
{
	partialconv->regenerate(text.toStdString());
}

void Inpainting::upload_origin_img(QString pos)
{
	QString cur_path = QDir::currentPath();
	QString title = "load original image";
	QString filt = "pictures(*.jpg *.jpeg *.png)";
	QString filename = QFileDialog::getOpenFileName(this, title, cur_path, filt);
	if (filename == "") return;
	if (pos == "origin")//专门说明pos是因为我上传的时候不知道是哪个
	{
		original_img_path = filename.toStdString();
		original_pixmap.load(filename);
		original_w = original_pixmap.width();
		original_h = original_pixmap.height();
	}
	else if (pos == "mask")
	{
		mask_img_path = filename.toStdString();
		cv::Mat x = cv::imread(mask_img_path, 0);
		mask_pixmap = wheels::Mat2Pixmap(x);
	}
	if (ui->inpaint_originsize_rb->isChecked() && !ui->inpaint_screensize_rb->isChecked())
		set_originalsize_image();
	else if (!ui->inpaint_originsize_rb->isChecked() && ui->inpaint_screensize_rb->isChecked())
		set_screensize_image();
	if (original_pixmap.isNull() || mask_pixmap.isNull()) return;
}

void Inpainting::make_inpainting()
{
	auto scaled_orgpixmap = original_pixmap.scaled(inpainted_img_w, inpainted_img_h, Qt::KeepAspectRatio,Qt::SmoothTransformation);
	auto scaled_mskpixmap = mask_pixmap.scaled(inpainted_img_w, inpainted_img_h, Qt::KeepAspectRatio,Qt::SmoothTransformation);
	auto org_mat = wheels::Pixmap2Mat(scaled_orgpixmap);
	auto mask_mat = wheels::Pixmap2Mat(scaled_mskpixmap);
	/*auto org_mat = wheels::Pixmap2Mat(original_pixmap);
	auto mask_mat = wheels::Pixmap2Mat(mask_pixmap);
	cv::resize(org_mat, org_mat, cv::Size(inpainted_img_w, inpainted_img_h), CV_INTER_LANCZOS4);
	cv::resize(mask_mat, mask_mat, cv::Size(inpainted_img_w, inpainted_img_h), CV_INTER_LANCZOS4);*/
	auto& [masked_img, output_img] = partialconv->run(org_mat, mask_mat);
	masked_img_pixmap = wheels::Mat2Pixmap(masked_img);
	masked_img_pixmap = masked_img_pixmap.scaled(original_w, original_h, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	output_pixmap = wheels::Mat2Pixmap(output_img);
	output_pixmap = output_pixmap.scaled(original_w, original_h, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	if (ui->inpaint_originsize_rb->isChecked() && !ui->inpaint_screensize_rb->isChecked())
	{
		set_pixmap(ui->inpaint_masked, masked_img_pixmap);
		set_pixmap(ui->inpaint_output, output_pixmap);
	}
	else if (!ui->inpaint_originsize_rb->isChecked() && ui->inpaint_screensize_rb->isChecked())
	{
		set_screensize_image();
	}
}

void Inpainting::on_inpaint_run_clicked()
{
	if (!original_pixmap.isNull() && !mask_pixmap.isNull())
		make_inpainting();
}

void Inpainting::on_inpaint_clear_clicked()
{
	ui->inpaint_origin->clear();
	ui->inpaint_mask->clear();
	ui->inpaint_masked->clear();
	ui->inpaint_output->clear();
	QPixmap temp = QPixmap();
	original_pixmap = temp;
	mask_pixmap = temp;
	masked_img_pixmap = temp;
	output_pixmap = temp;
}

void Inpainting::on_inpaint_save_clicked()
{
	QString cur_path = QDir::currentPath();
	QString title = "save image";
	QString filt = "pictures(*.png *.jpg *.jpeg)";
	QString filename = QFileDialog::getSaveFileName(this, title, cur_path, filt);
	if (filename == "") return;
	output_pixmap.save(filename, nullptr, 100);
}

void Inpainting::on_inpaint_org_larger_btn_clicked()
{
	if (original_pixmap.isNull()) return;
	InpaintingSubWindow* subwindow = new InpaintingSubWindow;
	subwindow->setWindowFlag(Qt::Window, true);
	subwindow->setWindowFlag(Qt::WindowContextHelpButtonHint, false);
	subwindow->setAttribute(Qt::WA_DeleteOnClose);
	subwindow->setWindowTitle("Original Image");
	subwindow->set_img(original_pixmap);
	subwindow->show();
}

void Inpainting::on_inpaint_masked_larger_btn_clicked()
{
	if (masked_img_pixmap.isNull()) return;
	InpaintingSubWindow* subwindow = new InpaintingSubWindow;
	subwindow->setWindowFlag(Qt::Window, true);
	subwindow->setWindowFlag(Qt::WindowContextHelpButtonHint, false);
	subwindow->setAttribute(Qt::WA_DeleteOnClose);
	subwindow->setWindowTitle("Masked Image");
	subwindow->set_img(masked_img_pixmap);
	subwindow->show();
}

void Inpainting::on_inpaint_output_larger_btn_clicked()
{
	if (output_pixmap.isNull()) return;
	InpaintingSubWindow* subwindow = new InpaintingSubWindow;
	subwindow->setWindowFlag(Qt::Window, true);
	subwindow->setWindowFlag(Qt::WindowContextHelpButtonHint, false);
	subwindow->setAttribute(Qt::WA_DeleteOnClose);
	subwindow->setWindowTitle("Output Image");
	subwindow->set_img(output_pixmap);
	subwindow->show();
}