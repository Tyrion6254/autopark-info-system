#include "../include/PassengerVehicle.hpp" 
#include <sstream>                        
#include <iomanip>                       

PassengerVehicle::PassengerVehicle(std::string regNum, std::string brd, std::string mdl, int yr, double mlg, int cap)
: Vehicle(regNum, brd, mdl, yr, mlg), capacity(cap) {}

PassengerVehicle::~PassengerVehicle() {}

// Метод для отримання місткості
int PassengerVehicle::getCapacity() const { return capacity; }

// Метод для встановлення місткості
void PassengerVehicle::setCapacity(int cap) { capacity = cap; }

// Перевизначений метод для інфи про пасажирські авто
void PassengerVehicle::displayInfo() const {
    std::cout << "Vehicle Type: Passenger" << std::endl;                 
    Vehicle::displayInfo();                                                
    std::cout << "  Capacity: " << capacity << " passengers" << std::endl; }

// Перевизначений метод для генерації рядка для запису у файл
std::string PassengerVehicle::toFileString() const {
    std::ostringstream oss; 
    oss << getTypeForFile() << ";"
        << regNumber << ";"
        << brand << ";"
        << model << ";"
        << year << ";"
        << std::fixed << std::setprecision(1) << mileage << ";" 
        << capacity;                                            
    return oss.str();                                           
}

// Перевизначений метод для отримання типу авто для файлу
std::string PassengerVehicle::getTypeForFile() const { return "P"; }