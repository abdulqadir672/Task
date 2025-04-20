#include <iostream>  
#include <fstream>  
#include <vector>  
#include <string>  
#include <iomanip>  

using namespace std;  

class Customer {  
public:  
    int customerId;  
    string name;  
    string phone;  

    Customer() {}  
    Customer(int id, string n, string p) : customerId(id), name(n), phone(p) {}  

    void save(ofstream &out) {  
        out << customerId << "," << name << "," << phone << endl;  
    }  

    static Customer load(const string &line) {  
        Customer c;  
        size_t pos1 = line.find(',');  
        size_t pos2 = line.find(',', pos1 + 1);  
        c.customerId = stoi(line.substr(0, pos1));  
        c.name = line.substr(pos1 + 1, pos2 - pos1 - 1);  
        c.phone = line.substr(pos2 + 1);  
        return c;  
    }  
};  

class Account {  
public:  
    int accountNumber;  
    int customerId;  
    float balance;  

    Account() {}  
    Account(int accNo, int custId, float bal = 0.0f) : accountNumber(accNo), customerId(custId), balance(bal) {}  

    void deposit(float amount) {  
        balance += amount;  
        cout << "✅ Deposit successful. New Balance: $" << fixed << setprecision(2) << balance << endl;  
    }  

    void withdraw(float amount) {  
        if (balance >= amount) {  
            balance -= amount;  
            cout << "✅ Withdrawal successful. New Balance: $" << fixed << setprecision(2) << balance << endl;  
        } else {  
            cout << "❌ Insufficient balance!" << endl;  
        }  
    }  

    void display() const {  
        cout << "Account Number: " << accountNumber  
             << ", Customer ID: " << customerId  
             << ", Balance: $" << fixed << setprecision(2) << balance << endl;  
    }  

    void save(ofstream &out) {  
        out << accountNumber << "," << customerId << "," << balance << endl;  
    }  

    static Account load(const string &line) {  
        Account a;  
        size_t pos1 = line.find(',');  
        size_t pos2 = line.find(',', pos1 + 1);  
        a.accountNumber = stoi(line.substr(0, pos1));  
        a.customerId = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));  
        a.balance = stof(line.substr(pos2 + 1));  
        return a;  
    }  
};  

class BankSystem {  
private:  
    vector<Customer> customers;  
    vector<Account> accounts;  
    int nextCustomerId = 1001;  
    int nextAccountNumber = 5001;  

public:  
    BankSystem() {  
        loadData();  
    }  

    ~BankSystem() {  
        saveData();  
    }  

    void createCustomer() {  
        string name, phone;  
        cout << "Enter customer name: ";  
        cin.ignore();  
        getline(cin, name);  
        cout << "Enter phone number: ";  
        getline(cin, phone);  

        customers.push_back(Customer(nextCustomerId, name, phone));  
        cout << "✅ Customer created with ID: " << nextCustomerId << endl;  
        nextCustomerId++;  
    }  

    void createAccount() {  
        int custId;  
        cout << "Enter existing customer ID: ";  
        cin >> custId;  

        if (!isCustomerExist(custId)) {  
            cout << "❌ Customer ID not found!" << endl;  
            return;  
        }  

        accounts.push_back(Account(nextAccountNumber, custId, 0.0f));  
        cout << "✅ Account created with Account Number: " << nextAccountNumber << endl;  
        nextAccountNumber++;  
    }  

    void depositMoney() {  
        int accNo;  
        float amount;  
        cout << "Enter account number: ";  
        cin >> accNo;  
        cout << "Enter amount to deposit: ";  
        cin >> amount;  

        Account* acc = getAccount(accNo);  
        if (acc) {  
            acc->deposit(amount);  
        } else {  
            cout << "❌ Account not found!" << endl;  
        }  
    }  

    void withdrawMoney() {  
        int accNo;  
        float amount;  
        cout << "Enter account number: ";  
        cin >> accNo;  
        cout << "Enter amount to withdraw: ";  
        cin >> amount;  

        Account* acc = getAccount(accNo);  
        if (acc) {  
            acc->withdraw(amount);  
        } else {  
            cout << "❌ Account not found!" << endl;  
        }  
    }  

