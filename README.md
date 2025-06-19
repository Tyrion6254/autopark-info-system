# AIS Autopark Management System
A C++ console application for managing a vehicle fleet. The system processes data on vehicles, employees, routes, and garages, providing basic analytics. Developed using a modular, object-oriented design in C++11. Future plans include data editing, advanced analytics, and a GUI version.

## Project Structure

-   `data/`: Directory for storing data files (`.txt`).
    -   `vehicles.txt`: Data about vehicles.
    -   `employees.txt`: Data about employees.
    -   `brigades.txt`: Data about brigades.
    -   `routes.txt`: Data about routes.
    -   `repairs.txt`: Data about repairs.
    -   `garages.txt`: Data about garages.
    -   `passenger_flow.txt`: Data for passenger flow analysis.
-   `include/`: Directory for header files (`.hpp`).
    -   `AIS_System.hpp`: The main system class.
    -   `Vehicle.hpp`, `PassengerVehicle.hpp`, `CargoVehicle.hpp`, `AuxiliaryVehicle.hpp`: Classes for vehicles.
    -   `Employee.hpp`, `Driver.hpp`, `MaintenanceStaff.hpp`: Classes for employees.
    -   `Brigade.hpp`: Class for brigades.
    -   `Route.hpp`: Class for routes.
    -   `Repair.hpp`: Class for repairs.
    -   `Garage.hpp`: Class for garages.
    -   `Utils.hpp`: Helper utilities.
-   `src/`: Directory for implementation files (`.cpp`).
    -   Contains implementation files for each header file.
    -   `main.cpp`: The program's entry point.
-   `AIS_System.exe`: The executable file of the program (after compilation).
-   `README_UA.md`: Project information file (Ukrainian).
-   `README.md`: Project information file (English).

## Features

-   **Data Management:**
    -   Add, view, and delete vehicles (passenger, cargo, auxiliary).
    -   Add, view, and delete employees (drivers, maintenance staff).
    -   Add, view, and delete brigades, routes, repair records, and garages.
-   **Saving and Loading Data:**
    -   Data is automatically loaded from text files on startup.
    -   Changes made during a session are saved to files when the corresponding menu options are selected or before exiting (depending on the save implementation in `AIS_System::processEditEntityChoice`).
-   **Analytics and Reporting:**
    -   Passenger flow analysis.
    -   Calculation of the total cost of repairs.
    -   Viewing vehicle mileage (total, by class, by vehicle number).
    -   Displaying the workload of repair brigades.
-   **Search:**
    -   Search for entities (vehicle, employee, route, etc.) by their unique identifier.

## Compilation Requirements

-   A C++ compiler that supports C++11 or a newer version (e.g., g++).
-   The C++ Standard Library.

## Compilation and Execution

1.  **Compilation:**
    Open a terminal or command prompt in the project's root directory and execute the following command:

    g++ src/AIS_System.cpp src/AuxiliaryVehicle.cpp src/Brigade.cpp src/CargoVehicle.cpp src/Driver.cpp src/Employee.cpp src/Garage.cpp src/main.cpp src/MaintenanceStaff.cpp src/PassengerVehicle.cpp src/Repair.cpp src/Route.cpp src/Utils.cpp src/Vehicle.cpp -Iinclude -o AIS_System.exe -std=c++11

2.  **Execution:**
    After successful compilation, run the executable file:

    ./AIS_System.exe

    Before the first run, ensure that the `data/` directory exists and contains the necessary data files.

## Data File Format (`.txt` files in the `data/` directory)

-   Field separator: semicolon (`;`).
-   Separator for lists within a field: comma (`,`).

**Examples:**

-   **vehicles.txt:**
    `P;AA1111BX;Mercedes-Benz;Sprinter 316CDI;2019;150200.5;18`
    `C;BD4321BA;Mercedes-Benz;Atego 1218;2019;122000.4;7500.0`
    `A;AE5555CI;Ford;Transit Connect;2017;180300.2;Technical Support`
-   **employees.txt:**
    `D;D001;Petrenko Vasyl Ivanovych;12;B,C,D;AA1111BX,AX7777BT`
    `M;M001;Sydorenko Oleh Petrovych;15;Engine Specialist`
-   **brigades.txt:**
    `B01;Alpha Shift;M001`
-   **routes.txt:**
    `R101;Center - Railway Station;Rynok Square,Svobody Avenue,University,Main Station;AA1111BX,AA2222CX,AO1234KP`
-   **repairs.txt:**
    `RP001;AA1111BX;2023-10-15;Oil and filter replacement;1250.50;B01`
-   **garages.txt:**
    `G01;Garage No.1 (Central)`
-   **passenger_flow.txt:**
    `R101;2350`