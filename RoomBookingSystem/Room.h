#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <string>
#include "Booking.h"

class Room {
public:
    int roomNumber;
    int capacity;
    std::string facilities;
    std::vector<Booking> bookings;

    Room() : roomNumber(0), capacity(0), facilities("") {}

    Room(int roomNumber, int capacity, const std::string& facilities)
        : roomNumber(roomNumber), capacity(capacity), facilities(facilities) {}

    void addBooking(const Booking& booking) {
        bookings.push_back(booking);
    }
};

#endif