#include <SDL/SDL.h>  // Pull in the SDL definitions
#include <vector>     // Pull in the std::vector
#include <memory>     // Pull in std::shared_ptr

using namespace std;  // So that we can write `vector` rather than `std::vector`

#include "SFCommon.h"
#include "SFApp.h"

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
  Uint32 colour_depth = 16; // in bits
  Uint32 delay = 1000/60; // in milliseconds
  
  // Initialise SDL - when using C/C++ it's common to have to
  // initialise libraries by calling a function within them.
  if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER)<0) {
    cerr << "Failed to initialise SDL: " << SDL_GetError() << endl;
    throw SF_ERROR_INIT;
  }

  // Create a new window
  if (!(SDL_SetVideoMode(width, height, colour_depth, SDL_DOUBLEBUF))) {
    cerr << "Failed to initialise video mode: " << SDL_GetError() << endl;
    throw SF_ERROR_VIDEOMODE;
  }

  SDL_WM_SetCaption("Starship Fontana", "Starship Fontana");

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
  sfapp = shared_ptr<SFApp>(new SFApp());

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
