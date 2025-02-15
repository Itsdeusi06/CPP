#pragma once
#include "blocs.h"

// Declaracio de les funcions
void score(int& soretotal, sf::RenderWindow& ventana);
void GameOver(sf::RenderWindow& ventana, bool& gameOver, sf::Vector2f& posicioPilota, float& velocitatX, float& velocitatY, std::vector<std::vector<Bloc>>& blocs, int& scoretotal, const int max_X, const int max_Y);
void victoriaMostrar(sf::RenderWindow& ventana, sf::Vector2f& posicioPilota, float& velocitatX, float& velocitatY, std::vector<std::vector<Bloc>>& blocs, int& scoretotal, const int max_X, const int max_Y);
