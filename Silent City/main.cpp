#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/menu.h"
#include "include/options.h"

int main() 
{
    sf::RenderWindow window(sf::VideoMode({ 1200, 900 }), "Silent City");
    window.setFramerateLimit(60);

    // Creating objects
    Menu menu(window);
    Options options(window);

    bool inMenu = true;

    while (window.isOpen()) {
        if (inMenu) {
           
            int choice = menu.run(window);

            if (choice == 0) {
                // Play 
                inMenu = false;
            }
            else if (choice == 1) {
                // Options
                options.run(window);
            }
            else if (choice == 2) {
                // Exit
                window.close();
            }
        }
        else {
            //  (Rendering, Physics)
            while (const std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) window.close();
            }

            window.clear(sf::Color::Black);
            // window.draw(Objects);
            window.display();
        }
    }

    return 0;
}