#include "../include/AIS_System.hpp"
#include "../include/Utils.hpp"
#include <iostream>

// #basic
AIS_System::AIS_System() {
    ensureDataDirectoryExists();
    loadData(); }

AIS_System::~AIS_System() {
    for (Vehicle *v : allVehicles)
        delete v;
    allVehicles.clear();
    for (Employee *e : allEmployees)
        delete e;
    allEmployees.clear();
    for (Brigade *b : allBrigades)
        delete b;
    allBrigades.clear();
    for (Route *r : allRoutes)
        delete r;
    allRoutes.clear();
    for (Repair *rp : allRepairs)
        delete rp;
    allRepairs.clear();
    for (Garage *g : allGarages)
        delete g;
    allGarages.clear();
    std::cout << "\nSystem shutdown complete\n"; }

void AIS_System::run() {
    int choice;
    do {
        displayMainMenu();
        choice = getValidatedIntInput("Your choice: ", 0, 4);
        processMainMenuChoice(choice); }
    while (choice != 0); }

void AIS_System::ensureDataDirectoryExists() {}
void AIS_System::loadData() {
    loadVehicles();
    loadEmployees();
    loadBrigades();
    loadRoutes();
    loadRepairs();
    loadGarages(); }

// Завантаження даних з файлу vehicles.txt
void AIS_System::loadVehicles() {
    std::ifstream file(vehiclesFile);
    std::string line;

    if (!file.is_open()) { std::cerr << "Warning: Could not open file " << vehiclesFile << ". Vehicle list will be empty.\n"; return;}

    while (getline(file, line)) {
        if (line.empty()) continue;
        std::vector<std::string> parts = splitString(line, ';');

        // v: ТипАвто; РегНомер; Марка; Модель; Рік; Пробіг; СпецифічнеПоле (7)
        if (parts.size() < 7) { std::cerr << "Warning: Incorrect line in file " << vehiclesFile << ": " << line << std::endl; continue;}

        try {
            std::string type = parts[0];       // Тип авто (P, C, A)
            std::string regNum = parts[1];
            std::string brand_v = parts[2];
            std::string model_v = parts[3];
            int year = std::stoi(parts[4]);
            double mileage = std::stod(parts[5]);

            // type
            if (type == "P") { int capacity = std::stoi(parts[6]); // Місткість
            allVehicles.push_back(new PassengerVehicle(regNum, brand_v, model_v, year, mileage, capacity));}
            else if (type == "C") { double cargoCap = std::stod(parts[6]); // Вантажопідйомність
            allVehicles.push_back(new CargoVehicle(regNum, brand_v, model_v, year, mileage, cargoCap));}
            else if (type == "A") { std::string purpose_val = parts[6]; // Призначення
            allVehicles.push_back(new AuxiliaryVehicle(regNum, brand_v, model_v, year, mileage, purpose_val));}
            else { std::cerr << "Warning: Unknown vehicle type or insufficient data in " << vehiclesFile << ": " << line << std::endl; } }
        
        catch (const std::exception &e) { std::cerr << "Error converting data in " << vehiclesFile << ": " << line << " - " << e.what() << std::endl; } }
file.close(); }

// Завантаження даних з файлу employees.txt
void AIS_System::loadEmployees() {
    std::ifstream file(employeesFile);
    std::string line;

    if (!file.is_open()) { std::cerr << "Warning: Could not open file " << employeesFile << ". Employee list will be empty.\n"; return; }

    while (getline(file, line)) {
        if (line.empty()) continue;
        std::vector<std::string> parts = splitString(line, ';');

        // e
        // M: Тип; ID; Ім'я; Досвід; Спеціалізація (5)
        // D: Тип; ID; Ім'я; Досвід; Категорії; авто (6)
        if (parts.size() < 5) { std::cerr << "Warning: Incorrect line in file " << employeesFile << ": " << line << std::endl; continue; }

        try {
            std::string type = parts[0]; // Тип працівника (D, M)
            std::string id = parts[1];
            std::string name = parts[2];
            int experience = std::stoi(parts[3]);

            if (type == "D" && parts.size() >= 6) {
                std::vector<std::string> categories = splitString(parts[4], ',');
                std::vector<std::string> vehicles_data = splitString(parts[5], ',');
                allEmployees.push_back(new Driver(id, name, experience, categories, vehicles_data)); }

            else if (type == "M" && parts.size() >= 5) {
                std::string specialization = parts[4];
                allEmployees.push_back(new MaintenanceStaff(id, name, experience, specialization)); }

            else { std::cerr << "Warning: Unknown employee type or insufficient data in " << employeesFile << ": " << line << std::endl; } }

        catch (const std::exception &e) { std::cerr << "Error converting data in " << employeesFile << ": " << line << " - " << e.what() << std::endl; } }
file.close(); }

// Завантаження даних з файлу brigades.txt
void AIS_System::loadBrigades() {
    std::ifstream file(brigadesFile);
    std::string line;

    if (!file.is_open()) { std::cerr << "Warning: Could not open file " << brigadesFile << ". Brigade list will be empty.\n"; return; }

    while (getline(file, line)) {
        if (line.empty()) continue;
        std::vector<std::string> parts = splitString(line, ';');

        // b: ID; Назва; ID_Бригадира (3)
        if (parts.size() == 3) { allBrigades.push_back(new Brigade(parts[0], parts[1], parts[2])); }
        else { std::cerr << "Warning: Incorrect line in file " << brigadesFile << ": " << line << std::endl; } }
file.close(); }

// Завантаження даних з файлу routes.txt
void AIS_System::loadRoutes() {
    std::ifstream file(routesFile);
    std::string line;

    if (!file.is_open()) { std::cerr << "Warning: Could not open file " << routesFile << ". Route list will be empty.\n"; return; }

    while (getline(file, line)) { if (line.empty()) continue;
        std::vector<std::string> parts = splitString(line, ';');

        // r: ID; Опис; Зупинки; Авто (4)
        if (parts.size() == 4) {
            std::vector<std::string> stops = splitString(parts[2], ',');
            std::vector<std::string> vehicles_data = splitString(parts[3], ',');
            allRoutes.push_back(new Route(parts[0], parts[1], stops, vehicles_data)); }

        else { std::cerr << "Warning: Incorrect line in file " << routesFile << ": " << line << std::endl; }}

file.close(); }

