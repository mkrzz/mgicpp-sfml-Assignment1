
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
	initialiseButtons();
	initialiseStamps();
	initialisePassports();
	newAnimal();
	
    return true;

}

void Game::update(float dt)
{

	if (is_running == true)
	{

		dragSprite(dragged);
		

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
		renderButtons();
		renderStamps();
		
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

void Game::mouseButtonPressed(sf::Event event)
{

	
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		
		sf::Vector2f mouse_position(event.mouseButton.x, event.mouseButton.y);
		sf::Vector2i click = sf::Mouse::getPosition(window);
		sf::Vector2f clickf = static_cast<sf::Vector2f>(click);

		

		if (passport->getGlobalBounds().contains(clickf))
		{

			dragged = passport;
			
		}

		if (button_visability)
		{

			if (accept_button.getGlobalBounds().contains(clickf))
			{

				std::cout << "Passport accepted\n";

				button_visability = false;
				passport_accepted = true;
				passport_rejected = false;
				stamp_pressed = true;

				renderStamps();

				// sets stamp to same position as button
				accept_stamp.setPosition(accept_button.getPosition());

				stamp_offset = accept_stamp.getPosition() - passport->getPosition();
				
			

			}

			else if (reject_button.getGlobalBounds().contains(clickf))
			{

				std::cout << "Passport rejected\n";

				button_visability = false;
				passport_accepted = false;
				passport_rejected = true;
				stamp_pressed = true;
			
				renderStamps();

				reject_stamp.setPosition(reject_button.getPosition());

				stamp_offset = reject_stamp.getPosition() - passport->getPosition();
				

			}
		}

		drag_offset = clickf - passport->getPosition();

	}

	if (event.mouseButton.button == sf::Mouse::Right)
	{

		sf::Vector2f mouse_position(event.mouseButton.x, event.mouseButton.y);
		sf::Vector2i click = sf::Mouse::getPosition(window);
		sf::Vector2f clickf = static_cast<sf::Vector2f>(click);

		accept_button.setPosition(mouse_position.x, mouse_position.y);
		reject_button.setPosition(mouse_position.x, mouse_position.y + accept_button.getGlobalBounds().height + 10);
		
		button_visability = true; 
		
		
	}

}

void Game::mouseButtonReleased(sf::Event event)
{

	button_visability = false;

	if (event.mouseButton.button == sf::Mouse::Left && dragged == passport)
	{
		dragged = nullptr;
		
		// collision detection between passport and animal, spawns new animal when detected 
		// added check to make sure passport has been stamped before accepting/rejecting
		if (stamp_pressed && passport->getGlobalBounds().intersects(character->getGlobalBounds()))
		{
			std::cout << "Delivered\n";

			stamp_pressed = false;

			newAnimal();
		}

	}
	
	

}




// - - - - - - - - - - - - - Rendering - - - - - - - - - - - - - - -


void Game::renderMenu()
{

	//menu texture
	if (!menu_background_texture.loadFromFile("../Data/Images/Stock_Images/Ark-p.png"))
	{
		std::cout << "background texture did not load \n";
	}

	
	menu_background.setTexture(menu_background_texture);
	menu_background.setScale(.16, .16);
	menu_background.setPosition(150, 280);
	
		

	window.draw(menu_background);
	window.draw(menu_text);
	window.draw(play_text);
	window.draw(quit_text);
	
		

}

void Game::renderWorld()
{
	

	if (!game_background_texture.loadFromFile("../Data/Images/Stock_Images/GameBackground.png"))
	{
		std::cout << "background texture did not load \n";
	}

	game_background.setTexture(game_background_texture);
	/*game_background.setScale(0, 0);*/
	game_background.setPosition(0, 0);
	/*window.draw(game_background);*/

	if (!stop_font.loadFromFile("../Data/Fonts/STOP.ttf"))
	{
		std::cout << "Font did not load";
	}

	playerLives();

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
	menu_text.setString("A.r.k");
	menu_text.setCharacterSize(110);
	menu_text.setLetterSpacing(1);
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

	if (!animals[0].loadFromFile("../Data/Images/Stock_images/Cow-P.png"))
	{
		std::cout << "image did not load";
	}

	if (!animals[1].loadFromFile("../Data/Images/Stock_images/Panda-P.png"))
	{
		std::cout << "image did not load";
	}

	if (!animals[2].loadFromFile("../Data/Images/Stock_images/Seal-P.png"))
	{
		std::cout << "image did not load";
	}

	

}

void Game::initialisePassports()
{

	if (!passports[0].loadFromFile("../Data/Images/Stock_images/Cow_passport.png"))
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

void Game::initialiseButtons()
{

	if (!accept_texture.loadFromFile("../Data/Images/Critter_Crossing/accept button.png"))
	{
		std::cout << "image did not load";
	}

	if (!reject_texture.loadFromFile("../Data/Images/Critter_Crossing/reject button.png"))
	{
		std::cout << "image did not load";
	}

	accept_button.setTexture(accept_texture);
	reject_button.setTexture(reject_texture);



}

void Game::initialiseStamps()
{

	if (!accept_stamp_texture.loadFromFile("../Data/Images/Critter_Crossing/accept.png"))
	{
		std::cout << "image did not load";
	}

	if (!reject_stamp_texture.loadFromFile("../Data/Images/Critter_Crossing/reject.png"))
	{
		std::cout << "image did not load";
	}

	accept_stamp.setTexture(accept_stamp_texture);
	reject_stamp.setTexture(reject_stamp_texture);

	



}

void Game::renderButtons()
{

	if (button_visability)
	{
		window.draw(accept_button);
		window.draw(reject_button);

	}

}

void Game::renderStamps()
{


	if (passport_accepted)
	{
		window.draw(accept_stamp);
	}
	else if (passport_rejected)
	{
		window.draw(reject_stamp);
	}
	
}






// - - - - - - - - - - - - - Spawn new animal - - - - - - - - - - - - -


void Game::newAnimal()
{

	passport_accepted = false;
	passport_rejected = false;
	stamp_pressed = false;

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
	character->setScale(.33, .33);
	character->setPosition(window.getSize().x / 10 + 35, window.getSize().y / 11 + 40);

	passport->setTexture(passports[passport_index]);
	passport->setScale(0.6, 0.6);
	passport->setPosition(window.getSize().x / 2, window.getSize().y / 3);



}



void Game::dragSprite(sf::Sprite* sprite)
{

	if (sprite != nullptr)
	{

		sf::Vector2i mouse_position = sf::Mouse::getPosition(window);

		sf::Vector2f mouse_positionf = static_cast<sf::Vector2f>(mouse_position);

		sf::Vector2f drag_position = mouse_positionf - drag_offset;

		sprite->setPosition(drag_position.x, drag_position.y);

		// sets the stamp positions relative to the passports when dragging
		if (sprite == passport && stamp_pressed)
		{
			accept_stamp.setPosition(drag_position + stamp_offset);
			reject_stamp.setPosition(drag_position + stamp_offset);
		}

	}
}


void Game::playerLives()
{

	if (!lives_texture.loadFromFile("../Data/Images/Lives/Wheel_lives.png"))
	{

		std::cout << "Texture did not load";

	}

	for (int i = 0; i < player_lives; ++i)
	{
			
		lives.setTexture(lives_texture);
		lives.setScale(0.025f, 0.025f);
		lives.setPosition(10 + i * 70, 10);
		window.draw(lives);

	}

}
