#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <limits>

using namespace std;

// Base class for date handling
class Date {
private:
    int day;
    int month;
    int year;

public:
    Date() {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        day = ltm->tm_mday;
        month = 1 + ltm->tm_mon;
        year = 1900 + ltm->tm_year;
    }

    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    void setDate(int d, int m, int y) {
        day = d;
        month = m;
        year = y;
    }

    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

    string toString() const {
        return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
    }

    // Calculate difference in days between two dates
    int diffDays(const Date& other) const {
        // Simple implementation for demonstration
        // In a real system, you'd use a more accurate algorithm
        int thisTotalDays = year * 365 + month * 30 + day;
        int otherTotalDays = other.year * 365 + other.month * 30 + other.day;
        return thisTotalDays - otherTotalDays;
    }
};

// Book class to store book information
class Book {
private:
    string title;
    string author;
    string isbn;
    bool available;

public:
    Book(const string& t, const string& a, const string& i)
        : title(t), author(a), isbn(i), available(true) {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getIsbn() const { return isbn; }
    bool isAvailable() const { return available; }

    void setAvailable(bool status) { available = status; }

    void displayInfo() const {
        cout << left << setw(30) << title.substr(0, 27) + (title.length() > 27 ? "..." : "")
             << setw(20) << author.substr(0, 17) + (author.length() > 17 ? "..." : "")
             << setw(15) << isbn
             << setw(10) << (available ? "Available" : "Borrowed") << endl;
    }
};

// Borrower class to store borrower information
class Borrower {
private:
    string name;
    string id;
    vector<string> borrowedBooks; // Store ISBNs of borrowed books

public:
    Borrower(const string& n, const string& i) : name(n), id(i) {}

    string getName() const { return name; }
    string getId() const { return id; }
    const vector<string>& getBorrowedBooks() const { return borrowedBooks; }

    void borrowBook(const string& isbn) {
        borrowedBooks.push_back(isbn);
    }

    void returnBook(const string& isbn) {
        auto it = find(borrowedBooks.begin(), borrowedBooks.end(), isbn);
        if (it != borrowedBooks.end()) {
            borrowedBooks.erase(it);
        }
    }

    void displayInfo() const {
        cout << "Borrower: " << name << " (ID: " << id << ")" << endl;
        cout << "Books borrowed: " << borrowedBooks.size() << endl;
    }
};

// Transaction class to store checkout and return information
class Transaction {
private:
    string isbn;
    string borrowerId;
    Date checkoutDate;
    Date returnDate;
    bool returned;
    double fine;

public:
    Transaction(const string& i, const string& b)
        : isbn(i), borrowerId(b), returned(false), fine(0.0) {
        // checkout date is automatically set to current date
    }

    string getIsbn() const { return isbn; }
    string getBorrowerId() const { return borrowerId; }
    const Date& getCheckoutDate() const { return checkoutDate; }
    const Date& getReturnDate() const { return returnDate; }
    bool isReturned() const { return returned; }
    double getFine() const { return fine; }

    void returnBook() {
        returned = true;
        returnDate = Date(); // Current date
        
        // Calculate fine (Rs. 10 per day after 14 days)
        int daysOut = returnDate.diffDays(checkoutDate);
        if (daysOut > 14) {
            fine = (daysOut - 14) * 10.0;
        }
    }

    void displayInfo() const {
        cout << "ISBN: " << isbn << ", Borrower ID: " << borrowerId << endl;
        cout << "Checkout date: " << checkoutDate.toString() << endl;
        if (returned) {
            cout << "Return date: " << returnDate.toString() << endl;
            cout << "Fine: Rs. " << fixed << setprecision(2) << fine << endl;
        } else {
            cout << "Status: Not returned yet" << endl;
        }
    }
};

// Library class to manage the entire system
class Library {
private:
    vector<Book> books;
    vector<Borrower> borrowers;
    vector<Transaction> transactions;

