#include <iostream> // for input/output
#include <limits> // For clearing input buffer
using namespace std; // using standard namespace for convenience

// Date struct
struct Date { // struct to represent a date
    // This struct contains three integers to represent a date
    int day, month, year; //represeting a date with day, month, and year
};

// Utility function to compare dates (returns true if date1 <= date2)
bool isEarlierOrEqual(const Date& date1, const Date& date2) { // checks if date1 is earlier than or eaqual to date2
    if (date1.year < date2.year) return true; // if date1 is earlier than date2
    if (date1.year == date2.year && date1.month < date2.month) return true; // if date1 is in the same year and earlier month than date2
    if (date1.year == date2.year && date1.month == date2.month && date1.day <= date2.day) return true; // if date1 is in the same year and month and ealier or equal day than date2
    return false; // otherwise, date1 is later than date2
}

// Utility function to check overlap between two date ranges
bool datesOverlap(const Date& start1, const Date& end1, const Date& start2, const Date& end2) { // checs if two date ranges overlap
    // Two date ranges overlap if neither range ends before the other starts
    return !(isEarlierOrEqual(end1, start2) || isEarlierOrEqual(end2, start1));
}

// Booking struct
struct Booking { // struct to represent a booking with check-in and check-out dates
    Date checkin;// check-in date
    Date checkout;// check-out date
    // Constructor for easy initialization

};

// Abstract base class for rooms
class Room {// abstract class representing a room in the hotel
protected: // protected members can be accessed by derived classes
    // Unique identifier for the room
    // Dynamic array to hold bookings
    // Count of bookings for the room
    int id;// unique room ID
    Booking* bookings; // dynamic array of bookings
    int bookingCount; // number of bookings for the room
public: // Constructor to initialize room with ID
    Room(int id) : id(id), bookings(nullptr), bookingCount(0) {} // constructor to initialize room with ID, bookings to nullptr, and bookingCount to 0
    virtual ~Room() {// destructor to clean up dynamic memory
        delete[] bookings;// delete the dynamic array of bookings
    }
    int getId() const { return id; }// getter for room ID
    // Pure virtual functions to be implemented by derived classes
    virtual bool isAvailable(const Date& checkin, const Date& checkout) = 0;// checks if the room is available for the given date range
    virtual void book(const Date& checkin, const Date& checkout) = 0;// books the room for the given date range
    virtual string getType() const = 0;// returns the type of room (Single or Double)
};

// SingleRoom class
class SingleRoom : public Room { // derived class for single rooms
public:// constructor to initialize SingleRoom with ID
    SingleRoom(int id) : Room(id) {} // constructor to initialize SingleRoom with ID
    // Check if the room is available for the given date range
    bool isAvailable(const Date& checkin, const Date& checkout) override {// checks if the room is available for the given date range
        for (int i = 0; i < bookingCount; ++i) {// loop through existing bookings
            if (datesOverlap(bookings[i].checkin, bookings[i].checkout, checkin, checkout)) {// checks if the new booking overlaps with existing bookings
                return false; // if overlap found, return false
            }
        }
        return true; // if no overlap found, return true
    }
    void book(const Date& checkin, const Date& checkout) override {// books the room for the given date range
        if (!isAvailable(checkin, checkout)) {// checks if the room is available
            cout << "Date range already booked in SingleRoom ID " << id << endl;// if not available, print message and return
            return;// return if the room is not available
        }
        Booking* newBookings = new Booking[bookingCount + 1];// create a new dynamic array with one more booking slot
        for (int i = 0; i < bookingCount; ++i)// loop through existing bookings
            newBookings[i] = bookings[i];// copy existing bookings to the new array
        newBookings[bookingCount] = {checkin, checkout};// add the new booking to the new array
        delete[] bookings;// delete the old bookings array to free memory
        bookings = newBookings;// assign the new bookings array to the room
        bookingCount++;// increment the booking count
        cout << "Booked SingleRoom ID " << id << " from " // prints booking confirmation
             << checkin.day << "/" << checkin.month << "/" << checkin.year 
             << " to "
             << checkout.day << "/" << checkout.month << "/" << checkout.year << endl; // prints booking confirmation
    }
    string getType() const override { // returns the type of room
        return "Single"; // returns "Single" for SingleRoom
    }
};

