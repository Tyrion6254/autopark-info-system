#include "../include/AuxiliaryVehicle.hpp"
#include <sstream>
#include <iomanip>

AuxiliaryVehicle::AuxiliaryVehicle(std::string regNum, std::string brd, std::string mdl, int yr, double mlg, std::string purp)
: Vehicle(regNum, brd, mdl, yr, mlg), purpose(purp) {}

AuxiliaryVehicle::~AuxiliaryVehicle() {}

// Метод для отримання призначення 
std::string AuxiliaryVehicle::getPurpose() const { return purpose; }

// Метод для встановлення призначення
void AuxiliaryVehicle::setPurpose(const std::string &purp) { purpose = purp; }

// Перевизначений метод для інфи про допоміжні авто
void AuxiliaryVehicle::displayInfo() const {
    std::cout << "Vehicle Type: Auxiliary" << std::endl;
    Vehicle::displayInfo();
    std::cout << "  Purpose: " << purpose << std::endl;
}

// Перевизначений метод для генерації рядка для запису у файл
std::string AuxiliaryVehicle::toFileString() const {
    std::ostringstream oss;
    oss << getTypeForFile() << ";"
        << regNumber << ";"
        << brand << ";"
        << model << ";"
        << year << ";"
        << std::fixed << std::setprecision(1) << mileage << ";"
        << purpose;
    return oss.str();
}

// Перевизначений метод для отримання типу авто для файлу
std::string AuxiliaryVehicle::getTypeForFile() const { return "A"; }