#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;



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
            sf::RenderWindow window(sf::VideoMode(2000, 1000), "Nivel 1");

            // Cargar las dos texturas
            sf::Texture textureCarro;
            sf::Texture textureCarroFuego;
            if (!textureCarro.loadFromFile("Texture/carro.jpeg")) {
                std::cerr << "Error cargando la imagen carro.jpeg" << std::endl;
                return 1;
            }
            if (!textureCarroFuego.loadFromFile("Texture/carrofuego.png")) {
                std::cerr << "Error cargando la imagen carrofuego.png" << std::endl;
                return 1;
            }

            // Crear 3 sprites para los carros
            sf::Sprite obstacle1(textureCarro);
            sf::Sprite obstacle2(textureCarro);
            sf::Sprite obstacle3(textureCarro);

            // Ajustar el tamanoo de los sprites a la mitad del tamaño original
            obstacle1.setScale(0.5f, 0.5f);
            obstacle2.setScale(0.5f, 0.5f);
            obstacle3.setScale(0.5f, 0.5f);

            // Configurar la semilla para la generación aleatoria
            std::srand(static_cast<unsigned int>(std::time(nullptr)));

            // Rango de cada carro
            int thirdOfScreen = window.getSize().y / 3;
            obstacle1.setPosition(0.f, static_cast<float>(std::rand() % thirdOfScreen));
            obstacle2.setPosition(0.f, static_cast<float>(thirdOfScreen + std::rand() % thirdOfScreen));
            obstacle3.setPosition(0.f, static_cast<float>((2 * thirdOfScreen) + std::rand() % thirdOfScreen));

            // Velocidades diferentes para cada carro
            float speed1 = 0.7f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / 0.1f));
            float speed2 = 0.3f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / 0.4f));
            float speed3 = 0.8f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / 0.7f));

            // Bucle principal
            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }

               //mover carros
                obstacle1.move(speed1, 0.f);
                if (obstacle1.getPosition().x > window.getSize().x / 2) {
                    obstacle1.setTexture(textureCarroFuego);
                }
                else {
                    obstacle1.setTexture(textureCarro);
                }

                obstacle2.move(speed2, 0.f);
                if (obstacle2.getPosition().x > window.getSize().x / 2) {
                    obstacle2.setTexture(textureCarroFuego);
                }
                else {
                    obstacle2.setTexture(textureCarro);
                }

                obstacle3.move(speed3, 0.f);
                if (obstacle3.getPosition().x > window.getSize().x / 2) {
                    obstacle3.setTexture(textureCarroFuego);
                }
                else {
                    obstacle3.setTexture(textureCarro);
                }

                // Regresar el carro al principio si sale de la pantalla
                if (obstacle1.getPosition().x > window.getSize().x) {
                    obstacle1.setPosition(0.f, static_cast<float>(std::rand() % thirdOfScreen));
                    speed1 = 0.7f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / 0.1f));
                    obstacle1.setTexture(textureCarro); // Restablecer la textura original
                }
                if (obstacle2.getPosition().x > window.getSize().x) {
                    obstacle2.setPosition(0.f, static_cast<float>(thirdOfScreen + std::rand() % thirdOfScreen));
                    speed2 = 0.3f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / 0.4f));
                    obstacle2.setTexture(textureCarro); // Restablecer la textura original
                }
                if (obstacle3.getPosition().x > window.getSize().x) {
                    obstacle3.setPosition(0.f, static_cast<float>((2 * thirdOfScreen) + std::rand() % thirdOfScreen));
                    speed3 = 0.8f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / 0.7f));
                    obstacle3.setTexture(textureCarro); // Restablecer la textura original
                }

                // Dibujar carros
                window.clear();
                window.draw(obstacle1);
                window.draw(obstacle2);
                window.draw(obstacle3);
                window.display();
            }

            return 0;
        }
        case 2:
            cout << "Instrucciones: " << endl;
            cout << "PASOS PARA JUGAR SDHUDHUSHUD" << endl;
            break;
        case 3: {
            
            sf::RenderWindow window(sf::VideoMode(1600, 800), "Seleccionar personaje");

            sf::Font font;
            if (!font.loadFromFile("Texture/Lato-Black.ttf")) {
                std::cerr << "Error al cargar la fuente " << std::endl;
                return EXIT_FAILURE;
            }

            sf::Texture texture_background;
            if (!texture_background.loadFromFile("Texture/imagenfondo.jpeg")) {
                std::cerr << "error imagen fondo" << std::endl;
                return EXIT_FAILURE;
            }
            sf::Sprite sprite_background(texture_background);

            sprite_background.setScale(window.getSize().x / sprite_background.getLocalBounds().width, window.getSize().y / sprite_background.getLocalBounds().height);


            sf::Text text("Seleccionar tu personaje", font);
            text.setCharacterSize(60);
            text.setFillColor(sf::Color::White);
            text.setStyle(sf::Text::Bold);

            sf::FloatRect textBounds = text.getLocalBounds();
            text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
            text.setPosition(window.getSize().x / 2.0f, 100);

            text.setOutlineColor(sf::Color::Black);
            text.setOutlineThickness(2);

            sf::Texture texture_apo;
            sf::Texture texture_ant;
            sf::Texture texture_ale;
            sf::Texture texture_alicia;

            if (!texture_apo.loadFromFile("personajeapo.png") ||
                !texture_ant.loadFromFile("personajeant.png") ||
                !texture_ale.loadFromFile("personajeale.png") ||
                !texture_alicia.loadFromFile("personajealicia.png")) {
                std::cerr << "Error al cargar" << std::endl;
                return EXIT_FAILURE;
            }

            sf::Sprite sprite_apo(texture_apo);
            sf::Sprite sprite_ant(texture_ant);
            sf::Sprite sprite_ale(texture_ale);
            sf::Sprite sprite_alicia(texture_alicia);

            sprite_apo.setScale(1.5f, 1.5f);
            sprite_ant.setScale(1.5f, 1.5f);
            sprite_ale.setScale(1.5f, 1.5f);
            sprite_alicia.setScale(1.5f, 1.5f);

            sprite_apo.setPosition(window.getSize().x / 8.0f - sprite_apo.getGlobalBounds().width / 2, 200);
            sprite_ant.setPosition(window.getSize().x / 8.0f * 3 - sprite_ant.getGlobalBounds().width / 2, 200);
            sprite_ale.setPosition(window.getSize().x / 8.0f * 5 - sprite_ale.getGlobalBounds().width / 2, 200);
            sprite_alicia.setPosition(window.getSize().x / 8.0f * 7 - sprite_alicia.getGlobalBounds().width / 2, 200);

            sf::Text text_apo("Apo", font);
            sf::Text text_ant("Ant", font);
            sf::Text text_ale("Ale", font);
            sf::Text text_alicia("Alicia", font);

            text_apo.setCharacterSize(30);
            text_ant.setCharacterSize(30);
            text_ale.setCharacterSize(30);
            text_alicia.setCharacterSize(30);

            text_apo.setFillColor(sf::Color::White);
            text_ant.setFillColor(sf::Color::White);
            text_ale.setFillColor(sf::Color::White);
            text_alicia.setFillColor(sf::Color::White);

            text_apo.setPosition(sprite_apo.getPosition().x + sprite_apo.getGlobalBounds().width / 2 - text_apo.getGlobalBounds().width / 2, sprite_apo.getPosition().y + sprite_apo.getGlobalBounds().height + 10);
            text_ant.setPosition(sprite_ant.getPosition().x + sprite_ant.getGlobalBounds().width / 2 - text_ant.getGlobalBounds().width / 2, sprite_ant.getPosition().y + sprite_ant.getGlobalBounds().height + 10);
            text_ale.setPosition(sprite_ale.getPosition().x + sprite_ale.getGlobalBounds().width / 2 - text_ale.getGlobalBounds().width / 2, sprite_ale.getPosition().y + sprite_ale.getGlobalBounds().height + 10);
            text_alicia.setPosition(sprite_alicia.getPosition().x + sprite_alicia.getGlobalBounds().width / 2 - text_alicia.getGlobalBounds().width / 2, sprite_alicia.getPosition().y + sprite_alicia.getGlobalBounds().height + 10);

            text_apo.setOutlineColor(sf::Color::Black);
            text_apo.setOutlineThickness(2);
            text_ant.setOutlineColor(sf::Color::Black);
            text_ant.setOutlineThickness(2);
            text_ale.setOutlineColor(sf::Color::Black);
            text_ale.setOutlineThickness(2);
            text_alicia.setOutlineColor(sf::Color::Black);
            text_alicia.setOutlineThickness(2);

            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                    }

                    if (event.type == sf::Event::KeyPressed) {
                        text_apo.setFillColor(sf::Color::White);
                        text_ant.setFillColor(sf::Color::White);
                        text_ale.setFillColor(sf::Color::White);
                        text_alicia.setFillColor(sf::Color::White);

                        if (event.key.code == sf::Keyboard::Left) {
                            text_apo.setFillColor(sf::Color::Blue);
                        }
                        else if (event.key.code == sf::Keyboard::Right) {
                            text_ant.setFillColor(sf::Color::Blue);
                        }
                        else if (event.key.code == sf::Keyboard::Up) {
                            text_ale.setFillColor(sf::Color::Blue);
                        }
                        else if (event.key.code == sf::Keyboard::Down) {
                            text_alicia.setFillColor(sf::Color::Blue);
                        }
                    }
                }

                window.clear();
                window.draw(sprite_background);
                window.draw(text);

                window.draw(sprite_apo);
                window.draw(sprite_ant);
                window.draw(sprite_ale);
                window.draw(sprite_alicia);

                window.draw(text_apo);
                window.draw(text_ant);
                window.draw(text_ale);
                window.draw(text_alicia);

                window.display();
            }

            return 0;
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

