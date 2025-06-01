#pragma once

#include <string>
#include <vector>

class Ant {
private:
    int number;
    std::string room;
    std::string status;
    std::vector<std::string> path;
    size_t path_index;

public:
    /* Constructor */
    Ant(int ant_number, const std::string& start_room);

    /* Getters */
    int get_number() const;
    const std::string& get_room() const;
    const std::string& get_status() const;
    const std::vector<std::string>& get_path() const;

    /* Display information */
    void display() const;

    /* Ants general methods */
    void move(std::string room);
    void change_status();

};
