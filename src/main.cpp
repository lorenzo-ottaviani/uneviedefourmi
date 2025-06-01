/*
* Author : Lorenzo OTTAVIANI.
* Date : 01/06/2025 17h03
* Aim of the program :
*    Ants.
* Input : ∅
* Output : Ants everywhere!
*/

#include <iostream>

#include "ant.hpp"
#include "anthill.hpp"

int main() {
    std::cout << "Hello, it's an Ant World !\n" << std::endl;

    Anthill anthill;

    // Simulate ants moving step-by-step
    anthill.simulate_movement();

    return 0;
}