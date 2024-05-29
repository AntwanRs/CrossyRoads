#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace sf;
using namespace std;


sf::Texture carroTexture;

#define Max_main_menu 4
const int anchoVentana = 1920;
const int altoVentana = 1200;
const float velocidadJugador = 300.0f;
float velocidadMinimaCarroInicial = 150.0f;
float velocidadMaximaCarroInicial = 400.0f;
const float limiteReinicio = -200.0f;
const float espacioEntreCarros = 200.0f;
const float retrasoSpawnCarro = 0.30f; //No se porque, no entiendo porque pero nunca quitar esto
const int numLineasCarretera = 5;
const int grosorLineaCarretera = 5;
const float distanciaMinimaCarros = 80.0f;
const float tiempoLimiteInactividad = 30.0f;
const sf::Time tiempoGameOver = sf::seconds(10.0f); // Tiempo que se muestra la ventana de Game Over

struct ZonaSegura {
    sf::Vector2f posicion;
    sf::Vector2f tamano;
};

enum class TipoEntidad { Jugador, Carro };

class MainMenu {
private:
    int MainMenuSelected;
    Font font;
    Text mainMenu[Max_main_menu];
    RenderWindow* window;

public:
    MainMenu(RenderWindow& win) : window(&win), MainMenuSelected(-1)
    {
        if (!font.loadFromFile("Pixel.otf")) {
            cout << "No se pudo cargar la fuente" << endl;
        }

        mainMenu[0].setFont(font);
        mainMenu[0].setFillColor(Color::Blue);
        mainMenu[0].setString("Play");
        mainMenu[0].setCharacterSize(200);
        mainMenu[0].setPosition(700, 100);

        mainMenu[1].setFont(font);
        mainMenu[1].setFillColor(Color::Blue);
        mainMenu[1].setString("Personajes");
        mainMenu[1].setCharacterSize(200);
        mainMenu[1].setPosition(350, 350);

        mainMenu[2].setFont(font);
        mainMenu[2].setFillColor(Color::Blue);
        mainMenu[2].setString("Salir");
        mainMenu[2].setCharacterSize(200);
        mainMenu[2].setPosition(690, 600);

        mainMenu[3].setFont(font);
        mainMenu[3].setFillColor(Color::Blue);
        mainMenu[3].setString("");
        mainMenu[3].setCharacterSize(70);
        mainMenu[3].setPosition(395, 390);
    }

    void draw()
    {
        for (int i = 0; i < Max_main_menu; i++) {
            window->draw(mainMenu[i]);
        }
    }

    void MoveUp()
    {
        if (MainMenuSelected - 1 >= 0) {
            mainMenu[MainMenuSelected].setFillColor(Color::Blue);
            MainMenuSelected--;
            if (MainMenuSelected == -1) {
                MainMenuSelected = Max_main_menu - 1;
            }
            mainMenu[MainMenuSelected].setFillColor(Color::Black);
        }
    }

    void MoveDown()
    {
        if (MainMenuSelected + 1 < Max_main_menu) {
            mainMenu[MainMenuSelected].setFillColor(Color::Blue);
            MainMenuSelected++;
            if (MainMenuSelected == Max_main_menu) {
                MainMenuSelected = 0;
            }
            mainMenu[MainMenuSelected].setFillColor(Color::Black);
        }
    }

    int MainMenuPressed() { return MainMenuSelected; }

    ~MainMenu() {}
};

