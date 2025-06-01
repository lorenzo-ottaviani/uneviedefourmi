#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "ant.hpp"

class Anthill {
private:
    int ant_number;
    std::vector<Ant> ants;  // Ant object vector of ant_number size.
    std::string start;  // All graphs start in Sv.
    const std::string end;  // All graphs end in Sd.
    std::unordered_map<std::string, std::vector<std::string>> graph;
    std::unordered_map<std::string, int> available_places; // The capacity of rooms where it is not unlimited.

public:
    /* Constructor */
    Anthill();

    /* Getters */
    int get_ant_number() const;
    const std::vector<Ant>& get_ants() const;
    const std::unordered_map<std::string, std::vector<std::string>>& get_graph() const;
    const std::unordered_map<std::string, int>& get_available_places() const;

    /* Methods to extract information from a file */
    std::vector<std::string> read_file();
    int parse_ant_number();
    std::unordered_map<std::string, std::vector<std::string>> parse_graph();
    std::unordered_map<std::string, int> parse_available_places();

    /* Graphs algorithms */
    std::vector<std::string> bfs(const std::string& from);

    /* Ants methods */
    void create_ants();
    void simulate_movement();
};
