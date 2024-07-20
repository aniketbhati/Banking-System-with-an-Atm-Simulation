#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

// Maximum number of users
const int MAX_USERS = 100;

// User struct to store account details
class User {
public:
    string name;
    string password;
    double balance;
};

// Admin login credentials
const string ADMIN_USERNAME = "Himanshu";
const string ADMIN_PASSWORD = "12345678";

// Global array to store user accounts
User users[MAX_USERS];
int numUsers = 0;

// Function to write user data to a file
void savingData() {
    ofstream outFile("userData.txt");
    if (outFile.is_open()) {
        outFile << numUsers << endl;
        for (int i = 0; i < numUsers; ++i) {
            outFile << users[i].name << endl;
            outFile << users[i].password << endl;
            outFile << users[i].balance << endl;
        }
        outFile.close();
        cout << "\nUser data saved successfully!" << endl;
    } else {
        cout << "\nError saving user data." << endl;
    }
}

// Function to read or check user data from a file
void readData() {
    ifstream inFile("userData.txt");
    if (inFile.is_open()) {
        inFile >> numUsers;
        inFile.ignore();
        for (int i = 0; i < numUsers; ++i) {
            getline(inFile, users[i].name);
            getline(inFile, users[i].password);
            inFile >> users[i].balance;
            inFile.ignore();
        }
        inFile.close();
        cout << "\nUser data Saved successfully!" << endl;
    } else {
        cout << "\nError in saving user data or starting with an empty database." << endl;
    }
}

// Function to display main menu
void displayMainMenu() {
    cout << "\n\t\tWelcome to the SBI Banking System" << endl;
    cout << "\t\t--------------------------------" << endl;
    cout << "1. Admin Login" << endl;
    cout << "2. User Login" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
}

// Function to display admin menu
void displayAdminMenu() {
    cout << "\n\t\tAdmin Menu" << endl;
    cout << "\t\t-----------" << endl;
    cout << "1. View all user accounts" << endl;
    cout << "2. Create a new user account" << endl;
    cout << "3. Main Menu" << endl;
    cout << "Enter your choice: ";
}

// Function to display user menu
void displayUserMenu() {
    cout << "\n\t\tUser Menu" << endl;
    cout << "\t\t---------" << endl;
    cout << "1. Deposit funds" << endl;
    cout << "2. Withdraw funds" << endl;
    cout << "3. Check balance" << endl;
    cout << "4. Main Menu" << endl;
    cout << "Enter your choice: ";
}

void adminLogin() {
    string username, password;
    cout << "\nEnter Admin Username: ";
    cin >> username;
    cout << "Enter Admin Password: ";
    cin >> password;
    if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD) {
        cout << "\nLogin successful!" << endl;
        int choice;
        do {
            displayAdminMenu();
            cin >> choice;
            switch (choice) {
            case 1:
                cout << "\nUser Accounts:" << endl;
                for (int i = 0; i < numUsers; i++) {
                    cout << "Name: " << users[i].name << ", Balance: Rs." << users[i].balance << endl;
                }
                break;
            case 2:
                if (numUsers < MAX_USERS) {
                    User newUser;
                    cout << "\nEnter new user name: ";
                    cin >> newUser.name;
                    cout << "Enter new user password: ";
                    cin >> newUser.password;
                    newUser.balance = 0.0;
                    users[numUsers++] = newUser;
                    cout << "New user account created successfully!" << endl;
                    savingData(); // Save data after creating a new user
                } else {
                    cout << "\nMaximum number of users reached. Cannot create more accounts." << endl;
                }
                break;
            case 3:
                cout << "\nReturning to main menu..." << endl;
                break;
            default:
                cout << "\nInvalid choice. Please try again." << endl;
                break;
            }
        } while (choice != 3);
    }
    else {
        cout << "\nInvalid username or password. Please try again." << endl;
    }
}

void userLogin() {
    string name, password;
    cout << "\nEnter your name: ";
    cin >> name;
    cout << "Enter your password: ";
    cin >> password;
    for (int i = 0; i < numUsers; i++) {
        if (users[i].name == name && users[i].password == password) {
            cout << "\nLogin successful!" << endl;
            int choice;
            do {
                displayUserMenu();
                cin >> choice;
                switch (choice) {
                case 1:
                    cout << "\nYou already have an account." << endl;
                    break;
                case 2:
                    double amount;
                    cout << "\nEnter amount to deposit: ";
                    cin >> amount;
                    users[i].balance += amount;
                    cout << "Deposit successful. New balance: Rs." << users[i].balance << endl;
                    savingData(); // Save data after depositing funds
                    break;
                case 3:
                    cout << "\nEnter amount to withdraw: ";
                    cin >> amount;
                    if (amount > users[i].balance) {
                        cout << "Insufficient funds." << endl;
                    } else {
                        users[i].balance -= amount;
                        cout << "Withdrawal successful. New balance: Rs." << users[i].balance << endl;
                        savingData(); // Save data after withdrawing funds
                    }
                    break;
                case 4:
                    cout << "\nYour current balance is: Rs." << users[i].balance << endl;
                    break;
                case 5:
                    cout << "\nReturning to main menu..." << endl;
                    break;
                default:
                    cout << "\nInvalid choice. Please try again." << endl;
                    break;
                }
            } while (choice != 5);
            break;
        }
        
    
    }
}

int main() {
    readData(); // saving data 
    //if code is running first time so initially no data is there
    int choice;
    do {
        displayMainMenu();
        cin >> choice;
        switch (choice) {
        case 1:
            adminLogin();
            break;
        case 2:
            userLogin();
            break;
        case 3:
            cout << "\nExiting the banking system. Goodbye!" << endl;
            break;
        default:
            cout << "\nInvalid choice. Please try again." << endl;
            break;
        }
    } while (choice != 3);

    return 0;
}