// DoubleRoom class
class DoubleRoom : public Room {// derived class for double rooms
public:// constructor to initialize DoubleRoom with ID
    DoubleRoom(int id) : Room(id) {}// constructor to initialize DoubleRoom with ID
    bool isAvailable(const Date& checkin, const Date& checkout) override { // checks if the room is available for the given date range
        for (int i = 0; i < bookingCount; ++i) {// loop through existing bookings
            if (datesOverlap(bookings[i].checkin, bookings[i].checkout, checkin, checkout)) {// checks if the new booking overlaps with existing bookings
                return false;// if overlap found, return false
            }
        }
        return true;// if no overlap found, return true
    }
    void book(const Date& checkin, const Date& checkout) override {// books the room for the given date range
        if (!isAvailable(checkin, checkout)) {// checks if the room is available
            cout << "Date range already booked in DoubleRoom ID " << id << endl;// if not available, print message and return
            return;// return if the room is not available
        }
        Booking* newBookings = new Booking[bookingCount + 1];// create a new dynamic array with one more booking slot
        for (int i = 0; i < bookingCount; ++i)// loop through existing bookings
            newBookings[i] = bookings[i];// copy existing bookings to the new array
        newBookings[bookingCount] = {checkin, checkout};// add the new booking to the new array
        delete[] bookings;// delete the old bookings array to free memory
        bookings = newBookings;// assign the new bookings array to the room
        bookingCount++;// increment the booking count
        cout << "Booked DoubleRoom ID " << id << " from "
             << checkin.day << "/" << checkin.month << "/" << checkin.year
             << " to "
             << checkout.day << "/" << checkout.month << "/" << checkout.year << endl;// prints booking confirmation
    }
    string getType() const override {// returns the type of room
        return "Double";// returns "Double" for DoubleRoom
    }
};

// HotelBookingSystem class
class HotelBookingSystem {// class to manage hotel rooms and bookings
private:// private members can only be accessed by this class
    // Dynamic array of room pointers
    Room** rooms;// dynamic array of pointers to Room objects
    int roomCount;// total number of rooms in the system
    // Helper function to check if a room with the given ID exists
public:// public members can be accessed by other classes
    HotelBookingSystem() : rooms(nullptr), roomCount(0) {}// constructor to initialize the hotel booking system with no rooms
    ~HotelBookingSystem() {// destructor to clean up dynamic memory
        for (int i = 0; i < roomCount; ++i)// loop through all rooms
            delete rooms[i];// delete each room object to free memory
        delete[] rooms;// delete the dynamic array of room pointers to free memory
    }

    void addRoom(Room* room) {// adds a new room to the system
        // Check if room already exists
        Room** newRooms = new Room*[roomCount + 1];// create a new dynamic array with one more room slot
        for (int i = 0; i < roomCount; ++i)// loop through existing rooms
            newRooms[i] = rooms[i];// copy existing rooms to the new array
        newRooms[roomCount] = room;// add the new room to the new array
        // Delete old array and replace with new
        delete[] rooms;// delete the old array of room pointers to free memory
        rooms = newRooms;// assign the new array to the rooms pointer
        roomCount++;// increment the room count
        cout << room->getType() << " Room ID " << room->getId() << " added.\n";// prints confirmation message
    }

