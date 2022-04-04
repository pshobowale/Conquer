
#include "lib/Config/Config.hpp"
#include "lib/Engine/Engine.hpp"
#include "lib/Map/Map.hpp"
#include <iostream>

int main() {
  ConquerConfig config = ConquerConfig();
  ConquerMap map = ConquerMap(config);
  // ConquerEngine engine = ConquerEngine(config,map);
  // engine.Update();
  return 0;
}