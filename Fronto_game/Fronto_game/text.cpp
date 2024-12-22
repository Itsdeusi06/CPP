#include <sstream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "text.h"

using namespace sf;
using namespace std;

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

// Función para mostrar el mensaje de Game Over
void GameOver(sf::RenderWindow& ventana, bool& gameOver, sf::Vector2f& posicioPilota, float& velocitatX, float& velocitatY, std::vector<std::vector<Bloc>>& blocs, int& scoretotal, const int max_X, const int max_Y) {

    if (gameOver) {
        // Mostrar el mensaje de GAME OVER
        Font font;
        font.loadFromFile("fonts/KOMIKAP_.ttf");

        Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setString("GAME OVER\nPress Enter to Restart");
        gameOverText.setCharacterSize(50);
        gameOverText.setFillColor(Color::Red);
        gameOverText.setPosition(200, 300);

        ventana.draw(gameOverText);
        ventana.display();

        // Esperar a que el jugador presione Enter para reiniciar
        if (Keyboard::isKeyPressed(Keyboard::Enter)) {
            // Reiniciar variables
            posicioPilota = Vector2f(max_X / 2, max_Y - 150); // Posición inicial de la pelota
            velocitatX = 0.5f;
            velocitatY = -0.5f;
            scoretotal = 0; // Reiniciar el puntaje
            gameOver = false;

            // Reactivar todos los bloques
            for (auto& fila : blocs) {
                for (auto& bloc : fila) {
                    bloc.active = true;
                }
            }
        }
    }
}
