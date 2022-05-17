#include "Map.hpp"

#include <SDL2/SDL.h>
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

    

    _BackgroundMask = SDL_ConvertSurface(src._BackgroundMask, src._BackgroundMask->format,
                                         src._BackgroundMask->flags);

    _BordersMask = SDL_ConvertSurface(src._BordersMask, src._BordersMask->format,
                                      src._BordersMask->flags);

    

    _MapDims.x=src._BordersMask->w;
    _MapDims.y=src._BordersMask->h;

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



SDL_Texture* ConquerMap::getMap(SDL_Renderer* renderer, SDL_Rect zoom){
  if(!Scene)
    CreateSceneTextures(renderer);

  return Scene;
}


void ConquerMap::ColorizeByID(unsigned int id, SDL_Colour color){
  return; //ToDo Load Images
}

void ConquerMap::ColorizeByPosition(SDL_Point position,SDL_Rect zoom_slice,SDL_Colour color){
  long long int id=0;

  int x= position.x+zoom_slice.w;
  int y= position.y+zoom_slice.h;

  if(x<_MapDims.x && y<_MapDims.y){
    id = _Pixel2Label[y*_MapDims.x+x];
    ColorizeByID(id,color);
  }
}

void ConquerMap::CreateSceneTextures(SDL_Renderer* renderer){
    auto Background=SDL_CreateTextureFromSurface(renderer, _BackgroundMask );
    auto Borders= SDL_CreateTextureFromSurface(renderer, _BordersMask);
    Scene = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, _MapDims.x, _MapDims.y);

    SDL_SetRenderTarget(renderer, Scene);
    SDL_SetTextureColorMod(Background, 50, 50, 50);

    SDL_SetRenderDrawColor(renderer, 0x0F, 0x0F, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, Background, NULL, NULL);
    SDL_RenderCopy(renderer, Borders, NULL, NULL);

    SDL_SetRenderTarget(renderer, NULL);

}

