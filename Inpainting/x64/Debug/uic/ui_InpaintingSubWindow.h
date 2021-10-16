/********************************************************************************
** Form generated from reading UI file 'InpaintingSubWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPAINTINGSUBWINDOW_H
#define UI_INPAINTINGSUBWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InpaintingSubWindowWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QRadioButton *originsize_rb;
    QRadioButton *screensize_rb;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_2;
    QScrollArea *output_scroll;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_5;
    QLabel *output_image;

    void setupUi(QWidget *InpaintingSubWindowWidget)
    {
        if (InpaintingSubWindowWidget->objectName().isEmpty())
            InpaintingSubWindowWidget->setObjectName(QString::fromUtf8("InpaintingSubWindowWidget"));
        InpaintingSubWindowWidget->resize(892, 839);
        verticalLayout = new QVBoxLayout(InpaintingSubWindowWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setSizeConstraint(QLayout::SetMinimumSize);
        originsize_rb = new QRadioButton(InpaintingSubWindowWidget);
        originsize_rb->setObjectName(QString::fromUtf8("originsize_rb"));
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font.setPointSize(12);
        originsize_rb->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/origin.ico"), QSize(), QIcon::Normal, QIcon::Off);
        originsize_rb->setIcon(icon);

        horizontalLayout_5->addWidget(originsize_rb);

        screensize_rb = new QRadioButton(InpaintingSubWindowWidget);
        screensize_rb->setObjectName(QString::fromUtf8("screensize_rb"));
        screensize_rb->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/icons/screen.ico"), QSize(), QIcon::Normal, QIcon::Off);
        screensize_rb->setIcon(icon1);

        horizontalLayout_5->addWidget(screensize_rb);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 2);
        horizontalLayout_5->setStretch(2, 11);

        verticalLayout->addLayout(horizontalLayout_5);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_2 = new QLabel(InpaintingSubWindowWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label_2);

        output_scroll = new QScrollArea(InpaintingSubWindowWidget);
        output_scroll->setObjectName(QString::fromUtf8("output_scroll"));
        output_scroll->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 866, 739));
        verticalLayout_5 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        output_image = new QLabel(scrollAreaWidgetContents_2);
        output_image->setObjectName(QString::fromUtf8("output_image"));
        output_image->setStyleSheet(QString::fromUtf8("background-color:rgb(240,240,240);"));

        verticalLayout_5->addWidget(output_image);

        output_scroll->setWidget(scrollAreaWidgetContents_2);

        verticalLayout_4->addWidget(output_scroll);


        verticalLayout->addLayout(verticalLayout_4);


        retranslateUi(InpaintingSubWindowWidget);

        QMetaObject::connectSlotsByName(InpaintingSubWindowWidget);
    } // setupUi

    void retranslateUi(QWidget *InpaintingSubWindowWidget)
    {
        InpaintingSubWindowWidget->setWindowTitle(QCoreApplication::translate("InpaintingSubWindowWidget", "InpaintingSubWindow", nullptr));
        originsize_rb->setText(QCoreApplication::translate("InpaintingSubWindowWidget", "\344\273\245\345\216\237\345\233\276\345\260\272\345\257\270\346\230\276\347\244\272", nullptr));
        screensize_rb->setText(QCoreApplication::translate("InpaintingSubWindowWidget", "\344\273\245\345\275\223\345\211\215\345\261\217\345\271\225\345\260\272\345\257\270\346\230\276\347\244\272", nullptr));
        label_2->setText(QCoreApplication::translate("InpaintingSubWindowWidget", "output image", nullptr));
        output_image->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class InpaintingSubWindowWidget: public Ui_InpaintingSubWindowWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPAINTINGSUBWINDOW_H
