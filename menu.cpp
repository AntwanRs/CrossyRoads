#include <iostream>

using namespace std;

int main() {
    int opcion;

    do {
        cout << " ____                                                            ____                           __     \n"
                "/\\  _`\\                                                         /\\  _`\\                        /\\ \\    \n"
                "\\ \\ \\/\\_\\   _ __    ___     ____    ____   __  __               \\ \\ \\L\\ \\     ___      __      \\_\\ \\   \n"
                " \\ \\ \\/_/_ /\\`'__\\ / __`\\  /',__\\  /',__\\ /\\ \\/\\ \\               \\ \\ ,  /    / __`\\  /'__`\\    /'_` \\  \n"
                "  \\ \\ \\L\\ \\\\ \\ \\/ /\\ \\L\\ \\/\\__, `\\/\\__, `\\\\ \\ \\_\\ \\               \\ \\ \\\\ \\  /\\ \\L\\ \\/\\ \\L\\.\\_ /\\ \\L\\ \\ \n"
                "   \\ \\____/ \\ \\_\\ \\ \\____/\\/\\____/\\/\\____/ \\/`____ \\               \\ \\_\\ \\_\\\\ \\____/\\ \\__/.\\_\\\\ \\___,_\\\n"
                "    \\/___/   \\/_/  \\/___/  \\/___/  \\/___/   `/___/> \\               \\/_/\\/ / \\/___/  \\/__/\\/_/ \\/__,_ /\n"
                "                                               /\\___/                                                  \n"
                "                                               \\/__/                                                   " << endl;
        cout << "Menu" << endl;
        cout << "1 Comenzar" << endl;
        cout << "2 Intrucciones para jugar" << endl;
        cout << "3 Escoger personaje" << endl;
        cout << "4 Salir" << endl;
        cout << "Ingrese su opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "start" << endl;
                //aqui se pone el codigo del juego
                break;
            case 2:
                cout << "Instrucciones: " << endl;
                cout << "PASOS PARA JUGAR SDHUDHUSHUD" << endl;
                break;
            case 3:
                cout << "Personajes: " << endl;
                break;
            case 4:
                cout << "Cerrando..." << endl;
                break;
            default:
                cout << "Ingrese una opcion valida" << endl;
        }
    } while (opcion != 4);

    return 0;
}
