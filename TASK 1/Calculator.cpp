#include <iostream>
#include <limits>
#include <cmath>
#include <string>

class Calculator {
private:
    double num1;
    double num2;
    std::string operation;

public:
    // Constructor
    Calculator() : num1(0), num2(0), operation("+") {}

    // Method to get user input
    void getUserInput() {
        std::cout << "\nAvailable operations:" << std::endl;
        std::cout << "1. Basic operations: +, -, *, /" << std::endl;
        std::cout << "2. Power (^)" << std::endl;
        std::cout << "3. Square root (sqrt)" << std::endl;
        std::cout << "4. Sine (sin)" << std::endl;
        std::cout << "5. Cosine (cos)" << std::endl;
        std::cout << "6. Tangent (tan)" << std::endl;
        std::cout << "7. Logarithm (log)" << std::endl;
        
        std::cout << "\nChoose operation (+, -, *, /, ^, sqrt, sin, cos, tan, log): ";
        std::cin >> operation;
        
        // For operations that need one number
        if (operation == "sqrt" || operation == "sin" || operation == "cos" || 
            operation == "tan" || operation == "log") {
            std::cout << "Enter number: ";
            while (!(std::cin >> num1)) {
                std::cout << "Invalid input. Please enter a number: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        } 
        // For operations that need two numbers
        else if (operation == "+" || operation == "-" || 
                 operation == "*" || operation == "/" || 
                 operation == "^") {
            std::cout << "Enter first number: ";
            while (!(std::cin >> num1)) {
                std::cout << "Invalid input. Please enter a number: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            std::cout << "Enter second number: ";
            while (!(std::cin >> num2)) {
                std::cout << "Invalid input. Please enter a number: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        else {
            std::cout << "Invalid operation selected." << std::endl;
        }
    }

    // Method to perform calculation
    double calculate() {
        if (operation == "+") {
            return num1 + num2;
        }
        else if (operation == "-") {
            return num1 - num2;
        }
        else if (operation == "*") {
            return num1 * num2;
        }
        else if (operation == "/") {
            if (num2 == 0) {
                std::cout << "Error: Division by zero!" << std::endl;
                return 0;
            }
            return num1 / num2;
        }
        else if (operation == "^") {
            return pow(num1, num2);
        }
        else if (operation == "sqrt") {
            if (num1 < 0) {
                std::cout << "Error: Cannot calculate square root of a negative number!" << std::endl;
                return 0;
            }
            return sqrt(num1);
        }
        else if (operation == "sin") {
            return sin(num1 * M_PI / 180.0); // Convert to radians
        }
        else if (operation == "cos") {
            return cos(num1 * M_PI / 180.0); // Convert to radians
        }
        else if (operation == "tan") {
            return tan(num1 * M_PI / 180.0); // Convert to radians
        }
        else if (operation == "log") {
            if (num1 <= 0) {
                std::cout << "Error: Logarithm is defined only for positive numbers!" << std::endl;
                return 0;
            }
            return log10(num1);
        }
        else {
            std::cout << "Invalid operation!" << std::endl;
            return 0;
        }
    }

    // Method to display result
    void displayResult() {
        if (operation != "+" && operation != "-" && operation != "*" && 
            operation != "/" && operation != "^" && operation != "sqrt" && 
            operation != "sin" && operation != "cos" && operation != "tan" && 
            operation != "log") {
            std::cout << "No calculation performed due to invalid operation." << std::endl;
            return;
        }
        
        double result = calculate();
        
        if (operation == "sqrt") {
            std::cout << "Square root of " << num1 << " = " << result << std::endl;
        } 
        else if (operation == "sin") {
            std::cout << "Sine of " << num1 << " degrees = " << result << std::endl;
        }
        else if (operation == "cos") {
            std::cout << "Cosine of " << num1 << " degrees = " << result << std::endl;
        } 
        else if (operation == "tan") {
            std::cout << "Tangent of " << num1 << " degrees = " << result << std::endl;
        } 
        else if (operation == "log") {
            std::cout << "Log(base 10) of " << num1 << " = " << result << std::endl;
        } 
        else {
            std::cout << "Result of " << num1 << " " << operation << " " << num2 << " = " << result << std::endl;
        }
    }
};

int main() {
    Calculator calc;
    char continueCalculation = 'y';
    
    std::cout << "Advanced Calculator Program" << std::endl;
    std::cout << "--------------------------" << std::endl;
    
    do {
        calc.getUserInput();
        calc.displayResult();
        
        std::cout << "\nDo you want to perform another calculation? (y/n): ";
        std::cin >> continueCalculation;
    } while (continueCalculation == 'y' || continueCalculation == 'Y');
    
    std::cout << "Thank you for using the calculator!" << std::endl;
    
    return 0;
}