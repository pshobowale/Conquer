#pragma once

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include "../Config/Config.hpp"

typedef struct{
    SDL_Point ClickPosition ={-1,-1};
    SDL_Rect MapSlice={-1,-1,-1,-1};
}GameControls;


class ConquerControls{
    private:
        int dx=0,dy=0,dz=0;
        unsigned int wh=0,ww=0,speed=0;
        unsigned int mw=0,mh=0;
        float window_ratio=1.0;
        float scale=0.0;
        GameControls Controls;
        bool mouse_moved=false;
        bool quit=false;

        void handleKeyboard(SDL_Event);
        void handleMouse(SDL_Event);
        void handleTouch(SDL_Event);
    public:
        ConquerControls(ConquerConfig config):
        ww(config.getWindowWidth()),
        wh(config.getWindowHeight()),
        speed(config.getGameSpeed()),
        dx(0),dy(0),dz(0){
            Controls.MapSlice.x=0;
            Controls.MapSlice.y=0;
            Controls.MapSlice.w=config.getWindowWidth();
            Controls.MapSlice.h=config.getWindowHeight();
            window_ratio=(float)config.getWindowHeight()/(float)config.getWindowWidth();
            Controls.ClickPosition.x=0;
            Controls.ClickPosition.y=0;
        }      

        GameControls getUpdate(void);
        void setMapDims(SDL_Point);
        void setRelativeScaleAndPosition(float rel_scale,float rel_x,float rel_y);
        bool Quit(void){return quit;};
};