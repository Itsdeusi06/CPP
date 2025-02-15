#include "Engine.h"
#include <iostream>

// This is the constructor, called whenever a 'Game' object is init.
Engine::Engine() : scoreManager("./highscore.txt") {
	// Get the screen resolution and create an SFML window and View
	//sizes of the window
	viewSize.y = sf::VideoMode::getDesktopMode().height / 2; 
	viewSize.x = sf::VideoMode::getDesktopMode().width / 2; 
	//creat the window
	window.create(sf::VideoMode(viewSize.x, viewSize.y),
		"Joc heroi - enemic",
		sf::Style::Default);
	window.setFramerateLimit(30);
}
// This is the destructor, called whenever a 'Game' object is destroyed.
Engine::~Engine() {
}

// Load and run the game
int Engine::run() {
	sf::Clock clock;
	// call the funcion to know how many plyers are playing 1 - 2
	numJugadors = seleccioJugadors();
	// call this to iniciate the game
	init();
	// while is open we handle the user inputs and we draw it
	while (window.isOpen()) {
		updateInput();
		sf::Time dt = clock.restart();
		if (!gameover) {
			update(dt.asSeconds());
			scoretext();
		}
		draw();
	}
	return 0;
}

void Engine::init() {
	
	//load the sky images
	skyTexture.loadFromFile("./Assets/Bg/cel.jpg");
	
	//Get size of texture Sky.
	TextureSize = skyTexture.getSize(); 
	
	//Get size of window.
	WindowSize = window.getSize();             
	
	//Calculate scale.
	float skyScaleX = (float)viewSize.x / TextureSize.x;
	float skyScaleY = (float)viewSize.y / TextureSize.y;     
	skySprite.setTexture(skyTexture);
	
	//Set scale.
	skySprite.setScale(skyScaleX, skyScaleY);      
	
	//load the bg images
	bgTexture.loadFromFile("./Assets/Bg/bg.png");
	
	//Get size of texture BackGround.
	TextureSize = bgTexture.getSize();             
	
	//Calculate scale.
	float bgScaleX = (float)viewSize.x / TextureSize.x;
	float bgScaleY = (float)viewSize.y / TextureSize.y;     
	bgSprite.setTexture(bgTexture);
	
	//Set scale.
	bgSprite.setScale(bgScaleX, bgScaleY);
	
	// Load font
	headingFont.loadFromFile("./Assets/Font/KOMIKAP_.ttf");
	scoreFont.loadFromFile("./Assets/Font/04B_11__.ttf");
	
	// Set Heading Text
	// Scale based on width if necessary (80% of the screen width)
	float maxWidth = viewSize.x * 0.8f; 
	headingText.setFont(headingFont);
	headingText.setString("Tiny Bazooka");
	headingText.setFillColor(sf::Color::Green);
	
	// Get the current width of the heading text
	sf::FloatRect headingBounds = headingText.getLocalBounds();
	float headingTextWidth = headingBounds.width;
	
	// Calculate scale factor based on width (to ensure text doesn't overflow)
	float scaleFactorWidth = maxWidth / headingTextWidth;
	headingText.setCharacterSize(static_cast<unsigned int>(headingText.getCharacterSize() * scaleFactorWidth));
	
	// Adjust the origin and position to center it
	headingBounds = headingText.getLocalBounds();
	headingText.setOrigin(headingBounds.width / 2, headingBounds.height / 2);
	headingText.setPosition(sf::Vector2f(viewSize.x * 0.5f, viewSize.y * 0.10f));
	
	// Set Score Text
	// Get the current width of the heading text
	sf::FloatRect scoreBounds = scoreText.getLocalBounds();
	float scoreTextWidth = scoreBounds.width;

	// Calculate scale factor based on width (to ensure text doesn't overflow)
	scaleFactorWidth = maxWidth / scoreTextWidth;
	scoreText.setFont(scoreFont);
	scoreText.setOrigin(scoreBounds.width / 2, scoreBounds.height / 2);
	scoreText.setPosition(sf::Vector2f(viewSize.x * 0, viewSize.y * 0));
	
	// Scale based on width if necessary (80% of screen width)
	maxWidth = viewSize.x * 0.8f;  // 80% of screen width
	tutorialText.setFont(scoreFont);
	tutorialText.setString("Press Down Arrow to Fire and Start Game, Up Arrow to Jump");
	tutorialText.setFillColor(sf::Color::Green);

	// Get the bounds of the tutorial text
	sf::FloatRect bounds = tutorialText.getLocalBounds();
	float textWidth = bounds.width;

	// Calculate the scaling factor based on the text width
	scaleFactorWidth = maxWidth / textWidth;
	tutorialText.setCharacterSize(static_cast<unsigned int>(tutorialText.getCharacterSize() * scaleFactorWidth));

	// Adjust origin and position to center it
	sf::FloatRect tutorialBounds = tutorialText.getLocalBounds();
	tutorialText.setOrigin(tutorialBounds.width / 2, tutorialBounds.height / 2);
	tutorialText.setPosition(sf::Vector2f(viewSize.x * 0.5f, viewSize.y * 0.30f));

	// Scale based on width if necessary (80% of screen width)
	maxWidth = viewSize.x * 0.8f; 
	gameOverText.setFont(scoreFont);
	gameOverText.setString("GAME OVER");
	gameOverText.setFillColor(sf::Color::Red);

	// Get the bounds of the game over text
	sf::FloatRect gameOverBounds = gameOverText.getLocalBounds();
	float gameOverTextWidth = gameOverBounds.width;

	// Calculate scale factor based on width
	float scaleFactorWidthGameOver = maxWidth / gameOverTextWidth;
	gameOverText.setCharacterSize(static_cast<unsigned int>(gameOverText.getCharacterSize() * scaleFactorWidthGameOver));

	// Adjust the position to center it
	gameOverBounds = gameOverText.getLocalBounds();
	gameOverText.setOrigin(gameOverBounds.width / 2, gameOverBounds.height / 2);
	gameOverText.setPosition(sf::Vector2f(viewSize.x * 2.f, viewSize.y * 2.f));  // Out of the screen
	
	// Audio
	soundBuffers.resize(3); // Three different sound buffers
	soundBuffers[0].loadFromFile("./Assets/Music/bgMusic.ogg");
	soundBuffers[1].loadFromFile("./Assets/Music/gameOverMusic.ogg");
	soundBuffers[2].loadFromFile("./Assets/Music/damageMusic.ogg");

	// Create sounds and link them to buffers
	sounds.resize(3);
	for (int i = 0; i < 3; i++) {
		sounds[i].setBuffer(soundBuffers[i]);
		sounds[i].setVolume(10);
	}
	
	// Load sound buffers
	killSoundBuffers.resize(5); // 5 different sounds for kill streaks
	killSoundBuffers[0].loadFromFile("./Assets/Music/killMusic1.ogg");
	killSoundBuffers[1].loadFromFile("./Assets/Music/killMusic2.ogg");
	killSoundBuffers[2].loadFromFile("./Assets/Music/killMusic3.ogg");
	killSoundBuffers[3].loadFromFile("./Assets/Music/killMusic4.ogg");
	killSoundBuffers[4].loadFromFile("./Assets/Music/killMusic5.ogg");

	// Create sounds and link them to buffers
	killSounds.resize(5);
	for (int i = 0; i < 5; i++) {
		killSounds[i].setBuffer(killSoundBuffers[i]);
	}

	//Inicialize the player
	Hero* Pau = new Hero(); 
	Pau->init("./Assets/Asset/dePeu.png", sf::Vector2f(viewSize.x * 0.25f, viewSize.y * 0.5f), 200, window, sf::Color::Red);
	heroes.push_back(Pau); 
	if (numJugadors == 2)
	{
		Hero* Pau1 = new Hero();
		Pau1->init("./Assets/Asset/dePeu.png", sf::Vector2f(viewSize.x * 0.25f, viewSize.y * 0.5f), 200, window, sf::Color::Blue);
		heroes.push_back(Pau1);
	}
	
	// Load the lives texture
	livesTexture.loadFromFile("./Assets/Asset/live.png");

	// Loop to create the sprites for each life
	for (int i = 0; i < lives; ++i) {
		sf::Sprite lifeSprite;
		lifeSprite.setTexture(livesTexture);

		// Set the position of each life (with an offset)
		float offsetX = 50.0f * i; // Adjust the X position for each life
		lifeSprite.setPosition(viewSize.x * 0.05f + offsetX, viewSize.y * 0.25f);

		// Set the origin to center the sprite
		lifeSprite.setOrigin(livesTexture.getSize().x / 2, livesTexture.getSize().y / 2);

		// Calculate the scale based on the window size
		sf::Vector2u windowSize = window.getSize();
		float scaleX = static_cast<float>(windowSize.x) / 1920.0f; // Dessigned for base resolution of 1920x1080
		float scaleY = static_cast<float>(windowSize.y) / 1080.0f;

		// Apply the calculated scale 
		lifeSprite.setScale(scaleX * 0.3f, scaleY * 0.3f); // Adjust the scale as needed (0.1f is a placeholder)

		// Store the sprite in the array (make sure the array is large enough)
		livesSprites[i] = lifeSprite;
	}

	//inicialitzem els nombre aleatoris.
	srand((int)time(0)); 
}

