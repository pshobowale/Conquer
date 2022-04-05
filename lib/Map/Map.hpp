#ifndef CONQUER_MAP_H
#define CONQUER_MAP_H

#include "../Config/Config.hpp"
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

  bool LoadAdjacencyGraph(ConquerConfig config);
  bool LoadLabelPositionGraph(ConquerConfig config);
  bool LoadLabelMapAndMasks(ConquerConfig config);

public:
  ConquerMap(void) = default;
  ConquerMap(ConquerConfig config);
  ConquerMap(const ConquerMap &, bool delete_src=false);
  ~ConquerMap();

  ConquerMap operator=(const ConquerMap &src){return ConquerMap(src,false);};

  bool isInitialized(void) { return _MapInitialized; }

  SDL_Surface* getMap(){ return _BackgroundMask;};
};

#endif