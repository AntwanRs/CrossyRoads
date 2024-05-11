#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

void moveObstacle(sf::Sprite& obstacle, sf::Texture& textureCarro, sf::Texture& textureCarroFuego, float& speed, int thirdOfScreen) {
    obstacle.move(speed, 0.f);
    if (obstacle.getPosition().x > 1000) {
        obstacle.setPosition(0.f, static_cast<float>(rand() % thirdOfScreen));
        speed = 0.7f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 0.1f));
        obstacle.setTexture(textureCarro);
    }
    if (obstacle.getPosition().x > 500) {
        obstacle.setTexture(textureCarroFuego);
    }
    else {
        obstacle.setTexture(textureCarro);
    }
} 


int main() {
    int opcion;

    do {
        cout << " ____                                                            ____                           __     \n"
            "/\\  _`\\                                                         /\\  _`\\                        /\\ \\    \n"
            "\\ \\ \\/\\_\\   _ __    ___     ____    ____   __  __               \\ \\ \\L\\ \\     ___      __      \\_\\ \\   \n"
            " \\ \\ \\/_/_ /\\`'__\\ / __`\\  /',__\\  /',__\\ /\\ \\/\\ \\               \\ \\ ,  /    / __`\\  /'__`\\    /'_` \\  \n"
            "  \\ \\ \\L\\ \\\\ \\ \\/ /\\ \\L\\ \\/\\__, `\\/\\__, `\\\\ \\ \\_\\ \\               \\ \\ \\\\ \\  /\\ \\L\\ \\/\\ \\L\\.\\_ /\\ \\L\\ \\ \n"
            "   \\ \\____/ \\ \\_\\ \\ \\____/\\/\\____/\\/\\____/ \\/`____ \\               \\ \\_\\ \\_\\\\ \\____/\\ \\__/.\\_\\\\ \\___,_\\\n"
            "    \\/___/   \\/_/  \\/___/  \\/___/  \\/___/   `/___/> \\               \\/_/\\/ / \\/___/  \\/__/\\/_/ \\/__,_ /\n"
            "                                               /\\___/                                                  \n"
            "                                               \\/__/                                                   " << endl;

        cout << "Menu" << endl;
        cout << "1. Comenzar" << endl;
        cout << "2. Instrucciones para jugar" << endl;
        cout << "3. Escoger personaje" << endl;
        cout << "4. Salir" << endl;

        cout << "Ingrese su opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            cout << "start" << endl;
            sf::RenderWindow window(sf::VideoMode(2000, 1000), "Nivel 1");

            sf::Texture textureCarro;
            sf::Texture textureCarroFuego;
            if (!textureCarro.loadFromFile("Texture/carro.jpeg")) {
                cerr << "Error cargando la imagen carro.jpeg" << endl;
                return 1;
            }
            if (!textureCarroFuego.loadFromFile("Texture/carrofuego.png")) {
                cerr << "Error cargando la imagen carrofuego.png" << endl;
                return 1;
            }

            sf::Sprite obstacle1(textureCarro);
            sf::Sprite obstacle2(textureCarro);
            sf::Sprite obstacle3(textureCarro);

            obstacle1.setScale(0.5f, 0.5f);
            obstacle2.setScale(0.5f, 0.5f);
            obstacle3.setScale(0.5f, 0.5f);

            srand(static_cast<unsigned int>(time(nullptr)));

            int thirdOfScreen = window.getSize().y / 3;
            obstacle1.setPosition(0.f, static_cast<float>(rand() % thirdOfScreen));
            obstacle2.setPosition(0.f, static_cast<float>(thirdOfScreen + rand() % thirdOfScreen));
            obstacle3.setPosition(0.f, static_cast<float>((2 * thirdOfScreen) + rand() % thirdOfScreen));

            float speed1 = 0.7f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 0.1f));
            float speed2 = 0.3f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 0.4f));
            float speed3 = 0.8f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 0.7f));

            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }

                moveObstacle(obstacle1, textureCarro, textureCarroFuego, speed1, thirdOfScreen);
                moveObstacle(obstacle2, textureCarro, textureCarroFuego, speed2, thirdOfScreen);
                moveObstacle(obstacle3, textureCarro, textureCarroFuego, speed3, thirdOfScreen);

                window.clear();
                window.draw(obstacle1);
                window.draw(obstacle2);
                window.draw(obstacle3);
                window.display();
            }
            break;
        }
        case 2:
            cout << "Instrucciones: " << endl;
            cout << "PASOS PARA JUGAR SDHUDHUSHUD" << endl;
            break;
        case 3: {
            // Crear una ventana de SFML
            sf::RenderWindow window(sf::VideoMode(2000, 1000), "MENU");

            //Cambiar por imagen de fondo 
            sf::RectangleShape background(sf::Vector2f(2000, 1000));
            background.setFillColor(sf::Color(255, 165, 0)); // Naranja

            // Cargar 
            sf::Texture texture_apo;
            sf::Texture texture_ant;
            sf::Texture texture_ale;
            sf::Texture texture_alicia;

            if (!texture_apo.loadFromFile("personajeapo.png") ||
                !texture_ant.loadFromFile("personajeant.png") ||
                !texture_ale.loadFromFile("personajeale.jpeg") ||
                !texture_alicia.loadFromFile("personajealicia.jpeg")) {
                std::cerr << "Error al cargar" << std::endl;
                return 1; // Salir con error
            }

            // Crear sprites para cada imagen
            sf::Sprite sprite_apo(texture_apo);
            sf::Sprite sprite_ant(texture_ant);
            sf::Sprite sprite_ale(texture_ale);
            sf::Sprite sprite_alicia(texture_alicia);

            // size de cada un
            sprite_apo.setScale(2.0f, 2.0f);
            sprite_ant.setScale(2.0f, 2.0f);
            sprite_ale.setScale(2.0f, 2.0f);
            sprite_alicia.setScale(2.0f, 2.0f);

            //posicion
            sprite_apo.setPosition(100, 100);
            sprite_ant.setPosition(400, 100);
            sprite_ale.setPosition(800, 100);
            sprite_alicia.setPosition(1500, 100);

            // Imprimir texto en la consola
            std::cout << "Selecciona tu personaje" << std::endl;

            // Bucle principal
            while (window.isOpen()) {
                // Manejar eventos
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }

                // Limpiar la ventana
                window.clear();

                // Dibujar los sprites en la ventana
                window.draw(sprite_apo);
                window.draw(sprite_ant);
                window.draw(sprite_ale);
                window.draw(sprite_alicia);

                // Mostrar la ventana
                window.display();
            }


            break;
        }
        case 4:
            cout << "Cerrando..." << endl;
            break;
        default:
            cout << "Ingrese una opcion valida" << endl;
        }
    } while (opcion != 4);

    return 0;
}


