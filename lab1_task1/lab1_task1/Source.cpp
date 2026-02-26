#include "Header.h"
#include <iostream>
#include <sstream>
#include <cctype>
#include <climits>


//FIX ME: Добавила функции проверки
// Функция для проверки, является ли строка числом
bool IsNumber(const std::string& str)
{
    if (str.empty())
    {
        return false;
    }

    size_t start = 0;
    if (str[0] == '-')
    {
        start = 1; // Разрешаем отрицательные числа
    }

    for (size_t i = start; i < str.length(); i++)
    {
        if (!isdigit(str[i])) return false;
    }
    return true;
}

// Функция для безопасного чтения числа из потока
bool SafeReadInt(std::ifstream& file, int& value, int lineNum)
{
    std::string token;
    file >> token;

    if (file.fail() || token.empty())
    {
        std::cout << "Ошибка: Не удалось прочитать число в строке " << lineNum << std::endl;
        return false;
    }

    if (!IsNumber(token))
    {
        std::cout << "Ошибка: В файле обнаружена буква '" << token << "' вместо числа в строке " << lineNum << std::endl;
        return false;
    }

    value = stoi(token);
    return true;
}

// Проверка, что в текущей строке достаточно чисел
bool HasEnoughNumbersInLine(std::ifstream& file, int requiredCount, int lineNum)
{
    std::streampos currentPos = file.tellg();  // Запоминаем текущую позицию
    std::string line;
    std::getline(file, line);  // Читаем всю строку

    if (file.fail())
    {
        std::cout << "Ошибка: Не удалось прочитать строку " << lineNum << std::endl;
        return false;
    }

    std::stringstream ss(line);
    std::string token;
    int count = 0;

    while (ss >> token)
    {
        if (IsNumber(token))
        {
            count++;
        }
        else
        {
            std::cout << "Ошибка: В строке " << lineNum << " обнаружена буква '" << token << "' вместо числа" << std::endl;
            return false;
        }
    }

    if (count != requiredCount)
    {
        std::cout << "Ошибка: В строке " << lineNum << " должно быть " << requiredCount
            << " чисел, а найдено " << count << std::endl;
        return false;
    }

    // Возвращаемся к началу строки для последующего чтения
    file.clear();
    file.seekg(currentPos);
    return true;
}

//FIX ME: Переименовала переменные и функцию
// W - minRequiredWeight
// wt - itemWeights
// val - itemTaxes
// void knapSack(int W, vector<int>& wt vector<int>& val) 

// Функция для решения задачи о рюкзаке
void KnapSack(int minRequiredWeight, std::vector<int>& itemWeights, std::vector<int>& itemTaxes)
{
    //FIX ME: Переименовала переменную 
    // n - itemCount
    // int n = itemWeights.size(); // Количество предметов

    int itemCount = itemWeights.size(); // Количество предметов
    int maxWeight = 0; // Максимально возможный вес всех предметов
    //FIX ME: Переименовала переменную 
    // w - currentWeight
    //  for (int w : itemWeights) maxWeight += w;

    for (int currentWeight : itemWeights)
    {
        maxWeight += currentWeight; // Считаем общий вес всех предметов
    }

    //FIX ME:  Переименовала вектор
    // dp - minTaxForWeight
    //  vector<int> dp(maxWeight + 1, INT_MAX); 

    // Вектор dp, где dp[w] хранит минимальное налоговое бремя для веса w
    std::vector<int> minTaxForWeight(maxWeight + 1, INT_MAX);
    minTaxForWeight[0] = 0; // Нулевой вес имеет нулевое налоговое бремя

    //FIX ME: Переименовала переменную 
    // n - itemCount

    // Матрица selected, где selected[w][i] = true, если предмет i включен в набор для веса w
    std::vector<std::vector<bool>> selected(maxWeight + 1, std::vector<bool>(itemCount, false));

    // Заполняем dp и selected
    for (int i = 0; i < itemCount; i++)
    { // Перебираем все предметы
            //FIX ME: Переименовала переменную 
            // w - currentWeight
            // for (int w = maxWeight; w >= itemWeights[i]; w--)

        for (int currentWeight = maxWeight; currentWeight >= itemWeights[i]; currentWeight--) // Перебираем все возможные веса
        {
            // Если можно достичь веса (w - wt[i]) и добавление текущего предмета улучшает результат
            if (minTaxForWeight[currentWeight - itemWeights[i]] != INT_MAX && minTaxForWeight[currentWeight - itemWeights[i]] + itemTaxes[i] < minTaxForWeight[currentWeight])
            {
                minTaxForWeight[currentWeight] = minTaxForWeight[currentWeight - itemWeights[i]] + itemTaxes[i]; // Обновляем минимальное налоговое бремя
                selected[currentWeight] = selected[currentWeight - itemWeights[i]]; // Копируем набор предметов для веса (w - wt[i])
                selected[currentWeight][i] = true; // Добавляем текущий предмет в набор
            }
        }
    }

    // Находим минимальное налоговое бремя для весов >= W
    int minVal = INT_MAX;
    int bestWeight = 0; // Вес, соответствующий минимальному налоговому бремени
    std::vector<bool> bestSelection(itemCount, false); // Набор предметов, дающий минимальное налоговое бремя


    //FIX ME:  Проверка, можно ли вообще достичь вес >= W
    bool possible = false;
    for (int currentWeight = minRequiredWeight; currentWeight <= maxWeight; currentWeight++)
    {
        if (minTaxForWeight[currentWeight] != INT_MAX)
        {
            possible = true;
            break;
        }
    }

    if (!possible)
    {
        std::cout << "Невозможно достичь минимального веса " << minRequiredWeight << " кг" << std::endl;
        return;
    }


    for (int currentWeight = minRequiredWeight; currentWeight <= maxWeight; currentWeight++) // Перебираем все веса >= W
    {
        if (minTaxForWeight[currentWeight] < minVal) // Если найдено лучшее решение
        {
            minVal = minTaxForWeight[currentWeight]; // Обновляем минимальное налоговое бремя
            bestWeight = currentWeight; // Запоминаем вес
            bestSelection = selected[currentWeight]; // Запоминаем набор предметов
        }
    }

    // Вывод результата
    if (minVal == INT_MAX) // Если решение не найдено
    {
        std::cout << "Невозможно достичь минимального веса " << minRequiredWeight << std::endl;
    }
    else// Если решение найдено
    {
        std::cout << "Порядковые номера выбранных предметов: ";
        for (int i = 0; i < itemCount; i++)
        {
            if (bestSelection[i])
            {
                std::cout << i + 1 << " ";
            }
        }
        std::cout << std::endl;

        // Выводим общий вес и итоговое налоговое бремя
        std::cout << "Общий вес: " << bestWeight << " кг" << std::endl;
        std::cout << "Итоговое налогообложение: " << minVal << std::endl;

    }
}