    void removeRoom(int roomId) {// removes a room with the given ID from the system
        int indexToRemove = -1;// index of the room to remove
        for (int i = 0; i < roomCount; ++i) {// loop through existing rooms
            if (rooms[i]->getId() == roomId) { // checks if the room ID matches the given ID
                indexToRemove = i;// set the index to remove
                break; // exit loop if room found
            }
        }
        if (indexToRemove == -1) {// if room not found
            // If room with given ID not found, print message and return
            cout << "Room ID " << roomId << " not found.\n";
            return; // return if room not found
        }

        delete rooms[indexToRemove];// delete the room object to free memory

        Room** newRooms = new Room*[roomCount - 1];// create a new dynamic array with one less room slot
        int newIndex = 0;// index for the new array
        for (int i = 0; i < roomCount; ++i) {// loop through existing rooms
            // Copy all rooms except the one to remove
            if (i != indexToRemove) {// checks if the current index is not the one to remove
                // If not the room to remove, copy it to the new array
                newRooms[newIndex++] = rooms[i];
            }
        }

        delete[] rooms;// delete the old array of room pointers to free memory
        // Replace old array with new array
        rooms = newRooms;// assign the new array to the rooms pointer
        roomCount--;// decrement the room count
        cout << "Room ID " << roomId << " Room is no longer available.\n";// prints confirmation message
    }

    void displayRooms() {// displays all registered rooms in the system
        cout << "Registered Rooms:\n";// prints header for registered rooms
        if (roomCount == 0) {// checks if there are no rooms registered
            cout << "No rooms registered.\n";// prints message if no rooms are registered
            return; // return if no rooms to display
        }
        for (int i = 0; i < roomCount; ++i) {// loop through all registered rooms
            // Print room ID and type
            cout << "Room ID: " << rooms[i]->getId()// prints room ID
                 << ", Type: " << rooms[i]->getType() << endl;// prints room type
        }
    }

    void bookRoom(int roomId, const Date& checkin, const Date& checkout) {// books a room with the given ID for the specified date range
        // Check if room with given ID exists
        if (roomCount == 0) {// checks if there are no rooms registered
            cout << "No rooms registered. Please wait an admin to update the available room.\n";// prints message if no rooms are registered
            return; // return if no rooms to book
        }
        for (int i = 0; i < roomCount; ++i) {// loop through all registered rooms
            // Check if room ID matches the given ID
            if (rooms[i]->getId() == roomId) {// checks if the current room ID matches the given ID
                // If room found, check availability and book
                if (rooms[i]->isAvailable(checkin, checkout)) { // checks if the room is available for the given date range
                    // If available, book the room
                    rooms[i]->book(checkin, checkout);
                } else {
                    cout << "Room " << roomId << " is already booked during this period.\n";// prints message if the room is already booked for the given date range
                }
                return;// return after booking the room
            }
        }
        cout << "Room with ID " << roomId << " not found.\n";// prints message if the room with the given ID is not found
        // If room with given ID not found, print message and return
    }
};

