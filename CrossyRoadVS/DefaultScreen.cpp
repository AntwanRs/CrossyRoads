#include "DefaultScreen.h"

//constructor
DefaultScreen::DefaultScreen(float ancho, float largo)
{
	//cargamos la fuente q esta como en 3d d crossy road
	if (!font.loadFromFile("Fonts/Blox2.ttf")) {
		//en caso de que no se pueda cargar, avisa
		cout << "font de default no se encontro????????????" << endl;
	}
	iniciarPressed = false; // Inicializar como false

	titulo.setCharacterSize(300);
	titulo.setFont(font);
	titulo.setFillColor(Color::Black);
	titulo.setString("CROSSY ROAD");
	titulo.setPosition(200, 100);

	instrucciones.setCharacterSize(60);
	instrucciones.setFont(font);
	instrucciones.setFillColor(Color::Red);
	instrucciones.setString("Presione cualquier tecla para iniciar");
	instrucciones.setPosition(50, 300);

	Text personitas;
	personitas.setCharacterSize(40);
	personitas.setFont(font);
	personitas.setFillColor(Color::Blue);
	personitas.setString("Antwan /n Alicia /n Apodaca \n Alejandra");
	personitas.setPosition(50, 300);

	Text team;
	Text nose;

}

void DefaultScreen::draw(RenderWindow& window ) {
			window.draw(titulo); 
}

void DefaultScreen::setIniciarPressed(bool status) {
	iniciarPressed = status;
}

bool DefaultScreen::getIniciarPressed() {
	return iniciarPressed;
}

DefaultScreen::~DefaultScreen() {
	// Limpieza de recursos si es necesario
}