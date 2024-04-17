#include <iostream>
using namespace std;
/*
 *
 *
 * // funcion para iniciar nivel
//funcion para iniciar juego
void StartGame()
{
    Pantalla();
    while (!GameOver() && !Victoria() && tiempoC)
    {
        ();

        switch (nivel)
        {
            case 1: case 2:
                autos();
                break;

            case 3: case 4: case 5:
                autos();
                animal();
                break;
        }
        //Se encarga de pausar la ejcucion del programa por un tiempo, basicamente duerme el codigo
        //frame es la variable para saber cuanto tiempo
        std::this_thread::sleep_for(std::chrono::milliseconds(frame));
    }
}

 void IniciarNivel()
{
    if (nivel == 1 || nivel == 3) frame = 45;
    else if (nivel == 2 || nivel == 4)
    {
        for (int i = 0; i < 2; ++i)
        {
            if (level == 2)
            {
                boost(autos);
                boost(autosB);
                boost(camionA);
                boost(camionB);
            }
            else
            {
                boost(autos);
                boost(autosB);
                boost(animalA);
                boost(animalB);
            }
        }
        frame = 35;
    }
    else if (nivel == 5)
    {
        for (int i = 0; i < 3; ++i)
        {
            boost(carrosA);
            boost(carrosB);
            boost(animalA);
            boost(animalB);
        }
        frame = 25;
    }
}

//fin del juego
bool GameOver()
{
    if (persona != nullptr && persona->Dead())
    {
        tiempoC = false;
        return true;
    }
    return false;
}
//Victoria
bool GameWin()
{
    if (nivel == nivelMax)
    {
        tiempoC = false;
        return true;
    }
    return false;
}
*/
int main() {
    cout << "Hello, World!" << std::endl;
    return 0;
}
