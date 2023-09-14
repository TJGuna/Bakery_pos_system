#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
using namespace std;

struct Product {
    string ProductId;
    string ProductName;
    double ProductPrice;
};
struct Package {
    string PackageId;
    string ProductId;
    string PackageName;
    int PackageQuantity;
};
struct Customer {
    string CustomerId;
    string CustomerName;
    string CustomerAddress;
    string CustomerPhone;
};
struct Staff {
    string StaffId;
    string StaffName;
    string StaffAddress;
    string StaffPhone;
    string StaffPassword;
    string StaffRole;
};

struct Order {
    string OrderId;
    string itemId;
    int quantity;
};

Staff currentStaff;
string currentDate;

// Forward declaration of functions
int getDataById(string title);
void menu();
void login();
void addOrder();
void addProduct();
void listProduct();
void listOrder();
void editProductById(string id);
void deleteProductById(string id);
void addCustomer();
void listCustomer();
void editCustomerById(string id);
void deleteCustomerById(string id);
void addStaff();
void listStaff();
void editStaffById(string id);
void deleteStaffById(string id);
void addPackage();
void Billing();
void editPackageById(string id);
void deletePackageById(string id);
void listPackage();
// common functions
void clearScreen(){
    // Clear the terminal screen
    #ifdef _WIN32
        system("cls"); // For Windows
    #else
        system("clear"); // For Unix-like systems
    #endif
};
void animateText(const string text, size_t index = 0) {
    if (index < text.size()) {
        std::cout << text[index] << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Adjust the delay as needed
        animateText(text, index + 1);
    } else {
        std::cout << std::endl;
    }
}
char charValidation(){
    char selection;
    while (cin.fail() || cin.peek() != '\n') {
        cin.clear();// Clear error flags
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
        cout << "Invalid input. Please enter a single character: ";
        cin >> selection;
    }
    return selection;
}
void printHeader() {
    cout << setfill('~')<< setw(60)<< right<<"\n";
    cout << setfill(' ')<< setw(35);
    animateText("   AMBER BAKERY ");
    cout << setfill('~')<< setw(60)<< right<<"\n";
}
void printDivider(char i,int n=60) {
    cout << setw(n) << setfill(i) << "" << "\n";
}
void printMenu() {

    cout << "\n";
    printDivider('=');
    if(currentStaff.StaffRole == "admin"){
        cout << "B - Billing\t\t";
        cout << "O - Orders\t\t";
        cout << "P - Products \t\t";
        cout << "L - Packages \t\t";
        cout << "C - Customers \n";
        cout << "S - Staff \t\t";
        cout << "I - Info \t\t";
        cout << "Z - log out \t\t";
        cout << "Q - Quit\n";
    }else{
        cout << "B - Billing\t\t";
        cout << "O - Orders\t\t";
        cout << "P - Products \t\t";
        cout << "L - Packages \t\t";
        cout << "C - Customers \n";
        cout << "I - Info \t\t";
        cout << "Z - log out \t\t";
        cout << "Q - Quit\n";
    }

}
void printTitle(string title) {
    cout<<"\n"<<setfill(' ')<< setw(35)<< right  << title<<"\n";

}
void list(string title){
    printDivider('=',80);
    printTitle("List of "+title );
    printDivider('-',80);

}
string spaceRemoving(string text){
    for (size_t i = 0; i < text.length(); ++i) {
        if (text[i] == ' ') {
            text[i] = '_';
        }
    }
    return text;
}

// search functions
Product searchNameByProductId(string productId){
    fstream MyFile("Products.txt");
    if (!MyFile) {
        cout << "Error opening file.\n";
//        return "err in file opening";
    }
    Product product;
    while (MyFile >> product.ProductId >> product.ProductName >> product.ProductPrice) {
        if (product.ProductId == productId) {
            return product;
        }
    }
    MyFile.close();
    return product;
}
Customer searchNameByCustomerId(string CustomerId){
    fstream MyFile("Customers.txt");
    if (!MyFile) {
        cout << "Error opening file.\n";
//        return "err in file opening";
    }
    Customer Customer;
    while (MyFile >> Customer.CustomerId >> Customer.CustomerName >> Customer.CustomerAddress >> Customer.CustomerPhone) {
        if (Customer.CustomerId == CustomerId) {
            return Customer;
        }
    }
    MyFile.close();
    return Customer;
}
Package searchNameByPackageId(string PackageId){
    fstream MyFile("Packages.txt");
    if (!MyFile) {
        cout << "Error opening file.\n";
//        return "err in file opening";
    }
    Package Package;
    while (MyFile >> Package.PackageId >> Package.PackageName >> Package.ProductId >> Package.PackageQuantity) {
        if (Package.PackageId == PackageId) {
            return Package;
        }
    }
    MyFile.close();
    return Package;
}
Order searchNameByOrderId(string OrderId){
    fstream MyFile("Orders.txt");
    if (!MyFile) {
        cout << "Error opening file.\n";
//        return "err in file opening";
    }
    Order Order;
    while (MyFile >> Order.OrderId >> Order.itemId >> Order.quantity) {
        if (Order.OrderId == OrderId) {
            return Order;
        }
    }
    MyFile.close();
    return Order;
}