class SeleccionPersonaje {
private:
    sf::RenderWindow window{ sf::VideoMode(1920, 1200), "Seleccionar personaje" };
    sf::Font font;
    sf::Texture textura_fondo;
    sf::Sprite sprite_fondo;
    sf::Text text;
    sf::Texture textura_apo;
    sf::Texture textura_ant;
    sf::Texture textura_ale;
    sf::Texture textura_alicia;
    sf::Sprite sprite_apo;
    sf::Sprite sprite_ant;
    sf::Sprite sprite_ale;
    sf::Sprite sprite_alicia;
    sf::Text text_apo;
    sf::Text text_ant;
    sf::Text text_ale;
    sf::Text text_alicia;
    sf::Text text_tecla_apo;
    sf::Text text_tecla_ant;
    sf::Text text_tecla_ale;
    sf::Text text_tecla_alicia;
    std::string personajeSeleccionado;
    sf::Texture textura_seleccionada; // Textura seleccionada del jugador

public:
    SeleccionPersonaje() {
        if (!font.loadFromFile("Pixel.otf")) {
            std::cerr << "Error al cargar la fuente " << std::endl;
            return;
        }

        if (!textura_fondo.loadFromFile("Fondo.png")) {
            std::cerr << "Error al cargar la imagen de fondo" << std::endl;
            return;
        }

        if (!textura_apo.loadFromFile("personaje1.png") ||
            !textura_ant.loadFromFile("personaje2.png") ||
            !textura_ale.loadFromFile("personaje3.png") ||
            !textura_alicia.loadFromFile("personaje4.png")) {
            std::cerr << "Error al cargar las texturas de los personajes" << std::endl;
            return;
        }

        sprite_fondo.setTexture(textura_fondo);
        sprite_fondo.setScale(window.getSize().x / sprite_fondo.getLocalBounds().width, window.getSize().y / sprite_fondo.getLocalBounds().height);

        text.setFont(font);
        text.setString("Selecciona tu personaje");
        text.setCharacterSize(100);
        text.setFillColor(sf::Color::Blue);

        sf::FloatRect limitesTexto = text.getLocalBounds();
        text.setOrigin(limitesTexto.left + limitesTexto.width / 2.0f, limitesTexto.top + limitesTexto.height / 2.0f);
        text.setPosition(window.getSize().x / 2.0f, 200);

        sprite_apo.setTexture(textura_apo);
        sprite_ant.setTexture(textura_ant);
        sprite_ale.setTexture(textura_ale);
        sprite_alicia.setTexture(textura_alicia);

        sprite_apo.setScale(2.5f, 2.5f);
        sprite_ant.setScale(2.5f, 2.5f);
        sprite_ale.setScale(2.5f, 2.5f);
        sprite_alicia.setScale(2.5f, 2.5f);

        sprite_apo.setPosition(window.getSize().x / 8.0f - sprite_apo.getGlobalBounds().width / 2, 450);
        sprite_ant.setPosition(window.getSize().x / 8.0f * 3 - sprite_ant.getGlobalBounds().width / 2, 450);
        sprite_ale.setPosition(window.getSize().x / 8.0f * 5 - sprite_ale.getGlobalBounds().width / 2, 450);
        sprite_alicia.setPosition(window.getSize().x / 8.0f * 7 - sprite_alicia.getGlobalBounds().width / 2, 450);

        text_apo.setFont(font);
        text_ant.setFont(font);
        text_ale.setFont(font);
        text_alicia.setFont(font);

        text_apo.setString("Apo");
        text_ant.setString("Ant");
        text_ale.setString("Ale");
        text_alicia.setString("Alicia");

        text_apo.setCharacterSize(50);
        text_ant.setCharacterSize(50);
        text_ale.setCharacterSize(50);
        text_alicia.setCharacterSize(50);

        text_apo.setFillColor(sf::Color::White);
        text_ant.setFillColor(sf::Color::White);
        text_ale.setFillColor(sf::Color::White);
        text_alicia.setFillColor(sf::Color::White);

        text_apo.setPosition(sprite_apo.getPosition().x + sprite_apo.getGlobalBounds().width / 2 - text_apo.getGlobalBounds().width / 2, sprite_apo.getPosition().y + sprite_apo.getGlobalBounds().height + 10);
        text_ant.setPosition(sprite_ant.getPosition().x + sprite_ant.getGlobalBounds().width / 2 - text_ant.getGlobalBounds().width / 2, sprite_ant.getPosition().y + sprite_ant.getGlobalBounds().height + 10);
        text_ale.setPosition(sprite_ale.getPosition().x + sprite_ale.getGlobalBounds().width / 2 - text_ale.getGlobalBounds().width / 2, sprite_ale.getPosition().y + sprite_ale.getGlobalBounds().height + 10);
        text_alicia.setPosition(sprite_alicia.getPosition().x + sprite_alicia.getGlobalBounds().width / 2 - text_alicia.getGlobalBounds().width / 2, sprite_alicia.getPosition().y + sprite_alicia.getGlobalBounds().height + 10);

        text_apo.setOutlineColor(sf::Color::Black);
        text_apo.setOutlineThickness(0);
        text_ant.setOutlineColor(sf::Color::Black);
        text_ant.setOutlineThickness(0);
        text_ale.setOutlineColor(sf::Color::Black);
        text_ale.setOutlineThickness(0);
        text_alicia.setOutlineColor(sf::Color::Black);
        text_alicia.setOutlineThickness(0);

        // Configuración de las teclas
        text_tecla_apo.setFont(font);
        text_tecla_ant.setFont(font);
        text_tecla_ale.setFont(font);
        text_tecla_alicia.setFont(font);

        text_tecla_apo.setString("Left");
        text_tecla_ant.setString("Right");
        text_tecla_ale.setString("Up");
        text_tecla_alicia.setString("Down");

        text_tecla_apo.setCharacterSize(30);
        text_tecla_ant.setCharacterSize(30);
        text_tecla_ale.setCharacterSize(30);
        text_tecla_alicia.setCharacterSize(30);

        text_tecla_apo.setFillColor(sf::Color::Yellow);
        text_tecla_ant.setFillColor(sf::Color::Yellow);
        text_tecla_ale.setFillColor(sf::Color::Yellow);
        text_tecla_alicia.setFillColor(sf::Color::Yellow);

        text_tecla_apo.setPosition(sprite_apo.getPosition().x + sprite_apo.getGlobalBounds().width / 2 - text_tecla_apo.getGlobalBounds().width / 2, text_apo.getPosition().y + text_apo.getGlobalBounds().height + 10);
        text_tecla_ant.setPosition(sprite_ant.getPosition().x + sprite_ant.getGlobalBounds().width / 2 - text_tecla_ant.getGlobalBounds().width / 2, text_ant.getPosition().y + text_ant.getGlobalBounds().height + 10);
        text_tecla_ale.setPosition(sprite_ale.getPosition().x + sprite_ale.getGlobalBounds().width / 2 - text_tecla_ale.getGlobalBounds().width / 2, text_ale.getPosition().y + text_ale.getGlobalBounds().height + 10);
        text_tecla_alicia.setPosition(sprite_alicia.getPosition().x + sprite_alicia.getGlobalBounds().width / 2 - text_tecla_alicia.getGlobalBounds().width / 2, text_alicia.getPosition().y + text_alicia.getGlobalBounds().height + 10);
    }

