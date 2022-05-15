#pragma once

#include "../Config/Config.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <cstddef>
#include <vector>

#include <SDL2/SDL_image.h>

class ConquerMap {

private:
  bool _MapInitialized = false;
  std::vector<std::vector<int>> _AdjacencyGraph;
  std::vector<std::array<unsigned int, 4>> _Label2Pixel;

  SDL_Surface *_Pixel2Label = NULL;
  SDL_Surface *_BackgroundMask = NULL;
  SDL_Surface *_BordersMask = NULL;
  SDL_Point _MapDims;

  bool LoadAdjacencyGraph(ConquerConfig config);
  bool LoadLabelPositionGraph(ConquerConfig config);
  bool LoadLabelMapAndMasks(ConquerConfig config);

public:
  ConquerMap(void) = default;
  ConquerMap(ConquerConfig config);
  ConquerMap(const ConquerMap &);
  ~ConquerMap();

  ConquerMap operator=(const ConquerMap &src) {
    return ConquerMap(src);
  };

  bool isInitialized(void) { return _MapInitialized; };

  SDL_Surface *getFullMap() { return _BackgroundMask; };
  SDL_Point getMapDims(){return _MapDims;};
};