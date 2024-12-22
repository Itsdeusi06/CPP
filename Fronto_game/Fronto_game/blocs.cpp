#include "blocs.h"

sf::Color generarColorAleatorio() {
    // Genera un valor aleatorio para cada componente de color (Rojo, Verde, Azul)
    return sf::Color(rand() % 256, rand() % 256, rand() % 256);
}

// Inicializar los bloques
void inicialitzarBlocs(std::vector<std::vector<Bloc>>& blocs, float ample, float altura, float separacio, float separacioDalt, float separacioEsq) {

    // Inicializar la semilla del generador de números aleatorios
    srand(static_cast<unsigned int>(time(0)));  // Solo lo hacemos una vez

    for (int fila = 0; fila < MaxRows; ++fila) {
        std::vector<Bloc> filaBlocs;
        for (int columna = 0; columna < MaxCols; ++columna) {
            Bloc bloc;
            bloc.forma.setSize(sf::Vector2f(ample, altura));
            bloc.forma.setFillColor(generarColorAleatorio());
            bloc.forma.setPosition(
                columna * (ample + separacio) + separacioEsq,
                fila * (altura + separacio) + separacioDalt
            );
            bloc.active = true;  // Marca el bloque como activo
            filaBlocs.push_back(bloc);
        }
        blocs.push_back(filaBlocs);
    }
}

// Definición de la función para dibujar los bloques
void dibuixarBlocs(sf::RenderWindow& finestra, std::vector<std::vector<Bloc>>& blocs) {
    for (auto& fila : blocs) {
        for (auto& bloc : fila) {
            if (bloc.active) {
                finestra.draw(bloc.forma);
            }
        }
    }
}

// Función para comprobar colisiones con los bloques
void comprovarColisioPilotaBlocs(sf::Vector2f& posicioPilota, float radi, float& velocitatX, float& velocitatY, std::vector<std::vector<Bloc>>& blocs, int& scoretotal) {
    for (auto& fila : blocs) {
        for (auto& bloc : fila) {
            if (bloc.active) {
                // Coordenadas del bloque
                float blocEsquerra = bloc.forma.getPosition().x;
                float blocDreta = blocEsquerra + bloc.forma.getSize().x;
                float blocSuperior = bloc.forma.getPosition().y;
                float blocInferior = blocSuperior + bloc.forma.getSize().y;

                // Comprobar colisión
                bool colisioX = posicioPilota.x + radi > blocEsquerra && posicioPilota.x - radi < blocDreta;
                bool colisioY = posicioPilota.y + radi > blocSuperior && posicioPilota.y - radi < blocInferior;

                if (colisioX && colisioY) {
                    // Determinar el lado de la colisión (horizontal o vertical)
                    float overlapEsquerra = posicioPilota.x + radi - blocEsquerra;
                    float overlapDreta = blocDreta - (posicioPilota.x - radi);
                    float overlapSuperior = posicioPilota.y + radi - blocSuperior;
                    float overlapInferior = blocInferior - (posicioPilota.y - radi);

                    // Detectamos la menor superposición (determinamos la dirección del rebote)
                    if (std::min(overlapEsquerra, overlapDreta) < std::min(overlapSuperior, overlapInferior)) {
                        // Colisión horizontal
                        velocitatX = -velocitatX;
                    }
                    else {
                        // Colisión vertical
                        velocitatY = -velocitatY;
                    }

                    // Incrementar el puntaje
                    scoretotal += 10;  // Añadir 10 puntos por cada bloque destruido

                    bloc.active = false;  // Desactivar el bloque después de la colisión
                    return;  // Salir de la función para no detectar más colisiones con otros bloques
                }
            }
        }
    }
}


