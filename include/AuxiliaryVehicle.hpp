#ifndef AUXILIARYVEHICLE_HPP
#define AUXILIARYVEHICLE_HPP

#include "Vehicle.hpp" 

class AuxiliaryVehicle : public Vehicle {
private:
    std::string purpose;

public:
    AuxiliaryVehicle(std::string regNum, std::string brd, std::string mdl, int yr, double mlg, std::string purp);

    ~AuxiliaryVehicle() override;

    // Метод для отримання призначення 
    std::string getPurpose() const;

    // Метод для встановлення призначення
    void setPurpose(const std::string &purp);

    // Перевизначений метод для інфи про допоміжні авто
    void displayInfo() const override;

    // Повертає рядок з даними обєкта для запису у файл
    std::string toFileString() const override;
    // Повертає тип транспортного засобу у вигляді скороченого рядка 
    std::string getTypeForFile() const override;
};

#endif 