#pragma once
#include "blocs.h"


void score(int& soretotal, sf::RenderWindow& ventana);
void GameOver(sf::RenderWindow& ventana, bool& gameOver, sf::Vector2f& posicioPilota, float& velocitatX, float& velocitatY, std::vector<std::vector<Bloc>>& blocs, int& scoretotal, const int max_X, const int max_Y);