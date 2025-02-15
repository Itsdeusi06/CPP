#include "Talp.h" 
Talp::Talp() {

}

Talp::~Talp() {

}

void Talp::init(std::string textureName, sf::Vector2f position, float speed, sf::RenderWindow& window) {
    m_position = position;
    m_speed = speed;

    // Load the texture for the Talp
    m_texture.loadFromFile(textureName.c_str());

    // Create Sprite and Attach the Texture
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(m_position);
    m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);

    // Get the size of the window
    sf::Vector2u windowSize = window.getSize();

    // Get the size of the Talp texture
    sf::Vector2u textureSize = m_texture.getSize();

    // Calculate the scale factor for both X and Y based on window size and texture size
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    // Choose the smaller scale to maintain the aspect ratio (prevents distortion)
    float scale = std::min(scaleX, scaleY);

    // Optional: Apply a manual scaling factor to control the Talp size
    float manualScale = 0.2f;  // Adjust this as necessary for your game
    scale *= manualScale;

    // Apply the calculated scale to the sprite
    m_sprite.setScale(scale, scale);
}



void Talp::update(float dt) {
	m_position.y += m_speed * dt;
	m_sprite.setPosition(m_position);

}

sf::Sprite Talp::getSprite() { return m_sprite; }