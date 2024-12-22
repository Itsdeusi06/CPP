#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <format>
using namespace std;
using namespace sf;

// Definir las dimensiones máximas de filas y columnas
const int MaxRows = 3;
const int MaxCols = 10;

// Estructura para representar cada bloque
struct Bloc {
    RectangleShape forma;  // Rectángulo que representa el bloque
    bool active;           // Indica si el bloque está activo o ha sido destruido
};

sf::Color generarColorAleatorio();
void inicialitzarBlocs(std::vector<std::vector<Bloc>>& blocs, float ample, float altura, float separacio, float separacioDalt, float separacioEsq);
void dibuixarBlocs(sf::RenderWindow& finestra, std::vector<std::vector<Bloc>>& blocs);
void comprovarColisioPilotaBlocs(Vector2f& posicioPilota, float radi, float& velocitatX, float& velocitatY, vector<vector<Bloc>>& blocs, int& scoretotal);

