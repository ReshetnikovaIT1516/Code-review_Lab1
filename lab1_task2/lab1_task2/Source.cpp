#include <iostream>
#include <fstream>
#include <vector>
#include "Header.h"
//FIX ME: Добавила необходимые библиоотеки
#include <limits>  
#include <string>  

//FIX ME: Добавила проверки
// Функции проверки ввода
bool CheckFileOpen(std::ifstream& input, std::ofstream& output)
{
    if (!input.is_open())
    {
        std::cout << "Ошибка: не удалось открыть файл A.txt" << std::endl;
        return false;
    }

    if (!output.is_open())
    {
        std::cout << "Ошибка: не удалось создать файл B.txt" << std::endl;
        return false;
    }

    return true;
}

bool ReadAndCheckN(std::ifstream& input, int& N)
{
    if (!(input >> N))
    {
        std::cout << "Ошибка: в файле должно быть число N" << std::endl;
        return false;
    }

    if (N <= 1 || N >= 80)
    {
        std::cout << "Ошибка: N должно быть в диапазоне 1 < N < 80" << std::endl;
        return false;
    }

    return true;
}
bool CheckBoardDimensions(std::ifstream& input, int N)
{
    // Сохраняем текущую позицию в файле
    std::streampos oldPos = input.tellg();

    int rowCount = 0;
    std::string line;

    // Считаем количество строк с числами
    while (input.peek() != EOF && rowCount < N + 1)
    {
        std::getline(input, line);
        if (!line.empty())
        {
            rowCount++;
        }
    }

    // Возвращаемся на сохраненную позицию
    input.clear();
    input.seekg(oldPos);

    if (rowCount < N)
    {
        std::cout << "Ошибка: в файле меньше строк, чем указано N=" << N << std::endl;
        std::cout << "Найдено строк: " << rowCount << std::endl;
        return false;
    }

    return true;
}

bool ReadAndCheckBoard(std::ifstream& input, std::vector<std::vector<int>>& board, int N)
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (!(input >> board[i][j]))
            {
                std::cout << "Ошибка: неверный формат данных в позиции [" << i << "][" << j << "]" << std::endl;
                std::cout << "Ожидалось число от 1 до 100" << std::endl;
                return false;
            }

            if (board[i][j] < 1 || board[i][j] > 100)
            {
                std::cout << "Ошибка: значение монеты должно быть от 1 до 100" << std::endl;
                std::cout << "В позиции [" << i << "][" << j << "] = " << board[i][j] << std::endl;
                return false;
            }
        }
    }

    return true;
}

bool CheckExtraCharacters(std::ifstream& input)
{
    char extraChar;
    if (input >> extraChar)
    {
        std::cout << "Ошибка: в файле есть лишние символы после данных" << std::endl;
        return false;
    }

    return true;
}



