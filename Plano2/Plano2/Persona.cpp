#include "Plano2.h"
#include <SFML/Graphics.hpp>

Persona::Persona(sf::Vector2u size) //este se usa para posicionar a el jugador (2 enteros sin asignar Vector2u)
{ 
	persona.setSize(sf::Vector2f(80.0f, 80.0f )); //vector con valores float
	persona.setPosition(sf::Vector2f(persona.getPosition().x, size.y - persona.getSize().y));
} 

void Persona::Dibujo(sf::RenderWindow *window) { //accesa la "window" original
	window->draw(persona);
}



void Persona::Mover(sf::Event event) {
	if (sf::Keyboard::Key::Left == event.key.code) //cuando se apriete la tecla se mueve
	{
		persona.move(-80, 0); //se mueve en eje x
	}
	else if(sf::Keyboard::Key::Right == event.key.code)
	{
		persona.move(80, 0); //se mueve en el eje x
	}
	else if (sf::Keyboard::Key::Up == event.key.code)
	{
		persona.move(0, -80); //se mueve en eje y
	}
	else if (sf::Keyboard::Key::Down == event.key.code) 
	{
		persona.move(0, 80); //se mueve en el eje y 
	}

}



sf::RectangleShape Persona::GetShape() { //tiene que regresar un rectangulo
	return persona; 
}
