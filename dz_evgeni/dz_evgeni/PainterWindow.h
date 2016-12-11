#pragma once

#include <QWidget>
#include <qmainwindow.h>
#include "ui_PainterWindow.h"
#include "qgraphicsview.h"
#include "Pancer.h"
#include "qmenu.h"
namespace Ui {
	class PainterWindow;
}

class PainterWindow :public QMainWindow
{
	Q_OBJECT

public:
	PainterWindow(QWidget *parent = Q_NULLPTR);
	~PainterWindow();
	void drawTree1(shared_ptr<tree>);
	int getLeftBot(shared_ptr<tree>);
	int getRightBot(shared_ptr<tree>);
	void setupScene();
	void drawTreeValues(shared_ptr<tree>);
	bool checkLine(QString&);
	void checkNumVariables(string&, Parcer&);
	void checkSimbols(string&, Parcer&);
	void checkPositionsSymbols(string&, Parcer&);
	int numberVariables(string& str);

	string inputFormula;
	shared_ptr<tree> headTree;
private:
	Ui::PainterWindow ui;
	QGraphicsScene* mScene;
	QGraphicsView* mView;
public slots:
	
	void drawTree(const QString&);
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
	void on_pushButton_4_clicked();

};
