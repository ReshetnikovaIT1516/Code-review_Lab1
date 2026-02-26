#include <iostream>
#include <fstream>
#include <vector>
#include <string>

/**
 * Проверяет открытие входного и выходного файлов
 */
bool CheckFileOpen(std::ifstream& input, std::ofstream& output);

/**
 * Читает и проверяет размер доски N
 */
bool ReadAndCheckN(std::ifstream& input, int& N);

/**
 * Проверяет количество строк в файле
 */
bool CheckBoardDimensions(std::ifstream& input, int N);

/**
 * Читает и проверяет доску с монетами
 */
bool ReadAndCheckBoard(std::ifstream& input, std::vector<std::vector<int>>& board, int N);

/**
 * Проверяет наличие лишних символов в файле
 */
bool CheckExtraCharacters(std::ifstream& input);

