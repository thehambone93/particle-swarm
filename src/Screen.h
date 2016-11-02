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

#ifndef SWARM_SCREEN_H
#define SWARM_SCREEN_H

#include <SDL.h>

namespace swarm
{

class Screen
{
public:
    const static int SCREEN_WIDTH;
    const static int SCREEN_HEIGHT;

private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Texture *m_texture;
    Uint32 *m_bufferPrimary;
    Uint32 *m_bufferSecondary;  /* Need two buffers for box blur algorithm */

public:
    Screen();
    bool init();
    void update();
    void clear();
    void close();
    bool processEvents();
    void setPixel(unsigned int x, unsigned int y, Uint8 r, Uint8 g, Uint8 b);
    void boxBlur();
};

} /* namespace swarm */

#endif /* SWARM_SCREEN_H */
