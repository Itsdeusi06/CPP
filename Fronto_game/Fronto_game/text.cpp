#include <sstream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "text.h"

using namespace sf;
using namespace std;

// Funcio per fer el text 
void score(int& scoretotal, sf::RenderWindow& ventana) {

	Text scoreText;
	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	scoreText.setFont(font);
	scoreText.setString("Score = 0");
	scoreText.setCharacterSize(25);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(10, 10);

	std::stringstream text;
	text << "Score = " << scoretotal;
	scoreText.setString(text.str());

	ventana.draw(scoreText);
}

#include <SFML/Graphics.hpp>
#include <sstream>
#include "text.h"
#include "blocs.h"

using namespace sf;

// Funcio per mostrar el game over
void GameOver(sf::RenderWindow& ventana, bool& gameOver, sf::Vector2f& posicioPilota, float& velocitatX, float& velocitatY, std::vector<std::vector<Bloc>>& blocs, int& scoretotal, const int max_X, const int max_Y) {

    // Preparar el Background
    Texture textureBackground;
    textureBackground.loadFromFile("asets/fons.png");
    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0, 0);
    spriteBackground.setScale(2, 2);
    
    if (gameOver) {
        // Mostrar el misatge de GAME OVER
        Font font;
        font.loadFromFile("fonts/KOMIKAP_.ttf");

        Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setString("GAME OVER\nPress Enter to Restart");
        gameOverText.setCharacterSize(50);
        gameOverText.setFillColor(Color::Red);
        gameOverText.setPosition(200, 300);

        ventana.clear();                    // Netejar la pantalla 
        ventana.draw(spriteBackground);     // Dibuixar el fons
        ventana.draw(gameOverText);         // Dibuxar el game over
        ventana.display();                  // Mostrar lo dibuxat

        // Esperar a que premi Enter per reiniciar
        if (Keyboard::isKeyPressed(Keyboard::Enter)) {
            // Reiniciar variables
            posicioPilota = Vector2f(max_X / 2, max_Y - 150); // Pocicio inicial de la pilota
            velocitatX = 1.f;
            velocitatY = -1.f;
            scoretotal = 0; // Reiniciar el puntaje
            gameOver = false;

            // Reactivar tots els blocs
            for (auto& fila : blocs) {
                for (auto& bloc : fila) {
                    bloc.active = true;
                }
            }
        }
    }
}
void victoriaMostrar(sf::RenderWindow& ventana, sf::Vector2f& posicioPilota, float& velocitatX, float& velocitatY, std::vector<std::vector<Bloc>>& blocs, int& scoretotal, const int max_X, const int max_Y) {

    // Preparar el Background
    Texture textureBackground;
    textureBackground.loadFromFile("asets/fons.png");
    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0, 0);
    spriteBackground.setScale(2, 2);

    if (!quedenBlocsActius(blocs)) {
        // Mostra el misatge de victoria
        Font font;
        font.loadFromFile("fonts/KOMIKAP_.ttf");
        Text victoriaText;
        victoriaText.setFont(font);
        victoriaText.setString("CONGRATS YOU WON !! \nPress Enter to Restart");
        victoriaText.setCharacterSize(50);
        victoriaText.setFillColor(Color::Green);
        victoriaText.setPosition(200, 300);

        ventana.clear();                    // Netejar la pantalla 
        ventana.draw(spriteBackground);     // Dibuixar el fons
        ventana.draw(victoriaText);         // Dibuixar el text
        ventana.display();                  // Mostrar-ho

        // Esperar a que premi Enter per reiniciar
        if (Keyboard::isKeyPressed(Keyboard::Enter)) {
            // Reiniciar variables
            posicioPilota = Vector2f(max_X / 2, max_Y - 150); // Posicio inical de la pilot
            velocitatX = 1.f;
            velocitatY = -1.f;
            scoretotal = 0; // Reiniciar el puntaje
           

            // Reactivar tots els blocs
            for (auto& fila : blocs) {
                for (auto& bloc : fila) {
                    bloc.active = true;
                }
            }
        }
    }
}