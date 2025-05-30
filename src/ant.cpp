#include <iostream>
#include <string>

#include "ant.hpp"

/* Constructor */
Ant::Ant(int AntNumber) : number(AntNumber), room("hall"), status("waiting") {}

/* Getters */
int Ant::get_number() const {
        return number;
}
std::string Ant::get_room() const {
        return room;
}

std::string Ant::get_status() const {
        return status;
}

/* Display information */
void Ant::display() const {
        std::cout << "I am the ant " << number << ", I am in the " << room << " and I am "<< status
        << "." << std::endl;
}

/* Methods */
void Ant::move(std::string room) {
        this->room = room;
}

void Ant::change_status() {
        if (status == "waiting") {
                this->status = "moving";
        } else if (status == "moving") {
                this->status = "waiting";
        }
}
