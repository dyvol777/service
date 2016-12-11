
//#include "stdafx.h"
#include "Pancer.h"
#include "PainterWindow.h"
#include "WelcomeWindow.h"


string variables("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
string operators("&|+-");//êîíúþíêöèÿ, äèçúþíêöèÿ, áóëåâ ïëþñ, ðàâåíñòâî
deque<char> tempOutput;
Parcer::Parcer(string data)
{
	input = "(" + data + ")";
	precedence['&'] = 2;
	precedence['|'] = 2;
	precedence['+'] = 2;
	precedence['-'] = 2;//equal
}
bool Parcer::isOperator(char c)
{
	for (auto v : operators)
	{
		if (c == v)
			return true;
	}
	return false;
}
bool Parcer::isVariable(char c)
{
	for (auto v : variables)
	{
		if (c == v)
			return true;
	}
	return false;
}
bool Parcer::higherPrecedence(char previous, char last)
{
	if (precedence[previous] < precedence[last])
		return true;
	return false;
}
int Parcer::goPolish()
{
	for (auto token : input)
	{
		if (isVariable(token))
			output.push_back(token);
		if (isOperator(token))
		{
			if (isOperator(operations.top()) && !higherPrecedence(operations.top(), token))
			{
				output.push_back(operations.top());
				operations.pop();
			}
			operations.push(token);
		}
		if (token == '(')
		{
			operations.push(token);
		}
		if (token == ')')
		{
			while (operations.top() != '(')
			{
				output.push_back(operations.top());
				operations.pop();
			}
			operations.pop();
		}
	}
	return output.size();
}
void Parcer::logPolish()
{

	deque<char> temp(output);
	while (temp.size() != 0)
	{
		cout << temp.front() << endl;
		temp.pop_front();
	}
}
void Parcer::setValues(map<char, char> init)
{
	values = init;
	values['f'] = '2';
}
QString Parcer::count(vector<char> variables,vector<vector<char>> values)
{
	
	int cur;
	char rez;
	QString result;
	result += 'f';
	result += ' ';
	int count = 0;
		while (count != pow(2, variables.size()))
		{
			vector<char> temp;
			for (int i = 0; i < output.size(); i++)//set formula with values
			{
				if (isVariable(output[i]))
					for(int j=0; j<variables.size();j++)
					if (variables[j]==output[i])
					temp.push_back(values[j][count]);
				if (isOperator(output[i]))
					temp.push_back(output[i]);
			}


			while (temp.size() != 1)
			{
				for (int j = 0; j < temp.size(); j++)
				{
					if (isOperator(temp[j]))
					{
						cur = j;
						break;
					}
				}
				switch (temp[cur])
				{
					{
				case '&':
					if ((temp[cur - 1] == '1') && (temp[cur - 2] == '1'))
						rez = '1';
					else
						rez = '0';
					temp[cur] = rez;
					temp.erase(temp.begin() + (cur - 1));
					temp.erase(temp.begin() + (cur - 2));
					break;
					}
					{
				case '|':
					if ((temp[cur - 1] == '1') || (temp[cur - 2] == '1'))
						rez = '1';
					else
						rez = '0';
					temp[cur] = rez;
					temp.erase(temp.begin() + (cur - 1));
					temp.erase(temp.begin() + (cur - 2));
					break;
					}
					{
				case '+':
					if ((temp[cur - 1] == '1') && (temp[cur - 2] == '1'))
						rez = '0';
					if ((temp[cur - 1] == '0') && (temp[cur - 2] == '0'))
						rez = '0';
					if ((temp[cur - 1] == '1') && (temp[cur - 2] == '0'))
						rez = '1';
					if ((temp[cur - 1] == '0') && (temp[cur - 2] == '1'))
						rez = '1';
					temp[cur] = rez;
					temp.erase(temp.begin() + (cur - 1));
					temp.erase(temp.begin() + (cur - 2));
					break;
					}
					{
				case '-':
					if (temp[cur - 1] == temp[cur - 2])
						rez = '1';
					else
						rez = '0';
					temp[cur] = rez;
					temp.erase(temp.begin() + (cur - 1));
					temp.erase(temp.begin() + (cur - 2));
					break;
					}

					{
				default:
					break;
					}
				}
			}
			result += temp[0];
			result += " ";
			count++;
		}
		return result;
}

void tree::set(Parcer &a)
{
	for (auto b : a.output)
	{
		tempOutput.push_back(b);
	}
}
bool tree::isOperator(char c)
{
	for (auto v : operators)
	{
		if (c == v)
			return true;
	}
	return false;
}
void tree::buildTree(shared_ptr<tree> current)
{
	current->right.reset(new tree); 
	current->right->data = tempOutput.back();
	tempOutput.pop_back();
	current->right->level = current->level + 1;
	if (current->right->level > biggestLevel)
		biggestLevel = current->right->level;
	if (isOperator(current->right->data))
	{
		buildTree(current->right);
		current->left.reset(new tree);
		current->left->data = tempOutput.back();
		tempOutput.pop_back();
		current->left->level = current->level + 1;
		if (current->left->level > biggestLevel)
			biggestLevel = current->left->level;
		if (isOperator(current->left->data))
		{
			buildTree(current->left);
		}
		else
			return;
	}
	else {
		current->left.reset(new tree);//current->left = new tree;
		current->left->data = tempOutput.back();
		tempOutput.pop_back();
		current->left->level = current->level + 1;
		if (current->left->level > biggestLevel)
			biggestLevel = current->left->level;
		//current->left->top = current;
		if (!isOperator(current->left->data))
			return;
		buildTree(current->left);
	}

}
void tree::setValues(string& str) {
	str += ' ';

	for (int i = 0; i < str.size()/4;i++)
	{
		
		values[str[i * 4]] = str[i * 4+2];
	}
}
char tree::rezultValue(char oper,char leftValue, char rightValue) {
	char rez;
	switch (oper)
	{
		{
	case '&':
		if ((leftValue == '1') && (rightValue == '1'))
			rez = '1';
		else
			rez = '0';
		break;
		}
		{
	case '|':
		if ((leftValue == '1') || (rightValue == '1'))
			rez = '1';
		else
			rez = '0';
		break;
		}
		{
	case '+':
		if (leftValue == rightValue)
			rez = '0';
		else
			rez = '1';
		break;
		}
		{
	case '-':
		if (leftValue == rightValue)
			rez = '1';
		else
			rez = '0';
		break;
		}

		{
	default:
		break;
		}
	}
	return rez;
}
void tree::countValues(shared_ptr<tree> current,int i)//void tree::countValues(tree* current,int i)
{
	
	if (current->right->level == biggestLevel - i)
	{
		if (isOperator(current->right->data))
		{
			current->right->currentValue = rezultValue(current->right->data, current->right->left->currentValue, current->right->right->currentValue);
		}
		else
		{
			current->right->currentValue = values[current->right->data];
		}
	}
	if (isOperator(current->right->data))
	{
		countValues(current->right,i);
		if (current->left->level == biggestLevel - i)
		{
			if (isOperator(current->left->data))
			{
				current->left->currentValue = rezultValue(current->left->data, current->left->left->currentValue, current->left->right->currentValue);
			}
			else
			{
				current->left->currentValue = values[current->left->data];
			}
		}
		if (isOperator(current->left->data))
		{
			countValues(current->left,i);
		}
		else
			return;
	}
	else {
		if (current->left->level == biggestLevel - i)
		{
			if (isOperator(current->left->data))
			{
				current->left->currentValue = rezultValue(current->left->data, current->left->left->currentValue, current->left->right->currentValue);
			}
			else
			{
				current->left->currentValue = values[current->left->data];
			}
		}
		if (!isOperator(current->left->data))
			return;
		countValues(current->left,i);
	}
}

void tree::setCoord(shared_ptr<tree> current)//void tree::setCoord(tree* current)
{

	current->right->coord.first = current->coord.first + (pow(2, (biggestLevel - current->right->level)) * 40);
	current->right->coord.second = current->coord.second + 80;
	if (isOperator(current->right->data))
	{
		setCoord(current->right);
		current->left->coord.first = current->coord.first - (pow(2, (biggestLevel - current->right->level)) * 40);
		current->left->coord.second = current->coord.second + 80;
		if (isOperator(current->left->data))
		{
			setCoord(current->left);
		}
		else
			return;
	}
	else {
		current->left->coord.first = current->coord.first - (pow(2, (biggestLevel - current->right->level)) * 40);
		current->left->coord.second = current->coord.second + 80;
		if (!isOperator(current->left->data))
			return;
		setCoord(current->left);
	}

}