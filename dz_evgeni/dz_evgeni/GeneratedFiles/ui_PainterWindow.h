/********************************************************************************
** Form generated from reading UI file 'PainterWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAINTERWINDOW_H
#define UI_PAINTERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PainterWindow
{
public:
    QLineEdit *lineEdit;
    QLabel *label;
    QTextBrowser *textBrowser;
    QPushButton *pushButton;

    void setupUi(QWidget *PainterWindow)
    {
        if (PainterWindow->objectName().isEmpty())
            PainterWindow->setObjectName(QStringLiteral("PainterWindow"));
        PainterWindow->resize(1812, 922);
        lineEdit = new QLineEdit(PainterWindow);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(1540, 110, 231, 21));
        label = new QLabel(PainterWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(1540, 70, 261, 31));
        textBrowser = new QTextBrowser(PainterWindow);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(1540, 170, 231, 91));
        pushButton = new QPushButton(PainterWindow);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(1540, 130, 231, 41));

        retranslateUi(PainterWindow);

        QMetaObject::connectSlotsByName(PainterWindow);
    } // setupUi

    void retranslateUi(QWidget *PainterWindow)
    {
        PainterWindow->setWindowTitle(QApplication::translate("PainterWindow", "PainterWindow", 0));
        label->setText(QApplication::translate("PainterWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\267\320\275\320\260\321\207\320\265\320\275\320\270\321\217 \320\277\320\265\321\200\320\265\320\274\320\265\320\275\320\275\321\213\321\205", 0));
        textBrowser->setHtml(QApplication::translate("PainterWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\320\237\321\200\320\270\320\274\320\265\321\200 \320\262\320\262\320\276\320\264\320\260 \320\264\320\273\321\217 \320\277\320\265\321\200\320\274\320\265\320\275\320\275\321\213\321\205 \320\220 \320\222 \320\241<br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">A=1 B=0 C=1</p></body></html>", 0));
        pushButton->setText(QApplication::translate("PainterWindow", "\320\237\320\276\321\201\321\207\320\270\321\202\320\260\321\202\321\214", 0));
    } // retranslateUi

};

namespace Ui {
    class PainterWindow: public Ui_PainterWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAINTERWINDOW_H
