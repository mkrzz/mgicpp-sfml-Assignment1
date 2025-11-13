
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);

 private:
  sf::RenderWindow& window;
  
  sf::Font menu_font;
  sf::Font play_font;
  sf::Font quit_font;

  sf::Text menu_text;
  sf::Text play_text;
  sf::Text quit_text;

  sf::Font stop_font;
  sf::Text stop_text;

  sf::Sprite* character;
  sf::Sprite* passport;

  sf::Texture* animals = new sf::Texture[3];
  sf::Texture* passports = new sf::Texture[3];

  sf::Sprite menu_background;
  sf::Texture menu_background_texture;

  sf::Sprite game_background;
  sf::Texture game_background_texture;
  
  sf::RectangleShape box;
  sf::RectangleShape box2;


  bool in_menu = true;
  bool play_selected = true;
  bool is_running = true;
  bool passport_accepted = true;
  bool passport_rejected = true;
  bool should_accept = false;


  void menuTexts();
  void renderMenu();
  void toggleMenuSelection();
  void handleMenuSelection();
  void renderWorld();
  void initialiseAnimals();
  void initialisePassports();
  void newAnimal();
  void initialiseSprites();
  void renderSprites();


};

#endif // PLATFORMER_GAME_H