    // Helper method to find a book by ISBN
    int findBookIndex(const string& isbn) const {
        for (size_t i = 0; i < books.size(); i++) {
            if (books[i].getIsbn() == isbn) {
                return i;
            }
        }
        return -1;
    }

    // Helper method to find a borrower by ID
    int findBorrowerIndex(const string& id) const {
        for (size_t i = 0; i < borrowers.size(); i++) {
            if (borrowers[i].getId() == id) {
                return i;
            }
        }
        return -1;
    }

    // Helper method to find active transaction by ISBN
    int findActiveTransaction(const string& isbn) const {
        for (size_t i = 0; i < transactions.size(); i++) {
            if (transactions[i].getIsbn() == isbn && !transactions[i].isReturned()) {
                return i;
            }
        }
        return -1;
    }

public:
    // Add a new book to the library
    void addBook(const string& title, const string& author, const string& isbn) {
        if (findBookIndex(isbn) == -1) {
            books.push_back(Book(title, author, isbn));
            cout << "Book added successfully!" << endl;
        } else {
            cout << "Book with ISBN " << isbn << " already exists!" << endl;
        }
    }

    // Add a new borrower to the library
    void addBorrower(const string& name, const string& id) {
        if (findBorrowerIndex(id) == -1) {
            borrowers.push_back(Borrower(name, id));
            cout << "Borrower added successfully!" << endl;
        } else {
            cout << "Borrower with ID " << id << " already exists!" << endl;
        }
    }

    // Search for books by title
    void searchBooksByTitle(const string& title) {
        bool found = false;
        cout << left << setw(30) << "TITLE" << setw(20) << "AUTHOR" << setw(15) << "ISBN" << setw(10) << "STATUS" << endl;
        cout << string(75, '-') << endl;
        
        for (const auto& book : books) {
            if (book.getTitle().find(title) != string::npos) {
                book.displayInfo();
                found = true;
            }
        }
        
        if (!found) {
            cout << "No books found with title containing '" << title << "'" << endl;
        }
    }

    // Search for books by author
    void searchBooksByAuthor(const string& author) {
        bool found = false;
        cout << left << setw(30) << "TITLE" << setw(20) << "AUTHOR" << setw(15) << "ISBN" << setw(10) << "STATUS" << endl;
        cout << string(75, '-') << endl;
        
        for (const auto& book : books) {
            if (book.getAuthor().find(author) != string::npos) {
                book.displayInfo();
                found = true;
            }
        }
        
        if (!found) {
            cout << "No books found with author containing '" << author << "'" << endl;
        }
    }

    // Search for a book by ISBN
    void searchBookByISBN(const string& isbn) {
        int index = findBookIndex(isbn);
        
        if (index != -1) {
            cout << left << setw(30) << "TITLE" << setw(20) << "AUTHOR" << setw(15) << "ISBN" << setw(10) << "STATUS" << endl;
            cout << string(75, '-') << endl;
            books[index].displayInfo();
        } else {
            cout << "No book found with ISBN '" << isbn << "'" << endl;
        }
    }

    // Check out a book to a borrower
    void checkoutBook(const string& isbn, const string& borrowerId) {
        int bookIndex = findBookIndex(isbn);
        int borrowerIndex = findBorrowerIndex(borrowerId);
        
        if (bookIndex == -1) {
            cout << "Book with ISBN " << isbn << " not found!" << endl;
            return;
        }
        
        if (borrowerIndex == -1) {
            cout << "Borrower with ID " << borrowerId << " not found!" << endl;
            return;
        }
        
        if (!books[bookIndex].isAvailable()) {
            cout << "Book is not available for checkout!" << endl;
            return;
        }
        
        // Update book status
        books[bookIndex].setAvailable(false);
        
        // Update borrower record
        borrowers[borrowerIndex].borrowBook(isbn);
        
        // Create transaction
        transactions.push_back(Transaction(isbn, borrowerId));
        
        cout << "Book checked out successfully!" << endl;
    }

