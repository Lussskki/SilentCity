#include "menu.h"
#include "options.h"

Menu::Menu(sf::RenderWindow& window)
	: backgroundSprite(backgroundTexture)
{
	if (!font.openFromFile("arial.ttf"))
	{

	}
}

int Menu::run(sf::RenderWindow& window)
{
	refresh(window);
	while (window.isOpen())
	{
		
	}
}