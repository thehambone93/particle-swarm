/*
* MIT License
*
* Copyright (c) 2016 Wes Hampson
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

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

    while (true)
    {
        unsigned int elapsed = SDL_GetTicks();

        Uint8 r = (1 + sin(elapsed * 0.0001)) * 127;
        Uint8 g = (1 + sin(elapsed * 0.0004)) * 127;
        Uint8 b = (1 + sin(elapsed * 0.0003)) * 127;

        for (int y = 0; y < swarm::Screen::SCREEN_HEIGHT; y++)
        {
            for (int x = 0; x < swarm::Screen::SCREEN_WIDTH; x++)
            {
                screen.setPixel(x, y, r, g, b);
            }
        }
        screen.update();

        if (!screen.processEvents())
        {
            break;
        }
    }

    screen.close();
    
    return 0;
}