#include "Purchases.h"
#include <sstream> // Include for istringstream

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
        string line;

        while (getline(file, line)) {
            stringstream ss(line);

            int accountNumber;
            string item, date;
            double amount;

            // Parse account number
            ss >> accountNumber;
            ss.ignore(); // Ignore the comma

            // Parse item
            getline(ss, item, ',');
            // Remove leading/trailing spaces (optional)
            item.erase(0, item.find_first_not_of(" \t"));
            item.erase(item.find_last_not_of(" \t") + 1);

            // Parse date
            getline(ss, date, ',');

            // Parse amount
            ss >> amount;

            // Add to purchases vector
            purchases.emplace_back(accountNumber, item, date, amount);
        }
        file.close();
    }
    else {
        cerr << "Error opening file: " << filename << endl;
    }

    return purchases;
}



// Add a single purchase
void Purchase::addPurchase(vector<Purchase>& purchases) {
    int accountNumber;
    string item, date;
    double amount;

    cout << "Enter account number: ";
    while (!(cin >> accountNumber)) {
        cout << "Invalid input. Please enter a valid account number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Enter item: ";
    cin.ignore(); // To ignore the newline character left in the buffer
    getline(cin, item);

    cout << "Enter date: ";
    getline(cin, date);

    cout << "Enter amount: ";
    while (!(cin >> amount)) {
        cout << "Invalid input. Please enter a valid amount: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Add the new purchase to the vector
    purchases.emplace_back(accountNumber, item, date, amount);
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
    bool found = false; // To track if any purchases are found for the account
    for (const auto& purchase : purchases) {
        if (purchase.getAccountNumber() == accountNumber) {
            cout << "Item: " << purchase.getItem()
                << ", Date: " << purchase.getDate()
                << ", Amount: " << purchase.getAmount() << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No purchases found for this account." << endl;
    }
}


void Purchase::saveToFile(const vector<Purchase>& purchases, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& purchase : purchases) {
            // Save purchase details with commas separating each field
            file << purchase.getAccountNumber() << ", "
                << purchase.getItem() << ", "
                << purchase.getDate() << ", "
                << purchase.getAmount() << endl;   // Amount remains as it is
        }
        file.close();
    }
    else {
        cerr << "Unable to open file for writing: " << filename << endl;
    }
}


