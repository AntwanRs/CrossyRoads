#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace sf;
using namespace std;


const int anchoVentana = 1920;
const int altoVentana = 1200;
const float velocidadJugador = 200.0f;
float velocidadMinimaCarroInicial = 150.0f;
float velocidadMaximaCarroInicial = 400.0f;
const float limiteReinicio = -200.0f;
const float espacioEntreCarros = 200.0f;
const float retrasoSpawnCarro = 0.900f; //nunca quitar esto
const int numLineasCarretera = 5;
const int grosorLineaCarretera = 5;
const float distanciaMinimaCarros = 100.0f;
const float tiempoLimiteInactividad = 30.0f;
const sf::Time tiempoGameOver = sf::seconds(05.0f); // Tiempo que se muestra la ventana de Game Over

struct ZonaSegura {
    sf::Vector2f posicion;
    sf::Vector2f tamano;
};

enum class TipoEntidad { Jugador, Carro };

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

    zonaSegura.tamano.x = anchoVentana;
    zonaSegura.tamano.y = jugador.getSize().y * 2.0f;

    zonaSegura.posicion.x = 0;
    zonaSegura.posicion.y = rand() % (altoVentana - static_cast<int>(zonaSegura.tamano.y));
}

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

class SeleccionPersonaje {
private:
    int personajeSelec; // Variable para almacenar el personaje seleccionado
    sf::RenderWindow& window;
    sf::Texture texture_background;
    sf::Sprite sprite_background;
    sf::Texture texture_apo;
    sf::Texture texture_ant;
    sf::Texture texture_ale;
    sf::Texture texture_alicia;
    sf::Sprite sprite_apo;
    sf::Sprite sprite_ant;
    sf::Sprite sprite_ale;
    sf::Sprite sprite_alicia;
    sf::RectangleShape indicador_apo;
    sf::RectangleShape indicador_ant;
    sf::RectangleShape indicador_ale;
    sf::RectangleShape indicador_alicia;

public:
    SeleccionPersonaje(sf::RenderWindow&window) : personajeSelec(0), window(window) {
        if (!texture_background.loadFromFile("Menu2.jpeg")) {
            std::cerr << "Error al cargar la imagen de fondo" << std::endl;
            return;
        }
        sprite_background.setTexture(texture_background);

        if (!texture_apo.loadFromFile("personajeapo.png") ||
            !texture_ant.loadFromFile("personajeant.png") ||
            !texture_ale.loadFromFile("personajeale.png") ||
            !texture_alicia.loadFromFile("personajealicia.png")) {
            std::cerr << "Error al cargar los personajes" << std::endl;
            return;
        }

        sprite_apo.setTexture(texture_apo);
        sprite_ant.setTexture(texture_ant);
        sprite_ale.setTexture(texture_ale);
        sprite_alicia.setTexture(texture_alicia);

        sprite_apo.setScale(1.5f, 1.5f);
        sprite_ant.setScale(1.5f, 1.5f);
        sprite_ale.setScale(1.5f, 1.5f);
        sprite_alicia.setScale(1.5f, 1.5f);

        sprite_apo.setPosition(60, 200);
        sprite_ant.setPosition(280, 200);
        sprite_ale.setPosition(490, 200);
        sprite_alicia.setPosition(720, 200);

        indicador_apo.setSize(sf::Vector2f(150, 20));
        indicador_ant.setSize(sf::Vector2f(150, 20));
        indicador_ale.setSize(sf::Vector2f(150, 20));
        indicador_alicia.setSize(sf::Vector2f(150, 20));

        // Position rectangles below character sprites
        indicador_apo.setPosition(sprite_apo.getPosition().x + (sprite_apo.getGlobalBounds().width - indicador_apo.getSize().x) / 2, sprite_apo.getPosition().y + sprite_apo.getGlobalBounds().height + 20);
        indicador_ant.setPosition(sprite_ant.getPosition().x + (sprite_ant.getGlobalBounds().width - indicador_ant.getSize().x) / 2, sprite_ant.getPosition().y + sprite_ant.getGlobalBounds().height + 20);
        indicador_ale.setPosition(sprite_ale.getPosition().x + (sprite_ale.getGlobalBounds().width - indicador_ale.getSize().x) / 2, sprite_ale.getPosition().y + sprite_ale.getGlobalBounds().height + 20);
        indicador_alicia.setPosition(sprite_alicia.getPosition().x + (sprite_alicia.getGlobalBounds().width - indicador_alicia.getSize().x) / 2, sprite_alicia.getPosition().y + sprite_alicia.getGlobalBounds().height + 20);

        // Set colors for indicators
        indicador_apo.setFillColor(sf::Color::Black);
        indicador_ant.setFillColor(sf::Color::Red);
        indicador_ale.setFillColor(sf::Color::Magenta);
        indicador_alicia.setFillColor(sf::Color::Blue);

        // Set outline color and thickness for indicators
        indicador_apo.setOutlineColor(sf::Color::Black);
        indicador_ant.setOutlineColor(sf::Color::Red);
        indicador_ale.setOutlineColor(sf::Color::Magenta);
        indicador_alicia.setOutlineColor(sf::Color::Blue);
        indicador_apo.setOutlineThickness(2);
        indicador_ant.setOutlineThickness(2);
        indicador_ale.setOutlineThickness(2);
        indicador_alicia.setOutlineThickness(2);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite_background);
        window.draw(sprite_apo);
        window.draw(sprite_ant);
        window.draw(sprite_ale);
        window.draw(sprite_alicia);
        window.draw(indicador_apo);
        window.draw(indicador_ant);
        window.draw(indicador_ale);
        window.draw(indicador_alicia);
    }
    

    int getPersonaje() const {
        return personajeSelec;
    }

    void guardarSelec() {
        // Aquí podrías guardar el personaje seleccionado en algún lugar para usarlo en la sección de juego
        std::cout << "Personaje seleccionado: " << personajeSelec << std::endl;
    }

    void Evento(const sf::Event& event) {
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                if (sprite_apo.getGlobalBounds().contains(mousePosition)) {
                    personajeSelec = 1; //  que marque el personaje Apo
                }
                else if (sprite_ant.getGlobalBounds().contains(mousePosition)) {
                    personajeSelec = 2; // que marque el personaje Ant 
                }
                else if (sprite_ale.getGlobalBounds().contains(mousePosition)) {
                    personajeSelec = 3; // que marque el personaje Ale 
                }
                else if (sprite_alicia.getGlobalBounds().contains(mousePosition)) {
                    personajeSelec = 4; // que marque el personaje Alicia 
                }
            guardarSelec();
        }
    }
    
};