// additional functions
int idSlice(string id){
    return stoi(id.substr(3));
}
double PriceCalc(string id){
    string type ;
    if(id.substr(0,3)=="PRO"){
        type="Product";
    }else if(id.substr(0,3)=="PKG"){
        type="Package";
    }
    fstream MyFile(type+"s.txt");
    if (!MyFile) {
        cout << "Error opening file.\n";
//        return "err in file opening";
    }
    double price = 0;
    if(type=="Product") {
        Product product;
        while (MyFile >> product.ProductId >> product.ProductName >> product.ProductPrice) {
            if (product.ProductId == id) {
                price = product.ProductPrice;
            }
        }
    }else if(type=="Package"){
        Package Package;
        while (MyFile >> Package.PackageId >> Package.PackageName >> Package.ProductId >> Package.PackageQuantity) {
            if (Package.PackageId == id) {
                price = price + (searchNameByProductId(Package.ProductId).ProductPrice * Package.PackageQuantity);
            }
        }
    }
    MyFile.close();
//    return product;
//    if(type=="Product") {
//        return searchNameByProductId(id).ProductPrice*quantity;
//    }else if(type=="Package"){
//        return searchNameByPackageId(id).PackageQuantity*quantity;
//    }
    return price;
}
string  orderTypeCheck(string id){
    if(id.substr(0,3)=="PRO") {
        return searchNameByProductId(id).ProductName;
    }else if(id.substr(0,3)=="PKG"){
        return searchNameByPackageId(id).PackageName;
    }
    return "err";
}
double totalPrice(string PackageId){
    ifstream MyFile("Packages.txt");
    if (!MyFile) {
        cout << "Error opening file.\n";
        return 0;
    }
    Package Package;
    int totalLines = 0;
    double tpp=0;
    while (MyFile >> Package.PackageId >> Package.PackageName >> Package.ProductId >> Package.PackageQuantity) {
        if (Package.PackageId == PackageId) {
            tpp = tpp + (Package.PackageQuantity * searchNameByProductId(Package.ProductId).ProductPrice);
        }
    }
    return tpp;
}
int getDataById(string title) {
    ifstream MyFile(title+".txt");
    if (!MyFile) {
        cout << "Error opening file.\n";
        return 0;
    }
    if (title == "Customers") {
        Customer Customer;
        while (MyFile >>Customer.CustomerId >> Customer.CustomerName >> Customer.CustomerAddress >> Customer.CustomerPhone) {}
        return idSlice(Customer.CustomerId);
    } else if (title == "Products") {
        Product Product;
        while (MyFile >> Product.ProductId >> Product.ProductName >> Product.ProductPrice ) {}
        return idSlice(Product.ProductId);
    }else if (title == "Packages") {
        Package Package;
        while (MyFile >> Package.PackageId >> Package.PackageName >>Package.ProductId>> Package.PackageQuantity  ) {}
        return idSlice(Package.PackageId);
    } else if (title == "Staffs") {
        Staff Staff;
        while (MyFile >> Staff.StaffId >> Staff.StaffName >>Staff.StaffAddress>>Staff.StaffPhone>>Staff.StaffPassword>>Staff.StaffRole ) {}
        return idSlice(Staff.StaffId);
    }else if (title == "Orders") {
        Order Order;
        while (MyFile >> Order.OrderId >> Order.itemId >> Order.quantity ) {}
        return idSlice(Order.OrderId);
    }

//    string line;
//    int lineCount = 0;

//    while (getline(MyFile, line)) {
//        lineCount++;
//    }
    MyFile.close();
    return 0;
}

// main functions

