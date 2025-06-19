#include "../include/Route.hpp"
#include <algorithm>

Route::Route(std::string rId, std::string desc, const std::vector<std::string> &rStops, const std::vector<std::string> &assignedVehicles)
: id(rId), description(desc), stops(rStops), assignedVehicleRegNumbers(assignedVehicles) {}

Route::~Route() {}

// Метод для отримання ID маршруту
std::string Route::getId() const { return id; }

// Метод для отримання опису маршруту
std::string Route::getDescription() const { return description; }

// Метод для отримання списку зупинок
std::vector<std::string> Route::getStops() const { return stops; }

// Метод для отримання списку номерів закріплених авто
std::vector<std::string> Route::getAssignedVehicleRegNumbers() const { return assignedVehicleRegNumbers; }

// Метод для встановлення ID маршруту
void Route::setId(const std::string &rId) { id = rId; }

// Метод для встановлення опису маршруту
void Route::setDescription(const std::string &desc) { description = desc; }

// Метод для встановлення списку зупинок
void Route::setStops(const std::vector<std::string> &rStops) { stops = rStops; }

// Метод для встановлення списку закріплених авто
void Route::setAssignedVehicleRegNumbers(const std::vector<std::string> &assignedVehicles)
{assignedVehicleRegNumbers = assignedVehicles;}

// Метод для додавання авто до списку закріплених
void Route::addAssignedVehicle(const std::string &regNumber){
// Перевірка на дублювання
if (std::find(assignedVehicleRegNumbers.begin(), assignedVehicleRegNumbers.end(), regNumber) == assignedVehicleRegNumbers.end())
{assignedVehicleRegNumbers.push_back(regNumber);}
}

// Метод для видалення авто з списку закріплених
void Route::removeAssignedVehicle(const std::string &regNumber)
{ assignedVehicleRegNumbers.erase(
std::remove(assignedVehicleRegNumbers.begin(), assignedVehicleRegNumbers.end(), regNumber),
assignedVehicleRegNumbers.end());
}

// Метод для відображення інфи про маршрут
void Route::displayInfo() const {
    std::cout << "Route ID: " << id << std::endl;
    std::cout << "  Description: " << description << std::endl;
    std::cout << "  Stops: " << joinString(stops, ',') << std::endl;
    std::cout << "  Assigned Vehicles: " << joinString(assignedVehicleRegNumbers, ',') << std::endl;
}

// Метод для генерації рядка для запису у файл
std::string Route::toFileString() const
{ return id + ";" +
        description + ";" +
        joinString(stops, ',') + ";" + 
        joinString(assignedVehicleRegNumbers, ',');
}