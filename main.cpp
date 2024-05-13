#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

const int anchoVentana = 1920;
const int altoVentana = 1200;
const float velocidadJugador = 200.0f;
float velocidadMinimaCarroInicial = 150.0f;
float velocidadMaximaCarroInicial = 300.0f;
const float limiteReinicio = -200.0f;
const float espacioEntreCarros = 200.0f;
const float retrasoSpawnCarro = 1.0f;
const int numLineasCarretera = 5;
const int grosorLineaCarretera = 5;
const float distanciaMinimaCarros = 200.0f;
const float tiempoLimiteInactividad = 30.0f;

struct ZonaSegura {
    sf::Vector2f posicion;
    sf::Vector2f tamano;
};

enum class TipoEntidad { Jugador, Carro };

class Entidad {
public:
    virtual void randomizar() = 0;
    virtual TipoEntidad getTipo() const = 0;
    virtual bool colision(const sf::Sprite& jugador) const = 0;
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

    void randomizar() override {
    }

    TipoEntidad getTipo() const override {
        return TipoEntidad::Carro;
    }

    bool colision(const sf::Sprite& jugador) const override {
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

void reiniciarJuego(sf::Sprite& jugador, std::vector<Entidad*>& entidades, std::vector<bool>& carrilesOcupados, ZonaSegura& zonaSegura, sf::Texture& personajeTexture) {
    jugador.setPosition(anchoVentana / 2 - jugador.getGlobalBounds().width / 2, altoVentana - jugador.getGlobalBounds().height);
    std::fill(carrilesOcupados.begin(), carrilesOcupados.end(), false);

    velocidadMinimaCarroInicial += 50.0f;
    velocidadMaximaCarroInicial += 50.0f;

    for (auto& entidad : entidades) {
        delete entidad;
    }
    entidades.clear();

    zonaSegura.tamano.x = anchoVentana;
    zonaSegura.tamano.y = jugador.getGlobalBounds().height * 2.0f;

    zonaSegura.posicion.x = 0;
    zonaSegura.posicion.y = rand() % (altoVentana - static_cast<int>(zonaSegura.tamano.y));

    jugador.setTexture(personajeTexture);
}

bool hayColisionJugadorCarro(const sf::Sprite& jugador, const std::vector<Entidad*>& entidades) {
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
                delete *it;
                it = entidades.erase(it);
                continue;
            }
        }
        ++it;
    }
}

int main() {
    sf::RenderWindow ventana(sf::VideoMode(anchoVentana, altoVentana), "CrossyRoads");
    ventana.setFramerateLimit(60);

    std::vector<Entidad*> entidades;
    std::vector<bool> carrilesOcupados(altoVentana / espacioEntreCarros, false);
    ZonaSegura zonaSegura;

    srand(time(nullptr));
    //Muestra el sprite de personaje en png
    sf::Sprite jugador;
    sf::Texture personajeTexture;
    if (!personajeTexture.loadFromFile("apo2.png")) {
        std::cerr << "Error al cargar la textura del personaje" << std::endl;
        return 1;
    }
    jugador.setTexture(personajeTexture);

    sf::View vista(sf::FloatRect(0, 0, anchoVentana, altoVentana));
    ventana.setView(vista);

    sf::RectangleShape calle(sf::Vector2f(anchoVentana, altoVentana));
    calle.setFillColor(sf::Color(100, 100, 100));

    float temporizadorSpawnCarro = 0.0f;
    float temporizadorInactividad = 0.0f;

    //Variables de contador de tiempo
    sf::Clock reloj;
    sf::Clock inactividadReloj;

    reiniciarJuego(jugador, entidades, carrilesOcupados, zonaSegura, personajeTexture);
    //Dibuja el carro en png
    sf::Texture carroTexture;
    if (!carroTexture.loadFromFile("urusframe1.png")) {
        std::cerr << "Error al cargar la textura del carro" << std::endl;
        return 1;
    }

    //Contador de tiempo para el score
    sf::Clock contadorTiempo;

    while (ventana.isOpen()) {
        sf::Time deltaTiempo = reloj.restart();

        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                ventana.close();
            }
        }
        //Movimiento de teclas
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && jugador.getPosition().x > 0) {
            jugador.move(-velocidadJugador * deltaTiempo.asSeconds(), 0.0f);
            temporizadorInactividad = 0.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && jugador.getPosition().x < anchoVentana - jugador.getGlobalBounds().width) {
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
        //Contador de tiempo para sacar de programa por inactividad
        temporizadorInactividad += inactividadReloj.restart().asSeconds();
        if (temporizadorInactividad >= tiempoLimiteInactividad) {
            std::cout << "Te has quedado inactivo durante demasiado tiempo. ¡Has perdido el juego!" << std::endl;
            ventana.close();
        }

        if (jugador.getPosition().y < limiteReinicio) {
            reiniciarJuego(jugador, entidades, carrilesOcupados, zonaSegura, personajeTexture);
        }

        temporizadorSpawnCarro += deltaTiempo.asSeconds();
        if (temporizadorSpawnCarro >= retrasoSpawnCarro) {
            temporizadorSpawnCarro = 0.0f;
            float posY = (rand() % carrilesOcupados.size()) * espacioEntreCarros;

            sf::RectangleShape carroNuevo(sf::Vector2f(150.0f, 80.0f));
            carroNuevo.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
            carroNuevo.setPosition(-150.0f, posY);

            while (hayColisionJugadorCarro(jugador, entidades) ||
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
                std::cout << "¡Has sido atropellado por un carro fuera de la zona segura! ¡Has perdido el juego!" << std::endl;
                ventana.close();
            }
        }

        ventana.clear();

        ventana.draw(calle);

        for (const auto& entidad : entidades) {
            entidad->update(deltaTiempo.asSeconds());
            entidad->draw(ventana);
        }

        sf::RectangleShape zonaSeguraRect(sf::Vector2f(zonaSegura.tamano.x, zonaSegura.tamano.y));
        zonaSeguraRect.setPosition(zonaSegura.posicion);
        zonaSeguraRect.setFillColor(sf::Color(0, 128, 0));
        ventana.draw(zonaSeguraRect);

        ventana.draw(jugador);

        //Muestra el score en forma de contador de tiempo
        sf::Font fuente;
        if (!fuente.loadFromFile("Lato-Light2.ttf")) {
            std::cerr << "Error al cargar la fuente" << std::endl;
            return 1; // Salir del programa con código de error
        }

        sf::Text textoScore;
        textoScore.setFont(fuente);
        textoScore.setCharacterSize(24);
        textoScore.setFillColor(sf::Color::White);
        //Texto mostrado arriba a la derecha
        textoScore.setPosition(anchoVentana - 200, 20);
        textoScore.setString("SCORE: " + std::to_string(contadorTiempo.getElapsedTime().asSeconds()) + " segundos");

        ventana.draw(textoScore);

        ventana.display();
    }

    for (auto& entidad : entidades) {
        delete entidad;
    }
    entidades.clear();

    return 0;
}
