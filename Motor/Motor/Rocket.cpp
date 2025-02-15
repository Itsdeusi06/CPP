#include "Rocket.h"

Rocket::Rocket() {

}

Rocket::~Rocket() {

}

void Rocket::init(std::string textureName, sf::Vector2f position, float speed, sf::RenderWindow& window) {
    // Initialize basic attributes
    m_position = position;
    m_speed = speed;

    // Load the texture for the rocket
    m_texture.loadFromFile(textureName.c_str());

    // Create Sprite and Attach the Texture
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(m_position);
    m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);

    // Get the size of the window
    sf::Vector2u windowSize = window.getSize();

    // Get the size of the rocket texture
    sf::Vector2u textureSize = m_texture.getSize();

    // Calculate the scale factor for both X and Y
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    // Choose the smaller scale factor to maintain the aspect ratio
    float scale = std::min(scaleX, scaleY);

    // Optional: Apply a manual scaling factor to control the rocket size
    float manualScale = 0.1f;  // Adjust this as necessary for your game
    scale *= manualScale;

    // Apply the calculated scale to the rocket sprite
    m_sprite.setScale(scale, scale);
}


sf::Sprite Rocket::getSprite() {
	return m_sprite;
}

void Rocket::update(float dt, sf::Vector2f position) {
	m_sprite.move(m_speed * dt, 0);
}