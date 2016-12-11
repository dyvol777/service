/********************************************************************************
** Form generated from reading UI file 'WelcomeWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WELCOMEWINDOW_H
#define UI_WELCOMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WelcomeWindowClass
{
public:
    QWidget *centralWidget;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QListWidget *listWidget;
    QTextBrowser *textBrowser;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *WelcomeWindowClass)
    {
        if (WelcomeWindowClass->objectName().isEmpty())
            WelcomeWindowClass->setObjectName(QStringLiteral("WelcomeWindowClass"));
        WelcomeWindowClass->resize(916, 432);
        centralWidget = new QWidget(WelcomeWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(20, 30, 421, 25));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(470, 30, 221, 34));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(470, 70, 221, 34));
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(20, 70, 421, 301));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(470, 120, 301, 231));
        WelcomeWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(WelcomeWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 916, 31));
        WelcomeWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(WelcomeWindowClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        WelcomeWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(WelcomeWindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        WelcomeWindowClass->setStatusBar(statusBar);

        retranslateUi(WelcomeWindowClass);

        QMetaObject::connectSlotsByName(WelcomeWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *WelcomeWindowClass)
    {
        WelcomeWindowClass->setWindowTitle(QApplication::translate("WelcomeWindowClass", "WelcomeWindow", 0));
        pushButton->setText(QApplication::translate("WelcomeWindowClass", "\320\222\321\213\321\207\320\270\321\201\320\273\320\270\321\202\321\214 \320\270 \320\275\320\260\321\200\320\270\321\201\320\276\320\262\320\260\321\202\321\214", 0));
        pushButton_2->setText(QApplication::translate("WelcomeWindowClass", "\320\236\321\202\320\276\320\261\321\200\320\260\320\267\320\270\321\202\321\214 \321\201\321\205\320\265\320\274\321\203", 0));
        textBrowser->setHtml(QApplication::translate("WelcomeWindowClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\320\237\321\200\320\260\320\262\320\270\320\273\320\260 \320\262\320\262\320\276\320\264\320\260 \321\204\321\203\320\275\320\272\321\206\320\270\320\270:<br />1) \320\237\320\265\321\200\320\265\320\274\320\265\320\275\320\275\321\213\320\265: A,B,C,...,Y,Z<br />2) \320\236\320\277\320\265\321\200\320\260\321\202\320\276\321\200\321\213:<br />    &quot;&amp;&quot; - \320\272\320\276\320\275\321\212\321\216\320\275\320\272\321\206\320\270\321\217<br />    &quot;|&quot; - \320\264\320\270\320\267\321\212\321\216\320\275\320\272\320\270\321\217</p>\n"
"<p st"
                        "yle=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">    &quot;+&quot; - \320\270\321\201\320\272\320\273\321\216\321\207\320\260\321\216\321\211\320\265\320\265 &quot;\320\230\320\233\320\230&quot;</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">    &quot;-&quot; - \321\215\320\272\320\262\320\270\320\262\320\260\320\273\320\265\320\275\321\202\320\275\320\276\321\201\321\202\321\214<br />3) \320\244\321\203\320\275\320\272\321\206\320\270\321\217 \320\262\320\262\320\276\320\264\320\270\321\202\321\201\321\217 \320\261\320\265\320\267 \320\277\321\200\320\276\320\261\320\265\320\273\320\276\320\262<br />\320\237\321\200\320\270\320\274\320\265\321\200 \321\204\321\203\320\275\320\272\321\206\320\270\320\270:<br />(A&amp;B|C)&amp;B|(A+C-(B|C))</p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class WelcomeWindowClass: public Ui_WelcomeWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WELCOMEWINDOW_H
