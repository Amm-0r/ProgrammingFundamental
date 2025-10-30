#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Book {
    string ISBN;
    string title;
    string author;
    double price;
    int stock;
};

struct SaleRecord {
    string ISBN;
    string title;
    int quantity;
    double totalPrice;
};

void addBook(Book books[], int &bookCount);
void displayBooks(Book books[], int bookCount);
int searchBook(Book books[], int bookCount, string keyword);
void buyBook(Book books[], int bookCount, SaleRecord sales[], int &saleCount);
void displaySalesSummary(SaleRecord sales[], int saleCount);
void displayRemainingStock(Book books[], int bookCount);
void mainMenu();

int main() {
    mainMenu();
    return 0;
}

void mainMenu() {
    const int MAX_BOOKS = 100;
    const int MAX_SALES = 100;

    Book books[MAX_BOOKS];
    SaleRecord sales[MAX_SALES];
    int bookCount = 0, saleCount = 0;

    int choice;
    do {
        cout << "\n===== BOOKSTORE SYSTEM =====" << endl;
        cout << "1. Add New Book" << endl;
        cout << "2. Display All Books" << endl;
        cout << "3. Search Book" << endl;
        cout << "4. Buy Book" << endl;
        cout << "5. Show Sales Summary" << endl;
        cout << "6. Show Remaining Stock" << endl;
        cout << "0. Exit" << endl;
        cout << "Choose: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addBook(books, bookCount);
                break;
            case 2:
                displayBooks(books, bookCount);
                break;
            case 3: {
                string keyword;
                cout << "Enter ISBN or Title to search: ";
                getline(cin, keyword);
                int index = searchBook(books, bookCount, keyword);
                if (index != -1) {
                    cout << "\nBook Found:" << endl;
                    cout << "ISBN: " << books[index].ISBN << endl;
                    cout << "Title: " << books[index].title << endl;
                    cout << "Author: " << books[index].author << endl;
                    cout << "Price: RM" << books[index].price << endl;
                    cout << "Stock: " << books[index].stock << endl;
                } else {
                    cout << "Book not found." << endl;
                }
                break;
            }
            case 4:
                buyBook(books, bookCount, sales, saleCount);
                break;
            case 5:
                displaySalesSummary(sales, saleCount);
                break;
            case 6:
                displayRemainingStock(books, bookCount);
                break;
            case 0:
                cout << "Exiting system... Bye!" << endl;
                break;
            default:
                cout << "Invalid choice, try again." << endl;
        }
    } while (choice != 0);
}

void addBook(Book books[], int &bookCount) {
    cout << "\n=== Add New Book ===" << endl;

    Book newBook;
    cout << "Enter ISBN: ";
    getline(cin, newBook.ISBN);

    for (int i = 0; i < bookCount; i++) {
        if (books[i].ISBN == newBook.ISBN) {
            cout << "Book with same ISBN already exists!" << endl;
            return;
        }
    }

    cout << "Enter Title: ";
    getline(cin, newBook.title);
    cout << "Enter Author: ";
    getline(cin, newBook.author);
    cout << "Enter Price (RM): ";
    cin >> newBook.price;
    cout << "Enter Stock Quantity: ";
    cin >> newBook.stock;
    cin.ignore();

    if (newBook.price < 0 || newBook.stock < 0) {
        cout << "Invalid price or stock!" << endl;
        return;
    }

    books[bookCount++] = newBook;
    cout << "Book added successfully!" << endl;
}

void displayBooks(Book books[], int bookCount) {
    cout << "\n=== Book List ===" << endl;
    if (bookCount == 0) {
        cout << "No books available." << endl;
        return;
    }

    cout << left << setw(15) << "ISBN"
         << setw(25) << "Title"
         << setw(20) << "Author"
         << setw(10) << "Price"
         << setw(10) << "Stock" << endl;
    cout << "--------------------------------------------------------------------------" << endl;

    for (int i = 0; i < bookCount; i++) {
        cout << left << setw(15) << books[i].ISBN
             << setw(25) << books[i].title
             << setw(20) << books[i].author
             << "RM" << setw(8) << fixed << setprecision(2) << books[i].price
             << setw(10) << books[i].stock << endl;
    }
}

int searchBook(Book books[], int bookCount, string keyword) {
    for (int i = 0; i < bookCount; i++) {
        if (books[i].ISBN == keyword || books[i].title == keyword)
            return i;
    }
    return -1;
}

void buyBook(Book books[], int bookCount, SaleRecord sales[], int &saleCount) {
    cout << "\n=== Buy Book ===" << endl;
    if (bookCount == 0) {
        cout << "No books in inventory!" << endl;
        return;
    }

    string keyword;
    cout << "Enter ISBN or Title: ";
    getline(cin, keyword);

    int index = searchBook(books, bookCount, keyword);
    if (index == -1) {
        cout << "Book not found!" << endl;
        return;
    }

    int qty;
    cout << "Enter quantity to buy: ";
    cin >> qty;
    cin.ignore();

    if (qty <= 0) {
        cout << "Invalid quantity!" << endl;
        return;
    }
    if (qty > books[index].stock) {
        cout << "Insufficient stock!" << endl;
        return;
    }

    double total = qty * books[index].price;
    books[index].stock -= qty;

    SaleRecord newSale;
    newSale.ISBN = books[index].ISBN;
    newSale.title = books[index].title;
    newSale.quantity = qty;
    newSale.totalPrice = total;

    sales[saleCount++] = newSale;

    cout << "Purchase successful! Total: RM" << fixed << setprecision(2) << total << endl;
}

void displaySalesSummary(SaleRecord sales[], int saleCount) {
    cout << "\n=== Sales Summary ===" << endl;
    if (saleCount == 0) {
        cout << "No sales yet." << endl;
        return;
    }

    double totalAll = 0;
    cout << left << setw(25) << "Title"
         << setw(10) << "Qty"
         << setw(10) << "Total(RM)" << endl;
    cout << "----------------------------------------" << endl;

    for (int i = 0; i < saleCount; i++) {
        cout << left << setw(25) << sales[i].title
             << setw(10) << sales[i].quantity
             << setw(10) << fixed << setprecision(2) << sales[i].totalPrice << endl;
        totalAll += sales[i].totalPrice;
    }
    cout << "----------------------------------------" << endl;
    cout << "Total Sales Today: RM" << totalAll << endl;
}

void displayRemainingStock(Book books[], int bookCount) {
    cout << "\n=== Remaining Stock ===" << endl;
    if (bookCount == 0) {
        cout << "No books in inventory." << endl;
        return;
    }

    cout << left << setw(25) << "Title"
         << setw(10) << "Stock" << endl;
    cout << "-----------------------------" << endl;

    for (int i = 0; i < bookCount; i++) {
        cout << left << setw(25) << books[i].title
             << setw(10) << books[i].stock << endl;
    }
}