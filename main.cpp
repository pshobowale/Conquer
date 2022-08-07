
#include "lib/Config/Config.hpp"
#include "lib/Engine/Engine.hpp"
#include "lib/Map/Map.hpp"
#include <iostream>
#include <ostream>

int main() {
  ConquerConfig config = ConquerConfig();
  ConquerEngine engine(config);

  Uint32 lastupdate = SDL_GetTicks();
  Uint32 dt = SDL_GetTicks() - lastupdate;
  int fps = 60;

  while (!engine.stopped()) {
    dt = SDL_GetTicks() - lastupdate;

    if (dt >= (1000.0 / fps)) {
      engine.Update();
      lastupdate += dt;
      //std::cout<<dt<<std::endl;
    }
  }

  return 0;
}
