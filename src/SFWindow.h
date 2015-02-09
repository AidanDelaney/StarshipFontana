#ifndef SFWINDOW_H
#define SFWINDOW_H

#include <SDL2/SDL.h>

class SFWindow {
 public:
  SFWindow(SDL_Window*, SDL_Renderer*);
  SDL_Window* getWindow();
  SDL_Renderer* getRenderer();
 private:
  SDL_Window*   window;
  SDL_Renderer* renderer;
};

#endif
