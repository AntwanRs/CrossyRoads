#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

const int anchoVentana = 1920;
const int altoVentana = 1200;
const float velocidadJugador = 200.0f;
const float velocidadMinimaCarro = 150.0f;
const float velocidadMaximaCarro = 300.0f;
const float limiteReinicio = -200.0f;
const float espacioEntreCarros = 200.0f;
const float retrasoSpawnCarro = 1.0f;
const int numLineasCarretera = 5;
const int grosorLineaCarretera = 5;
const float distanciaMinimaCarros = 200.0f; // Distancia mínima entre carros en el eje x
const float tiempoLimiteInactividad = 30.0f; // Tiempo límite de inactividad en segundos

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
    sf::RectangleShape forma;
    float velocidad;

public:
    Carro(float velocidadBase, float posY)
        : velocidad(velocidadBase + (rand() % 100)) {
        forma.setSize(sf::Vector2f(150.0f, 80.0f));
        forma.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        forma.setPosition(-150.0f, posY);
    }

    void randomizar() override {
        forma.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        velocidad = velocidadMinimaCarro + (rand() % static_cast<int>(velocidadMaximaCarro - velocidadMinimaCarro + 1));
    }

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
        return forma.getSize();
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

void reiniciarJuego(sf::RectangleShape& jugador, std::vector<Entidad*>& entidades, std::vector<bool>& carrilesOcupados) {
    jugador.setPosition(anchoVentana / 2 - jugador.getSize().x / 2, altoVentana - jugador.getSize().y);
    std::fill(carrilesOcupados.begin(), carrilesOcupados.end(), false);

    // Eliminar carros existentes
    for (auto& entidad : entidades) {
        delete entidad;
    }
    entidades.clear();
}

bool detectarColision(const sf::RectangleShape& jugador, const std::vector<Entidad*>& entidades) {
    for (const auto& entidad : entidades) {
        if (entidad->getTipo() == TipoEntidad::Carro && entidad->colision(jugador)) {
            return true;
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

bool hayColisionCarroEnX(const sf::RectangleShape& carroNuevo, const std::vector<Entidad*>& entidades) {
    for (const auto& entidad : entidades) {
        if (entidad->getTipo() == TipoEntidad::Carro) {
            if (entidad->getPosition().x + entidad->getSize().x > carroNuevo.getPosition().x &&
                carroNuevo.getPosition().x + carroNuevo.getSize().x > entidad->getPosition().x) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    sf::RenderWindow ventana(sf::VideoMode(anchoVentana, altoVentana), "Frogger");
    ventana.setFramerateLimit(60);

    std::vector<Entidad*> entidades;
    std::vector<bool> carrilesOcupados(altoVentana / espacioEntreCarros, false);

    srand(time(nullptr));

    sf::RectangleShape jugador(sf::Vector2f(100.0f, 100.0f));
    jugador.setFillColor(sf::Color::Green);
    jugador.setPosition(anchoVentana / 2 - jugador.getSize().x / 2, altoVentana - jugador.getSize().y);

    sf::View vista(sf::FloatRect(0, 0, anchoVentana, altoVentana));
    ventana.setView(vista);

    sf::RectangleShape calle(sf::Vector2f(anchoVentana, altoVentana));
    calle.setFillColor(sf::Color(100, 100, 100));

    float temporizadorSpawnCarro = 0.0f;
    float temporizadorInactividad = 0.0f; // Temporizador para rastrear la inactividad del jugador

    sf::Clock reloj;
    sf::Clock inactividadReloj; // Reloj para rastrear la inactividad del jugador

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
            temporizadorInactividad = 0.0f; // Restablecer el temporizador de inactividad si el jugador se mueve
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && jugador.getPosition().x < anchoVentana - jugador.getSize().x) {
            jugador.move(velocidadJugador * deltaTiempo.asSeconds(), 0.0f);
            temporizadorInactividad = 0.0f; // Restablecer el temporizador de inactividad si el jugador se mueve
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            jugador.move(0.0f, -velocidadJugador * deltaTiempo.asSeconds());
            temporizadorInactividad = 0.0f; // Restablecer el temporizador de inactividad si el jugador se mueve
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            jugador.move(0.0f, velocidadJugador * deltaTiempo.asSeconds());
            temporizadorInactividad = 0.0f; // Restablecer el temporizador de inactividad si el jugador se mueve
        }

        // Actualizar el temporizador de inactividad
        temporizadorInactividad += inactividadReloj.restart().asSeconds();
        if (temporizadorInactividad >= tiempoLimiteInactividad) {
            std::cout << "Te has quedado inactivo durante demasiado tiempo. ¡Has perdido el juego!" << std::endl;
            ventana.close();
        }

        if (jugador.getPosition().y < limiteReinicio) {
            reiniciarJuego(jugador, entidades, carrilesOcupados);
        }

        temporizadorSpawnCarro += deltaTiempo.asSeconds();
        if (temporizadorSpawnCarro >= retrasoSpawnCarro) {
            temporizadorSpawnCarro = 0.0f;
            float posY = (rand() % carrilesOcupados.size()) * espacioEntreCarros;

            sf::RectangleShape carroNuevo(sf::Vector2f(150.0f, 80.0f));
            carroNuevo.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
            carroNuevo.setPosition(-150.0f, posY);

            while (hayColisionCarroEnX(carroNuevo, entidades)) {
                posY = (rand() % carrilesOcupados.size()) * espacioEntreCarros;
                carroNuevo.setPosition(-150.0f, posY);
            }

            Carro* nuevoCarro = new Carro(velocidadMinimaCarro + (rand() % static_cast<int>(velocidadMaximaCarro - velocidadMinimaCarro + 1)), posY);
            entidades.push_back(nuevoCarro);
        }

        eliminarCarrosFueraDePantalla(entidades);

        if (detectarColision(jugador, entidades)) {
            std::cout << "Has sido golpeado por un carro. ¡Has perdido el juego!" << std::endl;
            ventana.close();
        }

        ventana.clear();
        ventana.draw(calle);

        ventana.draw(jugador);

        // Dibujar carros
        for (const auto& entidad : entidades) {
            entidad->update(deltaTiempo.asSeconds());
            entidad->draw(ventana);
        }

        ventana.display();
    }

    for (auto& entidad : entidades) {
        delete entidad;
    }
    entidades.clear();

    return 0;
}
