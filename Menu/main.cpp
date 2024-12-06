#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <limits>

#ifdef _WIN32
#include <conio.h>
#define CLEAR_SCREEN "cls"
#else
#include <termios.h>
#include <unistd.h>
#define CLEAR_SCREEN "clear"
#endif

#define RESET_COLOR "\033[0m"
#define RED_COLOR "\033[31m"
#define GREEN_COLOR "\033[32m"
#define YELLOW_COLOR "\033[33m"

using namespace std;

class Employ {
public:
    int ID;
    int Salary;
    string Name;
    int RollNo;

    void inputDetails();
    void displayDetails() const;
    static bool validateName(const string& name);
};

class Stack {
private:
    Employ* arr;
    int top;
    int maxSize;

public:
    Stack(int size) : maxSize(size), top(-1) {
        arr = new Employ[maxSize];
    }

    ~Stack() {
        delete[] arr;
    }

    bool push(const Employ& emp) {
        if (top >= maxSize - 1) {
            cout << RED_COLOR << "Stack Overflow!\n" << RESET_COLOR;
            return false;
        }
        arr[++top] = emp;
        return true;
    }

    bool pop(Employ& emp) {
        if (top < 0) {
            cout << RED_COLOR << "Stack Underflow!\n" << RESET_COLOR;
            return false;
        }
        emp = arr[top--];
        return true;
    }

    void printStack() const {
        if (top == -1) {
            cout << RED_COLOR << "Stack is empty.\n" << RESET_COLOR;
            return;
        }
        cout << GREEN_COLOR << "Stack contents:\n" << RESET_COLOR;
        for (int i = top; i >= 0; --i) {
            arr[i].displayDetails();
        }
    }
};

class Menu {
private:
    int position = 0;

public:
    void stackMenu(Stack& stack);
    void clearScreen() const { system(CLEAR_SCREEN); }
};

void Employ::inputDetails() {
    cout << "Enter Employee ID: ";
    while (!(cin >> ID)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << RED_COLOR << "Invalid input. Please enter a number.\n" << RESET_COLOR;
    }

    cout << "Enter Employee Roll No: ";
    while (!(cin >> RollNo)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << RED_COLOR << "Invalid input. Please enter a number.\n" << RESET_COLOR;
    }

    cin.ignore(); // Ignore leftover newline
    do {
        cout << "Enter Employee Name: ";
        getline(cin, Name);
        if (!validateName(Name)) {
            cout << RED_COLOR << "Invalid name. Only alphabets and spaces are allowed.\n" << RESET_COLOR;
        }
    } while (!validateName(Name));

    cout << "Enter Employee Salary: ";
    while (!(cin >> Salary) || Salary <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << RED_COLOR << "Invalid input. Salary must be a positive number.\n" << RESET_COLOR;
    }
}

void Employ::displayDetails() const {
    cout << YELLOW_COLOR << "----------------------" << RESET_COLOR << "\n";
    cout << "ID: " << ID << "\n";
    cout << "Roll No: " << RollNo << "\n";
    cout << "Name: " << Name << "\n";
    cout << "Salary: " << Salary << "\n";
    cout << YELLOW_COLOR << "----------------------" << RESET_COLOR << "\n";
}

bool Employ::validateName(const string& name) {
    for (char ch : name) {
        if (!isalpha(ch) && ch != ' ') return false;
    }
    return true;
}

void Menu::stackMenu(Stack& stack) {
    int choice;
    Employ emp; // Temporary object for stack operations

    while (true) {
        clearScreen();
        cout << YELLOW_COLOR << "=========   STACK MENU  =========" << RESET_COLOR << "\n";
        cout << "1. Push (Add Employee)\n";
        cout << "2. Pop (Remove Employee)\n";
        cout << "3. Print Stack\n";
        cout << "4. Back to Main Menu\n";
        cout << "Select an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << GREEN_COLOR << "Enter details for the new employee:\n" << RESET_COLOR;
                emp.inputDetails();
                if (stack.push(emp)) {
                    cout << GREEN_COLOR << "Employee added to stack successfully!\n" << RESET_COLOR;
                }
                break;

            case 2:
                if (stack.pop(emp)) {
                    cout << GREEN_COLOR << "Removed employee details:\n" << RESET_COLOR;
                    emp.displayDetails();
                }
                break;

            case 3:
                stack.printStack();
                break;

            case 4:
                return;

            default:
                cout << RED_COLOR << "Invalid choice. Please try again.\n" << RESET_COLOR;
        }
        cout << "Press any key to continue...";
        cin.ignore(); // Consume newline from the menu choice input
        cin.get();    // Wait for any key
    }
}

int main() {
    int stackSize;

    cout << "Enter stack size: ";
    cin >> stackSize;

    Stack stack(stackSize);
    Menu menu;
    menu.stackMenu(stack);

    return 0;
}
