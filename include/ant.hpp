#pragma once

#include <string>

class Ant {
private:
    int number;
    std::string room;
    std::string status;

public:
    /* Constructor */
    Ant(int AntNumber);

    /* Getters */
    int get_number() const;
    std::string get_room() const;
    std::string get_status() const;

    /* Display information */
    void display() const;

    /* Methods */
    void move(std::string room);
    void change_status();
};