void Engine::updateInput() {
	sf::Event event;
	// while there are pending events...
		while (window.pollEvent(event)) {
		if (event.type == sf::Event::KeyPressed) { //check key pressed
			if (event.key.code == sf::Keyboard::Up) { //player jumps
				heroes[0]->jump(750.0f);
			}
			if (event.key.code == sf::Keyboard::Left) { //player go left
				heroes[0]->ADmovement(-220.f);
			}
			if (event.key.code == sf::Keyboard::Right) { //player go right
				heroes[0]->ADmovement(220.f);
			}
			if (numJugadors == 2) // check teh key for player 2 if there is
			{
				if (event.key.code == sf::Keyboard::W) { //player jumps
					heroes[1]->jump(750.f);
				}
				if (event.key.code == sf::Keyboard::A) { // player go left
					heroes[1]->ADmovement(-220.f);
				}
				if (event.key.code == sf::Keyboard::D) { // player go right
					heroes[1]->ADmovement(220.f);
				}
				if (event.key.code == sf::Keyboard::Space) { // player shoot
					shootPlayer2();
				}
			}
			
			if (event.key.code == sf::Keyboard::Enter) { // player 1 shoot
				shootPlayer1();  	
			}
			
			if (event.key.code == sf::Keyboard::Down) { //start the game
				if (gameover) {// if we are not playing then we restart the game
					gameover = false;
					reset();	
				}
			}
		}
		if (event.type == sf::Event::KeyReleased) {  // Stop movement when keys are released
			if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) {
				heroes[0]->ADmovement(0.f);
			}
		}
		if (numJugadors == 2)
		{
			if (event.type == sf::Event::KeyReleased) {  // Stop movement when keys are released
				if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D) {
					heroes[1]->ADmovement(0.f);
				}
			}
		}
		
		//to close the game
		if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed)
		window.close();		
	}
}

