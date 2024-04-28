#pragma once
#include <SFML/Graphics.hpp>

class Camion {
private:
	sf::RectangleShape camion;

	float posOriginalX, posOriginalY;

public:
	Camion(float posX, float posY); //este se usa para posicionar a el jugador (2 enteros sin asignar Vector2u)
	
	void Dibujo(sf::RenderWindow*window);
	void Mover(sf::Vector2u size);

	sf::RectangleShape GetShape(); //tiene que regresar un rectangulo

};