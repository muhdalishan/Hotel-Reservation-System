#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string* roomIDs = nullptr;
string* roomTypes = nullptr;
bool* roomAvailability = nullptr;
int roomCount = 0;

string* customerIDs = nullptr;
string* customerNames = nullptr;
string* customerContacts = nullptr;
string* customerBookings = nullptr;
int customerCount = 0;

void addRoom() {
    string* newRoomIDs = new string[roomCount + 1];
    string* newRoomTypes = new string[roomCount + 1];
    bool* newRoomAvailability = new bool[roomCount + 1];

    for (int i = 0; i < roomCount; i++) {
        newRoomIDs[i] = roomIDs[i];
        newRoomTypes[i] = roomTypes[i];
        newRoomAvailability[i] = roomAvailability[i];
    }

    cout << "Room ID: ";
    cin >> newRoomIDs[roomCount];
    cout << "Type: ";
    cin >> newRoomTypes[roomCount];
    newRoomAvailability[roomCount] = true;

    delete[] roomIDs;
    delete[] roomTypes;
    delete[] roomAvailability;

    roomIDs = newRoomIDs;
    roomTypes = newRoomTypes;
    roomAvailability = newRoomAvailability;

    roomCount++;

    cout << "Room added: ID=" << roomIDs[roomCount-1] << ", Type=" << roomTypes[roomCount-1] << ", Availability=Available" << endl;
}

void registerCustomer() {
    string* newCustomerIDs = new string[customerCount + 1];
    string* newCustomerNames = new string[customerCount + 1];
    string* newCustomerContacts = new string[customerCount + 1];
    string* newCustomerBookings = new string[customerCount + 1];

    for (int i = 0; i < customerCount; i++) {
        newCustomerIDs[i] = customerIDs[i];
        newCustomerNames[i] = customerNames[i];
        newCustomerContacts[i] = customerContacts[i];
        newCustomerBookings[i] = customerBookings[i];
    }

    cout << "Customer ID: ";
    cin >> newCustomerIDs[customerCount];
    cout << "Name: ";
    cin >> newCustomerNames[customerCount];
    cout << "Contact Info: ";
    cin >> newCustomerContacts[customerCount];
    newCustomerBookings[customerCount] = "";

    delete[] customerIDs;
    delete[] customerNames;
    delete[] customerContacts;
    delete[] customerBookings;

    customerIDs = newCustomerIDs;
    customerNames = newCustomerNames;
    customerContacts = newCustomerContacts;
    customerBookings = newCustomerBookings;

    customerCount++;

    cout << "Customer registered: ID=" << customerIDs[customerCount-1] << ", Name=" << customerNames[customerCount-1] << ", Contact Info=" << customerContacts[customerCount-1] << endl;
}

void bookRoom() {
    string customerID, roomID;
    cout << "Customer ID: ";
    cin >> customerID;
    cout << "Room ID: ";
    cin >> roomID;

    int customerIndex = -1;
    for (int i = 0; i < customerCount; i++) {
        if (customerIDs[i] == customerID) {
            customerIndex = i;
            break;
        }
    }

    if (customerIndex == -1) {
        cout << "Customer not found!" << endl;
        return;
    }

    int roomIndex = -1;
    for (int i = 0; i < roomCount; i++) {
        if (roomIDs[i] == roomID && roomAvailability[i]) {
            roomIndex = i;
            break;
        }
    }

    if (roomIndex == -1) {
        cout << "Room not available!" << endl;
        return;
    }

    roomAvailability[roomIndex] = false;
    customerBookings[customerIndex] = roomID;

    cout << "Room booked: Customer ID=" << customerID << ", Room ID=" << roomID << endl;
}