void Engine::update(float dt) {
	// update game  
	checkAndSaveHighScore();
	if (lives == 0)
	{
		sounds[1].play();
		gameover = true;
	}
	//upldate the position of the player
	for (int i = 0; i < heroes.size(); i++) {
		Hero* Pau = heroes[i];
		Pau->update(dt, viewSize);
	}
	
	//we add time to know the time that has pased
	currentTime += dt;
	// Spawn Enemies
	if (currentTime >= prevTime + 1.125f) {
		spawnEnemy();
		prevTime = currentTime;
	}
	// Update Enemies
	for (int i = 0; i < enemies.size(); i++) {
		Enemy* enemy = enemies[i];
		enemy->update(dt);
		if (enemy->getSprite().getPosition().x < 0) {
			enemies.erase(enemies.begin() + i);
			delete(enemy);
		}
	}
	// Update rockets
	for (int i = 0; i < rockets.size(); i++) {
		Rocket* rocket = rockets[i];
		for (int j = 0; j < heroes.size(); j++)
		{
			rocket->update(dt, heroes[j]->getSprite().getPosition()); 
				if (rocket->getSprite().getPosition().x > viewSize.x) {
					rockets.erase(rockets.begin() + i);
					delete(rocket);
				}
		}
		
	}
	// Update talp
	for (int i = 0; i < talps.size(); i++) {
		Talp* talp = talps[i];
		talp->update(dt);
		if (talp->getSprite().getPosition().y < 0) {
			talps.erase(talps.begin() + i);
			delete(talp);
		}
	}
	// Check collision between Hero and Enemies
	for (int i = 0; i < heroes.size(); i++) {
		Hero* Pau = heroes[i];
		for (int j = 0; j < enemies.size(); j++) {
			Enemy* enemy = enemies[j];
			if (checkCollision(Pau->getSprite(), enemy->getSprite())) {
				// Remove the enemy from the vector after collision
				enemies.erase(enemies.begin() + j);
				// Decrement j to avoid skipping the next enemy after removal
				j--;
				i--;
				// - 1 to lives 
				lives--;
				sounds[2].play(); 
				break; // exit the loop after a collision
			}
		}
	}
	// Check collision between Hero and Talp
	for (int i = 0; i < heroes.size(); i++) {
		Hero* Pau = heroes[i];
		for (int j = 0; j < talps.size(); j++) {
			Talp* talp = talps[j];
			if (checkCollision(Pau->getSprite(), talp->getSprite())) {
				// Remove the enemy from the vector after collision
				talps.erase(talps.begin() + j);
				// Decrement j to avoid skipping the next enemy after removal
				j--;
				i--;
				// - 1 to lives 
				lives--;
				sounds[2].play();
				break; // exit the loop after a collision
			}
		}
	}
	// Check collision between Rocket and Enemies
	for (int i = 0; i < rockets.size(); i++) {
		Rocket* rocket = rockets[i];
		for (int j = 0; j < enemies.size(); j++) {
			Enemy* enemy = enemies[j];
			if (checkCollision(rocket->getSprite(), enemy->getSprite())) {
				// Remove the enemy from the vector after collision
				enemies.erase(enemies.begin() + j);
				rockets.erase(rockets.begin() + i);
				// Decrement j to avoid skipping the next enemy after removal
				j--;
				i--;
				// Add 1 to score 
				score++;
				playKillSound();
				break; // exit the loop after a collision
			}
		}
	}
	// Check collision between Rocket and talp
	for (int i = 0; i < rockets.size(); i++) {
		Rocket* rocket = rockets[i];
		for (int j = 0; j < talps.size(); j++) {
			Talp* talp = talps[j];
			if (checkCollision(rocket->getSprite(), talp->getSprite())) {
				// Remove the enemy from the vector after collision
				talps.erase(talps.begin() + j);
				rockets.erase(rockets.begin() + i);
				// Decrement j to avoid skipping the next enemy after removal
				j--;
				i--;
				// Add 1 to score 
				score++;
				playKillSound();
				break; // exit the loop after a collision
			}
		}
	}
	// Update score
	scoretext();
}

