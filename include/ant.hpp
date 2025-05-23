# pragma once
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
    int getNumber() const;
    std::string getRoom() const;
    std::string getStatus() const;
};
