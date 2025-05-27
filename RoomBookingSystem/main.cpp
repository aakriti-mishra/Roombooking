#include <iostream>
#include "BookingSystem.h"

void addRoom(BookingSystem& system) {
    int roomNumber, capacity;
    std::string facilities;

    std::cout << "Enter Room Number: ";
    std::cin >> roomNumber;
    std::cout << "Enter Capacity: ";
    std::cin >> capacity;
    std::cout << "Enter Facilities (comma-separated): ";
    std::cin.ignore();
    std::getline(std::cin, facilities);

    system.addRoom(roomNumber, capacity, facilities);
}

void addBooking(BookingSystem& system) {
    int roomNumber, attendees;
    std::string host, startDate, endDate, startTime, endTime;

    std::cout << "Enter Room Number: ";
    std::cin >> roomNumber;
    std::cin.ignore(); // Clear the newline character left by std::cin
    std::cout << "Enter Host Name: ";
    std::getline(std::cin, host);
    std::cout << "Enter Start Date (e.g., 2024-08-15): ";
    std::getline(std::cin, startDate);
    std::cout << "Enter End Date (e.g., 2024-08-16): ";
    std::getline(std::cin, endDate);
    std::cout << "Enter Start Time (e.g., 12PM): ";
    std::getline(std::cin, startTime);
    std::cout << "Enter End Time (e.g., 11AM): ";
    std::getline(std::cin, endTime);
    std::cout << "Enter Number of Attendees: ";
    std::cin >> attendees;

    Booking booking(host, startDate, endDate, startTime, endTime, attendees);
    system.bookRoom(roomNumber, booking);

    int choice;
    do {
        std::cout << "\nBooking Successful! What would you like to do next?\n";
        std::cout << "1. Go to Main Menu\n";
        std::cout << "2. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 2) {
            system.saveToFile("bookings.txt");
            exit(0); // Exit the program
        }
        else if (choice != 1) {
            std::cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 1);
}

void deleteRoom(BookingSystem& system) {
    int choice;
    do {
        system.showAllRooms(); // List all rooms first

        std::cout << "\nEnter 1 to go to Main Menu, 2 to Exit, or 3 to continue with room deletion: ";
        std::cin >> choice;

        if (choice == 1) {
            return; // Go back to main menu
        }
        else if (choice == 2) {
            system.saveToFile("bookings.txt");
            exit(0); // Exit the program
        }
        else if (choice == 3) {
            int roomNumber;
            std::cout << "Enter Room Number of the room you want to delete: ";
            std::cin >> roomNumber;

            system.deleteRoom(roomNumber);
        }
        else {
            std::cout << "Invalid choice, returning to Main Menu.\n";
            return; // Go back to main menu if invalid choice
        }

        std::cout << "\n1. Go to Main Menu\n";
        std::cout << "2. Exit\n";
        std::cout << "3. Delete Another Room\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 2) {
            system.saveToFile("bookings.txt");
            exit(0); // Exit the program
        }

    } while (choice == 3);
}

void deleteBooking(BookingSystem& system) {
    int choice;
    do {
        system.showAllBookings(); // List all bookings first

        std::cout << "\nEnter 1 to go to Main Menu, 2 to Exit, or 3 to continue with booking deletion: ";
        std::cin >> choice;

        if (choice == 1) {
            return; // Go back to main menu
        }
        else if (choice == 2) {
            system.saveToFile("bookings.txt");
            exit(0); // Exit the program
        }
        else if (choice == 3) {
            int roomNumber, bookingID;
            std::cout << "Enter Room Number of the booking you want to delete: ";
            std::cin >> roomNumber;
            std::cout << "Enter Booking ID to delete: ";
            std::cin >> bookingID;

            system.deleteBooking(roomNumber, bookingID);
        }
        else {
            std::cout << "Invalid choice, returning to Main Menu.\n";
            return; // Go back to main menu if invalid choice
        }

        std::cout << "\n1. Go to Main Menu\n";
        std::cout << "2. Exit\n";
        std::cout << "3. Delete Another Booking\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 2) {
            system.saveToFile("bookings.txt");
            exit(0); // Exit the program
        }

    } while (choice == 3);
}

