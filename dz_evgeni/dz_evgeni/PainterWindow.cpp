#include "PainterWindow.h"
#include <QGraphicsItem>
#include "WelcomeWindow.h"
#include <qlineedit.h>

class QLineEdit;
PainterWindow::PainterWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setupScene();
}
PainterWindow::~PainterWindow()
{
}
bool PainterWindow::checkLine(QString& Qstr) {
	Parcer helper;
	string str = Qstr.toStdString();
	int countVariable = 0;
	for (auto i : str)
		if (helper.isVariable(i))
			countVariable++;
	//begin repeated code
	if(countVariable!=numberVariables(inputFormula))
	{
		QMessageBox* pmb = new QMessageBox(QMessageBox::Information, "Error entering checking of variables", "Wrong number of variables");
		pmb->exec();
		delete pmb;
		return false;
	}
	for (auto i : str)
		if ((!helper.isVariable(i))&&(i!='=') && (i != ' ') && (i != '0') && (i != '1'))
		{
			QMessageBox* pmb = new QMessageBox(QMessageBox::Information, "Error entering checking of variables", "Wrong simbols detected");
			pmb->exec();
			delete pmb;
			return false;
		}
	for (int i=0;i<str.size()-1;i++)
		if((helper.isVariable(str[i]))&&(str[i+1]!='='))
		{
			QMessageBox* pmb = new QMessageBox(QMessageBox::Information, "Error entering checking of variables", "After variable is not =");
			pmb->exec();
			delete pmb;
			return false;
		}
	for (int i = 0;i<str.size()-1;i++)
		if ((str[i] == '=') && ((str[i + 1] != '0')&&(str[i+1]!='1')))
		{
			QMessageBox* pmb = new QMessageBox(QMessageBox::Information, "Error entering checking of variables", "After = is not value");
			pmb->exec();
			delete pmb;
			return false;
		}
	for (int i = 0;i<str.size()-1;i++)
		if (((str[i] == '0') || (str[i] == '1')) && (str[i+1]!=' '))
		{
			QMessageBox* pmb = new QMessageBox(QMessageBox::Information, "Error entering checking of variables", "After value is not space");
			pmb->exec();
			delete pmb;
			return false;
		}
	if((str[str.size()-1]!='0')&& (str[str.size() - 1] != '1'))
	{
		QMessageBox* pmb = new QMessageBox(QMessageBox::Information, "Error entering checking of variables", "Ends is not value");
		pmb->exec();
		delete pmb;
		return false;
	}
	if (!helper.isVariable(str[0]))
	{
		QMessageBox* pmb = new QMessageBox(QMessageBox::Information, "Error entering checking of variables", "Begins is not variable");
		pmb->exec();
		delete pmb;
		return false;
	}
	//end repeated code
	return true;
}
int PainterWindow::numberVariables(string& str) {
	Parcer toCheck;
	vector<char> tempVariables;
	int compares = 0;
	int quantity=0;
	for (auto ch : str)
	{
		if (toCheck.isVariable(ch)) {
			for (auto v : tempVariables)
				if (ch == v)
					compares++;
			if (!compares) {
				tempVariables.push_back(ch);
				quantity++;
			}
			compares = 0;
		}
	}
	return quantity;
}
void PainterWindow::drawTree(const QString& input)
{
	Parcer data(input.toStdString());
	inputFormula = input.toStdString();
	data.goPolish();
	data.logPolish();
	mScene->clear();
	tree* myTree = new tree;
	headTree.reset(myTree);
	headTree->set(data);//
	headTree->data = headTree->tempOutput.back();//
	headTree->tempOutput.pop_back();//
	tree::biggestLevel = 0;
	headTree->buildTree(headTree);//headTree.buildTree(headTree.current);
	if(headTree->biggestLevel>5)//
	{
		QMessageBox* pmb = new QMessageBox(QMessageBox::Information, "Error entering function", "You need full version");
		pmb->exec();
		delete pmb;
	}
	headTree->coord.first = 1500;//
	headTree->coord.second = 500;//
	headTree->setCoord(headTree);//headTree.setCoord(headTree.current);
	QRectF blok(headTree->coord.first, headTree->coord.second, 40, 40);//
	mScene->addRect(blok);
	auto mText = new QGraphicsSimpleTextItem(); // memory leak 

	mText->setPos(blok.center());
	QString str;
	str+=headTree->data;//
	mText->setText(str);
	mScene->addItem(mText);
	drawTree1(headTree);//drawTree1(headTree.current);

}
void PainterWindow::drawTreeValues(shared_ptr<tree> current)//void PainterWindow::drawTreeValues(tree* current)
{
	auto mValue = new QGraphicsSimpleTextItem(); // memory leak
	mValue->setPos(current->right->coord.first - 10, current->right->coord.second + 5);
	QString str;
	str += current->right->currentValue;
	mValue->setText(str);
	mScene->addItem(mValue);
	if (current->isOperator(current->right->data))
	{
		// begin repeated code
		drawTreeValues(current->right);
		auto mValue1 = new QGraphicsSimpleTextItem(); // memory leak
		mValue1->setPos(current->left->coord.first - 10, current->left->coord.second + 5);
		QString str1;
		str1 += current->left->currentValue;
		mValue1->setText(str1);
		mScene->addItem(mValue1);
		
		if (current->isOperator(current->left->data))
		
			drawTreeValues(current->left);
		
		else
		
			return;
		
	}
	else {
		auto mValue1 = new QGraphicsSimpleTextItem();
		mValue1->setPos(current->left->coord.first - 10, current->left->coord.second + 5);
		QString str1;
		str1 += current->left->currentValue;
		mValue1->setText(str1);
		mScene->addItem(mValue1);
		if (!current->isOperator(current->left->data))
			return;
		drawTreeValues(current->left);
		// end repeated code
	}
	
	
}
void PainterWindow::drawTree1(shared_ptr<tree> current)//void PainterWindow::drawTree1(tree* current)
{
	QRectF blok(current->right->coord.first, current->right->coord.second, 40, 40);
	mScene->addRect(blok);
	auto mText = new QGraphicsSimpleTextItem(); // memory leak
	mText->setPos(blok.center());
	QString str;
	str += current->right->data;
	mText->setText(str);
	mScene->addItem(mText);
	QLineF line(current->coord.first + 20, current->coord.second + 40, current->right->coord.first + 20, current->right->coord.second);
	mScene->addLine(line);
	if (current->isOperator(current->right->data))
	{
		// begin repeated code
		drawTree1(current->right);
		QRectF blok1(current->left->coord.first, current->left->coord.second, 40, 40);
		mScene->addRect(blok1);
		auto mText1 = new QGraphicsSimpleTextItem(); // memory leak
		mText1->setPos(blok1.center());
		QString str1;
		str1 += current->left->data;
		mText1->setText(str1);
		mScene->addItem(mText1);
		QLineF line1(current->coord.first + 20, current->coord.second + 40, current->left->coord.first + 20, current->left->coord.second);
		mScene->addLine(line1);
		
		if (current->isOperator(current->left->data))
		
			drawTree1(current->left);
		
		else
		
			return;
		
		
	}
	else {
		QRectF blok1(current->left->coord.first, current->left->coord.second, 40, 40);
		mScene->addRect(blok1);
		auto mText1 = new QGraphicsSimpleTextItem(); // memory leak
		mText1->setPos(blok1.center());
		QString str1;
		str1 += current->left->data;
		mText1->setText(str1);
		mScene->addItem(mText1);
		QLineF line1(current->coord.first + 20, current->coord.second + 40, current->left->coord.first + 20, current->left->coord.second);
		mScene->addLine(line1);
	
		if (!current->isOperator(current->left->data))
			return;
		drawTree1(current->left);
		// end repeated code
	}

}
void PainterWindow::setupScene() {
	mScene = new QGraphicsScene(this);
	mScene->setSceneRect(0, 0, 3000, 1000);
	mView = new QGraphicsView(this);
	mView->setScene(mScene);
}
void PainterWindow::on_pushButton_clicked(){
	QString text = ui.lineEdit->text();
	if (checkLine(text)) {
		mScene->clear();
		QRectF blok(headTree->coord.first, headTree->coord.second, 40, 40);//
		mScene->addRect(blok);
		auto mText = new QGraphicsSimpleTextItem(); // memory leak

		mText->setPos(blok.center());
		QString str;
		str += headTree->data;//
		mText->setText(str);
		mScene->addItem(mText);
		drawTree1(headTree);//drawTree1(headTree.current);
		headTree->setValues(text.toStdString());//
		for (int i = 0;i < tree::biggestLevel;i++)
			headTree->countValues(headTree, i);//headTree.countValues(headTree.current, i);
		headTree->currentValue = headTree->rezultValue(headTree->data, headTree->left->currentValue, headTree->right->currentValue);//
		auto mValue = new QGraphicsSimpleTextItem(); // memory leak
		mValue->setPos(headTree->coord.first - 10, headTree->coord.second + 5);//
		str = "";
		str += headTree->currentValue;//
		mValue->setText(str);
		mScene->addItem(mValue);
		drawTreeValues(headTree);//drawTreeValues(headTree.current);
	}
}