#include "Customers.h"
#include "Purchases.h"

// Constructor implementation
Customer::Customer(const string& firstName, const string& lastName, int accountNumber,
    const string& streetAddress, const string& city,
    const string& state, const string& zipCode,
    const string& phoneNumber)
    : firstName(firstName), lastName(lastName), accountNumber(accountNumber),
    streetAddress(streetAddress), city(city), state(state), zipCode(zipCode),
    phoneNumber(phoneNumber) {}

// Getter implementations
string Customer::getFirstName() const { return firstName; }
string Customer::getLastName() const { return lastName; }
int Customer::getAccountNumber() const { return accountNumber; }
string Customer::getStreetAddress() const { return streetAddress; }
string Customer::getCity() const { return city; }
string Customer::getState() const { return state; }
string Customer::getZipCode() const { return zipCode; }
string Customer::getPhoneNumber() const { return phoneNumber; }

// Setter implementations
void Customer::setFirstName(const string& firstName) { this->firstName = firstName; }
void Customer::setLastName(const string& lastName) { this->lastName = lastName; }
void Customer::setStreetAddress(const string& streetAddress) { this->streetAddress = streetAddress; }
void Customer::setCity(const string& city) { this->city = city; }
void Customer::setState(const string& state) { this->state = state; }
void Customer::setZipCode(const string& zipCode) { this->zipCode = zipCode; }
void Customer::setPhoneNumber(const string& phoneNumber) { this->phoneNumber = phoneNumber; }

// Load customers from file
vector<Customer> Customer::loadFromFile(const string& filename) {
    vector<Customer> customers;
    ifstream file(filename);
    if (file.is_open()) {
        string firstName, lastName, streetAddress, city, state, zipCode, phoneNumber;
        int accountNumber;
        while (file >> firstName >> lastName >> accountNumber >> streetAddress >> city >> state >> zipCode >> phoneNumber) {
            customers.emplace_back(firstName, lastName, accountNumber, streetAddress, city, state, zipCode, phoneNumber);
        }
        file.close();
    }
    return customers;
}

// Add a single customer
void Customer::addCustomer(vector<Customer>& customers, const Customer& customer) {
    customers.push_back(customer);
}

// Add multiple customers recursively
void Customer::addMultipleCustomers(vector<Customer>& customers, int count) {
    if (count <= 0) return;
    string firstName, lastName, streetAddress, city, state, zipCode, phoneNumber;
    int accountNumber;
    cout << "Enter first name: ";
    cin >> firstName;
    cout << "Enter last name: ";
    cin >> lastName;
    cout << "Enter account number: ";
    cin >> accountNumber;
    cout << "Enter street address: ";
    cin >> streetAddress;
    cout << "Enter city: ";
    cin >> city;
    cout << "Enter state: ";
    cin >> state;
    cout << "Enter zip code: ";
    cin >> zipCode;
    cout << "Enter phone number: ";
    cin >> phoneNumber;
    customers.emplace_back(firstName, lastName, accountNumber, streetAddress, city, state, zipCode, phoneNumber);
    addMultipleCustomers(customers, count - 1);
}

// Update customer information
void Customer::updateCustomer(vector<Customer>& customers, int accountNumber, const Customer& updatedCustomer) {
    for (auto& customer : customers) {
        if (customer.getAccountNumber() == accountNumber) {
            customer = updatedCustomer;
            break;
        }
    }
}

// Delete customer information
void Customer::deleteCustomer(vector<Customer>& customers, int accountNumber) {
    customers.erase(remove_if(customers.begin(), customers.end(),
        [accountNumber](const Customer& customer) { return customer.getAccountNumber() == accountNumber; }),
        customers.end());
}

// Sort customers
void Customer::sortCustomers(vector<Customer>& customers, bool ascending) {
    sort(customers.begin(), customers.end(), [ascending](const Customer& a, const Customer& b) {
        return ascending ? a.getLastName() < b.getLastName() : a.getLastName() > b.getLastName();
        });
}

// Print all customers
void Customer::printAllCustomers(const vector<Customer>& customers) {
    for (const auto& customer : customers) {
        cout << customer.getFirstName() << " " << customer.getLastName() << " " << customer.getAccountNumber() << " "
            << customer.getStreetAddress() << " " << customer.getCity() << " " << customer.getState() << " "
            << customer.getZipCode() << " " << customer.getPhoneNumber() << endl;
    }
}

// Print specific customer details
void Customer::printCustomerDetails(const vector<Customer>& customers, const vector<Purchase>& purchases, int accountNumber) {
    for (const auto& customer : customers) {
        if (customer.getAccountNumber() == accountNumber) {
            cout << customer.getFirstName() << " " << customer.getLastName() << " " << customer.getAccountNumber() << " "
                << customer.getStreetAddress() << " " << customer.getCity() << " " << customer.getState() << " "
                << customer.getZipCode() << " " << customer.getPhoneNumber() << endl;

            // Print linked purchases
            cout << "Purchases:" << endl;
            for (const auto& purchase : purchases) {
                if (purchase.getAccountNumber() == accountNumber) {
                    cout << "Item: " << purchase.getItem() << ", Date: " << purchase.getDate() << ", Amount: " << purchase.getAmount() << endl;
                }
            }
            break;
        }
    }
}

void Customer::saveToFile(const vector<Customer>& customers, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& customer : customers) {
            file << customer.getFirstName() << " " << customer.getLastName() << " " << customer.getAccountNumber() << " "
                << customer.getStreetAddress() << " " << customer.getCity() << " " << customer.getState() << " "
                << customer.getZipCode() << " " << customer.getPhoneNumber() << endl;
        }
        file.close();
    }
    else {
        cerr << "Unable to open file for writing: " << filename << endl;
    }
}