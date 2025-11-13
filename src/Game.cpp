
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

	in_menu = true;
	
	menuTexts();
	renderMenu();
	initialiseSprites();
	initialiseAnimals();
	initialisePassports();
	/*newAnimal();*/
	
    return true;

}

void Game::update(float dt)
{

	if (is_running == true)
	{

		
		
	}

}

void Game::render()
{

	if (in_menu)
	{

		renderMenu();
		
		
	}

	else if (is_running)
	{

		renderWorld();
		renderSprites();
		
		
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
	menu_background.setScale(.14, .14);
	menu_background.setPosition(165, 330);

	window.draw(menu_background);
	window.draw(menu_text);
	window.draw(play_text);
	window.draw(quit_text);
	
		

}

void Game::renderWorld()
{
	

	if (!game_background_texture.loadFromFile("../Data/Images/Stock_Images/Background_.png"))
	{
		std::cout << "background texture did not load \n";
	}

	game_background.setTexture(game_background_texture);
	game_background.setScale(1, 1);
	game_background.setPosition(1, 1);
	window.draw(game_background);

	if (!stop_font.loadFromFile("../Data/Fonts/STOP.ttf"))
	{
		std::cout << "Font did not load";
	}

	/*stop_text.setFont(stop_font);
	stop_text.setString("STOP!");
	stop_text.setCharacterSize(50);
	stop_text.setFillColor(sf::Color::Red);
	stop_text.setPosition(375, 35);
	window.draw(stop_text);*/

	/*box.setSize(sf::Vector2f(870, 300));
	box.setPosition(100, 380);
	box.setOutlineColor(sf::Color::Black);
	box.setOutlineThickness(1);
	window.draw(box);*/

	/*box2.setSize(sf::Vector2f(300, 300));
	box2.setPosition(700, 380);
	box2.setOutlineColor(sf::Color::Black);
	box2.setOutlineThickness(1);
	window.draw(box2);*/
}

void Game::renderSprites()
{

	window.draw(*character);
	window.draw(*passport);

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
		window.getSize().x / 2 - menu_text.getGlobalBounds().width / 2, 30);

	// play text in menu
	play_text.setFont(play_font);
	play_text.setString("PLAY");
	play_text.setCharacterSize(75);
	play_text.setLetterSpacing(1);
	play_text.setFillColor(sf::Color::Black);
	play_text.setOutlineColor(sf::Color::White);
	play_text.setOutlineThickness(2);
	play_text.setPosition(
		window.getSize().x / 4.5 - play_text.getGlobalBounds().width / 2, 190);

	// quit text in menu
	quit_text.setFont(play_font);
	quit_text.setString("quit");
	quit_text.setCharacterSize(75);
	quit_text.setLetterSpacing(1);
	quit_text.setFillColor(sf::Color::White);
	quit_text.setOutlineColor(sf::Color::Black);
	quit_text.setOutlineThickness(2);
	quit_text.setPosition(
		window.getSize().x / 4.5 - quit_text.getGlobalBounds().width / 2, 305);


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


// - - - - - - - - - - - - - Initialise - - - - - - - - - - - - -


void Game::initialiseSprites()
{

	character = new sf::Sprite;
	passport = new sf::Sprite;

}

void Game::initialiseAnimals()
{

	if (!animals[0].loadFromFile("../Data/Images/Critter_Crossing/elephant.png"))
	{
		std::cout << "image did not load";
	}

	if (!animals[1].loadFromFile("../Data/Images/Critter_Crossing/moose.png"))
	{
		std::cout << "image did not load";
	}

	if (!animals[2].loadFromFile("../Data/Images/Critter_Crossing/penguin.png"))
	{
		std::cout << "image did not load";
	}

	

}

void Game::initialisePassports()
{

	if (!passports[0].loadFromFile("../Data/Images/Critter_Crossing/elephant passport.png"))
	{
		std::cout << "image did not load";
	}

	if (!passports[1].loadFromFile("../Data/Images/Critter_Crossing/moose passport.png"))
	{
		std::cout << "image did not load";
	}

	if (!passports[2].loadFromFile("../Data/Images/Critter_Crossing/penguin passport.png"))
	{
		std::cout << "image did not load";
	}

	
}


// - - - - - - - - - - - - - Spawn new animal - - - - - - - - - - - - -

void Game::newAnimal()
{

	passport_accepted = false;
	passport_rejected = false;

	int animal_index = rand() % 3;
	int passport_index = rand() % 3;

	if (animal_index == passport_index)
	{

		should_accept = true;

	}
	else
	{

		should_accept = false;

	}

	character->setTexture(animals[animal_index], true);
	character->setScale(1.8, 1.8);
	character->setPosition(window.getSize().x / 12, window.getSize().y / 12);

	passport->setTexture(passports[passport_index]);
	passport->setScale(0.6, 0.6);
	passport->setPosition(window.getSize().x / 2, window.getSize().y / 3);



}