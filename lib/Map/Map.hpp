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
  bool _MapUpdated = false;
  std::vector<std::vector<int>> _AdjacencyGraph;
  std::vector<std::array<unsigned int, 4>> _Label2Pixel;

  unsigned short *_Pixel2Label = NULL;
  SDL_Surface *_BackgroundMask = NULL;
  SDL_Surface *_BordersMask = NULL;

  SDL_Texture *Scene = NULL;

  SDL_Point _MapDims;

  bool LoadAdjacencyGraph(ConquerConfig config);
  bool LoadLabelPositionGraph(ConquerConfig config);
  bool LoadLabelMapAndMasks(ConquerConfig config);
  void CreateSceneTextures(SDL_Renderer *renderer);

public:
  ConquerMap(void) = default;
  ConquerMap(ConquerConfig config);
  ConquerMap(const ConquerMap &);
  ~ConquerMap();

  ConquerMap operator=(const ConquerMap &src) { return ConquerMap(src); };

  bool isInitialized(void) { return _MapInitialized; };
  SDL_Point getMapDims() { return _MapDims; };
  SDL_Texture *getMap(SDL_Renderer *renderer, SDL_Rect zoom);
  void ColorizeByPosition(SDL_FPoint rel_win_pos, SDL_Rect zoom_slice,SDL_Colour color);
  void ColorizeByMapPosition(SDL_Point position,SDL_Rect zoom_slice, SDL_Color);
  void ColorizeByID(unsigned int id, SDL_Color color);
};