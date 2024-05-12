#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Crear la ventana
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Game Over");
    
    sf::Texture texture1, texture2;
    if (!texture1.loadFromFile("Gameover1.jpeg") || !texture2.loadFromFile("Gameover2.jpeg")) {
        std::cerr << "Error cargando las imágenes" << std::endl;
        return 1;
    }

    sf::Sprite sprite(texture1);
    sprite.setScale(1000.f / texture1.getSize().x, 800.f / texture1.getSize().y);

    sf::Time tiempoEspera = sf::milliseconds(50); //tiempo


    sf::Clock reloj;

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed) // salir si se presiona
                goto EndLoop;
        }

        if (reloj.getElapsedTime() > tiempoEspera) {
            // Cambiar a la segunda imagen
            if (sprite.getTexture() == &texture1) {
                sprite.setTexture(texture2);
                sprite.setScale(1000.f / texture2.getSize().x, 800.f / texture2.getSize().y);
            } else {
                sprite.setTexture(texture1);
                sprite.setScale(1000.f / texture1.getSize().x, 800.f / texture1.getSize().y);
            }

            reloj.restart();
        }

        // Limpiar la ventana
        window.clear();

        // Dibujar la imagen en la ventana
        window.draw(sprite);

        // Mostrar la ventana
        window.display();
    }

    EndLoop: //termianr imagenes
    return 0;
}
