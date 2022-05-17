#include "../Config/Config.hpp"
#include "Map.hpp"

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_surface.h>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#define STB_IMAGE_IMPLEMENTATION
#include <SDL2/SDL_image.h>
#include "png.h"
using namespace std;

bool ConquerMap::LoadAdjacencyGraph(ConquerConfig config) {
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

    // First Field in CSV is a duplicate
    adj.erase(adj.begin());
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

bool ConquerMap::LoadLabelPositionGraph(ConquerConfig config) {
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
      if (integer.length() > 0 and iter > 0 and iter < 5)
        pos[iter - 1] = atoi(integer.c_str());
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
  }*/

  return true;
}

bool ConquerMap::LoadLabelMapAndMasks(ConquerConfig config) {
      ConquerMap::_BackgroundMask = IMG_Load(config.getBackgroundMaskPath().c_str());
      ConquerMap::_BordersMask = IMG_Load(config.getBorderMaskPath().c_str());
      ConquerMap::_Pixel2Label=stbi_load_16(config.getMapPath().c_str(), &_MapDims.x, &_MapDims.y, NULL,1);
      
      
  //IMG_Load returns NULL if no image is found -->Loaded = NULL/POINTER!0 && N/P && N/P
  return (_Pixel2Label && _BackgroundMask && _BordersMask);
}