// Завантаження даних з файлу repairs.txt
void AIS_System::loadRepairs() {
    std::ifstream file(repairsFile);
    std::string line;

    if (!file.is_open()) { std::cerr << "Warning: Could not open file " << repairsFile << ". Repair list will be empty.\n"; return; }

    while (getline(file, line)) {
        if (line.empty()) continue;
        std::vector<std::string> parts = splitString(line, ';');

        // rp: ID; Номер_авто; Дата; Опис; Вартість; ID_Бригади (6)
        if (parts.size() == 6) {
            try { double cost = std::stod(parts[4]);
            allRepairs.push_back(new Repair(parts[0], parts[1], parts[2], parts[3], cost, parts[5])); }
            catch (const std::exception &e) { std::cerr << "Error converting cost in " << repairsFile << ": " << line << " - " << e.what() << std::endl; } }
        else { std::cerr << "Warning: Incorrect line in file " << repairsFile << ": " << line << std::endl; } }
file.close(); 
}

// Завантаження даних з файлу garages.txt
void AIS_System::loadGarages() {
    std::ifstream file(garagesFile);
    std::string line;

    if (!file.is_open()) { std::cerr << "Warning: Could not open file " << garagesFile << ". Garage list will be empty.\n"; return; }

    while (getline(file, line)) {
        if (line.empty()) continue;
        std::vector<std::string> parts = splitString(line, ';');

        // g: ID; Назва/Адреса (2)
        if (parts.size() == 2) { allGarages.push_back(new Garage(parts[0], parts[1])); }
        else { std::cerr << "Warning: Incorrect line in file " << garagesFile << ": " << line << std::endl; } }
file.close(); 
}

// Збереження всіх даних у їх файли
void AIS_System::saveData() {
    std::cout << "Saving data to files...\n";
    saveEntitiesToFile(allVehicles, vehiclesFile);
    saveEntitiesToFile(allEmployees, employeesFile);
    saveEntitiesToFile(allBrigades, brigadesFile);
    saveEntitiesToFile(allRoutes, routesFile);
    saveEntitiesToFile(allRepairs, repairsFile);
    saveEntitiesToFile(allGarages, garagesFile);
    std::cout << "Data successfully saved.\n"; 
}

// Меню системи - Відображення
void AIS_System::displayMainMenu() {
    std::cout << "\n============ Main Menu ============\n";
    std::cout << "1. Show data\n";
    std::cout << "2. Edit data (add/delete)\n";
    std::cout << "3. Analysis and reports\n";
    std::cout << "4. Find entity by ID/Number\n";
    std::cout << "0. Exit\n";
    std::cout << "===================================\n"; 
}

// Меню системи - Обробка
void AIS_System::processMainMenuChoice(int choice) {
    switch (choice) {
    case 1:
        displayDataMenu();
        break;
    case 2:
        editEntityMenu();
        break;
    case 3:
        analysisReportsMenu();
        break;
    case 4:
        findEntityMenu();
        break;
    case 0:
        std::cout << "Exiting program...\n";
        break;
    default:
        std::cout << "Invalid choice. Try again.\n";
        break;
} }

// Меню перегляду даних - Відображення
void AIS_System::displayDataMenu() {
    int choice;
    do {
        std::cout << "\n============ Show Data ============\n";
        std::cout << "1. All vehicles\n";
        std::cout << "2. All employees\n";
        std::cout << "3. Drivers only\n";
        std::cout << "4. Maintenance staff only\n";
        std::cout << "5. All routes\n";
        std::cout << "6. All brigades\n";
        std::cout << "7. All repairs\n";
        std::cout << "8. All garages\n";
        std::cout << "0. Return to main menu\n";
        std::cout << "===================================\n";
        choice = getValidatedIntInput("Your choice: ", 0, 8);
        processDisplayDataChoice(choice); }
while (choice != 0); }

// Меню перегляду даних - Обробка
void AIS_System::processDisplayDataChoice(int choice) {
    switch (choice) {
    case 1:
        displayAllVehicles();
        break;
    case 2:
        displayAllEmployees();
        break;
    case 3:
        displayDrivers();
        break;
    case 4:
        displayMaintenanceStaff();
        break;
    case 5:
        displayAllRoutes();
        break;
    case 6:
        displayAllBrigades();
        break;
    case 7:
        displayAllRepairs();
        break;
    case 8:
        displayAllGarages();
        break;
    case 0:
        break;
    default:
        std::cout << "Invalid choice.\n";
        break;
    }
}

// Меню редагування сутностей - Відображення
void AIS_System::editEntityMenu() {
    int choice;
    do {
        std::cout << "\n============ Edit Data ============\n";
        std::cout << "1.  Add vehicle\n";
        std::cout << "2.  Delete vehicle\n";
        std::cout << "3.  Add employee\n";
        std::cout << "4.  Delete employee\n";
        std::cout << "5.  Add route\n";
        std::cout << "6.  Delete route\n";
        std::cout << "7.  Add brigade\n";
        std::cout << "8.  Delete brigade\n";
        std::cout << "9.  Add repair record\n";
        std::cout << "10. Delete repair record\n";
        std::cout << "11. Add garage\n";
        std::cout << "12. Delete garage\n";
        std::cout << "0.  Return to main menu\n";
        std::cout << "===================================\n";
        choice = getValidatedIntInput("Your choice: ", 0, 12);
        processEditEntityChoice(choice); }
while (choice != 0); }

