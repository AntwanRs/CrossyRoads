#include <iostream>

int main() {
    //color en el txt

    std::string green = "\033[1;32m";

    std::cout << green;
    std::cout << " --------------------------------------------------------------------------\n";
    std::cout << " |                                                                        |\n";
    std::cout << " |                                                                        |\n";
    std::cout << " |                              GAME OVER                                 |\n";
    std::cout << " |                                                                        |\n";
    std::cout << " |                                SALIR                                   |\n";
    std::cout << " |                                                                        |\n";
    std::cout << " |                           JUGAR DE NUEVO                               |\n";
    std::cout << " |                                                                        |\n";
    std::cout << " |                                                                        |\n";
    std::cout << " --------------------------------------------------------------------------\n";

    return 0;
}
