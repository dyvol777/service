#pragma once

#include <QWidget>
#include "ui_PainterWindow.h"
#include "qgraphicsview.h"
#include "Pancer.h"
namespace Ui {
	class PainterWindow;
}

class PainterWindow : public QWidget
{
	Q_OBJECT

public:
	PainterWindow(QWidget *parent = Q_NULLPTR);
	~PainterWindow();
	void drawTree1(shared_ptr<tree>);//void drawTree1(tree*);
	void setupScene();
	void drawTreeValues(shared_ptr<tree>);//	void drawTreeValues(tree*);
	bool checkLine(QString&);
	int numberVariables(string& str);
	string inputFormula;
	shared_ptr<tree> headTree;//tree headTree
private:
	Ui::PainterWindow ui;
	QGraphicsScene* mScene;
	QGraphicsView* mView;
public slots:
	void drawTree(const QString&);
	void on_pushButton_clicked();

};