    // Return a book
    void returnBook(const string& isbn) {
        int bookIndex = findBookIndex(isbn);
        int transactionIndex = findActiveTransaction(isbn);
        
        if (bookIndex == -1) {
            cout << "Book with ISBN " << isbn << " not found!" << endl;
            return;
        }
        
        if (transactionIndex == -1) {
            cout << "No active checkout found for this book!" << endl;
            return;
        }
        
        // Get borrower ID from transaction
        string borrowerId = transactions[transactionIndex].getBorrowerId();
        int borrowerIndex = findBorrowerIndex(borrowerId);
        
        // Update book status
        books[bookIndex].setAvailable(true);
        
        // Update borrower record
        if (borrowerIndex != -1) {
            borrowers[borrowerIndex].returnBook(isbn);
        }
        
        // Update transaction
        transactions[transactionIndex].returnBook();
        double fine = transactions[transactionIndex].getFine();
        
        cout << "Book returned successfully!" << endl;
        if (fine > 0) {
            cout << "Fine for late return: Rs. " << fixed << setprecision(2) << fine << endl;
        }
    }

    // Display all books
    void displayAllBooks() const {
        if (books.empty()) {
            cout << "No books in the library!" << endl;
            return;
        }
        
        cout << left << setw(30) << "TITLE" << setw(20) << "AUTHOR" << setw(15) << "ISBN" << setw(10) << "STATUS" << endl;
        cout << string(75, '-') << endl;
        
        for (const auto& book : books) {
            book.displayInfo();
        }
    }

    // Display all borrowers
    void displayAllBorrowers() const {
        if (borrowers.empty()) {
            cout << "No borrowers registered!" << endl;
            return;
        }
        
        cout << "BORROWERS LIST:" << endl;
        cout << string(50, '-') << endl;
        
        for (const auto& borrower : borrowers) {
            borrower.displayInfo();
            cout << endl;
        }
    }

    // Display borrower's active checkouts
    void displayBorrowerCheckouts(const string& borrowerId) const {
        int borrowerIndex = findBorrowerIndex(borrowerId);
        
        if (borrowerIndex == -1) {
            cout << "Borrower with ID " << borrowerId << " not found!" << endl;
            return;
        }
        
        const Borrower& borrower = borrowers[borrowerIndex];
        const vector<string>& borrowedBooks = borrower.getBorrowedBooks();
        
        cout << "Checkouts for " << borrower.getName() << " (ID: " << borrower.getId() << "):" << endl;
        
        if (borrowedBooks.empty()) {
            cout << "No active checkouts." << endl;
            return;
        }
        
        cout << left << setw(30) << "TITLE" << setw(20) << "AUTHOR" << setw(15) << "ISBN" << setw(20) << "CHECKOUT DATE" << endl;
        cout << string(85, '-') << endl;
        
        for (const auto& isbn : borrowedBooks) {
            int bookIndex = findBookIndex(isbn);
            int transactionIndex = findActiveTransaction(isbn);
            
            if (bookIndex != -1 && transactionIndex != -1) {
                const Book& book = books[bookIndex];
                const Transaction& transaction = transactions[transactionIndex];
                
                cout << left << setw(30) << book.getTitle().substr(0, 27) + (book.getTitle().length() > 27 ? "..." : "")
                     << setw(20) << book.getAuthor().substr(0, 17) + (book.getAuthor().length() > 17 ? "..." : "")
                     << setw(15) << book.getIsbn()
                     << setw(20) << transaction.getCheckoutDate().toString() << endl;
            }
        }
    }
};

// User Interface class to handle all interactions
class LibraryUI {
private:
    Library library;

    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    void waitForEnter() {
        cout << "\nPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int getMenuChoice() {
        int choice;
        cout << "\nEnter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return choice;
    }

    void displayMainMenu() {
        clearScreen();
        cout << "========================================\n";
        cout << "        LIBRARY MANAGEMENT SYSTEM       \n";
        cout << "========================================\n";
        cout << "1. Book Management\n";
        cout << "2. Borrower Management\n";
        cout << "3. Transaction Management\n";
        cout << "4. Reports\n";
        cout << "0. Exit\n";
    }

