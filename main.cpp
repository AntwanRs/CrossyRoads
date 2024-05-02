#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

int main() {
    // crear ventana extra
    sf::RenderWindow window(sf::VideoMode(1000, 700), "Imagen con SFML");

    // Cargar archivo
    sf::Texture texture;
    if (!texture.loadFromFile("Texture/DEAUTOR.jpg")) {
        std::cerr << "Error al cargar la imagen" << std::endl;
        return 1;
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);


    sprite.setScale(1.77f, 1.7f); // Ajusta los valores según sea necesario

    // ver q sirva
    bool gameOverPrinted = false;

    // ciclo de la impresion
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(sprite);

        // Imprimir mensaje
        if (!gameOverPrinted) {
            cout << "GAME OVER - FALTA MEJORAR" << std::endl;
            cout << "1 - Intentar de nuevo "<< std::endl;
            cout << "2 - Rendirse " << std::endl;
            gameOverPrinted = true; // Marca como impreso
        }

        window.display();
    }

    return 0;
}