void listBookings(BookingSystem& system) {
    bool hasBookings = false;
    const auto& rooms = system.getRooms();

    for (const auto& pair : rooms) {
        const Room& room = pair.second;
        if (!room.bookings.empty()) {
            hasBookings = true;
            break;
        }
    }

    if (hasBookings) {
        system.showAllBookings();
    }
    else {
        std::cout << "No Bookings Found.\n";
    }

    int choice;
    do {
        std::cout << "\n1. Go to Main Menu\n";
        std::cout << "2. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 2) {
            system.saveToFile("bookings.txt");
            exit(0); // Exit the program
        }
        else if (choice != 1) {
            std::cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 1);
}

void listRooms(BookingSystem& system) {
    const auto& rooms = system.getRooms();

    if (rooms.empty()) {
        std::cout << "No Rooms Found.\n";
    }
    else {
        system.showAllRooms();
    }

    int choice;
    do {
        std::cout << "\n1. Go to Main Menu\n";
        std::cout << "2. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 2) {
            system.saveToFile("bookings.txt");
            exit(0); // Exit the program
        }
        else if (choice != 1) {
            std::cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 1);
}

void searchRoom(BookingSystem& system) {
    int roomNumber;
    std::cout << "Enter Room Number to search: ";
    std::cin >> roomNumber;

    const auto& rooms = system.getRooms();
    auto it = rooms.find(roomNumber);

    if (it != rooms.end()) {
        const Room& room = it->second;
        std::cout << "Room Number: " << room.roomNumber << ", Capacity: " << room.capacity
            << ", Facilities: " << room.facilities << "\n";
    }
    else {
        std::cout << "Room not found!\n";
    }

    int choice;
    do {
        std::cout << "\n1. Go to Main Menu\n";
        std::cout << "2. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 2) {
            system.saveToFile("bookings.txt");
            exit(0); // Exit the program
        }
        else if (choice != 1) {
            std::cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 1);
}

void searchBooking(BookingSystem& system) {
    int roomNumber;
    std::cout << "Enter Room Number to search for bookings: ";
    std::cin >> roomNumber;

    system.showRoomBookings(roomNumber);

    int choice;
    do {
        std::cout << "\n1. Go to Main Menu\n";
        std::cout << "2. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 2) {
            system.saveToFile("bookings.txt");
            exit(0); // Exit the program
        }
        else if (choice != 1) {
            std::cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 1);
}

int main() {
    BookingSystem system;

    // Load data from file if exists
    system.loadFromFile("bookings.txt");

    while (true) {
        std::cout << "\nRoom Booking System\n";
        std::cout << "1. Add Room\n";
        std::cout << "2. Add Booking\n";
        std::cout << "3. List All Rooms\n";
        std::cout << "4. List All Bookings\n";
        std::cout << "5. Search Room\n";
        std::cout << "6. Search Booking\n";
        std::cout << "7. Delete Room\n";
        std::cout << "8. Delete Booking\n";
        std::cout << "9. Save and Exit\n";
        std::cout << "\nEnter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            addRoom(system);
            break;
        case 2:
            addBooking(system);
            break;
        case 3:
            listRooms(system);
            break;
        case 4:
            listBookings(system);
            break;
        case 5:
            searchRoom(system);
            break;
        case 6:
            searchBooking(system);
            break;
        case 7:
            deleteRoom(system);
            break;
        case 8:
            deleteBooking(system);
            break;
        case 9:
            system.saveToFile("bookings.txt");
            return 0;
        default:
            std::cout << "Invalid choice, please try again.\n";
        }
    }

    return 0;
}
