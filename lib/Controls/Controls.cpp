#include "Controls.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_stdinc.h>
#include <iostream>
#include <math.h>
#include <ostream>



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
    
    scale+=float(dz)/1000.0;
    if(scale > 1.0)
      scale=1.0;
    if(scale<0)
      scale=0;
    
    if(window_ratio<1){
      if(std::round(ww + (mw-ww)*scale/window_ratio)<=mh){
        MapSlice.w = std::round(ww + (mw-ww)*scale);
        MapSlice.h = std::round(MapSlice.w/window_ratio);
      }else 
        scale-=float(dz)/1000.0;
    }
    else 
      if(std::round(wh+ (mh-wh)*scale/window_ratio)<=mw){
        MapSlice.h = std::round(wh+ (mh-wh)*scale);
        MapSlice.w =std::round(MapSlice.h/window_ratio);
      }else 
        scale-=float(dz)/1000.0;
      
    float zoom_speed=std::max((float)MapSlice.h/wh,(float)MapSlice.w/ww);
    MapSlice.x+=dx*zoom_speed;
    MapSlice.y+=dy*zoom_speed;

    //Check if Camera is inside of Map
    if((MapSlice.x+MapSlice.w)>mw)
      MapSlice.x=mw-MapSlice.w;
    
    if(MapSlice.x<0)
      MapSlice.x=0;
    
    if((MapSlice.y+MapSlice.h)>mh)
      MapSlice.y=mh-MapSlice.h;

    if(MapSlice.y<0)
      MapSlice.y=0;


    //std::cout<<"dx: "<<dx<<" dy: "<<dy<<" dz:"<<dz<<" Scale:"<<scale<<"\n";
    //std::cout<<MapSlice.x<<","<<MapSlice.y<<","<<MapSlice.w<<","<<MapSlice.h<<std::endl;
    return MapSlice;

};

void ConquerControls::setMapDims(SDL_Point dims){
    mw=dims.x;
    mh=dims.y;
}

void ConquerControls::setRelativeScaleAndPosition(float rel_scale,float rel_x,float rel_y){
  this->scale=rel_scale;

  if (window_ratio>1){
    rel_y=SDL_min(1.0-rel_scale,rel_y);
    rel_x=SDL_min(0.75*rel_scale,rel_x);
  }else{
    rel_x=SDL_min(1.0 -rel_scale,rel_x);
    rel_y=SDL_min(0.75*rel_scale,rel_y);
  }

  MapSlice.x=std::round(mw*rel_x);
  MapSlice.y=std::round(mh*rel_y);
}

void ConquerControls::handleKeyboard(SDL_Event event){

    auto state=SDL_GetKeyboardState(NULL);
    
    if(state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN])
      dy+=speed/30;
      
    if(state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP])
      dy-=speed/30;

    if(state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT])
      dx+=speed/30;

    if(state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT])
      dx-=speed/30;

    if(state[SDL_SCANCODE_E] || state[SDL_SCANCODE_KP_MINUS]||state[SDL_SCANCODE_MINUS])
      dz+=speed/30;

    if(state[SDL_SCANCODE_Q] || state[SDL_SCANCODE_KP_PLUS])
      dz-=speed/30;

    

 };

  