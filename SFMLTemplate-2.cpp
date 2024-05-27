#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace sf;
using namespace std;


#define Max_main_menu 4
const int anchoVentana = 1920;
const int altoVentana = 1200;
const float velocidadJugador = 200.0f;
float velocidadMinimaCarroInicial = 150.0f;
float velocidadMaximaCarroInicial = 400.0f;
const float limiteReinicio = -200.0f;
const float espacioEntreCarros = 200.0f;
const float retrasoSpawnCarro = 0.30f; //No se porque, no entiendo porque pero nunca quitar esto
const int numLineasCarretera = 5;
const int grosorLineaCarretera = 5;
const float distanciaMinimaCarros = 50.0f;
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
    sf::RenderWindow window{ sf::VideoMode(1600, 800), "Seleccionar personaje" };
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
    std::string personajeSeleccionado;
    sf::Texture textura_seleccionada; // Textura seleccionada del jugador

public:
    SeleccionPersonaje() {
        if (!font.loadFromFile("Lato-Black.ttf")) {
            std::cerr << "Error al cargar la fuente " << std::endl;
            return;
        }

        if (!textura_fondo.loadFromFile("imagenFondo (2).jpeg")) {
            std::cerr << "Error al cargar la imagen de fondo" << std::endl;
            return;
        }

        if (!textura_apo.loadFromFile("personajeapo.png") ||
            !textura_ant.loadFromFile("personajeant.png") ||
            !textura_ale.loadFromFile("personajeale.png") ||
            !textura_alicia.loadFromFile("personajealicia.png")) {
            std::cerr << "Error al cargar las texturas de los personajes" << std::endl;
            return;
        }

        sprite_fondo.setTexture(textura_fondo);
        sprite_fondo.setScale(window.getSize().x / sprite_fondo.getLocalBounds().width, window.getSize().y / sprite_fondo.getLocalBounds().height);

        text.setFont(font);
        text.setString("Selecciona tu personaje");
        text.setCharacterSize(60);
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold);

        sf::FloatRect limitesTexto = text.getLocalBounds();
        text.setOrigin(limitesTexto.left + limitesTexto.width / 2.0f, limitesTexto.top + limitesTexto.height / 2.0f);
        text.setPosition(window.getSize().x / 2.0f, 100);

        text.setOutlineColor(sf::Color::Black);
        text.setOutlineThickness(2);

        sprite_apo.setTexture(textura_apo);
        sprite_ant.setTexture(textura_ant);
        sprite_ale.setTexture(textura_ale);
        sprite_alicia.setTexture(textura_alicia);

        sprite_apo.setScale(1.5f, 1.5f);
        sprite_ant.setScale(1.5f, 1.5f);
        sprite_ale.setScale(1.5f, 1.5f);
        sprite_alicia.setScale(1.5f, 1.5f);

        sprite_apo.setPosition(window.getSize().x / 8.0f - sprite_apo.getGlobalBounds().width / 2, 200);
        sprite_ant.setPosition(window.getSize().x / 8.0f * 3 - sprite_ant.getGlobalBounds().width / 2, 200);
        sprite_ale.setPosition(window.getSize().x / 8.0f * 5 - sprite_ale.getGlobalBounds().width / 2, 200);
        sprite_alicia.setPosition(window.getSize().x / 8.0f * 7 - sprite_alicia.getGlobalBounds().width / 2, 200);

        text_apo.setFont(font);
        text_ant.setFont(font);
        text_ale.setFont(font);
        text_alicia.setFont(font);

        text_apo.setString("Apo");
        text_ant.setString("Ant");
        text_ale.setString("Ale");
        text_alicia.setString("Alicia");

        text_apo.setCharacterSize(30);
        text_ant.setCharacterSize(30);
        text_ale.setCharacterSize(30);
        text_alicia.setCharacterSize(30);

        text_apo.setFillColor(sf::Color::White);
        text_ant.setFillColor(sf::Color::White);
        text_ale.setFillColor(sf::Color::White);
        text_alicia.setFillColor(sf::Color::White);

        text_apo.setPosition(sprite_apo.getPosition().x + sprite_apo.getGlobalBounds().width / 2 - text_apo.getGlobalBounds().width / 2, sprite_apo.getPosition().y + sprite_apo.getGlobalBounds().height + 10);
        text_ant.setPosition(sprite_ant.getPosition().x + sprite_ant.getGlobalBounds().width / 2 - text_ant.getGlobalBounds().width / 2, sprite_ant.getPosition().y + sprite_ant.getGlobalBounds().height + 10);
        text_ale.setPosition(sprite_ale.getPosition().x + sprite_ale.getGlobalBounds().width / 2 - text_ale.getGlobalBounds().width / 2, sprite_ale.getPosition().y + sprite_ale.getGlobalBounds().height + 10);
        text_alicia.setPosition(sprite_alicia.getPosition().x + sprite_alicia.getGlobalBounds().width / 2 - text_alicia.getGlobalBounds().width / 2, sprite_alicia.getPosition().y + sprite_alicia.getGlobalBounds().height + 10);

        text_apo.setOutlineColor(sf::Color::Black);
        text_apo.setOutlineThickness(1);
        text_ant.setOutlineColor(sf::Color::Black);
        text_ant.setOutlineThickness(1);
        text_ale.setOutlineColor(sf::Color::Black);
        text_ale.setOutlineThickness(1);
        text_alicia.setOutlineColor(sf::Color::Black);
        text_alicia.setOutlineThickness(1);
    }


    std::string obtenerPersonajeSeleccionado() {
        return personajeSeleccionado;
    }
    sf::Texture obtenerTexturaJugador() {
        if (personajeSeleccionado == "Apo") {
            return textura_apo; // Textura por defecto
        }
        else {
            return textura_seleccionada; // Textura seleccionada
        }
    }

    const sf::Texture& obtenerTexturaJugador() const {
        if (personajeSeleccionado == "personajeapo") {
            return textura_apo; // Textura por defecto
        }
        else if (personajeSeleccionado == "personajeant") {
            return textura_ant;
        }
        else if (personajeSeleccionado == "personajeale") {
            return textura_ale;
        }
        else if (personajeSeleccionado == "personajealicia") {
            return textura_alicia;
        }
        else {
            return textura_apo; // Devolvemos la textura por defecto si no hay selección
        }
    }
    std::string iniciar() {
        bool seleccionado = false; // Variable para verificar si se ha seleccionado un personaje
        while (window.isOpen()) { // Bucle principal
            sf::Event evento;
            while (window.pollEvent(evento)) {
                if (evento.type == sf::Event::Closed) {
                    // Cerrar la ventana si se presiona el botón de cerrar
                    window.close();
                    return ""; // Salir y devolver una cadena vacía
                }

                if (evento.type == sf::Event::KeyPressed && !seleccionado) {
                    text_apo.setFillColor(sf::Color::White);
                    text_ant.setFillColor(sf::Color::White);
                    text_ale.setFillColor(sf::Color::White);
                    text_alicia.setFillColor(sf::Color::White);

                    if (evento.key.code == sf::Keyboard::Left) {
                        text_apo.setFillColor(sf::Color::Blue);
                        personajeSeleccionado = "personajeapo"; // Guardar el personaje seleccionado
                        seleccionado = true; // Marcar como seleccionado
                    }
                    else if (evento.key.code == sf::Keyboard::Right) {
                        text_ant.setFillColor(sf::Color::Blue);
                        personajeSeleccionado = "personajeant"; // Guardar el personaje seleccionado
                        seleccionado = true; // Marcar como seleccionado
                    }
                    else if (evento.key.code == sf::Keyboard::Up) {
                        text_ale.setFillColor(sf::Color::Blue);
                        personajeSeleccionado = "personajeale"; // Guardar el personaje seleccionado
                        seleccionado = true; // Marcar como seleccionado
                    }
                    else if (evento.key.code == sf::Keyboard::Down) {
                        text_alicia.setFillColor(sf::Color::Blue);
                        personajeSeleccionado = "personajealicia"; // Guardar el personaje seleccionado
                        seleccionado = true; // Marcar como seleccionado
                    }

                    if (seleccionado) {
                        // Asignar la textura seleccionada a la textura del jugador
                        textura_seleccionada = obtenerTexturaJugador();
                    }
                }
            }

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
            window.display();

            if (seleccionado) {
                sf::sleep(sf::seconds(2));
                window.close();
            }
        }
        return personajeSeleccionado;
    }
};

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
            mainMenu[0].setCharacterSize(70);
            mainMenu[0].setPosition(400, 90);

            mainMenu[1].setFont(font);
            mainMenu[1].setFillColor(Color::Blue);
            mainMenu[1].setString("Personajes");
            mainMenu[1].setCharacterSize(70);
            mainMenu[1].setPosition(280, 190);

            mainMenu[2].setFont(font);
            mainMenu[2].setFillColor(Color::Blue);
            mainMenu[2].setString("Controles");
            mainMenu[2].setCharacterSize(70);
            mainMenu[2].setPosition(300, 290);

            mainMenu[3].setFont(font);
            mainMenu[3].setFillColor(Color::Blue);
            mainMenu[3].setString("Salir");
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

    int main() {
        RenderWindow window(VideoMode(960, 720), "Default", Style::Default);
        sf::Sprite jugadorSprite;

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

        MainMenu mainMenu(window);

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
                                    // Playyyyyyyyy
                                    sf::RenderWindow ventana(sf::VideoMode(anchoVentana, altoVentana), "CrossyRoads");
                                    ventana.setFramerateLimit(60);

                                    std::vector<Entidad*> entidades;
                                    std::vector<bool> carrilesOcupados(altoVentana / espacioEntreCarros, false);
                                    ZonaSegura zonaSegura;

                                    srand(time(nullptr));

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

                                        //ventana.draw(jugadorSprite);
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
                                    SeleccionPersonaje seleccionPersonaje;

                                    std::string personajeSeleccionado = seleccionPersonaje.iniciar();
                                    if (!personajeSeleccionado.empty()) {
                                        // Obtener la textura del personaje seleccionado
                                        sf::Texture texturaJugador = seleccionPersonaje.obtenerTexturaJugador();
                                        // Asignar la textura al sprite del jugador
                                        jugadorSprite.setTexture(texturaJugador);
                             
                                    }
                                    break;
                                }
                                else if (x == 2) {
                                    // Controles
                                    cout << "Controles button pressed!" << endl;
                                }
                            }
                        }
                    }
                    window.clear();
                    window.draw(menuSprite); // Volver a dibujar la imagen de fondo del menú
                    window.draw(jugadorSprite);
                    mainMenu.draw(); // Volver a dibujar los elementos del menú
                    window.display();
                }
                showMainMenu = false; // Reiniciar para evitar volver a abrir el menú
            }
            window.display();
        }
        return 0;
    }