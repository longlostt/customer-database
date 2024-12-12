#include "Purchases.h"

// Constructor implementation
Purchase::Purchase(int accountNumber, const string& item, const string& date, double amount)
    : accountNumber(accountNumber), item(item), date(date), amount(amount) {}

// Getter implementations
int Purchase::getAccountNumber() const { return accountNumber; }
string Purchase::getItem() const { return item; }
string Purchase::getDate() const { return date; }
double Purchase::getAmount() const { return amount; }

// Setter implementations
void Purchase::setAccountNumber(int accountNumber) { this->accountNumber = accountNumber; }
void Purchase::setItem(const string& item) { this->item = item; }
void Purchase::setDate(const string& date) { this->date = date; }
void Purchase::setAmount(double amount) { this->amount = amount; }

// Load purchases from file
vector<Purchase> Purchase::loadFromFile(const string& filename) {
    vector<Purchase> purchases;
    ifstream file(filename);
    if (file.is_open()) {
        int accountNumber;
        string item, date;
        double amount;
        while (file >> accountNumber >> item >> date >> amount) {
            purchases.emplace_back(accountNumber, item, date, amount);
        }
        file.close();
    }
    return purchases;
}

// Add a single purchase
void Purchase::addPurchase(vector<Purchase>& purchases, const Purchase& purchase) {
    purchases.push_back(purchase);
}

// Add multiple purchases recursively
void Purchase::addMultiplePurchases(vector<Purchase>& purchases, int count) {
    if (count <= 0) return;
    int accountNumber;
    string item, date;
    double amount;
    cout << "Enter account number: ";
    cin >> accountNumber;
    cout << "Enter item: ";
    cin >> item;
    cout << "Enter date: ";
    cin >> date;
    cout << "Enter amount: ";
    cin >> amount;
    purchases.emplace_back(accountNumber, item, date, amount);
    addMultiplePurchases(purchases, count - 1);
}

// Calculate total spend for a customer
double Purchase::calculateTotalSpend(const vector<Purchase>& purchases, int accountNumber) {
    double total = 0.0;
    for (const auto& purchase : purchases) {
        if (purchase.getAccountNumber() == accountNumber) {
            total += purchase.getAmount();
        }
    }
    return total;
}

// Print purchases for a specific customer
void Purchase::printPurchasesForCustomer(const vector<Purchase>& purchases, int accountNumber) {
    for (const auto& purchase : purchases) {
        if (purchase.getAccountNumber() == accountNumber) {
            cout << "Item: " << purchase.getItem() << ", Date: " << purchase.getDate() << ", Amount: " << purchase.getAmount() << endl;
        }
    }
}

void Purchase::saveToFile(const vector<Purchase>& purchases, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& purchase : purchases) {
            // Enclose item and date in quotes to handle spaces
            file << purchase.getAccountNumber() << " "
                << "\"" << purchase.getItem() << "\" "   // Enclose item in quotes
                << "\"" << purchase.getDate() << "\" "   // Enclose date in quotes
                << purchase.getAmount() << endl;         // Amount remains as it is
        }
        file.close();
    }
    else {
        cerr << "Unable to open file for writing: " << filename << endl;
    }
}

