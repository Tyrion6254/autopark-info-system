#include "../include/Brigade.hpp"

Brigade::Brigade(std::string bId, std::string bName, std::string fId)
: id(bId), name(bName), foremanId(fId) {}

Brigade::~Brigade() {}

// Метод для отримання ID бригади
std::string Brigade::getId() const { return id; }

// Метод для отримання назви бригади
std::string Brigade::getName() const { return name; }

// Метод для отримання ID бригадира
std::string Brigade::getForemanId() const { return foremanId; }

// Метод для встановлення ID бригади
void Brigade::setId(const std::string &bId) { id = bId; }

// Метод для встановлення назви бригади
void Brigade::setName(const std::string &bName) { name = bName; }

// Метод для встановлення ID бригадира
void Brigade::setForemanId(const std::string &fId) { foremanId = fId; }

// Метод для відображення інформації про бригаду на консоль
void Brigade::displayInfo() const {
    std::cout << "Brigade ID: " << id << std::endl;
    std::cout << "  Name: " << name << std::endl;
    std::cout << "  Foreman ID: " << foremanId << std::endl;
}

// Метод для генерації рядка з даними обєкта для запису у файл
std::string Brigade::toFileString() const { return id + ";" + name + ";" + foremanId; }