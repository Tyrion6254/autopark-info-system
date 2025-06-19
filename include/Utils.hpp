#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>    
#include <vector>    
#include <iostream>  
#include <limits>    
#include <sstream>  
#include <algorithm> 
#include <cctype>   

// Розділяє рядок на підрядки за роздільником
std::vector<std::string> splitString(const std::string &str, char delimiter);

// Функція для обєднання рядків у один
std::string joinString(const std::vector<std::string> &elements, char delimiter);

// Функція для отримання цілого числа
int getValidatedIntInput(const std::string &prompt);

// Перевантажена функція для отримання цілого числа в певному діапазоні
int getValidatedIntInput(const std::string &prompt, int minVal, int maxVal);

// Реалізація функції для отримання double з перевіркою
double getValidatedDoubleInput(const std::string &prompt);

// Перевантажена функція для отримання double в певному діапазоні
double getValidatedDoubleInput(const std::string &prompt, double minVal, double maxVal);

// Функція для отримання рядка з перевіркою
std::string getValidatedStringInput(const std::string &prompt, bool allowEmpty = false);

// Функція для перетворення рядка в нижній регістр
std::string toLower(std::string s);

// Функція для обрізки пробілів
std::string trim(const std::string &str);

// Функція для очищення вводу
void clearInputBuffer();

#endif 