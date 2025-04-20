#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void registerUser();
void loginUser();
bool userExists(const string& username);
bool validateCredentials(const string& username, const string& password);

int main() {
    int choice;

    cout << "===== Login and Registration System =====" << endl;
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;

    switch (choice) {
        case 1:
            registerUser();
            break;
        case 2:
            loginUser();
            break;
        default:
            cout << "Invalid choice!" << endl;
    }

    return 0;
}

void registerUser() {
    string username, password;

    cout << "\n--- Register ---\n";
    cout << "Enter username: ";
    cin >> username;

    if (userExists(username)) {
        cout << "Username already exists. Try another one.\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    ofstream file("database/" + username + ".txt");
    file << username << endl << password;
    file.close();

    cout << "✅ Registration successful! You can now log in.\n";
}

void loginUser() {
    string username, password;

    cout << "\n--- Login ---\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (validateCredentials(username, password)) {
        cout << "✅ Login successful! Welcome, " << username << ".\n";
    } else {
        cout << "❌ Invalid username or password.\n";
    }
}

bool userExists(const string& username) {
    ifstream file("database/" + username + ".txt");
    return file.good();
}

bool validateCredentials(const string& username, const string& password) {
    ifstream file("database/" + username + ".txt");
    if (!file.is_open()) return false;

    string storedUsername, storedPassword;
    getline(file, storedUsername);
    getline(file, storedPassword);
    file.close();

    return (storedUsername == username && storedPassword == password);
}
