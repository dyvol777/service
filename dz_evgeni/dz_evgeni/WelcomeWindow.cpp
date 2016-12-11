#include "WelcomeWindow.h"
#include <qlineedit.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include "Pancer.h"
WelcomeWindow::WelcomeWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	mPWindow = new PainterWindow();
	connect(this, SIGNAL(formula(QString)), mPWindow, SLOT(drawTree(QString)));
	connect(ui.lineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(enableButton(const QString &)));
	emit ui.lineEdit->textChanged("");
	ui.pushButton_2->setEnabled(false);
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
		ui.pushButton_2->setEnabled(true);
	}
	
}
void WelcomeWindow::checkPositions(string& str, Parcer& helper)
{
	for (int i = 0;i < str.size() - 1;i++) {
		if (str[i] == ')'&&str[i + 1] == '(')
		{
			throw runtime_error("No operator between brackets");
		}
		if ((helper.isOperator(str[i])) && (helper.isOperator(str[i + 1])))
		{
			throw runtime_error("One by one operators");
		}
		if ((helper.isVariable(str[i])) && (helper.isVariable(str[i + 1])))
		{
			throw runtime_error("One by one variables");
		}
		if ((helper.isVariable(str[i])) && (str[i + 1] == '('))
		{
			throw runtime_error("variable+bracket");
		}
		if ((helper.isVariable(str[i + 1])) && (str[i] == ')'))
		{
			throw runtime_error("bracket+variable");
		}
	}
	if ((helper.isOperator(str[0])) || (helper.isOperator(str[str.size() - 1])))
	{
		throw runtime_error("Begins or ends with an operator");
	}
}
void WelcomeWindow::checkSize(string& str, Parcer& helper)
{
	if (str.size() < 3)
	{
		throw runtime_error("Too short function");
	}
	int counter = 0;
	for (auto i : str) {
		if (helper.isOperator(i))
			counter++;
	}
	if (counter == 0)
	{
		throw runtime_error("This is not a function");
	}
}
void WelcomeWindow::checkSimbols(string& str, Parcer& helper)
{
	for (auto i : str) {
		if (!((i == '(') || (i == ')') || (helper.isOperator(i)) || (helper.isVariable(i)))) {
			throw runtime_error("Wrong simbols detected");
		}
	}
}
void WelcomeWindow::checkBrakets(string& str, Parcer& helper)
{
	int countOpen = 0, countClose = 0;
	for (auto i : str) {
		if (i == '(')
			countOpen++;
		if (i == ')')
			countClose++;
	}
	if (countOpen != countClose) {
		throw runtime_error("Brackets miss count");
	}
}
bool WelcomeWindow::checkLine(string& str) {
	Parcer helper;
	bool ret = true;
	try
	{
		checkSimbols(str, helper);
		checkBrakets(str, helper);
		checkPositions(str, helper);
		checkSize(str, helper);
	}
	catch(runtime_error& ec)
	{
		QMessageBox* pmb = new QMessageBox(QMessageBox::Information, "Error entering function", ec.what());
		pmb->exec();
		delete pmb;
		ret = false;
	}
	return ret;
}
void WelcomeWindow::enableButton(const QString &text)
{
	ui.pushButton->setEnabled(!text.isEmpty());
	
}
void WelcomeWindow::tableTrue(const QString& text) {
	string str=text.toStdString();
	vector<char> Variables = searchVariables(str);
	vector<vector<char>> values;
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
