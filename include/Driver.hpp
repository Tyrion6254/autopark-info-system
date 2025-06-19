#ifndef DRIVER_HPP
#define DRIVER_HPP

#include "Employee.hpp"        
#include "../include/Utils.hpp" 
#include <vector>              
#include <string>             
#include <algorithm>           

class Driver : public Employee {
private:
    std::vector<std::string> licenseCategories;        
    std::vector<std::string> assignedVehicleRegNumbers; 

public:
    Driver(std::string empId, std::string empName, int exp,
           const std::vector<std::string> &licCategories,
           const std::vector<std::string> &assignedVehicles);

    ~Driver() override;

    // Методи для отримання значень полів 
    std::vector<std::string> getLicenseCategories() const;
    std::vector<std::string> getAssignedVehicleRegNumbers() const;

    // Метод для встановлення категорії прав
    void setLicenseCategories(const std::vector<std::string> &licCategories);

    // Методи для модифікації значень полів 
    void addAssignedVehicle(const std::string &regNumber);    // Додати авто
    void removeAssignedVehicle(const std::string &regNumber); // Видалити авто

    // Перевизначений метод для інфи про водія
    void displayInfo() const override;

    // Повертає рядок з даними обєкта для запису у файл
    std::string toFileString() const override;
    // Повертає тип транспортного засобу у вигляді скороченого рядка 
    std::string getTypeForFile() const override;
};

#endif 