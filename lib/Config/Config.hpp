
#include <SFML/System/String.hpp>
#ifndef CONQUER_CONFIG_H
    #define CONQUER_CONFIG_H

#include <string>

class ConquerConfig{
    private:
        bool CheckConfigPath(std::string fpath);
        void LoadConfig(std::string fpath);

        uint _WindowHeight,_WindowWidth;
        std::string _WindowTitle;

        std::string _MapPath,
                    _BackgroundMaskPath,
                    _BordersMaskPath,
                    _AdjacencyGraphPath,
                    _Label2PixelPath;

    public:
        ConquerConfig(std::string fpath = "");

        //Getter Functions
        //MainWindow Props
        std::string getWindowTitle(){return _WindowTitle;};
        uint getWindowHeight(){return _WindowHeight;};
        uint getWindowWidth(){return _WindowWidth;};

        //Assets
        std::string getMapPath(){return _MapPath;};
        std::string getBackgroundMaskPath(){return _BackgroundMaskPath;};
        std::string getBorderMaskPath(){return _BordersMaskPath;};
        std::string getAdjacencyGraphPath(){return _AdjacencyGraphPath;};
        std::string getLabel2PixelPath(){return _Label2PixelPath;};

        


};

#endif