#include "Header.h"
#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>

//FIX ME: Переименовала все функции теперь они начинаются с заглавной буквы
//FIX ME: Добавлены функции для проверки
// Рекурсивная функция для проверки символа
bool CheckChar(char currentChar, int& balance)
{
	if (currentChar == '(')
	{
		balance++;
		return true;
	}
	else if (currentChar == ')')
	{
		balance--;
		if (balance < 0)
		{
			return false;
		}
		return true;
	}
	else if (isdigit(currentChar) || currentChar == '+' || currentChar == '-' || currentChar == '*')
	{
		return true;
	}
	return false; // Недопустимый символ
}

// Рекурсивная проверка строки
bool ValidateRecursive(std::string expressionString, int currentIndex, int& balance)
{
	if (currentIndex >= expressionString.length())
	{
		return true;
	}

	if (!CheckChar(expressionString[currentIndex], balance))
	{
		return false;
	}

	return ValidateRecursive(expressionString, currentIndex + 1, balance);
}

// Добавлена функция для проверки
bool IsValidExpression(std::string expressionString)
{
	if (expressionString.empty())
	{
		return false;
	}

	// Проверяем первый символ (должна быть цифра или открывающая скобка)
	if (!isdigit(expressionString[0]) && expressionString[0] != '(')
	{
		return false;
	}

	int Balance = 0;

	// Рекурсивная проверка без циклов
	if (!ValidateRecursive(expressionString, 0, Balance))
	{
		return false;
	}

	return Balance == 0;
}
int FindOperator(std::string expressionString, int currentIndex, int level, char Operator)
{
	if (currentIndex < 0)
	{
		return -1;
	}
	if (expressionString[currentIndex] == ')')
	{
		return FindOperator(expressionString, currentIndex - 1, level + 1, Operator);
	}
	if (expressionString[currentIndex] == '(')
	{
		return FindOperator(expressionString, currentIndex - 1, level - 1, Operator);
	}
	if (level == 0 && expressionString[currentIndex] == Operator)
	{
		return currentIndex;
	}
	return FindOperator(expressionString, currentIndex - 1, level, Operator);
}

int FindOperator2(std::string expressionString, int currentIndex, int level)
{
	if (currentIndex < 0)
	{
		return -1;
	}
	if (expressionString[currentIndex] == ')')
	{
		return FindOperator2(expressionString, currentIndex - 1, level + 1);
	}
	if (expressionString[currentIndex] == '(')
	{
		return FindOperator2(expressionString, currentIndex - 1, level - 1);
	}
	if (level == 0 && (expressionString[currentIndex] == '-' || expressionString[currentIndex] == '+'))
	{
		return currentIndex;
	}
	return FindOperator2(expressionString, currentIndex - 1, level);
}
//FIX ME: Переименовала функции и их переменные 
//int calc(std::string str);
//int element(std::string str)
int Calc(std::string expressionString);
int Element(std::string expressionString)
{
	if (expressionString[0] == '(' && expressionString[expressionString.size() - 1] == ')')
	{
		return Calc(expressionString.substr(1, expressionString.size() - 2));
	}
	return stoi(expressionString);
}

//FIX ME: В функции term циклы while заменены на вызовы этих рекурсивных функций
//int term(string str)
//{
//	int i = str.size() - 1;
//	int level = 0;
//	int pos = -1;
//	while (i >= 0)
//	{
//		if (str[i] == ')')
//			level++;
//		if (str[i] == '(')
//			level--;
//		if (level == 0 && str[i] == '*')
//		{
//			pos = i;
//			break;
//		}
//		i--;
//	}
//	if (pos == -1)
//		return element(str);
//	return term(str.substr(0, pos)) * element(str.substr(pos + 1));
//}
// 
//FIX ME: Переименовала функцию и ее переменную
//int term(std::string str)
int Term(std::string expressionString)
{
	int pos = FindOperator(expressionString, expressionString.size() - 1, 0, '*');
	if (pos == -1)
	{
		return Element(expressionString);
	}
	return Term(expressionString.substr(0, pos)) * Element(expressionString.substr(pos + 1));
}

//FIX ME: В функции calc циклы while заменены на вызовы этих рекурсивных функций
//int calc(string str)
//{
//	int i = str.size() - 1;
//	int level = 0;
//	int pos = -1;
//	while (i >= 0)
//	{
//		if (str[i] == ')')
//			level++;
//		if (str[i] == '(')
//			level--;
//		if (level == 0 && (str[i] == '-' || str[i] == '+'))
//		{
//			pos = i;
//			break;
//		}
//		i--;
//	}
//	if (pos == -1)
//		return term(str);
//	char ch = str[pos];
//	if (ch == '+')
//		return calc(str.substr(0, pos)) + term(str.substr(pos + 1));
//	if (ch == '-')
//		return calc(str.substr(0, pos)) - term(str.substr(pos + 1));
//	return 0;
//}

//FIX ME: Переименовала функцию и ее переменные
//int calc(std::string str)
int Calc(std::string expressionString)
{
	//FIX ME: Переименовала переменные
	//int pos = FindOperator2(expressionString, expressionString.size() - 1, 0);
	// char ch = expressionString[оperatorPosition];
	int оperatorPosition = FindOperator2(expressionString, expressionString.size() - 1, 0);
	if (оperatorPosition == -1)
	{
		return Term(expressionString);
	}
	char foundOperator = expressionString[оperatorPosition];
	if (foundOperator == '+')
	{
		return Calc(expressionString.substr(0, оperatorPosition)) + Term(expressionString.substr(оperatorPosition + 1));
	}
	if (foundOperator == '-')
	{
		return Calc(expressionString.substr(0, оperatorPosition)) - Term(expressionString.substr(оperatorPosition + 1));
	}
	return 0;
}