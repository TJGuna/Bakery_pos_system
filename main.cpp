#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct Product {
    int ProductId{};
    string ProductName;
    double ProductPrice{};
};
struct BillingProduct {
    int ProductId{};
    string ProductName;
    double ProductPrice{};
    double TotalProductPrice{};
    int qty;
};
const int MAX_PRODUCTS = 10; // Maximum number of products per order

struct Order {
    int OrderId{};
    string CustomerName;
    BillingProduct Products[MAX_PRODUCTS];
    int numProducts{};
    double TotalPrice{};
};

// Forward declaration of countLines()
int countLines();

void addProduct();
void listProduct();
void menu();

void editProductById(int id);
void deleteProductById(int id);

void printHeader() {
    cout << setfill('~')<< setw(60)<< right<<"\n";
    cout << setfill(' ')<< setw(35)<< "   AMBER BAKERY  \n";
}
void printDivider(char i) {
    cout << setw(60) << setfill(i) << "" << "\n";
}

void printMenu() {
    cout << "\n";
    printDivider('=');
    cout << "O - Orders\t\t";
    cout << "P - Products \t\t";
    cout << "U - Users \n";
    cout << "C - Info \t\t";
    cout << "Q - Quit\n";
}
void printTitle(string title) {
    cout<<"\n"<<setfill(' ')<< setw(35)<< right  << title<<"\n";

}

void listProduct() {
    printDivider('=');
    printTitle("List of Products");
    printDivider('-');
    ifstream MyFile("Products.txt");
    if (!MyFile) {
        cout << "Error opening file.\n";
        menu();
        return;
    }

    Product Product;
    cout <<"|  "<<setfill(' ')<< setw(10) << left << "ID " << setw(30) << left << "Name"<< setw(10) << left << "Price"<< setw(7)<< right<<"|"<<"\n";
    printDivider('-');
    while (MyFile >> Product.ProductId >> Product.ProductName >> Product.ProductPrice) {
        cout <<"|  "<< setfill(' ')
             << setw(10) << left  << Product.ProductId
             << setw(30) << left << Product.ProductName
             << setw(10)  << left << Product.ProductPrice << setw(9)<<right<<"|  "<< endl;
    }
    MyFile.close();
    printDivider('-');
    printDivider('=');
    cout << "A - Add Product \t";
    cout << "E - Edit Item\t\t";
    cout << "D - Delete Item\n";
    cout << "M - Main Menu\t\t";
    cout << "Q - Quit\n";
    cout<<"Enter the key: ";
    int id = 0;
    char u ;
    cin>>u;
    cin.ignore();
    switch (u) {
        case 'A':
        case 'a':
            addProduct();
            break;
        case 'E':
        case 'e':
            printDivider('-');
            cout<<"Which id should be edit : ";
            cin>>id;
            editProductById(id);
            break;
        case 'D':
        case 'd':
            printDivider('-');
            cout<<"Which id should be delete : ";
            cin>>id;
            deleteProductById(id);
            break;
        case 'M':
        case 'm':
            menu();
            break;
        default:
            cout << "Invalid selection. Please try again.\n";
            listProduct();
            break;
    }

//    menu();
}
void listOrders() {
    printDivider('=');
    printTitle("List of Orders");
    printDivider('-');
    ifstream MyFile("Orders.txt");
    if (!MyFile) {
        cout << "Error opening file.\n";
        menu();
        return;
    }

    cout << "| " << setfill(' ') << setw(10) << left << "ID"
         << setw(20) << left << "Customer Name" << setw(15) << left << "Total Price" << setw(55) << left << "Order Details" << "|\n";
    printDivider('-');

    int orderId, quantity;
    string customerName, productName;
    double productPrice, totalProductPrice;
    double totalPrice;
    char c;

    while (MyFile >> orderId >> customerName) {
        totalPrice = 0.0;

        cout << "| " << setw(10) << left << orderId << setw(20) << left << customerName;
        cout << setw(15) << left << "$" << fixed << setprecision(2) << totalPrice;

        cout << "[";
        bool isFirstProduct = true;

        while (MyFile >> productName >> c >> productPrice >> c >> quantity) {
            cout << (isFirstProduct ? "" : ", ") << productName << " | " << quantity << " | $" << productPrice;
            isFirstProduct = false;

            totalProductPrice = productPrice * quantity;
            totalPrice += totalProductPrice;
        }
        cout << "]";

        cout << setw(55) << left << "|" << "|\n";

        // Adjust the "Order Details" column width based on the number of characters in each product entry
        MyFile.clear(); // Clear error flags to continue reading the next order
        MyFile.ignore(numeric_limits<streamsize>::max(), '[');
        int detailsWidth = 0;

        while (true) {
            char nextChar = MyFile.peek();
            if (nextChar == ']') {
                MyFile.ignore(); // Ignore the closing bracket
                break;
            }
            MyFile.ignore();
            detailsWidth++;
        }

        cout << setfill(' ') << setw(48) << "";
        cout << "[";

        // Print the "Order Details" column with the correct width
        while (detailsWidth--)
            cout << "-";
        cout << "]|\n";
    }
    MyFile.close();
    printDivider('-');
    printDivider('=');
    cout << "M - Main Menu\t\t";
    cout << "Q - Quit\n";
    cout << "Enter the key: ";
    char u;
    cin >> u;
    cin.ignore();
    switch (u) {
        case 'M':
        case 'm':
            menu();
            break;
        default:
            cout << "Invalid selection. Please try again.\n";
            listOrders();
            break;
    }
}

