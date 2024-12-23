#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <exception>
#include <limits> // Add this line


using namespace std;

// === Vehicle Base Class ===
class Vehicle {
protected:
    string type;
    string model;
    string registrationNumber;

public:
    Vehicle(string t, string m, string reg) : type(t), model(m), registrationNumber(reg) {}

    virtual void display() const {
        cout << "Type: " << type << ", Model: " << model << ", Registration: " << registrationNumber << endl;
    }

    virtual void saveToFile(ofstream &file) const {
        file << type << "," << model << "," << registrationNumber << endl;
    }

    static Vehicle *loadFromFile(const string &line) {
        size_t pos1 = line.find(",");
        size_t pos2 = line.find(",", pos1 + 1);

        string t = line.substr(0, pos1);
        string m = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string reg = line.substr(pos2 + 1);

        return new Vehicle(t, m, reg);
    }

    virtual ~Vehicle() {}
};

// === Car and Truck Derived Classes ===
class Car : public Vehicle {
private:
    int seatingCapacity;

public:
    Car(string m, string reg, int sc) : Vehicle("Car", m, reg), seatingCapacity(sc) {}

    void display() const override {
        cout << "Type: Car, Model: " << model << ", Registration: " << registrationNumber
             << ", Seating Capacity: " << seatingCapacity << endl;
    }

    void saveToFile(ofstream &file) const override {
        file << "Car," << model << "," << registrationNumber << "," << seatingCapacity << endl;
    }

    static Car *loadFromFile(const string &line) {
        size_t pos1 = line.find(",");
        size_t pos2 = line.find(",", pos1 + 1);
        size_t pos3 = line.find(",", pos2 + 1);

        string m = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string reg = line.substr(pos2 + 1, pos3 - pos2 - 1);
        int sc = stoi(line.substr(pos3 + 1));

        return new Car(m, reg, sc);
    }
};

class Truck : public Vehicle {
private:
    double payloadCapacity;

public:
    Truck(string m, string reg, double pc) : Vehicle("Truck", m, reg), payloadCapacity(pc) {}

    void display() const override {
        cout << "Type: Truck, Model: " << model << ", Registration: " << registrationNumber
             << ", Payload Capacity: " << payloadCapacity << " tons" << endl;
    }

    void saveToFile(ofstream &file) const override {
        file << "Truck," << model << "," << registrationNumber << "," << payloadCapacity << endl;
    }

    static Truck *loadFromFile(const string &line) {
        size_t pos1 = line.find(",");
        size_t pos2 = line.find(",", pos1 + 1);
        size_t pos3 = line.find(",", pos2 + 1);

        string m = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string reg = line.substr(pos2 + 1, pos3 - pos2 - 1);
        double pc = stod(line.substr(pos3 + 1));

        return new Truck(m, reg, pc);
    }
};

// === Customer Class ===
class Customer {
private:
    string name;
    string contact;

public:
    Customer(string n, string c) : name(n), contact(c) {}

    void display() const {
        cout << "Name: " << name << ", Contact: " << contact << endl;
    }

    void saveToFile(ofstream &file) const {
        file << name << "," << contact << endl;
    }

    static Customer loadFromFile(const string &line) {
        size_t pos = line.find(",");
        string n = line.substr(0, pos);
        string c = line.substr(pos + 1);

        return Customer(n, c);
    }
};

// === Backend Functions ===
/*void saveVehiclesToFile(const vector<Vehicle *> &vehicles) {
    string filename;
    cout << "Enter the file path to save vehicles (e.g., vehicles.txt): ";
    cin.ignore();
    getline(cin, filename);

    ofstream file(filename);
    if (!file) {
        cerr << "Error: Unable to open file for saving vehicles!" << endl;
        return;
    }

    for (const auto &vehicle : vehicles) {
        vehicle->saveToFile(file);
    }

    cout << "Vehicles saved successfully to " << filename << "!" << endl;
    file.close();
}*/

void saveVehiclesToFile(const vector<Vehicle *> &vehicles) {
    string filename;
    cout << "Enter the file path to save vehicles (e.g., vehicles.txt): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    getline(cin, filename);

    ofstream file(filename);
    if (!file) {
        cerr << "Error: Unable to open file for saving vehicles!" << endl;
        return;
    }

    for (const auto &vehicle : vehicles) {
        vehicle->saveToFile(file);
    }

    cout << "Vehicles saved successfully to " << filename << "!" << endl;
    file.close();
}

/*void loadVehiclesFromFile(vector<Vehicle *> &vehicles) {
    string filename;
    cout << "Enter the file path to load vehicles (e.g., vehicles.txt): ";
    cin.ignore();
    getline(cin, filename);

    ifstream file(filename);
    if (!file) {
        cerr << "Error: Unable to open file for loading vehicles!" << endl;
        return;
    }*/

void loadVehiclesFromFile(vector<Vehicle *> &vehicles) {
    string filename;
    cout << "Enter the file path to load vehicles (e.g., vehicles.txt): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    getline(cin, filename);

    ifstream file(filename);
    if (!file) {
        cerr << "Error: Unable to open file for loading vehicles!" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        try {
            size_t pos1 = line.find(",");
            string type = line.substr(0, pos1);

            if (type == "Car") {
                vehicles.push_back(Car::loadFromFile(line));
            } else if (type == "Truck") {
                vehicles.push_back(Truck::loadFromFile(line));
            } else {
                cerr << "Warning: Unknown vehicle type in file: " << line << endl;
            }
        } catch (const exception &e) {
            cerr << "Error parsing line: " << line << " - " << e.what() << endl;
        }
    }

    cout << "Vehicles loaded successfully from " << filename << "!" << endl;
    file.close();
}


