#ifndef CONQUER_MAP_H
#define CONQUER_MAP_H

#include "../Config/Config.hpp"
#include <vector>

#include <SFML/Graphics/Image.hpp>

class ConquerMap {
private:
  std::string svg_path;
  ConquerConfig config;

  std::vector<std::vector<int>> _AdjacencyGraph;
  std::vector<std::array<unsigned int, 4>> _Label2Pixel;

  sf::Image _Pixel2Label;
  sf::Image _BackgroundMask;
  sf::Image _BordersMask;

  bool LoadAdjacencyGraph();
  bool LoadLabelPositionGraph();
  bool LoadLabelMapAndMasks();

public:
  ConquerMap(ConquerConfig config);
};

#endif