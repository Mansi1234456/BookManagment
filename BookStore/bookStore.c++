#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Book {
public:
    string title;
    string author;
    string ISBN;
    double price;
    int quantity;

    Book(string t, string a, string i, double p, int q)
        : title(t), author(a), ISBN(i), price(p), quantity(q) {}
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
    }

    void loadUsersFromFile() {
        // Load user accounts from a file
    }

    void saveUsersToFile() {
        // Save user accounts to a file
    }

    User *findUser(string username) {
        for (auto &user : users) {
            if (user.username == username) {
                return &user;
            }
        }
        return nullptr;
    }

    // Implement other functions for user interactions, shopping, orders, etc.
};

// Function prototypes
void displayMenu();
void loginMenu(Bookstore &store);
void userMenu(Bookstore &store, User &user);
void adminMenu(Bookstore &store);
void createUser(Bookstore &store);
void browseBooks(Bookstore &store, User &user);
void searchBooks(Bookstore &store, User &user);
void addToCart(Bookstore &store, User &user);
void viewCart(User &user);
void checkout(Bookstore &store, User &user);
void viewOrderHistory(User &user);
void addBook(Bookstore &store);
void editBook(Bookstore &store);
void saveAndExit(Bookstore &store);

int main() {
    Bookstore bookstore;
    bookstore.loadCatalogFromFile();
    bookstore.loadUsersFromFile();

    displayMenu();

    return 0;
}


    void displayMenu() {
    Bookstore bookstore;
    bookstore.loadCatalogFromFile();
    bookstore.loadUsersFromFile();

    int choice;

    do {
        cout << "\nWelcome to the Online Bookstore!\n";
        cout << "1. Log In\n";
        cout << "2. Create an Account\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                loginMenu(bookstore);
                break;
            case 2:
                createUser(bookstore);
                break;
            case 3:
                saveAndExit(bookstore);
                cout << "Thank you for using the Online Bookstore. Goodbye!\n";
                exit(0);
            default:
                cout << "Invalid choice. Please select a valid option.\n";
        }
    } while (true);
}

void loginMenu(Bookstore &store) {
    string username, password;
    
    cout << "\nLog In\n";
    cout << "Username: ";
    cin >> username;
    
    User *user = store.findUser(username);
    if (user) {
        cout << "Password: ";
        cin >> password;

        if (user->password == password) {
            cout << "Welcome, " << user->username << "!\n";
            userMenu(store, *user);
        } else {
            cout << "Incorrect password. Please try again.\n";
        }
    } else {
        cout << "User not found. Please check the username or create an account.\n";
    }
}


void userMenu(Bookstore &store, User &user) {
    int choice;

    do {
        cout << "\nUser Menu\n";
        cout << "1. Browse Books\n";
        cout << "2. Search Books\n";
        cout << "3. View Cart\n";
        cout << "4. Checkout\n";
        cout << "5. View Order History\n";
        cout << "6. Log Out\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                browseBooks(store, user);
                break;
            case 2:
                searchBooks(store, user);
                break;
            case 3:
                viewCart(user);
                break;
            case 4:
                checkout(store, user);
                break;
            case 5:
                viewOrderHistory(user);
                break;
            case 6:
                cout << "Logging out. Goodbye, " << user.username << "!\n";
                return;
            default:
                cout << "Invalid choice. Please select a valid option.\n";
        }
    } while (true);
}


void adminMenu(Bookstore &store) {
    int choice;

    do {
        cout << "\nAdmin Menu\n";
        cout << "1. Add Book\n";
        cout << "2. Edit Book\n";
        cout << "3. Log Out\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(store);
                break;
            case 2:
                editBook(store);
                break;
            case 3:
                cout << "Logging out from admin panel.\n";
                return;
            default:
                cout << "Invalid choice. Please select a valid option.\n";
        }
    } while (true);
}


void createUser(Bookstore &store) {
    string username, password;

    cout << "\nCreate an Account\n";
    cout << "Username: ";
    cin >> username;

    User *existingUser = store.findUser(username);
    if (existingUser) {
        cout << "Username already exists. Please choose a different username.\n";
        return;
    }

    cout << "Password: ";
    cin >> password;

    store.users.push_back(User(username, password));
    store.saveUsersToFile();

    cout << "Account created successfully!\n";
}


void browseBooks(Bookstore &store, User &user) {
    cout << "\nAvailable Books:\n";

    for (const auto &book : store.catalog) {
        cout << "Title: " << book.title << endl;
        cout << "Author: " << book.author << endl;
        cout << "ISBN: " << book.ISBN << endl;
        cout << "Price: $" << book.price << endl;
        cout << "Quantity available: " << book.quantity << endl;
    }
}


