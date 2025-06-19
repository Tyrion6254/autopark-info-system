#include "../include/Driver.hpp" 
#include <algorithm>             

Driver::Driver(std::string empId, std::string empName, int exp,
            const std::vector<std::string> &licCategories,
            const std::vector<std::string> &assignedVehicles)
: Employee(empId, empName, exp), licenseCategories(licCategories), assignedVehicleRegNumbers(assignedVehicles) {}

Driver::~Driver() {}

// Метод для отримання списку категорій водійських прав
std::vector<std::string> Driver::getLicenseCategories() const { return licenseCategories; }

// Метод для отримання списку номерів авто
std::vector<std::string> Driver::getAssignedVehicleRegNumbers() const { return assignedVehicleRegNumbers; }

// Метод для встановлення нового списку категорій прав
void Driver::setLicenseCategories(const std::vector<std::string> &licCategories) { licenseCategories = licCategories; }

// Метод для додавання номера авто до списку 
void Driver::addAssignedVehicle(const std::string &regNumber) {
// Перевірка на дублювання
    if (std::find(assignedVehicleRegNumbers.begin(), assignedVehicleRegNumbers.end(), regNumber) == assignedVehicleRegNumbers.end())
    { assignedVehicleRegNumbers.push_back(regNumber); }
}

// Метод для видалення номера авто зі списку 
void Driver::removeAssignedVehicle(const std::string &regNumber) {
    assignedVehicleRegNumbers.erase(
        std::remove(assignedVehicleRegNumbers.begin(), assignedVehicleRegNumbers.end(), regNumber),
        assignedVehicleRegNumbers.end());
}

// Перевизначений метод для інфи про водія
void Driver::displayInfo() const {
    std::cout << "Employee Type: Driver" << std::endl;                                                              
    Employee::displayInfo();                                                                                       
    std::cout << "  License Categories: " << joinString(licenseCategories, ',') << std::endl;                     
    std::cout << "  Assigned Vehicles: " << joinString(assignedVehicleRegNumbers, ',') << std::endl; 
}

// Перевизначений метод для генерації рядка для запису у файл
std::string Driver::toFileString() const {
    return getTypeForFile() + ";" +
           id + ";" +
           name + ";" +
           std::to_string(experience) + ";" + 
           joinString(licenseCategories, ',') + ";" +
           joinString(assignedVehicleRegNumbers, ',');
}

// Перевизначений метод для отримання типу працівника для файлу
std::string Driver::getTypeForFile() const { return "D"; }