void Engine::draw() {
	//show teh text depending if we are playing or not
	if (gameover) {
		window.clear();
		window.draw(skySprite);
		window.draw(bgSprite);
		window.draw(headingText);
		window.draw(tutorialText);
		window.draw(gameOverText);
	}
	else {
		// clear the window
		window.clear(sf::Color::Red);
		// draw the elements
		window.draw(skySprite);
		window.draw(bgSprite);
		window.draw(scoreText); 
		for (Hero* Pau : heroes)
		{
			window.draw(Pau->getSprite());
		}
		for (Enemy* enemy : enemies) {
			window.draw(enemy->getSprite());
		}
		for (Rocket* rocket : rockets)
		{
			window.draw(rocket->getSprite());
		}
		for (Talp* talp : talps)
		{
			window.draw(talp->getSprite());
		}
		// draw all the lives
		for (int i = 0; i < lives; ++i) {
			window.draw(livesSprites[i]);
		}
	}
	window.display();
}

void Engine::reset() {
	// restart all the variables to restart the game
	score = 0;
	lives = 5;
	currentTime = 0.0f;
	prevTime = 0.0;
	scoreText.setString("Score: 0");
	// Play background music
	sounds[0].play();
	for (Enemy* enemy : enemies) {
		delete(enemy);
	}
	for (Rocket* rocket : rockets) {
		delete(rocket);
	}
	for (Talp* talp : talps) {
		delete(talp);
	}
	for (Hero* Pau : heroes) 
	{
		Pau->setPossiton(sf::Vector2f(viewSize.x * 0.25f, viewSize.y * 0.5f)); 
	}
	gameOverText.setPosition(sf::Vector2f(viewSize.x * 0.5f, viewSize.y * 0.5f)); // Center when it resets the game

	enemies.clear();
	rockets.clear();
	talps.clear();

	
}