//order functions
void listOrder() {
    list("Orders");
    ifstream MyFile("Orders.txt");
    if (!MyFile) {
        cout << "Error opening file.\n";
        menu();
        return;
    }
    Order Order;
    string OrderId = " ";

    cout <<"|  "<<setfill(' ')<< setw(10) << left << "ID " << setw(10) << left << "Item Id"<< setw(15) << left << "Item"<< setw(10) << left << "Price"<< setw(5) << left << "Qty"<< setw(15) << left << "Sub Total"<< setw(10) << left << "Total"<< setw(7)<< right<<"|"<<"\n";
    printDivider('-',80);
    double total=0;

    while (MyFile >> Order.OrderId >> Order.itemId >> Order.quantity ) {

        if (!(Order.OrderId == OrderId || OrderId == " ")) {
            cout<< "|  " << setfill('~')<< setw(70) << to_string(total).substr(0, to_string(total).find('.')+3)<< setw(9) << right << "|  " << endl;
            total = 0;

        }
        total = total + Order.quantity*PriceCalc(Order.itemId);

        OrderId = Order.OrderId;


        cout << "|  " << setfill(' ')
             << setw(10) << left << Order.OrderId
             << setw(10) << left << Order.itemId
             << setw(15) << left << orderTypeCheck(Order.itemId)
             << setw(10) << left <<to_string(PriceCalc(Order.itemId)).substr(0,to_string(PriceCalc(Order.itemId)).find('.')+3)
             << setw(5) << left << Order.quantity
             << setw(10) << left << to_string(Order.quantity*PriceCalc(Order.itemId)).substr(0,to_string(Order.quantity*PriceCalc(Order.itemId)).find('.')+3)
             << setw(19) << right << "|  " << endl;

//                to_string(searchNameByProductId(Package.ProductId).ProductPrice).substr(0,to_string(searchNameByProductId(Package.ProductId).ProductPrice).length()-4)


    }
    cout<< "|  " << setfill('~')<< setw(70) << to_string(total).substr(0, to_string(total).find('.')+3)<< setw(9) << right << "|  " << endl;
    MyFile.close();
//    printDivider('-');
    printDivider('=');
    cout << "A - Add Order \t";
    cout << "E - Edit Order\t\t";
    cout << "D - Delete Order\n";
    cout << "M - Main Menu\t\t";
    cout << "Q - Quit\n";
    cout<<"Enter the key: ";
    string id = "0";
    char u ;
    cin>>u;
    cin.ignore();
    switch (u) {
        case 'A':
        case 'a':
            addOrder();
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
void addOrder() {
    printDivider('=');
    printTitle("Add new Order");

    ofstream MyFile;
    MyFile.open("Orders.txt", ios::out | ios::app); // Open in append mode
    if (!MyFile) {
        cout << "Error opening file.\n";
        menu();
        return;
    }

    int lineCount = getDataById("Orders");
    Order newOrder;
    newOrder.OrderId = "ORD"+to_string(lineCount + 1);
    int numberOfItems=1;
    int runningCount = 0;
//    getline(cin, newOrder.OrderId);
    cout << "How many products need to add : ";
    cin >> numberOfItems;
    while(numberOfItems > runningCount){
        cout << "Enter the Order's info - ItemId : ";
        cin >> newOrder.itemId;
        cout << "Enter the product's quantity : ";
        cin >> newOrder.quantity;
        MyFile << newOrder.OrderId << "  " << newOrder.itemId << "  "<<newOrder.quantity << endl;
        runningCount++;
    }
    MyFile.close();

    cout << "\nOrder added successfully!\n";
    listOrder();
}
//

//product functions
void listProduct() {
    list("Products");
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
    string id = "0";
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
        case 'Q':
        case 'q':
            cout << "Exiting the application.\n";
            break;
        default:
            cout << "Invalid selection. Please try again.\n";
            listProduct();
            break;
    }

//    menu();
}
void deleteProductById(string Id) {
    int productId = idSlice(Id);
    ifstream MyFile("Products.txt");
    if (!MyFile) {
        cout << "Error opening file.\n";
        return;
    }

    bool foundProduct = false;
    Product product;
    ofstream TempFile("Temp.txt"); // Create a temporary file to store modified data

    while (MyFile >> product.ProductId >> product.ProductName >> product.ProductPrice) {
        if (product.ProductId == Id) {
            foundProduct = true;
            cout << "Product with ID " << Id << " has been deleted.\n";
        } else {
            TempFile << product.ProductId << " " << product.ProductName << " " << product.ProductPrice << endl;
        }
    }

    MyFile.close();
    TempFile.close();

    if (!foundProduct) {
        cout << "Product with ID " << Id << " not found.\n";
        remove("Temp.txt"); // Remove the temporary file if the product was not found
        return;
    }

    // Remove the original file and rename the temporary file
    remove("Products.txt");
    rename("Temp.txt", "Products.txt");
    listProduct();

}
void editProductById(string productId) {
    int Id = idSlice(productId);
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

    int lineCount = getDataById("Products");
    Product newProduct;
    newProduct.ProductId = "PRO"+to_string(lineCount + 1);

    cout << "Enter the Product's name : ";
    getline(cin, newProduct.ProductName);

    cout << "Enter the Product's price : ";
    cin >> newProduct.ProductPrice;

    MyFile << newProduct.ProductId << "  " << newProduct.ProductName << "  " << newProduct.ProductPrice << endl;
    MyFile.close();

    cout << "\nProduct added successfully!\n";
    listProduct();
}

//package functions
void listPackage() {
    list("Packages");
    ifstream MyFile("Packages.txt");
    if (!MyFile) {
        cout << "Error opening file.\n";
        menu();
        return;
    }
    Package Package;
    cout <<"|  "<<setfill(' ')<< setw(10) << left << "ID " << setw(10) << left << "Name"<< setw(10) << left << "Product Name"<< setw(20) << left<< "Price"<< setw(10) << left<< "Quantity"<< setw(10) << left << "Sub Total"<< setw(10) << left << "Total"<< setw(7)<< right<<"|"<<"\n";
    printDivider('-', 90);
    string PackageId = " ";
    while (MyFile >> Package.PackageId >> Package.PackageName >> Package.ProductId >> Package.PackageQuantity) {
        bool totalPriceDisplay = false;
        if(PackageId == " "){
            totalPriceDisplay = true;
        }else if( PackageId == Package.PackageId ){
            totalPriceDisplay = false;
        }else{
            printDivider('~', 90);
            totalPriceDisplay = true;
        }
        PackageId = Package.PackageId;

        cout <<"|  "<< setfill(' ')
             << setw(10) << left  << Package.PackageId
             << setw(20) << left << Package.PackageName
             << setw(10) << left << searchNameByProductId(Package.ProductId).ProductName
             << setw(10) << left << to_string(searchNameByProductId(Package.ProductId).ProductPrice).substr(0,to_string(searchNameByProductId(Package.ProductId).ProductPrice).length()-4)
             << setw(10)  << left << Package.PackageQuantity
             << setw(10) << left << to_string(searchNameByProductId(Package.ProductId).ProductPrice * Package.PackageQuantity).substr(0,to_string(searchNameByProductId(Package.ProductId).ProductPrice * Package.PackageQuantity).length()-4)
             << setw(10) << left << (totalPriceDisplay  ? to_string(totalPrice(Package.PackageId)).substr(0,to_string(totalPrice(Package.PackageId)).length()-4):" ")
             << setw(9)<<right<<"|  "<< endl;


    }
    MyFile.close();
    printDivider('-');
    printDivider('=');
    cout << "A - Add Package \t";
    cout << "E - Edit Item\t\t";
    cout << "D - Delete Item\n";
    cout << "M - Main Menu\t\t";
    cout << "Q - Quit\n";
    cout<<"Enter the key: ";
    string id = " ";
    char u ;
    cin>>u;
    cin.ignore();
    switch (u) {
        case 'A':
        case 'a':
            addPackage();
            break;
        case 'E':
        case 'e':
            printDivider('-');
            cout<<"Which id should be edit : ";
            cin>>id;
            editPackageById(id);
            break;
        case 'D':
        case 'd':
            printDivider('-');
            cout<<"Which id should be delete : ";
            cin>>id;
            deletePackageById(id);
            break;
        case 'M':
        case 'm':
            menu();
            break;
        default:
            cout << "Invalid selection. Please try again.\n";
            listPackage();
            break;
    }

//    menu();
}
void deletePackageById(string Id) {
    int PackageId = idSlice(Id);
    ifstream MyFile("Packages.txt");
    if (!MyFile) {
        cout << "Error opening file.\n";
        return;
    }

    bool foundPackage = false;
    Package Package;
    ofstream TempFile("Temp.txt"); // Create a temporary file to store modified data

    while (MyFile >> Package.PackageId >> Package.PackageName >> Package.ProductId >> Package.PackageQuantity) {
        if (Package.PackageId == Id) {
            foundPackage = true;
            cout << "Package with ID " << Id << " has been deleted.\n";
        } else {
            TempFile << Package.PackageId << " " << Package.PackageName << " " << Package.ProductId <<" " << Package.PackageQuantity<< endl;
        }
    }

    MyFile.close();
    TempFile.close();

    if (!foundPackage) {
        cout << "Package with ID " << Id << " not found.\n";
        remove("Temp.txt"); // Remove the temporary file if the Package was not found
        return;
    }

    // Remove the original file and rename the temporary file
    remove("Packages.txt");
    rename("Temp.txt", "Packages.txt");
    listPackage();

}
void editPackageById(string PackageId) {
    int Id = idSlice(PackageId);
    fstream MyFile("Packages.txt");
    if (!MyFile) {
        cout << "Error opening file.\n";
        return;
    }

    bool foundPackage = false;
    string PackageName;
    Package package;
    ofstream TempFile("Temp.txt"); // Create a temporary file to store modified data
    cout << "Enter new Package name: ";
    cin.ignore();
    getline(cin, PackageName);
    for (size_t i = 0; i < package.PackageName.length(); ++i) {
        if (package.PackageName[i] == ' ') {
            package.PackageName[i] = '_';
        }
    }
    while (MyFile >> package.PackageId >> package.PackageName >> package.ProductId >> package.PackageQuantity) {

        if (package.PackageId == PackageId) {
            foundPackage = true;

            cout << "Enter new Product Id: ";
            cin >> package.ProductId;
            cout << "Enter the Quantity: ";
            cin >> package.PackageQuantity;
            TempFile << package.PackageId << " " << PackageName << " " << package.ProductId<< " " << package.PackageQuantity << endl;
            cout << package.PackageId << " " << PackageName << " " << package.ProductId<< " " << package.PackageQuantity << endl;
        } else {
            TempFile << package.PackageId << " " << package.PackageName << " " << package.ProductId<< " " << package.PackageQuantity << endl;
        }
    }

    MyFile.close();
    TempFile.close();

    if (!foundPackage) {
        cout << "Package with ID " << PackageId << " not found.\n";
        remove("Temp.txt"); // Remove the temporary file if the Package was not found
        return;
    }

    // Remove the original file and rename the temporary file
    remove("Packages.txt");
    rename("Temp.txt", "Packages.txt");

    cout << "Package with ID " << PackageId << " has been updated successfully.\n";
    listPackage();
}
void addPackage() {
    printDivider('=');
    printTitle("Add new Package");
    ofstream MyFile;
    MyFile.open("Packages.txt", ios::out | ios::app); // Open in append mode
    if (!MyFile) {
        cout << "Error opening file.\n";
        menu();
        return;
    }
    int lineCount = getDataById("Packages");
    Package newPackage;
    newPackage.PackageId = "PKG"+to_string(lineCount + 1);
    int numberOfProcucts=1;
    int runningCount = 0;
    cout << "Enter the Package's name : ";
    getline(cin, newPackage.PackageName);
    for (size_t i = 0; i < newPackage.PackageName.length(); ++i) {
        if (newPackage.PackageName[i] == ' ') {
            newPackage.PackageName[i] = '_';
        }
    }
    cout << "How many products need to add : ";
    cin >> numberOfProcucts;
    while(numberOfProcucts > runningCount){
        cout << "Enter the Package's info - productId : ";
        cin >> newPackage.ProductId;
        cout << "Enter the product's quantity : ";
        cin >> newPackage.PackageQuantity;
        MyFile << newPackage.PackageId << "  " << newPackage.PackageName << "  " << newPackage.ProductId << "  "<<newPackage.PackageQuantity << endl;
        runningCount++;
    }
    MyFile.close();
    cout << "\nPackage added successfully!\n";
    listPackage();
}

//customer functions
void listCustomer() {
    list("Customers");
    ifstream MyFile("Customers.txt");
    if (!MyFile) {
        cout << "Error opening file.\n";
        menu();
        return;
    }
    Customer Customer;
    cout <<"|  "<<setfill(' ')<< setw(10) << left << "ID " << setw(30) << left << "Name"<< setw(10) << left << "Address"<< setw(10) << left << "Phone"<< setw(7)<< right<<"|"<<"\n";
    printDivider('-');
    while (MyFile >> Customer.CustomerId >> Customer.CustomerName >> Customer.CustomerAddress >> Customer.CustomerPhone) {
        cout <<"|  "<< setfill(' ')
             << setw(10) << left  << Customer.CustomerId
             << setw(30) << left << Customer.CustomerName
             << setw(30) << left << Customer.CustomerAddress
             << setw(10)  << left << Customer.CustomerPhone << setw(9)<<right<<"|  "<< endl;
    }
    MyFile.close();
    printDivider('-');
    printDivider('=');
    cout << "A - Add Customer \t";
    cout << "E - Edit Customer\t\t";
    cout << "D - Delete Customer\n";
    cout << "M - Main Menu\t\t";
    cout << "Q - Quit\n";
    cout<<"Enter the key: ";
    string id = "0";
    char u ;
    cin>>u;
    cin.ignore();
    switch (u) {
        case 'A':
        case 'a':
            addCustomer();
            break;
        case 'E':
        case 'e':
            printDivider('-');
            cout<<"Which id should be edit : ";
            cin>>id;
            editCustomerById(id);
            break;
        case 'D':
        case 'd':
            printDivider('-');
            cout<<"Which id should be delete : ";
            cin>>id;
            deleteCustomerById(id);
            break;
        case 'M':
        case 'm':
            menu();
            break;
        default:
            cout << "Invalid selection. Please try again.\n";
            listCustomer();
            break;
    }

//    menu();
}
void deleteCustomerById(string CustomerId) {
    ifstream MyFile("Customers.txt");
    if (!MyFile) {
        cout << "Error opening file.\n";
        return;
    }

    bool foundCustomer = false;
    Customer Customer;
    ofstream TempFile("Temp.txt"); // Create a temporary file to store modified data

    while (MyFile >> Customer.CustomerId >> Customer.CustomerName >> Customer.CustomerAddress >> Customer.CustomerPhone) {
        if (Customer.CustomerId == CustomerId) {
            foundCustomer = true;
            cout << "Customer with ID " << CustomerId << " has been deleted.\n";
        } else {
            TempFile << Customer.CustomerId << " " << Customer.CustomerName << " " << Customer.CustomerAddress<<" "<< Customer.CustomerPhone<< endl;
        }
    }

    MyFile.close();
    TempFile.close();

    if (!foundCustomer) {
        cout << "Customer with ID " << CustomerId << " not found.\n";
        remove("Temp.txt"); // Remove the temporary file if the Customer was not found
        return;
    }

    // Remove the original file and rename the temporary file
    remove("Customers.txt");
    rename("Temp.txt", "Customers.txt");
    listCustomer();

}
void editCustomerById(string CustomerId) {
    fstream MyFile("Customers.txt");
    if (!MyFile) {
        cout << "Error opening file.\n";
        return;
    }

    bool foundCustomer = false;
    Customer Customer;
    ofstream TempFile("Temp.txt"); // Create a temporary file to store modified data

    while (MyFile >> Customer.CustomerId >> Customer.CustomerName >> Customer.CustomerAddress >> Customer.CustomerPhone) {
        if (Customer.CustomerId == CustomerId) {
            foundCustomer = true;
            cout << "Current Customer Details:\n";
            cout << "Customer ID: " << Customer.CustomerId << "\n";
            cout << "Customer Name: " << Customer.CustomerName << "\n";
            cout << "Customer Adress: " << Customer.CustomerAddress << "\n";
            cout << "Customer Phone: " << Customer.CustomerPhone << "\n";

            cout << "Enter new Customer name: ";
            cin.ignore();
            getline(cin, Customer.CustomerName);

            cout << "Enter new Customer Address: ";
            cin >> Customer.CustomerAddress;
            cout << "Enter new Customer Phone: ";
            cin >> Customer.CustomerPhone;

            TempFile << Customer.CustomerId << " " << Customer.CustomerName << " " << Customer.CustomerAddress<<" " <<Customer.CustomerPhone << endl;
        } else {
            TempFile << Customer.CustomerId << " " << Customer.CustomerName << " " << Customer.CustomerAddress <<" "<< Customer.CustomerPhone << endl;
        }
    }

    MyFile.close();
    TempFile.close();

    if (!foundCustomer) {
        cout << "Customer with ID " << CustomerId << " not found.\n";
        remove("Temp.txt"); // Remove the temporary file if the Customer was not found
        return;
    }

    // Remove the original file and rename the temporary file
    remove("Customers.txt");
    rename("Temp.txt", "Customers.txt");

    cout << "Customer with ID " << CustomerId << " has been updated successfully.\n";
    listCustomer();
}
void addCustomer() {
    printDivider('=');
    printTitle("Add new Customer");

    ofstream MyFile;
    MyFile.open("Customers.txt", ios::out | ios::app); // Open in append mode
    if (!MyFile) {
        cout << "Error opening file.\n";
        menu();
        return;
    }

    int lineCount = getDataById("Customers");
    Customer newCustomer;
    newCustomer.CustomerId = "CUS"+to_string(lineCount + 1);

    cout << "Enter the Customer's name : ";
//    cin.ignore();
    getline(cin, newCustomer.CustomerName);

    cout << "Enter the Customer's Address : ";
    cin >> newCustomer.CustomerAddress;
    cout << "Enter the Customer's Phone : ";
    cin >> newCustomer.CustomerPhone;
    MyFile << newCustomer.CustomerId << "  " << newCustomer.CustomerName << "  " << newCustomer.CustomerAddress<< "  "<<newCustomer.CustomerPhone << endl;
    MyFile.close();

    cout << "\nCustomer added successfully!\n";
    listCustomer();
}

//staff functions
void listStaff() {
    list("Staffs");
    ifstream MyFile("Staffs.txt");
    if (!MyFile) {
        cout << "Error opening file.\n";
        menu();
        return;
    }
    Staff Staff;
    cout <<"|  "<<setfill(' ')<< setw(10) << left << "ID " << setw(30) << left << "Name"<< setw(10) << left << "Address"<< setw(10) << left << "Phone"<< setw(7)<< right<<"|"<<"\n";
    printDivider('-');
    while (MyFile >> Staff.StaffId >> Staff.StaffName >> Staff.StaffAddress >> Staff.StaffPhone >>Staff.StaffPassword>> Staff.StaffRole) {
        cout <<"|  "<< setfill(' ')
             << setw(10) << left  << Staff.StaffId
             << setw(30) << left << Staff.StaffName
             << setw(30) << left << Staff.StaffAddress
             << setw(10)  << left << Staff.StaffPhone << setw(9)<<right<<"|  "<< endl;
    }
    MyFile.close();
    printDivider('-');
    printDivider('=');
    cout << "A - Add Staff \t";
    cout << "E - Edit Staff\t\t";
    cout << "D - Delete Staff\n";
    cout << "M - Main Menu\t\t";
    cout << "Q - Quit\n";
    cout<<"Enter the key: ";
    string id = "0";
    char u ;
    cin>>u;
    charValidation();
    cin.ignore();
    switch (u) {
        case 'A':
        case 'a':
            addStaff();
            break;
        case 'E':
        case 'e':
            printDivider('-');
            cout<<"Which id should be edit : ";
            cin>>id;
            editStaffById(id);
            break;
        case 'D':
        case 'd':
            printDivider('-');
            cout<<"Which id should be delete : ";
            cin>>id;
            deleteStaffById(id);
            break;
        case 'M':
        case 'm':
            menu();
            break;
        default:
            cout << "Invalid selection. Please try again.\n";
            listStaff();
            break;
    }

//    menu();
}
void deleteStaffById(string StaffId) {
    ifstream MyFile("Staffs.txt");
    if (!MyFile) {
        cout << "Error opening file.\n";
        return;
    }

    bool foundStaff = false;
    Staff Staff;
    ofstream TempFile("Temp.txt"); // Create a temporary file to store modified data

    while (MyFile >> Staff.StaffId >> Staff.StaffName >> Staff.StaffAddress >> Staff.StaffPhone >> Staff.StaffPassword>>Staff.StaffRole) {
        if (Staff.StaffId == StaffId) {
            foundStaff = true;
            cout << "Staff with ID " << StaffId << " has been deleted.\n";
        } else {
            TempFile << Staff.StaffId << " " << Staff.StaffName << " " << Staff.StaffAddress<< " " << Staff.StaffPhone << " " <<Staff.StaffPassword << " " << Staff.StaffRole<< endl;
        }
    }
    MyFile.close();
    TempFile.close();

    if (!foundStaff) {
        cout << "Staff with ID " << StaffId << " not found.\n";
        remove("Temp.txt"); // Remove the temporary file if the Staff was not found
        return;
    }

    // Remove the original file and rename the temporary file
    remove("Staffs.txt");
    rename("Temp.txt", "Staffs.txt");
    listStaff();
}
void editStaffById(string StaffId) {
    fstream MyFile("Staffs.txt");
    if (!MyFile) {
        cout << "Error opening file.\n";
        return;
    }

    bool foundStaff = false;
    Staff Staff;
    ofstream TempFile("Temp.txt"); // Create a temporary file to store modified data

    while (MyFile >> Staff.StaffId >> Staff.StaffName >> Staff.StaffAddress >> Staff.StaffPhone >> Staff.StaffPassword >> Staff.StaffRole) {
        if (Staff.StaffId == StaffId) {
            foundStaff = true;
            cout << "Current Staff Details:\n";
            cout << "Staff Role: " << Staff.StaffRole << "\n";
            cout << "Staff ID: " << Staff.StaffId << "\n";
            cout << "Staff Name: " << Staff.StaffName << "\n";
            cout << "Staff Address: " << Staff.StaffAddress << "\n";
            cout << "Staff Phone: " << Staff.StaffPhone << "\n";
            cout << "Staff Password: " << Staff.StaffPassword << "\n";

            cout << "Enter new Staff name: ";
            cin >> Staff.StaffName;
            cout << "Enter new Staff Role: ";
            cin >> Staff.StaffRole;
            cout << "Enter new Staff Address: ";
            cin >> Staff.StaffAddress;
            cout << "Enter new Staff Phone: ";
            cin >> Staff.StaffPhone;
            cout << "Enter new Staff Password: ";
            cin >> Staff.StaffPassword;

            TempFile << Staff.StaffId << " " << Staff.StaffName << " " << Staff.StaffAddress<< " "<<Staff.StaffPhone <<" "<<Staff.StaffPassword<<" "<<Staff.StaffRole<< endl;
        } else {
            TempFile << Staff.StaffId << " " << Staff.StaffName << " " << Staff.StaffAddress << " "<< Staff.StaffPhone <<" "<<Staff.StaffPassword<<" "<<Staff.StaffRole<< endl;
        }
    }

    MyFile.close();
    TempFile.close();

    if (!foundStaff) {
        cout << "Staff with ID " << StaffId << " not found.\n";
        remove("Temp.txt"); // Remove the temporary file if the Staff was not found
        return;
    }

    // Remove the original file and rename the temporary file
    remove("Staffs.txt");
    rename("Temp.txt", "Staffs.txt");

    cout << "Staff with ID " << StaffId << " has been updated successfully.\n";
    listStaff();
}
void addStaff() {
    printDivider('=');
    printTitle("Add new Staff");

    ofstream MyFile;
    MyFile.open("Staffs.txt", ios::out | ios::app); // Open in append mode
    if (!MyFile) {
        cout << "Error opening file.\n";
        menu();
        return;
    }

    int lineCount = getDataById("Staffs");
    Staff newStaff;
    cout << lineCount;
    newStaff.StaffId = "STF"+to_string(lineCount + 1);
    cout << "Enter the Staff's Role : ";
    cin >> newStaff.StaffRole;
    cout << "Enter the Staff's name : ";
//    cin >> newStaff.StaffName;
    cin.ignore();
    getline(cin,newStaff.StaffName);
    for (size_t i = 0; i < newStaff.StaffName.length(); ++i) {
        if (newStaff.StaffName[i] == ' ') {
            newStaff.StaffName[i] = '_';
        }
    }

    cout << "Enter the Staff's Address : ";
    cin >> newStaff.StaffAddress;
    cout << "Enter the Staff's Phone : ";
    cin >> newStaff.StaffPhone;
    cout << "Enter the Staff's Password : ";
    cin >> newStaff.StaffPassword;
    MyFile << newStaff.StaffId << "  " << newStaff.StaffName << "  " << newStaff.StaffAddress << "  "<< newStaff.StaffPhone <<" "<< newStaff.StaffPassword <<" "<< newStaff.StaffRole<< endl;
    MyFile.close();
    cout << "\nStaff added successfully!\n";
    listStaff();
}

void info(){
    printf("Company Name: Amber Bakery\n");
    printf("Company Type: Bakery\n");
    printf("Company Registration Number: 12345-ABCDE\n");
    printf("Company Address: 123 Main Street, City, Country\n");
    printf("Company Phone: +1 (123) 456-7890\n");
    printf("Company Email: info@amberbakery.com\n");
    printf("Company Website: https://www.amberbakery.com\n");
    printf("Operating Hours: Mon-Fri 8:00 AM - 6:00 PM, Sat 9:00 AM - 4:00 PM\n");
    printf("About Us: Amber Bakery is a family-owned bakery specializing in artisanal bread and pastries. We use only the finest ingredients to bring you the freshest and most delicious baked goods. Our bakery has been serving the community for over 20 years, and we take pride in our commitment to quality and customer satisfaction. We offer a wide range of products, from traditional baguettes to custom-designed cakes for special occasions. Thank you for choosing Amber Bakery!\n");
    std::cout << "\n\n\nPress any Enter key ";
    // Keep reading characters until Enter is pressed
    getchar();
    menu();

}
void instructions(){
    cout << "Welcome to Amber Bakery - Instructions" << endl;
    cout << "--------------------------------------" << endl;
    cout << "Amber Bakery is a simple bakery management system." << endl;
    cout << "Here are the available options and how to use them:" << endl;
    cout << "1. Display Bakery Items: View the list of available bakery items." << endl;
    cout << "2. Add Bakery Items: Add a new bakery item to the inventory." << endl;
    cout << "3. Update Bakery Items: Update the details of existing bakery items." << endl;
    cout << "4. Delete Bakery Items: Remove bakery items from the inventory." << endl;
    cout << "5. Manage Orders: Create and manage customer orders." << endl;
    cout << "6. Customer Management: Add, edit, and delete customer information." << endl;
    cout << "7. Staff Management: Add, edit, and delete staff information." << endl;
    cout << "8. Billing: Calculate and finalize customer bills." << endl;
    cout << "9. Exit: Close the program." << endl;
    cout << "--------------------------------------" << endl;
    cout << "To select an option, enter the corresponding letter and press Enter." << endl;
    cout << "Follow the on-screen prompts to complete your desired task." << endl;
    cout << "--------------------------------------" << endl;
}
//main functions
void menu() {
    clearScreen();
    char selection;
    printMenu();
    cout << "Enter the key: ";
    cin >> selection;
//    cin.ignore();
    charValidation();
if(currentStaff.StaffRole == "admin"){
    switch (selection) {
        case 'P':
        case 'p':
            listProduct();
            break;
        case 'l':
        case 'L':
            listPackage();
            break;
        case 'S':
        case 's':
            listStaff();
            break;
        case 'C':
        case 'c':
            listCustomer();
            break;
        case 'B':
        case 'b':
            Billing();
            break;
        case 'O':
        case 'o':
            listOrder();
//            addOrder();
            break;
        case 'I':
        case 'i':
            info();
            break;
        case 'Q':
        case 'q':
            cout << "Exiting the application.\n";
            break;
        case 'Z':
        case 'z':
            login();
            break;
        default:
            cout << "Invalid selection. Please try again.\n";
            menu();
    }
}else{
    switch (selection) {
        case 'P':
        case 'p':
            listProduct();
            break;
        case 'l':
        case 'L':
            listPackage();
            break;
        case 'C':
        case 'c':
            listCustomer();
            break;
        case 'B':
        case 'b':
            Billing();
            break;
        case 'O':
        case 'o':
            listOrder();
//            addOrder();
            break;
        case 'I':
        case 'i':
            info();
            break;
        case 'Q':
        case 'q':
            cout << "Exiting the application.\n";
            break;
        case 'Z':
        case 'z':
            login();
            break;
        default:
            cout << "Invalid selection. Please try again.\n";
            menu();
    }

}
}
void login(){
    string username, password;
    animateText( "Please enter your username: ");
    cin >> username;
    animateText( "Please enter your password: ");
    cin >> password;
    ifstream MyFile("Staffs.txt");
    if (!MyFile) {
        cout << "Error opening file.\n";
        menu();
        return;
    }
    Staff Staff;
    printDivider('-');
    while (MyFile >> Staff.StaffId >> Staff.StaffName >> Staff.StaffAddress >> Staff.StaffPhone >> Staff.StaffPassword >> Staff.StaffRole) {
        if(Staff.StaffName==username && Staff.StaffPassword==password){
            cout << "Login successfully!\n";
            currentStaff = Staff;

            return menu();
        } else{
            clearScreen();
            animateText( "Login failed!\nCheck your username and password\n");
            login();
        }
    }
    MyFile.close();

}
void Billing(){
    cout<<"Enter Customer ID: ";
    string CustomerId;
    cin>>CustomerId;
    cout<<"Enter Order ID: ";
    string OrderId;
    cin>>OrderId;
    Customer Customer = searchNameByCustomerId(CustomerId);
    list("Billing");
    ifstream MyFile("Orders.txt");
    if (!MyFile) {
        cout << "Error opening file.\n";
        menu();
        return;
    }
    Order Order;

    cout <<"|  "<<setfill(' ')<< setw(10) << left << "Name : " << setw(35) << left << Customer.CustomerName<< setw(10) << left << "Contact No : " << setw(10) << left << Customer.CustomerPhone<< setw(7)<< right<<"|"<<"\n";
    printDivider('-',80);
    cout <<"|  "<<setfill(' ')<< setw(10) << left << "ID " << setw(10) << left << "Item Id"<< setw(15) << left << "Item"<< setw(10) << left << "Price"<< setw(5) << left << "Qty"<< setw(10) << left << "Sub Total"<< setw(15) << left << "Total"<< setw(7)<< right<<"|"<<"\n";
    printDivider('-',80);
    double total=0;

    while (MyFile >> Order.OrderId >> Order.itemId >> Order.quantity ) {

//        OrderId = Order.OrderId;

        if (Order.OrderId == OrderId) {
            total = total + Order.quantity*PriceCalc(Order.itemId);

            cout << "|  " << setfill(' ')
                 << setw(10) << left << Order.OrderId
                 << setw(10) << left << Order.itemId
                 << setw(15) << left << orderTypeCheck(Order.itemId)
                 << setw(10) << left
                 << to_string(PriceCalc(Order.itemId)).substr(0, to_string(PriceCalc(Order.itemId)).find('.') + 3)
                 << setw(5) << left << Order.quantity
                 << setw(10) << left << to_string(Order.quantity * PriceCalc(Order.itemId)).substr(0, to_string(
                    Order.quantity * PriceCalc(Order.itemId)).find('.') + 3)
                 << setw(19) << right << "|  " << endl;
        }
    }
    cout<< "|  " << setfill('~')<< setw(70) << to_string(total).substr(0, to_string(total).find('.')+3)<< setw(9) << right << "|  " << endl;
    cout <<"|  "<<setfill(' ')<< setw(10) << left << "Date : " << setw(35) << left << currentDate << setw(10) << left << "Billed By : " << setw(10) << left << currentStaff.StaffName<< setw(7)<< right<<"|"<<"\n";
    printDivider('-',80);
    MyFile.close();
    menu();
}
int main() {
    instructions();
    std::time_t now = std::time(nullptr);
    std::tm* local_time = std::localtime(&now);
    int year = local_time->tm_year + 1900; // tm_year is the year since 1900
    int month = local_time->tm_mon + 1;    // tm_mon is zero-based, so add 1
    int day = local_time->tm_mday;
    currentDate = to_string(year) + "-" + to_string(month) + "-" + to_string(day);
    printHeader();
    login();
//menu();
//info();
//instructions();
return 0;
}
