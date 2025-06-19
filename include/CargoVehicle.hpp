#ifndef CARGOVEHICLE_HPP
#define CARGOVEHICLE_HPP

#include "Vehicle.hpp" 

class CargoVehicle : public Vehicle {
private:
    double cargoCapacity; 

public:
    CargoVehicle(std::string regNum, std::string brd, std::string mdl, int yr, double mlg, double cCapacity);

    ~CargoVehicle() override;

    // Метод для отримання вантажопідйомності 
    double getCargoCapacity() const;

    // Метод для встановлення вантажопідйомності 
    void setCargoCapacity(double cCapacity);

    // Перевизначений метод для інфи про вантажні авто
    void displayInfo() const override;

    // Повертає рядок з даними обєкта для запису у файл
    std::string toFileString() const override;
    // Повертає тип транспортного засобу у вигляді скороченого рядка 
    std::string getTypeForFile() const override;
};

#endif 