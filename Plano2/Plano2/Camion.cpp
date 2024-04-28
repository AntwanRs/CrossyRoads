#include "Camion.h"
#include <SFML/Graphics.hpp>
#include <random>

Camion::Camion(float posX, float posY) {
	camion.setSize(sf::Vector2f(120, 60));

	// Aleatorizar el color del camion
	std::random_device generadorAleatorio; //Da numeros aleatorios no deterministas para inicializar otros generadores.
	std::mt19937 generadorMotor(generadorAleatorio());
	std::uniform_int_distribution<> distribucionUniforme(0, 255);

	int rojo = distribucionUniforme(generadorMotor);
	int verde = distribucionUniforme(generadorMotor);
	int azul = distribucionUniforme(generadorMotor);

	camion.setFillColor(sf::Color(rojo, verde, azul));

	camion.setPosition(sf::Vector2f(posX, posY)); // Pone a el camion fuera de la ventana

	posOriginalX = posX;
	posOriginalY = posY;
} //este se usa para posicionar a el jugador (2 enteros sin asignar Vector2u)

void Camion::Dibujo(sf::RenderWindow*window) {

	window->draw(camion);

}
void Camion::Mover(sf::Vector2u size) {
	float velocidadMin = 0.1; // Velocidad minima
	float velocidadMax = 0.5; // Velocidad maxima
	float velocidadAleatoria; // Variable para almacenar la velocidad aleatoria
	camion.move(0.2, 0.0);
	std::random_device rd; 
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(velocidadMin, velocidadMax);
	velocidadAleatoria = dis(gen);

	// Mover el camión con la velocidad aleatoria
	camion.move(velocidadAleatoria, 0.0);

	if (camion.getPosition().x > size.x) {
		camion.setPosition(sf::Vector2f(-camion.getSize().x, posOriginalY)); //resetea la posicion del camion para que siempre este pasando
	}

}

sf::RectangleShape Camion::GetShape() {
	return camion;

} //tiene que regresar un rectangulo

/*
#include "Camion.h"
#include <SFML/Graphics.hpp>
#include <random>

Camion::Camion(float posX, float posY) {
	camion.setSize(sf::Vector2f(120, 60));

	// Aleatorizar el color del camión
	std::random_device generadorAleatorio;
	std::mt19937 generadorMotor(generadorAleatorio());
	std::uniform_int_distribution<> distribucionUniforme(0, 255);

	int rojo = distribucionUniforme(generadorMotor);
	int verde = distribucionUniforme(generadorMotor);
	int azul = distribucionUniforme(generadorMotor);

	camion.setFillColor(sf::Color(rojo, verde, azul));

	camion.setPosition(sf::Vector2f(posX, posY)); // Pone a el camion fuera de la ventana

	posOriginalX = posX;
	posOriginalY = posY;
}

void Camion::Dibujo(sf::RenderWindow* window) {
	window->draw(camion);
}

void Camion::Mover(sf::Vector2u size) {
	float velocidadMin = 0.1;
	float velocidadMax = 0.5;
	float velocidadAleatoria;

	camion.move(0.2, 0.0);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(velocidadMin, velocidadMax);
	velocidadAleatoria = dis(gen);

	// Mover el camión con la velocidad aleatoria
	camion.move(velocidadAleatoria, 0.0);

	if (camion.getPosition().x > size.x) {
		camion.setPosition(sf::Vector2f(-camion.getSize().x, posOriginalY)); // Resetea la posición del camión para que siempre esté pasando
	}
}

sf::RectangleShape Camion::GetShape() {
	return camion;
}

bool Camion::DetectarColision(const sf::RectangleShape& jugador) {
	return camion.getGlobalBounds().intersects(jugador.getGlobalBounds());
}*/