    void transferMoney() {  
        int fromAcc, toAcc;  
        float amount;  
        cout << "Enter sender account number: ";  
        cin >> fromAcc;  
        cout << "Enter receiver account number: ";  
        cin >> toAcc;  
        cout << "Enter amount to transfer: ";  
        cin >> amount;  

        Account* sender = getAccount(fromAcc);  
        Account* receiver = getAccount(toAcc);  

        if (sender && receiver) {  
            if (sender->balance >= amount) {  
                sender->withdraw(amount);  
                receiver->deposit(amount);  
                cout << "✅ Transfer successful." << endl;  
            } else {  
                cout << "❌ Sender has insufficient balance!" << endl;  
            }  
        } else {  
            cout << "❌ One or both account numbers are invalid!" << endl;  
        }  
    }  

    void viewAccount() {  
        int accNo;  
        cout << "Enter account number: ";  
        cin >> accNo;  

        Account* acc = getAccount(accNo);  
        if (acc) {  
            acc->display();  
        } else {  
            cout << "❌ Account not found!" << endl;  
        }  
    }  

    void listAccounts() {  
        cout << "\n=== All Accounts ===" << endl;  
        for (const auto& acc : accounts) {  
            acc.display();  
        }  
    }  

private:  
    Account* getAccount(int accNo) {  
        for (auto& acc : accounts) {  
            if (acc.accountNumber == accNo) return &acc;  
        }  
        return nullptr;  
    }  

    bool isCustomerExist(int custId) {  
        for (const auto& c : customers) {  
            if (c.customerId == custId) return true;  
        }  
        return false;  
    }  

    void saveData() {  
        ofstream outC("customers.txt");  
        for (const auto& c : customers) {  
            c.save(outC);  
        }  
        outC.close();  

        ofstream outA("accounts.txt");  
        for (const auto& a : accounts) {  
            a.save(outA);  
        }  
        outA.close();  
    }  

    void loadData() {  
        string line;  

        // Load customers  
        ifstream inC("customers.txt");  
        while (getline(inC, line)) {  
            if (line.empty()) continue;  // Skip empty lines  
            Customer c = Customer::load(line);  
            customers.push_back(c);  
            if (c.customerId >= nextCustomerId) nextCustomerId = c.customerId + 1;  
        }  
        inC.close();  

        // Load accounts  
        ifstream inA("accounts.txt");  
        while (getline(inA, line)) {  
            if (line.empty()) continue;  // Skip empty lines  
            Account a = Account::load(line);  
            accounts.push_back(a);  
            if (a.accountNumber >= nextAccountNumber) nextAccountNumber = a.accountNumber + 1;  
        }  
        inA.close();  
    }  
};  

// Main function  
int main() {  
    BankSystem bank;  
    int choice;  

    do {  
        cout << "\n===== BANKING SYSTEM MENU =====" << endl;  
        cout << "1. Create Customer\n"  
             << "2. Create Account\n"  
             << "3. Deposit Money\n"  
             << "4. Withdraw Money\n"  
             << "5. Transfer Money\n"  
             << "6. View Account\n"  
             << "7. List All Accounts\n"  
             << "0. Exit\n";  
        cout << "Enter your choice: ";  
        cin >> choice;  

        switch (choice) {  
            case 1: bank.createCustomer(); break;  
            case 2: bank.createAccount(); break;  
            case 3: bank.depositMoney(); break;  
            case 4: bank.withdrawMoney(); break;  
            case 5: bank.transferMoney(); break;  
            case 6: bank.viewAccount(); break;  
            case 7: bank.listAccounts(); break;  
            case 0: cout << "👋 Exiting... Goodbye!\n"; break;  
            default: cout << "❌ Invalid choice! Try again.\n"; break;  
        }  
    } while (choice != 0);  

    return 0;  
}  