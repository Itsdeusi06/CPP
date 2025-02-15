#include "Hero.h"

Hero::Hero() {
	
}

Hero::~Hero() {

}

void Hero::init(std::string textureName, sf::Vector2f position, float mass, sf::RenderWindow& window, sf::Color color) {
	// Initialize basic attributes
	m_position = position;
	m_mass = mass;
	m_grounded = false;

	// Load textures for the hero in different states
	m_textureStand.loadFromFile(textureName.c_str());
	m_textureJump.loadFromFile("./Assets/Asset/saltant.png");
	m_textureCrouch.loadFromFile("./Assets/Asset/ajupit.png");

	// Create Sprite and set initial texture
	m_sprite.setTexture(m_textureStand);
	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(m_textureStand.getSize().x / 2, m_textureStand.getSize().y / 2);

	// Get window size
	sf::Vector2u windowSize = window.getSize();

	// Get the texture size of the hero's standing texture
	sf::Vector2u textureSize = m_textureStand.getSize();

	// Calculate the scale factor for both X and Y based on window size
	float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
	float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

	// Choose the smaller scale factor to maintain the aspect ratio (prevents distortion)
	float scale = std::min(scaleX, scaleY);

	// Optional manual scale factor for more control over sprite size (you can adjust this)
	float manualScale = 0.3f;  // Scaling to 30% of the calculated size
	scale *= manualScale;

	// Apply the calculated scale to the sprite
	m_sprite.setScale(scale, scale);

	// Optionally set color for the sprite
	m_sprite.setColor(color);
}

void Hero::update(float dt, sf::Vector2f viewSize) {
	// Apply gravity correctly
	m_velocityJump += m_mass * m_gravity * dt;

	// Update position based on velocity
	m_position.y += m_velocityJump * dt;
	m_position.x += m_velocityAD * dt;

	m_sprite.setPosition(m_position);
	float groundLevel = viewSize.y * 0.75f; // Adjust this for better feel
	if (m_position.y >= groundLevel) {
		m_position.y = groundLevel;
		m_velocityJump = 0;
		// Check if just landed
		if (!m_grounded) {
			useFirstTexture = true;  // Reset to standing texture
			m_sprite.setTexture(m_textureStand);
			animationTimer = 0;  // Reset animation timer
		}
		m_grounded = true;
		jumpCount = 0;

	} else {
        m_grounded = false; // Character is in the air
    }

	if (m_grounded) {
		// Timer for switching between standing and crouching
		animationTimer += dt;
		if (animationTimer >= switchTime) {
			animationTimer = 0; // Reset timer
			useFirstTexture = !useFirstTexture; // Toggle texture

			if (useFirstTexture)
				m_sprite.setTexture(m_textureStand);
			else {

				m_sprite.setTexture(m_textureCrouch);
			}
		}
	}
	else {
		// If in the air, use the jump texture
		m_sprite.setTexture(m_textureJump);
	}
	// Set max positon for x to don't go off the screen
	if (m_position.x >= viewSize.x)
	{
		m_position.x = viewSize.x;
	}
	if (m_position.x <= 0)
	{
		m_position.x = 0;
	}
}

void Hero::jump(float velocity) {
	if (jumpCount < 2) {
		jumpCount++;
		m_velocityJump = -velocity;
		m_grounded = false;
	}
}

sf::Sprite Hero::getSprite() { return m_sprite; }

void Hero::ADmovement(float velocity) {
	m_velocityAD = velocity;
}

void Hero::setPossiton(sf::Vector2f position) {
	m_position = position;
}