#pragma once
#include <SFML/Graphics.hpp>

class Persona {
private:
	sf::RectangleShape persona;

	public :
		Persona(sf::Vector2u size ); //este se usa para posicionar a el jugador (2 enteros sin asignar Vector2u)
		void Dibujo(sf::RenderWindow*window);
		void Mover(sf::Event event);

		sf::RectangleShape GetShape( ); //tiene que regresar un rectangulo



};