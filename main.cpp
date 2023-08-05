#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>

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
//struct Billing {
//    int BillingId;
//    Order orders[];
//    double price;
//};
Staff currentStaff;
string currentDate;
int idSlice(string id){
    return stoi(id.substr(3));
}

// Forward declaration of getDataById()
int getDataById(string title);
void menu();

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

void printHeader() {
    cout << setfill('~')<< setw(60)<< right<<"\n";
    cout << setfill(' ')<< setw(35)<< "   AMBER BAKERY  \n";
}
void printDivider(char i,int n=60) {
    cout << setw(n) << setfill(i) << "" << "\n";
}
void printMenu() {
    cout << "\n";
    printDivider('=');
    cout << "B - Billing\t\t";
    cout << "O - Orders\t\t";
    cout << "P - Products \t\t";
    cout << "L - Packages \t\t";
    cout << "C - Customers \n";
    cout << "S - Staff \t\t";
    cout << "I - Info \t\t";
    cout << "Q - Quit\n";
}
void printTitle(string title) {
    cout<<"\n"<<setfill(' ')<< setw(35)<< right  << title<<"\n";

}
void list(string title){
    printDivider('=',80);
    printTitle("List of "+title );
    printDivider('-',80);

}
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
        default:
            cout << "Invalid selection. Please try again.\n";
            listProduct();
            break;
    }

//    menu();
}

string  orderTypeCheck(string id){
    if(id.substr(0,3)=="PRO") {
        return searchNameByProductId(id).ProductName;
    }else if(id.substr(0,3)=="PKG"){
        return searchNameByPackageId(id).PackageName;
    }
    return "err";
}
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
    int id = 0;
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
//            editPackageById(id);
            break;
        case 'D':
        case 'd':
            printDivider('-');
            cout<<"Which id should be delete : ";
            cin>>id;
//            deletePackageById(id);
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
    newPackage.PackageId = lineCount + 1;
    int numberOfProcucts=1;
    int runningCount = 0;
    cout << "Enter the Package's name : ";
    getline(cin, newPackage.PackageName);
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
void addOrder() {
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
    ifstream MyFile("Customer.txt");
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
            TempFile << Customer.CustomerId << " " << Customer.CustomerName << " " << Customer.CustomerAddress<< Customer.CustomerPhone<< endl;
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

            TempFile << Customer.CustomerId << " " << Customer.CustomerName << " " << Customer.CustomerAddress<<Customer.CustomerPhone << endl;
        } else {
            TempFile << Customer.CustomerId << " " << Customer.CustomerName << " " << Customer.CustomerAddress << Customer.CustomerPhone << endl;
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
    while (MyFile >> Staff.StaffId >> Staff.StaffName >> Staff.StaffAddress >> Staff.StaffPhone) {
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
    ifstream MyFile("Staff.txt");
    if (!MyFile) {
        cout << "Error opening file.\n";
        return;
    }

    bool foundStaff = false;
    Staff Staff;
    ofstream TempFile("Temp.txt"); // Create a temporary file to store modified data

    while (MyFile >> Staff.StaffId >> Staff.StaffName >> Staff.StaffAddress >> Staff.StaffPhone) {
        if (Staff.StaffId == StaffId) {
            foundStaff = true;
            cout << "Staff with ID " << StaffId << " has been deleted.\n";
        } else {
            TempFile << Staff.StaffId << " " << Staff.StaffName << " " << Staff.StaffAddress<< Staff.StaffPhone<< endl;
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

    while (MyFile >> Staff.StaffId >> Staff.StaffName >> Staff.StaffAddress >> Staff.StaffPhone) {
        if (Staff.StaffId == StaffId) {
            foundStaff = true;
            cout << "Current Staff Details:\n";
            cout << "Staff ID: " << Staff.StaffId << "\n";
            cout << "Staff Name: " << Staff.StaffName << "\n";
            cout << "Staff Adress: " << Staff.StaffAddress << "\n";
            cout << "Staff Phone: " << Staff.StaffPhone << "\n";

            cout << "Enter new Staff name: ";
            cin.ignore();
            getline(cin, Staff.StaffName);

            cout << "Enter new Staff Address: ";
            cin >> Staff.StaffAddress;
            cout << "Enter new Staff Phone: ";
            cin >> Staff.StaffPhone;

            TempFile << Staff.StaffId << " " << Staff.StaffName << " " << Staff.StaffAddress<<Staff.StaffPhone << endl;
        } else {
            TempFile << Staff.StaffId << " " << Staff.StaffName << " " << Staff.StaffAddress << Staff.StaffPhone << endl;
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
    if(currentStaff.StaffRole == "admin"){
            ofstream MyFile;
            MyFile.open("Staffs.txt", ios::out | ios::app); // Open in append mode
            if (!MyFile) {
                cout << "Error opening file.\n";
                menu();
                return;
            }

            int lineCount = getDataById("Staffs");
            Staff newStaff;
            newStaff.StaffId = "STF"+to_string(lineCount + 1);

            cout << "Enter the Staff's name : ";
//    cin.ignore();
            getline(cin, newStaff.StaffName);

            cout << "Enter the Staff's Address : ";
            cin >> newStaff.StaffAddress;
            cout << "Enter the Staff's Phone : ";
            cin >> newStaff.StaffPhone;
            MyFile << newStaff.StaffId << "  " << newStaff.StaffName << "  " << newStaff.StaffAddress << "  "
                   << newStaff.StaffPhone << endl;
            MyFile.close();

            cout << "\nStaff added successfully!\n";
        }else{
            cout<<"You are not allowed to add new Staff";
            menu();
        }
    listStaff();
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
        while (MyFile >> Staff.StaffId >> Staff.StaffName >>Staff.StaffAddress>>Staff.StaffPhone ) {}
        return idSlice(Staff.StaffId);
    }

//    string line;
//    int lineCount = 0;

//    while (getline(MyFile, line)) {
//        lineCount++;
//    }
    MyFile.close();
    return 0;
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
        case 'Q':
        case 'q':
            cout << "Exiting the application.\n";
            break;
        default:
            cout << "Invalid selection. Please try again.\n";
            menu();
    }
}
void login(){
    string username, password;
    cout << "Please enter your username: ";
    cin >> username;
    cout << "Please enter your password: ";
    cin >> password;
    ifstream MyFile("Staffs.txt");
    if (!MyFile) {
        cout << "Error opening file.\n";
        menu();
        return;
    }
    Staff Staff;
    printDivider('-');
    while (MyFile >> Staff.StaffId >> Staff.StaffName >> Staff.StaffAddress >> Staff.StaffPhone >> Staff.StaffPassword) {
        if(Staff.StaffName==username && Staff.StaffPassword==password){
            cout << "Login successfully!\n";
            currentStaff = Staff;
            return menu();
        } else{
            cout << "Login failed!\n";
            login();
        }
    }
    MyFile.close();
    cout << " do here"<<"\n";

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
    std::time_t now = std::time(nullptr);
    std::tm* local_time = std::localtime(&now);
    int year = local_time->tm_year + 1900; // tm_year is the year since 1900
    int month = local_time->tm_mon + 1;    // tm_mon is zero-based, so add 1
    int day = local_time->tm_mday;
    currentDate = to_string(year) + "-" + to_string(month) + "-" + to_string(day);

    printHeader();
    login();
return 0;
}
