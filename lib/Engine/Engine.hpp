#pragma once

#include "../Config/Config.hpp"
#include "../Map/Map.hpp"
#include <SFML/Graphics.hpp>
#include <string>

class ConquerEngine {
private:
  ConquerMap map;
  unsigned int _windowHeight = 0;
  unsigned int _windowWidth = 0;
  std::string _windowName = "noName";

  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *tex;
  SDL_Rect dest;

  unsigned int speed;

  bool _quit = false;

  void init(void);

public:
  ConquerEngine(ConquerConfig config);
  ~ConquerEngine();

  bool stopped(void) { return _quit; };
  void Update(bool force = false);
};
