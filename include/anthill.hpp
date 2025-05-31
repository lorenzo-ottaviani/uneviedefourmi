#pragma once

#include <string>
#include <unordered_map>
#include <vector>

class Anthill {
private:
    int ant_number;
    const std::string start;
    std::unordered_map<std::string, std::vector<std::string>> graph;
    std::unordered_map<std::string, int> empty_places;

public:
    /* Constructor */
    Anthill();

    /* Getters */
    int get_ant_number() const;
    const std::unordered_map<std::string, std::vector<std::string>>& get_graph() const;
    const std::unordered_map<std::string, int>& get_empty_places() const;

    /* Methods to extract information from a file */
    std::vector<std::string> read_file();
    int parse_ant_number();
    std::unordered_map<std::string, std::vector<std::string>> parse_graph();
    std::unordered_map<std::string, int> parse_empty_places();

    /* Graphs algorithms */
    void bfs();

    /* Others methods */
    void change_empty_places(const std::string& room);
};
