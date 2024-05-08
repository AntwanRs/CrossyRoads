#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
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

    // Ajustar el tamaño de los sprites a la mitad del tamaño original
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

        // Mover los carros y cambiar la textura si han pasado la mitad de la pantalla
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
