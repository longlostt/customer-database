#pragma once
#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "Purchases.h" // Include the Purchases header

using namespace std;

class Customer {
public:
    // Constructor
    Customer(const string& firstName, const string& lastName, int accountNumber,
        const string& streetAddress, const string& city,
        const string& state, const string& zipCode,
        const string& phoneNumber);

    // Getters
    string getFirstName() const;
    string getLastName() const;
    int getAccountNumber() const;
    string getStreetAddress() const;
    string getCity() const;
    string getState() const;
    string getZipCode() const;
    string getPhoneNumber() const;
    

    // Setters
    void setFirstName(const string& firstName);
    void setLastName(const string& lastName);
    void setStreetAddress(const string& streetAddress);
    void setCity(const string& city);
    void setState(const string& state);
    void setZipCode(const string& zipCode);
    void setPhoneNumber(const string& phoneNumber);

    // Public member functions

    // Ensure there are no unnecessary copies of Customer objects
    static vector<Customer> loadFromFile(const string& filename); // define a fixed file format (e.g., comma-separated values) to prevent issues with spaces in fields like the street address.
	static void addCustomer(vector<Customer>& customers); // handle edge cases
	static void addMultipleCustomers(vector<Customer>& customers, int count); // handle edge cases // error handling
    static void updateCustomer(vector<Customer>& customers, int accountNumber);// add error handling
    static void deleteCustomer(vector<Customer>& customers, int accountNumber); // add error handling
	static void sortCustomers(vector<Customer>& customers, bool ascending = true); // use lambda function
	static void printAllCustomers(const vector<Customer>& customers); // format output
    static void printCustomerDetailsWithPurchases(const vector<Customer>& customers, const vector<Purchase>& purchases, int accountNumber); // add error handling // consider using find_if
    static void saveToFile(const vector<Customer>& customers, const string& filename); // define a fixed file format (e.g., comma-separated values) to prevent issues with spaces in fields like the street address.
    void addPurchase(const Purchase& purchase);
    const std::vector<Purchase>& getPurchases() const;
    //static void linkPurchasesToCustomers(std::vector<Customer>& customers, const std::vector<Purchase>& purchases);

private:
    std::vector<Purchase> purchases; // Vector to store associated purchases
    string firstName;
    string lastName;
    int accountNumber;
    string streetAddress;
    string city;
    string state;
    string zipCode;
    string phoneNumber;
};

#endif // CUSTOMERS_H
    