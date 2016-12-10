#include "WelcomeWindow.h"
#include <qlineedit.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include "Pancer.h"
WelcomeWindow::WelcomeWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	mPWindow = new PainterWindow; // why not in member initializer?
	connect(this, SIGNAL(formula(QString)), mPWindow, SLOT(drawTree(QString)));
	connect(ui.lineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(enableButton(const QString &)));
	emit ui.lineEdit->textChanged(""); // setText() ?
}
WelcomeWindow::~WelcomeWindow()
{
	mPWindow->close();
	delete mPWindow;

}
void WelcomeWindow::on_pushButton_clicked()
{
	QString text = ui.lineEdit->text();
	string str = text.toStdString();
	if (checkLine(str)) {
		emit formula(text);
		tableTrue(text);
	}
}
bool WelcomeWindow::checkLine(string& str) {
	Parcer helper;
	for (auto i : str) {
		if (!((i == '(') || (i == ')') || (helper.isOperator(i)) || (helper.isVariable(i)))) {
			QMessageBox* pmb = new QMessageBox(QMessageBox::Information, "Error entering function", "Wrong simbols detected");
			pmb->exec();
			delete pmb;
			return false;
		}
	}
	int countOpen = 0, countClose = 0;
	for (auto i : str) {
		if (i == '(')
			countOpen++;
		if (i == ')')
			countClose++;
	}
	//begin repeated code
	if (countOpen != countClose) {
		QMessageBox* pmb = new QMessageBox(QMessageBox::Information, "Error entering function", "Brackets miss count");
		pmb->exec();
		delete pmb;
		return false;
	}
	for (int i = 0;i < str.size() - 1;i++) {
		if ((helper.isOperator(str[i])) && (helper.isOperator(str[i + 1])))
		{
			QMessageBox* pmb = new QMessageBox(QMessageBox::Information, "Error entering function", "One by one operators");
			pmb->exec();
			delete pmb;
			return false;
		}
		if ((helper.isVariable(str[i])) && (helper.isVariable(str[i + 1])))
		{
			QMessageBox* pmb = new QMessageBox(QMessageBox::Information, "Error entering function", "One by one variables");
			pmb->exec();
			delete pmb;
			return false;
		}
		if ((helper.isVariable(str[i])) && (str[i + 1] == '('))
		{
			QMessageBox* pmb = new QMessageBox(QMessageBox::Information, "Error entering function", "variable+bracket");
			pmb->exec();
			delete pmb;
			return false;
		}
		if ((helper.isVariable(str[i + 1])) && (str[i] == ')'))
		{
			QMessageBox* pmb = new QMessageBox(QMessageBox::Information, "Error entering function", "bracket+variable");
			pmb->exec();
			delete pmb;
			return false;
		}
	}

	if (str.size() < 3)
	{
		QMessageBox* pmb = new QMessageBox(QMessageBox::Information, "Error entering function", "Too short function");
		pmb->exec();
		delete pmb;
		return false;
	}
	int counter = 0;
	for (auto i : str) {
		if (helper.isOperator(i))
			counter++;
	}
	if (counter == 0)
	{
		QMessageBox* pmb = new QMessageBox(QMessageBox::Information, "Error entering function", "This is not a function");
		pmb->exec();
		delete pmb;
		return false;
	}
	if ((helper.isOperator(str[0])) || (helper.isOperator(str[str.size() - 1])))
	{
		QMessageBox* pmb = new QMessageBox(QMessageBox::Information, "Error entering function", "Begins or ends with an operator");
		pmb->exec();
		delete pmb;
		return false;
	}
	//end repeated code
	return true;
}
void WelcomeWindow::enableButton(const QString &text)
{
	ui.pushButton->setEnabled(!text.isEmpty());
}
void WelcomeWindow::tableTrue(const QString& text) {
	string str=text.toStdString();
	vector<char> Variables = searchVariables(str);
	vector<vector<char>> values; //
	ui.listWidget->clear();
	for (int i = 0;i < Variables.size();i++) {
		int count = 0;
		//int currentIndex = 0;
		vector<char> tempToPush;
		while (count != pow(2, i + 1)) {
			for (int j = 0;j < pow(2, Variables.size()-(i+1));j++) {
				if (count % 2 == 0)
					tempToPush.push_back('0');
				else
					tempToPush.push_back('1');
			}
			count++;
		}
		values.push_back(tempToPush);
	}
	QString table;
	for (int i = 0;i < Variables.size();i++) {
		table = "";
		table += Variables[i];
		table += " ";
		for (int j = 0;j < values[i].size();j++) {
			table += values[i][j];
			table += " ";
		}
		ui.listWidget->addItem(table);
	}
	Parcer mParcer(str);
	mParcer.goPolish();
	ui.listWidget->addItem(mParcer.count(Variables, values));


}
vector<char> WelcomeWindow::searchVariables(string& str) {
	vector<char> tempVariables;
	int compares = 0;
	Parcer toCheck;
	for (auto ch : str)
	{
		if (toCheck.isVariable(ch)) {
			for (auto v : tempVariables)
				if (ch == v)
					compares++;
			if (!compares)
				tempVariables.push_back(ch);
			compares = 0;
		}
	}
	return tempVariables;
}
void WelcomeWindow::on_pushButton_2_clicked()
{
	mPWindow->show();
}
