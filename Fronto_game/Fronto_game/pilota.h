#pragma once
#include <SFML/Graphics.hpp>
#include "blocs.h"

// Declaracio de la funcio pilota

void pilota(sf::RenderWindow& finestra, sf::Vector2f& posicio, float radi, float& velocitatX, float& velocitatY, const int max_X, const int max_Y, sf::Vector2f posicioBarra, std::vector<std::vector<Bloc>>& blocs, float altBarra, float longitutBarra, bool& gameOver);
