#include "../Config/Config.hpp"
#include "Map.hpp"

#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

ConquerMap::ConquerMap(ConquerConfig config) {
  config = config;
  bool Loaded = LoadAdjacencyGraph() && 
                LoadLabelPositionGraph() &&
                LoadLabelMapAndMasks();
  if (!Loaded)
    throw std::runtime_error("Some Files could not be found or are corrupted\n\
                              Please check if the config is valid!");
}

bool ConquerMap::LoadAdjacencyGraph() {
  ifstream adj_csv_file(config.getAdjacencyGraphPath());

  // First Line describes all Fields
  string description = "adjacency file not found or corrupted\n";

  if (!getline(adj_csv_file, description)) {
    cerr << description;
    return false;
  }

  for (string line; getline(adj_csv_file, line);) {
    istringstream l(line);

    vector<int> adj;

    for (string integer; getline(l, integer, ',');)
      if (integer.length() > 0)
        adj.push_back(atoi(integer.c_str()));

    ConquerMap::_AdjacencyGraph.push_back(adj);
  }

  /*
   cout << "Size of Vector: " << ConquerMap::_AdjacencyGraph.size() << "\n";

   for (auto l : _AdjacencyGraph) {
     for (auto i : l)
       cout << i << ", ";
     cout << "\b\b \b\b\n";
   } */

  return true;
}

bool ConquerMap::LoadLabelPositionGraph() {
  ifstream l2p_csv_file(config.getLabel2PixelPath());

  // First Line describes all Fields
  string description = "Label2PixelGraph file not found or corrupted\n";

  if (!getline(l2p_csv_file, description)) {
    cerr << description;
    return false;
  }

  for (string line; getline(l2p_csv_file, line);) {
    istringstream l(line);

    array<unsigned int, 4> pos;
    int iter = 0;

    for (string integer; getline(l, integer, ','); iter++) {
      if (integer.length() > 0 and iter < 4)
        pos[iter] = atoi(integer.c_str());
    }

    ConquerMap::_Label2Pixel.push_back(pos);
  }

  /*
  cout << "Size of Vector: " << ConquerMap::_Label2Pixel.size() << "\n";

  for (auto integer : _Label2Pixel) {
    cout << "[";
    for (int i = 0; i < 4; i++)
      cout << integer[i] << ", ";
    cout << "\b\b]\b\b\n";
  }
  */

  return true;
}

bool ConquerMap::LoadLabelMapAndMasks() {
  bool Loaded =
      ConquerMap::_Pixel2Label.loadFromFile(config.getMapPath()) &&
      ConquerMap::_BackgroundMask.loadFromFile(config.getBackgroundMaskPath()) &&
      ConquerMap::_BackgroundMask.loadFromFile(config.getBorderMaskPath());

  return Loaded;
}