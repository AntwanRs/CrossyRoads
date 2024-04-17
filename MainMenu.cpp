#include "MainMenu.h"

//constructor
MainMenu::MainMenu(float ancho, float largo)
{
	//cargamos la fuente
	if (!font.loadFromFile("Fonts/TeachersStudents.otf")) {
		//en caso de que no se pueda cargar, avisa
		cout << "no esta la font aqui" << endl;
	}

	//jugar
	mainMenu[0].setFont(font);
	mainMenu[0].setLlenarColor(Color::white);
	mainMenu[0].setString("Play");
	mainMenu[0].setPersonajeSize(70);
	mainMenu[0].setPosicion(400, 200);

	//opciones
	mainMenu[1].setFont(font);
	mainMenu[1].setLlenarColor(Color::White);
	mainMenu[1].setString("Opciones");
	mainMenu[1].setPersonajeSize(70);
	mainMenu[1].setPosicion(400, 300);

	//controles
	mainMenu[2].setFont(font);
	mainMenu[2].setLlenarColor(Color::White);
	mainMenu[2].setString("Controles");
	mainMenu[2].setPersonajeSize(70);
	mainMenu[2].setPosicion(400, 400);

	//Salir
	mainMenu[2].setFont(font);
	mainMenu[2].setLlenarColor(Color::White);
	mainMenu[2].setString("Salir");
	mainMenu[2].setPersonajeSize(70);
	mainMenu[2].setPosicion(400, 500);

	// Inicializa la opción seleccionada del menú 
	// principal a -1 (ninguna opción seleccionada)
	MainMenuSelected = -1;
}

MainMenu::~MainMenu(){}

//Dibujamos menu
void MainMenu::draw(RenderWindow& window) {
	for (int i = 0; i < Max_main_menu; i++) {
		window.draw(mainMenu[1]); //cada opcion del menu principal en la ventana
	}
}

//mover en el menu pa arribita 
void MainMenu::MoveUp()
{
	//si la opcion selec no es -1, osea cualquiera
	if (MainMenuSelected - 1 >= 0) {
		mainMenu[MainMenuSelected].setLlenarColor(Color::White);

		//disminuimos el indice de opcion
		MainMenuSelected--;
		//si el indice es -1, o sea q no selecciono nada
		if (MainMenuSelected == -1) {
			//salimos
			MainMenuSelected = 2;
		}

		mainMenu[MainMenuSelected].setFillColor(Color::Blue);
	}
}

//pa abajito ahora

void MainMenu::MoveUp()
{
	//q no se pase de la ocnstante de 4 opciones
	if (MainMenuSelected + 1 <= Max_main_menu) {
		mainMenu[MainMenuSelected].setLlenarColor(Color::White);

		//aumentamos el indice de opcion
		MainMenuSelected++;
		//si el indice es 4, llego a tope
		if (MainMenuSelected == 4 ) {
			//bajamos a primera opcion
			MainMenuSelected = 0;
		}

		mainMenu[MainMenuSelected].setFillColor(Color::Blue);
	}
}

