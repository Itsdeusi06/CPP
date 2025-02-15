#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <vector>
#include "Hero.h"
#include "Enemy.h"
#include "Rocket.h"
#include "Talp.h"
#include "ScoreManager.h"



class Engine {
	private:
		//create variable for the widnow of the game
		sf::Vector2f viewSize;
		sf::VideoMode vm;
		sf::RenderWindow window;
		//variable to save the bg
		//sky
		sf::Texture skyTexture;
		sf::Sprite skySprite;
		//variable to save the size of the image and the window
		sf::Vector2u TextureSize; 
		sf::Vector2u WindowSize;
		//bg
		sf::Texture bgTexture;
		sf::Sprite bgSprite;
		// Text
		sf::Font headingFont;
		sf::Text headingText;
		sf::Text tutorialText;
		sf::Font scoreFont;
		sf::Text scoreText;
		sf::Text gameOverText;
		// Audio
		std::vector<sf::SoundBuffer> soundBuffers;
		std::vector<sf::Sound> sounds;
		//Kill sound variables
		// load the differents kill souns
		std::vector<sf::SoundBuffer> killSoundBuffers;
		std::vector<sf::Sound> killSounds; // Store Sound objects 
		int killStreak = 0; 
		sf::Clock killTimer; 
		const float killInterval = 1.0f; // 1 second 
		//variable of player 
		std::vector<Hero*> heroes;
		//variable of enemy
		std::vector<Enemy*> enemies;
		std::vector<Talp*> talps;
		//variable of rocket
		std::vector<Rocket*> rockets;
		//variable select playeres 
		sf::Font escolliJugadoFont; 
		sf::Text textJugador1, textJugador2;
		sf::RectangleShape boto1, boto2;
		//time to change animation
		float currentTime;
		float prevTime = 0.0f;
		//variable to know haw many players are there
		int numJugadors = 1;
		// texture and sprite of live
		sf::Texture livesTexture;
		sf::Sprite livesSprites[5];  // Array to hold life sprites
		// variable to manage score
		ScoreManager scoreManager;
		//variable of game.
		int score = 0;
		int lives = 5;
		bool gameover = true;
		void reset();
		void init();
		void updateInput();
		void update(float dt); 
		void draw();
		void spawnEnemy();
		void shootPlayer1();
		void shootPlayer2();
		bool checkCollision(sf::Sprite sprite1, sf::Sprite sprite2);
		void scoretext();
		int seleccioJugadors();
		void playKillSound();
		void checkAndSaveHighScore();
	public:
		// This is the constructor, called whenever a 'Game' object is created.
		// Use this to setup stuff you have to set once.
		// This should only be used for things that can't fail, to always have a defined state.
		Engine();
		// This is the destructor, called whenever a 'Game' object is destroyed.
		~Engine();
		// Load and run the game
		int run();
	
};
