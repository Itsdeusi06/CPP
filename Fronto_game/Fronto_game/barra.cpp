#include <SFML/Graphics.hpp>
#include "barra.h"

using namespace sf;

void barra(RenderWindow& ventana, Vector2f& posicion, float longitud, float alto, float velocidad, const int max_X, const int max_Y)
{
    RectangleShape barra;
    barra.setSize(Vector2f(longitud, alto));  // Establir el tamany
    barra.setFillColor(Color::White);  // Color de la barra
    barra.setPosition(Vector2f(posicion.x, posicion.y));  // Posicio de la barra

    // Moviment de la barra cap a la dreta
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        posicion.x += velocidad;  // Moure a la dreta
    }
    // Moviment de la barra cap a la esquerra
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        posicion.x -= velocidad;  // Moure a la dreta
    }

    // Limitar el moviment per que la barra no surti de la finestra
    if (posicion.x < 0)  // Limitar la posicio de la esquerra
    {
        posicion.x = 0;
    }
    if (posicion.x + longitud > max_X)  // Limitar la posicio de la dreta
    {
        posicion.x = max_X - longitud;
    }

    // Dibuxar la barra
    ventana.draw(barra);
}

