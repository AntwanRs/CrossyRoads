/*#include "Juego.h" //me dio miedo usar el new

Juego::Juego() {

	window = new sf::RenderWindow(sf::VideoMode(1800, 1200), "Intento");

	persona = new Persona(window->getSize());

	camion = new Camion(0, window->getSize().y / 2);
	camion2 = new Camion(560, window->getSize().y / 2);
	camion3 = new Camion(1000, window->getSize().y / 2);

	camion4 = new Camion(0, window->getSize().y / 4);
	camion5 = new Camion(500, window->getSize().y / 4);
	camion6 = new Camion(1000, window->getSize().y / 6);

};

void Juego::Ciclo() {

	while (window->isOpen()) {
		sf::Event event;

		// Maneja los eventos
		while (window->pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window->close();
				break;
			case sf::Event::KeyReleased:
				persona->Mover(event);
				break;
			}
		}

		// Actualizar objetos

		camion->Mover(window->getSize());
		camion2->Mover(window->getSize());
		camion3->Mover(window->getSize());

		camion4->Mover(window->getSize());
		camion5->Mover(window->getSize());
		camion6->Mover(window->getSize());

		// Detectar colisiones

		if (persona->GetShape().getGlobalBounds().intersects(camion->GetShape().getGlobalBounds())) {
			window->close();
		}

		if (persona->GetShape().getGlobalBounds().intersects(camion2->GetShape().getGlobalBounds())) {
			window->close();
		}

		if (persona->GetShape().getGlobalBounds().intersects(camion3->GetShape().getGlobalBounds())) {
			window->close();
		}

		if (persona->GetShape().getGlobalBounds().intersects(camion4->GetShape().getGlobalBounds())) {
			window->close();
		}

		if (persona->GetShape().getGlobalBounds().intersects(camion5->GetShape().getGlobalBounds())) {
			window->close();
		}

		if (persona->GetShape().getGlobalBounds().intersects(camion6->GetShape().getGlobalBounds())) {
			window->close();
		}
		// Dibujar objetos

		window->clear();

		camion->Dibujo(window);
		camion2->Dibujo(window);
		camion3->Dibujo(window);


		camion4->Dibujo(window);
		camion5->Dibujo(window);
		camion6->Dibujo(window);

		persona->Dibujo(window);

		window->display();
	}

	Juego::~Juego(); {
		delete camion;
		delete camion2;
		delete camion3;
		delete camion4;
		delete camion5;
		delete camion6;
		delete window;
	};
}*/

#include "Juego.h"

Juego::Juego() {
	window = new sf::RenderWindow(sf::VideoMode(1800, 1200), "Intento");

	// Create rectangle shapes for the road and sidewalk
	sf::RectangleShape road(sf::Vector2f(window->getSize().x, window->getSize().y / 2.0f));
	road.setFillColor(sf::Color(128, 128, 128)); // Light gray for road

	sf::RectangleShape sidewalk(sf::Vector2f(window->getSize().x / 5.0f, window->getSize().y / 2.0f));
	sidewalk.setFillColor(sf::Color(200, 200, 200)); // Lighter gray for sidewalk

	// Position the shapes
	sidewalk.setPosition(sf::Vector2f(0, window->getSize().y / 2.0f));
	road.setPosition(sf::Vector2f(0, 0));

	//inicializa y agrega camiones al vectorcito lindo >>>>>::((((((
	camiones.push_back(Camion(0, window->getSize().y / 2));
	camiones.push_back(Camion(700, window->getSize().y / 2));
	camiones.push_back(Camion(1000, window->getSize().y / 2));

	camiones.push_back(Camion(0, window->getSize().y / 4));
	camiones.push_back(Camion(900, window->getSize().y / 4));
	camiones.push_back(Camion(2000, window->getSize().y / 6));

	persona = new Persona(window->getSize());
}


void Juego::Ciclo() {
	while (window->isOpen()) {
		sf::Event event;

		// Maneja los eventos
		while (window->pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window->close();
				break;
			case sf::Event::KeyReleased:
				persona->Mover(event);
				break;
			}
		}

		// Actualizar objetos

		for (Camion& camion : camiones) {
			camion.Mover(window->getSize());
		}

		// Detectar colisiones

		for (Camion& camion : camiones) {
			if (persona->GetShape().getGlobalBounds().intersects(camion.GetShape().getGlobalBounds())) {
				window->close();
			}
		}

		// Dibujar objetos

		window->clear();
	}

		for (Camion& camion : camiones) {
			camion.Dibujo(window);
		}

		// Clear window and draw the shapes
		window->draw(camino);
		window->draw(acera);


		persona->Dibujo(window);

		window->display();
	}

