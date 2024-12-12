#include "Customers.h"
#include "Purchases.h"
#include <sstream> // Include for istringstream


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
std::string trim(const std::string& str) {
    auto start = std::find_if_not(str.begin(), str.end(), isspace);
    auto end = std::find_if_not(str.rbegin(), str.rend(), isspace).base();
    return (start < end) ? std::string(start, end) : std::string();
}

vector<Customer> Customer::loadFromFile(const string& filename) {
    vector<Customer> customers;
    ifstream file(filename);
    if (file.is_open()) {
        string firstName, lastName, streetAddress, city, state, zipCode, phoneNumber;
        int accountNumber;
        string line;

        while (getline(file, line)) {
            stringstream ss(line);

            // Read first name, last name, and account number
            ss >> firstName >> lastName >> accountNumber;

            // Read the rest of the address fields
            getline(ss, streetAddress, ',');
            streetAddress = trim(streetAddress); // Trim leading and trailing whitespace
            ss.ignore();

            getline(ss, city, ',');
            city = trim(city);
            ss.ignore();

            getline(ss, state, ',');
            state = trim(state);
            ss.ignore();

            getline(ss, zipCode, ',');
            zipCode = trim(zipCode);
            ss.ignore();

            // Read phone number and trim it
            getline(ss, phoneNumber);
            phoneNumber = trim(phoneNumber);

            // Add the customer to the vector
            customers.emplace_back(firstName, lastName, accountNumber, streetAddress, city, state, zipCode, phoneNumber);
        }

        file.close();
    }
    return customers;
}

// Add a single customer
void Customer::addCustomer(vector<Customer>& customers) {
    string firstName, lastName, streetAddress, city, state, zipCode, phoneNumber;
    int accountNumber;

	cin.ignore();  // Clear the buffer before using getline

    // Get customer information using a method from the Customer class
    cout << "Enter first name: ";
    getline(cin, firstName);  // Use getline for multi-word input
	
    cout << "Enter last name: ";
    getline(cin, lastName);
    
    cout << "Enter account number: ";
    cin >> accountNumber;
    cin.ignore();  // Clear the buffer after cin, before using getline

    cout << "Enter street address: ";
    getline(cin, streetAddress);
    
    cout << "Enter city: ";
    getline(cin, city);
   
    cout << "Enter state: ";
    getline(cin, state);
    
    cout << "Enter zip code: ";
    getline(cin, zipCode);
    
    cout << "Enter phone number: ";
    getline(cin, phoneNumber);
   
    // Create a customer object with the input data
    Customer newCustomer(firstName, lastName, accountNumber, streetAddress, city, state, zipCode, phoneNumber);

    // Add the new customer to the customers vector
    customers.push_back(newCustomer);
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
        cout << "Name: " << customer.getFirstName() << " " << customer.getLastName() << endl;
        cout << "Account Number: " << customer.getAccountNumber() << endl;
        cout << "Address: " << customer.getStreetAddress() << ", "
            << customer.getCity() << ", " << customer.getState()
            << " " << customer.getZipCode() << endl;
        cout << "Phone: " << customer.getPhoneNumber() << endl;
        cout << "----------------------------------" << endl;
    }
    cout << endl;
}


// Print specific customer details
void Customer::printCustomerDetailsWithPurchases(const vector<Customer>& customers, const vector<Purchase>& purchases, int accountNumber) {
    for (const auto& customer : customers) {
        if (customer.getAccountNumber() == accountNumber) {
            // Print customer details
            cout << "Customer Details:\n";
            cout << "Name: " << customer.getFirstName() << " " << customer.getLastName() << endl;
            cout << "Account #: " << customer.getAccountNumber() << endl;
            cout << "Address:" << customer.getStreetAddress() << ", " << customer.getCity() << ", "
                << customer.getState() << " " << customer.getZipCode() << endl;
            cout << "Phone: " << customer.getPhoneNumber() << endl;

            // Print purchases associated with the account number
            cout << "Purchases:\n";
            bool found = false;
            for (const auto& purchase : purchases) {
                if (purchase.getAccountNumber() == accountNumber) {
                    cout << "  Item:" << purchase.getItem()
                        << ", Date:" << purchase.getDate()
                        << ", Amount:" << purchase.getAmount() << endl;
                    found = true;
                }
            }
            if (!found) {
                cout << "  No purchases found for this customer." << endl;
            }
            return; // Exit after finding and printing the customer
        }
    }

    // If no customer matches the account number
    cout << "No customer found with account number " << accountNumber << "." << endl;
}



void Customer::saveToFile(const vector<Customer>& customers, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& customer : customers) {
            // Write the customer's data to the file with the desired format
            file << customer.getFirstName() << " "
                << customer.getLastName() << " "
                << customer.getAccountNumber() << ""
                << customer.getStreetAddress() << ", "  // Add a comma after the street address
                << customer.getCity() << ", "           // Add a comma after the city
                << customer.getState() << ", "          // Add a comma after the state
                << customer.getZipCode() << ", "        // Add a comma after the zip code
                << customer.getPhoneNumber() << endl;   // Phone number is last, no comma after it
        }
        file.close();
    }
    else {
        cerr << "Unable to open file for writing: " << filename << endl;
    }
}



// addPurchase 
void Customer::addPurchase(const Purchase& purchase) {
    purchases.push_back(purchase);
}

const std::vector<Purchase>& Customer::getPurchases() const {
    return purchases;
}

//void Customer::linkPurchasesToCustomers(std::vector<Customer>& customers, const std::vector<Purchase>& purchases) {
//    for (const auto& purchase : purchases) {
//        for (auto& customer : customers) {
//            if (customer.getAccountNumber() == purchase.getAccountNumber()) {
//                customer.addPurchase(purchase);
//            }
//        }
//    }
//}