void Engine::spawnEnemy() {
	// random number to enter later in the switch and get differents positions to spawn and speeds
	int randLocEnemy = rand() % 3;
	int randLocTalp = rand() % 3;
	sf::Vector2f enemyPos;
	sf::Vector2f talpPos;
	float speedEnemy;
	float speedTalp;
	switch (randLocEnemy) {
	case 0: enemyPos = sf::Vector2f(viewSize.x, viewSize.y * 0.75f);
		speedEnemy = -400;
		break;
	case 1: enemyPos = sf::Vector2f(viewSize.x, viewSize.y * 0.60f);
		speedEnemy = -550;
		break;
	case 2: enemyPos = sf::Vector2f(viewSize.x, viewSize.y * 0.40f);
		speedEnemy = -650;
		break;
	default: printf("incorrect y value \n");
		break;
	}
	switch (randLocTalp) {
	case 0: talpPos = sf::Vector2f(viewSize.x * 0.75f, viewSize.y);
		speedTalp = -200;
		break;
	case 1: talpPos = sf::Vector2f(viewSize.x * 0.60f, viewSize.y);
		speedTalp = -350;
		break;
	case 2: talpPos = sf::Vector2f(viewSize.x * 0.40f, viewSize.y);
		speedTalp = -450;
		break;
	default: printf("incorrect y value \n");
		break;
	}

	// spawn enemies
	Enemy* enemy = new Enemy();
	enemy->init("./Assets/Asset/enemic.png", enemyPos, speedEnemy, window);
	enemies.push_back(enemy);

	// spawn talps
	Talp* talp = new Talp();
	talp->init("./Assets/Asset/Talp.png", talpPos, speedTalp, window);
	talps.push_back(talp);
}

void Engine::shootPlayer1() {
	// spqwn rockets for plaer 1
	Rocket* rocket = new Rocket();
	float velocitat = 500.0f;
	rocket->init("./Assets/Asset/fireball.png", heroes[0]->getSprite().getPosition(), velocitat, window);
	rockets.push_back(rocket); 
}

void Engine::shootPlayer2() {
	// spawn rockets for palyer 2
	Rocket* rocket = new Rocket();
	float velocitat = 500.0f;
	rocket->init("./Assets/Asset/fireball.png", heroes[1]->getSprite().getPosition(), velocitat, window);
	rockets.push_back(rocket);
}

