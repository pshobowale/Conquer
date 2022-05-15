#include "Controls.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_scancode.h>
#include <math.h>



SDL_Rect ConquerControls::getCameraUpdate(){
    SDL_Event event;
    SDL_Rect slice;
    dx=0,dy=0,dz=0;

    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                _quit = true;
                break;
            case SDL_KEYDOWN:
                handleKeyboard(event);
                break;
            case SDL_MOUSEMOTION:
                break;
            case SDL_FINGERMOTION:
                break;
            default:
                break;

        }
    }

    //Check if Zoom does not distort and is inside
    if(window_ratio>1)
      if((dz+MapSlice.w+MapSlice.y)>0 &&
         (dz+MapSlice.w+MapSlice.y)<=mw &&
         (std::round(dz*window_ratio)+MapSlice.h+MapSlice.x)>0 &&
         (std::round(dz*window_ratio)+MapSlice.h+MapSlice.x)<=mh){
           MapSlice.w+=dz;
           MapSlice.h+=std::round(dz*window_ratio);
         }


    //Check if Camera is inside of Map
    if((dx+MapSlice.w+MapSlice.x)<=mw &&
        (dx+MapSlice.w+MapSlice.x)>0)
        MapSlice.x+=dx;
    if((dx+MapSlice.w+MapSlice.y)<=mh &&
        (dx+MapSlice.w+MapSlice.y)<=mh)
        MapSlice.y+=dy;

    return MapSlice;

};

void ConquerControls::setMapDims(SDL_Point dims){
    mw=dims.y;
    mh=dims.x;
}

void ConquerControls::handleKeyboard(SDL_Event event){

    switch (event.key.keysym.scancode) {
      case SDL_SCANCODE_W:
      case SDL_SCANCODE_UP:
        dy-= speed / 30;
        break;
      case SDL_SCANCODE_A:
      case SDL_SCANCODE_LEFT:
        dx-= speed / 30;
        break;
      case SDL_SCANCODE_S:
      case SDL_SCANCODE_DOWN:
        dy += speed / 30;
        break;
      case SDL_SCANCODE_D:
      case SDL_SCANCODE_RIGHT:
        dx += speed / 30;
        break;
      case SDL_SCANCODE_KP_PLUS:
        dz+= speed / 30;
        break;
      case SDL_SCANCODE_KP_MINUS:
        dz-= speed / 30;
        break;
      default:
        break;
      }
 };

  