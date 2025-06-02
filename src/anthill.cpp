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

#include "ant.hpp"
#include "anthill.hpp"

/* Constructor */
Anthill::Anthill()
    : start("Sv"), end("Sd")
{
    ant_number = parse_ant_number();
    create_ants();
    graph = parse_graph();
    available_places = parse_available_places();
}

/* Getters */
int Anthill::get_ant_number() const {
    return ant_number;
}

const std::vector<Ant>& Anthill::get_ants() const {
    return ants;
}

const std::unordered_map<std::string, std::vector<std::string>>& Anthill::get_graph() const {
    return graph;
}

const std::unordered_map<std::string, int>& Anthill::get_available_places() const {
    return available_places;
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

std::unordered_map<std::string, int> Anthill::parse_available_places() {
    std::vector<std::string> instructions = read_file();
    std::unordered_map<std::string, int> available_map;

    std::regex with_value(R"((\w+)\s*\{\s*(\d+)\s*\})"); // regex for room like : S1 { 8 }
    std::regex no_value(R"((\w+)\s*$)");                 // regex form room like : S9
    std::smatch match;

    /* Rooms details */
    for (const auto& line : instructions) {
        if (line.find('-') != std::string::npos) break; // End reading when graph beggin

        if (std::regex_match(line, match, with_value)) {
            std::string room = match[1];
            int count = std::stoi(match[2]);
            available_map[room] = count;
        } else if (std::regex_match(line, match, no_value)) {
            std::string room = match[1];
            available_map[room] = 1;
        }
    }

    return available_map;
}

/* Graphs algorithms */

/**
 * @brief Finds the shortest path from start to end in the graph using BFS.
 *
 * @param from The current start room used.
 * @return std::vector<std::string> The path from start to end.
 *         Returns an empty vector if no path is found.
 */
std::vector<std::string> Anthill::bfs(const std::string& actual_room) {
    std::unordered_map<std::string, std::string> parent;
    std::queue<std::string> queue;
    std::unordered_set<std::string> visited;

    queue.push(actual_room);
    visited.insert(actual_room);

    while (!queue.empty()) {
        std::string current = queue.front();
        queue.pop();

        if (current == end) {
            std::vector<std::string> path;
            for (std::string at = end; at != ""; at = parent[at]) {
                path.push_back(at);
                if (at == actual_room) break;
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        auto it = graph.find(current);
        if (it != graph.end()) {
            for (const auto& neighbor : it->second) {
                if (neighbor != start && neighbor != end && available_places.at(neighbor) <= 0) continue;
                if (visited.count(neighbor) == 0) {
                    visited.insert(neighbor);
                    parent[neighbor] = current;
                    queue.push(neighbor);
                }
            }
        }
    }

    return {};
}

/* Ants methods */

/**
 * @brief Create an Ant object for each ant int the anthill.
 *
 * Ants objects are stocked in a vector of ant_number size.
 */
void Anthill::create_ants() {
    for (int i = 1; i < ant_number + 1; ++i) {
        ants.emplace_back(i, start);
    }
}

/**
 * @brief Simulates ants moving step by step along their assigned paths.
 *
 * At each step, each ant moves forward by one room if the next room is available.
 * The start and end rooms have infinite capacity; other rooms have limited capacity defined in available_places.
 * Displays each ant’s movement at every step.
 */
void Anthill::simulate_movement() {
    int step = 0;

    while (true) {
        bool any_moved = false;

        // Phase 1: Display
        std::cout << "Step " << step << std::endl;
        for (const Ant& ant : ants) {
            ant.display();
        }
        std::cout << std::endl;

        // Phase 2: Movement
        for (auto& ant : ants) {
            if (ant.get_room() == end) continue;

            std::vector<std::string> path = bfs(ant.get_room());
            if (path.size() < 2) continue;

            std::string current_room = path[0];
            std::string next_room = path[1];

            if (next_room == start || next_room == end || available_places[next_room] > 0) {
                if (current_room != start && current_room != end)
                    available_places[current_room]++;

                if (next_room != start && next_room != end)
                    available_places[next_room]--;

                ant.move(next_room);
                any_moved = true;
            }
        }

        if (!any_moved) break;

        step++;
    }
}
