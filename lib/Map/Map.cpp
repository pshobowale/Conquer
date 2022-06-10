#include "Map.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>

#include <iostream>

ConquerMap::ConquerMap(ConquerConfig config) {
  config = config;
  bool Loaded = LoadAdjacencyGraph(config) && LoadLabelPositionGraph(config) &&
                LoadLabelMapAndMasks(config);
  if (!Loaded)
    throw std::runtime_error("Some Files could not be found or are corrupted\n\
                              Please check if the config is valid!");
  ConquerMap::_MapInitialized = true;
}

ConquerMap::ConquerMap(const ConquerMap &src) {
  if (src._MapInitialized == false)
    std::cerr << "You tried to copy an uninitialized Map";
  else {
    for (auto element : src._AdjacencyGraph)
      _AdjacencyGraph.push_back(element);

    for (auto element : src._Label2Pixel)
      _Label2Pixel.push_back(element);

    _BackgroundMask =
        SDL_ConvertSurface(src._BackgroundMask, src._BackgroundMask->format,
                           src._BackgroundMask->flags);

    _BordersMask = SDL_ConvertSurface(
        src._BordersMask, src._BordersMask->format, src._BordersMask->flags);

    _MapDims.x = src._BordersMask->w;
    _MapDims.y = src._BordersMask->h;

    _MapInitialized = !_AdjacencyGraph.empty() && !_Label2Pixel.empty() &&
                      _Pixel2Label && _BackgroundMask && _BordersMask;

    if (!_MapInitialized)
      std::cerr << "Failed to copy map";
  }
}

ConquerMap::~ConquerMap() {
  _AdjacencyGraph = std::vector<std::vector<int>>();
  _Label2Pixel = std::vector<std::array<unsigned int, 4>>();

  SDL_FreeSurface(_BackgroundMask);
  SDL_FreeSurface(_BordersMask);
  SDL_DestroyTexture(Scene);

  _MapInitialized = false;
}

SDL_Texture *ConquerMap::getMap(SDL_Renderer *renderer, SDL_Rect zoom) {
  if (!Scene)
    CreateSceneTextures(renderer);

  return Scene;
}

void ConquerMap::ColorizeByPosition(SDL_Renderer *renderer, SDL_FPoint rel_pos,
                                    SDL_Rect zoom_slice, SDL_Colour color) {
  unsigned short id = 0;

  int x = std::round(rel_pos.x * zoom_slice.w) + zoom_slice.x;
  int y = std::round(rel_pos.y * zoom_slice.h) + zoom_slice.y;

  ColorizeByMapPosition(renderer, SDL_Point{x, y}, zoom_slice, color);
}

void ConquerMap::ColorizeByMapPosition(SDL_Renderer *renderer,
                                       SDL_Point position, SDL_Rect zoom_slice,
                                       SDL_Color color) {
  if (position.x < _MapDims.x && position.y < _MapDims.y) {
    auto id = _Pixel2Label[position.y * _MapDims.x + position.x];
    ColorizeByID(renderer, id, color);
  }
}

void ConquerMap::ColorizeByID(SDL_Renderer *renderer, unsigned int id,
                              SDL_Colour color) {

  unsigned int y = _Label2Pixel[id][0], x = _Label2Pixel[id][1],
               h = _Label2Pixel[id][2], w = _Label2Pixel[id][3];

  auto country = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32,SDL_PIXELFORMAT_RGBA32);
  Uint32 country_color = SDL_MapRGBA(country->format, color.r, color.g, color.b,0xff);
  SDL_FillRect(country, 0, country_color);
  Uint32 *pixels = (Uint32 *)country->pixels;

  for (int i = x; i < x + w; ++i)
    for (int j = y; j < y + h; ++j)
      if (_Pixel2Label[j * _MapDims.x + i] != id)
        pixels[(j - y) * w + (i - x)] = 0;
      
      

  auto dst = SDL_Rect{(int)x, (int)y, (int)w, (int)h};
  auto c = SDL_CreateTextureFromSurface(renderer, country);
  auto b = SDL_CreateTextureFromSurface(renderer, _BordersMask);

  SDL_SetRenderTarget(renderer, Scene);
  SDL_SetTextureBlendMode(c, SDL_BLENDMODE_BLEND);
  SDL_RenderCopy(renderer, c, NULL, &dst);
  SDL_RenderCopy(renderer, b, &dst, &dst);
  SDL_SetRenderTarget(renderer, NULL);
}

void ConquerMap::CreateSceneTextures(SDL_Renderer *renderer) {
  auto Background = SDL_CreateTextureFromSurface(renderer, _BackgroundMask);
  auto Borders = SDL_CreateTextureFromSurface(renderer, _BordersMask);
  Scene = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32,
                            SDL_TEXTUREACCESS_TARGET, _MapDims.x, _MapDims.y);

  SDL_SetRenderTarget(renderer, Scene);
  SDL_SetTextureColorMod(Background, 50, 50, 50);

  SDL_SetRenderDrawColor(renderer, 0x0F, 0x0F, 0xFF, 0xFF);
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, Background, NULL, NULL);
  SDL_RenderCopy(renderer, Borders, NULL, NULL);

  SDL_SetRenderTarget(renderer, NULL);
}