// function to check colision between sprite 1 and 2
bool Engine::checkCollision(sf::Sprite sprite1, sf::Sprite sprite2) {
	sf::FloatRect shape1 = sprite1.getGlobalBounds();
	sf::FloatRect shape2 = sprite2.getGlobalBounds();
	if (shape1.intersects(shape2)) {
		return true;
	}
	else {
		return false;
	}
}

void Engine::scoretext() {
	// Update the score text
	scoreText.setString("Score: " + std::to_string(score) +
		"\nHigh Score: " + std::to_string(scoreManager.loadScore()));
}

int Engine::seleccioJugadors() {
	//create the text and buttosn for the selector
	escolliJugadoFont.loadFromFile("./Assets/Font/KOMIKAP_.ttf");
	
	boto1.setSize(sf::Vector2f(300, 50));
	boto1.setPosition(sf::Vector2f(viewSize.x * 0.5f, viewSize.y * 0.45f));
	boto1.setOrigin(boto1.getSize().x / 2, boto1.getSize().y / 2);
	boto1.setFillColor(sf::Color::Red);
	boto1.setOutlineColor(sf::Color::White);
	boto1.setOutlineThickness(2);

	boto2.setSize(sf::Vector2f(300, 50));
	boto2.setPosition(sf::Vector2f(viewSize.x * 0.5f, viewSize.y * 0.55f));
	boto2.setOrigin(boto2.getSize().x / 2, boto2.getSize().y / 2);
	boto2.setFillColor(sf::Color::Blue);
	boto2.setOutlineColor(sf::Color::White);
	boto2.setOutlineThickness(2);

	textJugador1.setFont(escolliJugadoFont);
	textJugador1.setString("1 Jugador");
	textJugador1.setCharacterSize(40);
	textJugador1.setPosition(sf::Vector2f(viewSize.x * 0.5f, viewSize.y * 0.45f));
	textJugador1.setOrigin(boto1.getSize().x / 2, boto1.getSize().y / 2);

	textJugador2.setFont(escolliJugadoFont);
	textJugador2.setString("2 Jugador");
	textJugador2.setCharacterSize(40);
	textJugador2.setPosition(sf::Vector2f(viewSize.x * 0.5f, viewSize.y * 0.55f));
	textJugador2.setOrigin(boto2.getSize().x / 2, boto2.getSize().y / 2);

	// draw in the widnow i show the options
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			// Detect if the mouse button is presed and in which button is presed
			if (event.type == sf::Event::MouseButtonPressed) {
				if (boto1.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
					return 1;
				}
				else if (boto2.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
					return 2;
				}
			}

			// Detect key 
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Num1) {
					return 1;
				}
				else if (event.key.code == sf::Keyboard::Num2) {
					return 2;
				}
			}
		}

		// draw the window
		window.clear();
		window.draw(boto1);
		window.draw(boto2);
		window.draw(textJugador1);
		window.draw(textJugador2);
		window.display();
	}

}


// Play sound based on streak
void Engine::playKillSound() {
	// Get the time difference since last kill
	float timeSinceLastKill = killTimer.getElapsedTime().asSeconds();

	// If the time between kills is more than 1 second, reset kill streak
	if (timeSinceLastKill > killInterval) {
		killStreak = 0;  // Reset streak if gap is more than 1 second
	}
	else {
		killStreak++; // Increase streak if within 1 second
	}

	// Determine the sound index 0,1,2,3,4 there are 5
	int index = killStreak; 
	if (index >= 4) {
		index = 4;  // After 5 kills, stay at sound 5
	}

	// Play the sound corresponding to the streak
	killSounds[index].setVolume(10);
	killSounds[index].play();

	// Reset the timer for the next kill
	killTimer.restart();

}

void Engine::checkAndSaveHighScore() { 
	int highScore = scoreManager.loadScore(); // Get the current high score
	if (score > highScore) {
		// If the current score is better, save it
		scoreManager.saveScore(score);
	}
}
