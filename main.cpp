#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Crear la ventana
    sf::RenderWindow window(sf::VideoMode(1600, 800), "Seleccionar personaje");

    // Cargar la fuente
    sf::Font font;
    if (!font.loadFromFile("Texture/Lato-Black.ttf")) {
        std::cerr << "Error al cargar la fuente " << std::endl;
        return EXIT_FAILURE;
    }

    // Cargar la imagen de fondo
    sf::Texture texture_background;
    if (!texture_background.loadFromFile("Texture/imagenfondo.jpeg")) {
        std::cerr << "Error al cargar la imagen de fondo" << std::endl;
        return EXIT_FAILURE;
    }
    sf::Sprite sprite_background(texture_background);

    sprite_background.setScale(window.getSize().x / sprite_background.getLocalBounds().width, window.getSize().y / sprite_background.getLocalBounds().height);


    sf::Text text("Seleccionar tu personaje", font);
    text.setCharacterSize(60);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    // alineacion texto
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    text.setPosition(window.getSize().x / 2.0f, 100);

    //sombra titulo
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(2);

    // Cargar las texturas de los personajes
    sf::Texture texture_apo;
    sf::Texture texture_ant;
    sf::Texture texture_ale;
    sf::Texture texture_alicia;

    if (!texture_apo.loadFromFile("personajeapo.png") ||
        !texture_ant.loadFromFile("personajeant.png") ||
        !texture_ale.loadFromFile("personajeale.png") ||
        !texture_alicia.loadFromFile("personajealicia.png")) {
        std::cerr << "Error al cargar" << std::endl;
        return EXIT_FAILURE; // Salir con error
    }

    // Crear sprites para cada imagen
    sf::Sprite sprite_apo(texture_apo);
    sf::Sprite sprite_ant(texture_ant);
    sf::Sprite sprite_ale(texture_ale);
    sf::Sprite sprite_alicia(texture_alicia);

    // Escalar personaje
    sprite_apo.setScale(1.5f, 1.5f);
    sprite_ant.setScale(1.5f, 1.5f);
    sprite_ale.setScale(1.5f, 1.5f);
    sprite_alicia.setScale(1.5f, 1.5f);

    // Posicionar las fotos debajo del texto
    sprite_apo.setPosition(window.getSize().x / 8.0f - sprite_apo.getGlobalBounds().width / 2, 200);
    sprite_ant.setPosition(window.getSize().x / 8.0f * 3 - sprite_ant.getGlobalBounds().width / 2, 200);
    sprite_ale.setPosition(window.getSize().x / 8.0f * 5 - sprite_ale.getGlobalBounds().width / 2, 200);
    sprite_alicia.setPosition(window.getSize().x / 8.0f * 7 - sprite_alicia.getGlobalBounds().width / 2, 200);

    // Crear el texto para cada imagen
    sf::Text text_apo("Apo", font);
    sf::Text text_ant("Ant", font);
    sf::Text text_ale("Ale", font);
    sf::Text text_alicia("Alicia", font);

    // Configurar el estilo y size del texto
    text_apo.setCharacterSize(30);
    text_ant.setCharacterSize(30);
    text_ale.setCharacterSize(30);
    text_alicia.setCharacterSize(30);

    // Configurar el color del texto
    text_apo.setFillColor(sf::Color::White);
    text_ant.setFillColor(sf::Color::White);
    text_ale.setFillColor(sf::Color::White);
    text_alicia.setFillColor(sf::Color::White);

    // coordenadas del texto abajo de cada personaje
    text_apo.setPosition(sprite_apo.getPosition().x + sprite_apo.getGlobalBounds().width / 2 - text_apo.getGlobalBounds().width / 2, sprite_apo.getPosition().y + sprite_apo.getGlobalBounds().height + 10);
    text_ant.setPosition(sprite_ant.getPosition().x + sprite_ant.getGlobalBounds().width / 2 - text_ant.getGlobalBounds().width / 2, sprite_ant.getPosition().y + sprite_ant.getGlobalBounds().height + 10);
    text_ale.setPosition(sprite_ale.getPosition().x + sprite_ale.getGlobalBounds().width / 2 - text_ale.getGlobalBounds().width / 2, sprite_ale.getPosition().y + sprite_ale.getGlobalBounds().height + 10);
    text_alicia.setPosition(sprite_alicia.getPosition().x + sprite_alicia.getGlobalBounds().width / 2 - text_alicia.getGlobalBounds().width / 2, sprite_alicia.getPosition().y + sprite_alicia.getGlobalBounds().height + 10);

    // sombra texto
    text_apo.setOutlineColor(sf::Color::Black);
    text_apo.setOutlineThickness(2);
    text_ant.setOutlineColor(sf::Color::Black);
    text_ant.setOutlineThickness(2);
    text_ale.setOutlineColor(sf::Color::Black);
    text_ale.setOutlineThickness(2);
    text_alicia.setOutlineColor(sf::Color::Black);
    text_alicia.setOutlineThickness(2);

    // seleccion
    while (window.isOpen()) {
        // Manejo de eventos
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // ver clicks
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (text_apo.getGlobalBounds().contains(mousePos)) {
                    // Resaltar el texto de Apo
                    text_apo.setFillColor(sf::Color::Blue);
                    // color en texto
                    text_ant.setFillColor(sf::Color::White);
                    text_ale.setFillColor(sf::Color::White);
                    text_alicia.setFillColor(sf::Color::White);
                }
                if (text_ant.getGlobalBounds().contains(mousePos)) {
                    // Resaltar el texto de Ant
                    text_ant.setFillColor(sf::Color::Blue);
                    // color en texto
                    text_apo.setFillColor(sf::Color::White);
                    text_ale.setFillColor(sf::Color::White);
                    text_alicia.setFillColor(sf::Color::White);
                }
                if (text_ale.getGlobalBounds().contains(mousePos)) {
                    // Resaltar el texto de Ale
                    text_ale.setFillColor(sf::Color::Blue);
                    // color en texto
                    text_apo.setFillColor(sf::Color::White);
                    text_ant.setFillColor(sf::Color::White);
                    text_alicia.setFillColor(sf::Color::White);
                }
                if (text_alicia.getGlobalBounds().contains(mousePos)) {
                    // Resaltar el texto de Alicia
                    text_alicia.setFillColor(sf::Color::Blue);
                    // color en texto
                    text_apo.setFillColor(sf::Color::White);
                    text_ant.setFillColor(sf::Color::White);
                    text_ale.setFillColor(sf::Color::White);
                }
            }
        }

        // Limpiar la ventana
        window.clear();

        // Dibujar el fondo
        window.draw(sprite_background);

        // Dibujar elementos en la ventana
        window.draw(text);

        // Dibujar las personajes en la ventana
        window.draw(sprite_apo);
        window.draw(sprite_ant);
        window.draw(sprite_ale);
        window.draw(sprite_alicia);

        // Dibujar el texto para cada imagen
        window.draw(text_apo);
        window.draw(text_ant);
        window.draw(text_ale);
        window.draw(text_alicia);

        // Mostrar la ventana
        window.display();
    }

    return 0;
}
