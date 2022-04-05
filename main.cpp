
#include "lib/Config/Config.hpp"
#include "lib/Engine/Engine.hpp"
#include "lib/Map/Map.hpp"
#include <iostream>

int main() {
  ConquerConfig config = ConquerConfig();
  ConquerEngine engine(config);
  
  while(!engine.stopped())
    engine.Update();
    
  return 0;
}