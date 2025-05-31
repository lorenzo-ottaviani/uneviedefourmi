#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <queue>
#include <regex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "anthill.hpp"

/* Constructor */
Anthill::Anthill()
    : start("Sv")
{
    ant_number = parse_ant_number();
    graph = parse_graph();
    empty_places = parse_empty_places();
}

/* Getters */
int Anthill::get_ant_number() const {
    return ant_number;
}

const std::unordered_map<std::string, std::vector<std::string>>& Anthill::get_graph() const {
    return graph;
}

const std::unordered_map<std::string, int>& Anthill::get_empty_places() const {
    return empty_places;
}

/* Methods to extract information from a file */
std::vector<std::string> Anthill::read_file() {
    const std::string path = "../assets/anthills/fourmiliere_zero.txt";
    std::ifstream file(path);

    if(!file)
    {
        std::cerr << "Error opening file. Please check if the path is correct: '" << path << "'" << std::endl;
        return {};
    }

    std::string line;
    std::vector<std::string> anthill;

    while(getline(file, line))
    {
        anthill.push_back(line);
    }

    return anthill;
}

int Anthill::parse_ant_number() {
    std::vector<std::string> instructions = read_file();
    int ant_count = 0;

    if (instructions.empty()) return ant_count;  // When file reading error or file is empty

    /* Extract ant count */
    std::string line = instructions.at(0);
    size_t pos = line.find('=');
    if (pos != std::string::npos) {
        ant_count = std::stoi(line.substr(pos + 1));
    }

    return ant_count;
}

std::unordered_map<std::string, std::vector<std::string>> Anthill::parse_graph() {
    std::vector<std::string> instructions = read_file();
    std::unordered_map<std::string, std::vector<std::string>> graph;

    if (instructions.empty()) return graph;  // When file reading error or file is empty


    /* Parse connections */
    std::string line = instructions.at(0);
    for (size_t i = 1; i < instructions.size(); ++i) {
        line = instructions.at(i);

        size_t dash = line.find('-');
        if (dash != std::string::npos) {
            // Clean and split: "Sv - S1" to "Sv" and "S1"
            std::string left = line.substr(0, dash);
            std::string right = line.substr(dash + 1);

            // Remove spaces
            left.erase(remove_if(left.begin(), left.end(), isspace), left.end());
            right.erase(remove_if(right.begin(), right.end(), isspace), right.end());

            // Add bidirectional edges
            graph[left].push_back(right);
            graph[right].push_back(left);
        }
    }

    return graph;
}

std::unordered_map<std::string, int> Anthill::parse_empty_places() {
    std::vector<std::string> instructions = read_file();
    std::unordered_map<std::string, int> empty_map;

    std::regex with_value(R"((\w+)\s*\{\s*(\d+)\s*\})"); // regex for room like : S1 { 8 }
    std::regex no_value(R"((\w+)\s*$)");                 // regex form room like : S9
    std::smatch match;

    /* Rooms details */
    for (const auto& line : instructions) {
        if (line.find('-') != std::string::npos) break; // End reading when graph beggin

        if (std::regex_match(line, match, with_value)) {
            std::string room = match[1];
            int count = std::stoi(match[2]);
            empty_map[room] = count;
        } else if (std::regex_match(line, match, no_value)) {
            std::string room = match[1];
            empty_map[room] = 1;
        }
    }

    return empty_map;
}

void Anthill::bfs() {
    std::unordered_set<std::string> visited;
    std::queue<std::string> queue;
    queue.push(start);

    while (!queue.empty()) {
        std::string node = queue.front();
        queue.pop();

        if (visited.find(node) == visited.end()) {
            std::cout << node << " ";
            visited.insert(node);
            auto it = graph.find(node);
            if (it != graph.end()) {
                for (const std::string& adjacent : it->second) {
                    queue.push(adjacent);
                }
            }
        }
    }
}
