#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <cctype>

#include "ParkingLot.cpp"




int main() {
    std::unique_ptr<ParkingLot> parkingLot;
    bool isRunning = true;

    while (isRunning) {
        std::string input;
        std::getline(std::cin, input);

        std::istringstream iss(input);
        std::vector<std::string> commands;
        std::string command;
        while (iss >> command) {
            commands.push_back(command);
        }

        if (commands.empty()) continue; 

        if (commands[0] == "create_parking_lot") {
            int slots = std::stoi(commands[1]);
            parkingLot = std::make_unique<ParkingLot>(slots);
            std::cout << "Created a parking lot with " << slots << " slots\n";

        } else if (commands[0] == "park") {
            if (parkingLot) {
                std::cout << parkingLot->parkVehicle(commands[1], commands[2], commands[3]) << "\n";
            }

        } else if (commands[0] == "leave") {
            if (parkingLot) {
                int slot = std::stoi(commands[1]);
                std::cout << parkingLot->leaveVehicle(slot) << "\n";
            }

        } else if (commands[0] == "status") {
            if (parkingLot) {
                parkingLot->status();
            }

        } else if (commands[0] == "registration_numbers_for_vehicles_with_odd_plate") {
            if (parkingLot) {
                std::cout << parkingLot->getRegistrationNumbersByPlateType(true) << "\n";
            }

        } else if (commands[0] == "registration_numbers_for_vehicles_with_even_plate") {
            if (parkingLot) {
                std::cout << parkingLot->getRegistrationNumbersByPlateType(false) << "\n";
            }

        } else if (commands[0] == "slot_number_for_registration_number") {
            if (parkingLot) {
                std::cout << parkingLot->getSlotByRegistrationNumber(commands[1]) << "\n";
            }

        } else if (commands[0] == "vehicle_reg_number_for_slot") {
            if (parkingLot) {
                std::cout << parkingLot->getRegistrationNumberBySlot(std::stoi(commands[1])) << "\n";
            }

        } else if (commands[0] == "slot_number_for_vehicle_with_colour") {
            if (parkingLot) {
                std::cout << parkingLot->getSlotByColour(commands[1]) << "\n";
            }

        } else if (commands[0] == "count_by_colour") {
            if (parkingLot) {
                std::cout << parkingLot->getCountByColour(commands[1]) << "\n";
            }

        } else if (commands[0] == "count_by_type") {
            if (parkingLot) {
                std::cout << parkingLot->getCountByType(commands[1]) << "\n";
            }

        } else if (commands[0] == "exit") {
            isRunning = false;

        } else if (commands[0] == "help") {
            std::cout << "Available commands:\n";
            std::cout << "create_parking_lot <slots>\n";
            std::cout << "park <reg> <type> <colour>\n";
            std::cout << "leave <slot>\n";
            std::cout << "status\n";
            std::cout << "registration_numbers_for_vehicles_with_odd_plate\n";
            std::cout << "registration_numbers_for_vehicles_with_even_plate\n";
            std::cout << "slot_number_for_registration_number <reg>\n";
            std::cout << "vehicle_reg_number_for_slot <slot>\n";
            std::cout << "slot_number_for_vehicle_with_colour <colour>\n";
            std::cout << "count_by_colour <colour>\n";
            std::cout << "count_by_type <type>\n";
            std::cout << "exit\n";
        } else {
            std::cout << "Invalid command\n";
        }
    }

    return 0;
}
