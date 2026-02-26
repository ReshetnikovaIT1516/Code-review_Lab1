//К - ичные числа.Среди чисел в системе счисления с основанием K(2≤K≤10) определить сколько 
//имеется чисел из N(1 < N < 20, N + K < 26) разрядов таких, что в их записи содержится более 
//трех подряд идущих нулей.Для того, чтобы избежать переполнения, ответ представьте в виде 
//вещественного числа.

#include <iostream>
//FIX ME: Убрала лишнюю библиотеку
//#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <climits>

#include "Header.h"
//FIX ME: Добавила раздление на модули
//FIX ME: Убрала глобальное использование using namespace std;
//FIX ME: Перенесла все фигурные скобки на новую строкку


int main()
{
    setlocale(LC_ALL, "ru");
    ProcessKRadixNumbersTask();
}

