#include "../include/CargoVehicle.hpp"
#include <sstream> 
#include <iomanip> 

CargoVehicle::CargoVehicle(std::string regNum, std::string brd, std::string mdl, int yr, double mlg, double cCapacity)
: Vehicle(regNum, brd, mdl, yr, mlg), cargoCapacity(cCapacity) {}

CargoVehicle::~CargoVehicle() {}

// Метод для отримання вантажопідйомності
double CargoVehicle::getCargoCapacity() const { return cargoCapacity; }

// Метод для встановлення вантажопідйомності
void CargoVehicle::setCargoCapacity(double cCapacity) { cargoCapacity = cCapacity; }

// Перевизначений метод для інфи про вантажні авто
void CargoVehicle::displayInfo() const
{
    std::cout << "Vehicle Type: Cargo" << std::endl;
    Vehicle::displayInfo();
    std::cout << "  Cargo Capacity: " << std::fixed << std::setprecision(1)
              << cargoCapacity << " kg" << std::endl;
}

// Перевизначений метод для генерації рядка для запису у файл
std::string CargoVehicle::toFileString() const {
    std::ostringstream oss;
    oss << getTypeForFile() << ";"
        << regNumber << ";"
        << brand << ";"
        << model << ";"
        << year << ";"
        << std::fixed << std::setprecision(1) << mileage << ";"
        << std::fixed << std::setprecision(1) << cargoCapacity;
    return oss.str();
}

// Перевизначений метод для отримання типу авто для файлу
std::string CargoVehicle::getTypeForFile() const { return "C"; }