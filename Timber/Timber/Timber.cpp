
// Include important C++ libraries here
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Audio.hpp>

// Make code easier to type with "using namespace"
using namespace sf;

// Left or Right
enum class side { LEFT, RIGHT, NONE };

// Function declaration
void updateBranches(int seed, side branchPositions[]);

// Const declaration
const int Xmax = 1920;
const int Ymax = 1080;
const int NumMaxCloudsBee = 3;
const int NUM_BRANCHES = 6;

// Create a structure variable for the Cloud and the Bee
struct CloudBeesStructure {
	sf::Sprite dibuixCloud;
	sf::Sprite dibuixBee;
	bool  ActiveCloud;
	float SpeedCloud;
	bool  ActiveBee;
	float SpeedBee;
};

// Create variables for the sprite and the position
Sprite branches[NUM_BRANCHES]; 
side branchPositions[NUM_BRANCHES]; 

// Line the axe up with the tree – Cal posar-ho fora de la funció main
const float AXE_POSITION_LEFT = 850;
const float AXE_POSITION_RIGHT = 1075;

int main()
{
	// Create a video mode object
	VideoMode vm(Xmax, Ymax);

	// Create and open a window for the game
	RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

	// Set the frame rate
	window.setFramerateLimit(100);

	// Prepere the Background
	Texture textureBackground;
	textureBackground.loadFromFile("assets/graphics/newAssets/ChatGPTfonsB.png");
	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);

	// Prepare the tree
	Texture textureTree;
	textureTree.loadFromFile("assets/graphics/newAssets/arbre1.1.png");
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(830, 0);

	// Prepare the bee and the cloud
	Texture textureBee; 
	textureBee.loadFromFile("assets/graphics/newAssets/bee1.png");
	Texture textureCloud;
	textureCloud.loadFromFile("assets/graphics/newAssets/Nube.png");
	CloudBeesStructure spriteCloudBee[NumMaxCloudsBee];
	for (int i = 0; i < NumMaxCloudsBee; i++)
	{
		spriteCloudBee[i].dibuixCloud.setTexture(textureCloud);
		spriteCloudBee[i].dibuixCloud.setPosition(0, i * 250);
		spriteCloudBee[i].dibuixCloud.setScale(6, 6);
		spriteCloudBee[i].dibuixBee.setTexture(textureBee);
		spriteCloudBee[i].dibuixBee.setPosition(2000, 900);
		spriteCloudBee[i].dibuixBee.setScale(2, 2);
		spriteCloudBee[i].ActiveCloud = false;
		spriteCloudBee[i].SpeedCloud = 0.0f;
		spriteCloudBee[i].ActiveBee = false;
		spriteCloudBee[i].SpeedBee = 0.0f;
	}

	// Variables to control time itself
	Clock clock;
	Clock fpsClock;

	// Time bar
	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);
	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

	// Track whether the game is running
	bool paused = true;

	// Prepere the text
	int score = 0;
	int fpsContador = 0;
	Text messageText;
	Text scoreText;
	Text fpsText;

	// Prepere the font
	Font font;
	Font font2;
	font.loadFromFile("assets/fonts/KOMIKAP_.ttf");
	font2.loadFromFile("assets/fonts/04B_11__.ttf");

	// Prepere the message
	messageText.setFont(font);
	scoreText.setFont(font);
	fpsText.setFont(font2);
	messageText.setString("Press Enter To Start!");
	scoreText.setString("Score = 0");
	fpsText.setString("0 FPS");
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);
	fpsText.setCharacterSize(40);
	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);
	fpsText.setFillColor(Color::White);

	// Prepere Text position 
	FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left +
	textRect.width / 2.0f,
	textRect.top +
	textRect.height / 2.0f);
	messageText.setPosition(Xmax / 2.0f, Ymax / 2.0f);
	scoreText.setPosition(20, 20);
	fpsText.setPosition(1700, 20);

	// Prepare the texture branches
	Texture textureBranch;
	textureBranch.loadFromFile("assets/graphics/branch.png");
	
	// Bucle for 6 branches
	for (int i = 0; i < NUM_BRANCHES; i++) {
		branches[i].setTexture(textureBranch); 
		branches[i].setPosition(-2000, -2000);
		branches[i].setOrigin(220, 20); 
	}

	// Prepare the player
	Texture texturePlayer;
	texturePlayer.loadFromFile("assets/graphics/newAssets/playerSanta.png");
	Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setPosition(580, 720);
	spritePlayer.setScale(0.8f, 0.8f);

	// The player starts on the left
	side playerSide = side::LEFT;
	branchPositions[3] = side::NONE;
	
	// Prepare the gravestone
	Texture textureGravestone;
	textureGravestone.loadFromFile("assets/graphics/newAssets/tumba.png");
	Sprite spriteGravestone;
	spriteGravestone.setTexture(textureGravestone);
	spriteGravestone.setPosition(-580, -820);
	
	// Prepare the axe
	Texture textureAxe;
	textureAxe.loadFromFile("assets/graphics/newAssets/Hacha.png");
	Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(11750, 825);
	spriteAxe.setScale(2.5f,2.5f);
	spriteAxe.setOrigin(40, 20);
	
	// Prepare the flying log
	Texture textureLog;
	textureLog.loadFromFile("assets/graphics/newAssets/arbre2.png");
	Sprite spriteLog;
	spriteLog.setTexture(textureLog);
	spriteLog.setPosition(-700, -825);
	spriteLog.setScale(0.4f, 0.3f);

	// Variables for the log
	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500;
	
	// Control the player input
	bool acceptInput = false;
	
	// The player chopping sound
	SoundBuffer chopBuffer;
	chopBuffer.loadFromFile("assets/sound/NewSound/chopNewSound.wav");
	Sound chop;
	chop.setBuffer(chopBuffer);
	
	// Out of time sound
	SoundBuffer outTimeBuffer;
	outTimeBuffer.loadFromFile("assets/sound/NewSound/out-of-time.wav");
	Sound outTime;
	outTime.setBuffer(outTimeBuffer);
	
	// Death sound
	SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("assets/sound/NewSound/dead.wav");
	Sound death;
	death.setBuffer(deathBuffer);
	
	// Random seed
	srand((int)time(0) * 10);
	
	// Call the funtcions
	updateBranches(1, branchPositions);
	updateBranches(2, branchPositions);
	updateBranches(3, branchPositions);
	updateBranches(4, branchPositions);
	updateBranches(5, branchPositions);

	
	// Game loop
	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased && !paused)
			{
				// Listen for key presses again
				acceptInput = true;
				// hide the axe
				spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
			}
		}
		// ESC pressed close
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Start the game
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			paused = false;
			// Reset the time and the score
			score = 0;
			timeRemaining = 6;
			// Make all the branches disappear
			for (int i = 1; i < NUM_BRANCHES; i++)
			{
				branchPositions[i] = side::NONE;
			}
			// Make sure the gravestone is hidden
			spriteGravestone.setPosition(675, 2000);
			// Move the player into position
			spritePlayer.setPosition(580, 720);
			acceptInput = true;
		
		}

		// Wrap the player controls to make sure we are accepting input
		if (acceptInput)
		{	
		// First handle pressing the right cursor key
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				// Make sure the player is on the right
				playerSide = side::RIGHT;
				score++;
				
				// Add to the amount of time remaining
				timeRemaining += (2 / score) + .15;
				spriteAxe.setPosition(AXE_POSITION_RIGHT,
					spriteAxe.getPosition().y);
				spriteAxe.setRotation(0);
				spritePlayer.setPosition(1100, 720);
				
				// update the branches
				updateBranches(score, branchPositions);
				
				// Set the log flying to the left
				spriteLog.setPosition(810, 720);
				logSpeedX = -5000;
				logActive = true;
				acceptInput = false;
				
				// Play a chop sound
				chop.play();
				
				// Update the score text
				std::stringstream ss;
				ss << "Score = " << score;
				scoreText.setString(ss.str());
			}
		// Second handle pressing the left cursor key
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				// Make sure the player is on the left
				playerSide = side::LEFT;
				score++;
				
				// Add to the amount of time remaining
				timeRemaining += (2 / score) + .15;
				spriteAxe.setPosition(AXE_POSITION_LEFT,
					spriteAxe.getPosition().y);
				spriteAxe.setRotation(180);
				spritePlayer.setPosition(620, 720);
				
				// update the branches
				updateBranches(score, branchPositions);
				
				// Set the log flying to the left
				spriteLog.setPosition(810, 720);
				logSpeedX = +5000;
				logActive = true;
				acceptInput = false;
				
				// Play a chop sound
				chop.play();
				
				// Update the score text
				std::stringstream ss;
				ss << "Score = " << score;
				scoreText.setString(ss.str());
			}
		}
		
		/*
		****************************************
		Update the scene
		****************************************
		*/
		
		// Measure time
		Time dt;
		if (!paused)
		{	
			
			Time dt = clock.restart();

			// FPS calculation every 100 frames
			fpsContador++;  // Increment frame counter
			if (fpsContador >= 100) {
				int fps = fpsContador / fpsClock.restart().asSeconds(); // Calculate FPS
				std::stringstream fpsT;
				fpsT << fps << " FPS";
				fpsText.setString(fpsT.str());  // Update the FPS display text
				fpsContador = 0;  // Reset the frame counter
			}
			
		// Subtract from the amount of time remaining
			timeRemaining -= dt.asSeconds(); 
		// Size up the time bar
			timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));
			if (timeRemaining <= 0.0f) {
				// Pause the game
				paused = true;
				// Change the message shown to the player
				messageText.setString("Out of time!!");
				// Reposition the text based on its new size
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left + textRect.width / 2.0f,
					textRect.top + textRect.height / 2.0f);
				messageText.setPosition(Xmax / 2.0f, Ymax / 2.0f);
				// Play the out of time sound
				outTime.play();
			}
		
		// Manage the clouds and bees
		for (int i = 0; i < NumMaxCloudsBee; i++)
		{
			// Update the Clouds
			if (!spriteCloudBee[i].ActiveCloud)
			{
				spriteCloudBee[i].SpeedCloud = (rand() % 200);
				spriteCloudBee[i].dibuixCloud.setPosition(-200, (rand() % 500));
				spriteCloudBee[i].ActiveCloud = true;
			}
			else
			{
				spriteCloudBee[i].dibuixCloud.setPosition(spriteCloudBee[i].dibuixCloud.getPosition().x + (spriteCloudBee[i].SpeedCloud * dt.asSeconds()),
					spriteCloudBee[i].dibuixCloud.getPosition().y);
				if (spriteCloudBee[i].dibuixCloud.getPosition().x > Xmax)
				{
					spriteCloudBee[i].ActiveCloud = false;
				}
			}
			// Update the Bees
			if (!spriteCloudBee[i].ActiveBee)
			{
				spriteCloudBee[i].SpeedBee = (rand() % 200) - 400;
				spriteCloudBee[i].dibuixBee.setPosition(2000, (rand() % 400) + 400);
				spriteCloudBee[i].ActiveBee = true;
			}
			else
			{
				spriteCloudBee[i].dibuixBee.setPosition(spriteCloudBee[i].dibuixBee.getPosition().x + (spriteCloudBee[i].SpeedBee * dt.asSeconds()),
					spriteCloudBee[i].dibuixBee.getPosition().y);
				if (spriteCloudBee[i].dibuixBee.getPosition().x < -100)
				{
					spriteCloudBee[i].ActiveBee = false;
				}
			}
		}

		// update the branch sprites 
		for (int i = 0; i < NUM_BRANCHES; i++)
		{
			float height = i * 150; 
			if (branchPositions[i] == side::LEFT)
			{
				// Move the sprite to the left side
				branches[i].setPosition(610, height); 
				// Flip the sprite round the other way
				branches[i].setRotation(180); 
			}
			else if (branchPositions[i] == side::RIGHT) 
			{
				// Move the sprite to the right side
				branches[i].setPosition(1330, height); 
				// Set the sprite rotation to normal
				branches[i].setRotation(0); 
			}
			else
			{
				// Hide the branch
				branches[i].setPosition(3000, height); 
			}
		}

		// Handle a flying log				
		if (logActive) {
			spriteLog.setPosition(
				spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()),
				spriteLog.getPosition().y + (logSpeedY * dt.asSeconds())
			);

			// Has the insect reached the right hand edge of the screen?
			if (spriteLog.getPosition().x < -100 || spriteLog.getPosition().x > 2000)
			{
				// Set it up ready to be a whole new cloud next frame
				logActive = false;
				spriteLog.setPosition(810, 720);
			}
		}

		// has the player been squished by a branch?
		if (branchPositions[5] == playerSide)
		{
			// death
			paused = true;
			acceptInput = false;
			// Draw the gravestone
			spriteGravestone.setPosition(spritePlayer.getPosition());
			// hide the player
			spritePlayer.setPosition(2000, 660);
			// Change the text of the message
			messageText.setString("SQUISHED!!");
			// Center it on the screen
			FloatRect textRect = messageText.getLocalBounds();
			messageText.setOrigin(textRect.left + textRect.width / 2.0f,
				textRect.top + textRect.height / 2.0f);
			messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
			// Play the death sound
			death.play();
		}

	}

	 /*
	 ****************************************
	 Draw the scene
	 ****************************************
	 */

	 // Clear everything from the last frame
		window.clear();

		// Draw our game scene here
		window.draw(spriteBackground);

		// Draw the clouds and the bees
		for (int i = 0; i < NumMaxCloudsBee; i++)
		{
			window.draw(spriteCloudBee[i].dibuixCloud);
			window.draw(spriteCloudBee[i].dibuixBee);
		}


		// Draw the branches
		for (int i = 0; i < NUM_BRANCHES; i++) { 
			window.draw(branches[i]);
		}


		// Draraw the flying log
		window.draw(spriteLog);

		// Draw the tree
		window.draw(spriteTree);

		// Draw the player
		window.draw(spritePlayer);

		// Draw the axe
		if (!paused) {
			window.draw(spriteAxe);
		}
		
		// Draw the gravestone
		if (paused) {
			window.draw(spriteGravestone);
		}

		// Draw the score
		window.draw(scoreText);
		
		// Draw the fps
		window.draw(fpsText);
		if (paused)
		{
			// Draw our message
			window.draw(messageText);
		}

		// Draw the timebar
		window.draw(timeBar);

		// Show everything we just drew
		window.display();
	}

	return 0;
}

// Function definition
void updateBranches(int seed, side branchPositions[])
{
	// Move all the branches down one place
	for (int j = NUM_BRANCHES - 1; j > 0; j--) {
		branchPositions[j] = branchPositions[j - 1];
	}
	// Spawn a new branch at position 0
		// LEFT, RIGHT or NONE
	srand((int)time(0) + seed);
	int r = (rand() % 5);
	switch (r) {
	case 0:
		branchPositions[0] = side::LEFT;
		break;
	case 1:
		branchPositions[0] = side::RIGHT;
		break;
	default:
		branchPositions[0] = side::NONE;
		break;
	}
}


