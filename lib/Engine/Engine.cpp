

#include "Engine.hpp"
#include "../Config/Config.hpp"
#include "../Map/Map.hpp"




ConquerEngine::ConquerEngine(ConquerConfig config,ConquerMap map){
    window = new sf::RenderWindow(sf::VideoMode(config.getWindowWidth(), 
                                                config.getWindowHeight()), 
                                                config.getWindowTitle());
    //ConquerEngine
};

void ConquerEngine::Update(){
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear();
        window->draw(shape);
        window->display();
    }
}
