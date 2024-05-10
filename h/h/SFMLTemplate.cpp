#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

const int anchoVentana = 1920;
const int altoVentana = 1200;
const float velocidadJugador = 200.0f;
float velocidadMinimaCarroInicial = 150.0f;
float velocidadMaximaCarroInicial = 300.0f;
const float limiteReinicio = -200.0f; // Limite de reinicio del jugador en la pantalla
const float espacioEntreCarros = 200.0f; // Espacio entre carros en la carretera
const float retrasoSpawnCarro = 1.0f; // Retraso entre la aparicion de carros (tal vez cambiar esto pq hace bien facil el juego)
const int numLineasCarretera = 5; // Numero de lineas en la carretera
const int grosorLineaCarretera = 5; // Grosor de las lineas en la carretera
const float distanciaMinimaCarros = 200.0f; // Distancia iínima entre carros en el eje x
const float tiempoLimiteInactividad = 30.0f; // Tiempo limite de inactividad en segundos

// Estructura para definir una zona segura en la pantalla
struct ZonaSegura {
    sf::Vector2f posicion; // Posicion de la zona segura
    sf::Vector2f tamano; // Tamano de la zona segura
};

// Enumeracion para definir el tipo de entidad
enum class TipoEntidad { Jugador, Carro };

// Clase base abstracta para todas las entidades del juego
class Entidad {
public:
    virtual void randomizar() = 0; // funcion virtual puro para randomizar la entidad
    virtual TipoEntidad getTipo() const = 0; // funcion virtual puro para obtener el tipo de entidad
    virtual bool colision(const sf::RectangleShape& jugador) const = 0; // funcion virtual puro para verificar colisiones
    virtual sf::Vector2f getPosition() const = 0; // funcion virtual puro para obtener la posición de la entidad
    virtual sf::Vector2f getSize() const = 0; // funcion virtual puro para obtener el tamaño de la entidad
    virtual void setPosition(const sf::Vector2f& position) = 0; // funcion virtual puro para establecer la posición de la entidad
    virtual void draw(sf::RenderWindow& window) const = 0; // funcion virtual puro para dibujar la entidad en la ventana
    virtual void update(float deltaTime) = 0; // funcion virtual puro para actualizar la entidad
    virtual ~Entidad() {} // Destructor virtual :)
};

// Clase para representar un carro en el juego
class Carro : public Entidad {
private:
    sf::RectangleShape forma; // Forma del carro
    float velocidad; // Velocidad del carro

public:
    Carro(float velocidadBase, float posY)
        : velocidad(velocidadBase) {
        forma.setSize(sf::Vector2f(150.0f, 80.0f)); // Tamano del carro
        forma.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256)); // Color aleatorio para el carro (creo que esto no importa cuando ya pongamos las imagenes)
        forma.setPosition(-150.0f, posY); // Posicion inicial del carro fuera de la pantalla
    }

    void randomizar() override {
        // No se requiere randomizacion para el carro en este caso pero si quito la funcion sale error
    }

    TipoEntidad getTipo() const override {
        return TipoEntidad::Carro;
    }

    bool colision(const sf::RectangleShape& jugador) const override {
        return forma.getGlobalBounds().intersects(jugador.getGlobalBounds()); // Verificar colision con el jugador
    }

    sf::Vector2f getPosition() const override {
        return forma.getPosition(); // Obtener la posicion del carro
    }

    sf::Vector2f getSize() const override {
        return forma.getSize(); // Obtener el tamano del carro
    }

    void setPosition(const sf::Vector2f& position) override {
        forma.setPosition(position); // Establecer la posicion del carro
    }

    void move(float deltaX, float deltaY) {
        forma.move(deltaX, deltaY); // Mover el carro
    }

    void draw(sf::RenderWindow& window) const override {
        window.draw(forma); // Dibujar el carro en la ventana
    }

    void update(float deltaTime) override {
        forma.move(velocidad * deltaTime, 0.0f); // Actualizar la posicio del carro
    }
};

