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

#include <cstring>

#include "Screen.h"

namespace swarm
{

const int Screen::SCREEN_WIDTH = 800;
const int Screen::SCREEN_HEIGHT = 600;

Screen::Screen() :
    m_window(NULL),
    m_renderer(NULL),
    m_texture(NULL),
    m_bufferPrimary(NULL),
    m_bufferSecondary(NULL)
{ }

bool Screen::init()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        return false;
    }

    // Create SDL window
    m_window = SDL_CreateWindow(
        "Particle Swarm",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (m_window == NULL)
    {
        close();
        return false;
    }

    // Create SDL renderer for rendering textures
    m_renderer = SDL_CreateRenderer(
        m_window,
        -1,
        SDL_RENDERER_PRESENTVSYNC);
    if (m_renderer == NULL)
    {
        close();
        return false;
    }

    // Create SDL texture, we will write pixel information to this texture
    m_texture = SDL_CreateTexture(
        m_renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STATIC,
        SCREEN_WIDTH,
        SCREEN_HEIGHT);
    if (m_texture == NULL)
    {
        close();
        return false;
    }

    // Allocate pixel buffers
    // A second buffer is needed for creating box blur
    m_bufferPrimary = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
    m_bufferSecondary = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
    if (m_bufferPrimary == NULL || m_bufferSecondary == NULL)
    {
        close();
        return false;
    }

    // Set all pixels to black
    clear();

    return true;
}

void Screen::update()
{
    SDL_UpdateTexture(m_texture, NULL, m_bufferPrimary, SCREEN_WIDTH * sizeof(Uint32));
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
    SDL_RenderPresent(m_renderer);
}

void Screen::clear()
{
    memset(m_bufferPrimary, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(Uint32));
    memset(m_bufferSecondary, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(Uint32));
}

void Screen::close()
{
    delete[] m_bufferPrimary;
    delete[] m_bufferSecondary;
    SDL_DestroyTexture(m_texture);
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

bool Screen::processEvents()
{
    SDL_Event e;
    
    while (SDL_PollEvent(&e))
    {
        // Check for window close event
        if (e.type == SDL_QUIT)
        {
            return false;
        }
    }

    return true;
}

void Screen::setPixel(unsigned int x, unsigned int y, Uint8 r, Uint8 g, Uint8 b)
{
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
    {
        return;
    }

    Uint32 color = (r << 24) | (g << 16) | (b << 8) | 0xFF;
    m_bufferPrimary[(y * SCREEN_WIDTH) + x] = color;
}


} /* namespace swarm */