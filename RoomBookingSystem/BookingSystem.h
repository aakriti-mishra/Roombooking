#ifndef BOOKINGSYSTEM_H
#define BOOKINGSYSTEM_H

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Room.h"

class BookingSystem {
private:
    std::map<int, Room> rooms;

public:
    void addRoom(int roomNumber, int capacity, const std::string& facilities) {
        rooms[roomNumber] = Room(roomNumber, capacity, facilities);
    }

    void deleteRoom(int roomNumber) {
        if (rooms.erase(roomNumber)) {
            std::cout << "Room deleted successfully." << std::endl;
        }
        else {
            std::cout << "Room not found!" << std::endl;
        }
    }

    void bookRoom(int roomNumber, const Booking& booking) {
        if (rooms.find(roomNumber) != rooms.end()) {
            rooms[roomNumber].addBooking(booking);
        }
        else {
            std::cout << "Room not found!" << std::endl;
        }
    }

    void deleteBooking(int roomNumber, int bookingID) {
        if (rooms.find(roomNumber) != rooms.end()) {
            auto& bookings = rooms[roomNumber].bookings;
            auto it = std::remove_if(bookings.begin(), bookings.end(),
                [&](const Booking& b) { return b.bookingID == bookingID; });

            if (it != bookings.end()) {
                bookings.erase(it, bookings.end());
                std::cout << "Booking deleted successfully." << std::endl;
            }
            else {
                std::cout << "Booking ID not found!" << std::endl;
            }
        }
        else {
            std::cout << "Room not found!" << std::endl;
        }
    }

    void showRoomBookings(int roomNumber) {
        if (rooms.find(roomNumber) != rooms.end()) {
            for (const auto& booking : rooms[roomNumber].bookings) {
                std::cout << "Booking ID: " << booking.bookingID << "\n";
                std::cout << "Host: " << booking.host << ", Start Date: " << booking.startDate
                    << ", End Date: " << booking.endDate << ", Start Time: " << booking.startTime
                    << ", End Time: " << booking.endTime << ", Attendees: " << booking.attendees << std::endl;
            }
        }
        else {
            std::cout << "Room not found!" << std::endl;
        }
    }

    void showAllBookings() {
        for (const auto& pair : rooms) {
            const Room& room = pair.second;
            for (const auto& booking : room.bookings) {
                std::cout << "Room Number: " << room.roomNumber << "\n";
                std::cout << "Booking ID: " << booking.bookingID << ", Host: " << booking.host
                    << ", Start Date: " << booking.startDate << ", End Date: " << booking.endDate
                    << ", Start Time: " << booking.startTime << ", End Time: " << booking.endTime
                    << ", Attendees: " << booking.attendees << "\n\n";
            }
        }
    }

    void showAllRooms() {
        for (const auto& pair : rooms) {
            const Room& room = pair.second;
            std::cout << "Room Number: " << room.roomNumber << ", Capacity: " << room.capacity
                << ", Facilities: " << room.facilities << "\n";
        }
    }

    std::map<int, Room>& getRooms() {
        return rooms;
    }

    void saveToFile(const std::string& filename) {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& pair : rooms) {
                const Room& room = pair.second;
                file << "R," << room.roomNumber << "," << room.capacity << "," << room.facilities << "\n";
                for (const auto& booking : room.bookings) {
                    file << "B," << room.roomNumber << "," << booking.bookingID << ","
                        << booking.host << "," << booking.startDate << "," << booking.endDate
                        << "," << booking.startTime << "," << booking.endTime
                        << "," << booking.attendees << "\n";
                }
            }
            file.close();
        }
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string type;
            std::getline(ss, type, ',');

            if (type == "R") {
                int roomNumber, capacity;
                std::string facilities;
                ss >> roomNumber;
                ss.ignore(); // Ignore comma
                ss >> capacity;
                ss.ignore(); // Ignore comma
                std::getline(ss, facilities);
                rooms[roomNumber] = Room(roomNumber, capacity, facilities);
            }
            else if (type == "B") {
                int roomNumber, bookingID, attendees;
                std::string host, startDate, endDate, startTime, endTime;
                ss >> roomNumber;
                ss.ignore(); // Ignore comma
                ss >> bookingID;
                ss.ignore(); // Ignore comma
                std::getline(ss, host, ',');
                std::getline(ss, startDate, ',');
                std::getline(ss, endDate, ',');
                std::getline(ss, startTime, ',');
                std::getline(ss, endTime, ',');
                ss >> attendees;
                Booking booking(host, startDate, endDate, startTime, endTime, attendees);
                booking.bookingID = bookingID;
                rooms[roomNumber].addBooking(booking);
            }
        }
        file.close();
    }
};

#endif
