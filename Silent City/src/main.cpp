#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Main window
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "SFML Window");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        // Event processing
        while (const std::optional event = window.pollEvent()) 
        {
            
            if (event->is<sf::Event::Closed>()) 
            {
                window.close();
            }
        }

        // Rendering
        window.clear(sf::Color::Black); // Clear old frame

       

        window.display(); 
    }

    return 0;
}
