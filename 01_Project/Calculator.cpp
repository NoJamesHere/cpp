#include <iostream>
#include <limits>
#include <cctype>

// Function declarations
void addition(int a, int b) {
    std::cout << "\033[32m" << a << " + " << b << " = " << a + b << "\033[0m\n";
}

void subtraction(int a, int b) {
    std::cout << "\033[32m" << a << " - " << b << " = " << a - b << "\033[0m\n";
}

void multiply(int a, int b) {
    std::cout << "\033[32m" << a << " * " << b << " = " << a * b << "\033[0m\n";
}

void divide(int a, int b) {
    if (b == 0) {
        std::cout << "\033[31mCannot divide by 0. Please try again.\033[0m\n";
    } else {
        std::cout << "\033[32m" << a << " / " << b << " = " << static_cast<double>(a) / b << "\033[0m\n";
    }
}

int main() {
    bool running = true;
    int a, b;
    char option;

    std::cout << "Simple arithmetic calculator\n";

    while (running) {
        // Get first number
        std::cout << "Enter your first number: ";
        while (!(std::cin >> a)) {
            std::cin.clear(); // clear error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            std::cout << "Invalid input. Enter a number: ";
        }

        // Get second number
        std::cout << "Enter your second number: ";
        while (!(std::cin >> b)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Enter a number: ";
        }

        // Clear input buffer before reading option
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Get operation
        std::cout << "Choose operation:\n";
        std::cout << "  a -> addition\n";
        std::cout << "  s -> subtraction\n";
        std::cout << "  m -> multiplication\n";
        std::cout << "  d -> division\n";
        std::cout << "  e -> exit\n";
        std::cout << "Your choice: ";
        std::cin >> option;
        option = std::tolower(option);

        switch(option) {
            case 'a': addition(a, b); break;
            case 's': subtraction(a, b); break;
            case 'm': multiply(a, b); break;
            case 'd': divide(a, b); break;
            case 'e': running = false; break;
            default:
                std::cout << "\033[31mPlease select a valid option.\033[0m\n";
        }

        std::cout << "\n"; // Add a newline for readability
    }

    std::cout << "Exiting program.\n";
    return 0;
}