// Funcion para reiniciar el juego cuando se llegue a una coord
void reiniciarJuego(sf::RectangleShape& jugador, std::vector<Entidad*>& entidades, std::vector<bool>& carrilesOcupados, ZonaSegura& zonaSegura) {
    jugador.setPosition(anchoVentana / 2 - jugador.getSize().x / 2, altoVentana - jugador.getSize().y); // Posicion inicial del jugador 
    std::fill(carrilesOcupados.begin(), carrilesOcupados.end(), false); // Reiniciar los carriles ocupados a falso

    // Aumentar las velocidades minima y maxima de los carros para que se incremente la dificultad
    velocidadMinimaCarroInicial += 50.0f;
    velocidadMaximaCarroInicial += 50.0f;

    // Eliminar carros existentes
    for (auto& entidad : entidades) {
        delete entidad; // Liberar memoria
    }
    entidades.clear(); // Limpiar el vector de entidades

    // Generar zona segura aleatoria
    zonaSegura.tamano.x = anchoVentana;
    zonaSegura.tamano.y = jugador.getSize().y * 2.0f; // Aumentar el tamaño verticalmente 

    // Calcular la nueva posicion de la zona segura para evitar colisiones con carros
    zonaSegura.posicion.x = 0;
    zonaSegura.posicion.y = rand() % (altoVentana - static_cast<int>(zonaSegura.tamano.y)); // Ajustar posicion vertical para evitar colisiones
}

// Funcion para detectar colisiones entre el jugador y las entidades (los carros)
bool hayColisionJugadorCarro(const sf::RectangleShape& jugador, const std::vector<Entidad*>& entidades) {
    for (const auto& entidad : entidades) {
        if (entidad->getTipo() == TipoEntidad::Carro) {
            if (entidad->colision(jugador)) {
                return true; // Hay colisión entre el jugador y un carro
            }
        }
    }
    return false; // No hay colisión entre el jugador y ningún carro
}

// Funcion para eliminar carros que están fuera de la pantalla
void eliminarCarrosFueraDePantalla(std::vector<Entidad*>& entidades) {
    auto it = entidades.begin();
    while (it != entidades.end()) {
        if ((*it)->getTipo() == TipoEntidad::Carro) {
            if ((*it)->getPosition().x > anchoVentana) {
                delete* it; // Liberar memoria del carro fuera de la pantalla
                it = entidades.erase(it); // Eliminar el carro del vector de entidades
                continue;
            }
        }
        ++it;
    }
}