const int MAX_ORDERS = 100; // Maximum number of orders

int countOrderLines() {
    ifstream MyFile("Orders.txt");
    if (!MyFile) {
        cout << "Error opening file.\n";
        return 0;
    }

    string line;
    int lineCount = 0;
    while (getline(MyFile, line)) {
        lineCount++;
    }
    MyFile.close();
    return lineCount;
}

void deleteProductById(int productId) {
    ifstream MyFile("Products.txt");
    if (!MyFile) {
        cout << "Error opening file.\n";
        return;
    }

    bool foundProduct = false;
    Product product;
    ofstream TempFile("Temp.txt"); // Create a temporary file to store modified data

    while (MyFile >> product.ProductId >> product.ProductName >> product.ProductPrice) {
        if (product.ProductId == productId) {
            foundProduct = true;
            cout << "Product with ID " << productId << " has been deleted.\n";
        } else {
            TempFile << product.ProductId << " " << product.ProductName << " " << product.ProductPrice << endl;
        }
    }

    MyFile.close();
    TempFile.close();

    if (!foundProduct) {
        cout << "Product with ID " << productId << " not found.\n";
        remove("Temp.txt"); // Remove the temporary file if the product was not found
        return;
    }

    // Remove the original file and rename the temporary file
    remove("Products.txt");
    rename("Temp.txt", "Products.txt");
    listProduct();

}
void editProductById(int productId) {
    fstream MyFile("Products.txt");
    if (!MyFile) {
        cout << "Error opening file.\n";
        return;
    }

    bool foundProduct = false;
    Product product;
    ofstream TempFile("Temp.txt"); // Create a temporary file to store modified data

    while (MyFile >> product.ProductId >> product.ProductName >> product.ProductPrice) {
        if (product.ProductId == productId) {
            foundProduct = true;
            cout << "Current Product Details:\n";
            cout << "Product ID: " << product.ProductId << "\n";
            cout << "Product Name: " << product.ProductName << "\n";
            cout << "Product Price: " << product.ProductPrice << "\n";

            cout << "Enter new product name: ";
            cin.ignore();
            getline(cin, product.ProductName);

            cout << "Enter new product price: ";
            cin >> product.ProductPrice;

            TempFile << product.ProductId << " " << product.ProductName << " " << product.ProductPrice << endl;
        } else {
            TempFile << product.ProductId << " " << product.ProductName << " " << product.ProductPrice << endl;
        }
    }

    MyFile.close();
    TempFile.close();

    if (!foundProduct) {
        cout << "Product with ID " << productId << " not found.\n";
        remove("Temp.txt"); // Remove the temporary file if the product was not found
        return;
    }

    // Remove the original file and rename the temporary file
    remove("Products.txt");
    rename("Temp.txt", "Products.txt");

    cout << "Product with ID " << productId << " has been updated successfully.\n";
    listProduct();
}
void addProduct() {
    printDivider('=');
    printTitle("Add new Product");

    ofstream MyFile;
    MyFile.open("Products.txt", ios::out | ios::app); // Open in append mode
    if (!MyFile) {
        cout << "Error opening file.\n";
        menu();
        return;
    }

    int lineCount = countLines();
    Product newProduct;
    newProduct.ProductId = lineCount + 1;

    cout << "Enter the Product's name : ";
    cin.ignore();
    getline(cin, newProduct.ProductName);

    cout << "Enter the Product's price : ";
    cin >> newProduct.ProductPrice;

    MyFile << newProduct.ProductId << "  " << newProduct.ProductName << "  " << newProduct.ProductPrice << endl;
    MyFile.close();

    cout << "\nProduct added successfully!\n";
    listProduct();
}

int countLines() {
    ifstream MyFile("Products.txt");
    if (!MyFile) {
        cout << "Error opening file.\n";
        return 0;
    }

    string line;
    int lineCount = 0;
    while (getline(MyFile, line)) {
        lineCount++;
    }
    MyFile.close();
    return lineCount;
}
void menu() {

    char selection;
    printMenu();
    cout << "Enter the key: ";
    cin >> selection;
    cin.ignore();

    switch (selection) {
        case 'P':
        case 'p':
            listProduct();
            break;
        case 'O':
        case 'o':
            listOrders();
//            addOrder();
            break;
        case 'Q':
        case 'q':
            cout << "Exiting the application.\n";
            break;
        default:
            cout << "Invalid selection. Please try again.\n";
            menu();
    }
}

int main() {
    printHeader();
    menu();
//    listProduct();
    return 0;
}
