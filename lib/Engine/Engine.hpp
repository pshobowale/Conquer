#pragma once

#include "../Config/Config.hpp"
#include "../Map/Map.hpp"
#include "../Controls/Controls.hpp"
#include <string>

class ConquerEngine {
private:
  ConquerMap map;
  ConquerControls controls;
  unsigned int _windowHeight = 0;
  unsigned int _windowWidth = 0;
  std::string _windowName = "noName";
  unsigned int _gameSpeed=0;

  SDL_Window *window;
  SDL_Renderer *renderer;


  bool _quit = false;

  void init(void);

public:
  ConquerEngine(ConquerConfig config);
  ~ConquerEngine(void);

  bool stopped(void) { return _quit; };
  void Update(bool force = false);
};