// En el bucle principal...
int main() {
    sf::RenderWindow ventana(sf::VideoMode(anchoVentana, altoVentana), "CrossyRoads");
    ventana.setFramerateLimit(60); // Establecer limite de frames

    std::vector<Entidad*> entidades; // Vector de entidades en el juego
    std::vector<bool> carrilesOcupados(altoVentana / espacioEntreCarros, false); // Vector para mantener el estado de los carriles ocupados
    ZonaSegura zonaSegura; // Zona segura para el jugador

    srand(time(nullptr)); // Semilla para la generación de números aleatorios

    sf::RectangleShape jugador(sf::Vector2f(100.0f, 100.0f)); // Forma del jugador
    jugador.setFillColor(sf::Color(0, 100, 0)); // Color verde oscuro para el jugador
    jugador.setPosition(anchoVentana / 2 - jugador.getSize().x / 2, altoVentana - jugador.getSize().y); // Posicion inicial del jugador

    sf::View vista(sf::FloatRect(0, 0, anchoVentana, altoVentana)); // Vista de la ventana
    ventana.setView(vista); // Establecer la vista de la ventana

    sf::RectangleShape calle(sf::Vector2f(anchoVentana, altoVentana)); // Forma de la calle
    calle.setFillColor(sf::Color(100, 100, 100)); // Color gris para la calle

    float temporizadorSpawnCarro = 0.0f; // Temporizador para la aparicion de carros
    float temporizadorInactividad = 0.0f; // Temporizador para rastrear la inactividad del jugador

    sf::Clock reloj; // Reloj para medir el tiempo transcurrido
    sf::Clock inactividadReloj; // Reloj para rastrear la inactividad del jugador

    // Generar zona segura
    reiniciarJuego(jugador, entidades, carrilesOcupados, zonaSegura);

    while (ventana.isOpen()) {
        sf::Time deltaTiempo = reloj.restart(); // Obtener el tiempo transcurrido desde la ultima actualizacion

        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                ventana.close(); // Cerrar la ventana si se detecta el evento de cierre
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && jugador.getPosition().x > 0) {
            jugador.move(-velocidadJugador * deltaTiempo.asSeconds(), 0.0f); // Mover el jugador hacia la izquierda
            temporizadorInactividad = 0.0f; // Restablecer el temporizador de inactividad si el jugador se mueve
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && jugador.getPosition().x < anchoVentana - jugador.getSize().x) {
            jugador.move(velocidadJugador * deltaTiempo.asSeconds(), 0.0f); //
            temporizadorInactividad = 0.0f; // Restablecer el temporizador de inactividad si el jugador se mueve
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            jugador.move(0.0f, -velocidadJugador * deltaTiempo.asSeconds()); // Mover el jugador hacia arriba
            temporizadorInactividad = 0.0f; // Restablecer el temporizador de inactividad si el jugador se mueve
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            jugador.move(0.0f, velocidadJugador * deltaTiempo.asSeconds()); // Mover el jugador hacia abajo
            temporizadorInactividad = 0.0f; // Restablecer el temporizador de inactividad si el jugador se mueve
        }

        // Actualizar el temporizador de inactividad
        temporizadorInactividad += inactividadReloj.restart().asSeconds();
        if (temporizadorInactividad >= tiempoLimiteInactividad) {
            std::cout << "Te has quedado inactivo durante demasiado tiempo. ¡Has perdido el juego!" << std::endl; // Mostrar mensaje de perdida AQUI VA UNA PANTALLA DE GAMEOVER
            ventana.close(); // Cerrar la ventana
        }

        if (jugador.getPosition().y < limiteReinicio) {
            reiniciarJuego(jugador, entidades, carrilesOcupados, zonaSegura); // Reiniciar el juego si el jugador alcanza el limite de reinicio
        }

        temporizadorSpawnCarro += deltaTiempo.asSeconds(); // Actualizar el temporizador de aparicion de carros
        if (temporizadorSpawnCarro >= retrasoSpawnCarro) {
            temporizadorSpawnCarro = 0.0f; // Reiniciar el temporizador de aparicion de carros
            float posY = (rand() % carrilesOcupados.size()) * espacioEntreCarros; // Posicion vertical aleatoria para el nuevo carro

            sf::RectangleShape carroNuevo(sf::Vector2f(150.0f, 80.0f)); // Forma del nuevo carro
            carroNuevo.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256)); // Color aleatorio para el nuevo carro
            carroNuevo.setPosition(-150.0f, posY); // Posicion inicial del nuevo carro fuera de la pantalla

            while (hayColisionJugadorCarro(carroNuevo, entidades)) {
                posY = (rand() % carrilesOcupados.size()) * espacioEntreCarros; // Obtener una nueva posicion vertical si hay colision en el eje x
                carroNuevo.setPosition(-150.0f, posY); // Establecer la nueva posicion del nuevo carro
            }

            float velocidadCarro = velocidadMinimaCarroInicial + (rand() % static_cast<int>(velocidadMaximaCarroInicial - velocidadMinimaCarroInicial + 1)); // Velocidad aleatoria para el nuevo carro
            Carro* nuevoCarro = new Carro(velocidadCarro, posY); // Crear un nuevo objeto carro
            entidades.push_back(nuevoCarro); // Agregar el nuevo carro al vector de entidades
        }

        eliminarCarrosFueraDePantalla(entidades); // Eliminar carros que estan fuera de la pantalla (SI SE QUITA ESTO EL JUEGO SE TRABA)

        // Verificar colisión entre el jugador y los carros
        if (hayColisionJugadorCarro(jugador, entidades)) {
            // Verificar si la colisión ocurrió fuera de la zona segura
            if (jugador.getPosition().y < zonaSegura.posicion.y || jugador.getPosition().y > zonaSegura.posicion.y + zonaSegura.tamano.y) {
                std::cout << "¡Has sido atropellado por un carro fuera de la zona segura! ¡Has perdido el juego!" << std::endl;
                ventana.close(); // Cerrar la ventana
            }
        }

        ventana.clear(); // Limpiar la ventana

        ventana.draw(calle); // Dibujar la calle

        // Dibujar entidades (carros)
        for (const auto& entidad : entidades) {
            entidad->update(deltaTiempo.asSeconds()); // Actualizar la entidad
            entidad->draw(ventana); // Dibujar la entidad
        }

        // Dibujar zona segura
        sf::RectangleShape zonaSeguraRect(sf::Vector2f(zonaSegura.tamano.x, zonaSegura.tamano.y)); // Forma de la zona segura
        zonaSeguraRect.setPosition(zonaSegura.posicion); // Establecer la posición de la zona segura
        zonaSeguraRect.setFillColor(sf::Color(0, 128, 0)); // Color verde sólido para la zona segura
        ventana.draw(zonaSeguraRect); // Dibujar la zona segura en la ventana

        ventana.draw(jugador); // Dibujar al jugador

        ventana.display(); // Mostrar la ventana
    }

    // Limpiar memoria de las entidades al salir del juego
    for (auto& entidad : entidades) {
        delete entidad; // Liberar memoria de la entidad
    }
    entidades.clear(); // Limpiar el vector de entidades

    return 0; // Salir del programa
}