// Меню редагування сутностей - Обробка
void AIS_System::processEditEntityChoice(int choice) {
    switch (choice) {
    case 1:
        addVehicle();
        break;
    case 2:
        deleteVehicle();
        break;
    case 3:
        addEmployee();
        break;
    case 4:
        deleteEmployee();
        break;
    case 5:
        addRoute();
        break;
    case 6:
        deleteRoute();
        break;
    case 7:
        addBrigade();
        break;
    case 8:
        deleteBrigade();
        break;
    case 9:
        addRepair();
        break;
    case 10:
        deleteRepair();
        break;
    case 11:
        addGarage();
        break;
    case 12:
        deleteGarage();
        break;
    case 0:
        break;
    default:
        std::cout << "Invalid choice.\n";
        break; }
    if (choice >= 1 && choice <= 12) { saveData(); }
}

// Меню звітів - Відображення
void AIS_System::analysisReportsMenu() {
    int choice;
    do {
        std::cout << "\n============ Analysis and Reports ============\n";
        std::cout << "1. Passenger flow analysis\n";
        std::cout << "2. Total repair cost\n";
        std::cout << "3. Vehicle mileage\n";
        std::cout << "4. Brigade workload\n";
        std::cout << "0. Return to main menu\n";
        std::cout << "==============================================\n";
        choice = getValidatedIntInput("Your choice: ", 0, 4);
        processAnalysisReportsChoice(choice); }
while (choice != 0); }

// Меню звітів - Обробка
void AIS_System::processAnalysisReportsChoice(int choice) {
    switch (choice) {
    case 1:
        performPassengerFlowAnalysis();
        break;
    case 2:
        calculateRepairCostSummary();
        break;
    case 3:
        displayVehicleMileageMenu();
        break;
    case 4:
        displayBrigadeWorkload();
        break;
    case 0:
        break;
    default:
        std::cout << "Invalid choice.\n";
        break;
    }
}

// Меню пошуку сутностей - Відображення
void AIS_System::findEntityMenu() {
    int choice;
    do {
        std::cout << "\n============ Find Entity ============\n";
        std::cout << "1. Find vehicle by registration number\n";
        std::cout << "2. Find employee by ID\n";
        std::cout << "3. Find route by ID\n";
        std::cout << "4. Find brigade by ID\n";
        std::cout << "5. Find repair by ID\n";
        std::cout << "6. Find garage by ID\n";
        std::cout << "0. Return to main menu\n";
        std::cout << "==============================================\n";
        choice = getValidatedIntInput("Your choice: ", 0, 6);
        processFindEntityChoice(choice); }
while (choice != 0); }

// Меню пошуку сутностей - Обробка
void AIS_System::processFindEntityChoice(int choice) {
    switch (choice) {
    case 1:
        findVehicleByRegNumber();
        break;
    case 2:
        findEmployeeById();
        break;
    case 3:
        findRouteById();
        break;
    case 4:
        findBrigadeById();
        break;
    case 5:
        findRepairById();
        break;
    case 6:
        findGarageById();
        break;
    case 0:
        break;
    default:
        std::cout << "Invalid choice.\n";
        break;
    }
}

 // Відображення транспортних засобів
void AIS_System::displayAllVehicles() const {
    std::cout << "\n============= List of All Vehicles =============\n";
    if (allVehicles.empty()) {
        std::cout << "List is empty.\n";
        std::cout << "Total vehicles: 0\n"; 
        return; }
    for (const auto *v : allVehicles) {
        v->displayInfo();
        std::cout << "================================================\n"; }
    std::cout << "Total vehicles: " << allVehicles.size() << std::endl;
}

// Відображення працівників
void AIS_System::displayAllEmployees() const {
    std::cout << "\n=============== List of All Employees ===============\n";
    if (allEmployees.empty()) {
        std::cout << "List is empty.\n";
        std::cout << "Total employees: 0\n"; 
        return; }
    for (const auto *e : allEmployees) {
        e->displayInfo();
        std::cout << "=====================================================\n"; }
    std::cout << "Total employees: " << allEmployees.size() << std::endl;
}

// Відображення водіїв
void AIS_System::displayDrivers() const {
    std::cout << "\n================= List of Drivers =================\n";
    bool found = false;
    long driverCount = 0; 
    for (const auto *e : allEmployees) {
        if (dynamic_cast<const Driver *>(e)) {
            if (!found) { 
                e->displayInfo();
                std::cout << "====================================================\n"; } 
                else { e->displayInfo();
                 std::cout << "====================================================\n"; }
            found = true;
            driverCount++; } }
    if (!found) { std::cout << "Drivers not found or list is empty.\n"; }
   
    std::cout << "Total drivers: " << driverCount << std::endl; }

// Відображення персоналу
void AIS_System::displayMaintenanceStaff() const {
    std::cout << "\n========== List of Maintenance Staff ==========\n";
    bool found = false;
    long staffCount = 0; 
    for (const auto *e : allEmployees) {
        if (dynamic_cast<const MaintenanceStaff *>(e)) {
            if (!found) { e->displayInfo();
                std::cout << "===============================================\n"; }
                else { e->displayInfo();
                std::cout << "===============================================\n"; }
            found = true;
            staffCount++; } }
    if (!found) { std::cout << "Maintenance staff not found or list is empty.\n"; }
    std::cout << "Total maintenance staff: " << staffCount << std::endl; }

// Відображення бригад
void AIS_System::displayAllBrigades() const {
    std::cout << "\n========== List of All Brigades ==========\n";
    if (allBrigades.empty()) {
        std::cout << "List is empty.\n";
        std::cout << "Total brigades: 0\n"; 
        return; }
    for (const auto *b : allBrigades) { b->displayInfo();
        std::cout << "==========================================\n"; }
    std::cout << "Total brigades: " << allBrigades.size() << std::endl; }

// Відображення маршрутів
void AIS_System::displayAllRoutes() const {
    std::cout << "\n============================ List of All Routes ============================\n";
    if (allRoutes.empty()) {
        std::cout << "List is empty.\n";
        std::cout << "Total routes: 0\n"; 
        return; }
    for (const auto *r : allRoutes) { r->displayInfo();
    std::cout << "============================================================================\n"; }
    std::cout << "Total routes: " << allRoutes.size() << std::endl; }

