//Археолог нашел N артефактов.Известны веса(сi) и налоговое бремя(di) находок.
//Нужно выбрать такое подмножество находок, чтобы их суммарный вес превысил Z кг, а их общее 
//налоговое бремя оказалось минимальным.Известно, что решение единственно.Укажите
//порядковые номера вещей, которые нужно взять.Исходный данные находятся в текстовом файле, 
//в первой строке указаны N и Z, а во второй строке значения весов(в кг), в третьей - величина
//налога по каждой находке.Вывести так же суммарный вес и общую ценность результата.

#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
//FIX ME: Добавила необходимые библиотеки 
#include <sstream>  
#include <string>   

#include "Header.h"


//FIX ME: Убрала глобальное использование using namespace std;
//FIX ME: Перенесла все фигурные скобки на новую строку
//FIX ME: Добавила функции проверки
//FIX ME: Добавила разделение на модули 

int main()
{
    setlocale(LC_ALL, "russian");

    std::ifstream input("t.txt");

    if (!input.is_open()) 
    {
        std::cout << "Ошибка открытия файла!" << std::endl;
        //FIX ME: Возвращаем код ошибки
        return 1; 
    }
    //FIX ME: Замена обычного чтения на безопасное
    //int N, Z;
    //input >> N >> Z; // Считываем количество предметов и минимальный вес Z
    int N, Z;
    int lineNum = 1;
    if (!SafeReadInt(input, N, lineNum))
    {
        return 1;
    }
    if (!SafeReadInt(input, Z, lineNum))
    {
        return 1;
    }

    //FIX ME: Проверка корректности N и Z
    // Проверка N и Z
    if (N <= 0) 
    {
        std::cout << "Ошибка: N должно быть положительным числом!" << std::endl;
        return 1;
    }

    if (Z < 0) 
    {
        std::cout << "Ошибка: Z не может быть отрицательным!" << std::endl;
        return 1;
    }

    //FIX ME: Пропускаем остаток первой строки
    std::string skipLine;
    getline(input, skipLine);


    //FIX ME: Проверка строки с весами
    lineNum = 2;
    if (!HasEnoughNumbersInLine(input, N, lineNum))
    {
        return 1;
    }

    
    std::vector<int> weights; // Вектор для хранения весов предметов
    std::vector<int> taxes; // Вектор для хранения налогового бремени предметов

    //FIX ME: Замена чтения весов
    //// Считываем веса предметов
    //for (int i = 0; i < N; ++i)
    //{
    //    int value;
    //    input >> value;
    //    weights.push_back(value);
    //}


    for (int i = 0; i < N; ++i)
    {
        int value;
        if (!SafeReadInt(input, value, lineNum))
        {
            std::cout << "Ошибка при чтении " << i + 1 << "-го веса" << std::endl;
            return 1;
        }
        weights.push_back(value);
    }

    //FIX ME:  ПРОВЕРКА ВЕСОВ ПОСЛЕ СЧИТЫВАНИЯ 
    for (int i = 0; i < N; i++) 
    {
        if (weights[i] < 0) 
        {
            std::cout << "Ошибка: вес предмета " << i + 1 << " отрицательный: " << weights[i] << std::endl;
            return 1;  // Программа завершается здесь, не вызывая knapSack
        }
    }
    //FIX ME: Замена чтения налогового бремени
    //// Считываем налоговое бремя предметов
    //for (int i = 0; i < N; ++i)
    //{
    //    int value;
    //    input >> value;
    //    taxes.push_back(value);
    //}


    //FIX ME: Проверка строки с налогами
    std::string skipSecondLine;
    getline(input, skipSecondLine);
    lineNum = 3;
    if (!HasEnoughNumbersInLine(input, N, lineNum))
    {
        return 1;
    }

    for (int i = 0; i < N; ++i)
    {
        int value;
        if (!SafeReadInt(input, value, lineNum))
        {
            std::cout << "Ошибка при чтении " << i + 1 << "-го налога" << std::endl;
            return 1;
        }
        taxes.push_back(value);
    }

    //FIX ME: ПРОВЕРКА НАЛОГОВ ПОСЛЕ СЧИТЫВАНИЯ 
    for (int i = 0; i < N; i++)
    {
        if (taxes[i] < 0)
        {
            std::cout << "Ошибка: налог предмета " << i + 1 << " отрицательный: " << taxes[i] << std::endl;
            return 1;  // Программа завершается здесь, не вызывая knapSack
        }
    }
    input.close();

    //FIX ME: Проверка количества считанных данных
    if (weights.size() != N || taxes.size() != N)
    {
        std::cout << "Ошибка: неверный формат файла! Недостаточно данных." << std::endl;
        return 1;
    }

    // Проверка на лишние данные
    char remaining;
    if (input >> remaining) 
    {
        std::cout << "Предупреждение: в файле есть лишние данные после основной информации" << std::endl;
    }


    KnapSack(Z, weights, taxes);
    //FIX ME: Явный возврат 0
    return 0; 
}