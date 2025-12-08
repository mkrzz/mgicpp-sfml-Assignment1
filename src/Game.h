
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"

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
  sf::RectangleShape overlay;

 private:
  sf::RenderWindow& window;
  
  sf::Font menu_font;
  sf::Font play_font;
  sf::Font quit_font;
  sf::Font main_game_font;
  sf::Font dead_font;

  sf::Text menu_text;
  sf::Text play_text;
  sf::Text quit_text;
  sf::Text main_game_text;
  sf::Text dead_text;
  sf::Text play_again_text;
  sf::Text out_of_time_text;
  sf::Text timer_text;
  sf::Text end_of_day_text;
  sf::Text end_of_day_info_text;
  sf::Text current_day_text;

  sf::Clock game_clock;
  sf::Time game_duration;

  sf::Sprite* character;
  sf::Sprite* passport;

  sf::Texture* animals = new sf::Texture[5];
  sf::Texture* passports = new sf::Texture[5];

  sf::Sprite menu_background;
  sf::Texture menu_background_texture;

  sf::Sprite game_background;
  sf::Texture game_background_texture;

  sf::RectangleShape overlay_rect;
  sf::RectangleShape flood_gauge;
  float flood_timer = 0.f;
  float flood_max_timer = 60.0f * 2;
  float day_timer = 0.f;

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

  sf::SoundBuffer thunderstorm_buffer;
  sf::Sound thunderstorm;
  sf::SoundBuffer bear_buffer;
  sf::Sound bear;
  sf::SoundBuffer cow_buffer;
  sf::Sound cow;
  sf::SoundBuffer frog_buffer;
  sf::Sound frog; 
  sf::SoundBuffer seagull_buffer;
  sf::Sound seagull;
  sf::SoundBuffer wolf_buffer;
  sf::Sound wolf;
  sf::SoundBuffer lose_life_buffer;
  sf::Sound lose_life;
  sf::SoundBuffer thunderclap_buffer;
  sf::Sound thunderclap;
  sf::SoundBuffer declined_buffer;
  sf::Sound declined;

  std::vector<sf::SoundBuffer> soundBuffers;
  std::vector<sf::Sound> sounds;

  int player_lives = 3;
  int passports_approved = 0;
  int passports_approved_illegally = 0;
  int current_day = 1;
  int animal_index;
  int passport_index;
  

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
  bool time_up = false;
  bool is_dead = false;
  bool game_over = false;
  bool timer_active = true;
  bool show_timer = true;
  bool show_overlay = false;

  
  

  void initialiseMenuFonts();
  void initialiseMenu();
  void toggleMenuSelection();
  void handleMenuSelection();
  void drawFloodGauge();
  void initialiseAnimals();
  void initialisePassports();
  void newAnimal();
  void initialiseSprites();
  void drawSprites();
  void dragSprite(sf::Sprite* sprite);
  void initialiseButtons();
  void initialiseStamps();
  void drawButtons();
  void drawStamps();
  void drawPlayerLives();
  void initialiseFloodGauge();
  void floodTimer(float dt);
  void passportApprovedText();
  void passportDeniedText();
  void rejectedValidPassportText();
  void passportDidNotMatchText();
  void drawNoLivesText();
  void checkPlayerDead();
  void drawMenu();
  void drawWorld();
  void initialisePlayerLives();
  void handlePassportTextChoice();
  void initialiseMainGameFont();
  void restartGame();
  void drawFloodHasRisenText();
  void initialisePlayAgainFont();
  void initialiseGameScreen();
  void initialiseGameTimer();
  void gameTimer();
  void startNewDay();
  void drawEndOfDay();
  void initialiseOverlay();
  void initialiseEndOfDayFont();
  void updateEndofDayText();
  void updateCurrentDayText();
  void initialiseCurrentDayText();
  void playBackgroundSound();
  void playAnimalSounds();



};

#endif // PLATFORMER_GAME_H