// Відображення ремонтів
void AIS_System::displayAllRepairs() const {
    std::cout << "\n============== List of All Repairs ==============\n";
    if (allRepairs.empty()) {
        std::cout << "List is empty.\n";
        std::cout << "Total repairs: 0\n";
        return; }
    for (const auto *rp : allRepairs) { rp->displayInfo();
        std::cout << "=================================================\n"; }
    std::cout << "Total repairs: " << allRepairs.size() << std::endl; }

// Відображення гаражів
void AIS_System::displayAllGarages() const {
    std::cout << "\n=============== List of All Garages ===============\n";
    if (allGarages.empty()) {
        std::cout << "List is empty.\n";
        std::cout << "Total garages: 0\n"; 
        return; }
    for (const auto *g : allGarages) {
        g->displayInfo();
        std::cout << "===================================================\n"; }
    std::cout << "Total garages: " << allGarages.size() << std::endl; }

// Перевірка унікальності номера авто
bool AIS_System::isRegNumberUnique(const std::string &regNum) const {
    return std::find_if(allVehicles.begin(), allVehicles.end(),
                        [&](Vehicle *v)
                        { return v->getRegNumber() == regNum; }) == allVehicles.end(); }

// Перевірка унікальності ID працівника
bool AIS_System::isEmployeeIdUnique(const std::string &empId) const {
    return std::find_if(allEmployees.begin(), allEmployees.end(),
                        [&](Employee *e)
                        { return e->getId() == empId; }) == allEmployees.end(); }

// Перевірка унікальності ID бригади
bool AIS_System::isBrigadeIdUnique(const std::string &bId) const {
    return std::find_if(allBrigades.begin(), allBrigades.end(),
                        [&](Brigade *b)
                        { return b->getId() == bId; }) == allBrigades.end(); }

// Перевірка унікальності ID маршруту
bool AIS_System::isRouteIdUnique(const std::string &rId) const {
    return std::find_if(allRoutes.begin(), allRoutes.end(),
                        [&](Route *r)
                        { return r->getId() == rId; }) == allRoutes.end(); }

// Перевірка унікальності ID ремонту
bool AIS_System::isRepairIdUnique(const std::string &rpId) const {
    return std::find_if(allRepairs.begin(), allRepairs.end(),
                        [&](Repair *rp)
                        { return rp->getId() == rpId; }) == allRepairs.end(); }

// Перевірка унікальності ID гаража
bool AIS_System::isGarageIdUnique(const std::string &gId) const {
    return std::find_if(allGarages.begin(), allGarages.end(),
                        [&](Garage *g)
                        { return g->getId() == gId; }) == allGarages.end(); }

// Додавання нового транспортного засобу
void AIS_System::addVehicle() {
    std::cout << "\n============ Adding New Vehicle ============\n";
    std::cout << "Select vehicle type:\n";
    std::cout << "1. Passenger\n";
    std::cout << "2. Cargo\n";
    std::cout << "3. Auxiliary\n";
    std::cout << "===================================================\n"; 
    int typeChoice = getValidatedIntInput("Your type choice: ", 1, 3);

    std::string regNum, brand_v, model_v;
    int year;
    double mileage;

    // Введення номера авто + перевірка на унікальність
    do {
        regNum = getValidatedStringInput("Registration number (AB1234CD): ");
        if (!isRegNumberUnique(regNum)) { std::cout << "Vehicle with this registration number already exists. Try another.\n"; } }
        while (!isRegNumberUnique(regNum));

    // Введення інших загальних даних для авто
    brand_v = getValidatedStringInput("Brand: ");
    model_v = getValidatedStringInput("Model: ");
    year = getValidatedIntInput("Year of manufacture: ", 1886, 2024);
    mileage = getValidatedDoubleInput("Mileage (km): ", 0.0, 10000000.0);

    Vehicle *newVehicle = nullptr;
    switch (typeChoice) {
    case 1: {
        int capacity = getValidatedIntInput("Capacity (passengers): ", 1, 200);
        newVehicle = new PassengerVehicle(regNum, brand_v, model_v, year, mileage, capacity);
        break; }
    case 2: {
        double cargoCap = getValidatedDoubleInput("Cargo capacity (kg): ", 1.0, 100000.0);
        newVehicle = new CargoVehicle(regNum, brand_v, model_v, year, mileage, cargoCap);
        break; }
    case 3: {
        std::string purpose = getValidatedStringInput("Purpose: ");
        newVehicle = new AuxiliaryVehicle(regNum, brand_v, model_v, year, mileage, purpose);
        break; }
    }

    if (newVehicle) { allVehicles.push_back(newVehicle); std::cout << "Vehicle added successfully.\n"; } }

// Додавання нового працівника
void AIS_System::addEmployee() {
    std::cout << "\n============ Adding New Employee ============\n";
    std::cout << "Select employee type:\n";
    std::cout << "1. Driver\n";
    std::cout << "2. Maintenance Staff\n";
    std::cout << "===================================================\n"; 
    int typeChoice = getValidatedIntInput("Your type choice: ", 1, 2);
    if (typeChoice == 1)
        addDriver();
    else if (typeChoice == 2)
        addMaintenanceStaff();
}

// Додавання нового водія
void AIS_System::addDriver() {
    std::string id, name;
    int experience;
    std::vector<std::string> categories, assignedVehiclesRegNums;

    // Введення ID водія + перевірка на унікальність
    do {
        id = getValidatedStringInput("Driver ID (D001): ");
        if (!isEmployeeIdUnique(id)) { std::cout << "Employee with this ID already exists. Try another.\n"; } }
        while (!isEmployeeIdUnique(id));

    name = getValidatedStringInput("Driver's full name: ");
    experience = getValidatedIntInput("Work experience (years): ", 0, 70);

    // Введення категорій прав
    std::string catStr = getValidatedStringInput("License categories (A,B,C): ");
    categories = splitString(catStr, ',');

    // Введення закріплених авто
    std::string vehStr = getValidatedStringInput("Reg numbers of assigned vehicles: ", true);
    if (!vehStr.empty()) { assignedVehiclesRegNums = splitString(vehStr, ','); }

    allEmployees.push_back(new Driver(id, name, experience, categories, assignedVehiclesRegNums));
    std::cout << "Driver added successfully.\n"; }

