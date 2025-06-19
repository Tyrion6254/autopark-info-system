#include "../include/Vehicle.hpp"
#include <iomanip>

Vehicle::Vehicle(std::string regNum, std::string brd, std::string mdl, int yr, double mlg)
: regNumber(regNum), brand(brd), model(mdl), year(yr), mileage(mlg) {}

Vehicle::~Vehicle() {}

// Метод для отримання номера
std::string Vehicle::getRegNumber() const { return regNumber; }

// Метод для отримання марки
std::string Vehicle::getBrand() const { return brand; }

// Метод для отримання моделі
std::string Vehicle::getModel() const { return model; }

// Метод для отримання року
int Vehicle::getYear() const { return year; }

// Метод для отримання пробігу
double Vehicle::getMileage() const { return mileage; }

// Метод для встановлення номера
void Vehicle::setRegNumber(const std::string &regNum) { regNumber = regNum; }

// Метод для встановлення марки
void Vehicle::setBrand(const std::string &brd) { brand = brd; }

// Метод для встановлення моделі
void Vehicle::setModel(const std::string &mdl) { model = mdl; }

// Метод для встановлення року
void Vehicle::setYear(int yr) { year = yr; }

// Метод для встановлення пробігу
void Vehicle::setMileage(double mlg) { mileage = mlg; }

// Спільна інфо для всіх авто
void Vehicle::displayInfo() const {
    std::cout << "  Registration Number: " << regNumber << std::endl;
    std::cout << "  Brand: " << brand << std::endl;
    std::cout << "  Model: " << model << std::endl;
    std::cout << "  Year of Manufacture: " << year << std::endl;
    std::cout << "  Mileage: " << std::fixed << std::setprecision(1) << mileage << " km" << std::endl;
}
