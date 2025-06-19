#ifndef GARAGE_HPP
#define GARAGE_HPP

#include <string>   
#include <iostream> 

class Garage {
private:
    std::string id;   
    std::string name; 

public:
    Garage(std::string gId, std::string gName);

    ~Garage();

    // Методи для отримання значень полів 
    std::string getId() const;
    std::string getName() const;

    // Методи для встановлення значень полів 
    void setId(const std::string &gId);
    void setName(const std::string &gName);

    // Метод для відображення інформації про гараж
    void displayInfo() const;

    // Метод для генерації рядка для запису у файл
    std::string toFileString() const;
};

#endif 