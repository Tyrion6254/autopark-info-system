#include "../include/Employee.hpp" 

Employee::Employee(std::string empId, std::string empName, int exp)
: id(empId), name(empName), experience(exp) {}

Employee::~Employee() {}

// Метод для отримання ID працівника
std::string Employee::getId() const { return id; }

// Метод для отримання імені працівника
std::string Employee::getName() const { return name; }

// Метод для отримання досвіду роботи працівника
int Employee::getExperience() const { return experience; }

// Метод для встановлення ID працівника
void Employee::setId(const std::string &empId) {id = empId;}

// Метод для встановлення імені працівника
void Employee::setName(const std::string &empName) { name = empName; }

// Метод для встановлення досвіду роботи
void Employee::setExperience(int exp) { experience = exp; }

// Метод для інфи про працівника
void Employee::displayInfo() const {
    std::cout << "  ID: " << id << std::endl;
    std::cout << "  Name: " << name << std::endl;                             
    std::cout << "  Work Experience: " << experience << " years" << std::endl; 
}
