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
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "Particle.h"
#include "Screen.h"
#include "Swarm.h"

int main(int argc, char* argv[])
{
    srand(time(NULL));

    swarm::Screen screen;
    if (!screen.init())
    {
        std::cerr << "Failed to create screen!" << std::endl;
        screen.close();
        return 1;
    }

    swarm::Swarm swarm;

    const int HALF_WIDTH = swarm::Screen::SCREEN_WIDTH / 2;
    const int HALF_HEIGHT = swarm::Screen::SCREEN_HEIGHT / 2;

    while (true)
    {
        unsigned int elapsed = SDL_GetTicks();

        swarm.update();

        Uint8 r = (1 + sin(elapsed * 0.0001)) * 127;
        Uint8 g = (1 + sin(elapsed * 0.0004)) * 127;
        Uint8 b = (1 + sin(elapsed * 0.0003)) * 127;

        const swarm::Particle *const particles = swarm.get_particles();
        for (int i = 0; i < swarm::Swarm::NUM_PARTICLES; i++)
        {
            swarm::Particle particle = particles[i];

            // Convert cartesian (x,y) to screen (x,y) without stretching
            int x = (particle.m_x + 1) * HALF_WIDTH;
            int y = (particle.m_y * HALF_WIDTH) + HALF_HEIGHT;

            screen.setPixel(x, y, r, g, b);
        }

        screen.update();
        screen.boxBlur();

        if (!screen.processEvents())
        {
            break;
        }
    }

    screen.close();
    
    return 0;
}
