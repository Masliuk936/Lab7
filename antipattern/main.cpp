#include <iostream>
#include <string>
#include <stdexcept>
#include <exception>

void throwInteger() {
    throw 404;
}

void throwString() {
    throw std::string("Error occurred");
}

void demonstrateSlicing() {
    try {
        throw std::invalid_argument("Detailed error message");
    }
    catch (const std::exception& ex) {
        throw ex;
    }
}

int main() {
    std::cout << "=== Example 1: int exception ===\n";
    try {
        throwInteger();
    }
    catch (const std::exception& ex) {
        std::cout << "Caught by std::exception: " << ex.what() << '\n';
    }
    catch (int error) {
        std::cout << "Caught int: " << error << "\n";
    }

    std::cout << "\n=== Example 2: string exception ===\n";
    try {
        throwString();
    }
    catch (const std::exception& ex) {
        std::cout << "Caught by std::exception: " << ex.what() << '\n';
    }
    catch (const std::string& error) {
        std::cout << "Caught string: " << error << "\n";
    }

    std::cout << "\n=== Example 3: Object Slicing ===\n";
    try {
        demonstrateSlicing();
    }
    catch (const std::invalid_argument& ex) {
        std::cout << "Caught specific invalid_argument\n";
    }
    catch (const std::exception& ex) {
        std::cout << "Caught base std::exception (Object was sliced!)\n";
    }

    return 0;
}