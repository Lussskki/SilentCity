#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <optional> 

class Options 
{
public:
	Options(sf::RenderWindow& window);
	int run(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	void moveUp();
	void moveDown();

	
	static bool isFullscreen;

private:
	std::vector<sf::Text> options;
	int selectedIndex = 0;
	sf::Font font;

	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	sf::Color selectedColor = sf::Color(120, 120, 120);
	sf::Color normalColor = sf::Color(185, 100, 210);

	void refresh(sf::RenderWindow& window);
};