class MainMenu {
private:
    int seleccionMenu;
    RectangleShape menuItems[3]; 

public:
    MainMenu(float width, float height) {
        for (int i = 0; i < 3; ++i) {
            menuItems[i].setSize(Vector2f(200, 50));
            menuItems[i].setFillColor(Color::Green);
            menuItems[i].setPosition(Vector2f(width / 2 - 100, 500 / 3 * (i + 1)));
        }

        seleccionMenu = 0;
        menuItems[seleccionMenu].setFillColor(Color::Red);
    }

    void draw(RenderWindow& window, Sprite& backgroundSprite) {
        window.draw(backgroundSprite);
        for (int i = 0; i < 3; ++i) {
            window.draw(menuItems[i]);
        }
    }

    void MoveUp() {
        if (seleccionMenu - 1 >= 0) {
            menuItems[seleccionMenu].setFillColor(Color::Green);
            seleccionMenu--;
            menuItems[seleccionMenu].setFillColor(Color::Red);
        }
    }

    void MoveDown() {
        if (seleccionMenu + 1 < 3) {
            menuItems[seleccionMenu].setFillColor(Color::Green);
            seleccionMenu++;
            menuItems[seleccionMenu].setFillColor(Color::Red);
        }
    }

    int MainMenuPressed() {
        return seleccionMenu;
    }
};

