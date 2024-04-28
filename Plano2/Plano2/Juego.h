#pragma once
#include <SFML/Graphics.hpp>
#include "Plano2.h"
#include "Camion.h"

class Juego {


public:
	Juego();
	void Ciclo( );
	~Juego() {};

private:
	sf::RenderWindow *window;
	Persona *persona;
	std::vector<Camion> camiones;

};

