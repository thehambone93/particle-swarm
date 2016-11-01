#include <iostream>

#include <SDL.h>

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL initialization failed!" << std::endl;
	}
    else 
    {
        std::cout << "SDL initialized successfully!" << std::endl;
    }
    
    SDL_Quit();
    
    return 0;
}