// Додавання нового працівника обслуговуючого персоналу
void AIS_System::addMaintenanceStaff() {
    std::string id, name, specialization;
    int experience;

    // Введення ID працівника + перевірка на унікальність
    do {
        id = getValidatedStringInput("Employee ID (M001): ");
        if (!isEmployeeIdUnique(id)) { std::cout << "Employee with this ID already exists. Try another.\n"; } } while (!isEmployeeIdUnique(id));

    name = getValidatedStringInput("Employee's name: ");
    experience = getValidatedIntInput("Work experience (years): ", 0, 70);
    specialization = getValidatedStringInput("Specialization: ");

    allEmployees.push_back(new MaintenanceStaff(id, name, experience, specialization));
    std::cout << "Maintenance staff member added successfully.\n"; }

// Додавання нової бригади
void AIS_System::addBrigade() {
    std::cout << "\n============ Adding New Brigade ============\n";
    std::string id, name, foremanId;

    // Введення ID бригади + перевірка на унікальність
    do {
        id = getValidatedStringInput("Brigade ID (B01): ");
        if (!isBrigadeIdUnique(id)) { std::cout << "Brigade with this ID already exists. Try another.\n"; } } while (!isBrigadeIdUnique(id));
    name = getValidatedStringInput("Brigade name: ");

    // Введення ID бригадира + перевірка на існування
    Employee *foreman = nullptr;
    do {
        foremanId = getValidatedStringInput("Foreman ID: ");
        foreman = getEmployeeById(foremanId);
        if (!foreman) { std::cout << "Employee with ID '" << foremanId << "' not found. Try again.\n"; } } while (!foreman);

    allBrigades.push_back(new Brigade(id, name, foremanId));
    std::cout << "Brigade added successfully.\n";
}

// Додавання нового маршруту
void AIS_System::addRoute() {
    std::cout << "\n============ Adding New Route ============\n";
    std::string id, description;
    std::vector<std::string> stops, assignedVehiclesRegNums;

    // Введення ID маршруту + перевірка на унікальність
    do {
        id = getValidatedStringInput("Route ID (R101): ");
        if (!isRouteIdUnique(id)) { std::cout << "Route with this ID already exists. Try another.\n"; } } while (!isRouteIdUnique(id));

    description = getValidatedStringInput("Route description: ");

    // Введення зупинок
    std::string stopsStr = getValidatedStringInput("Stops (Stop1,Stop2): ");
    stops = splitString(stopsStr, ',');

    // Введення закріплених авто
    std::string vehStr = getValidatedStringInput("Reg numbers of assigned vehicles: ", true);
    if (!vehStr.empty()) {
        assignedVehiclesRegNums = splitString(vehStr, ',');
        // Перевірка, чи існують введені авто
        for (const auto &regNum : assignedVehiclesRegNums) {
            if (!getVehicleByRegNumber(regNum))
           { std::cout << "Warning: Vehicle with number '" << regNum << "' not found. It will be added to the list, but the link may be invalid.\n"; } } }
    allRoutes.push_back(new Route(id, description, stops, assignedVehiclesRegNums));
    std::cout << "Route added successfully.\n"; }

// Додавання нового запису про ремонт
void AIS_System::addRepair() {
    std::cout << "\n============ Adding Repair Record ============\n";
    std::string id, vehicleRegNum, date, description_rep, brigadeId;
    double cost;

    // Введення ID ремонту + перевірка на унікальність
    do {
        id = getValidatedStringInput("Repair ID (RP001): ");
        if (!isRepairIdUnique(id)) { std::cout << "Repair record with this ID already exists. Try another.\n"; } } while (!isRepairIdUnique(id));

    // Введення номера авто + перевірка на існування
    Vehicle *vehicle_ptr = nullptr;
    do {
        vehicleRegNum = getValidatedStringInput("Vehicle registration number: ");
        vehicle_ptr = getVehicleByRegNumber(vehicleRegNum);
        if (!vehicle_ptr) { std::cout << "Vehicle with number '" << vehicleRegNum << "' not found. Try again.\n"; } } while (!vehicle_ptr);

    date = getValidatedStringInput("Repair date (DD-MM-YYYY): ");
    description_rep = getValidatedStringInput("Work description: ");
    cost = getValidatedDoubleInput("Repair cost (UAH): ", 0.0, 1000000.0);

    // Введення ID бригади + перевірка на існування
    Brigade *brigade_ptr = nullptr;
    do {
        brigadeId = getValidatedStringInput("Brigade ID: ");
        brigade_ptr = getBrigadeById(brigadeId);
        if (!brigade_ptr) { std::cout << "Brigade with ID '" << brigadeId << "' not found. Try again.\n"; } } while (!brigade_ptr);

    allRepairs.push_back(new Repair(id, vehicleRegNum, date, description_rep, cost, brigadeId));
    std::cout << "Repair record added successfully.\n"; }

// Додавання гаража
void AIS_System::addGarage() {
    std::cout << "\n============ Adding New Garage ============\n";
    std::string id, name;

    // Введення ID гаража + перевірка на існування
    do {
        id = getValidatedStringInput("Garage ID (G01): ");
        if (!isGarageIdUnique(id)) { std::cout << "Garage with this ID already exists. Try another.\n"; } } while (!isGarageIdUnique(id));

    name = getValidatedStringInput("Garage name/address: ");
    allGarages.push_back(new Garage(id, name));
    std::cout << "Garage added successfully.\n"; }

