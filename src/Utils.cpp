#include "../include/Utils.hpp"

// Розділяє рядок на підрядки за роздільником
std::vector<std::string> splitString(const std::string &str,
                                    char delimiter) {
    std::vector<std::string> tokens; 
    std::string token;               
    std::istringstream tokenStream(str); //Поток для читання
    while (std::getline(tokenStream, token, delimiter))
    {tokens.push_back(trim(token)); }
    return tokens; }

// Функція для обєднання рядків у один
std::string joinString(const std::vector<std::string> &elements,
                        char delimiter) {
    std::string result = ""; 
    for (size_t i = 0; i < elements.size(); ++i) {result += elements[i];
    if (i < elements.size() - 1) { result += delimiter; } }
    return result; } 

// Функція для очищення вводу
void clearInputBuffer() { std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); }

// Функція для отримання цілого числа
int getValidatedIntInput(const std::string &prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.good()) {
            clearInputBuffer();
            return value; }

        else {
            std::cout << "Invalid input. Please enter an integer.\n";
            std::cin.clear();
            clearInputBuffer(); } }
}


// Перевантажена функція для отримання цілого числа в певному діапазоні
int getValidatedIntInput(const std::string &prompt,
                            int minVal,
                            int maxVal) {
    int value;
    while (true) {
        value = getValidatedIntInput(prompt);
        if (value >= minVal && value <= maxVal) { return value; }
        else {std::cout << "Value must be between " << minVal << " and " << maxVal << ". Try again.\n";} }
}

// Реалізація функції для отримання double з перевіркою
double getValidatedDoubleInput(const std::string &prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
            if (std::cin.good()) {
                clearInputBuffer();
                return value; }
            else {
                std::cout << "Invalid input. Please enter a number (123.45).\n";
                std::cin.clear();
                clearInputBuffer(); } }
}

// Перевантажена функція для отримання double в певному діапазоні
double getValidatedDoubleInput(const std::string &prompt,
                                double minVal,
                                double maxVal) {
    double value;
    while (true) {
        value = getValidatedDoubleInput(prompt);
        if (value >= minVal && value <= maxVal){return value;}
        else { std::cout << "Value must be between " << minVal << " and " << maxVal << ". Try again.\n"; } }
}

// Функція для отримання рядка з перевіркою
std::string getValidatedStringInput(const std::string &prompt, 
                                    bool allowEmpty) {
    std::string value;
    while (true) {
        std::cout << prompt;           
        std::getline(std::cin, value);
        value = trim(value); 
        if (!value.empty() || allowEmpty){return value;}
        else { std::cout << "Input cannot be empty. Try again.\n"; } }
}

// Функція для перетворення рядка в нижній регістр
std::string toLower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c)             
                   { return std::tolower(c); }); 
                   //З-До-У Пр-Пов
return s; }

// Функція для обрізки пробілів
std::string trim(const std::string &str) {
    const std::string whitespace = " \t\n\r\f\v";
    // Знаходження першого символу
    size_t start = str.find_first_not_of(whitespace);
    if (start == std::string::npos){return "";}
    // Знаходження останнього символу
    size_t end = str.find_last_not_of(whitespace);
    // Вирізання підрядка
    return str.substr(start, end - start + 1);
}