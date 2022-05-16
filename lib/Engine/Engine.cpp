

#include "Engine.hpp"
#include "../Config/Config.hpp"
#include "../Map/Map.hpp"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <ostream>

ConquerEngine::ConquerEngine(ConquerConfig config)
    : map(ConquerMap(config)), controls(ConquerControls(config)),
      _windowHeight(config.getWindowHeight()),
      _windowWidth(config.getWindowWidth()),
      _windowName(config.getWindowTitle()) {

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cerr << "error initializing SDL: " << SDL_GetError() << std::endl;
    _quit = true;
    return;
  }

  window =
      SDL_CreateWindow(_windowName.c_str(), SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, _windowWidth, _windowHeight, 0);

  Uint32 render_flags = SDL_RENDERER_ACCELERATED;
  renderer = SDL_CreateRenderer(window, -1, render_flags);

  controls.setMapDims(map.getMapDims());
  controls.setRelativeScaleAndPosition(1.0, 0.5, 0.5);
}

void ConquerEngine::Update(bool force) {

  SDL_Rect zoom_slice = controls.getCameraUpdate();

  SDL_Point zero;
  SDL_Color color;

  // map.ColorizeByPosition(zero,zoom_slice, color);
  auto tex = map.getMap(renderer, zoom_slice);

  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, tex, &zoom_slice, NULL);
  SDL_RenderPresent(renderer);

  if (controls.Quit()) {
    _quit = true;
  }
}

ConquerEngine::~ConquerEngine() {

  // destroy renderer
  SDL_DestroyRenderer(renderer);

  // destroy window
  SDL_DestroyWindow(window);

  // close SDL
  SDL_Quit();
};
