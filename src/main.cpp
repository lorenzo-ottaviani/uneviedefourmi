/*
* Author : Lorenzo OTTAVIANI.
* Date : 27/05/2025 10h06
* Aim of the program :
*    Ants.
* Input : ∅
* Output : Ants everywhere!
*/

#include <iostream>
#include <string>
#include <vector>

#include "ant.hpp"
#include "anthill.hpp"

int main() {
    std::cout << "Hello, it's an Ant World !" << std::endl;

    Anthill anthill_test;
    std::vector<std::string> file_test = anthill_test.read_file();
    for (const std::string& line : file_test) {
        std::cout << line << std::endl;
    }

    std::cout << "Number of ants: " << anthill_test.get_ant_number() << std::endl;

    std::cout << "\nGraph connections:\n";
    auto graph = anthill_test.get_graph();
    for (const auto& [room, connections] : graph) {
        std::cout << room << " -> ";
        for (const auto& connected_room : connections) {
            std::cout << connected_room << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "\nEmpty places (room capacities):\n";
    auto empty_places = anthill_test.get_empty_places();
    for (const auto& [room, capacity] : empty_places) {
        std::cout << room << " : " << capacity << std::endl;
    }

    Ant ant_1(1);
    ant_1.display();

    std::string my_room = "Cell";
    ant_1.move(my_room);
    ant_1.display();

    ant_1.change_status();
    ant_1.display();

    return 0;
}