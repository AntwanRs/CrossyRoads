#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "DefaultScreen.h"

using namespace sf;

//aqui esta creando la pantalla del tamaño especificadoooooooooo
//videomode usa el sf
//funcion principal
int main() {

	//ventana de renderizado window 960X720 
	RenderWindow window(VideoMode(960, 720), "Default ", Style::Default);
	DefaultScreen defaultScreen(window.getSize().x, window.getSize().y);
	
	//MainMenu mainMenu(window.getSize().x, window.getSize().y);

	//defulttt fotito pantalla
	// ola (- Alan)
	RectangleShape defaultBackground;
	defaultBackground.setSize(Vector2f(960, 720));
	//obj
	Texture defaultTexture;
	defaultTexture.loadFromFile("Texture/Default.jpeg");
	
	// Sprite para cargar la textura, se puede usar rectangulo tambien
	Sprite defaultSprite;
	// Se pone la posicion en 0,0 es decir la esquina
	defaultSprite.setPosition(0, 0);
	// Se asigna la textura
	defaultSprite.setTexture(defaultTexture);
	// Se escala la textura (2000 x 2000) para que quede con la ventana(960 x 720) (960/2000, 720/2000)

	defaultSprite.setScale(.475, .36);
	//direcc de la imagennn
	defaultBackground.setTexture(&defaultTexture);

	//background
	RectangleShape background;
	background.setSize(Vector2f(960, 720));
	Texture menuTexture;
	menuTexture.loadFromFile("Texture/Menu.jpeg");
	background.setTexture(&menuTexture);

	/*foto al juego
	RectangleShape playBackground;
	playBackground.setSize(Vector2f(960, 720));
	Texture back_texture;
	back_texture loadFromFiles("Texture/PlayBackground.jpeg")*/

	//VARIABLE IMPORTANTISIMAAAA!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1111!!!!!!!
	//con esta sabemos si necesitamos mostrar el menu con puro booool

	/*
	
	Considero que quedaria mejor si inicia directamente en el menu (Alan)
	
	*/
	bool showMainMenu = false;
	MainMenu mainMenu(window.getSize().x, window.getSize().y);

	// cilco principal del juego
		while (window.isOpen()) {
			Event event;
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed)
					window.close();

				// Cambiar a la pantalla del menu principal cuando se presione cualquier tecla
				if (event.type == Event::KeyPressed) {
					showMainMenu = true;
				}
			}

			window.clear();

			window.draw(defaultSprite);

			//  pantalla por defecto o menu segun el bool
			if (showMainMenu) {
				// meniuuuu 
				RenderWindow MENU(VideoMode(960, 720), "Main Menu", Style::Default);
				//MainMenu mainMenu(window.getSize().x, window.getSize().y);

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
								break; //no se si va esto aqui?
							}
							//si la tecla q echaron es down
							if (event.key.code == Keyboard::Down) {
								mainMenu.MoveDown(); // pa abajo
								break; //igual q esto
							}
							//si la tecla es un return o enter 
							if (event.key.code == Keyboard::Return) {
								//hacemos 3 ventanas de renderizado
								//con titulo y 960x720
								RenderWindow Play(VideoMode(960, 720), "PLEYYYYCROSSY");
								RenderWindow PERSONAJES(VideoMode(960, 720), "PERSONAJES");
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
									PERSONAJES.close();

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
									while (PERSONAJES.isOpen()) {
										Event aevent;
										//mientras haya eventos en la cola de eventos de la ventana opciones
										while (PERSONAJES.pollEvent(aevent)) {
											// si el evento esta cerradi 
											if (aevent.type == Event::Closed) {
												PERSONAJES.close(); //cerramos ventana
											}
											//si hay tecla
											if (aevent.type == Event::KeyPressed) {

												//escape
												if (aevent.key.code == Keyboard::Escape) {
													PERSONAJES.close(); //CERRAMOOOOOOOS
												}
											}
										}
										Play.close(); // cierra ventana play

										PERSONAJES.clear(); // limpia ventana opciones

										CONTROLES.close(); // cierra la ventana controles

										PERSONAJES.display(); // muestra la ventana opciones
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
										PERSONAJES.clear();
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

			}
window.display();

		}

	
	return 0;
}