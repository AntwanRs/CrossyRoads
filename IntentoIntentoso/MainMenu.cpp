/*#include "MainMenu.h"

//constructor
MainMenu::MainMenu(float ancho, float largo)
{
	
	MainMenuSelected = -1;
}

MainMenu::~MainMenu() {}

//Dibujamos menu
void MainMenu::draw(RenderWindow& window) {
	for (int i = 0; i < Max_main_menu; i++) {
		//window.draw([i); //cada opcion del menu principal en la ventana
	}
}

//mover en el menu pa arribita 
void MainMenu::MoveUp()
{
	//si la opcion selec no es -1, osea cualquiera
	//if (MainMenuSelected - 1 >= 0) {
		//mainMenu[MainMenuSelected].setFillColor(Color::White);

		//disminuimos el indice de opcion
		MainMenuSelected--;
		//si el indice es -1, o sea q no selecciono nada
		if (MainMenuSelected == -1) {
			//salimos
			MainMenuSelected = 2;
		}

		//mainMenu[MainMenuSelected].setFillColor(Color::Blue);
	}
}

//pa abajito ahora

void MainMenu::MoveDown()
{
	//q no se pase de la ocnstante de 4 opciones
	if (MainMenuSelected + 1 <= Max_main_menu) {
		//mainMenu[MainMenuSelected].setFillColor(Color::White);

		//aumentamos el indice de opcion
		MainMenuSelected++;
		//si el indice es 4, llego a tope
		if (MainMenuSelected == 4) {
			//bajamos a primera opcion
			MainMenuSelected = 0;
		}

		//mainMenu[MainMenuSelected].setFillColor(Color::Blue);
	}
}
*/