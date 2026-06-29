#include "SDL3/SDL_init.h"
#include "SDL3/SDL_video.h"
#include <SDL3/SDL.h>

int main() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("SDL Failed to Initialize.");
    return -1;
  }

  SDL_Window *window;
  window = SDL_CreateWindow("BURZA", 600, 600, SDL_WINDOW_RESIZABLE);

  SDL_Delay(5000);

  SDL_Quit();
}
