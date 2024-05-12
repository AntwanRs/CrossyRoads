// CrossyRoadVS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

#define Max_main_menu 4

class MainMenu
{
    //solo a llamadas internas
private:
    int MainMenuSelected;
    Font font;
    Text mainMenu[Max_main_menu];
    //podemos accesar por fuera
public:
    MainMenu(float ancho, float alto);

    void dibujar(RenderWindow& window);
    void MoveUp();
    void MoveDown();

    int MainMenuPressed() {
        return MainMenuSelected;
    }

    ~MainMenu();


int main() {
    //color en el txt

    string green = "\033[1;32m";

    cout << green;
    cout << " --------------------------------------------------------------------------\n";
    cout << " |                                                                        |\n";
    cout << " |                                                                        |\n";
    cout << " |                              GAME OVER                                 |\n";
    cout << " |                                                                        |\n";
    cout << " |                                SALIR                                   |\n";
    cout << " |                                                                        |\n";
    cout << " |                           JUGAR DE NUEVO                               |\n";
    cout << " |                                                                        |\n";
    cout << " |                                                                        |\n";
    cout << " --------------------------------------------------------------------------\n";

    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file