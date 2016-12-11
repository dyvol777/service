#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_WelcomeWindow.h"
#include "PainterWindow.h"
#include "Pancer.h"
#include <qmessagebox.h>
namespace Ui {
	class WelcomeWindow;
}
class QLineEdit;
class QListWidget;
class QPushButton;
class QMessageBox;
class WelcomeWindow : public QMainWindow
{
	Q_OBJECT
		public slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void enableButton(const QString &text);
	
signals:
	void formula(const QString&);

public:

	void tableTrue(const QString&);
	vector<char> searchVariables(string&);
    WelcomeWindow(QWidget *parent = Q_NULLPTR);
	bool checkLine(string&);
	void checkSimbols(string&, Parcer&);
	void checkBrakets(string&, Parcer&);
	void checkPositions(string&, Parcer&);
	void checkSize(string&, Parcer&);
	~WelcomeWindow();
protected:
	void closeEvent(QCloseEvent *event)
	{
		QMainWindow::closeEvent(event);
		mPWindow->close();
	}

private:
    Ui::WelcomeWindowClass ui;
	PainterWindow* mPWindow;
};
