#ifndef MAINTENANCEDETAIL_HPP 
#define MAINTENANCEDETAIL_HPP

#include "Employee.hpp"
#include <string>    

class MaintenanceStaff : public Employee{
private:
    std::string specialization; 

public:

    MaintenanceStaff(std::string empId, std::string empName, int exp, std::string spec);

    ~MaintenanceStaff() override;

    // Метод для отримання спеціалізації
    std::string getSpecialization() const;

    // Метод для встановлення спеціалізації 
    void setSpecialization(const std::string &spec);

    // Перевизначений метод для інфи про працівника
    void displayInfo() const override;
    
    // Повертає рядок з даними обєкта для запису у файл
    std::string toFileString() const override;
    // Повертає тип транспортного засобу у вигляді скороченого рядка 
    std::string getTypeForFile() const override;
};

#endif 