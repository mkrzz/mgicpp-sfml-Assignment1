
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
	if (in_menu)
	{

		if ((event.key.code == sf::Keyboard::Up) || (event.key.code == sf::Keyboard::Down))
		{

			toggleMenuSelection();

		}
		else if (event.key.code == sf::Keyboard::Enter)
		{

			handleMenuSelection();
			

		}

	}
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
	menu_text.setFillColor(sf::Color::Black);
	menu_text.setOutlineColor(sf::Color::White);
	menu_text.setOutlineThickness(3);
	menu_text.setPosition(
		window.getSize().x / 2 - menu_text.getGlobalBounds().width / 2, 50);

	// play text in menu
	play_text.setFont(play_font);
	play_text.setString("  PLAY ");
	play_text.setCharacterSize(80);
	play_text.setLetterSpacing(2);
	play_text.setFillColor(sf::Color::Black);
	play_text.setOutlineColor(sf::Color::White);
	play_text.setOutlineThickness(2);
	play_text.setPosition(
		window.getSize().x / 4 - play_text.getGlobalBounds().width / 2, 300);

	// quit text in menu
	quit_text.setFont(play_font);
	quit_text.setString("  quit  ");
	quit_text.setCharacterSize(80);
	quit_text.setLetterSpacing(2);
	quit_text.setFillColor(sf::Color::White);
	quit_text.setOutlineColor(sf::Color::Black);
	quit_text.setOutlineThickness(2);
	quit_text.setPosition(
		window.getSize().x / 4 - quit_text.getGlobalBounds().width / 2, 400);
}

void Game::toggleMenuSelection()
{

	play_selected = !play_selected;

	if (play_selected)
	{

		play_text.setString("  PLAY ");
		play_text.setFillColor(sf::Color::Black);
		play_text.setOutlineColor(sf::Color::White);
		quit_text.setFillColor(sf::Color::White);
		quit_text.setOutlineColor(sf::Color::Black);
		quit_text.setString("  quit  ");

	}

	else
	{

		play_text.setString("  play  ");
		play_text.setFillColor(sf::Color::White);
		play_text.setOutlineColor(sf::Color::Black);
		quit_text.setFillColor(sf::Color::Black);
		quit_text.setOutlineColor(sf::Color::White);
		quit_text.setString("  QUIT  ");
		 
	}

}

void Game::handleMenuSelection()
{

	if (play_selected)
	{

		in_menu = false;
		is_running = true;


	}
	else
	{

		window.close();

	}

}