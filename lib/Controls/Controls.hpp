#pragma once

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include "../Config/Config.hpp"


class ConquerControls{
    private:
        int dx=0,dy=0,dz=0;
        unsigned int wh=0,ww=0,speed=0;
        unsigned int mw=0,mh=0;
        float window_ratio=1;
        SDL_Rect MapSlice;
        bool _quit=false;

        void handleKeyboard(SDL_Event);
        void handleMouse(SDL_Event);
        void handleTouch(SDL_Event);
    public:
        ConquerControls(ConquerConfig config):
        ww(config.getWindowWidth()),
        wh(config.getWindowHeight()),
        speed(config.getGameSpeed()),
        dx(0),dy(0),dz(0){
            MapSlice.x=0;
            MapSlice.y=0;
            MapSlice.w=config.getWindowWidth();
            MapSlice.h=config.getWindowHeight();
            window_ratio=(float)config.getWindowHeight()/(float)config.getWindowWidth();
        }      

        SDL_Rect getCameraUpdate(void);
        void setMapDims(SDL_Point);
        bool Quit(void){return _quit;};
};