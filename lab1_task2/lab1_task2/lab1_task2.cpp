//Хромой король.На квадратной доске расставлены монеты, достоинством от 1 до
//100. Хромой король, находящийся в правом нижнем углу, мечтает попасть в левый верхний.
//При этом он может передвигаться только в клетку слева или сверху и хочет, чтобы сумма всех
//монет, оказавшихся у него на пути, была бы максимальной.Определить эту сумму и путь, каким
//образом должен двигаться король, чтобы ее собрать.Ввод и вывод организовать при помощи
//текстовых файлов.Формат входных данных : в первой строке входного файла записано число N
//- размер доски(1 < N < 80).Далее следует N строк, каждая из которых содержит N целых чисел,
//представляющих доску.В первую строку выходного файл нужно вывести единственное число :
//максимальную сумму, а во второй строке вывести путь в виде строки символов, обозначив символом L 
//движение влево, а символом U - движение вверх.

#include <iostream>
#include <fstream>
#include <vector>
#include "Header.h"
//FIX ME: Добавила необходимые библиоотеки
#include <limits>  
#include <string>  

//FIX ME: Убрала глобальное использование using namespace std;
//using namespace std;
//FIX ME: Перенесла все фигурные скобки на новую строку
//FIX ME: Разделила на модули
//FIX ME: Добавила setlocale( LC_ALL, "rus");
int main() 
{
    //FIX ME: Названия файлов с большой буквы
    //std::ifstream input("a.txt");
    //std::ofstream output("b.txt");
    setlocale( LC_ALL, "rus");
    std::ifstream input("A.txt");
    std::ofstream output("B.txt");
    //FIX ME: Проверка открытия файлов
    if (!CheckFileOpen(input, output))
    {
        input.close();
        output.close();
        return 1;
    }
    int N;
    //FIX ME: Проверка чтения N
    //input >> N;
    if (!ReadAndCheckN(input, N))
    {
        input.close();
        output.close();
        return 1;
    }
    //FIX ME: Проверка количества строк
    if (!CheckBoardDimensions(input, N))
    {
        input.close();
        output.close();
        return 1;
    }
    //FIX ME: Изменила название вектора
    //std::vector<std::vector<int>> docka(N, std::vector<int>(N));
    // Используем вектор векторов для представления доски
    std::vector<std::vector<int>> board(N, std::vector<int>(N));


    //FIX ME: Чтение доски из файла с проверкой
    //for (int i = 0; i < N; ++i) {
    //    for (int j = 0; j < N; ++j) {
    //        input >> docka[i][j];
    //    }
    //}
    if (!ReadAndCheckBoard(input, board, N))
    {
        input.close();
        output.close();
        return 1;
    }
    //FIX ME: Проверка на лишние символы
    if (!CheckExtraCharacters(input))
    {
        input.close();
        output.close();
        return 1;
    }

    // Вектор для хранения максимальных сумм
    std::vector<std::vector<int>> dp(N, std::vector<int>(N, 0));

    // Начальная позиция (правый нижний угол)
    dp[N - 1][N - 1] = board[N - 1][N - 1];

    //// Заполнение таблицы максимальных сумм
    //for (int i = N - 1; i >= 0; --i) {
    //    for (int j = N - 1; j >= 0; --j) {
    //        if (i < N - 1) {
    //            dp[i][j] = max(dp[i][j], dp[i + 1][j] + docka[i][j]);
    //        }
    //        if (j < N - 1) {
    //            dp[i][j] = max(dp[i][j], dp[i][j + 1] + docka[i][j]);
    //        }
    //    }
    //}



    // Заполнение ДП (двигаемся из правого нижнего угла)
    dp[N - 1][N - 1] = board[N - 1][N - 1];

    for (int i = N - 1; i >= 0; i--) {
        for (int j = N - 1; j >= 0; j--) {
            if (i == N - 1 && j == N - 1) continue;

            int fromDown = (i < N - 1) ? dp[i + 1][j] : -1;  // снизу
            int fromRight = (j < N - 1) ? dp[i][j + 1] : -1; // справа

            if (fromDown == -1) {
                dp[i][j] = fromRight + board[i][j];
            }
            else if (fromRight == -1) {
                dp[i][j] = fromDown + board[i][j];
            }
            else {
                dp[i][j] = std::max(fromDown, fromRight) + board[i][j];
            }
        }
    }




    // Максимальная сумма монет
    int maxSum = dp[0][0];
    output << maxSum << std::endl;

    // Восстановление пути
    std::vector<char> path;
    int x = 0, y = 0;

    while (x < N - 1 || y < N - 1) {
        if (x == N - 1) { // можем двигаться только вверх
            path.push_back('L');
            y++;
        }
        else if (y == N - 1) { // можем двигаться только влево
            path.push_back('U');
            x++;
        }
        else if (dp[x + 1][y] > dp[x][y + 1]) { // двигаться вверх
            path.push_back('L');
            y++;
        }
        else {
            path.push_back('U'); // двигаться влево
            x++;
        }
    }

    // Вывод пути
    for (char move : path) {
        output << move;
    }
    output << std::endl;

    input.close();
    output.close();
    std::cout << "Ответ записан в файле b.txt" << std::endl;
    return 0;
}
