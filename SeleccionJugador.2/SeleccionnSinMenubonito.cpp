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

    void randomizar() override {
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

// Función para mostrar el menú de selección de personajes
int mostrarMenu(sf::RenderWindow& ventana, std::vector<sf::Texture>& texturas) {
  //AQUI VA EL MENU BONITOOOOO NO LO PUDE PONER PQ NO M CARGAN LAS FUENTES???NOSE PQ

    std::vector<sf::Sprite> opciones;
    for (int i = 0; i < texturas.size(); ++i) {
        sf::Sprite sprite(texturas[i]);
        sprite.setPosition(anchoVentana / 2 - sprite.getGlobalBounds().width / 2, 150 + i * 150);
        opciones.push_back(sprite);
    }

    while (ventana.isOpen()) {
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                ventana.close();
                return -1;
            }
            if (evento.type == sf::Event::MouseButtonPressed) {
                if (evento.mouseButton.button == sf::Mouse::Left) {
                    for (int i = 0; i < texturas.size(); ++i) {
                        if (opciones[i].getGlobalBounds().contains(evento.mouseButton.x, evento.mouseButton.y)) {
                            return i;
                        }
                    }
                }
            }
        }

        ventana.clear(sf::Color::White);
        for (const auto& opcion : opciones) {
            ventana.draw(opcion);
        }
        ventana.display();
    }

    return -1;
}

int main() {
    sf::RenderWindow ventana(sf::VideoMode(anchoVentana, altoVentana), "CrossyRoads");
    ventana.setFramerateLimit(60);

    std::vector<Entidad*> entidades;
    std::vector<bool> carrilesOcupados(altoVentana / espacioEntreCarros, false);
    ZonaSegura zonaSegura;

    srand(time(nullptr));

    sf::RectangleShape fondoCalle(sf::Vector2f(anchoVentana, altoVentana));
    fondoCalle.setFillColor(sf::Color(100, 100, 100));

    sf::RectangleShape jugador(sf::Vector2f(90.0f, 170.0f)); //esto se puede modificar
    //jugador.setFillColor(sf::Color(0, 100, 0));
    jugador.setPosition(anchoVentana / 2 - jugador.getSize().x / 2, altoVentana - jugador.getSize().y);

    sf::View vista(sf::FloatRect(0, 0, anchoVentana, altoVentana));
    ventana.setView(vista);

    float temporizadorSpawnCarro = 0.0f;
    float temporizadorInactividad = 0.0f;

    sf::Clock reloj;
    sf::Clock inactividadReloj;

    // Mostrar menú de selección de personajes
    std::vector<sf::Texture> texturasPersonajes;
    for (int i = 0; i < 4; ++i) {
        sf::Texture textura;
        if (!textura.loadFromFile("personaje" + std::to_string(i + 1) + ".png")) { //aqui poner los png de nombre personaje 1.. 2 bla bla para q sirva la iteracion
            std::cerr << "Error al cargar la textura del personaje " << i + 1 << std::endl;
            return -1;
        }
        texturasPersonajes.push_back(textura);
    }

    int indicePersonajeSeleccionado = mostrarMenu(ventana, texturasPersonajes);
    if (indicePersonajeSeleccionado == -1) {
        ventana.close();
        return 0;
    }

    sf::Texture& texturaPersonaje = texturasPersonajes[indicePersonajeSeleccionado];
    jugador.setTexture(&texturaPersonaje);

    reiniciarJuego(jugador, entidades, carrilesOcupados, zonaSegura);

    // Cargar textura del carro
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
                std::cout << "Has sido atropelladoooo por un carro fuera de la zona segura! GAME OVERRR!" << std::endl;
                ventana.close();
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

    for (auto& entidad : entidades) {
        delete entidad;
    }
    entidades.clear();

    return 0;
}
