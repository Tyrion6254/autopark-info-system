#ifndef REPAIR_HPP
#define REPAIR_HPP

#include <string> 
#include <iostream> 
#include <iomanip>  

class Repair {
private:
    std::string id;             
    std::string vehicleRegNumber; 
    std::string date;             
    std::string description;     
    double cost;                 
    std::string brigadeId;      

public:
    Repair(std::string repId, std::string vehRegNum, std::string repDate, std::string desc, double c, std::string bId);

    ~Repair();

    // Методи для отримання значень полів 
    std::string getId() const;
    std::string getVehicleRegNumber() const;
    std::string getDate() const;
    std::string getDescription() const;
    double getCost() const;
    std::string getBrigadeId() const;

    // Методи для встановлення айді ремонту
    void setId(const std::string &repId);

    // Метод для відображення інформації про ремонт
    void displayInfo() const;

    // Повертає рядок з даними обєкта для запису у файл
    std::string toFileString() const;
};

#endif 