#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <string>   
#include <iostream> 

class Vehicle {
protected:              
    std::string regNumber; 
    std::string brand;     
    std::string model;   
    int year;              
    double mileage;       

public:
    Vehicle(std::string regNum, std::string brd, std::string mdl, int yr, double mlg);
    
    virtual ~Vehicle();
    
    // Методи для отримання значень полів 
    std::string getRegNumber() const;
    std::string getBrand() const;
    std::string getModel() const;
    int getYear() const;
    double getMileage() const;

    // Методи для встановлення значень полів 
    void setRegNumber(const std::string &regNum);
    void setBrand(const std::string &brd);
    void setModel(const std::string &mdl);
    void setYear(int yr);
    void setMileage(double mlg);

    // Віртуальний метод для відображення інформації про транспортний засіб
    // Може бути перевизначений у похідних класах для відображення специфічної інформації
    // Не є чисто віртуальним. Має реалізацію за замовчуванням у Vehicle.cpp
    virtual void displayInfo() const;

    // Чисто віртуальний метод для генерації рядка з даними обєкта для запису у файл
    // = 0 робить цей метод чисто віртуальним
    // Клас Vehicle не надає реалізації для цього методу і кожен неабстрактний
    // Похідний клас зобовязаний надати свою власну реалізацію
    virtual std::string toFileString() const = 0;

    // Чисто віртуальний метод для отримання типу транспортного засобу у вигляді скороченого рядка
    // Цей рядок використовується для ідентифікації типу авто при збереженні/завантаженні з файлу
    // Також зобовязує похідні класи реалізувати його
    virtual std::string getTypeForFile() const = 0;
};

#endif 