// Helper to clear input buffer after invalid input
void clearInputBuffer() {// clears the input buffer to handle invalid input
    // This function clears the input buffer to avoid infinite loops on invalid input
    cin.clear(); // clear the error state of cin
    // Ignore characters until a newline is found or the maximum size is reached
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Main program
int main() {// main function to run the hotel booking system
    // Create an instance of HotelBookingSystem
    HotelBookingSystem system;
    int choice; // variable to store user choice

    cout << "===== Hotel Booking System Admin Panel =====\n";
    // Admin panel for registering rooms
    // This section allows the admin to update the available rooms in the system
    cout << "Register rooms to the system:\n";

    while (true) {// loop until the admin finishes registration
        cout << "\n1. Add Single Room\n";// option to add a single room
        cout << "2. Add Double Room\n";// option to add a double room
        cout << "3. Remove Room\n";// option to remove a room
        cout << "4. Finish Registration\n"; // option to complete registration of the room
        cout << "Enter choice: "; // prompt for user input
        // Read user choice
        cin >> choice;// read user input for choice

        if (cin.fail()) {// checks if the input is valid
            // If input is invalid, clear the input buffer and prompt again
            clearInputBuffer();// clear the input buffer to handle invalid input
            cout << "Invalid input. Please enter a number.\n";// prints message if input is invalid
            continue;// continue to the next iteration to prompt for input again
        }

        if (choice == 1 || choice == 2) {// checks if the choice is to add a room
            // If choice is to add a room, prompt for room ID
            int id;// variable to store room ID
            cout << "Enter Room ID: ";// prompt for room ID
            cin >> id;// read user input for room ID
            if (cin.fail()) {// checks if the input is valid
                clearInputBuffer();// clear the input buffer to handle invalid input
                // If input is invalid, prompt again
                cout << "Invalid ID. Try again.\n";
                continue;// continue to the next iteration to prompt for input again
            }
            if (choice == 1)// checks if the choice is to add a single room
                system.addRoom(new SingleRoom(id));// adds a new SingleRoom with the given ID
            else
                system.addRoom(new DoubleRoom(id));// adds a new DoubleRoom with the given ID
        } else if (choice == 3) {// checks if the choice is to remove a room
            // If choice is to remove a room, prompt for room ID
            int id;// variable to store room ID
            cout << "Enter Room ID to remove: ";// prompt for room ID to remove
            cin >> id;// read user input for room ID to remove
            if (cin.fail()) {// checks if the input is valid
                clearInputBuffer();// clear the input buffer to handle invalid input
                // If input is invalid, prompt again
                cout << "Invalid ID. Try again.\n";
                continue;// continue to the next iteration to prompt for input again
            }
            system.removeRoom(id);// removes the room with the given ID from the system
        } else if (choice == 4) {// checks if the choice is to finish registration
            cout << "Registration completed.\n";// prints message indicating registration is completed
            break;// exit the loop to finish registration
        } else {
            cout << "Invalid choice. Try again.\n";// prints message if the choice is invalid
            continue; // continue to the next iteration to prompt for input again
        }
    }

    cout << "\n=== User pannel for booking room in hotel ====\n";

    while (true) {// loop until the user exits the booking system
        // User booking panel
        cout << "\n1. View Rooms\n";// option to view available rooms
        cout << "2. Book a Room\n";// option to book a room
        cout << "3. Exit\n";// option to exit the booking system
        cout << "Enter choice: ";// prompt for user input
        cin >> choice;// read user input for choice

        if (cin.fail()) {// checks if the input is valid
            clearInputBuffer();// clear the input buffer to handle invalid input
            cout << "Invalid input. Try again.\n";// prints message if input is invalid
            continue;// continue to the next iteration to prompt for input again
        }

        if (choice == 1) {// checks if the choice is to view available rooms
            system.displayRooms();// displays all registered rooms in the system
        } else if (choice == 2) {
            int roomId;// variable to store room ID
            // If choice is to book a room, prompt for room ID and dates
            Date checkin, checkout;// variables to store check-in and check-out dates
            cout << "Available Rooms:\n";// prints header for available rooms
            cout << "Enter Room ID to book: ";// prompt for room ID to book
            // Read room ID
            cin >> roomId;
            if (cin.fail()) {// checks if the input is valid
                clearInputBuffer();// clear the input buffer to handle invalid input
                // If input is invalid, prompt again
                cout << "Invalid Room ID. Try again.\n";
                continue;
            }
            cout << "Enter check-in date (day month year): ";
            cin >> checkin.day >> checkin.month >> checkin.year;// prompt for check-in date
            if (cin.fail()) {// checks if the input is valid
                clearInputBuffer();// clear the input buffer to handle invalid input
                cout << "Invalid date. Try again.\n";// prints message if input is invalid
                continue;
            }
            cout << "Enter check-out date (day month year): ";
            cin >> checkout.day >> checkout.month >> checkout.year;// prompt for check-out date
            // Read check-out date
            if (cin.fail()) {// checks if the input is valid
                clearInputBuffer();// clear the input buffer to handle invalid input
                cout << "Invalid date. Try again.\n";
                continue;
            }
            if (!isEarlierOrEqual(checkin, checkout)) {// checks if check-in date is earlier than or equal to check-out date
                // If check-in date is not earlier than or equal to check-out date, print message and continue
                cout << "Check-in date must be before or equal to check-out date.\n";
                continue;
            }
            system.bookRoom(roomId, checkin, checkout);// books the room with the given ID for the specified date range
        } else if (choice == 3) {
            cout << "thank you for using our system!\n";// prints message indicating the user is exiting the booking system
            break;
        } else {
            cout << "Invalid choice. Try again.\n";// prints message if the choice is invalid
            continue; // continue to the next iteration to prompt for input again
        }
    }

    return 0;// return 0 to indicate successful execution of the program
}
