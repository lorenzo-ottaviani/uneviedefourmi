#include <iostream>
#include <string>
#include <vector>

#include "ant.hpp"

/* Constructor */
Ant::Ant(int ant_number, const std::string& start_room) : number(ant_number), room(start_room), status("waiting"),
path({}), path_index(0) {}

/* Getters */
int Ant::get_number() const {
        return number;
}
const std::string& Ant::get_room() const {
        return room;
}

const std::string& Ant::get_status() const {
        return status;
}

const std::vector<std::string>& Ant::get_path() const {
        return path;
}

/* Display information */
void Ant::display() const {
        std::cout << "Ant " << number << " in the " << room << "." << std::endl;
}

/* Ants general methods */
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
