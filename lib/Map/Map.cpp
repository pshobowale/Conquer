#include "Map.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
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

    _Pixel2Label = SDL_ConvertSurface(
        src._Pixel2Label, src._Pixel2Label->format, src._Pixel2Label->flags);

    _BackgroundMask =
        SDL_ConvertSurface(src._BackgroundMask, src._BackgroundMask->format,
                           src._BackgroundMask->flags);

    _BordersMask = SDL_ConvertSurface(
        src._BordersMask, src._BordersMask->format, src._BordersMask->flags);

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

  SDL_FreeSurface(_Pixel2Label);
  SDL_FreeSurface(_BackgroundMask);
  SDL_FreeSurface(_BordersMask);

  _MapInitialized = false;
}

