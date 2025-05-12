#include <iostream>
using namespace std;

// Base class
class Card {
public:
    int cardNumber;
    int balance;
    int password;
};


// Derived classes
class DebitCard : public Card {
public:
    int dailyLimit;

    void withdraw(int amount) {
        if (amount <= dailyLimit && amount <= balance) {
            balance -= amount;
            cout << "DebitCard: Withdrawn " << amount << ", New balance: " << balance << endl;
        } else {
            cout << "DebitCard: Withdrawal failed due to limit or insufficient balance." << endl;
        }
    }
    void addBalance(int amount) {
        balance += amount;
        cout << "DebitCard: Added " << amount << ", New balance: " << balance << endl;
    }
};

// derived from card
class CreditCard : public Card {
public:
    int creditLimit;

    void withdraw(int amount) {
        if (amount <= balance + creditLimit) {
            balance -= amount;
            cout << "CreditCard: Withdrawn " << amount << ", New balance: " << balance << endl;
        } else {
            cout << "CreditCard: Exceeded credit limit." << endl;
        }
    }
};

class VirtualCard : public DebitCard {
public:
    bool isTemporary;

    void withdraw(int amount) {
        if (isTemporary) {
            cout << "VirtualCard: Temporary card verified." << endl;
        }
        if (amount <= dailyLimit && amount <= balance) {
            balance -= amount;
            cout << "VirtualCard: Withdrawn " << amount << ", New balance: " << balance << endl;
        } else {
            cout << "VirtualCard: Withdrawal failed." << endl;
        }
    }
    void addBalance(int amount) {
        balance += amount;
        cout << "VirtualCard: Added " << amount << ", New balance: " << balance << endl;
    }
};

// ATM class
class ATM {
public:
    DebitCard debitCards[10];
    int debitCount = 0;

    VirtualCard virtualCards[10];
    int virtualCount = 0;

    void addCard(DebitCard card) {
        debitCards[debitCount++] = card;
    }

    void addCard(VirtualCard card) {
        virtualCards[virtualCount++] = card;
    }

    bool authenticate(int cardNumber, int password) {
        for (int i = 0; i < debitCount; i++) {
            if (debitCards[i].cardNumber == cardNumber && debitCards[i].password == password)
                return true;
        }
        for (int i = 0; i < virtualCount; i++) {
            if (virtualCards[i].cardNumber == cardNumber && virtualCards[i].password == password)
                return true;
        }
        return false;
    }

    void checkBalance(int cardNumber, int password) {
        for (int i = 0; i < debitCount; i++) {
            if (debitCards[i].cardNumber == cardNumber)
                cout << "Balance: " << debitCards[i].balance << endl;
        }
        for (int i = 0; i < virtualCount; i++) {
            if (virtualCards[i].cardNumber == cardNumber)
                cout << "Balance: " << virtualCards[i].balance << endl;
        }
    }

    void withdraw(int amount, int cardNumber, int password) {
        for (int i = 0; i < debitCount; i++) {
            if (debitCards[i].cardNumber == cardNumber) {
                debitCards[i].withdraw(amount);
                return;
            }
        }
        for (int i = 0; i < virtualCount; i++) {
            if (virtualCards[i].cardNumber == cardNumber) {
                virtualCards[i].withdraw(amount);
                return;
            }
        }
    }
    void addBalance(int amount, int cardNumber) {
        for (int i = 0; i < debitCount; i++) {
            if (debitCards[i].cardNumber == cardNumber) {
                debitCards[i].addBalance(amount);
            }
            else if (virtualCards[i].cardNumber == cardNumber) {
                virtualCards[i].addBalance(amount);
            }
        }
    }
};

int main() {
    DebitCard d{};
    d.cardNumber = 1111;
    d.password = 1234;
    d.balance = 1000;
    d.dailyLimit = d.balance * 90 / 100;

    VirtualCard v{};
    v.cardNumber = 3333;
    v.password = 4321;
    v.balance = 1500;
    v.dailyLimit = (v.balance * 90 / 100);
    v.isTemporary = true;

    ATM atm;
    atm.addCard(d);
    atm.addCard(v);

    int cardNumber, password;

    // Keep asking for card Number and password until authentication succeeds
    while (true) {
        cout << "Enter card number: ";
        cin >> cardNumber;
        cout << "Enter password: ";
        cin >> password;

        if (cin.fail()) {
            cin.clear(); // clear input errors
            cin.ignore(1000, '\n'); // discard invalid input
            cout << "Invalid input. Please try again.\n";
            continue;
        }

        if (atm.authenticate(cardNumber, password)) {
            cout << "Welcome to ATM. Your card#" << cardNumber << endl;

            while (true) {
                string choice;
                cout << "\n1. Check balance\n2. Withdraw \n3 Deposit \n4. Check Daily Limit \n5. Exit";
                cout << "\nEnter your choice: ";
                cin >> choice;

                if (choice == "1") {
                    atm.checkBalance(cardNumber, password);
                } else if (choice == "2") {
                    int amount;
                    cout << "Enter amount: ";
                    cin >> amount;
                    atm.withdraw(amount, cardNumber, password);
                } else if (choice == "4") {
                    cout << "Daily Limit: " << v.dailyLimit << endl;
                } else if (choice == "3") {
                    int amount;
                    cout << "Enter amount: ";
                    cin >> amount;
                    atm.addBalance(amount, cardNumber);
                } else if (choice == "5") {
                   break;
                } else {
                    cout << "Invalid choice." << endl;
                }
            }
            break; // exit login loop after
        } else {
            cout << "Invalid card number or password. Please try again.\n";
        }
    }

    return 0;
}