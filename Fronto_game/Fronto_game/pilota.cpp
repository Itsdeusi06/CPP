#include <SFML/Graphics.hpp>
#include "barra.h"  // importem el .h de la barra per poder utilitzar la funcio
#include "blocs.h"

using namespace sf;

void pilota(sf::RenderWindow& finestra, sf::Vector2f& posicio, float radi, float& velocitatX, float& velocitatY, const int max_X, const int max_Y, sf::Vector2f posicioBarra, std::vector<std::vector<Bloc>>& blocs, float altBarra, float longitutBarra, bool& gameOver)
{
    // Crear la pilota
    CircleShape pilota(radi);
    pilota.setFillColor(sf::Color::Green);
    pilota.setPosition(posicio.x, posicio.y);
    pilota.setOrigin(sf::Vector2f(pilota.getRadius(), pilota.getRadius()));  // Centrar el origen de la pilota

    // Moure la pilota depenen de les velocitats
    posicio.x += velocitatX;  // Mover en X
    posicio.y += velocitatY;  // Mover en Y

    // Incrementar la velocitat proporcionalmente
    float increment = 0.00001f;  // Factor de incremento
    velocitatX += velocitatX * increment;  // Incrementar velocidad en X
    velocitatY += velocitatY * increment;  // Incrementar velocidad en Y

    // Colisions amb les parets
    // Colisio amb el costat esquerra
    if (posicio.x < radi) {
        posicio.x = radi;  // Evitar que pasi del costat
        velocitatX = -velocitatX;  // Invertir la direccio de la X
    }
    // Colisio amb el canto dret
    if (posicio.x + radi > max_X) {
        posicio.x = max_X - radi;  // Evitar que pasi del costat
        velocitatX = -velocitatX;  // Invertir la direccio de la X
    }
    // Colisio amb el canto superior
    if (posicio.y < radi) {
        posicio.y = radi;  // Evitar que pasi del costat
        velocitatY = -velocitatY;  // Invertir la direccio de la Y
    }
    // Colisio amb el costat inferior (game over)
    if (posicio.y + radi > max_Y) {
        gameOver = true;
        increment = 0.001f;
        return;
    }

    // Rebot amb la barra
    if (posicio.y + radi >= posicioBarra.y &&                  // Toca el borde superior de la barra
        posicio.y - radi <= posicioBarra.y + altBarra &&       // No sobrepasa el borde inferior
        posicio.x + radi >= posicioBarra.x &&                  // Toca el borde izquierdo
        posicio.x - radi <= posicioBarra.x + longitutBarra) {  // No sobrepasa el borde derecho
        posicio.y = posicioBarra.y - radi;                     // Ajustar posicio per evitar superposicio


        // Invertir la direcio Y per que puji
        velocitatY = -abs(velocitatY);  // Asegurar que semplre anira amunt

        // Calcul per moures en una direcio depenen del angle de rebot
        float impact = (posicio.x - (posicioBarra.x + longitutBarra / 2)) / (longitutBarra / 2);
        velocitatX = impact * abs(velocitatY);  // Cambiar la direccio en X basat en el impacto
    }


    // Dibuixar la pilota
    finestra.draw(pilota);
}