    int iniciar() {
        int indicePersonajeSeleccionado = -1;
        int ultimoPersonajeSeleccionado = -1;

        while (window.isOpen()) { // Bucle principal
            sf::Event evento;
            while (window.pollEvent(evento)) {
                if (evento.type == sf::Event::Closed) {
                    // Cerrar la ventana si se presiona el botón de cerrar
                    window.close();
                }
            }

            // Restablecer colores de texto
            text_apo.setFillColor(sf::Color::White);
            text_ant.setFillColor(sf::Color::White);
            text_ale.setFillColor(sf::Color::White);
            text_alicia.setFillColor(sf::Color::White);

            // Verificar la entrada del teclado y resaltar el personaje seleccionado
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                text_apo.setFillColor(sf::Color::Blue);
                indicePersonajeSeleccionado = 1;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                text_ant.setFillColor(sf::Color::Blue);
                indicePersonajeSeleccionado = 2;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                text_ale.setFillColor(sf::Color::Blue);
                indicePersonajeSeleccionado = 3;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                text_alicia.setFillColor(sf::Color::Blue);
                indicePersonajeSeleccionado = 4;
            }

            // Mantener el último personaje seleccionado resaltado en azul
            if (indicePersonajeSeleccionado != ultimoPersonajeSeleccionado) {
                switch (ultimoPersonajeSeleccionado) {
                case 1:
                    text_apo.setFillColor(sf::Color::Blue);
                    break;
                case 2:
                    text_ant.setFillColor(sf::Color::Blue);
                    break;
                case 3:
                    text_ale.setFillColor(sf::Color::Blue);
                    break;
                case 4:
                    text_alicia.setFillColor(sf::Color::Blue);
                    break;
                default:
                    break;
                }
                ultimoPersonajeSeleccionado = indicePersonajeSeleccionado;
            }

            // Verificar si se ha seleccionado un personaje y se ha presionado la tecla espaciadora
            if (indicePersonajeSeleccionado != -1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                window.close(); // Cerrar la ventana al presionar Space
                return indicePersonajeSeleccionado;
            }

            // Dibujar
            window.clear();
            window.draw(sprite_fondo);
            window.draw(text);
            window.draw(sprite_apo);
            window.draw(sprite_ant);
            window.draw(sprite_ale);
            window.draw(sprite_alicia);
            window.draw(text_apo);
            window.draw(text_ant);
            window.draw(text_ale);
            window.draw(text_alicia);
            window.draw(text_tecla_apo);
            window.draw(text_tecla_ant);
            window.draw(text_tecla_ale);
            window.draw(text_tecla_alicia);
            window.display();
        }

