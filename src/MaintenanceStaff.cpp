#include "../include/MaintenanceStaff.hpp" 

MaintenanceStaff::MaintenanceStaff(std::string empId, std::string empName, int exp, std::string spec)
: Employee(empId, empName, exp), specialization(spec) {}

MaintenanceStaff::~MaintenanceStaff() {}

// Метод для отримання спеціалізації
std::string MaintenanceStaff::getSpecialization() const { return specialization; }

// Метод для встановлення спеціалізації
void MaintenanceStaff::setSpecialization(const std::string &spec) { specialization = spec; }

// Перевизначений метод для інфи про працівника
void MaintenanceStaff::displayInfo() const {
    std::cout << "Employee Type: Maintenance Staff" << std::endl;  
    Employee::displayInfo();                                        
    std::cout << "  Specialization: " << specialization << std::endl; 
}

// Перевизначений метод для генерації рядка для запису у файл
std::string MaintenanceStaff::toFileString() const {
    return getTypeForFile() + ";" +
           id + ";" +
           name + ";" +
           std::to_string(experience) + ";" + 
           specialization;
}

// Перевизначений метод для отримання типу працівника для файлу
std::string MaintenanceStaff::getTypeForFile() const { return "M"; }