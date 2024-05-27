#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

int main() {
    //ventana game ove
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Game Over");

    //texturas
    sf::Texture texture1, texture2;
    if (!texture1.loadFromFile("Gameover1.jpeg") || !texture2.loadFromFile("Gameover2.jpeg")) { //aqui se suben las 2 fotos, del ciclo
        std::cerr << "Error cargando las imagenes" << std::endl;
        return 1;
    }

    //audio de efecto
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("over.mp3")) { //archivo de las notas del piano
        std::cerr << "Error cargando el sonido over.mp3" << std::endl;
        return 1;
    }
    sf::Sound sound;
    sound.setBuffer(buffer); //ejecutar el sonido
    sound.play();

    sf::Sprite sprite(texture1);  //imprimri la foto
    sprite.setScale(1000.f / texture1.getSize().x, 800.f / texture1.getSize().y);

    sf::Time tiempoEspera = sf::milliseconds(50);

    // Reloj para medir el tiempo
    sf::Clock reloj;

    while (window.isOpen()) {
        // Manejo de eventos
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
                window.close();
        }

        if (reloj.getElapsedTime() > tiempoEspera) {
            // Cambiar a la segunda imagen
            if (sprite.getTexture() == &texture1) {
                sprite.setTexture(texture2);
                sprite.setScale(1000.f / texture2.getSize().x, 800.f / texture2.getSize().y);
            }
            else {
                sprite.setTexture(texture1);
                sprite.setScale(1000.f / texture1.getSize().x, 800.f / texture1.getSize().y);
            }

            // Reiniciar el reloj
            reloj.restart();
        }

        // Dibujar
        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
