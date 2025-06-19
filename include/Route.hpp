#ifndef ROUTE_HPP
#define ROUTE_HPP

#include <string>            
#include <vector>              
#include <iostream>       
#include "../include/Utils.hpp" 
#include <algorithm>       

class Route {
private:
    std::string id;                                    
    std::string description;                        
    std::vector<std::string> stops;                     
    std::vector<std::string> assignedVehicleRegNumbers; 

public:

    Route(std::string rId, std::string desc, const std::vector<std::string> &rStops, const std::vector<std::string> &assignedVehicles);
    
    ~Route();

    // Методи для отримання значень полів 
    std::string getId() const;
    std::string getDescription() const;
    std::vector<std::string> getStops() const;
    std::vector<std::string> getAssignedVehicleRegNumbers() const;

    // Методи для встановлення значень полів 
    void setId(const std::string &rId);
    void setDescription(const std::string &desc);
    void setStops(const std::vector<std::string> &rStops);
    void setAssignedVehicleRegNumbers(const std::vector<std::string> &assignedVehicles);

    // Методи для ...
    void addAssignedVehicle(const std::string &regNumber);    // Додавання авто до маршруту
    void removeAssignedVehicle(const std::string &regNumber); // Видалення авто з маршруту

    // Метод для інфи про маршрут 
    void displayInfo() const;
    // Метод для генерації рядка для запису у файл
    std::string toFileString() const;
};

#endif 