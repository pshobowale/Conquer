#include "Controls.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_stdinc.h>
#include <iostream>
#include <math.h>
#include <ostream>



GameControls ConquerControls::getUpdate(){
    SDL_Event event;
    dx=0,dy=0,dz=0;
    Controls.ClickPosition={-1,-1};

    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                handleKeyboard(event);
                break;
            
            case SDL_MOUSEBUTTONDOWN:
                SDL_SetRelativeMouseMode(SDL_TRUE);
                mouse_moved=false;
                break;

            case SDL_MOUSEMOTION:
                  handleMouse(event);
                  break;
                  
            case SDL_MOUSEBUTTONUP:
                handleMouse(event);
                SDL_SetRelativeMouseMode(SDL_FALSE);
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
        Controls.MapSlice.w = std::round(ww + (mw-ww)*scale);
        Controls.MapSlice.h = std::round(Controls.MapSlice.w/window_ratio);
      }else 
        scale-=float(dz)/1000.0;
    }
    else 
      if(std::round(wh+ (mh-wh)*scale/window_ratio)<=mw){
        Controls.MapSlice.h = std::round(wh+ (mh-wh)*scale);
        Controls.MapSlice.w =std::round(Controls.MapSlice.h/window_ratio);
      }else 
        scale-=float(dz)/1000.0;
      
    float zoom_speed=std::max((float)Controls.MapSlice.h/wh,(float)Controls.MapSlice.w/ww);
    Controls.MapSlice.x+=dx*zoom_speed;
    Controls.MapSlice.y+=dy*zoom_speed;

    //Check if Camera is inside of Map
    if((Controls.MapSlice.x+Controls.MapSlice.w)>mw)
      Controls.MapSlice.x=mw-Controls.MapSlice.w;
    
    if(Controls.MapSlice.x<0)
      Controls.MapSlice.x=0;
    
    if((Controls.MapSlice.y+Controls.MapSlice.h)>mh)
      Controls.MapSlice.y=mh-Controls.MapSlice.h;

    if(Controls.MapSlice.y<0)
      Controls.MapSlice.y=0;


    //std::cout<<"dx: "<<dx<<" dy: "<<dy<<" dz:"<<dz<<" Scale:"<<scale<<"\n";
    //std::cout<<Controls.MapSlice.x<<","<<Controls.MapSlice.y<<","<<Controls.MapSlice.w<<","<<Controls.MapSlice.h<<std::endl;
    return Controls;

};



void ConquerControls::setMapDims(SDL_Point dims){
    mw=dims.x;
    mh=dims.y;
}

void ConquerControls::setRelativeScaleAndPosition(float rel_scale,float rel_x,float rel_y){
  this->scale=rel_scale;

  //Prevent Distortions by Limiting to max rel_pos plausible/possible
  if (window_ratio>1){
    rel_y=SDL_min(1.0-rel_scale,rel_y);
    rel_x=SDL_min(0.75*rel_scale,rel_x);
  }else{
    rel_x=SDL_min(1.0 -rel_scale,rel_x);
    rel_y=SDL_min(0.75*rel_scale,rel_y);
  }

 Controls.MapSlice.x=std::round(mw*rel_x);
 Controls.MapSlice.y=std::round(mh*rel_y);
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


void ConquerControls::handleMouse(SDL_Event event){
  int xrel=0,yrel=0;
  SDL_GetRelativeMouseState(&xrel, &yrel);

  if(event.type==SDL_MOUSEBUTTONUP && !mouse_moved){
    Controls.ClickPosition={event.motion.x,event.motion.y};
    return;
  }
    
  mouse_moved=true;
  switch(event.motion.state){
    //std::cout<<"Moved! xrel:"<<xrel<<" yrel:"<<yrel<<std::endl;
    case SDL_BUTTON_LMASK:
      dx+=xrel/2;
      dy-=yrel/2;
      break;

    case SDL_BUTTON_RMASK:
      dz+=yrel/2;
      break;
  }

}