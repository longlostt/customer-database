#include <iostream>
#include <vector>
#include <string>
#include "Customers.h"
#include "Purchases.h"

using namespace std;

void printMenu() {
    cout << "Menu Options:" << endl;
    cout << "1. Print all customers" << endl;
    cout << "2. Sort and print customers in ascending/descending order" << endl;
    cout << "3. Print a specific customer’s account information and all associated purchases" << endl;
    cout << "4. Print total spend for a customer" << endl;
    cout << "5. Add a new customer" << endl;
    cout << "6. Add multiple new customers" << endl; // using recursion
    cout << "7. Update a customer’s information" << endl;
    cout << "8. Delete a customer’s information" << endl;
    cout << "9. Add a new purchase for a customer" << endl;
    cout << "10. Add multiple new purchases (using recursion)" << endl;
    cout << "11. Save updated data to the original files or copy to a new file" << endl;
    cout << "12. Exit" << endl;
    
}

int main() {
    vector<Customer> customers;
    vector<Purchase> purchases;
    // Load initial data from files
    customers = Customer::loadFromFile("customers.txt");
    purchases = Purchase::loadFromFile("purchases.txt");

    int choice;
    do {
        printMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
			system("cls");
            Customer::printAllCustomers(customers);
            break;
        case 2: {
            system("cls");
            bool ascending;
            cout << "Enter 1 for ascending or 0 for descending: ";
            cin >> ascending;
            Customer::sortCustomers(customers, ascending);
            Customer::printAllCustomers(customers);
            break;
        }
        case 3: {
            system("cls");
            int accountNumber;
            cout << "Enter account number: ";
            cin >> accountNumber;
            //Customer::printCustomerDetails(customers, purchases, accountNumber);
            Purchase::printPurchasesForCustomer(purchases, accountNumber);
            break;
        }
        case 4: {
            system("cls");
            int accountNumber;
            cout << "Enter account number: ";
            cin >> accountNumber;
            double totalSpend = Purchase::calculateTotalSpend(purchases, accountNumber);
            cout << "Total spend for account " << accountNumber << ": " << totalSpend << endl;
            break;
        }
        case 5: {
            system("cls");
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
            break;
        }
        case 6: {
            system("cls");
            int count;
            cout << "Enter number of customers to add: ";
            cin >> count;
            Customer::addMultipleCustomers(customers, count);
            break;
        }
        case 7: {
            system("cls");
            int accountNumber;
            cout << "Enter account number of the customer to update: ";
            cin >> accountNumber;

            string firstName, lastName, streetAddress, city, state, zipCode, phoneNumber;
            cout << "Enter new first name: ";
            cin >> firstName;
            cout << "Enter new last name: ";
            cin >> lastName;
            cout << "Enter new street address: ";
            cin >> streetAddress;
            cout << "Enter new city: ";
            cin >> city;
            cout << "Enter new state: ";
            cin >> state;
            cout << "Enter new zip code: ";
            cin >> zipCode;
            cout << "Enter new phone number: ";
            cin >> phoneNumber;

            Customer updatedCustomer(firstName, lastName, accountNumber, streetAddress, city, state, zipCode, phoneNumber);
            Customer::updateCustomer(customers, accountNumber, updatedCustomer);
            break;
        }
        case 8: {
            system("cls");
            int accountNumber;
            cout << "Enter account number to delete: ";
            cin >> accountNumber;
            Customer::deleteCustomer(customers, accountNumber);
            break;
        }
        case 9: {
            system("cls");
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
            break;
        }
        case 10: {
            system("cls");
            int count;
            cout << "Enter number of purchases to add: ";
            cin >> count;
            Purchase::addMultiplePurchases(purchases, count);
            break;
        }
        case 11: {
            system("cls");
            string filename;
            cout << "Enter filename to save data (leave empty to overwrite original files): ";
            cin.ignore(); // To ignore the newline character left in the buffer
            getline(cin, filename);
            if (filename.empty()) {
                Customer::saveToFile(customers, "customers.txt");
                Purchase::saveToFile(purchases, "purchases.txt");
            }
            else {
                Customer::saveToFile(customers, filename + "_customers.txt");
                Purchase::saveToFile(purchases, filename + "_purchases.txt");
            }
            break;
        }
        case 12: {
            system("cls");
            cout << "Exiting program." << endl;
            break;
        }
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 12);

    return 0;
}
