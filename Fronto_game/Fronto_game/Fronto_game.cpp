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

    // Prepere the Background
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
    float velocitatBarra = 2.f;

    // Parametres dels blocs
    Vector2f posicioBlocs(max_X / 2, max_Y - 100);  // Posicio inicial dels blocs
    // Configuración de los bloques 
    float ampleBlocs = 80.0f;
    float alturaBlocs = 40.0f;
    float separacioBlocs = 10.0f;
    float separacioDalt = 50.0f;
    float SeparacioEsq = 50.0f;
    std::vector<std::vector<Bloc>> blocs;
    inicialitzarBlocs(blocs, ampleBlocs, alturaBlocs, separacioBlocs, separacioDalt, SeparacioEsq);

    // Parametres de la pilota
    Vector2f posicioPilota(max_X / 2, max_Y - 150); // Posicio inicial de la pilota
    float velocitatPilotaX = 1.f;
    float velocitatPilotaY = 1.f;
    float radiPilota = 10.f;
    CircleShape pilotaForma;

    // text 
    int scoretotal = 0;
    // Variable para saber si el juego ha terminado
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

        

        GameOver(finestra, gameOver, posicioPilota, velocitatPilotaX, velocitatPilotaY, blocs, scoretotal, max_X, max_Y);
        if (gameOver) continue; // Pausar el juego mientras esté en Game Over

        finestra.clear();  // Netejar la finestra avans de dibuixar

        finestra.draw(spriteBackground);

        // Actualizar y comprobar colisiones
        pilota(finestra, posicioPilota, radiPilota, velocitatPilotaX, velocitatPilotaY, max_X, max_Y, posicioBarra, blocs, altBarra, longitutBarra, gameOver);

        // Comprobar colisiones con bloques
        score(scoretotal, finestra);
        comprovarColisioPilotaBlocs(posicioPilota, radiPilota, velocitatPilotaX, velocitatPilotaY, blocs, scoretotal);

        // Dibujar elementos
        barra(finestra, posicioBarra, longitutBarra, altBarra, velocitatBarra, max_X, max_Y);
        dibuixarBlocs(finestra, blocs);

        finestra.display();  // Mostrar els objectes dibuixats
    }

    return 0;
}