int main() {
    RenderWindow window(VideoMode(960, 720), "Default ", Style::Default);

    int personajeSeleccionado = 0;


    Texture defaultTexture;
    if (!defaultTexture.loadFromFile("Crss.jpeg")) {
        cerr << "Failed to load background image!" << endl;
        return -1;
    }
    Sprite defaultSprite(defaultTexture);
    defaultSprite.setScale(0.75f, 0.5625f);

    Texture menuTexture;
    if (!menuTexture.loadFromFile("Menu2.jpeg")) {
        cerr << "Failed to load menu background image!" << endl;
        return -1;
    }
    Sprite menuSprite(menuTexture);
    menuSprite.setScale(0.75f, 0.5625f); // Escalar si es necesario

    MainMenu mainMenu(window.getSize().x, window.getSize().y);

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
            // Dibujar la segunda imagen de fondo antes de los elementos del menú
            mainMenu.draw(window, menuSprite);
            while (window.isOpen()) {
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
                            if (x == 0) {
                                // Play
                                sf::RenderWindow ventana(sf::VideoMode(anchoVentana, altoVentana), "CrossyRoads");
                                ventana.setFramerateLimit(60);

                                std::vector<Entidad*> entidades;
                                std::vector<bool> carrilesOcupados(altoVentana / espacioEntreCarros, false);
                                ZonaSegura zonaSegura;

                                srand(time(nullptr));


                                sf::Texture jugadorTexture;
                                std::string nombreTexturaJugador;
                               
                                switch (personajeSeleccionado) {
                                case 1:
                                    nombreTexturaJugador = "personajeapo.png";
                                    break;
                                case 2:
                                    nombreTexturaJugador = "personajeant.png";
                                    break;
                                case 3:
                                    nombreTexturaJugador = "personajeale.png";
                                    break;
                                case 4:
                                    nombreTexturaJugador = "personajealicia.png";
                                    break;
                                default:
                                    nombreTexturaJugador = "personajeapo.png"; // Cambiar a la textura predeterminada
                                    break;
                                }

                                if (!jugadorTexture.loadFromFile(nombreTexturaJugador)) {
                                    std::cerr << "Error al cargar la textura del jugador" << std::endl;
                                    return 1;
                                }

                                // Configurar el sprite del jugador con la textura cargada
                                sf::Sprite jugadorSprite(jugadorTexture);
                                jugadorSprite.setScale(1.5f, 1.5f);
                                jugadorSprite.setPosition(anchoVentana / 2 - jugadorSprite.getGlobalBounds().width / 2, altoVentana - jugadorSprite.getGlobalBounds().height);


                                sf::RectangleShape fondoCalle(sf::Vector2f(anchoVentana, altoVentana));
                                fondoCalle.setFillColor(sf::Color(100, 100, 100));

                                sf::RectangleShape jugador(sf::Vector2f(90.0f, 170.0f)); // Esto se puede modificar
                                jugador.setPosition(anchoVentana / 2 - jugador.getSize().x / 2, altoVentana - jugador.getSize().y);

                                sf::View vista(sf::FloatRect(0, 0, anchoVentana, altoVentana));
                                ventana.setView(vista);

                                float temporizadorSpawnCarro = 0.0f;
                                float temporizadorInactividad = 0.0f;

                                sf::Clock reloj;
                                sf::Clock inactividadReloj;


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

                                    eliminarCarrosFueraDePantalla(entidades);

                                    if (hayColisionJugadorCarro(jugador, entidades)) {
                                        if (jugador.getPosition().y < zonaSegura.posicion.y || jugador.getPosition().y > zonaSegura.posicion.y + zonaSegura.tamano.y) {
                                            std::cout << "GAME OVER!" << std::endl;
                                            ventana.close();
                                            break; // Salimos del bucle principal
                                        }
                                    }

                                    ventana.clear();

                                    ventana.draw(fondoCalle);

                                    for (const auto& entidad : entidades) {
                                        entidad->update(deltaTiempo.asSeconds());
                                        entidad->draw(ventana);
                                    }

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
                                    ventana.draw(zonaSeguraRect);

                                    ventana.draw(jugador);
                                    ventana.display();
                                }

                                // Ventana de "Game Over"
                                sf::RenderWindow gameOverWindow(sf::VideoMode(1000, 800), "Game Over");
                                sf::Texture texture1, texture2;
                                if (!texture1.loadFromFile("Gameover1.jpeg") || !texture2.loadFromFile("Gameover2.jpeg")) {
                                    std::cerr << "Error cargando las imágenes" << std::endl;
                                    return 1;
                                }

                                sf::Sprite sprite(texture1);
                                sprite.setScale(1000.f / texture1.getSize().x, 800.f / texture1.getSize().y);

                                sf::Clock reloj2;
                                sf::Time tiempoTranscurrido = sf::Time::Zero;

                                while (gameOverWindow.isOpen()) {
                                    sf::Event event;
                                    while (gameOverWindow.pollEvent(event)) {
                                        if (event.type == sf::Event::Closed)
                                            gameOverWindow.close();
                                    }

                                    if (reloj2.getElapsedTime() > tiempoGameOver) {
                                        gameOverWindow.close();
                                        break; // Salimos del bucle de la ventana de "Game Over"
                                    }

                                    if (reloj2.getElapsedTime() > tiempoTranscurrido) {
                                        if (sprite.getTexture() == &texture1) {
                                            sprite.setTexture(texture2);
                                            sprite.setScale(1000.f / texture2.getSize().x, 800.f / texture2.getSize().y);
                                        }
                                        else {
                                            sprite.setTexture(texture1);
                                            sprite.setScale(1000.f / texture1.getSize().x, 800.f / texture1.getSize().y);
                                        }
                                        tiempoTranscurrido += reloj2.restart();
                                    }

                                    gameOverWindow.clear();
                                    gameOverWindow.draw(sprite);
                                    gameOverWindow.display();
                                }
                                // Limpiar memoria de las entidades al salir del juego
                                for (auto& entidad : entidades) {
                                    delete entidad; // Liberar memoria de la entidad
                                }
                                entidades.clear(); // Limpiar el vector de entidades

                            }
                            else if (x == 1) {
                                // Personajes
                                SeleccionPersonaje seleccionPersonaje(window);
                                while (window.isOpen()) {
                                    Event event;
                                    while (window.pollEvent(event)) {
                                        seleccionPersonaje.Evento(event);
                                        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
                                            mainMenu.MainMenuPressed();
                                            break;
                                        }
                                    }
                                    window.clear();
                                    seleccionPersonaje.draw(window);
                                    window.display();

                                    // Si el jugador ha seleccionado un personaje
                                    if (seleccionPersonaje.getPersonaje() != 0) {
                                        // Guardar el personaje seleccionado
                                        personajeSeleccionado = seleccionPersonaje.getPersonaje(); // Actualiza la variable personajeSeleccionado
                                        // Regresar al menu principal
                                        break;
                                    }
                                }
}
                            else if (x == 2) {
                                // Controles
                                cout << "Controles button pressed!" << endl;
                            }
                        }
                    }
                }
                window.clear();
                mainMenu.draw(window, menuSprite);
                window.display();
            }
            showMainMenu = false; // Reset to avoid reopening MENU
        }
        window.display();
    }
    return 0;
}