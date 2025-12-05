
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
	
	
	initialiseMenuFonts();
	initialiseMenu();
	initialiseMainGameFont();
	initialisePlayAgainFont();
	initialiseEndOfDayFont();
	initialiseSprites();
	initialiseAnimals();
	initialiseButtons();
	initialiseStamps();
	initialisePassports();
	initialiseFloodGauge();
	initialisePlayerLives();
	initialiseGameScreen();
	newAnimal();
	initialiseGameTimer();
	initialiseOverlay();
	
	
	
	
	
    return true;

}

void Game::update(float dt)
{

	if (is_running == true)
	{

		dragSprite(dragged);
		floodTimer(dt);
		checkPlayerDead();
		gameTimer();
		
	}

	
}

void Game::render()
{

	if (in_menu)
	{

		drawMenu();

	}

	else
	{


		drawWorld();
		drawSprites();
		drawButtons();
		drawStamps();
		drawPlayerLives();
		drawFloodGauge();
		window.draw(timer_text);

		
		if (show_overlay)
		{

			endOfDay();

		}

		if (time_up)
		{

			drawFloodHasRisenText();
			
		}
					
		else if (is_dead)
		{

			drawNoLivesText();
			

		}
		
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

	// resets game if game over - restarts each day fresh
	else
	{
		if (event.key.code == sf::Keyboard::Enter)
		{

			if (is_dead || time_up)
			{

				restartGame();
				newAnimal();

			}
			else if (show_overlay)
			{

				show_overlay = false;
				startNewDay();
				game_clock.restart();
				newAnimal();

			}
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


				button_visability = false;
				passport_accepted = true;
				passport_rejected = false;
				stamp_pressed = true;
				

				drawStamps();

				// sets stamp to same position as button
				accept_stamp.setPosition(accept_button.getPosition());

				stamp_offset = accept_stamp.getPosition() - passport->getPosition();
				
				
			

			}

			else if (reject_button.getGlobalBounds().contains(clickf))
			{


				button_visability = false;
				passport_accepted = false;
				passport_rejected = true;
				stamp_pressed = true;
				
			
				drawStamps();

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

		// position of stamps relative to mouse position
		accept_button.setPosition(mouse_position.x - 20 - accept_button.getGlobalBounds().width,
			mouse_position.y - accept_button.getGlobalBounds().height / 2);
		reject_button.setPosition(mouse_position.x + 20, mouse_position.y - reject_button.getGlobalBounds().height / 2);
		
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
		// displays correct text depending on player stamp choice 

		if (stamp_pressed && passport->getGlobalBounds().intersects(character->getGlobalBounds()))
		{
			
			handlePassportTextChoice();
			
			stamp_pressed = false;

			newAnimal();

		}

	}
	
	

}




// - - - - - - - - - - - - - Draw - - - - - - - - - - - - - - -



void Game::drawSprites()
{

	window.draw(*character);
	window.draw(*passport);

}

void Game::drawButtons()
{

	if (button_visability)
	{
		window.draw(accept_button);
		window.draw(reject_button);

	}

}

void Game::drawStamps()
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

void Game::drawPlayerLives()
{

	for (int i = 0; i < player_lives; ++i)
	{

		lives.setPosition(100 + i * 70, 300);
		window.draw(lives);

	}

}

void Game::drawNoLivesText()
{
	
	// adds a transparantish overlay when player dies
	sf::RectangleShape overlay(sf::Vector2f(window.getSize()));
	overlay.setFillColor(sf::Color(0, 0, 0, 200));
	
	window.draw(overlay);
	

	window.draw(dead_text);
	window.draw(play_again_text);

	is_running = false;


}

void Game::drawMenu()
{

	timer_active = false;

	window.draw(menu_background);
	window.draw(menu_text);
	window.draw(play_text);
	window.draw(quit_text);

}

void Game::drawWorld()
{

	timer_active = true;
				
	window.draw(game_background);
	window.draw(main_game_text);


}

void Game::drawFloodHasRisenText()
{

	if (flood_timer >= flood_max_timer)
	{

		// adds a transparant-ish overlay when player dies
		sf::RectangleShape overlay(sf::Vector2f(window.getSize()));
		overlay.setFillColor(sf::Color(0, 0, 0, 200));
		window.draw(overlay);


		out_of_time_text.setFont(dead_font);
		out_of_time_text.setCharacterSize(100);
		out_of_time_text.setFillColor(sf::Color::White);
		out_of_time_text.setString("The flood has risen\n You saved " + std::to_string(passports_approved) + " animals");
		out_of_time_text.setPosition(window.getSize().x / 2 - out_of_time_text.getGlobalBounds().width / 2, 20);

		window.draw(out_of_time_text);

	}

}

void Game::drawFloodGauge()
{


	//disables timer from game over screen
	if (show_timer)
	{
		window.draw(flood_gauge);
	}




}




// - - - - - - - - - - - - - Menu / Game UI - - - - - - - - - - - - -



void Game::toggleMenuSelection()
{

	play_selected = !play_selected;

	if (play_selected)
	{

		play_text.setString("play");
		play_text.setFillColor(sf::Color::White);
		play_text.setOutlineColor(sf::Color::Black);
		quit_text.setFillColor(sf::Color::Black);
		quit_text.setOutlineColor(sf::Color::White);
		quit_text.setString("quit");

	}

	else
	{

		play_text.setString("play");
		play_text.setFillColor(sf::Color::Black);
		play_text.setOutlineColor(sf::Color::White);
		quit_text.setFillColor(sf::Color::White);
		quit_text.setOutlineColor(sf::Color::Black);
		quit_text.setString("quit");
		 
	}

}

void Game::handleMenuSelection()
{

	if (play_selected)
	{

		is_running = true;
		in_menu = false;

		game_clock.restart();
		show_overlay = false;
		time_up = false;
		
		
		
		

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

	if (!animals[0].loadFromFile("../Data/Images/Animal_set/Bear.png"))
	{
		std::cout << "image did not load";
	}

	if (!animals[1].loadFromFile("../Data/Images/Animal_set/Frog.png"))
	{
		std::cout << "image did not load";
	}

	if (!animals[2].loadFromFile("../Data/Images/Animal_set/Pig.png"))
	{
		std::cout << "image did not load";
	}

	if (!animals[3].loadFromFile("../Data/Images/Animal_set/Seagul.png"))
	{
		std::cout << "image did not load";
	}
	
	if (!animals[4].loadFromFile("../Data/Images/Animal_set/Wolf.png"))
	{
		std::cout << "image did not load";
	}


}

void Game::initialisePassports()
{

	if (!passports[0].loadFromFile("../Data/Images/Passports/Bear_Passport.png"))
	{
		std::cout << "image did not load";
	}

	if (!passports[1].loadFromFile("../Data/Images/Passports/Frog_Passport.png"))
	{
		std::cout << "image did not load";
	}

	if (!passports[2].loadFromFile("../Data/Images/Passports/Pig_Passport.png"))
	{
		std::cout << "image did not load";
	}

	if (!passports[3].loadFromFile("../Data/Images/Passports/Seagul_Passport.png"))
	{
		std::cout << "image did not load";
	}

	if (!passports[4].loadFromFile("../Data/Images/Passports/Wolf_Passport.png"))
	{
		std::cout << "image did not load";
	}


}

void Game::initialiseButtons()
{

	if (!accept_texture.loadFromFile("../Data/Images/Stamps/Approved_button_new.png"))
	{
		std::cout << "image did not load";
	}

	if (!reject_texture.loadFromFile("../Data/Images/Stamps/Rejected_button_new.png"))
	{
		std::cout << "image did not load";
	}

	accept_button.setTexture(accept_texture);
	reject_button.setTexture(reject_texture);
	accept_button.setScale(.7f, .7f);
	reject_button.setScale(.7f, .7f);



}

void Game::initialiseStamps()
{

	if (!accept_stamp_texture.loadFromFile("../Data/Images/Stamps/Approved_stamp.png"))
	{
		std::cout << "image did not load";
	}

	if (!reject_stamp_texture.loadFromFile("../Data/Images/Stamps/Rejected_stamp.png"))
	{
		std::cout << "image did not load";
	}

	accept_stamp.setTexture(accept_stamp_texture);
	reject_stamp.setTexture(reject_stamp_texture);
	accept_stamp.setScale(.7f, .7f);
	reject_stamp.setScale(.7f, .7f);

	



}

void Game::initialiseFloodGauge()
{
	flood_gauge.setSize(sf::Vector2f(200.f, 25.f));
	flood_gauge.setFillColor(sf::Color::Blue);
	flood_gauge.setPosition(20.f, 20.f);
}

void Game::initialiseMenu()
{

	//menu texture
	if (!menu_background_texture.loadFromFile("../Data/Images/Stock_Images/Ark-p.png"))
	{
		std::cout << "background texture did not load \n";
	}

	/*menu_background.setTexture(menu_background_texture);
	menu_background.setScale(.16, .16);
	menu_background.setPosition(150, 280);*/


}

void Game::initialisePlayerLives()
{

	if (!lives_texture.loadFromFile("../Data/Images/Heart.png"))
	{

		std::cout << "Texture did not load";

	}
	lives.setTexture(lives_texture);
	lives.setScale(1.0f, 1.0f);

	dead_text.setFont(dead_font);
	dead_text.setCharacterSize(50);
	dead_text.setFillColor(sf::Color::Black);
	dead_text.setString("You have made too many errors\n");
	dead_text.setPosition(window.getSize().x / 2 - dead_text.getGlobalBounds().width / 2, 20);


	play_again_text.setFont(dead_font);
	play_again_text.setCharacterSize(50);
	play_again_text.setFillColor(sf::Color::Black);
	play_again_text.setString("Play again? \n Press enter");
	play_again_text.setPosition(window.getSize().x / 2 - play_again_text.getGlobalBounds().width / 2, 50);

}

void Game::initialisePlayAgainFont()
{
	if (!dead_font.loadFromFile("../Data/Fonts/open-sans/OpenSans-BoldItalic.ttf"))
	{

		std::cout << "Font did not load";
	}
}

void Game::initialiseGameScreen()
{
	if (!game_background_texture.loadFromFile("../Data/Images/Stock_Images/Artboard 1.png"))
	{
		std::cout << "background texture did not load \n";
	}

	game_background.setTexture(game_background_texture);
	game_background.setScale(1.f, 1.f);
	game_background.setPosition(0.f, 0.f);

}

void Game::initialiseGameTimer()
{

	game_duration = sf::seconds(2);
	timer_text.setFont(dead_font);
	timer_text.setCharacterSize(50);
	timer_text.setFillColor(sf::Color::Black);
	timer_text.setPosition(window.getSize().x - 220, 10);
	timer_text.setString("Time: 2");

	

}

void Game::initialiseMainGameFont()
{

	if (!main_game_font.loadFromFile("../Data/Fonts/VacationPostcardNF.ttf"))
	{
		std::cout << "Font did not load\n";
	}

}

void Game::initialiseMenuFonts()
{
	// menu font file
	if (!menu_font.loadFromFile("../Data/Fonts/VacationPostcardNF.ttf"))
	{
		std::cout << "Font did not load";
	}

	// play font file
	if (!play_font.loadFromFile("../Data/Fonts/Moon Flower.ttf"))
	{
		std::cout << "Font did not load";
	}


	// menu title text
	menu_text.setFont(menu_font);
	menu_text.setString("Passport Please");
	menu_text.setCharacterSize(200);
	/*menu_text.setLetterSpacing(1);*/
	menu_text.setFillColor(sf::Color::Black);
	/*menu_text.setOutlineColor(sf::Color::White);*/
	/*menu_text.setOutlineThickness(3);*/
	menu_text.setPosition(
		window.getSize().x / 2 - menu_text.getGlobalBounds().width / 2, 30);

	// play text in menu
	play_text.setFont(play_font);
	play_text.setString("PLAY");
	play_text.setCharacterSize(150);
	play_text.setLetterSpacing(1);
	play_text.setFillColor(sf::Color::White);
	play_text.setOutlineColor(sf::Color::Black);
	play_text.setOutlineThickness(2);
	play_text.setPosition(
		window.getSize().x / 2 - play_text.getGlobalBounds().width / 2, 290);

	// quit text in menu
	quit_text.setFont(play_font);
	quit_text.setString("quit");
	quit_text.setCharacterSize(150);
	quit_text.setLetterSpacing(1);
	quit_text.setFillColor(sf::Color::Black);
	quit_text.setOutlineColor(sf::Color::White);
	quit_text.setOutlineThickness(2);
	quit_text.setPosition(
		window.getSize().x / 2 - quit_text.getGlobalBounds().width / 2, 435);


}

void Game::initialiseOverlay()
{

	// adds a transparantish overlay when player dies
	overlay.setSize(sf::Vector2f(window.getSize()));
	overlay.setFillColor(sf::Color(0, 0, 0, 200));

}

void Game::initialiseEndOfDayFont()
{

	end_of_day_text.setFont(dead_font);
	end_of_day_text.setCharacterSize(100);
	end_of_day_text.setPosition(
		window.getSize().x / 2 - menu_text.getGlobalBounds().width / 2, 30);

}

void Game::updateEndofDayText()
{

	end_of_day_text.setString("End of day " + std::to_string(current_day));

}


// - - - - - - - - - - - - - Spawn new animal - - - - - - - - - - - - -



void Game::newAnimal()
{

	passport_accepted = false;
	passport_rejected = false;
	
	stamp_pressed = false;

	int animal_index = rand() % 5;
	int passport_index = rand() % 5;

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
	passport->setScale(1.f, 1.f);
	passport->setPosition(window.getSize().x / 2 + 10, window.getSize().y / 3 - 190);
	


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




// - - - - - - - - - - - - - Timer - - - - - - - - - - - - -




void Game::floodTimer(float dt)
{

	//stops timer if not active
	if (!timer_active)
	{
		return;
	}

	//increases at real time speed
	flood_timer += dt;

	// set an end clamp to stop the timer 
	if (flood_timer >= flood_max_timer && !time_up)
	{

		flood_timer = flood_max_timer;
		time_up = true;
		is_running = false;
		show_timer = false;

	}

	// converts timer to control max percentage of gauge (the bars width)
	float percent = flood_timer / flood_max_timer;
	float max_height = 400.0f;
	float current_height = max_height * percent;

	// sets max size of gauge
	flood_gauge.setSize(sf::Vector2f(500.f, current_height));

	// anchors bar from the bottom so bar rises upwards
	flood_gauge.setPosition(50, 600 - current_height);


}

void Game::gameTimer()
{

	if (is_running)
	{
		//sets game timer per round
		sf::Time elapsed = game_clock.getElapsedTime();
		sf::Time remaining = game_duration - elapsed;

		int remainingSeconds = static_cast<int>(remaining.asSeconds());
		timer_text.setString(
			"Time: " + std::to_string(std::max(remainingSeconds, 0)));

		//pauses flood timer when overlay is showing 
		if (remaining <= sf::Time::Zero)
		{
			is_running = false;
			show_overlay = true;
			updateEndofDayText();
			
		}
	}
}

void Game::startNewDay()
{

	//restarts game clock 
	is_running = true;
	show_overlay = false;
	game_duration = sf::seconds(2);
	game_clock.restart();
	current_day++;


}

void Game::endOfDay()
{
	
	window.draw(overlay);
	window.draw(end_of_day_text);
	

	
}





// - - - - - - - - - - - - - Passport - - - - - - - - - - - - -



void Game::passportApprovedText()
{

	

	main_game_text.setFont(main_game_font);
	main_game_text.setString("PASSPORT APPROVED - You may board the Ark\n");
	main_game_text.setCharacterSize(50);
	main_game_text.setPosition(window.getSize().x / 2 - main_game_text.getGlobalBounds().width / 2, 20);
	main_game_text.setFillColor(sf::Color::Black);


	
}

void Game::passportDeniedText()
{
	main_game_text.setFont(main_game_font);
	main_game_text.setString("PASSPORT DENIED!\n");
	main_game_text.setCharacterSize(50);
	main_game_text.setPosition(window.getSize().x / 2 - main_game_text.getGlobalBounds().width / 2, 20);
	main_game_text.setFillColor(sf::Color::Black);
	
}

void Game::rejectedValidPassportText()
{
	main_game_text.setFont(main_game_font);
	main_game_text.setString("VIOLATION - You rejected a valid passport\n\n");
	main_game_text.setCharacterSize(50);
	main_game_text.setPosition(window.getSize().x / 2 - main_game_text.getGlobalBounds().width / 2, 20);
	main_game_text.setFillColor(sf::Color::Black);
	
}

void Game::passportDidNotMatchText()
{

	main_game_text.setFont(main_game_font);
	main_game_text.setString("VIOLATION - Passport did not match!\n");
	main_game_text.setCharacterSize(50);
	main_game_text.setPosition(window.getSize().x / 2 - main_game_text.getGlobalBounds().width / 2, 20);
	main_game_text.setFillColor(sf::Color::Black);
	
}

void Game::handlePassportTextChoice()
{

	if (passport_accepted)
	{

		if (should_accept)
		{

			passportApprovedText();
			std::cout << "PASSPORT APPROVED - You may board the Ark\n";
			passports_approved++;


		}
		else
		{

			passportDidNotMatchText();
			std::cout << "VIOLATION - Passport did not match!\n";
			player_lives--;
			passports_approved_illegally++;


		}

	}
	else if (passport_rejected)
	{

		if (!should_accept)
		{

			passportDeniedText();
			std::cout << "PASSPORT DENIED\n";


		}
		else
		{

			rejectedValidPassportText();
			std::cout << "VIOLATION - You rejected a valid passport\n";
			player_lives--;


		}


	}

	/*if (wrong_name)
	{

		{
			std::cout << "VIOLATION - Wrong name on Passport\n";
		}


	}*/
}



// - - - - - - - - - - - - - Restart Game - - - - - - - - - - - - -



void Game::restartGame()
{

	is_running = true;
	player_lives = 3;
	time_up = false;
	is_dead = false;
	timer_active = true;
	show_timer = true;
	flood_timer = 0.f;
	game_clock.restart();
	game_duration = sf::seconds(45);

}

void Game::checkPlayerDead()
{

	if (player_lives <= 0 && !is_dead)
	{
		is_dead = true;
		is_running = false;
		timer_active = false;
		show_timer = false;
	}


}














