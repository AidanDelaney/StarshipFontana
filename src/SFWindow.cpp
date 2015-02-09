#include "SFWindow.h"

SFWindow::SFWindow(SDL_Window * w, SDL_Renderer * r): window(w), renderer(r) {
}

SDL_Window * SFWindow::getWindow() {
  return window;
}

SDL_Renderer * SFWindow::getRenderer() {
  return renderer;
}
