#include <iostream>
#include <vector>
#include "LinearSystem.h"
#include "LinearSystemExceptions.h"
#include "ScopeLogger.h"

void level3() {
    ScopeLogger logger("level3");
    std::cout << "Creating system with invalid size...\n";
    std::vector<double> A = { 1, 2, 3, 4 };
    std::vector<double> b = { 1 };

    LinearSystem sys(A, b, 2);
}

void level2() {
    ScopeLogger logger("level2");
    try {
        level3();
    }
    catch (const InvalidSizeException& ex) {
        std::cout << "[LOG] level2 caught: expected " << ex.expected() << ", got " << ex.actual() << '\n';
        throw;
    }
}

void level1() {
    ScopeLogger logger("level1");
    level2();
}

int main() {
    try {
        level1();
    }
    catch (const LinearSystemException& ex) {
        std::cout << "[MAIN] Exception caught: " << ex.what() << '\n';
    }
    catch (const std::exception& ex) {
        std::cout << "[MAIN] Standard exception: " << ex.what() << '\n';
    }

    std::cout << "Program finished gracefully.\n";
    return 0;
}