void searchBooks(Bookstore &store, User &user) {
    string searchTerm;
    cout << "\nEnter search term (title, author, or ISBN): ";
    cin.ignore();
    getline(cin, searchTerm);

    cout << "\nSearch Results:\n";

    bool found = false;
    for (const auto &book : store.catalog) {
        if (book.title.find(searchTerm) != string::npos ||
            book.author.find(searchTerm) != string::npos ||
            book.ISBN.find(searchTerm) != string::npos) {
            cout << "Title: " << book.title << endl;
            cout << "Author: " << book.author << endl;
            cout << "ISBN: " << book.ISBN << endl;
            cout << "Price: $" << book.price << endl;
            cout << "Quantity available: " << book.quantity << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No matching books found.\n";
    }
}


void addToCart(Bookstore &store, User &user) {
    cout << "\nEnter the ISBN of the book you want to add to your cart: ";
    string isbn;
    cin.ignore();
    getline(cin, isbn);

    Book *bookToAdd = nullptr;

    for (auto &book : store.catalog) {
        if (book.ISBN == isbn) {
            bookToAdd = &book;
            break;
        }
    }

    if (bookToAdd) {
        user.cart.push_back(*bookToAdd);
        cout << "Book added to your cart.\n";
    } else {
        cout << "Book with ISBN " << isbn << " not found.\n";
    }
}


void viewCart(User &user) {
    if (user.cart.empty()) {
        cout << "\nYour cart is empty.\n";
        return;
    }

    cout << "\nYour Cart:\n";

    double total = 0.0;
    for (const auto &book : user.cart) {
        cout << "Title: " << book.title << endl;
        cout << "Price: $" << book.price << endl;
        cout << "---------------------" << endl;
        total += book.price;
    }

    cout << "Total Price: $" << total << endl;
}


void checkout(Bookstore &store, User &user) {
    if (user.cart.empty()) {
        cout << "\nYour cart is empty. Nothing to checkout.\n";
        return;
    }

    cout << "\nCheckout Summary:\n";

    double total = 0.0;
    for (const auto &book : user.cart) {
        cout << "Title: " << book.title << endl;
        cout << "Price: $" << book.price << endl;
        cout << "---------------------" << endl;
        total += book.price;
    }

    cout << "Total Price: $" << total << endl;
    cout << "\nConfirm checkout? (yes/no): ";
    
    string confirmation;
    cin >> confirmation;

    if (confirmation == "yes") {
        for (auto &book : user.cart) {
            for (auto &storeBook : store.catalog) {
                if (book.ISBN == storeBook.ISBN) {
                    storeBook.quantity--;
                    user.orderHistory.push_back(book);
                    break;
                }
            }
        }

        user.cart.clear();
        store.saveUsersToFile();
        cout << "\nThank you for your purchase! Your order has been confirmed.\n";
    } else {
        cout << "\nCheckout cancelled.\n";
    }
}


void viewOrderHistory(User &user) {
    if (user.orderHistory.empty()) {
        cout << "\nYour order history is empty.\n";
        return;
    }

    cout << "\nOrder History:\n";

    for (const auto &book : user.orderHistory) {
        cout << "Title: " << book.title << endl;
        cout << "Price: $" << book.price << endl;
        cout << "---------------------" << endl;
    }
}


void addBook(Bookstore &store) {
    string title, author, ISBN;
    double price;
    int quantity;

    cout << "\nEnter Book Details:\n";
    cout << "Title: ";
    cin.ignore();
    getline(cin, title);

    cout << "Author: ";
    getline(cin, author);

    cout << "ISBN: ";
    getline(cin, ISBN);

    cout << "Price: $";
    cin >> price;

    cout << "Quantity: ";
    cin >> quantity;

    store.catalog.push_back(Book(title, author, ISBN, price, quantity));
    cout << "Book added to the catalog.\n";
}


void editBook(Bookstore &store) {
    string ISBN;
    cout << "\nEnter the ISBN of the book you want to edit: ";
    cin.ignore();
    getline(cin, ISBN);

    for (auto &book : store.catalog) {
        if (book.ISBN == ISBN) {
            cout << "\nEditing Book: " << book.title << "\n";
            
            cout << "New Title: ";
            getline(cin, book.title);

            cout << "New Author: ";
            getline(cin, book.author);

            cout << "New ISBN: ";
            getline(cin, book.ISBN);

            cout << "New Price: $";
            cin >> book.price;

            cout << "New Quantity: ";
            cin >> book.quantity;

            cout << "Book details updated.\n";
            return;
        }
    }

    cout << "Book with ISBN " << ISBN << " not found.\n";
}

void saveAndExit(Bookstore &store) {
    store.saveUsersToFile();
    // Save the updated catalog to a file (if needed)
    // ...

    cout << "Saving data and exiting the program.\n";
}



