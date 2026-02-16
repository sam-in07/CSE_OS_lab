#include <iostream>
using namespace std;


double calculate(double a, double b, char symbol) {
    switch (symbol) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                cout << " Error: Cannot divide by zero!" << endl;
                return 0;
            }
            return a / b;
        default:
            cout << "Error: Invalid operator!" << endl;
            return 0;
    }
}





int main() {
    double x, y;
    char choice;
    char operation;

    do {
        cout << "\n=====  CALCULATOR =====" << endl;
        cout << "Available Operations: +  -  *  /" << endl;

        cout << "Enter first number: ";
        cin >> x;

        cout << "Enter second number: ";
        cin >> y;

        cout << "Choose operation: ";
        cin >> operation;

        double result = calculate(x, y, operation);

        cout << "Result = " << result << endl;

        cout << "\nDo you want to calculate again? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');


    return 0;
}