
#include "Game.h"
#include <iostream>
#include <SFML/Graphics.hpp>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{
	in_menu = true;

	menuTexts();

  return true;
}

void Game::update(float dt)
{
	if (is_running == true)
	{
		if (!in_menu)
		{

		}
	}
}

void Game::render()
{
	if (in_menu)
	{
		renderMenu();
	}

}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);


}

void Game::keyPressed(sf::Event event)
{

}

void Game::keyReleased(sf::Event event)
{

}

// - - - - - - - - - - - - - Rendering - - - - - - - - - - - - - - -

void Game::renderMenu()
{

	window.draw(menu_text);
	window.draw(play_text);
	window.draw(quit_text);

}

// - - - - - - - - - - - - - Menu / Game UI - - - - - - - - - - - - -

void Game::menuTexts()
{
	// menu font file
	if (!menu_font.loadFromFile("../Data/Fonts/orange.ttf"))
	{
		std::cout << "Font did not load";
	}

	// play font file
	if (!play_font.loadFromFile("../Data/Fonts/Blocks.ttf"))
	{
		std::cout << "Font did not load";
	}


	// menu title text
	menu_text.setFont(menu_font);
	menu_text.setString("Paw-der Patrol");
	menu_text.setCharacterSize(140);
	menu_text.setLetterSpacing(2);
	menu_text.setFillColor(sf::Color::White);
	menu_text.setPosition(
		window.getSize().x / 2 - menu_text.getGlobalBounds().width / 2, 50);

	// play text in menu
	play_text.setFont(play_font);
	play_text.setString(" [PLAY]");
	play_text.setCharacterSize(60);
	play_text.setLetterSpacing(2);
	play_text.setFillColor(sf::Color::White);
	play_text.setPosition(
		window.getSize().x / 2 - play_text.getGlobalBounds().width / 2, 300);

	// quit text in menu
	quit_text.setFont(play_font);
	quit_text.setString(" QUIT");
	quit_text.setCharacterSize(60);
	quit_text.setLetterSpacing(2);
	quit_text.setFillColor(sf::Color::White);
	quit_text.setPosition(
		window.getSize().x / 2 - quit_text.getGlobalBounds().width / 2, 400);
}

