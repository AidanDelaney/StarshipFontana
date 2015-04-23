#include <SDL2/SDL.h> // Pull in the SDL definitions
#include <memory>     // Pull in std::shared_ptr

using namespace std;  // So that we can write `vector` rather than `std::vector`

#include "SFCommon.h"
#include "SFApp.h"

// Very Uncool Global Variable
// Fixme: Bonus points for making this go away.
SDL_Window * g_window;
SDL_Renderer * g_renderer;

enum userEvents{UPDATE_EVENT};

Uint32 PushUpdateEvent(Uint32 interval, void *param) {
  SDL_Event event;
  event.type       = SDL_USEREVENT;
  event.user.code  = UPDATE_EVENT;
  event.user.data1 = 0;
  event.user.data2 = 0;
  SDL_PushEvent(&event);
  return interval;
}

SFError InitGraphics() {
  Uint32 width = 640;
  Uint32 height = 480;

  // Initialise SDL - when using C/C++ it's common to have to
  // initialise libraries by calling a function within them.
  if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER)<0) {
    cerr << "Failed to initialise SDL: " << SDL_GetError() << endl;
    throw SF_ERROR_INIT;
  }

  // Create a new window
  g_window = SDL_CreateWindow("StarShip Fontana"
                            , SDL_WINDOWPOS_CENTERED
                            , SDL_WINDOWPOS_CENTERED
                            , width
                            , height
                            , SDL_WINDOW_SHOWN);
  if (!g_window) {
    cerr << "Failed to initialise video mode: " << SDL_GetError() << endl;
    throw SF_ERROR_VIDEOMODE;
  }

  g_renderer = SDL_CreateRenderer(g_window, -1, 0);
  if (!g_renderer) {
    cerr << "Failed to create renderer: " << SDL_GetError() << endl;
    throw SF_ERROR_VIDEOMODE;
  }

  SDL_SetRenderDrawColor(g_renderer, 128, 128, 128, 255);

  return SF_ERROR_NONE;
}

int main(int arc, char ** argv) {
  shared_ptr<SFApp> sfapp = nullptr;

  // Initialise graphics context
  try {
    InitGraphics();
  } catch (SFError e) {
    return e;
  }

  // Initialise world
  std::shared_ptr<SFWindow> window = make_shared<SFWindow>(g_window, g_renderer);
  sfapp = shared_ptr<SFApp>(new SFApp(window));

  // Set up top-level timer to UpdateWorld
  // Call the function "display" every delay milliseconds
  int delay = 1000/60; // 1000 milis in a second, divide by 60 - the framerate
  SDL_AddTimer(delay, PushUpdateEvent, NULL);

  // Start game loop
  sfapp->OnExecute();

  // Delete the app -- allows the SFApp object to do its own cleanup
  sfapp.reset();
  return SF_ERROR_NONE;
}
