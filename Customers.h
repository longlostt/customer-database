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
    static vector<Customer> loadFromFile(const string& filename);
    static void addCustomer(vector<Customer>& customers, const Customer& customer);
    static void addMultipleCustomers(vector<Customer>& customers, int count);
    static void updateCustomer(vector<Customer>& customers, int accountNumber, const Customer& updatedCustomer);
    static void deleteCustomer(vector<Customer>& customers, int accountNumber);
    static void sortCustomers(vector<Customer>& customers, bool ascending = true);
    static void printAllCustomers(const vector<Customer>& customers);
    static void printCustomerDetails(const vector<Customer>& customers, const vector<Purchase>& purchases, int accountNumber);
    static void saveToFile(const vector<Customer>& customers, const string& filename);

private:
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
    