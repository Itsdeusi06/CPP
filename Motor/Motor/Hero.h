#pragma once
#include "SFML\Graphics.hpp"

class Hero
{
public:
	Hero();
	~Hero();
	void init(std::string textureName, sf::Vector2f position, float mass, sf::RenderWindow& window, sf::Color color);
	void update(float dt, sf::Vector2f viewSize);
	void jump(float velocity);
	void ADmovement(float velocity);
	sf::Sprite getSprite();
	void setPossiton(sf::Vector2f position);
private:
	sf::Texture m_textureStand;
	sf::Texture m_textureJump;
	sf::Texture m_textureCrouch;
	sf::Sprite m_sprite; 
	sf::Vector2f m_position;
	float animationTimer = 0.0f; // Time tracker
	float switchTime = 0.5f; // Change sprite every 0.5 seconds (adjust as needed)
	bool useFirstTexture = true;
	int jumpCount = 0;
	float m_mass;
	float m_velocityJump=0;
	float m_velocityAD=0;
	float m_force;
	const float m_gravity = 9.80f;
	bool m_grounded;
};