    void displayBookMenu() {
        clearScreen();
        cout << "========================================\n";
        cout << "             BOOK MANAGEMENT            \n";
        cout << "========================================\n";
        cout << "1. Add New Book\n";
        cout << "2. Search Books by Title\n";
        cout << "3. Search Books by Author\n";
        cout << "4. Search Book by ISBN\n";
        cout << "5. Display All Books\n";
        cout << "0. Back to Main Menu\n";
    }

    void displayBorrowerMenu() {
        clearScreen();
        cout << "========================================\n";
        cout << "          BORROWER MANAGEMENT           \n";
        cout << "========================================\n";
        cout << "1. Add New Borrower\n";
        cout << "2. Display All Borrowers\n";
        cout << "0. Back to Main Menu\n";
    }

    void displayTransactionMenu() {
        clearScreen();
        cout << "========================================\n";
        cout << "         TRANSACTION MANAGEMENT         \n";
        cout << "========================================\n";
        cout << "1. Checkout Book\n";
        cout << "2. Return Book\n";
        cout << "3. View Borrower's Checkouts\n";
        cout << "0. Back to Main Menu\n";
    }

    void displayReportsMenu() {
        clearScreen();
        cout << "========================================\n";
        cout << "                REPORTS                 \n";
        cout << "========================================\n";
        cout << "1. Available Books\n";
        cout << "2. Borrowed Books\n";
        cout << "0. Back to Main Menu\n";
    }

    void handleBookManagement() {
        int choice;
        do {
            displayBookMenu();
            choice = getMenuChoice();
            
            switch (choice) {
                case 1: addBook(); break;
                case 2: searchBooksByTitle(); break;
                case 3: searchBooksByAuthor(); break;
                case 4: searchBookByISBN(); break;
                case 5: displayAllBooks(); break;
                case 0: break;
                default: cout << "Invalid choice! Please try again.\n"; waitForEnter();
            }
        } while (choice != 0);
    }

    void handleBorrowerManagement() {
        int choice;
        do {
            displayBorrowerMenu();
            choice = getMenuChoice();
            
            switch (choice) {
                case 1: addBorrower(); break;
                case 2: displayAllBorrowers(); break;
                case 0: break;
                default: cout << "Invalid choice! Please try again.\n"; waitForEnter();
            }
        } while (choice != 0);
    }

    void handleTransactionManagement() {
        int choice;
        do {
            displayTransactionMenu();
            choice = getMenuChoice();
            
            switch (choice) {
                case 1: checkoutBook(); break;
                case 2: returnBook(); break;
                case 3: viewBorrowerCheckouts(); break;
                case 0: break;
                default: cout << "Invalid choice! Please try again.\n"; waitForEnter();
            }
        } while (choice != 0);
    }

    void handleReports() {
        int choice;
        do {
            displayReportsMenu();
            choice = getMenuChoice();
            
            switch (choice) {
                case 1: displayAvailableBooks(); break;
                case 2: displayBorrowedBooks(); break;
                case 0: break;
                default: cout << "Invalid choice! Please try again.\n"; waitForEnter();
            }
        } while (choice != 0);
    }

    // Book Management Functions
    void addBook() {
        clearScreen();
        cout << "========================================\n";
        cout << "               ADD NEW BOOK             \n";
        cout << "========================================\n";
        
        string title, author, isbn;
        
        cout << "Enter book title: ";
        getline(cin, title);
        
        cout << "Enter author name: ";
        getline(cin, author);
        
        cout << "Enter ISBN: ";
        getline(cin, isbn);
        
        library.addBook(title, author, isbn);
        waitForEnter();
    }

    void searchBooksByTitle() {
        clearScreen();
        cout << "========================================\n";
        cout << "           SEARCH BOOKS BY TITLE        \n";
        cout << "========================================\n";
        
        string title;
        cout << "Enter title to search: ";
        getline(cin, title);
        
        library.searchBooksByTitle(title);
        waitForEnter();
    }