        return 1;
    }

};
//clase padrastra
class Entidad {
public:
    virtual void randomizar() = 0;
    virtual TipoEntidad getTipo() const = 0;
    virtual bool colision(const sf::RectangleShape& jugador) const = 0;
    virtual sf::Vector2f getPosition() const = 0;
    virtual sf::Vector2f getSize() const = 0;
    virtual void setPosition(const sf::Vector2f& position) = 0;
    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual void update(float deltaTime) = 0;
    virtual ~Entidad() {}
};

//clase hijilla
class Carro : public Entidad {
private:
    sf::Sprite forma;
    float velocidad;

public:
    Carro(float velocidadBase, float posY, sf::Texture& texture)
        : velocidad(velocidadBase) {
        forma.setTexture(texture);
        forma.setScale(0.4f, 0.4f);
        forma.setPosition(-150.0f, posY);
    }

    void randomizar() override {}

    TipoEntidad getTipo() const override {
        return TipoEntidad::Carro;
    }

    bool colision(const sf::RectangleShape& jugador) const override {
        return forma.getGlobalBounds().intersects(jugador.getGlobalBounds());
    }

    sf::Vector2f getPosition() const override {
        return forma.getPosition();
    }

    sf::Vector2f getSize() const override {
        return sf::Vector2f(forma.getGlobalBounds().width, forma.getGlobalBounds().height);
    }

    void setPosition(const sf::Vector2f& position) override {
        forma.setPosition(position);
    }

    void move(float deltaX, float deltaY) {
        forma.move(deltaX, deltaY);
    }

    void draw(sf::RenderWindow& window) const override {
        window.draw(forma);
    }

    void update(float deltaTime) override {
        forma.move(velocidad * deltaTime, 0.0f);
    }
};

void generarZonaSegura(ZonaSegura& zonaSegura) {
    zonaSegura.tamano.x = anchoVentana;
    zonaSegura.tamano.y = 200.0f; // Altura fija para la zona segura, ajusta según necesites
    zonaSegura.posicion.x = 0;
    zonaSegura.posicion.y = rand() % (altoVentana - static_cast<int>(zonaSegura.tamano.y));
}


//funcion para reiniciar el juego cuando se llega al bound fuera de la vista del jugador
void reiniciarJuego(sf::RectangleShape& jugador, std::vector<Entidad*>& entidades, std::vector<bool>& carrilesOcupados, ZonaSegura& zonaSegura) {
    jugador.setPosition(anchoVentana / 2 - jugador.getSize().x / 2, altoVentana - jugador.getSize().y);
    std::fill(carrilesOcupados.begin(), carrilesOcupados.end(), false);

    velocidadMinimaCarroInicial += 50.0f;
    velocidadMaximaCarroInicial += 50.0f;

    for (auto& entidad : entidades) {
        delete entidad;
    }
    entidades.clear();

    for (int i = 0; i < numLineasCarretera; ++i) {
        carrilesOcupados.push_back(false);
    }

    generarZonaSegura(zonaSegura); // Generar una nueva zona segura

    // Generar carros inicialmente fuera de la pantalla
    float posY = 0.0f;
    for (int i = 0; i < carrilesOcupados.size(); ++i) {
        posY = i * espacioEntreCarros;
        Carro* nuevoCarro = new Carro(0.0f, posY, carroTexture);
        nuevoCarro->setPosition(sf::Vector2f(-150.0f, posY));
        entidades.push_back(nuevoCarro);
    }
}

