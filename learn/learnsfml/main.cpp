#include<cstdlib>
#include <SFML/Window.hpp>

using namespace sf;


int main()
{
  sf::Window window(sf::VideoMode(800, 600), "Let's start!");
    while (window.isOpen())
    {
        // on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
        sf::Event event;
        while (window.pollEvent(event))
        {
            // évènement "fermeture demandée" : on ferme la fenêtre
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
	return 0;
}
	
	
	
	
//compilation:
//g++ -c main.cpp 
//g++ main.o -o smflapp -lsfml-graphics -lsfml-window -lsfml-system
