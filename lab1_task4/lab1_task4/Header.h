#include <string>

// Функции для проверки валидности выражения
bool CheckChar(char currentChar, int& balance);
bool ValidateRecursive(std::string expressionString, int currentIndex, int& balance);
bool IsValidExpression(std::string expressionString);

// Функции для поиска операторов
int FindOperator(std::string expressionString, int currentIndex, int level, char Operator);
int FindOperator2(std::string expressionString, int currentIndex, int level);

// Основные функции вычисления
int Element(std::string expressionString);
int Term(std::string expressionString);
int Calc(std::string expressionString);
