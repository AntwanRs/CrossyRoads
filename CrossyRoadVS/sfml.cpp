#include <SFML/Graphics.hpp>
#include "MainMenu.h"
using namespace sf;

//aqui esta creando la pantalla del tamaño especificadoooooooooo
//videomode usa el sf
//funcion principal
int main() {
	//ventana de renderizado MENU 960X720 LLAMADA MAIN MEN
	RenderWindow MENU(VideoMode(960, 720), "Main Menu", Style::Default);
	//Objwto de la clase mainmenu llamado mainmenu con el tamaño de la ventana menu
	MainMenu mainMenu(MENU.getSize().x, MENU.getSize().y);

	//background
	RectangleShape background;
	background.setSize(Vector2f(960, 720));
	Texture Maintexture;
	Maintexture.loadFromFile("Texture/Background.jpeg");
	background.setTexture(&Maintexture);

	/*foto al juego
	RectangleShape playBackground;
	playBackground.setSize(Vector2f(960, 720));
	Texture back_texture;
	back_texture loadFromFiles("Texture/PlayBackground.jpeg")*/

	

	//mientras la ventana menu este abierta
	while (MENU.isOpen()) {
		Event event; //objeto event de clase event
		//true si regresa event
		//mientras haya eventos en al cola de eventos de la ventana MENU
		while (MENU.pollEvent(event)) {

			//cout << "EVent check" << endl;

			//si el evento es tipo closed 
			if (event.type == Event::Closed()) {
				MENU.close(); //CIERRA LA VENTANAAAAAAA MENU
			}
			//Si el evento es de tipo keyreleased (se echo una tecla)
			if (event.type == Event::KeyReleased) {
				//si es arriba
				if (event.key.code == Keyboard::Up) {
					mainMenu.MoveUp(); // pues mueves arriba el menu
					break;
				}
				//si la tecla q echaron es down
				if (event.key.code == Keyboard::Down) {
					mainMenu.MoveDown(); // pa abajo
					break;
				}
				//si la tecla es un return o enter 
				if (event.key.code == Keyboard::Return) {
					//hacemos 3 ventanas de renderizado
					//con titulo y 960x720
					RenderWindow Play(VideoMode(960, 720), "nombre_juego");
					RenderWindow OPCIONES(VideoMode(960, 720), "OPCIONES");
					RenderWindow CONTROLES(VideoMode(960, 720), "CONTROLES");

					//indice de la opcion select del main menu 
					int x = mainMenu.MainMenuPressed();
					//si es 0
					if (x == 0) {
						//mientras este abierta la ventanilla play
						while (Play.isOpen())
						{
							Event aevent;//creamos objeto de la clase event llamado aevent
							//mientras haya eventos en la cola de eventos de la ventana play
							while (Play.pollEvent(aevent)) {
								//si el evento esta cerrado 
								if (aevent.type == Event::Closed) {

									Play.close();//cierra la ventana de play
								}
								//si hay tecla..
								if (aevent.type == Event::KeyPressed)
									//si la tecla es escape
									if (aevent.key.code == Keyboard::Escape) {
										Play.close(); //cerramos play
									}
							}
						}
						//cerramos opciones
						OPCIONES.close();

						//cerramos ventana de controles
						CONTROLES.close();

						//limpiamos ventana play
						Play.clear();

						//Muestra ventana play
						Play.display();
					}
					//si es la segunda opcion
					if (x == 1) {
						//mientras opciones este abierta
						while (OPCIONES.isOpen()) {
							Event aevent;
							//mientras haya eventos en la cola de eventos de la ventana opciones
							while (OPCIONES.pollEvent(aevent)) {
								// si el evento esta cerradi 
								if (aevent.type == Event::Closed) {
									OPCIONES.close(); //cerramos ventana
								}
								//si hay tecla
								if (aevent.type == Event::KeyPressed) {

									//escape
									if (aevent.key.code == Keyboard::Escape) {
										OPCIONES.close(); //CERRAMOOOOOOOS
									}
								}
							}
							Play.close(); // cierra ventana play

							OPCIONES.clear(); // limpia ventana opciones

							CONTROLES.close(); // cierra la ventana controles

							OPCIONES.display(); // muestra la ventana opciones
						}
					}
					// si es la tercera opcion
					if (x == 2) {
						//mientras la venta control este abierta
						while (CONTROLES.isOpen()) {
							Event aevent;
							//mientras haya eventos en la cola de eventos de la ventana controles
							while (CONTROLES.pollEvent(aevent))
							{
								if (aevent.type == Event::Closed)
								{
									CONTROLES.close();
								}
								if (aevent.type == Event::KeyPressed) {
									if (aevent.key.code == Keyboard::Escape) {
										CONTROLES.close();
									}
								}
							}
							Play.close();
							OPCIONES.clear();
							CONTROLES.clear();
						}
					}
					if (x == 3)
						MENU.close();
					break;
				}
			}
		}
		MENU.clear();
		MENU.draw(background);
		mainMenu.draw(MENU);
		MENU.display();
		
	}
	return 0;
}