// Видалення транспорту
void AIS_System::deleteVehicle() {
    std::cout << "\n============ Deleting Vehicle ============\n";
    if (allVehicles.empty()) { std::cout << "Vehicle list is empty. Nothing to delete.\n"; return; }
    std::string regNum = getValidatedStringInput("Enter registration number of vehicle to delete: ");

    bool isAssignedToDriver = false;
    for (const auto *emp : allEmployees) { const Driver *driver = dynamic_cast<const Driver *>(emp); 
        if (driver) {
            const auto &assignedVehs = driver->getAssignedVehicleRegNumbers();
            if (std::find(assignedVehs.begin(), assignedVehs.end(), regNum) != assignedVehs.end()) { isAssignedToDriver = true; 
                break; 
        } } }
    bool isAssignedToRoute = false;
    for (const auto *route : allRoutes) { const auto &assignedVehs = route->getAssignedVehicleRegNumbers();
        if (std::find(assignedVehs.begin(), assignedVehs.end(), regNum) != assignedVehs.end()) {
            isAssignedToRoute = true;
            break; } }

    if (isAssignedToDriver || isAssignedToRoute) {
        std::cout << "WARNING: Vehicle " << regNum << " is assigned to a driver and/or route.\n"; 
        std::string confirm = getValidatedStringInput("Delete vehicle anyway? (yes/no): ");      
        if (toLower(confirm) != "yes") { std::cout << "Deletion cancelled.\n"; return; }
        for (auto *emp : allEmployees) { Driver *driver = dynamic_cast<Driver *>(emp); 
        if (driver) driver->removeAssignedVehicle(regNum); // Метод видалення авто з водія
}
        for (auto *route : allRoutes) { 
        route->removeAssignedVehicle(regNum); // Метод видалення авто з маршруту
        } }

    deleteEntityFromVector<Vehicle, std::string>(allVehicles, regNum, "Vehicle", 
                                                 [](const Vehicle *v)
                                                 { return v->getRegNumber(); });
}

// Видалення працівника
void AIS_System::deleteEmployee()
{
    std::cout << "\n============ Deleting Employee ============\n"; 
    if (allEmployees.empty()) { std::cout << "Employee list is empty.\n"; return; }
    std::string empId = getValidatedStringInput("Enter ID of employee to delete: "); 

    for (const auto *brigade : allBrigades) {
    if (brigade->getForemanId() == empId)
        {
            std::cout << "Error: Employee " << empId << " is the foreman of brigade " << brigade->getId() << ".\n"; 
            std::cout << "First change the foreman in this brigade or delete the brigade.\n";                      
            return;                                                                                                
        }
    }

    deleteEntityFromVector<Employee, std::string>(allEmployees, empId, "Employee", 
                                                  [](const Employee *e)
                                                  { return e->getId(); });
}

// Видалення бригади
void AIS_System::deleteBrigade() {
    std::cout << "\n============ Deleting Brigade ============\n"; 
    if (allBrigades.empty()) { std::cout << "Brigade list is empty.\n"; return; }
    std::string brigadeId = getValidatedStringInput("Enter ID of brigade to delete: "); 

    for (const auto *repair : allRepairs) {
        if (repair->getBrigadeId() == brigadeId)
        {
            std::cout << "Error: Brigade " << brigadeId << " is involved in repair " << repair->getId() << ".\n"; 
            std::cout << "First delete or change the corresponding repair records.\n";                            
            return; 
        }
    }
    deleteEntityFromVector<Brigade, std::string>(allBrigades, brigadeId, "Brigade", 
                                                 [](const Brigade *b)
                                                 { return b->getId(); });
}

// Видалення маршруту
void AIS_System::deleteRoute() {
    std::cout << "\n============ Deleting Route ============\n"; 
    if (allRoutes.empty()) {
        std::cout << "Route list is empty.\n";
        return; }
    std::string routeId = getValidatedStringInput("Enter ID of route to delete: "); 
    deleteEntityFromVector<Route, std::string>(allRoutes, routeId, "Route",         
                                               [](const Route *r)
                                               { return r->getId(); });
}

// Видалення запису про ремонт
void AIS_System::deleteRepair() {
    std::cout << "\n============ Deleting Repair Record ============\n"; 
    if (allRepairs.empty()) { std::cout << "Repair list is empty.\n";  return; }
    std::string repairId = getValidatedStringInput("Enter ID of repair record to delete: "); 
    deleteEntityFromVector<Repair, std::string>(allRepairs, repairId, "Repair record",       
                                                [](const Repair *rp)
                                                { return rp->getId(); });
}

// Видалення гаража
void AIS_System::deleteGarage() {
    std::cout << "\n============ Deleting Garage ============\n"; 
    if (allGarages.empty()) { std::cout << "Garage list is empty.\n"; return; }
    std::string garageId = getValidatedStringInput("Enter ID of garage to delete: "); 
    deleteEntityFromVector<Garage, std::string>(allGarages, garageId, "Garage",      
                                                [](const Garage *g)
                                                { return g->getId(); });
}

