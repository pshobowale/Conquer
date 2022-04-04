#include "Config.hpp"
#include "DefaultConfig.h"
#include "iostream"
#include <string>


ConquerConfig::ConquerConfig(std::string fpath) {
  if (CheckConfigPath(fpath)) {
    std::cerr<< "Loading is not supported in the Moment\n Using default values";
    ConquerConfig::LoadConfig(fpath);
  } else {
    ConquerConfig::_WindowTitle = WINDOW_TITLE;
    ConquerConfig::_WindowHeight = WINDOW_HEIGHT;
    ConquerConfig::_WindowWidth = WINDOW_WIDTH;

    ConquerConfig::_MapPath = PIXEL_2_LABEL_PNG_PATH;
    ConquerConfig::_BackgroundMaskPath = BACKGROUND_MASK_PNG_PATH ;
    ConquerConfig::_BordersMaskPath = BORDERS_MASK_PNG_PATH ;
    ConquerConfig::_AdjacencyGraphPath = ADJACENCY_CSV_PATH;
    ConquerConfig::_Label2PixelPath = LABEL_2_PIXEL_CSV_PATH;
  }
}

void ConquerConfig::LoadConfig(std::string fpath) {
  std::cerr << "Loading Configs is not implemented";
}

bool ConquerConfig::CheckConfigPath(std::string fpath) {
  // Loading Configs is not implemented"
  return false;
}