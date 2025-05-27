#ifndef BOOKING_H
#define BOOKING_H

#include <string>

class Booking {
public:
    static int idCounter; // Static counter to generate unique IDs
    int bookingID;
    std::string host;
    std::string startDate;
    std::string endDate;
    std::string startTime;
    std::string endTime;
    int attendees;

    Booking() : bookingID(++idCounter), host(""), startDate(""), endDate(""), startTime(""), endTime(""), attendees(0) {}

    Booking(const std::string& host, const std::string& startDate, const std::string& endDate,
        const std::string& startTime, const std::string& endTime, int attendees)
        : bookingID(++idCounter), host(host), startDate(startDate), endDate(endDate),
        startTime(startTime), endTime(endTime), attendees(attendees) {}
};

int Booking::idCounter = 0; // Initialize static counter

#endif