// Аналіз пасажиропотоку
void AIS_System::performPassengerFlowAnalysis() {
    std::cout << "\n================================= Passenger Flow Analysis =================================\n"; 
    std::ifstream flowFile(passengerFlowFile);          // passenger_flow.txt
    if (!flowFile.is_open()) {
        std::cerr << "Error: Could not open passenger flow file: " << passengerFlowFile << std::endl;                     
        std::cerr << "Create file " << passengerFlowFile << " in 'data' folder in format: route_ID;number_of_passengers\n"; 
        std::cerr << "Example:\nR101;1500\nR102;800\n";                                                                    
        return;
    }

    std::map<std::string, int> routePassengerCounts;
    std::string line;
    while (getline(flowFile, line)) {
        if (line.empty()) continue;
        std::vector<std::string> parts = splitString(line, ';');
        if (parts.size() == 2) { try
        { routePassengerCounts[parts[0]] = std::stoi(parts[1]); }
            catch (const std::exception &e) { std::cerr << "Error reading passenger flow data: " << line << " - " << e.what() << std::endl; } } }
    flowFile.close();

    if (routePassengerCounts.empty()) { std::cout << "Passenger flow data is missing or could not be read.\n"; return; }

    // Виведення таблиці 
    std::cout << std::left                              
              << std::setw(10) << "Route ID"             
              << std::setw(30) << "Route Description"    
              << std::setw(15) << "Passengers"          
              << std::setw(15) << "Veh. Capacity"       
              << std::setw(20) << "Status" << std::endl; 
    std::cout << std::string(91, '-') << std::endl;      

    // Обробка кожного маршруту з файлу пасажиропотоку
    for (const auto &pair : routePassengerCounts) {
        const std::string &routeId = pair.first; 
        int passengerCount = pair.second;       
        Route *route = getRouteById(routeId);    

        if (!route) { 
            std::cout << std::left << std::setw(10) << routeId
                      << std::setw(30) << "N/A (route not found)" 
                      << std::setw(15) << passengerCount
                      << std::setw(15) << "N/A"              
                      << std::setw(20) << "N/A" << std::endl; 
            continue;                                        
        }

        // Розрахунок загальної місткості пасажирських авто на цьому маршруті
        int totalCapacityOnRoute = 0;
        for (const std::string &regNum : route->getAssignedVehicleRegNumbers()) {
            Vehicle *veh = getVehicleByRegNumber(regNum); 
            if (veh) {
                if (PassengerVehicle *pVeh = dynamic_cast<PassengerVehicle *>(veh))
                { totalCapacityOnRoute += pVeh->getCapacity(); } } }

        // Визначення статусу завантаженості маршруту
        std::string status;
        if (totalCapacityOnRoute == 0 && passengerCount > 0)
        { status = "No pass. vehicles!"; }
        else if (totalCapacityOnRoute == 0 && passengerCount == 0)
        { status = "No data"; }
        else if (passengerCount > totalCapacityOnRoute * 1.1)
        { status = "Overloaded!"; }
        else if (passengerCount < totalCapacityOnRoute * 0.7)
        { status = "Underloaded"; }
        else { status = "Balanced"; }

        // Виведення інформації про маршрут
        std::cout << std::left << std::setw(10) << route->getId()
                  << std::setw(30) << route->getDescription().substr(0, 28) 
                  << std::setw(15) << passengerCount
                  << std::setw(15) << totalCapacityOnRoute
                  << std::setw(20) << status << std::endl; }
    std::cout << std::string(90, '-') << std::endl;
    std::cout << "Recommendations:\n";                                                                                 
    std::cout << "- For overloaded routes: consider adding vehicles or vehicles with higher capacity.\n";              
    std::cout << "- For underloaded routes: consider reallocating vehicles to other routes or changing the schedule.\n"; 
}

// Розрахунок загальної вартості всіх ремонтів
void AIS_System::calculateRepairCostSummary() const {
    std::cout << "\n============ Total Repair Cost ============\n"; 
    if (allRepairs.empty()) { std::cout << "No repair records found.\n"; return; }
    double totalCost = 0;
    for (const auto *repair : allRepairs) { totalCost += repair->getCost(); }
    std::cout << "Total cost of all repairs: "                               
              << std::fixed << std::setprecision(2) << totalCost << " UAH\n"; }

// Меню для відображення інформації про пробіг авто
void AIS_System::displayVehicleMileageMenu() {
    int choice;
    do {
        std::cout << "\n============ Vehicle Mileage ============\n";          
        std::cout << "1. Mileage of all vehicles\n";         
        std::cout << "2. Mileage by vehicle class\n";        
        std::cout << "3. Mileage by registration number\n";   
        std::cout << "0. Return to analytics menu\n";         
        choice = getValidatedIntInput("Your choice: ", 0, 3); 
        switch (choice) {
        case 1:
            displayAllVehicleMileages();
            break;
        case 2:
            displayVehicleMileagesByClass();
            break;
        case 3:
            displayVehicleMileageByRegNumber();
            break;
        case 0:
            break; 
        default:
            std::cout << "Invalid choice.\n";
            break; } }
while (choice != 0); }

// Відображення пробігу всіх авто
void AIS_System::displayAllVehicleMileages() const {
    std::cout << "\n====================== Mileage of All Vehicles ======================\n"; 
    if (allVehicles.empty()) { std::cout << "Vehicle list is empty.\n"; return; }
    // Заголовки таблиці
    std::cout << std::left << std::setw(15) << "Reg.Number"    
              << std::setw(20) << "Brand"                      
              << std::setw(20) << "Model"                      
              << std::setw(15) << "Mileage (km)" << std::endl; 
    std::cout << std::string(70, '-') << std::endl;
    for (const auto *v : allVehicles) {
        std::cout << std::left << std::setw(15) << v->getRegNumber()
                  << std::setw(20) << v->getBrand()
                  << std::setw(20) << v->getModel()
                  << std::fixed << std::setprecision(1) << std::setw(15) << v->getMileage() << std::endl; }
    std::cout << std::string(70, '-') << std::endl; }

// Відображення пробігу авто за обраним класом
void AIS_System::displayVehicleMileagesByClass() const {
    std::cout << "\n============ Mileage by Vehicle Class ============\n"; 
    if (allVehicles.empty()) { std::cout << "Vehicle list is empty.\n"; return; }
    std::cout << "Select vehicle class:\n";
    std::cout << "1. Passenger\n";          
    std::cout << "2. Cargo\n";              
    std::cout << "3. Auxiliary\n";          
    int classChoice = getValidatedIntInput("Your class choice: ", 1, 3); 

    std::cout << std::left << std::setw(15) << "Reg.Number"    
              << std::setw(20) << "Brand"                     
              << std::setw(20) << "Model"                      
              << std::setw(15) << "Mileage (km)" << std::endl; 
    std::cout << std::string(70, '-') << std::endl;
    bool found = false; 

    for (const auto *v : allVehicles) {
        bool match = false; 
        if (classChoice == 1 && dynamic_cast<const PassengerVehicle *>(v))
            match = true;
        else if (classChoice == 2 && dynamic_cast<const CargoVehicle *>(v))
            match = true;
        else if (classChoice == 3 && dynamic_cast<const AuxiliaryVehicle *>(v))
            match = true;
    
        if (match) { 
            found = true;
            std::cout << std::left << std::setw(15) << v->getRegNumber()
                      << std::setw(20) << v->getBrand()
                      << std::setw(20) << v->getModel()
                      << std::fixed << std::setprecision(1) << std::setw(15) << v->getMileage() << std::endl; } }
    if (!found) { std::cout << "Vehicles of selected class not found.\n"; }
    std::cout << std::string(70, '-') << std::endl; }

