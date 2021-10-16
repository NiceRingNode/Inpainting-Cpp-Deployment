#pragma once

#ifndef _INPAINTING_H_
#define _INPAINTING_H_

#include<QtWidgets/QWidget>
#include<QtCore/QPoint>
#include"ui_Inpainting.h"
#include"PConvApplication.h"
#include"InpaintingSubWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class InpaintingWidget; }
QT_END_NAMESPACE

namespace wheels
{
enum class Directs
{
	None, Left, Right, Top, Bottom, TopLeft, TopRight, BottomLeft, BottomRight
};

struct PressState
{
	bool mouse_pressed;
	bool border_pressed;
	QPoint mouse_pos;
	QPoint window_pos;
	QSize pressed_size;
};
}

class Inpainting : public QWidget
{
    Q_OBJECT

public:
    Inpainting(QWidget *parent = nullptr);
	~Inpainting();

private slots:
	bool eventFilter(QObject* watched, QEvent* event) override;
	void paintEvent(QPaintEvent* event) override;
	void dragEnterEvent(QDragEnterEvent* event) override;
	void dropEvent(QDropEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseDoubleClickEvent(QMouseEvent* event) override;
	void on_lightmode_rb_toggled([[maybe_unused]] bool checked);
	void on_darkmode_rb_toggled([[maybe_unused]] bool checked);
	void on_inpaint_originsize_rb_toggled([[maybe_unused]] bool checked);
	void on_inpaint_screensize_rb_toggled([[maybe_unused]] bool checked);
	void on_inpaint_run_clicked();
	void on_inpaint_clear_clicked();
	void on_inpaint_save_clicked();
	void on_inpaint_org_larger_btn_clicked();
	void on_inpaint_masked_larger_btn_clicked();
	void on_inpaint_output_larger_btn_clicked();
	void on_inpaint_weights_select_currentTextChanged(QString text);

private:
	void init_ui();
	void upload_origin_img(QString pos = "origin");
	inline bool check_original_path() { return original_img_path.empty(); }
	inline bool check_mask_path() { return mask_img_path.empty(); }
	void set_screensize_image();
	void set_originalsize_image();
	void make_inpainting();
	void set_frameless();
	void set_shadow();
	void set_pixmap(QLabel*, QPixmap&);
	void set_border(int);
	void resize_window(const QPoint& pos);

private:
	Ui::InpaintingWidget* ui;
	wheels::PConvApplication* partialconv;
	std::string original_img_path;//path是因为要用opencv来读取灰度图
	std::string mask_img_path;
	const int inpainted_img_h = 256;
	const int inpainted_img_w = 256;
	const QVector<QString> postfixs;
	QPixmap original_pixmap;
	QPixmap mask_pixmap;
	QPixmap masked_img_pixmap;
	QPixmap output_pixmap;
	int original_w;
	int original_h;
	
	int border;
	wheels::PressState pressed_state;
	wheels::Directs mouse_direct;

	bool light_mode;
	bool dark_mode;
};

#endif //_INPAINTING_H_