#include "../include/AIS_System.hpp"
#include <iostream>
int main()
{
    std::cout << "Welcome to the Automated Information System for Urban Transport!\n";
    std::cout << "------------------------------------------------------------------------------------------------------------------------\n";

    //Створення обєкта системи та запуск
    try{AIS_System cityTransportAIS;
        cityTransportAIS.run();}

    //Обробка стандартних помилок
    catch (const std::exception &e) {std::cerr << "A critical error occurred: " << e.what() << std::endl; return 1;}

    //Other
    catch (...) {std::cerr << "An unknown critical error occurred." << std::endl; return 1;}

    std::cout << "\nThank you for using the system!\n";
    std::cout << "Press Enter to exit...";
    std::cin.get();
    return 0;
}