// Función para eliminar carros dentro de la zona segura
void eliminarCarrosEnZonaSegura(std::vector<Entidad*>& entidades, const ZonaSegura& zonaSegura) {
    auto it = entidades.begin();
    while (it != entidades.end()) {
        if ((*it)->getTipo() == TipoEntidad::Carro) {
            sf::Vector2f carroPos = (*it)->getPosition();
            sf::Vector2f carroSize = (*it)->getSize();

            // Aumentar el área de detección para incluir una parte del carro
            sf::FloatRect areaDeteccion(carroPos.x, carroPos.y, carroSize.x, carroSize.y * 0.75f);

            // Verificar si alguna parte del carro está dentro de la zona segura
            if (zonaSegura.posicion.y <= areaDeteccion.top + areaDeteccion.height &&
                zonaSegura.posicion.y + zonaSegura.tamano.y >= areaDeteccion.top &&
                zonaSegura.posicion.x <= areaDeteccion.left + areaDeteccion.width &&
                zonaSegura.posicion.x + zonaSegura.tamano.x >= areaDeteccion.left) {
                std::cout << "Carro eliminado dentro de la zona segura" << std::endl;
                delete* it;
                it = entidades.erase(it);
                continue;
            }
        }
        ++it;
    }
}

//cuando hay colision morirrrs
bool hayColisionJugadorCarro(const sf::RectangleShape& jugador, const std::vector<Entidad*>& entidades) {
    for (const auto& entidad : entidades) {
        if (entidad->getTipo() == TipoEntidad::Carro) {
            if (entidad->colision(jugador)) {
                return true;
            }
        }
    }
    return false;
}

void eliminarCarrosFueraDePantalla(std::vector<Entidad*>& entidades) {
    auto it = entidades.begin();
    while (it != entidades.end()) {
        if ((*it)->getTipo() == TipoEntidad::Carro) {
            if ((*it)->getPosition().x > anchoVentana) {
                delete* it;
                it = entidades.erase(it);
                continue;
            }
        }
        ++it;
    }
}


