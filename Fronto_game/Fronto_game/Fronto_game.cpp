#include <iostream>
#include <SFML/Graphics.hpp>
#include "barra.h"
#include "pilota.h"
#include "blocs.h"
#include "text.h"

using namespace sf;

int main()
{
    const float max_X = 1000;  // Ample de finestra
    const float max_Y = 700;  // Altura de la finestra

    RenderWindow finestra(VideoMode(max_X, max_Y), "Fronto Game");

    // Preparar Background
    Texture textureBackground;
    textureBackground.loadFromFile("asets/fons.png");
    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0, 0);
    spriteBackground.setScale(2, 2);

    // Parametres de la barra
    Vector2f posicioBarra(max_X / 2, max_Y - 100);  // Posicio inicial de la barra
    float longitutBarra = max_X / 4;  // Longitut de la barra
    float altBarra = max_Y / 20;    // Altura de la barra
    float velocitatBarra = 2.f;     // Velocitat de la barra

    // Parametres dels blocs
    Vector2f posicioBlocs(max_X / 2, max_Y - 100);  // Posicio inicial dels blocs
    float ampleBlocs = 80.0f;           // Ample dels blocs
    float alturaBlocs = 40.0f;          // Altura dels blocs
    float separacioBlocs = 10.0f;       // Separacio dels blocs entre ells
    float separacioDalt = 50.0f;        // Separacio del sostre
    float SeparacioEsq = 50.0f;         // Separacio de la esquera
    std::vector<std::vector<Bloc>> blocs;   // Forma (en vectors) blocs
    inicialitzarBlocs(blocs, ampleBlocs, alturaBlocs, separacioBlocs, separacioDalt, SeparacioEsq); // Inicia els blocs amb les dades inicials

    // Parametres de la pilota  
    Vector2f posicioPilota(max_X / 2, max_Y - 150); // Posicio inicial de la pilota
    float velocitatPilotaX = 1.f;       // Velocitat pilota de x
    float velocitatPilotaY = 1.f;       // Velocitat pilota de y
    float radiPilota = 10.f;            // Radi de la pilota
    CircleShape pilotaForma;            // Forma de la pilota

    // Text 
    int scoretotal = 0;     // Inicar els punts a zero
    // Variable per saber si a acabat el joc
    bool gameOver = false;

    // Bucle de dibuixar
    while (finestra.isOpen())
    {
        // Event per tancar la finestra amb la creueta de la finestra
        Event evento;
        while (finestra.pollEvent(evento))
        {
            if (evento.type == Event::Closed)
                finestra.close();
        }
        
        // Per fer proves per no tenir que guanyar tot el rato
        //////////if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { // Si es l'espai es premut tots els blocs se piran
        //////////    for (auto& fila : blocs) {
        //////////        for (auto& bloc : fila) {
        //////////            bloc.active = false; // Desactivar tots els blocs
        //////////        }
        //////////    }
        //////////}

        GameOver(finestra, gameOver, posicioPilota, velocitatPilotaX, velocitatPilotaY, blocs, scoretotal, max_X, max_Y);
        if (gameOver) continue; // Pausar el joc si esta en GameOver

        victoriaMostrar(finestra, posicioPilota, velocitatPilotaX, velocitatPilotaY, blocs, scoretotal, max_X, max_Y);
        if (!quedenBlocsActius(blocs)) continue;    // Pausar el joc si esta no hi han blocs

        finestra.clear();  // Netejar la finestra avans de dibuixar

        finestra.draw(spriteBackground);    // Dibujar el fons

        // Actualizar y comprobar colisions de la pilota
        pilota(finestra, posicioPilota, radiPilota, velocitatPilotaX, velocitatPilotaY, max_X, max_Y, posicioBarra, blocs, altBarra, longitutBarra, gameOver);

        // Comprobar colisiones amb blocs i actualizar els punts
        score(scoretotal, finestra);
        comprovarColisioPilotaBlocs(posicioPilota, radiPilota, velocitatPilotaX, velocitatPilotaY, blocs, scoretotal);

        // Dibujar barra i blocs
        barra(finestra, posicioBarra, longitutBarra, altBarra, velocitatBarra, max_X, max_Y);
        dibuixarBlocs(finestra, blocs);

        finestra.display();  // Mostrar els objectes dibuixats
    }

    return 0;
}
