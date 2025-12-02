
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
  void mouseButtonPressed(sf::Event event);
  void mouseButtonReleased(sf::Event event);

 private:
  sf::RenderWindow& window;
  
  sf::Font menu_font;
  sf::Font play_font;
  sf::Font quit_font;
  sf::Font main_game_font;

  sf::Text menu_text;
  sf::Text play_text;
  sf::Text quit_text;
  sf::Text main_game_text;


  sf::Sprite* character;
  sf::Sprite* passport;

  sf::Texture* animals = new sf::Texture[5];
  sf::Texture* passports = new sf::Texture[5];

  sf::Sprite menu_background;
  sf::Texture menu_background_texture;

  sf::Sprite game_background;
  sf::Texture game_background_texture;

  sf::RectangleShape flood_gauge;
  float flood_timer = 0.f;
  float flood_max_timer = 30.0f;

  sf::Sprite* dragged = nullptr;
  sf::Vector2f drag_offset;

  sf::Sprite accept_button;
  sf::Texture accept_texture;

  sf::Sprite reject_button;
  sf::Texture reject_texture;

  sf::Sprite accept_stamp;
  sf::Texture accept_stamp_texture;

  sf::Sprite reject_stamp;
  sf::Texture reject_stamp_texture;

  sf::Vector2f stamp_offset;

  sf::Sprite lives;
  sf::Texture lives_texture;

  int player_lives = 3;


  bool in_menu = true;
  bool play_selected = true;
  bool is_running = true;
  bool passport_accepted = false;
  bool passport_rejected = false;
  bool should_accept = false;
  bool is_dragging = false;
  bool button_visability = false;
  bool stamp_pressed = false;
  bool wrong_name = false;
 

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
  void dragSprite(sf::Sprite* sprite);
  void initialiseButtons();
  void initialiseStamps();
  void renderButtons();
  void renderStamps();
  void playerLives();
  void initialiseFloodGauge();
  void floodTimer(float dt);
  void passportApprovedText();
  void passportDeniedText();
  void rejectedValidPassportText();
  void passportDidNotMatchText();
  


};

#endif // PLATFORMER_GAME_H