void gameOver() {
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Game Over");

    // cargar texturas
    sf::Texture texture1, texture2;
    if (!texture1.loadFromFile("Gameover1.png") || !texture2.loadFromFile("Gameover2.png")) {
        std::cerr << "Error cargando las imagenes" << std::endl;
        return;
    }

    // cargar efecto de sonido
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("over.mp3")) {
        std::cerr << "Error cargando el sonido over.mp3 noooooooooooo" << std::endl;
        return;
    }
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();

    sf::Sprite sprite(texture1);

    // Calcular la escala basada en las dimensiones de la ventana y la imagen original
    float scaleX = 1600.f / 1920.f;
    float scaleY = 900.f / 1080.f;
    sprite.setScale(scaleX, scaleY);

    sf::Time tiempoEspera = sf::milliseconds(500); // 500ms delay para cambiar imagenes
    sf::Clock reloj;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed)
                window.close();
        }

        if (reloj.getElapsedTime() > tiempoEspera) {
            if (sprite.getTexture() == &texture1) {
                sprite.setTexture(texture2);
            }
            else {
                sprite.setTexture(texture1);
            }
            // Aplicar la escala nuevamente después de cambiar la textura
            sprite.setScale(scaleX, scaleY);
            reloj.restart();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }
}

 int main() {
        RenderWindow window(VideoMode(1800, 1000), "Crossy", Style::Default);
        //sf::Sprite jugadorSprite;     

        sf::Music musicaFondo;
        if (!musicaFondo.openFromFile("musicFondo.wav")) {
            std::cerr << "Error al cargar el archivo de música" << std::endl;
            // Manejar el error, como salir del programa o continuar sin música
        }

        sf::Font font;
        if (!font.loadFromFile("Pixel.otf")) {
            std::cerr << "Error al cargar la fuente" << std::endl;
            return 1; // Salir del programa con código de error
        }

        sf::Text textoScore;
        textoScore.setFont(font);

        int personajeSeleccionado = 0;

        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile("efectoColision.wav")) {
            // Manejo de error si no se puede cargar el archivo
            return EXIT_FAILURE;
        }

        // Crear una instancia de sf::Sound y asignarle el buffer cargado
        sf::Sound colision;
        colision.setBuffer(buffer);


        Texture defaultTexture;

        if (!defaultTexture.loadFromFile("Crss.jpg")) {
            cerr << "no se cargo mams" << endl;
            return -1;
        }
        Sprite defaultSprite(defaultTexture);
        //defaultSprite.setScale(0.75f, 0.5625f);

         // Calcular la escala basada en las dimensiones de la ventana y la imagen original
        float scaleX = 1800.f / 1920.f;
        float scaleY = 1000.f / 1080.f;
        defaultSprite.setScale(scaleX, scaleY);

        Texture menuTexture;
        if (!menuTexture.loadFromFile("imagenFondo.png")) {
            cerr << "esta tampico" << endl;
            return -1;
        }

        sf::Clock contadorTiempo; // Se inicia el contador de tiempo

        Sprite menuSprite(menuTexture);
        //menuSprite.setScale(0.75f, 0.5625f); // Escalar si es necesario

        MainMenu mainMenu(window);
        sf::RectangleShape jugador(sf::Vector2f(90.0f, 150.0f)); // Esto se puede modificar

        bool showMainMenu = false;
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed)
                    window.close();

                if (event.type == Event::KeyPressed) {
                    showMainMenu = true;
                }
            }

            window.clear();
            window.draw(defaultSprite);


            if (showMainMenu) {


                window.clear();
                window.draw(menuSprite); // Dibujar la imagen de fondo del menú
                mainMenu.draw(); // Dibujar los elementos del menú
                while (window.isOpen()) {
                    sf::Time deltaTiempo = contadorTiempo.restart();

                    Event event;
                    while (window.pollEvent(event)) {
                        if (event.type == Event::Closed) {
                            window.close();
                        }
                        if (event.type == Event::KeyReleased) {
                            if (event.key.code == Keyboard::Up) {
                                mainMenu.MoveUp();
                                break;
                            }
                            if (event.key.code == Keyboard::Down) {
                                mainMenu.MoveDown();
                                break;
                            }
                            if (event.key.code == Keyboard::Return) {
                                int x = mainMenu.MainMenuPressed();
                            
                              if (x == 1) {
                                  SeleccionPersonaje seleccionPersonaje;

                                  int indicePersonajeSeleccionado = seleccionPersonaje.iniciar();
                                  if (indicePersonajeSeleccionado != -1) {
                                      // Cargar la textura del personaje seleccionado
                                      sf::Texture* texturaPersonaje = new sf::Texture();
                                      if (!texturaPersonaje->loadFromFile("personaje" + std::to_string(indicePersonajeSeleccionado) + ".png")) {
                                          std::cerr << "Error al cargar la textura del personaje seleccionado" << std::endl;
                                          return -1;
                                      }
                                      // Asignar la textura del jugador
                                      jugador.setTexture(texturaPersonaje);
                                  
                                  }
                                  break;
                                }
                              else if (x == 0) {
                                  // Playyyyyyyyy
                                  if (jugador.getTexture() == nullptr) {
                                      sf::Texture* texturaPersonaje = new sf::Texture();
                                      if (!texturaPersonaje->loadFromFile("personaje1.png")) {
                                          std::cerr << "Error al cargar la textura del personaje predeterminado" << std::endl;
                                          return -1;
                                      }
                                      jugador.setTexture(texturaPersonaje);

                                      // Escalar el sprite para que se ajuste al tamaño deseado
                                      float scaleFactor = 1.0f; // Factor de escala, ajusta según sea necesario
                                      jugador.setScale(scaleFactor, scaleFactor);
                                  }

                                  sf::RenderWindow ventana(sf::VideoMode(anchoVentana, altoVentana), "CrossyRoads");
                                  ventana.setFramerateLimit(60);

                                  std::vector<Entidad*> entidades;
                                  std::vector<bool> carrilesOcupados(altoVentana / espacioEntreCarros, false);
                                  ZonaSegura zonaSegura;

                                  srand(time(nullptr));

                                  sf::RectangleShape fondoCalle(sf::Vector2f(anchoVentana, altoVentana));
                                  fondoCalle.setFillColor(sf::Color(100, 100, 100));

                                 
                                  jugador.setPosition(anchoVentana / 2 - jugador.getSize().x / 2, altoVentana - jugador.getSize().y);

                                  sf::View vista(sf::FloatRect(0, 0, anchoVentana, altoVentana));
                                  ventana.setView(vista);

                                  float temporizadorSpawnCarro = 0.0f;
                                  float temporizadorInactividad = 0.0f;

                                  sf::Clock reloj;
                                  sf::Clock inactividadReloj;

                                  eliminarCarrosEnZonaSegura(entidades, zonaSegura);
                                  eliminarCarrosFueraDePantalla(entidades);
                                  reiniciarJuego(jugador, entidades, carrilesOcupados, zonaSegura);

                                  sf::Texture carroTexture;
                                  if (!carroTexture.loadFromFile("carro.png")) {
                                      std::cerr << "Error al cargar la textura del carro" << std::endl;
                                      return 1;
                                  }

                                  sf::Texture pastoTexture;
                                  if (!pastoTexture.loadFromFile("pasto.jpg")) {
                                      std::cerr << "Error al cargar la textura de pasto" << std::endl;
                                      return 1;
                                  }

                                  while (ventana.isOpen()) {
                                      sf::Time deltaTiempo = reloj.restart();

                                      sf::Event evento;
                                      while (ventana.pollEvent(evento)) {
                                          if (evento.type == sf::Event::Closed) {
                                              ventana.close();
                                          }
                                      }

                                      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && jugador.getPosition().x > 0) {
                                          jugador.move(-velocidadJugador * deltaTiempo.asSeconds(), 0.0f);
                                          temporizadorInactividad = 0.0f;
                                      }
                                      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && jugador.getPosition().x < anchoVentana - jugador.getSize().x) {
                                          jugador.move(velocidadJugador * deltaTiempo.asSeconds(), 0.0f);
                                          temporizadorInactividad = 0.0f;
                                      }
                                      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                                          jugador.move(0.0f, -velocidadJugador * deltaTiempo.asSeconds());
                                          temporizadorInactividad = 0.0f;
                                      }
                                      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                                          jugador.move(0.0f, velocidadJugador * deltaTiempo.asSeconds());
                                          temporizadorInactividad = 0.0f;
                                      }

                                      temporizadorInactividad += inactividadReloj.restart().asSeconds();
                                      if (temporizadorInactividad >= tiempoLimiteInactividad) {
                                          std::cout << "Te has quedado inactivo durante demasiado tiempo. Has perdido el juego!" << std::endl;
                                          ventana.close();
                                          musicaFondo.pause();
                                          gameOver();
                                          musicaFondo.play();

                                          break; // Salimos del bucle principal
                                      }

                                      if (jugador.getPosition().y < limiteReinicio) {
                                          reiniciarJuego(jugador, entidades, carrilesOcupados, zonaSegura);
                                      }

                                      temporizadorSpawnCarro += deltaTiempo.asSeconds();
                                      if (temporizadorSpawnCarro >= retrasoSpawnCarro) {
                                          temporizadorSpawnCarro = 0.0f;
                                          float posY = (rand() % carrilesOcupados.size()) * espacioEntreCarros;

                                          sf::RectangleShape carroNuevo(sf::Vector2f(150.0f, 80.0f));
                                          carroNuevo.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
                                          carroNuevo.setPosition(-150.0f, posY);

                                          sf::SoundBuffer buffer;
                                          if (!buffer.loadFromFile("efectoColision.wav")) {
                                              // Manejo de error si no se puede cargar el archivo
                                              return EXIT_FAILURE;
                                          }

                                          while (hayColisionJugadorCarro(carroNuevo, entidades) ||
                                              (carroNuevo.getPosition().y >= zonaSegura.posicion.y &&
                                                  carroNuevo.getPosition().y <= zonaSegura.posicion.y + zonaSegura.tamano.y + 110)) {
                                              posY = (rand() % carrilesOcupados.size()) * espacioEntreCarros;
                                              carroNuevo.setPosition(-150.0f, posY);
                                          }

                                          float velocidadCarro = velocidadMinimaCarroInicial + (rand() % static_cast<int>(velocidadMaximaCarroInicial - velocidadMinimaCarroInicial + 1));
                                          Carro* nuevoCarro = new Carro(velocidadCarro, posY, carroTexture);
                                          entidades.push_back(nuevoCarro);
                                      }

                                      if (hayColisionJugadorCarro(jugador, entidades)) {
                                          if (jugador.getPosition().y < zonaSegura.posicion.y || jugador.getPosition().y > zonaSegura.posicion.y + zonaSegura.tamano.y) {
                                              std::cout << "GAME OVER!" << std::endl;
                                              ventana.close();
                                              musicaFondo.pause();
                                              colision.play();
                                              gameOver();
                                              musicaFondo.play();

                                              break; // Salimos del bucle principal
                                          }
                                      }

                                      ventana.clear();

                                      ventana.draw(fondoCalle);


                                      sf::RectangleShape zonaSeguraRect(sf::Vector2f(zonaSegura.tamano.x, 200));
                                      zonaSeguraRect.setPosition(zonaSegura.posicion);
                                      zonaSeguraRect.setTexture(&pastoTexture);



                                     

                                      for (int i = 0; i < numLineasCarretera; ++i) {
                                          sf::RectangleShape linea(sf::Vector2f(anchoVentana, grosorLineaCarretera));
                                          linea.setFillColor(sf::Color::White);
                                          linea.setPosition(0, (i + 1) * (altoVentana / (numLineasCarretera + 1)) - grosorLineaCarretera / 2);
                                          ventana.draw(linea);
                                      }



                                      zonaSeguraRect.setTextureRect(sf::IntRect(0, 0, static_cast<int>(zonaSegura.tamano.x), static_cast<int>(200)));

                                
                                      textoScore.setCharacterSize(24);
                                      textoScore.setFillColor(sf::Color::White);
                                      textoScore.setPosition(anchoVentana - 200, 20);
                                      textoScore.setString("SCORE: " + std::to_string(contadorTiempo.getElapsedTime().asSeconds()) + " segundos");

                                      ventana.draw(textoScore);

                                     
                                      
                                      for (const auto& entidad : entidades) {
                                          entidad->update(deltaTiempo.asSeconds());
                                          entidad->draw(ventana);
                                      }

                                      ventana.draw(zonaSeguraRect);

                                      ventana.draw(jugador);

                                      ventana.display();
                                  }

                          
                                  // Limpiar memoria de las entidades al salir del juego
                                  for (auto& entidad : entidades) {
                                      delete entidad; // Liberar memoria de la entidad
                                  }
                                  entidades.clear(); // Limpiar el vector de entidades

                              }
                                else if (x == 2) {
                                    window.close();
                                    return 0;
                                }
                            }
                        }
                    }
                    window.clear();
                    window.draw(menuSprite); // Volver a dibujar la imagen de fondo del menú
                    mainMenu.draw(); // Volver a dibujar los elementos del menú
                    window.display();
                  
                }
                showMainMenu = false; // Reiniciar para evitar volver a abrir el menú
            }
            musicaFondo.play();
            musicaFondo.setLoop(true); // Reproducir en bucle
            window.display();
        }
        return 0;
    }