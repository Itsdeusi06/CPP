#pragma once
#include <SFML/Graphics.hpp>
class Rocket
{
public:
	Rocket();
	~Rocket();
	void init(std::string textureName, sf::Vector2f position, float _speed, sf::RenderWindow& window);
	void update(float dt, sf::Vector2f position);
	sf::Sprite getSprite();
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
	float m_speed;
}; 