void cancelBooking() {
    string customerID, roomID;
    cout << "Customer ID: ";
    cin >> customerID;
    cout << "Room ID: ";
    cin >> roomID;

    int customerIndex = -1;
    for (int i = 0; i < customerCount; i++) {
        if (customerIDs[i] == customerID && customerBookings[i] == roomID) {
            customerIndex = i;
            break;
        }
    }

    if (customerIndex == -1) {
        cout << "Booking not found!" << endl;
        return;
    }

    int roomIndex = -1;
    for (int i = 0; i < roomCount; i++) {
        if (roomIDs[i] == roomID) {
            roomIndex = i;
            break;
        }
    }

    if (roomIndex == -1) {
        cout << "Room not found!" << endl;
        return;
    }

    roomAvailability[roomIndex] = true;
    customerBookings[customerIndex] = "";

    cout << "Booking canceled: Customer ID=" << customerID << ", Room ID=" << roomID << endl;
}

void displayAllRooms() {
    cout << "All Rooms:" << endl;
    for (int i = 0; i < roomCount; i++) {
        cout << "Room ID: " << roomIDs[i] << ", Type: " << roomTypes[i] << ", Availability: " << (roomAvailability[i] ? "Available" : "Booked") << endl;
    }
}

void displayAllCustomers() {
    cout << "All Customers:" << endl;
    for (int i = 0; i < customerCount; i++) {
        cout << "Customer ID: " << customerIDs[i] << ", Name: " << customerNames[i] << ", Contact Info: " << customerContacts[i] << ", Booking: " << customerBookings[i] << endl;
    }
}

void saveRecords() {
    ofstream outFile("hotel_data.txt");
    outFile << roomCount << endl;
    for (int i = 0; i < roomCount; i++) {
        outFile << roomIDs[i] << " " << roomTypes[i] << " " << roomAvailability[i] << endl;
    }

    outFile << customerCount << endl;
    for (int i = 0; i < customerCount; i++) {
        outFile << customerIDs[i] << " " << customerNames[i] << " " << customerContacts[i] << " " << customerBookings[i] << endl;
    }

    outFile.close();
    cout << "Records saved to file." << endl;
}

void loadRecords() {
    ifstream inFile("hotel_data.txt");
    inFile >> roomCount;

    delete[] roomIDs;
    delete[] roomTypes;
    delete[] roomAvailability;

    roomIDs = new string[roomCount];
    roomTypes = new string[roomCount];
    roomAvailability = new bool[roomCount];

    for (int i = 0; i < roomCount; i++) {
        inFile >> roomIDs[i] >> roomTypes[i] >> roomAvailability[i];
    }

    inFile >> customerCount;

    delete[] customerIDs;
    delete[] customerNames;
    delete[] customerContacts;
    delete[] customerBookings;

    customerIDs = new string[customerCount];
    customerNames = new string[customerCount];
    customerContacts = new string[customerCount];
    customerBookings = new string[customerCount];

    for (int i = 0; i < customerCount; i++) {
        inFile >> customerIDs[i] >> customerNames[i] >> customerContacts[i] >> customerBookings[i];
    }

    inFile.close();
    cout << "Records loaded from file." << endl;
}

void displayMenu() {
    cout << "1. Add a new room" << endl;
    cout << "2. Register a new customer" << endl;
    cout << "3. Book a room" << endl;
    cout << "4. Cancel a booking" << endl;
    cout << "5. Display all rooms" << endl;
    cout << "6. Display all customers" << endl;
    cout << "7. Save records to file" << endl;
    cout << "8. Load records from file" << endl;
    cout << "9. Exit" << endl;
    cout << "Choose an option: ";
}

int main() {
    int choice;
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addRoom();
                break;
            case 2:
                registerCustomer();
                break;
            case 3:
                bookRoom();
                break;
            case 4:
                cancelBooking();
                break;
            case 5:
                displayAllRooms();
                break;
            case 6:
                displayAllCustomers();
                break;
            case 7:
                saveRecords();
                break;
            case 8:
                loadRecords();
                break;
            case 9:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    } while (choice != 9);

    delete[] roomIDs;
    delete[] roomTypes;
    delete[] roomAvailability;
    delete[] customerIDs;
    delete[] customerNames;
    delete[] customerContacts;
    delete[] customerBookings;

    return 0;
}
