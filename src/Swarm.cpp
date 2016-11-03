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

#define _USE_MATH_DEFINES

#include <math.h>
#include <stdlib.h>

#include "Swarm.h"

namespace swarm
{

const int Swarm::NUM_PARTICLES = 5000;
const int Swarm::PARTICLE_MIN_X = -1;
const int Swarm::PARTICLE_MAX_X = 1;
const int Swarm::PARTICLE_MIN_Y = -1;
const int Swarm::PARTICLE_MAX_Y = 1;

Swarm::Swarm()
{
    m_particles = new Particle[NUM_PARTICLES];

    for (int i = 0; i < NUM_PARTICLES; i++)
    {
        init_particle(&m_particles[i]);
    }
}

Swarm::~Swarm()
{
    delete[] m_particles;
}

const Particle *const Swarm::get_particles()
{
    return m_particles;
}

void Swarm::update()
{
    for (int i = 0; i < NUM_PARTICLES; i++)
    {
        update_particle(&m_particles[i]);
    }
}

void Swarm::init_particle(Particle *p)
{
    p->m_x = 0;
    p->m_y = 0;

    // Give the particle a random velocity
    p->m_speed = (0.08 * rand()) / RAND_MAX;
    p->m_direction = (2.0 * M_PI * rand()) / RAND_MAX;
}

void Swarm::update_particle(Particle *p)
{
    // Advance the particle position based on its velocity
    p->m_x += p->m_speed * cos(p->m_direction);
    p->m_y += p->m_speed * sin(p->m_direction);

    // Slowly change the particle's direction
    p->m_direction += 0.0008;   // TODO: make this dynamic

    // Reinitalize particle if it goes off-screen
    if (p->m_x < PARTICLE_MIN_X || p->m_x > PARTICLE_MAX_X ||
        p->m_y < PARTICLE_MIN_Y || p->m_y > PARTICLE_MAX_Y)
    {
        init_particle(p);
    }

    // Reinitalize particle at random
    if (rand() < RAND_MAX * 0.0001)
    {
        init_particle(p);
    }
}

}