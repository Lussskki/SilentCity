#include "options.h"
#include <iostream>

// Static member initialization
bool Options::isFullscreen = false;

// Constructor: Loads assets and prepares the settings UI
Options::Options(sf::RenderWindow& window)
	: backgroundSprite(backgroundTexture)
{
	if (!font.openFromFile("fonts/arial.ttf"))
	{
		std::cout << "Error: fonts/arial.ttf not found!" << std::endl;
	}

	// Menu options
	std::vector<std::string> names = { "Fullscreen", "Back" };

	if (!backgroundTexture.loadFromFile("photos/menu-options-jimi-hendrix.png"))
	{
		std::cout << "Error: photos/menu-options-jimi-hendrix.png not found!" << std::endl;
	}
	backgroundSprite.setTexture(backgroundTexture);

	for (const auto& name : names)
	{
		sf::Text text(font, name, 36);
		text.setFillColor(normalColor);
		options.push_back(text);
	}

	if (!options.empty())
	{
		options[selectedIndex].setFillColor(selectedColor);
	}

	refresh(window);
}

// Logic loop for the options menu
int Options::run(sf::RenderWindow& window)
{
	refresh(window);

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
				return 1;
			}

			if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				if (keyPressed->code == sf::Keyboard::Key::Up)
				{
					moveUp();
				}
				else if (keyPressed->code == sf::Keyboard::Key::Down)
				{
					moveDown();
				}
				else if (keyPressed->code == sf::Keyboard::Key::Enter)
				{
					if (selectedIndex == 0) // Toggle Fullscreen logic
					{
						isFullscreen = !isFullscreen;

						if (isFullscreen) {
							sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
							window.create(desktop, "Silent City", sf::Style::None);
						}
						else {
							
							window.create(sf::VideoMode({ 1200, 1000 }), "Silent City", sf::Style::Default);
						}

						
						window.setFramerateLimit(60);
						refresh(window);

						
						break;
					}
					else if (selectedIndex == 1) // Back button
					{
						return 1;
					}
				}
			}
		}

		draw(window);
	}

	return 1;
}

// Renders the options UI
void Options::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::Black);
	window.draw(backgroundSprite);
	for (const auto& text : options)
	{
		window.draw(text);
	}
	window.display();
}

// Changes selection to previous item
void Options::moveUp()
{
	if (selectedIndex > 0)
	{
		options[selectedIndex].setFillColor(normalColor);
		selectedIndex--;
		options[selectedIndex].setFillColor(selectedColor);
	}
}

// Changes selection to next item
void Options::moveDown()
{
	if (selectedIndex < (int)options.size() - 1)
	{
		options[selectedIndex].setFillColor(normalColor);
		selectedIndex++;
		options[selectedIndex].setFillColor(selectedColor);
	}
}

// Handles window resizing and UI positioning
void Options::refresh(sf::RenderWindow& window)
{
	sf::Vector2u winSize = window.getSize();
	float hf = static_cast<float>(winSize.y);

	// Re-bind texture to sprite (Fixes potential white screen after window.create)
	backgroundSprite.setTexture(backgroundTexture, true);

	if (backgroundTexture.getSize().x > 0 && backgroundTexture.getSize().y > 0)
	{
		backgroundSprite.setScale({
			static_cast<float>(winSize.x) / backgroundTexture.getSize().x,
			static_cast<float>(winSize.y) / backgroundTexture.getSize().y
			});
	}

	float spacing = 60.f;
	float startY = hf * 0.80f;


	for (size_t i = 0; i < options.size(); ++i)
	{
		float x = 50.f;
		float y = startY + (static_cast<float>(i) * spacing);
		options[i].setPosition({ x, y });
	}
}