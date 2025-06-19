#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include <string>  
#include <iostream> 
#include <vector>   

class Employee {
protected:          
    std::string id;  
    std::string name; 
    int experience;  

public:
    Employee(std::string empId, std::string empName, int exp);

    virtual ~Employee();

    // Методи для отримання значень полів
    std::string getId() const;
    std::string getName() const;
    int getExperience() const;

    // Методи для встановлення значень полів 
    void setId(const std::string &empId);
    void setName(const std::string &empName);
    void setExperience(int exp);

    // Віртуальний метод для відображення інформації про працівника
    // Може бути перевизначений у похідних класах для відображення специфічної інформації
    // Не є чисто віртуальним. Має реалізацію за замовчуванням у Employee.cpp
    virtual void displayInfo() const;

    // Чисто віртуальний метод для генерації рядка з даними обєкта для запису у файл
    // = 0 робить цей метод чисто віртуальним
    // Похідні класи зобовязані його реалізувати
    virtual std::string toFileString() const = 0;

    // Чисто віртуальний метод для отримання типу працівника у вигляді скороченого рядка 
    // Похідні класи зобовязані його реалізувати
    virtual std::string getTypeForFile() const = 0;
};

#endif 