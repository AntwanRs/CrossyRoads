#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

#define Max_Default 7

class DefaultScreen
{
    //solo a llamadas internas
private:
    bool iniciarPressed;
    Font font;
    Text titulo;
    Text instrucciones;
    Text personitas;
    Text nose;
    //podemos accesar por fuera
public:
    DefaultScreen(float ancho, float alto);

    void draw(RenderWindow& window);

    void setIniciarPressed(bool status);

    bool getIniciarPressed(); 

    ~DefaultScreen();
};
