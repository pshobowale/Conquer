
#ifndef CONQUER_ENGINE_H
#define CONQUER_ENGINE_H

#include "../Config/Config.hpp"
#include "../Map/Map.hpp"
#include <SFML/Graphics.hpp>

class ConquerEngine {
private:
  sf::RenderWindow *window;
  sf::CircleShape shape;

public:
  ConquerEngine(ConquerConfig config, ConquerMap map);
  void Update();
};

#endif