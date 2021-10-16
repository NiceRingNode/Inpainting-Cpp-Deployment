#pragma once

#ifndef _INPAINTINGSUBWINDOW_H_
#define _INPAINTINGSUBWINDOW_H_

#include<QtWidgets/QWidget>
#include<QtGui/QPixmap>
#include"ui_InpaintingSubWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class InpaintingSubWindowWidget; }
QT_END_NAMESPACE

class InpaintingSubWindow : public QWidget
{
	Q_OBJECT

public:
	InpaintingSubWindow(QWidget* parent = nullptr);
	~InpaintingSubWindow();

	void set_img(QPixmap& pixmap);
	void set_pixmap(QLabel*, QPixmap&);
	inline void set_w(int w) { img_w = w; }
	inline void set_h(int h) { img_h = h; }
	void set_screensize_image();
	void set_originalsize_image();
	
private slots:
	void paintEvent(QPaintEvent* event) override;
	void mouseDoubleClickEvent(QMouseEvent* event) override;
	void on_originsize_rb_toggled([[maybe_unused]] bool checked);
	void on_screensize_rb_toggled([[maybe_unused]] bool checked);

private:
	Ui::InpaintingSubWindowWidget* ui;
	QPixmap img_pixmap;//放大来看
	int img_w;
	int img_h;
	QString type;
};

#endif // _INPAINTINGSUBWINDOW_H_