#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <format>
using namespace std;
using namespace sf;

// Definir las files i columnes maximes
const int MaxRows = 3;
const int MaxCols = 10;

// Estructura per representar cada bloc
struct Bloc {
    RectangleShape forma;  // Rectangle que representa el bloc
    bool active;           // Indica si el bloque esta actiu o ha sigut destruit
};

// Declarar les funcions
sf::Color generarColorAleatorio();
void inicialitzarBlocs(std::vector<std::vector<Bloc>>& blocs, float ample, float altura, float separacio, float separacioDalt, float separacioEsq);
void dibuixarBlocs(sf::RenderWindow& finestra, std::vector<std::vector<Bloc>>& blocs);
void comprovarColisioPilotaBlocs(Vector2f& posicioPilota, float radi, float& velocitatX, float& velocitatY, vector<vector<Bloc>>& blocs, int& scoretotal);
bool quedenBlocsActius(const std::vector<std::vector<Bloc>>& blocs);
