
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

  sf::RectangleShape box;
  sf::RectangleShape underscore;
  sf::RectangleShape underscore1;

  bool in_menu = true;
  bool play_selected = true;
  bool is_running = true;

  void menuTexts();
  void renderMenu();
  void toggleMenuSelection();
  void handleMenuSelection();

};

#endif // PLATFORMER_GAME_H
