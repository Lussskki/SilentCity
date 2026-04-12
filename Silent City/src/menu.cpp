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

void Menu::draw(sf::RenderWindow& window)
{
	window.clear();
	window.draw(backgroundSprite);
	for (const auto& text : options)
	{
		window.draw(text);
	}
	window.display();
}

void  Menu::moveUp()
{
	if (selectedIndex > 0)
	{
		options[selectedIndex].setFillColor(normalColor);
		selectedIndex--;
		options[selectedIndex].setFillColor(selectedColor);
	}
}

void Menu::moveDown()
{
	if (selectedIndex < (int)options.size() - 1)
	{
		options[selectedIndex].setFillColor(normalColor);
		selectedIndex++;
		options[selectedIndex].setFillColor(selectedColor);
	}
}

void Menu::refresh(sf::RenderWindow& window)
{
	sf::Vector2u winSize = window.getSize();
	float spacing = 60.f;

	for (size_t i = 0; i < options.size(); ++i)
	{
		float x = 50.f;
		float y = (float)winSize.y / 2 + (i * spacing);
		options[i].setPosition({ x, y });

		backgroundSprite.setScale({
			(float)winSize.x / backgroundTexture.getSize().x,
			(float)winSize.y / backgroundTexture.getSize().y
			});
	}
}