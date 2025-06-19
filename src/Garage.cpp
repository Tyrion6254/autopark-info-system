#include "../include/Garage.hpp" 

Garage::Garage(std::string gId, std::string gName)
: id(gId), name(gName) {}

Garage::~Garage() {}

// Метод для отримання ID гаража
std::string Garage::getId() const { return id; }

// Метод для отримання назви/адреси гаража
std::string Garage::getName() const { return name; }

// Метод для встановлення ID гаража
void Garage::setId(const std::string &gId) { id = gId; }

// Метод для встановлення назви/адреси гаража
void Garage::setName(const std::string &gName) { name = gName; }

// Метод для відображення інформації про гараж
void Garage::displayInfo() const {
    std::cout << "Garage ID: " << id << std::endl;    
    std::cout << "  Name/Address: " << name << std::endl; 
}

// Метод для генерації рядка для запису у файл
std::string Garage::toFileString() const {return id + ";" + name;}