    void searchBooksByAuthor() {
        clearScreen();
        cout << "========================================\n";
        cout << "          SEARCH BOOKS BY AUTHOR        \n";
        cout << "========================================\n";
        
        string author;
        cout << "Enter author name to search: ";
        getline(cin, author);
        
        library.searchBooksByAuthor(author);
        waitForEnter();
    }

    void searchBookByISBN() {
        clearScreen();
        cout << "========================================\n";
        cout << "           SEARCH BOOK BY ISBN          \n";
        cout << "========================================\n";
        
        string isbn;
        cout << "Enter ISBN to search: ";
        getline(cin, isbn);
        
        library.searchBookByISBN(isbn);
        waitForEnter();
    }

    void displayAllBooks() {
        clearScreen();
        cout << "========================================\n";
        cout << "              ALL BOOKS                 \n";
        cout << "========================================\n";
        
        library.displayAllBooks();
        waitForEnter();
    }

    void displayAvailableBooks() {
        // This would be implemented in a full system by filtering books in the Library class
        clearScreen();
        cout << "========================================\n";
        cout << "           AVAILABLE BOOKS              \n";
        cout << "========================================\n";
        
        cout << "This feature would display only available books.\n";
        waitForEnter();
    }

    void displayBorrowedBooks() {
        // This would be implemented in a full system by filtering books in the Library class
        clearScreen();
        cout << "========================================\n";
        cout << "            BORROWED BOOKS              \n";
        cout << "========================================\n";
        
        cout << "This feature would display only borrowed books.\n";
        waitForEnter();
    }

    // Borrower Management Functions
    void addBorrower() {
        clearScreen();
        cout << "========================================\n";
        cout << "            ADD NEW BORROWER            \n";
        cout << "========================================\n";
        
        string name, id;
        
        cout << "Enter borrower name: ";
        getline(cin, name);
        
        cout << "Enter borrower ID: ";
        getline(cin, id);
        
        library.addBorrower(name, id);
        waitForEnter();
    }

    void displayAllBorrowers() {
        clearScreen();
        cout << "========================================\n";
        cout << "             ALL BORROWERS              \n";
        cout << "========================================\n";
        
        library.displayAllBorrowers();
        waitForEnter();
    }

    // Transaction Management Functions
    void checkoutBook() {
        clearScreen();
        cout << "========================================\n";
        cout << "              CHECKOUT BOOK             \n";
        cout << "========================================\n";
        
        string isbn, borrowerId;
        
        cout << "Enter book ISBN: ";
        getline(cin, isbn);
        
        cout << "Enter borrower ID: ";
        getline(cin, borrowerId);
        
        library.checkoutBook(isbn, borrowerId);
        waitForEnter();
    }

    void returnBook() {
        clearScreen();
        cout << "========================================\n";
        cout << "               RETURN BOOK              \n";
        cout << "========================================\n";
        
        string isbn;
        cout << "Enter book ISBN: ";
        getline(cin, isbn);
        
        library.returnBook(isbn);
        waitForEnter();
    }

    void viewBorrowerCheckouts() {
        clearScreen();
        cout << "========================================\n";
        cout << "          BORROWER'S CHECKOUTS          \n";
        cout << "========================================\n";
        
        string borrowerId;
        cout << "Enter borrower ID: ";
        getline(cin, borrowerId);
        
        library.displayBorrowerCheckouts(borrowerId);
        waitForEnter();
    }

public:
    void run() {
        int choice;
        do {
            displayMainMenu();
            choice = getMenuChoice();
            
            switch (choice) {
                case 1: handleBookManagement(); break;
                case 2: handleBorrowerManagement(); break;
                case 3: handleTransactionManagement(); break;
                case 4: handleReports(); break;
                case 0: cout << "Exiting...\n"; break;
                default: cout << "Invalid choice! Please try again.\n"; waitForEnter();
            }
        } while (choice != 0);
    }
};

// Main function
int main() {
    LibraryUI ui;
    ui.run();
    return 0;
}