// Відображення пробігу конкретного авто за його реєстраційним номером
void AIS_System::displayVehicleMileageByRegNumber() const {
    std::cout << "\n=============== Mileage by Registration Number ===============\n"; 
    if (allVehicles.empty()) { std::cout << "Vehicle list is empty.\n"; return; }
    std::string regNum = getValidatedStringInput("Enter vehicle registration number: "); 
    Vehicle *v = getVehicleByRegNumber(regNum);                                         
    if (v) {
    std::cout << "Mileage for vehicle " << regNum << " (" << v->getBrand() << " " << v->getModel() << "): " 
    << std::fixed << std::setprecision(1) << v->getMileage() << " km\n"; }
    else { std::cout << "Vehicle with number '" << regNum << "' not found.\n"; }
}

// Відображення навантаження на бригади 
void AIS_System::displayBrigadeWorkload() const {
    std::cout << "\n=============== Brigade Workload ===============\n"; 
    if (allBrigades.empty())
    { std::cout << "Brigade list is empty.\n"; return; }
    if (allRepairs.empty()) { std::cout << "No repair records found, cannot calculate workload.\n"; return; }

    std::map<std::string, int> brigadeRepairCounts;
    for (const auto *brigade : allBrigades)
    { brigadeRepairCounts[brigade->getId()] = 0; }
    for (const auto *repair : allRepairs) { brigadeRepairCounts[repair->getBrigadeId()]++; }

    // Виведення таблиці навантаження
    std::cout << std::left << std::setw(10) << "Brig. ID"     
              << std::setw(25) << "Brigade Name"              
              << std::setw(15) << "No. Repairs" << std::endl; 
    std::cout << std::string(50, '-') << std::endl;

    for (const auto &pair : brigadeRepairCounts) {
        Brigade *brigade = getBrigadeById(pair.first); 
        std::string brigadeName = brigade ? brigade->getName() : "N/A (brigade deleted?)"; 
        std::cout << std::left << std::setw(10) << pair.first                              
                  << std::setw(25) << brigadeName                                         
                  << std::setw(15) << pair.second                                         
                  << std::endl; }
    std::cout << std::string(50, '-') << std::endl; }

// Допоміжні методи для пошуку сутностей. Повертають вказівник
Vehicle *AIS_System::getVehicleByRegNumber(const std::string &regNum) const {
    for (Vehicle *v : allVehicles) { if (v->getRegNumber() == regNum) return v; }
    return nullptr; }

Employee *AIS_System::getEmployeeById(const std::string &empId) const {
    for (Employee *e : allEmployees) { if (e->getId() == empId) return e; }
    return nullptr; }

Route *AIS_System::getRouteById(const std::string &routeId) const {
    for (Route *r : allRoutes) { if (r->getId() == routeId) return r; }
    return nullptr; }

Brigade *AIS_System::getBrigadeById(const std::string &brigadeId) const {
    for (Brigade *b : allBrigades) { if (b->getId() == brigadeId) return b; }
    return nullptr; }

Repair *AIS_System::getRepairById(const std::string &repairId) const {
    for (Repair *rp : allRepairs) { if (rp->getId() == repairId) return rp;}
    return nullptr; }

Garage *AIS_System::getGarageById(const std::string &garageId) const {
    for (Garage *g : allGarages) { if (g->getId() == garageId) return g; }
    return nullptr; }

// Методи для пошуку сутностей 
void AIS_System::findVehicleByRegNumber() const {
    std::string regNum = getValidatedStringInput("Enter vehicle registration number to search: "); 
    Vehicle *v = getVehicleByRegNumber(regNum);
    if (v) { std::cout << "\n=============== Vehicle Found ===============\n"; v->displayInfo(); }
    else { std::cout << "Vehicle with number '" << regNum << "' not found.\n"; }
    std::cout << "=============================================\n"; }

void AIS_System::findEmployeeById() const {
    std::string empId = getValidatedStringInput("Enter employee ID to search: "); 
    Employee *e = getEmployeeById(empId);
    if (e) { std::cout << "\n=============== Employee Found ===============\n"; e->displayInfo(); }
    else { std::cout << "Employee with ID '" << empId << "' not found.\n"; } 
    std::cout << "==============================================\n"; }

void AIS_System::findRouteById() const {
    std::string routeId = getValidatedStringInput("Enter route ID to search: ");
    Route *r = getRouteById(routeId);
    if (r) { std::cout << "\n======================= Route Found =======================\n"; r->displayInfo(); }
    else { std::cout << "Route with ID '" << routeId << "' not found.\n"; }
    std::cout << "===========================================================\n"; }

void AIS_System::findBrigadeById() const {
    std::string brigadeId = getValidatedStringInput("Enter brigade ID to search: "); 
    Brigade *b = getBrigadeById(brigadeId);
    if (b) { std::cout << "\n=============== Brigade Found ===============\n"; b->displayInfo(); }
    else { std::cout << "Brigade with ID '" << brigadeId << "' not found.\n"; } 
    std::cout << "===================================================\n"; }

void AIS_System::findRepairById() const {
    std::string repairId = getValidatedStringInput("Enter repair ID to search: "); 
    Repair *rp = getRepairById(repairId);
    if (rp) { std::cout << "\n=============== Repair Record Found ===============\n"; rp->displayInfo(); }
    else { std::cout << "Repair record with ID '" << repairId << "' not found.\n"; }
    std::cout << "===================================================\n"; }

void AIS_System::findGarageById() const {
    std::string garageId = getValidatedStringInput("Enter garage ID to search: "); 
    Garage *g = getGarageById(garageId);
    if (g) { std::cout << "\n================ Garage Found ================\n"; 
    g->displayInfo(); }
    else { std::cout << "Garage with ID '" << garageId << "' not found.\n"; }
    std::cout << "==============================================\n"; }


