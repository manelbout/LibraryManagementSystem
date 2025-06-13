#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Book {
public:
    string title;
    string author;
    bool isBorrowed;

    Book(string t, string a) : title(t), author(a), isBorrowed(false) {}

    void displayInfo() {
        cout << "Title: " << title << ", Author: " << author;
        if (isBorrowed) cout << " [Borrowed]";
        cout << endl;
    }
};

class User {
protected:
    string name;
public:
    User(string n) : name(n) {}
    virtual void menu(vector<Book>& books) = 0;
};

class Student : public User {
public:
    Student(string n) : User(n) {}
    void menu(vector<Book>& books) override;
};

class Teacher : public User {
public:
    Teacher(string n) : User(n) {}
    void menu(vector<Book>& books) override;
};

class Librarian : public User {
public:
    Librarian(string n) : User(n) {}
    void menu(vector<Book>& books) override;
};

void borrowBook(vector<Book>& books) {
    string title;
    cout << "Enter the title of the book to borrow: ";
    cin.ignore();
    getline(cin, title);

    for (Book& b : books) {
        if (b.title == title && !b.isBorrowed) {
            b.isBorrowed = true;
            cout << "Book borrowed successfully.\n";
            return;
        }
    }
    cout << "Book not found or already borrowed.\n";
}

void returnBook(vector<Book>& books) {
    string title;
    cout << "Enter the title of the book to return: ";
    cin.ignore();
    getline(cin, title);

    for (Book& b : books) {
        if (b.title == title && b.isBorrowed) {
            b.isBorrowed = false;
            cout << "Book returned successfully.\n";
            return;
        }
    }
    cout << "Book not found or wasn't borrowed.\n";
}

void searchBook(vector<Book>& books) {
    string title;
    cout << "Enter the title to search: ";
    cin.ignore();
    getline(cin, title);

    bool found = false;
    for (Book& b : books) {
        if (b.title.find(title) != string::npos) {
            b.displayInfo();
            found = true;
        }
    }
    if (!found) cout << "No matching books found.\n";
}

void displayBooks(vector<Book>& books) {
    for (Book& b : books) {
        b.displayInfo();
    }
}

// Student Menu
void Student::menu(vector<Book>& books) {
    int choice;
    do {
        cout << "\nStudent Menu\n1. Borrow Book\n2. Return Book\n3. Search Book\n4. Display All Books\n5. Logout\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: borrowBook(books); break;
            case 2: returnBook(books); break;
            case 3: searchBook(books); break;
            case 4: displayBooks(books); break;
            case 5: cout << "Logging out...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 5);
}

// Teacher Menu
void Teacher::menu(vector<Book>& books) {
    int choice;
    do {
        cout << "\nTeacher Menu\n1. Borrow Book\n2. Return Book\n3. Search Book\n4. Display All Books\n5. Logout\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: borrowBook(books); break;
            case 2: returnBook(books); break;
            case 3: searchBook(books); break;
            case 4: displayBooks(books); break;
            case 5: cout << "Logging out...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 5);
}

// Librarian Menu
void Librarian::menu(vector<Book>& books) {
    int choice;
    do {
        cout << "\nLibrarian Menu\n1. Add Book\n2. Remove Book\n3. Search Book\n4. Display All Books\n5. Logout\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                string title, author;
                cout << "Enter book title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter book author: ";
                getline(cin, author);
                books.push_back(Book(title, author));
                cout << "Book added successfully.\n";
                break;
            }
            case 2: {
                string title;
                cout << "Enter the title of the book to remove: ";
                cin.ignore();
                getline(cin, title);
                auto it = remove_if(books.begin(), books.end(), [&](Book& b) {
                    return b.title == title;
                });
                if (it != books.end()) {
                    books.erase(it, books.end());
                    cout << "Book removed.\n";
                } else {
                    cout << "Book not found.\n";
                }
                break;
            }
            case 3: searchBook(books); break;
            case 4: displayBooks(books); break;
            case 5: cout << "Logging out...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 5);
}

int main() {
    vector<Book> books = {
        Book("Linear Algebra Done Right", "Sheldon Axler"),
        Book("Introduction to Linear Algebra", "Gilbert Strang"),
        Book("Linear Algebra and Its Applications", "David C. Lay"),
        Book("Elementary Linear Algebra", "Howard Anton"),
        Book("Practical Linear Algebra", "Gerard E. Dullerud"),
        Book("The Elements of Statistical Learning", "Trevor Hastie"),
        Book("Statistical Inference", "George Casella & Roger L. Berger"),
        Book("Applied Multivariate Statistical Analysis", "Richard A. Johnson"),
        Book("Introduction to the Theory of Statistics", "Alexander M. Mood"),
        Book("All of Statistics", "Larry Wasserman"),
        Book("Brave New World", "Aldous Huxley"),
        Book("The Great Gatsby", "F. Scott Fitzgerald"),
        Book("1984", "George Orwell")
    };

    while (true) {
        string role, name;
        cout << "\nLogin (student / teacher / librarian or 'exit'): ";
        cin >> role;
        if (role == "exit") break;

        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, name);

        User* user = nullptr;
        if (role == "student") user = new Student(name);
        else if (role == "teacher") user = new Teacher(name);
        else if (role == "librarian") user = new Librarian(name);
        else {
            cout << "Invalid role.\n";
            continue;
        }

        user->menu(books);
        delete user;
    }

    cout << "Goodbye!\n";
    return 0;
}
