#include "blocs.h"
#include "text.h"

sf::Color generarColorAleatorio() {
    // Genera un valor aleatori para cada element de color (R,G,B)
    return sf::Color(rand() % 256, rand() % 256, rand() % 256);
}

// Inicializar els blocs
void inicialitzarBlocs(std::vector<std::vector<Bloc>>& blocs, float ample, float altura, float separacio, float separacioDalt, float separacioEsq) {

    // Iniciar la semilla per el rand de numeros
    srand((time(0)));

    for (int fila = 0; fila < MaxRows; ++fila) {    // Dibuixar cada bloc per numero de maxRows que hi hagi
        std::vector<Bloc> filaBlocs;
        for (int columna = 0; columna < MaxCols; ++columna) {   // Igual per el numero de maxCols
            Bloc bloc;
            bloc.forma.setSize(sf::Vector2f(ample, altura));
            bloc.forma.setFillColor(generarColorAleatorio());   // Aqui es crida la funcio per posar un color al bloc (cada cop sera diferent)
            bloc.forma.setPosition(columna * (ample + separacio) + separacioEsq, fila * (altura + separacio) + separacioDalt);
            bloc.active = true;  // Marca el bloc como actiu
            filaBlocs.push_back(bloc);
        }
        blocs.push_back(filaBlocs);
    }
}

// Funcio per dibuxar els blocs 
void dibuixarBlocs(sf::RenderWindow& finestra, std::vector<std::vector<Bloc>>& blocs) {
    for (auto& fila : blocs) {
        for (auto& bloc : fila) {
            if (bloc.active) {
                finestra.draw(bloc.forma);
            }
        }
    }
}

// Funcio per mirar si col·lisionen amb la pilota
void comprovarColisioPilotaBlocs(sf::Vector2f& posicioPilota, float radi, float& velocitatX, float& velocitatY, std::vector<std::vector<Bloc>>& blocs, int& scoretotal) {
    // Per cada fila de blocs
    for (auto& fila : blocs) { 
        // Per cada bloc de la fila
        for (auto& bloc : fila) {
            // Comprovem si el bloc esta actiu (si no esta destruit)
            if (bloc.active) {
                // Coordenades del bloc
                float blocEsquerra = bloc.forma.getPosition().x; // Coordenada X de l'esquerra del bloc
                float blocDreta = blocEsquerra + bloc.forma.getSize().x; // Coordenada X de la dreta del bloc
                float blocSuperior = bloc.forma.getPosition().y; // Coordenada Y de la part superior del bloc
                float blocInferior = blocSuperior + bloc.forma.getSize().y; // Coordenada Y de la part inferior del bloc

                // Comprovar col.lisio en l'eix X
                bool colisioX = posicioPilota.x + radi > blocEsquerra && posicioPilota.x - radi < blocDreta;
                // Comprovar col.lisio en l'eix Y
                bool colisioY = posicioPilota.y + radi > blocSuperior && posicioPilota.y - radi < blocInferior;

                // Si es detecta col.lisio amb el bloc en ambdos eixos (X i Y)
                if (colisioX && colisioY) {
                    // Determinar el costat de la col.lisio (horizontal o vertical)
                    float overlapEsquerra = posicioPilota.x + radi - blocEsquerra; // Superposicio per l'esquerra
                    float overlapDreta = blocDreta - (posicioPilota.x - radi); // Superposicio per la dreta
                    float overlapSuperior = posicioPilota.y + radi - blocSuperior; // Superposicio per la part superior
                    float overlapInferior = blocInferior - (posicioPilota.y - radi); // Superposicio per la part inferior

                    // Detecta la menor superposicio per determinar la direccio del rebot
                    if (std::min(overlapEsquerra, overlapDreta) < std::min(overlapSuperior, overlapInferior)) {
                        // Si la superposicio horitzontal es menor, la col.lisio es horitzontal
                        velocitatX = -velocitatX;  // Invertim la velocitat en l'eix X (rebota horitzontal)
                    }
                    else {
                        // Si la superposicio vertical és menor, la col.lisio es vertical
                        velocitatY = -velocitatY;  // Invertim la velocitat en l'eix Y (rebota vertical)
                    }

                    scoretotal += 10;  // Afegim 10 punts per cada bloc destruït

                    bloc.active = false;  // Desactivem el bloc (marquem com destruït)

                    return;  // Sortir de la funcio, ja que nomes es vol detectar una col.lisio per vegada
                }
            }
        }
    }
}


// Funcio per verificar si quedan blocs atius
bool quedenBlocsActius(const std::vector<std::vector<Bloc>>& blocs) {
    for (const auto& fila : blocs) {
        for (const auto& bloc : fila) {
            if (bloc.active) {
                return true; // Al menos un bloc esta actiu
            }
        }
    }
    return false; // No quedan blocs actius
}

