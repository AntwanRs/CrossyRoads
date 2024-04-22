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
	mainMenu[0].setFillColor(Color::White);
	mainMenu[0].setString("Play");
	mainMenu[0].setCharacterSize(70);
	mainMenu[0].setPosition(400, 200);

	//opciones
	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(Color::White);
	mainMenu[1].setString("Opciones");
	mainMenu[1].setCharacterSize(70);
	mainMenu[1].setPosition(400, 300);

	//controles
	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(Color::White);
	mainMenu[2].setString("Controles");
	mainMenu[2].setCharacterSize(70);
	mainMenu[2].setPosition(400, 400);

	//Salir
	mainMenu[3].setFont(font);
	mainMenu[3].setFillColor(Color::White);
	mainMenu[3].setString("Salir");
	mainMenu[3].setCharacterSize(70);
	mainMenu[3].setPosition(400, 500);

	// Inicializa la opción seleccionada del menú 
	// principal a -1 (ninguna opción seleccionada)
	MainMenuSelected = -1;
}

MainMenu::~MainMenu(){}

//Dibujamos menu
void MainMenu::draw(RenderWindow& window) {
	for (int i = 0; i < Max_main_menu; i++) {
		window.draw(mainMenu[i]); //cada opcion del menu principal en la ventana
	}
}

//mover en el menu pa arribita 
void MainMenu::MoveUp()
{
	//si la opcion selec no es -1, osea cualquiera
	if (MainMenuSelected - 1 >= 0) {
		mainMenu[MainMenuSelected].setFillColor(Color::White);

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

void MainMenu::MoveDown()
{
	//q no se pase de la ocnstante de 4 opciones
	if (MainMenuSelected + 1 <= Max_main_menu) {
		mainMenu[MainMenuSelected].setFillColor(Color::White);

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

