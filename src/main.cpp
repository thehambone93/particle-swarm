#include <iostream>

#include "Screen.h"

int main(int argc, char* argv[])
{
    swarm::Screen screen;
    if (!screen.init())
    {
        std::cerr << "Failed to create screen!" << std::endl;
        screen.close();
        return 1;
    }
    
    screen.update();

    while (true)
    {
        if (!screen.processEvents())
        {
            break;
        }
    }

    screen.close();
    
    return 0;
}