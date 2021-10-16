/********************************************************************************
** Form generated from reading UI file 'Inpainting.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPAINTING_H
#define UI_INPAINTING_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InpaintingWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *closewindow;
    QLabel *maximize;
    QLabel *minimize;
    QSpacerItem *horizontalSpacer_5;
    QRadioButton *lightmode_rb;
    QRadioButton *darkmode_rb;
    QTabWidget *tabWidget;
    QWidget *inpainting;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_5;
    QRadioButton *originsize_inpaint_rb;
    QRadioButton *screensize_inpaint_rb;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *run_inpaint;
    QPushButton *clear_inpaint;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QScrollArea *scrollop;
    QWidget *inpainted_origin_scroll;
    QVBoxLayout *verticalLayout_2;
    QLabel *inpainted_origin;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_2;
    QScrollArea *scrollmask;
    QWidget *inpainted_mask_scroll;
    QVBoxLayout *verticalLayout_6;
    QLabel *inpainted_mask;
    QWidget *SR;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *horizontalLayout_6;
    QRadioButton *originsize_SR_rb;
    QRadioButton *screensize_SR_rb;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *clear_SR;
    QPushButton *save_SR;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_3;
    QScrollArea *scrollArea_3;
    QWidget *scrollAreaWidgetContents_3;
    QVBoxLayout *verticalLayout_5;
    QLabel *SR_origin;
    QSpacerItem *horizontalSpacer_6;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_4;
    QScrollArea *scrollArea_4;
    QWidget *scrollAreaWidgetContents_4;
    QVBoxLayout *verticalLayout_10;
    QLabel *SR_output;

    void setupUi(QWidget *InpaintingWidget)
    {
        if (InpaintingWidget->objectName().isEmpty())
            InpaintingWidget->setObjectName(QString::fromUtf8("InpaintingWidget"));
        InpaintingWidget->resize(1413, 819);
        verticalLayout = new QVBoxLayout(InpaintingWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        closewindow = new QLabel(InpaintingWidget);
        closewindow->setObjectName(QString::fromUtf8("closewindow"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(closewindow->sizePolicy().hasHeightForWidth());
        closewindow->setSizePolicy(sizePolicy);
        closewindow->setMinimumSize(QSize(28, 24));
        closewindow->setMaximumSize(QSize(28, 24));
        closewindow->setScaledContents(true);

        horizontalLayout_3->addWidget(closewindow);

        maximize = new QLabel(InpaintingWidget);
        maximize->setObjectName(QString::fromUtf8("maximize"));
        sizePolicy.setHeightForWidth(maximize->sizePolicy().hasHeightForWidth());
        maximize->setSizePolicy(sizePolicy);
        maximize->setMinimumSize(QSize(24, 24));
        maximize->setMaximumSize(QSize(24, 24));
        maximize->setScaledContents(true);

        horizontalLayout_3->addWidget(maximize);

        minimize = new QLabel(InpaintingWidget);
        minimize->setObjectName(QString::fromUtf8("minimize"));
        sizePolicy.setHeightForWidth(minimize->sizePolicy().hasHeightForWidth());
        minimize->setSizePolicy(sizePolicy);
        minimize->setMinimumSize(QSize(24, 24));
        minimize->setMaximumSize(QSize(24, 24));
        minimize->setScaledContents(true);

        horizontalLayout_3->addWidget(minimize);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        lightmode_rb = new QRadioButton(InpaintingWidget);
        lightmode_rb->setObjectName(QString::fromUtf8("lightmode_rb"));
        lightmode_rb->setMinimumSize(QSize(0, 24));
        QFont font;
        font.setFamily(QString::fromUtf8("Lucida Fax"));
        font.setPointSize(12);
        lightmode_rb->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/light_bulb.ico"), QSize(), QIcon::Normal, QIcon::Off);
        lightmode_rb->setIcon(icon);

        horizontalLayout_3->addWidget(lightmode_rb);

        darkmode_rb = new QRadioButton(InpaintingWidget);
        darkmode_rb->setObjectName(QString::fromUtf8("darkmode_rb"));
        darkmode_rb->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/icons/dark_bulb.ico"), QSize(), QIcon::Normal, QIcon::Off);
        darkmode_rb->setIcon(icon1);

        horizontalLayout_3->addWidget(darkmode_rb);


        verticalLayout->addLayout(horizontalLayout_3);

        tabWidget = new QTabWidget(InpaintingWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font1.setPointSize(12);
        tabWidget->setFont(font1);
        inpainting = new QWidget();
        inpainting->setObjectName(QString::fromUtf8("inpainting"));
        verticalLayout_8 = new QVBoxLayout(inpainting);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setSizeConstraint(QLayout::SetMinimumSize);
        originsize_inpaint_rb = new QRadioButton(inpainting);
        originsize_inpaint_rb->setObjectName(QString::fromUtf8("originsize_inpaint_rb"));
        originsize_inpaint_rb->setFont(font1);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/icons/origin.ico"), QSize(), QIcon::Normal, QIcon::Off);
        originsize_inpaint_rb->setIcon(icon2);

        horizontalLayout_5->addWidget(originsize_inpaint_rb);

        screensize_inpaint_rb = new QRadioButton(inpainting);
        screensize_inpaint_rb->setObjectName(QString::fromUtf8("screensize_inpaint_rb"));
        screensize_inpaint_rb->setFont(font1);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/icons/screen.ico"), QSize(), QIcon::Normal, QIcon::Off);
        screensize_inpaint_rb->setIcon(icon3);

        horizontalLayout_5->addWidget(screensize_inpaint_rb);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        run_inpaint = new QPushButton(inpainting);
        run_inpaint->setObjectName(QString::fromUtf8("run_inpaint"));
        run_inpaint->setMinimumSize(QSize(100, 35));
        run_inpaint->setMaximumSize(QSize(100, 35));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/icons/inpaint_run.ico"), QSize(), QIcon::Normal, QIcon::Off);
        run_inpaint->setIcon(icon4);

        horizontalLayout_5->addWidget(run_inpaint);

        clear_inpaint = new QPushButton(inpainting);
        clear_inpaint->setObjectName(QString::fromUtf8("clear_inpaint"));
        clear_inpaint->setMinimumSize(QSize(100, 35));
        clear_inpaint->setMaximumSize(QSize(100, 35));
        clear_inpaint->setFont(font1);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/icons/clear.ico"), QSize(), QIcon::Normal, QIcon::Off);
        clear_inpaint->setIcon(icon5);

        horizontalLayout_5->addWidget(clear_inpaint);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 2);
        horizontalLayout_5->setStretch(2, 11);

        verticalLayout_8->addLayout(horizontalLayout_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label = new QLabel(inpainting);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label);

        scrollop = new QScrollArea(inpainting);
        scrollop->setObjectName(QString::fromUtf8("scrollop"));
        scrollop->setWidgetResizable(true);
        inpainted_origin_scroll = new QWidget();
        inpainted_origin_scroll->setObjectName(QString::fromUtf8("inpainted_origin_scroll"));
        inpainted_origin_scroll->setGeometry(QRect(0, 0, 650, 615));
        verticalLayout_2 = new QVBoxLayout(inpainted_origin_scroll);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        inpainted_origin = new QLabel(inpainted_origin_scroll);
        inpainted_origin->setObjectName(QString::fromUtf8("inpainted_origin"));
        inpainted_origin->setStyleSheet(QString::fromUtf8("background-color:rgb(240,240,240);"));

        verticalLayout_2->addWidget(inpainted_origin);

        scrollop->setWidget(inpainted_origin_scroll);

        verticalLayout_3->addWidget(scrollop);


        horizontalLayout->addLayout(verticalLayout_3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        label_2 = new QLabel(inpainting);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(label_2);

        scrollmask = new QScrollArea(inpainting);
        scrollmask->setObjectName(QString::fromUtf8("scrollmask"));
        scrollmask->setWidgetResizable(true);
        inpainted_mask_scroll = new QWidget();
        inpainted_mask_scroll->setObjectName(QString::fromUtf8("inpainted_mask_scroll"));
        inpainted_mask_scroll->setGeometry(QRect(0, 0, 649, 615));
        verticalLayout_6 = new QVBoxLayout(inpainted_mask_scroll);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        inpainted_mask = new QLabel(inpainted_mask_scroll);
        inpainted_mask->setObjectName(QString::fromUtf8("inpainted_mask"));
        inpainted_mask->setStyleSheet(QString::fromUtf8("background-color:rgb(240,240,240);"));

        verticalLayout_6->addWidget(inpainted_mask);

        scrollmask->setWidget(inpainted_mask_scroll);

        verticalLayout_7->addWidget(scrollmask);


        horizontalLayout->addLayout(verticalLayout_7);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(2, 1);

        verticalLayout_8->addLayout(horizontalLayout);

        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/icons/Inpainting.ico"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(inpainting, icon6, QString());
        SR = new QWidget();
        SR->setObjectName(QString::fromUtf8("SR"));
        verticalLayout_11 = new QVBoxLayout(SR);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setSizeConstraint(QLayout::SetMinimumSize);
        originsize_SR_rb = new QRadioButton(SR);
        originsize_SR_rb->setObjectName(QString::fromUtf8("originsize_SR_rb"));
        originsize_SR_rb->setFont(font1);
        originsize_SR_rb->setIcon(icon2);

        horizontalLayout_6->addWidget(originsize_SR_rb);

        screensize_SR_rb = new QRadioButton(SR);
        screensize_SR_rb->setObjectName(QString::fromUtf8("screensize_SR_rb"));
        screensize_SR_rb->setFont(font1);
        screensize_SR_rb->setIcon(icon3);

        horizontalLayout_6->addWidget(screensize_SR_rb);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);

        clear_SR = new QPushButton(SR);
        clear_SR->setObjectName(QString::fromUtf8("clear_SR"));
        clear_SR->setMinimumSize(QSize(100, 35));
        clear_SR->setMaximumSize(QSize(100, 35));
        clear_SR->setFont(font1);
        clear_SR->setIcon(icon5);

        horizontalLayout_6->addWidget(clear_SR);

        save_SR = new QPushButton(SR);
        save_SR->setObjectName(QString::fromUtf8("save_SR"));
        sizePolicy.setHeightForWidth(save_SR->sizePolicy().hasHeightForWidth());
        save_SR->setSizePolicy(sizePolicy);
        save_SR->setMinimumSize(QSize(100, 35));
        save_SR->setMaximumSize(QSize(100, 35));
        save_SR->setFont(font1);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/icons/save.ico"), QSize(), QIcon::Normal, QIcon::Off);
        save_SR->setIcon(icon7);

        horizontalLayout_6->addWidget(save_SR);

        horizontalLayout_6->setStretch(1, 2);
        horizontalLayout_6->setStretch(2, 11);
        horizontalLayout_6->setStretch(4, 4);

        verticalLayout_11->addLayout(horizontalLayout_6);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_3 = new QLabel(SR);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label_3);

        scrollArea_3 = new QScrollArea(SR);
        scrollArea_3->setObjectName(QString::fromUtf8("scrollArea_3"));
        scrollArea_3->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 650, 615));
        verticalLayout_5 = new QVBoxLayout(scrollAreaWidgetContents_3);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        SR_origin = new QLabel(scrollAreaWidgetContents_3);
        SR_origin->setObjectName(QString::fromUtf8("SR_origin"));
        SR_origin->setStyleSheet(QString::fromUtf8("background-color:rgb(240,240,240);"));

        verticalLayout_5->addWidget(SR_origin);

        scrollArea_3->setWidget(scrollAreaWidgetContents_3);

        verticalLayout_4->addWidget(scrollArea_3);


        horizontalLayout_2->addLayout(verticalLayout_4);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        label_4 = new QLabel(SR);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_9->addWidget(label_4);

        scrollArea_4 = new QScrollArea(SR);
        scrollArea_4->setObjectName(QString::fromUtf8("scrollArea_4"));
        scrollArea_4->setWidgetResizable(true);
        scrollAreaWidgetContents_4 = new QWidget();
        scrollAreaWidgetContents_4->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_4"));
        scrollAreaWidgetContents_4->setGeometry(QRect(0, 0, 649, 615));
        verticalLayout_10 = new QVBoxLayout(scrollAreaWidgetContents_4);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        SR_output = new QLabel(scrollAreaWidgetContents_4);
        SR_output->setObjectName(QString::fromUtf8("SR_output"));
        SR_output->setStyleSheet(QString::fromUtf8("background-color:rgb(240,240,240);"));

        verticalLayout_10->addWidget(SR_output);

        scrollArea_4->setWidget(scrollAreaWidgetContents_4);

        verticalLayout_9->addWidget(scrollArea_4);


        horizontalLayout_2->addLayout(verticalLayout_9);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(2, 1);

        verticalLayout_11->addLayout(horizontalLayout_2);

        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icons/icons/SR.ico"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(SR, icon8, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(InpaintingWidget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(InpaintingWidget);
    } // setupUi

    void retranslateUi(QWidget *InpaintingWidget)
    {
        InpaintingWidget->setWindowTitle(QCoreApplication::translate("InpaintingWidget", "Inpainting", nullptr));
        closewindow->setText(QString());
        maximize->setText(QString());
        minimize->setText(QString());
        lightmode_rb->setText(QCoreApplication::translate("InpaintingWidget", "light mode", nullptr));
        darkmode_rb->setText(QCoreApplication::translate("InpaintingWidget", "dark mode", nullptr));
        originsize_inpaint_rb->setText(QCoreApplication::translate("InpaintingWidget", "\344\273\245\345\216\237\345\233\276\345\260\272\345\257\270\346\230\276\347\244\272", nullptr));
        screensize_inpaint_rb->setText(QCoreApplication::translate("InpaintingWidget", "\344\273\245\345\275\223\345\211\215\345\261\217\345\271\225\345\260\272\345\257\270\346\230\276\347\244\272", nullptr));
        run_inpaint->setText(QCoreApplication::translate("InpaintingWidget", "\344\277\256\345\244\215", nullptr));
        clear_inpaint->setText(QCoreApplication::translate("InpaintingWidget", "\346\270\205\347\251\272", nullptr));
        label->setText(QCoreApplication::translate("InpaintingWidget", "original image", nullptr));
        inpainted_origin->setText(QString());
        label_2->setText(QCoreApplication::translate("InpaintingWidget", "mask image", nullptr));
        inpainted_mask->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(inpainting), QCoreApplication::translate("InpaintingWidget", "\345\233\276\345\203\217\344\277\256\345\244\215", nullptr));
        originsize_SR_rb->setText(QCoreApplication::translate("InpaintingWidget", "\344\273\245\345\216\237\345\233\276\345\260\272\345\257\270\346\230\276\347\244\272", nullptr));
        screensize_SR_rb->setText(QCoreApplication::translate("InpaintingWidget", "\344\273\245\345\275\223\345\211\215\345\261\217\345\271\225\345\260\272\345\257\270\346\230\276\347\244\272", nullptr));
        clear_SR->setText(QCoreApplication::translate("InpaintingWidget", "\346\270\205\347\251\272", nullptr));
        save_SR->setText(QCoreApplication::translate("InpaintingWidget", "\344\277\235\345\255\230", nullptr));
        label_3->setText(QCoreApplication::translate("InpaintingWidget", "original image", nullptr));
        SR_origin->setText(QString());
        label_4->setText(QCoreApplication::translate("InpaintingWidget", "output image", nullptr));
        SR_output->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(SR), QCoreApplication::translate("InpaintingWidget", "\350\266\205\345\210\206\350\276\250\347\216\207", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InpaintingWidget: public Ui_InpaintingWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPAINTING_H
