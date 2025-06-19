#ifndef BRIGADE_HPP
#define BRIGADE_HPP

#include <string>   
#include <iostream>

class Brigade {
private:
    std::string id;        
    std::string name;      
    std::string foremanId; 

public:
    Brigade(std::string bId, std::string bName, std::string fId);

    ~Brigade();

    // Методи для отримання значень полів 
    std::string getId() const;
    std::string getName() const;
    std::string getForemanId() const;

    // Методи для встановлення значень полів 
    void setId(const std::string &bId);
    void setName(const std::string &bName);
    void setForemanId(const std::string &fId);

    // Метод для відображення інформації про бригаду на консоль
    void displayInfo() const;
    
    // Метод для генерації рядка з даними обєкта для запису у файл
    std::string toFileString() const;
};

#endif