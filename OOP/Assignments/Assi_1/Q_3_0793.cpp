#include <iostream>
#include <string>
using namespace std;

class User
{
    string name;
    int age;
    string licenseType;
    string contact;
    string userID;

public:
    User() : name(""), age(-1), licenseType(""), contact(""), userID("") {}

    void registerUser()
    {
        cin.ignore();
        cout << "Enter the name of the user: ";
        getline(cin, name);
        cout << "Enter the age of the user: ";
        cin >> age;
        cin.ignore();
        cout << "Enter the license type (Learner, Intermediate, Full): ";
        getline(cin, licenseType);
        cout << "Enter the user's contact number: ";
        getline(cin, contact);
        cout << "Enter the user ID: ";
        getline(cin, userID);
        cout << "User registered successfully." << endl;
    }

    void updateUser()
    {
        if (age == -1)
        {
            cout << "User has not been registered yet." << endl;
            return;
        }

        cin.ignore();
        cout << "Enter the updated name of the user: ";
        getline(cin, name);
        cout << "Enter the updated age of the user: ";
        cin >> age;
        cin.ignore();
        cout << "Enter the updated license type (Learner, Intermediate, Full): ";
        getline(cin, licenseType);
        cout << "Enter the updated user's contact number: ";
        getline(cin, contact);
        cout << "Enter the updated user ID: ";
        getline(cin, userID);
        cout << "User details updated successfully." << endl;
    }

    string getLicenseType() { return licenseType; }
};

class Vehicle
{
    string model;
    float rentalPricePerDay;
    string eligibility;

public:
    Vehicle(string m, float rp, string e) : model(m), rentalPricePerDay(rp), eligibility(e) {}

    void displayVehicle()
    {
        cout << "Model: " << model << endl;
        cout << "Rental Price per day: $" << rentalPricePerDay << endl;
        cout << "Eligibility: " << eligibility << endl
             << endl;
    }

    bool isEligible(const string &licenseType)
    {
        int userStatus, vehicleStatus;

        if (licenseType == "Full")
        {
            userStatus = 3;
        }
        else if (licenseType == "Intermediate")
        {
            userStatus = 2;
        }
        else if (licenseType == "Learner")
        {
            userStatus = 1;
        }

        if (eligibility == "Full")
        {
            vehicleStatus = 3;
        }
        else if (eligibility == "Intermediate")
        {
            vehicleStatus = 2;
        }
        else if (eligibility == "Learner")
        {
            vehicleStatus = 1;
        }

        return (userStatus >= vehicleStatus);
    }

    string getVehicleModel() { return model; }
};

void displayMenu()
{
    cout << "-------- Rent A Car Menu --------" << endl;
    cout << "Enter 1 to register user." << endl;
    cout << "Enter 2 to update user details." << endl;
    cout << "Enter 3 to view available vehicles." << endl;
    cout << "Enter 4 to rent a vehicle." << endl;
    cout << "Enter 5 to exit." << endl;
}

void rentVehicle(User &user, Vehicle **vehicles, int vehicleCount)
{
    string m;
    cin.ignore();
    cout << "Enter the vehicle model you would like to rent: ";
    getline(cin, m);
    int found = 0;
    for (int i = 0; i < vehicleCount; i++)
    {
        if (m == vehicles[i]->getVehicleModel())
        {
            if (vehicles[i]->isEligible(user.getLicenseType()))
            {
                cout << vehicles[i]->getVehicleModel() << " rented successfully." << endl;
            }
            else
            {
                cout << "You are not eligible to rent " << vehicles[i]->getVehicleModel() << "." << endl;
            }
            found = 1;
            break;
        }
    }

    if (!found)
    {
        cout << "Invalid vehicle model entered." << endl;
    }
}

int main()
{
    User user;
    int vehicleCount = 3;
    Vehicle **vehicles = new Vehicle *[vehicleCount];
    vehicles[0] = new Vehicle("Toyota Yaris", 49.99, "Learner");
    vehicles[1] = new Vehicle("Mercedes A-Class", 89.99, "Intermediate");
    vehicles[2] = new Vehicle("Ferrari LaFerrari", 124.99, "Full");

    int choice;
    while (1)
    {
        displayMenu();
        cout << "Enter your choice: " << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            user.registerUser();
            break;

        case 2:
            user.updateUser();
            break;

        case 3:
        {
            for (int i = 0; i < vehicleCount; i++)
            {
                cout << "Details of Vehicle " << (i + 1) << ": " << endl;
                vehicles[i]->displayVehicle();
            }
            break;
        }

        case 4:
            rentVehicle(user, vehicles, vehicleCount);
            break;

        case 5:
            cout << "Exiting the program...";
            return 0;

        default:
            cout << "Invalid choice. Try again." << endl;
        }
    }
}