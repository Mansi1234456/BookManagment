//============================================================================
// Name        : BookStore.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Book {
public:
    string title;
    string author;
    string ISBN;
    double price;
    int quantity;

    Book(string t, string a, string i, double p, int q) : title(t), author(a), ISBN(i), price(p), quantity(q) {}
};

class User {
public:
    string username;
    string password;
    vector<Book> cart;
    vector<Book> orderHistory;

    User(string u, string p) : username(u), password(p) {}
};

class Bookstore {
public:
    vector<Book> catalog;
    vector<User> users;

    void loadCatalogFromFile() {
        // Load book catalog from a file
        // Initialize 'catalog' vector
    }

    void loadUsersFromFile() {
        // Load user accounts from a file
        // Initialize 'users' vector
    }

    void saveUsersToFile() {
        // Save user accounts to a file
    }

    // Other functions to handle user interactions, shopping cart, orders, etc.
};

int main() {
    Bookstore bookstore;
    bookstore.loadCatalogFromFile();
    bookstore.loadUsersFromFile();

    // Implement a menu system for user interactions
    // Example: Login, Browse Books, Search, Add to Cart, Checkout, etc.

    bookstore.saveUsersToFile();
    return 0;
}

