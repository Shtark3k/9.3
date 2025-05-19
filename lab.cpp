#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <iomanip>
using namespace std;

struct Price {
    string productName;
    string shopName;
    double costUah;
};

int getPositiveInt(const string& prompt) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x && x > 0) {
            cin.ignore();
            return x;
        }
        cout << "Error: enter an integer > 0\n";
        cin.clear();
        cin.ignore();
    }
}

int getMenuChoice() {
    int choice;
    while (true) {
        cout << "Choose an option (0-6): ";
        if (cin >> choice && choice >= 0 && choice <= 6) {
            cin.ignore();
            return choice;
        }
        cout << "Error: enter a number between 0 and 6\n";
        cin.clear();
        cin.ignore();
    }
}

int showMenu() {
    cout << "\n=== Price Manager ===\n"
        << "1. Input data from keyboard\n"
        << "2. Read data from file\n"
        << "3. Write data to file\n"
        << "4. Sort by shop name\n"
        << "5. Search product by name\n"
        << "6. Display array\n"
        << "0. Exit\n";
    return getMenuChoice();
}

string getFileName(const string& prompt) {
    cout << prompt;
    string fn;
    getline(cin, fn);
    return fn;
}

void inputArray(Price*& arr, int& n) {
    delete[] arr;
    n = getPositiveInt("Enter number of items: ");
    arr = new Price[n];
    for (int i = 0; i < n; i++) {
        cout << "Item [" << i << "]\n";
        cout << "Product name: ";
        getline(cin, arr[i].productName);
        cout << "Shop name: ";
        getline(cin, arr[i].shopName);
        while (true) {
            cout << "Cost: ";
            if (cin >> arr[i].costUah && arr[i].costUah >= 0) {
                cin.ignore();
                break;
            }
            cout << "Error: enter a non-negative number\n";
            cin.clear();
            cin.ignore();
        }
    }
}

void readArrayFromFile(Price*& arr, int& n, const string& fileName) {
    ifstream in(fileName);
    if (!in) {
        cout << "Failed to open file for reading\n";
        return;
    }
    delete[] arr;
    in >> n;
    in.ignore();
    arr = new Price[n];
    for (int i = 0; i < n; i++) {
        getline(in, arr[i].productName);
        getline(in, arr[i].shopName);
        in >> arr[i].costUah;
        in.ignore();
    }
    cout << "Read " << n << " items\n";
}

void writeArrayToFile(const Price* arr, int n, const string& fileName) {
    ofstream out(fileName);
    if (!out) {
        cout << "Failed to open file for writing\n";
        return;
    }
    out << n << '\n';
    for (int i = 0; i < n; i++) {
        out << arr[i].productName << '\n'
            << arr[i].shopName << '\n'
            << arr[i].costUah << '\n';
    }
    cout << "Written " << n << " items to file\n";
}

void sortByShop(Price* arr, int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (arr[j].shopName > arr[j + 1].shopName)
                swap(arr[j], arr[j + 1]);
    cout << "Sorting complete\n";
}

int findByProductName(const Price* arr, int n, const string& product) {
    for (int i = 0; i < n; i++)
        if (arr[i].productName == product)
            return i;
    return -1;
}

void printPrice(const Price& p) {
    cout << setw(20) << left << p.productName
        << setw(20) << left << p.shopName
        << setw(10) << right << p.costUah << " UAH\n";
}

void printArray(const Price* arr, int n) {
    if (n <= 0) {
        cout << "Array is empty\n";
        return;
    }
    cout << setw(20) << left << "Product"
        << setw(20) << left << "Shop"
        << setw(10) << right << "Cost\n";
    cout << string(55, '=') << '\n';
    for (int i = 0; i < n; i++)
        printPrice(arr[i]);
}

int main() {
    Price* arr = nullptr;
    int n = 0;
    bool running = true;
    while (running) {
        switch (showMenu()) {
        case 1:
            inputArray(arr, n);
            break;
        case 2: {
            string fn = getFileName("Enter file name to read: ");
            readArrayFromFile(arr, n, fn);
            break;
        }
        case 3: {
            string fn = getFileName("Enter file name to write: ");
            writeArrayToFile(arr, n, fn);
            break;
        }
        case 4:
            sortByShop(arr, n);
            break;
        case 5: {
            cout << "Enter product name to search: ";
            string prod;
            getline(cin, prod);
            int idx = findByProductName(arr, n, prod);
            if (idx >= 0)
                printPrice(arr[idx]);
            else
                cout << "Product \"" << prod << "\" not found\n";
            break;
        }
        case 6:
            printArray(arr, n);
            break;
        case 0:
            running = false;
            break;
        }
    }
    delete[] arr;
    cout << "Goodbye\n";
    return 0;
}
