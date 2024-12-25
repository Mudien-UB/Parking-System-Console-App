#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <regex>
#include <string>
#include <cctype>

#include "Vehicle.cpp"

class ParkingLot {
private:
    std::vector<std::unique_ptr<Vehicle>> slots;

    bool isOddPlate(const std::string& registrationNumber) {
        if (registrationNumber.empty()) return false;

        std::regex patern(R"((\d+))");
        std::smatch match;
        std::regex_search(registrationNumber, match, patern);
        return std::stoi(match[1]) % 2 == 1;
    }

public:
    ParkingLot(int totalSlots) : slots(totalSlots) {}

    std::string parkVehicle(const std::string& reg, const std::string& type, const std::string& colour) {
        for (size_t i = 0; i < slots.size(); ++i) {
            if (!slots[i]) {
                slots[i] = std::make_unique<Vehicle>(reg, type, colour);
                return "Allocated slot number: " + std::to_string(i + 1);
            }
        }
        return "Sorry, parking lot is full";
    }

    std::string leaveVehicle(int slot) {
        if (slot < 1 || slot > static_cast<int>(slots.size()) || !slots[slot - 1]) {
            return "Slot not found";
        }
        slots[slot - 1].reset();
        return "Slot number " + std::to_string(slot) + " is free";
    }

    void status() {
        std::cout << "Slot No.\tRegistration No\tType\tColour\n";
        for (size_t i = 0; i < slots.size(); ++i) {
            if (slots[i]) {
                std::cout << (i + 1) << "\t" << slots[i]->registrationNumber << "\t"
                          << slots[i]->type << "\t" << slots[i]->colour << "\n";
            }
        }
    }

    std::string getRegistrationNumbersByPlateType(bool isOdd) {
        std::vector<std::string> results;
        for (const auto& slot : slots) {
            if (slot && isOddPlate(slot->registrationNumber) == isOdd) {
                results.push_back(slot->registrationNumber);
            }
        }
        return results.empty() ? "" : join(results, ", ");
    }

    std::string getRegistrationNumberBySlot(int slot) {
        if (slot < 1 || slot > static_cast<int>(slots.size()) || !slots[slot - 1]) {
            return "-";
        }
        return slots[slot - 1]->registrationNumber;
    }

    std::string getSlotByRegistrationNumber(const std::string& reg) {
        for (size_t i = 0; i < slots.size(); ++i) {
            if (slots[i] && slots[i]->registrationNumber == reg) {
                return std::to_string(i + 1);
            }
        }
        return "-";
    }

    std::string getSlotByColour(const std::string& colour) {
        std::string result;
        for (size_t i = 0; i < slots.size(); ++i) {
            if (slots[i] && slots[i]->colour == colour) {
                if (!result.empty()) result += ", ";
                result += std::to_string(i + 1);
            }
        }
        return (result.empty()) ? "-" : result;
    }

    int getCountByType(const std::string& type) {
        int count = 0;
        for (const auto& slot : slots) {
            if (slot && slot->type == type) {
                count++;
            }
        }
        return count;
    }

    int getCountByColour(const std::string& colour) {
        int count = 0;
        for (const auto& slot : slots) {
            if (slot && slot->colour == colour) {
                count++;
            }
        }
        return count;
    }

private:
    static std::string join(const std::vector<std::string>& elements, const std::string& delimiter) {
        std::string result;
        for (size_t i = 0; i < elements.size(); ++i) {
            result += elements[i];
            if (i < elements.size() - 1) result += delimiter;
        }
        return result;
    }
};