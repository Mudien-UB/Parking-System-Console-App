#include <string>

class Vehicle {
public:
    std::string registrationNumber;
    std::string type;
    std::string colour;

    Vehicle(std::string reg, std::string type, std::string colour)
        : registrationNumber(reg), type(type), colour(colour) {}
};