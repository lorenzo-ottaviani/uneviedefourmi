#include <string>

#include "ant.hpp"

/* Constructor */
Ant::Ant(int AntNumber) : number(AntNumber), room("hall"), status("waiting") {}

/* Getters */
    int Ant::getNumber() const {
        return number;
}
    std::string Ant::getRoom() const {
        return room;
}

    std::string Ant::getStatus() const {
        return status;
}
