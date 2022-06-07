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




void ConquerMap::ColorizeByPosition(SDL_FPoint rel_pos,SDL_Rect zoom_slice,SDL_Colour color){
  unsigned short id=0;

  int x= std::round(rel_pos.x*zoom_slice.w)+zoom_slice.x;
  int y= std::round(rel_pos.y*zoom_slice.h)+zoom_slice.y;

  ColorizeByMapPosition(SDL_Point {x,y}, zoom_slice, color);
  std::cout<<x<<" "<<y<<std::endl;
  
}

void ConquerMap::ColorizeByMapPosition(SDL_Point position, SDL_Rect zoom_slice, SDL_Color color){
  if(position.x<_MapDims.x && position.y<_MapDims.y){
    auto id = _Pixel2Label[position.y*_MapDims.x+position.x];
    ColorizeByID(id,color);
  }
}

void ConquerMap::ColorizeByID(unsigned int id, SDL_Colour color){
  
  std::cout<<"id:"<<id<<std::endl;
  std::cout<<_Label2Pixel[id][0]<<" "<<_Label2Pixel[id][1]<<" "<<_Label2Pixel[id][2]<<" "<<_Label2Pixel[id][3]<<std::endl;
  return; //ToDo Load Images by Label2Pixel
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

