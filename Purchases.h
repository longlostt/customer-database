#pragma once
#ifndef PURCHASES_H
#define PURCHASES_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class Purchase {
public:
    // Constructor
    Purchase(int accountNumber, const string& item, const string& date, double amount);

    // Getters
    int getAccountNumber() const;
    string getItem() const;
    string getDate() const;
    double getAmount() const;

    // Setters
    void setAccountNumber(int accountNumber);
    void setItem(const string& item);
    void setDate(const string& date);
    void setAmount(double amount);

    // Public member functions
    static vector<Purchase> loadFromFile(const string& filename);
    static void addPurchase(vector<Purchase>& purchases, const Purchase& purchase);
    static void addMultiplePurchases(vector<Purchase>& purchases, int count);
    static double calculateTotalSpend(const vector<Purchase>& purchases, int accountNumber);
    static void printPurchasesForCustomer(const vector<Purchase>& purchases, int accountNumber);
    static void saveToFile(const vector<Purchase>& purchases, const string& filename);

private:
    int accountNumber;
    string item;
    string date;
    double amount;
};

#endif // PURCHASES_H
