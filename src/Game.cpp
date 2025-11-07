
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

	delete[] animals;
	delete[] passports;
	delete character;
	delete passport;

}

bool Game::init()
{
	
	

	character = new sf::Sprite;
	passport = new sf::Sprite;

	if (in_menu)
	{
		in_menu = true;

	    menuTexts();
		renderMenu();

	}
	

    return true;

}

void Game::update(float dt)
{
	if (is_running == true)
	{
		if (!in_menu)
		{
			renderGame();
		}
	}
}

void Game::render()
{
	if (in_menu)
	{
		renderMenu();
	}

	else
	{
		renderGame();
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
	//menu texture
	if (!menu_background_texture.loadFromFile("../Data/Images/Stock_Images/Menu_back.jpeg"))
	{
		std::cout << "background texture did not load \n";
	}

	menu_background.setTexture(menu_background_texture);
	menu_background.setScale(.15, .15);
	menu_background.setPosition(130, 310);

	window.draw(menu_background);
	window.draw(menu_text);
	window.draw(play_text);
	window.draw(quit_text);
	
		

}

void Game::renderGame()
{
	/*if (!officer_white_texture.loadFromFile("../Data/Images/Stock_Images/OfficersWhite.jpeg"))
	{
		std::cout << "background texture did not load \n";
	}

	if (!officer_black_texture.loadFromFile("../Data/Images/Stock_Images/OfficersBlack.jpeg"))
	{
		std::cout << "background texture did not load \n";
	}

	officer_white.setTexture(officer_white_texture);
	officer_white.setScale(.15, .15);
	officer_white.setPosition(130, 310);

	window.draw(officer_white);

	officer_black.setTexture(officer_black_texture);
	officer_black.setScale(.15, .15);
	officer_black.setPosition(130, 310);

	window.draw(officer_black);*/

	if (!game_background_texture.loadFromFile("../Data/Images/Stock_Images/GameBackground.png"))
	{
		std::cout << "background texture did not load \n";
	}

	game_background.setTexture(game_background_texture);
	game_background.setScale(.15, .15);
	game_background.setPosition(125, 20);
	window.draw(game_background);

	if (!stop_font.loadFromFile("../Data/Fonts/STOP.ttf"))
	{
		std::cout << "Font did not load";
	}

	stop_text.setFont(stop_font);
	stop_text.setString("STOP!");
	stop_text.setCharacterSize(50);
	stop_text.setFillColor(sf::Color::Red);
	stop_text.setPosition(380, 65);

	window.draw(stop_text);
}

// - - - - - - - - - - - - - Menu / Game UI - - - - - - - - - - - - -

void Game::menuTexts()
{
	// menu font file
	if (!menu_font.loadFromFile("../Data/Fonts/Impact.ttf"))
	{
		std::cout << "Font did not load";
	}

	// play font file
	if (!play_font.loadFromFile("../Data/Fonts/Impact.ttf"))
	{
		std::cout << "Font did not load";
	}


	// menu title text
	menu_text.setFont(menu_font);
	menu_text.setString("Pawder-Patrol");
	menu_text.setCharacterSize(110);
	/*menu_text.setLetterSpacing(2);*/
	menu_text.setFillColor(sf::Color::Black);
	menu_text.setOutlineColor(sf::Color::White);
	menu_text.setOutlineThickness(3);
	menu_text.setPosition(
		window.getSize().x / 2 - menu_text.getGlobalBounds().width / 2, 10);

	// play text in menu
	play_text.setFont(play_font);
	play_text.setString("PLAY");
	play_text.setCharacterSize(75);
	play_text.setLetterSpacing(1);
	play_text.setFillColor(sf::Color::Black);
	play_text.setOutlineColor(sf::Color::White);
	play_text.setOutlineThickness(2);
	play_text.setPosition(
		window.getSize().x / 4.5 - play_text.getGlobalBounds().width / 2, 170);

	// quit text in menu
	quit_text.setFont(play_font);
	quit_text.setString("quit");
	quit_text.setCharacterSize(75);
	quit_text.setLetterSpacing(1);
	quit_text.setFillColor(sf::Color::White);
	quit_text.setOutlineColor(sf::Color::Black);
	quit_text.setOutlineThickness(2);
	quit_text.setPosition(
		window.getSize().x / 4.5 - quit_text.getGlobalBounds().width / 2, 285);


}

void Game::toggleMenuSelection()
{

	play_selected = !play_selected;

	if (play_selected)
	{

		play_text.setString("play");
		play_text.setFillColor(sf::Color::Black);
		play_text.setOutlineColor(sf::Color::White);
		quit_text.setFillColor(sf::Color::White);
		quit_text.setOutlineColor(sf::Color::Black);
		quit_text.setString("quit");

	}

	else
	{

		play_text.setString("play");
		play_text.setFillColor(sf::Color::White);
		play_text.setOutlineColor(sf::Color::Black);
		quit_text.setFillColor(sf::Color::Black);
		quit_text.setOutlineColor(sf::Color::White);
		quit_text.setString("quit");
		 
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


