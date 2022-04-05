

#include "Engine.hpp"
#include "../Config/Config.hpp"
#include "../Map/Map.hpp"
#include <SDL2/SDL_timer.h>
#include <iostream>
#include <iterator>

ConquerEngine::ConquerEngine(ConquerConfig config)
    : map(ConquerMap(config)), _windowHeight(config.getWindowHeight()),
      _windowWidth(config.getWindowWidth()),
      _windowName(config.getWindowTitle()),
      speed(config.getGameSpeed()) {
  init();
};

ConquerEngine::~ConquerEngine() { map.~ConquerMap(); }

void ConquerEngine::init() {
 
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    printf("error initializing SDL: %s\n", SDL_GetError());
  }
  window = SDL_CreateWindow("GAME", // creates a window
                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            _windowWidth, _windowHeight, 0);

  // triggers the program that controls
  // your graphics hardware and sets flags
  Uint32 render_flags = SDL_RENDERER_ACCELERATED;

  // creates a renderer to render our images
  renderer = SDL_CreateRenderer(window, -1, render_flags);

  // loads image to our graphics hardware memory.
  tex = SDL_CreateTextureFromSurface(renderer, map.getMap());

  // connects our texture with dest to control position
  SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);

  // adjust height and width of our image box.
  dest.w /= 12;
  dest.h /= 12;

  // sets initial x-position of object
  dest.x = (_windowWidth - dest.w) / 2;

  // sets initial y-position of object
  dest.y = (_windowHeight - dest.h) / 2;


}

void ConquerEngine::Update(bool force) {
  SDL_Event event;

  // Events management
  while (SDL_PollEvent(&event)) {
    switch (event.type) {

    case SDL_QUIT:
      // handling of close button
      _quit = true;
      break;

    case SDL_KEYDOWN:
      // keyboard API for key pressed
      switch (event.key.keysym.scancode) {
      case SDL_SCANCODE_W:
      case SDL_SCANCODE_UP:
        dest.y -= speed / 30;
        break;
      case SDL_SCANCODE_A:
      case SDL_SCANCODE_LEFT:
        dest.x -= speed / 30;
        break;
      case SDL_SCANCODE_S:
      case SDL_SCANCODE_DOWN:
        dest.y += speed / 30;
        break;
      case SDL_SCANCODE_D:
      case SDL_SCANCODE_RIGHT:
        dest.x += speed / 30;
        break;
      default:
        break;
      }
    }
  }

  // right boundary
  if (dest.x + dest.w > _windowWidth)
    dest.x = _windowWidth - dest.w;

  // left boundary
  if (dest.x < 0)
    dest.x = 0;

  // bottom boundary
  if (dest.y + dest.h > _windowHeight)
    dest.y = _windowHeight - dest.h;

  // upper boundary
  if (dest.y < 0)
    dest.y = 0;

  // clears the screen
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, tex, NULL, &dest);

  // triggers the double buffers
  // for multiple rendering
  SDL_RenderPresent(renderer);

  // calculates to 60 fps
  SDL_Delay(1000 / 120);

  if (_quit) {
    // destroy texture
    SDL_DestroyTexture(tex);

    // destroy renderer
    SDL_DestroyRenderer(renderer);

    // destroy window
    SDL_DestroyWindow(window);

    // close SDL
    SDL_Quit();
  }
}
