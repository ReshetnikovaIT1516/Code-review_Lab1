#include "Header.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <limits>

//FIX ME: Переименовала функцию
// double Count(int N, int K) 
double CountNumbersWithFourConsecutiveZeros(int N, int K)
{
    // dp[i][j] — количество чисел длины i, заканчивающихся на j подряд идущих нулей
    // dp[i][4] — количество чисел, где уже было 4+ подряд идущих нулей
    std::vector<std::vector<long long>> countingTable(N + 1, std::vector<long long>(5, 0));
    //FIX ME: неправильная логика
    //dp[1][0] = K - 1;  // Любая цифра кроме нуля
    //dp[1][1] = 1;      // Только ноль

    //FIX ME: Переименовала переменную dp

    countingTable[1][0] = K - 1;  // цифры 1..K-1
    countingTable[1][1] = 0;      // первая цифра не может быть 0!

    for (int i = 2; i <= N; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            countingTable[i][0] += countingTable[i - 1][j] * (K - 1);
        }
        countingTable[i][1] += countingTable[i - 1][0];
        countingTable[i][2] += countingTable[i - 1][1];
        countingTable[i][3] += countingTable[i - 1][2];

        countingTable[i][4] += countingTable[i - 1][3];

        countingTable[i][4] += countingTable[i - 1][4] * K;
    }

    double count = countingTable[N][4];
    std::cout << "Количество чисел, содержащих болше 3 нулей подряд: " << count << std::endl;
    return count;
}

//void HomeDyn16() {
//    int N, K;
//
//    cout << "Система счисления: "; cin >> K;
//    cout << "Количество разрядов: "; cin >> N;
//
//    /*double all = pow(K, N);*/
//    double all = (K - 1) * pow(K, N - 1);  // Первая цифра не может быть 0
//    cout << "Общее количество: " << all << endl;
//    double result = Count(N, K) / all;
//    cout << result << endl;
//}
//FIX ME: Переименовала функцию
// void HomeDyn16()
void ProcessKRadixNumbersTask()
{
    int N, K;
    //FIX ME: Добавлены проверки на ввод K и N
    // Ввод K с проверкой
    while (true)
    {
        std::cout << "Система счисления (2-10): ";
        std::cin >> K;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка: введите целое число!" << std::endl;
            continue;
        }

        if (K < 2 || K > 10)
        {
            std::cout << "Ошибка: K должно быть от 2 до 10!" << std::endl;
            continue;
        }

        break; // K введен правильно
    }

    // Ввод N с проверкой
    while (true)
    {
        std::cout << "Количество разрядов (2-" << std::min(19, 25 - K) << "): ";
        std::cin >> N;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка: введите целое число!" << std::endl;
            continue;
        }

        // Проверка из условия 1 < N < 20
        if (N < 2 || N > 19)
        {
            std::cout << "Ошибка: N должно быть от 2 до 19!" << std::endl;
            continue;
        }

        // Проверка N + K < 26
        if (N + K >= 26)
        {
            std::cout << "Ошибка: N + K должно быть меньше 26! (макс. N = " << 25 - K << ")" << std::endl;
            continue;
        }

        break; // N введен правильно
    }

    // ОСНОВНАЯ ЛОГИКА 
    //FIX ME: Переименовала переменную
    // double all = (K - 1) * pow(K, N - 1); 
    double totalPossibleNumbers = (K - 1) * pow(K, N - 1);  // Первая цифра не может быть 0
    std::cout << "Общее количество: " << totalPossibleNumbers << std::endl;

    double result = CountNumbersWithFourConsecutiveZeros(N, K) / totalPossibleNumbers;
    std::cout << "Результат: " << result << std::endl;
}