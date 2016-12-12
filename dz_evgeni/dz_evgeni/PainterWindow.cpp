#include "PainterWindow.h"
#include <QGraphicsItem>
#include "WelcomeWindow.h"
#include <qlineedit.h>
#include <qfiledialog.h>
class QLineEdit;
PainterWindow::PainterWindow(QWidget *parent)
	:QMainWindow(parent)
	//QWidget(parent)
{
	ui.setupUi(this);
	setupScene();
	connect(ui.lineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(enableButton(const QString &)));
}
PainterWindow::~PainterWindow()
{

}
void PainterWindow::checkNumVariables(string& tocheck,Parcer& helper)
{
	int countVariable = 0;
	for (auto i : tocheck)
		if (helper.isVariable(i))
			countVariable++;
	if (countVariable != numberVariables(inputFormula))
	{
		
		throw runtime_error("Wrong number of variables");
	}
}
void PainterWindow::checkSimbols(string& tocheck, Parcer& helper)
{
	for (auto i : tocheck)
		if ((!helper.isVariable(i)) && (i != '=') && (i != ' ') && (i != '0') && (i != '1'))
		{
			throw runtime_error("Wrong simbols detected");
		}
}
void PainterWindow::checkPositionsSymbols(string& tocheck, Parcer& helper)
{
	for (int i = 0;i<tocheck.size() - 1;i++)
		if ((helper.isVariable(tocheck[i])) && (tocheck[i + 1] != '='))
		{
			throw runtime_error("After variable is not =");
			
		}

	for (int i = 0;i<tocheck.size() - 1;i++)
		if ((tocheck[i] == '=') && ((tocheck[i + 1] != '0') && (tocheck[i + 1] != '1')))
		{
			throw runtime_error("After = is not value");
		}

	for (int i = 0;i<tocheck.size() - 1;i++)
		if (((tocheck[i] == '0') || (tocheck[i] == '1')) && (tocheck[i + 1] != ' '))
		{
			throw runtime_error("After value is not space");
		}

	if ((tocheck[tocheck.size() - 1] != '0') && (tocheck[tocheck.size() - 1] != '1'))
	{
		throw runtime_error("Ends is not value");
	}

	if (!helper.isVariable(tocheck[0]))
	{
		throw runtime_error("Begins is not variable");
	}
}
bool PainterWindow::checkLine(QString& Qstr) {
	Parcer helper;
	string str = Qstr.toStdString();
	bool ret = true;
	
	try 
	{
		checkNumVariables(str, helper);
		checkSimbols(str, helper);
		checkPositionsSymbols(str, helper);
	}
	catch (runtime_error& ec)
	{
		QMessageBox* pmb = new QMessageBox(QMessageBox::Information, "Error entering checking of variables", ec.what());
		pmb->exec();
		delete pmb;
		ret = false;
	}
	return ret;
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
int PainterWindow::getLeftBot(shared_ptr<tree> current)
{
	if (current->left != nullptr)
		getLeftBot(current->left);
	if (current->left == nullptr)
		return current->coord.first;
}
int PainterWindow::getRightBot(shared_ptr<tree> current)
{
	if (current->right != nullptr)
		getLeftBot(current->left);
	if (current->right == nullptr)
		return current->coord.first;
}

// функции ниже хотят рефакторинга. Возможно, имеет смысл вызделить какие-л. дополнительные классы.
// магические константы сильно напрягают. как они связаны между собой?
void PainterWindow::drawTree(const QString& input)//çäåñü íàãàæåíî
{
	
	delete mScene;
	delete mView;
	mScene = new QGraphicsScene(this);
	Parcer data(input.toStdString());
	inputFormula = input.toStdString();
	data.goPolish();
	data.logPolish();
	mScene->clear();
	tree* myTree = new tree;
	{
		headTree.reset(myTree);
		headTree->set(data);
		headTree->data = headTree->tempOutput.back();
		headTree->tempOutput.pop_back();
		tree::biggestLevel = 0;
		headTree->buildTree(headTree);
		headTree->coord.first = 1500;
		headTree->coord.second = 500;
		headTree->setCoord(headTree);
	}
	int top=headTree->coord.second;
	int leftBot = getLeftBot(headTree);
	int rightBot = getRightBot(headTree);
	int bot = top + headTree->biggestLevel * 80;
	QSize minSize(1500, 700);
	mView = new QGraphicsView(this);
	mView->setMinimumSize(minSize);
	mView->setScene(mScene);
	QRectF blok(headTree->coord.first, headTree->coord.second, 40, 40);//
	mScene->addRect(blok);
	QString str;
	str+=headTree->data;
	mScene->addSimpleText(str)->setPos(blok.center());
	drawTree1(headTree);
}
void PainterWindow::drawTreeValues(shared_ptr<tree> current)
{
	QString str;
	str += current->right->currentValue;
	mScene->addSimpleText(str)->setPos(current->right->coord.first - 10, current->right->coord.second + 5);
	if (current->isOperator(current->right->data))
	{
		drawTreeValues(current->right);
		QString str1;
		str1 += current->left->currentValue;
		mScene->addSimpleText(str1)->setPos(current->left->coord.first - 10, current->left->coord.second + 5);
		if (current->isOperator(current->left->data))
			drawTreeValues(current->left);
		else
			return;
	}
	else {
		QString str1;
		str1 += current->left->currentValue;
		mScene->addSimpleText(str1)->setPos(current->left->coord.first - 10, current->left->coord.second + 5);
		if (!current->isOperator(current->left->data))
			return;
		drawTreeValues(current->left);
	}
}
void PainterWindow::drawTree1(shared_ptr<tree> current)
{
	QRectF blok(current->right->coord.first, current->right->coord.second, 40, 40);
	mScene->addRect(blok);
	QString str;
	str += current->right->data;
	mScene->addSimpleText(str)->setPos(blok.center());
	QLineF line(current->coord.first + 20, current->coord.second + 40, current->right->coord.first + 20, current->right->coord.second);
	mScene->addLine(line);
	if (current->isOperator(current->right->data))
	{
		drawTree1(current->right);
		QRectF blok1(current->left->coord.first, current->left->coord.second, 40, 40);
		mScene->addRect(blok1);
		QString str1;
		str1 += current->left->data;
		mScene->addSimpleText(str1)->setPos(blok1.center());
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
		QString str1;
		str1 += current->left->data;
		mScene->addSimpleText(str1)->setPos(blok1.center());
		QLineF line1(current->coord.first + 20, current->coord.second + 40, current->left->coord.first + 20, current->left->coord.second);
		mScene->addLine(line1);
		if (!current->isOperator(current->left->data))
			return;
		drawTree1(current->left);
	}
}
void PainterWindow::setupScene() //����� �������� ����
{
	mScene = new QGraphicsScene(this);
	//mScene->setSceneRect(0, 0, 3000, 1000);
	mView = new QGraphicsView(this);
	//mView->setScene(mScene);
}

// нельзя ли слотам дать нормальные имена?
void PainterWindow::on_pushButton_clicked(){
	QString text = ui.lineEdit->text();
	if (checkLine(text)) {
		mScene->clear();
		QRectF blok(headTree->coord.first, headTree->coord.second, 40, 40);//
		mScene->addRect(blok);
		auto mText = new QGraphicsSimpleTextItem();

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
		auto mValue = new QGraphicsSimpleTextItem();
		mValue->setPos(headTree->coord.first - 10, headTree->coord.second + 5);//
		str = "";
		str += headTree->currentValue;//
		mValue->setText(str);
		mScene->addItem(mValue);
		drawTreeValues(headTree);//drawTreeValues(headTree.current);
	}
}
void PainterWindow::on_pushButton_2_clicked() 
{
	mView->scale(1.25, 1.25);
}
void PainterWindow::on_pushButton_3_clicked()
{
	mView->scale(0.8, 0.8);
}
void PainterWindow::on_pushButton_4_clicked()
{
	QString fileName = QFileDialog::getSaveFileName(this, "Save image", QCoreApplication::applicationDirPath(), "BMP Files (*.bmp);;JPEG (*.JPEG);;PNG (*.png)");
	QPixmap pixMap = QPixmap::grabWidget(mView);
	pixMap.save(fileName);
}