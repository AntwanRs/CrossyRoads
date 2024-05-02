#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib> // Numeros para que los carros no sean iguales
#include <ctime>   

int main() {
    sf::RenderWindow window(sf::VideoMode(2000, 1000), "Nivel 1"); // Donde se abre la ventana
    sf::Texture obstacleTexture;
    if (!obstacleTexture.loadFromFile("Texture/carro.jpeg")) { // se carga la imagen del carro verde
        std::cerr << "Error cargando la imagen carro.jpeg" << std::endl;
        return 1;
    }

    // Crear 3 sprites para los carros
    sf::Sprite obstacle1(obstacleTexture);
    sf::Sprite obstacle2(obstacleTexture);
    sf::Sprite obstacle3(obstacleTexture);

    // Configurar la semilla para la generación aleatoria
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    //rango de cada carro
    int thirdOfScreen = window.getSize().y / 7;
    obstacle1.setPosition(0.f, static_cast<float>(std::rand() % thirdOfScreen));
    obstacle2.setPosition(0.f, static_cast<float>(thirdOfScreen + std::rand() % thirdOfScreen));
    obstacle3.setPosition(0.f, static_cast<float>((2 * thirdOfScreen) + std::rand() % thirdOfScreen));

    // Velocidades diferentes para cada carro
    float speed1 = 0.7f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / 0.1f));
    float speed2 = 0.3f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / 0.4f));
    float speed3 = 0.8f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / 0.7f));

    // no tengan misma velocidad
    while (speed1 == speed2 || speed1 == speed3 || speed2 == speed3) {
        speed2 = 0.3f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / 0.2f));
        speed3 = 0.2f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / 0.1f));
    }

    // Bucle principal
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //velocidades diferentes a cada uno
        obstacle1.move(speed1, 0.f); // La velocidad
        obstacle2.move(speed2, 0.f); // La velocidad
        obstacle3.move(speed3, 0.f); // La velocidad

        // regresar el carro al principio
        if (obstacle1.getPosition().x > window.getSize().x) {
            obstacle1.setPosition(0.f, static_cast<float>(std::rand() % thirdOfScreen));
            speed1 = 0.8f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / 0.5f)); // cambio de velocidad
        }
        if (obstacle2.getPosition().x > window.getSize().x) {
            obstacle2.setPosition(0.f, static_cast<float>(thirdOfScreen + std::rand() % thirdOfScreen));
            speed2 = 0.2f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / 0.5f)); 
        }
        if (obstacle3.getPosition().x > window.getSize().x) {
            obstacle3.setPosition(0.f, static_cast<float>((2 * thirdOfScreen) + std::rand() % thirdOfScreen));
            speed3 = 0.5f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / 0.5f)); 
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
