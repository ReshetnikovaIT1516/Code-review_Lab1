//Строки, определяющие выражения, не содержат пробелов. 
//При выполнении заданий не следует использовать оператор цикла.
//Вывести значение целочисленного выражения, заданного в виде строки S.Выражение
//определяется следующим образом :
//		<выражение> :: = <цифра> | <выражение> +<цифра> | <выражение> − <цифра>

#include <iostream> 
#include <string> 

#include "Header.h"

//FIX ME: Дбавила новую библлиотеку для функции проверки
#include <cctype>  // для isdigit

//FIX ME: Убрала глобальное использование using namespace std;
//FIX ME: Перенесла все фигурные скобки на новую строку

int main()
{
	setlocale(LC_ALL, "Russian");
	//FIX ME: Добавлена строка с указанием допустимых значений
	std::cout << "Допустимые символы: цифры, +, -, *, (, )" << std::endl;
	std::cout << "Программа считает значение выражения которое вы введете" << std::endl;
	//FIX ME: Переименовала функцию 
	//std::string str;
	std::string UserInput;
	std::cout << "Введите выражение: ";
	std::getline(std::cin, UserInput);

	//FIX ME: Добавила проверку корректности вводимых данных
	//int r = calc(str);
	//cout << "Ответ: " << r << endl;
	if (!IsValidExpression(UserInput))
	{
		std::cout << "Ошибка: выражение содержит недопустимые символы или некорректные скобки!" << std::endl;
		return 1;
	}

	try
	{
		//FIX ME: Переименовала переменную
		// int r = Calc(UserInput);
		int result = Calc(UserInput);
		std::cout << "Ответ: " << result << std::endl;
	}

	catch (const std::exception& e)
	{
		std::cout << "Ошибка при вычислении: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}

