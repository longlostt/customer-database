#include <iostream>
#include <vector>
#include <string>
#include "Customers.h"
#include "Purchases.h"
#include <limits>


using namespace std;

void printMenu() {
    cout << endl;
    cout << "Menu Options:" << endl;
    cout << "1. Print all customers" << endl;
    cout << "2. Sort and print customers in ascending/descending order" << endl;
    cout << "3. Print a specific customer's account information and all associated purchases" << endl; // FIX 
    cout << "4. Print total spend for a customer" << endl;
    cout << "5. Add a new customer" << endl;
    cout << "6. Add multiple new customers" << endl; // using recursion
    cout << "7. Update a customer's information" << endl;
    cout << "8. Delete a customer's information" << endl;
    cout << "9. Add a new purchase for a customer" << endl;
	cout << "10. Add multiple new purchases" << endl; // using recursion
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
        while (!(cin >> choice)) {
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid input. Please enter an integer: ";
        }

        switch (choice) {
        case 1:
			system("cls");
            Customer::printAllCustomers(customers);
            break;
        case 2: {
            system("cls");
            bool ascending;
            cout << "Enter 1 for ascending or 0 for descending: " ;
            cin >> ascending;
            cout << endl;
            Customer::sortCustomers(customers, ascending);
            Customer::printAllCustomers(customers);
            break;
        }
        case 3: {
            system("cls");
            int accountNumber;
            cout << "Enter account number: ";
            cin >> accountNumber;
            cout << endl;
            Customer::printCustomerDetailsWithPurchases(customers, purchases, accountNumber);
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
            // Simply call the addCustomer function from the Customer class
            customers[0].addCustomer(customers);  // You can call it from any customer in the list
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
            Customer::updateCustomer(customers, accountNumber);
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
            Purchase::addPurchase(purchases);
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
			system("cls");
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 12);

    return 0;
}
