#ifndef AIS_SYSTEM_HPP 
#define AIS_SYSTEM_HPP

#include <fstream>   
#include <vector>     
#include <string>    
#include <map>       
#include <functional> 
#include <algorithm>  
#include <iostream>   
#include <iomanip>    
#include <limits>     

#include "Vehicle.hpp"
#include "PassengerVehicle.hpp"
#include "CargoVehicle.hpp"
#include "AuxiliaryVehicle.hpp"
#include "Employee.hpp"
#include "Driver.hpp"
#include "MaintenanceStaff.hpp"
#include "Brigade.hpp"
#include "Route.hpp"
#include "Repair.hpp"
#include "Garage.hpp"

class AIS_System {
private:
    // Приватні поля класу
    // Вектори для зберігання вказівників на обєкти різних типів
    // Використання вказівників дозволяє реалізувати поліморфізм
    // Наприклад зберігати PassengerVehicle та CargoVehicle в одному векторі
    std::vector<Vehicle *> allVehicles;  
    std::vector<Employee *> allEmployees; 
    std::vector<Brigade *> allBrigades;  
    std::vector<Route *> allRoutes;      
    std::vector<Repair *> allRepairs;  
    std::vector<Garage *> allGarages;    

    // Константи зберігають імена файлів для збереження та завантаження даних
    // Дані будуть зберігатися у папці data
    const std::string vehiclesFile = "data/vehicles.txt";
    const std::string employeesFile = "data/employees.txt";
    const std::string brigadesFile = "data/brigades.txt";
    const std::string routesFile = "data/routes.txt";
    const std::string repairsFile = "data/repairs.txt";
    const std::string garagesFile = "data/garages.txt";
    const std::string passengerFlowFile = "data/passenger_flow.txt"; 

    // Методи для завантаження даних з файлів
    void loadData();      
    void loadVehicles();  
    void loadEmployees(); 
    void loadBrigades();  
    void loadRoutes();    
    void loadRepairs();   
    void loadGarages();  

    // Метод для збереження всіх даних у файли
    void saveData();

    // Шаблонний метод для збереження списку сутностей у файл
    // Дозволяє уникнути дублювання коду для збереження різних типів сутностей
    template <typename T>
    void saveEntitiesToFile(const std::vector<T *> &entities, const std::string &filename);

    // Методи для відображення різних меню користувачеві
    void displayMainMenu();   
    void displayDataMenu();   
    void editEntityMenu();      
    void analysisReportsMenu(); 
    void findEntityMenu();      

    // Методи для обробки вибору користувача в меню
    void processMainMenuChoice(int choice);
    void processDisplayDataChoice(int choice);
    void processEditEntityChoice(int choice);
    void processAnalysisReportsChoice(int choice);
    void processFindEntityChoice(int choice);

    // Методи для відображення списків сутностей
    void displayAllVehicles() const;
    void displayAllEmployees() const;
    void displayDrivers() const;         
    void displayMaintenanceStaff() const; 
    void displayAllBrigades() const;
    void displayAllRoutes() const;
    void displayAllRepairs() const;
    void displayAllGarages() const;

    // Методи для додавання нових сутностей
    void addVehicle();
    void addEmployee();
    void addDriver();
    void addMaintenanceStaff();
    void addBrigade();
    void addRoute();
    void addRepair();
    void addGarage();

    // Методи для видалення сутностей
    void deleteVehicle();
    void deleteEmployee();
    void deleteBrigade();
    void deleteRoute();
    void deleteRepair();
    void deleteGarage();

    // Шаблонний метод для видалення сутності з вектора за її ID 
    template <typename T, typename U>
    void deleteEntityFromVector(std::vector<T *> &vec, const U &id, const std::string &entityTypeForMessages, std::function<U(const T *)> getIdFunc);

    // Методи для аналітики та звітів
    void performPassengerFlowAnalysis();          
    void calculateRepairCostSummary() const;       
    void displayVehicleMileageMenu();              
    void displayAllVehicleMileages() const;        
    void displayVehicleMileagesByClass() const;    
    void displayVehicleMileageByRegNumber() const; 
    void displayBrigadeWorkload() const;          

    // Методи для пошуку конкретних сутностей за їх ID або номером
    void findVehicleByRegNumber() const;                            
    Vehicle *getVehicleByRegNumber(const std::string &regNum) const; 

    void findEmployeeById() const;                           
    Employee *getEmployeeById(const std::string &empId) const; 

    void findRouteById() const;                            
    Route *getRouteById(const std::string &routeId) const; 

    void findBrigadeById() const;                               
    Brigade *getBrigadeById(const std::string &brigadeId) const;

    void findRepairById() const;                              
    Repair *getRepairById(const std::string &repairId) const; 

    void findGarageById() const;                             
    Garage *getGarageById(const std::string &garageId) const; 

    // Метод для перевірки існування папки data 
    void ensureDataDirectoryExists();

    // Методи для перевірки унікальності ID перед додаванням нових сутностей
    bool isRegNumberUnique(const std::string &regNum) const;
    bool isEmployeeIdUnique(const std::string &empId) const;
    bool isBrigadeIdUnique(const std::string &brigadeId) const;
    bool isRouteIdUnique(const std::string &routeId) const;
    bool isRepairIdUnique(const std::string &repairId) const;
    bool isGarageIdUnique(const std::string &garageId) const;

public:
    AIS_System();

    ~AIS_System();

    void run();
};

// Шаблонний метод для збереження сутностей у файл
template <typename T>
void AIS_System::saveEntitiesToFile(const std::vector<T *> &entities, const std::string &filename) {
    std::ofstream file(filename, std::ios::trunc);
    if (!file.is_open()) {                                                                                  
        std::cerr << "Error: Failed to open file for writing: " << filename << std::endl; 
        return; }

    // Проходимо по всіх сутностях у векторі
    for (const auto *entity : entities) {
        file << entity->toFileString() << std::endl; }
        file.close(); }

// Шаблонний метод для видалення сутності з вектора
template <typename T, typename U>
void AIS_System::deleteEntityFromVector(std::vector<T *> &vec, const U &id, const std::string &entityTypeForMessages, std::function<U(const T *)> getIdFunc)
{
    auto it = std::find_if(vec.begin(), vec.end(), [&](T *entity)
                           { return getIdFunc(entity) == id; });

    if (it != vec.end()) {                                                                                             
        delete *it;                                                                                   
        vec.erase(it);                                                                              
        std::cout << entityTypeForMessages << " with ID/number '" << id << "' successfully deleted.\n"; }
    else { std::cout << entityTypeForMessages << " with ID/number '" << id << "' not found.\n"; } }

#endif 