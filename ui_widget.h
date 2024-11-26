/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *btn_start;
    QLabel *lb_score;
    QLabel *lb_time_sys;
    QLabel *lb_time_game;
    QLabel *lb_score_2;
    QLabel *lb_score_3;
    QLabel *lb_score_4;
    QLabel *lb_score_5;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(528, 600);
        Widget->setStyleSheet(QString::fromUtf8("#Widget{background-color: rgb(0, 153, 230);}"));
        btn_start = new QPushButton(Widget);
        btn_start->setObjectName(QString::fromUtf8("btn_start"));
        btn_start->setGeometry(QRect(340, 530, 81, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\346\226\207\350\241\214\346\245\267"));
        font.setPointSize(12);
        btn_start->setFont(font);
        btn_start->setStyleSheet(QString::fromUtf8("border-radius:3px;\n"
"color: rgb(0, 20, 20);\n"
"background-color: rgb(140, 255, 155);"));
        lb_score = new QLabel(Widget);
        lb_score->setObjectName(QString::fromUtf8("lb_score"));
        lb_score->setGeometry(QRect(316, 140, 111, 21));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\226\260\351\255\217"));
        font1.setPointSize(12);
        lb_score->setFont(font1);
        lb_time_sys = new QLabel(Widget);
        lb_time_sys->setObjectName(QString::fromUtf8("lb_time_sys"));
        lb_time_sys->setGeometry(QRect(316, 30, 151, 21));
        lb_time_sys->setFont(font1);
        lb_time_game = new QLabel(Widget);
        lb_time_game->setObjectName(QString::fromUtf8("lb_time_game"));
        lb_time_game->setGeometry(QRect(316, 85, 151, 21));
        lb_time_game->setFont(font1);
        lb_score_2 = new QLabel(Widget);
        lb_score_2->setObjectName(QString::fromUtf8("lb_score_2"));
        lb_score_2->setGeometry(QRect(310, 240, 141, 21));
        lb_score_2->setFont(font1);
        lb_score_3 = new QLabel(Widget);
        lb_score_3->setObjectName(QString::fromUtf8("lb_score_3"));
        lb_score_3->setGeometry(QRect(310, 270, 161, 21));
        lb_score_3->setFont(font1);
        lb_score_4 = new QLabel(Widget);
        lb_score_4->setObjectName(QString::fromUtf8("lb_score_4"));
        lb_score_4->setGeometry(QRect(310, 300, 141, 21));
        lb_score_4->setFont(font1);
        lb_score_5 = new QLabel(Widget);
        lb_score_5->setObjectName(QString::fromUtf8("lb_score_5"));
        lb_score_5->setGeometry(QRect(350, 210, 141, 21));
        lb_score_5->setFont(font1);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "\344\277\204\347\275\227\346\226\257\346\226\271\345\235\227", nullptr));
        btn_start->setText(QCoreApplication::translate("Widget", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
        lb_score->setText(QCoreApplication::translate("Widget", "\345\276\227\345\210\206\357\274\2320", nullptr));
        lb_time_sys->setText(QCoreApplication::translate("Widget", "\347\263\273\347\273\237\346\227\266\351\227\264", nullptr));
        lb_time_game->setText(QCoreApplication::translate("Widget", "\346\270\270\346\210\217\346\227\266\351\227\264:0\345\210\2060\347\247\222", nullptr));
        lb_score_2->setText(QCoreApplication::translate("Widget", "B22080228 \345\276\220\345\237\272\346\201\222", nullptr));
        lb_score_3->setText(QCoreApplication::translate("Widget", "B22080204 \346\254\247\351\230\263\350\212\263\350\217\262", nullptr));
        lb_score_4->setText(QCoreApplication::translate("Widget", "B22080214 \347\245\201\346\226\207\347\235\277", nullptr));
        lb_score_5->setText(QCoreApplication::translate("Widget", "\345\260\217\347\273\204\346\210\220\345\221\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
