#include "menu.h"
#include <iostream>

// Constructor: Initializes assets, creates menu items, and sets initial state
Menu::Menu(sf::RenderWindow& window)
	: backgroundSprite(backgroundTexture)
{
	// Load font for menu text
	if (!font.openFromFile("fonts/arial.ttf"))
	{
		std::cout << "Error: fonts/arial.ttf not found!" << std::endl;
	}

	// Load background image
	if (!backgroundTexture.loadFromFile("photos/menu-options-jimi-hendrix.png"))
	{
		std::cerr << "CRITICAL ERROR: photos/menu-options-jimi-hendrix.png not found!" << std::endl;
	}
	else
	{
		std::cout << "SUCCESS: Image loaded correctly!" << std::endl;
		backgroundSprite.setTexture(backgroundTexture, true);
	}

	// Initialize menu options
	std::vector<std::string> names = { "Play", "Options", "Exit" };
	for (const auto& name : names)
	{
		sf::Text text(font, name, 36);
		text.setFillColor(normalColor);
		options.push_back(text);
	}

	// Highlight the first option by default
	if (!options.empty())
	{
		options[selectedIndex].setFillColor(selectedColor);
	}

	refresh(window);
}

// Main execution loop for the menu: handles events and logic
int Menu::run(sf::RenderWindow& window)
{
	refresh(window);
	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			// Window close event
			if (event->is<sf::Event::Closed>())
			{
				window.close();
				return 2;
			}

			// Keyboard navigation
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
					return selectedIndex; // Return the chosen option index
				}
			}

			// Mouse hover logic
			if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
			{
				sf::Vector2f mousePos = window.mapPixelToCoords(mouseMoved->position);
				for (size_t i = 0; i < options.size(); ++i)
				{
					if (options[i].getGlobalBounds().contains(mousePos))
					{
						options[selectedIndex].setFillColor(normalColor);
						selectedIndex = static_cast<int>(i);
						options[selectedIndex].setFillColor(selectedColor);
					}
				}
			}
		}
		draw(window);
	}
	return 2;
}

// Renders background and menu options to the screen
void Menu::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color(50, 50, 50));
	window.draw(backgroundSprite);
	for (const auto& text : options)
	{
		window.draw(text);
	}
	window.display();
}

// Selection logic: moves selection up in the list
void Menu::moveUp()
{
	if (selectedIndex > 0)
	{
		options[selectedIndex].setFillColor(normalColor);
		selectedIndex--;
		options[selectedIndex].setFillColor(selectedColor);
	}
}

// Selection logic: moves selection down in the list
void Menu::moveDown()
{
	if (selectedIndex < (int)options.size() - 1)
	{
		options[selectedIndex].setFillColor(normalColor);
		selectedIndex++;
		options[selectedIndex].setFillColor(selectedColor);
	}
}

// UI Adjustment: recalculates positions and scales based on window size
void Menu::refresh(sf::RenderWindow& window)
{
	sf::Vector2u winSize = window.getSize();
	float wf = static_cast<float>(winSize.x);
	float hf = static_cast<float>(winSize.y);

	// 1. Setup View configuration
	sf::View view;
	view.setSize({ wf, hf });
	view.setCenter({ wf / 2.f, hf / 2.f });
	window.setView(view);

	// 2. Scale background to fit window
	if (backgroundTexture.getSize().x > 0 && backgroundTexture.getSize().y > 0)
	{
		float tx = static_cast<float>(backgroundTexture.getSize().x);
		float ty = static_cast<float>(backgroundTexture.getSize().y);
		backgroundSprite.setScale({ wf / tx, hf / ty });
		backgroundSprite.setPosition({ 0.f, 0.f });
	}

	// 3. Position menu text options
	float spacing = 60.f;
	float startY = hf * 0.80f;


	for (size_t i = 0; i < options.size(); ++i)
	{
		float x = 50.f;
		float y = startY + (static_cast<float>(i) * spacing);
		options[i].setPosition({ x, y });
	}
}