#ifndef PASSENGERVEHICLE_HPP
#define PASSENGERVEHICLE_HPP

#include "Vehicle.hpp" 

class PassengerVehicle : public Vehicle {
private:
     int capacity; 

public:
    PassengerVehicle(std::string regNum, std::string brd, std::string mdl, int yr, double mlg, int cap);

    ~PassengerVehicle() override;

    // Метод для отримання місткості 
    int getCapacity() const;
    
    // Метод для встановлення місткості 
    void setCapacity(int cap);

    // Перевизначений метод для інфи про пасажирські авто
    void displayInfo() const override;

    // Повертає рядок з даними обєкта для запису у файл
    std::string toFileString() const override;
    // Повертає тип транспортного засобу у вигляді скороченого рядка 
    std::string getTypeForFile() const override;
};

#endif 