// Add customer functions (existing logic preserved)
/*void addCustomer(vector<Customer> &customers) {
    string name, contact;

    cout << "\nEnter Customer Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Contact: ";
    getline(cin, contact);

    customers.push_back(Customer(name, contact));
    cout << "Customer added successfully!\n" << endl;
}*/

void addCustomer(vector<Customer> &customers) {
    string name, contact;

    cout << "\nEnter Customer Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    getline(cin, name);
    cout << "Enter Contact: ";
    getline(cin, contact);

    customers.push_back(Customer(name, contact));
    cout << "Customer added successfully!\n" << endl;
}

void displayCustomers(const vector<Customer> &customers) {
    if (customers.empty()) {
        cout << "\nNo customers available.\n" << endl;
        return;
    }

    cout << "\n=== Customer List ===" << endl;
    for (const auto &customer : customers) {
        customer.display();
    }
    cout << endl;
}

/*void saveCustomers(const vector<Customer> &customers) {
    string filename;
    cout << "Enter the file path to save customers (e.g., customers.txt): ";
    getline(cin, filename);

    ofstream file(filename);
    if (!file) {
        cerr << "Error: Unable to open file for saving customers!\n" << endl;
        return;
    }

    for (const auto &customer : customers) {
        customer.saveToFile(file);
    }

    cout << "Customers saved successfully to " << filename << "!\n" << endl;
    file.close();
}*/

void saveCustomers(const vector<Customer> &customers) {
    string filename;
    cout << "Enter the file path to save customers (e.g., customers.txt): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    getline(cin, filename);

    ofstream file(filename);
    if (!file) {
        cerr << "Error: Unable to open file for saving customers!\n" << endl;
        return;
    }

    for (const auto &customer : customers) {
        customer.saveToFile(file);
    }

    cout << "Customers saved successfully to " << filename << "!\n" << endl;
    file.close();
}

/*void loadCustomers(vector<Customer> &customers) {
    string filename;
    cout << "Enter the file path to load customers (e.g., customers.txt): ";
    getline(cin, filename);

    ifstream file(filename);
    if (!file) {
        cerr << "Error: Unable to open file for loading customers!\n" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        customers.push_back(Customer::loadFromFile(line));
    }

    cout << "Customers loaded successfully from " << filename << "!\n" << endl;
    file.close();
}*/
void loadCustomers(vector<Customer> &customers) {
    string filename;
    cout << "Enter the file path to load customers (e.g., customers.txt): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    getline(cin, filename);

    ifstream file(filename);
    if (!file) {
        cerr << "Error: Unable to open file for loading customers!\n" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        customers.push_back(Customer::loadFromFile(line));
    }

    cout << "Customers loaded successfully from " << filename << "!\n" << endl;
    file.close();
}

// === Frontend Menu ===
void showMenu() {
    cout << "\t\t\t\t==================== SWIFT LOGISTICS ===================\n" << endl;
    cout << "\t\t======================= Welcome to the Transport Logistics System! =======================\n" << endl;


    cout << "\t\t\t============= Manage your fleet and customers with ease. ================\n" << endl;
    cout << "1. Add Vehicle\n" << endl;
    cout << "2. Display Vehicles\n" << endl;
    cout << "3. Save Vehicles to File\n" << endl;
    cout << "4. Load Vehicles from File\n" << endl;
    cout << "5. Add Customer\n" << endl;
    cout << "6. Display Customers\n" << endl;
    cout << "7. Save Customers to File\n" << endl;
    cout << "8. Load Customers from File\n" << endl;
    cout << "9. Exit" << endl;
    cout << "Enter your choice: ";
}

// === Main Function ===
int main() {
    vector<Vehicle *> vehicles;
    vector<Customer> customers;
    string vehicleFile = "vehicles.txt";
    string customerFile = "customers.txt";

    int choice;

    do {
        showMenu();
        cin >> choice;

        try {
            switch (choice) {
                case 1: {
                    // Add vehicle logic
                    string model, reg;
                    int typeChoice;

                    cout << "1. Car\n2. Truck\nEnter Vehicle Type: ";
                    cin >> typeChoice;

                    cout << "Enter Model: ";
                    cin >> model;
                    cout << "Enter Registration Number: ";
                    cin >> reg;

                    if (typeChoice == 1) {
                        int seating;
                        cout << "Enter Seating Capacity: ";
                        cin >> seating;
                        vehicles.push_back(new Car(model, reg, seating));
                    } else if (typeChoice == 2) {
                        double payload;
                        cout << "Enter Payload Capacity (tons): ";
                        cin >> payload;
                        vehicles.push_back(new Truck(model, reg, payload));
                    } else {
                        cout << "Invalid Vehicle Type!" << endl;
                    }
                    break;
                }

                case 2: {
                    // Display vehicles
                    for (const auto &vehicle : vehicles) {
                        vehicle->display();
                    }
                    break;
                }

                case 3: {
                    // Save vehicles to file
                    saveVehiclesToFile(vehicles);
                    break;
                }

                case 4: {
                    // Load vehicles from file
                    loadVehiclesFromFile(vehicles);
                    break;
                }

                case 5: {
                    // Add customer logic
                    addCustomer(customers);
                    break;
                }

                case 6: {
                    // Display customers
                    displayCustomers(customers);
                    break;
                }

                case 7: {
                    // Save customers to file
                    saveCustomers(customers);
                    break;
                }

                case 8: {
                    // Load customers from file
                    loadCustomers(customers);
                    break;
                }

                case 9: {
                    // Exit
                    cout << "Exiting program." << endl;
                    break;
                }

                default: {
                    cout << "Invalid choice." << endl;
                    break;
                }
            }
        } catch (exception &e) {
            cerr << "Error: " << e.what() << endl;
        }
    } while (choice != 9);

    return 0;
}
