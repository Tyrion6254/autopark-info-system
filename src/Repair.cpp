#include "../include/Repair.hpp" 
#include <sstream>              
#include <iomanip>               

Repair::Repair(std::string repId, std::string vehRegNum, std::string repDate, std::string desc, double c, std::string bId)
: id(repId), vehicleRegNumber(vehRegNum), date(repDate), description(desc), cost(c), brigadeId(bId) {}

Repair::~Repair() {}

// Метод для отримання ID ремонту
std::string Repair::getId() const { return id; }

// Метод для отримання ремонтованого авто
std::string Repair::getVehicleRegNumber() const { return vehicleRegNumber; }

// Метод для отримання дати ремонту
std::string Repair::getDate() const { return date; }

// Метод для отримання опису робіт
std::string Repair::getDescription() const { return description; }

// Метод для отримання вартості ремонту
double Repair::getCost() const { return cost; }

// Метод для отримання ID бригади
std::string Repair::getBrigadeId() const { return brigadeId; }

// Метод для встановлення ID ремонту
void Repair::setId(const std::string &repId) { id = repId; }

// Метод для відображення інформації про ремонт
void Repair::displayInfo() const {
    std::cout << "Repair ID: " << id << std::endl;                                    
    std::cout << "  Vehicle: " << vehicleRegNumber << std::endl; 
    std::cout << "  Date: " << date << std::endl;                                      
    std::cout << "  Work Description: " << description << std::endl;                   
    std::cout << "  Cost: " << std::fixed << std::setprecision(2) << cost << " UAH" << std::endl;
    std::cout << "  Brigade ID: " << brigadeId << std::endl;                                      
}

// Метод для генерації рядка для запису у файл
std::string Repair::toFileString() const {
    std::ostringstream oss; 
    oss << id << ";"
        << vehicleRegNumber << ";"
        << date << ";"
        << description << ";"
        << std::fixed << std::setprecision(2) << cost << ";"
        << brigadeId;
    return oss.str(); 
}