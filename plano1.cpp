#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <conio.h>
#include <time.h>

using namespace std;
const int WIDTH = 600, HEIGHT = 200; //espacio queva a tener la consola de juego
const int dW = 10, dH = 5;

char obs[12][2][8] =
{
		{
				"+U+    ",
				"+B+    "
		},
};

struct coord{
	int x;
	int y;
};

struct dato{
	coord pos[14];
	char carro[14];
};

dato pasa[12];




void gotoxy(int x, int y) {
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;

    SetConsoleCursorPosition(hcon, dwPos);
}

// Ayuda a plantera todas las figuras que queremos poner en el mapa
void dibujar(char plano[HEIGHT/dH][WIDTH/dW + 1], int a, int b, char c) {
    if (a < 0 || b < 0 || a >= WIDTH/dW || b >= HEIGHT/dH) return;
    plano[b][a] = c;
}

class mapa {
private:
int x, y, c, m;

float vy = 0.0f;

int SB[13] = {0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36}; //se usa para saber la coordenada en los espacios donde se posiciona el personaje a moverse


public:
mapa(int x1, int y1, int c1, int m1){
	x = x1;
	y = y1;
	c = c1;
	m = m1;
}
    void Pmapa(char plano[HEIGHT/dH][WIDTH/dW + 1]) {
        for (int i = 0; i < WIDTH/dW; i++) {
            for (int j = 0; j < HEIGHT/dH; j++) {
                if (i == 0 || i == 59 || j == 0 || j == 39) {
                    dibujar(plano, i, j, '*');
                }
                if (j % 3 == 0)
                    dibujar(plano, i, j, '_');
            }
        }
    }
    void pasar(){
    	for(int t = 0; t<1; t++)
    	{
    		int q = 0;
    		int y;
    		for(int i = 0; i <2; i++)
    		{
    			y = 2 - i;
    			for(int j = 0; j < 7; j++)
    			{
    				if(obs[t][i][j] != ' '){ //si detecta que un espacio esta en blanco guarda el espacio y almacena el caracter
    					pasa[t].pos[q] = {j,y};
    					pasa[t].carro[q] = obs[t][i][j];
    					q++;
    				}
    			}
    		}
    	}
    }
    void draw(char plano[HEIGHT/dH][WIDTH/dW + 1]){
    for(int i = 0; i < 6; i++){
    	dibujar(plano, x + pasa[c].pos[i].x, SB[y]+pasa[c].pos[i].y,pasa[c].carro[i]);//pasa las coordenadas para
    }
    }

    void ejecucion(int &dir){
    	vy -= 1150.0f*0.0416;
    	if(vy >= 752.0f)//vy pasa a 800 despues de la resta vy pasa a valer 752
    		direccion(dir);
    }

    void direccion(int &dir){
    	switch(dir){
    	case 1:
    		y++;
    		dir = 0;
    		break;
    	case 2:
    		x += 2;
    		dir = 0;
    		break;
    	case 3:
    		y --;
    		dir = 0;
    		break;
    	case 4:
    		x -=2;
    		dir = 0;
    		break;
    	}
    }

    void dir2(){
    	if(vy <= 600.0f)
    		vy = 800.0f;
    }
    void esconderCursor() {
        CONSOLE_CURSOR_INFO info;
        info.dwSize = 100;
        info.bVisible = FALSE; // Ocultar cursor
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    }
};
int main() {

    char plano[HEIGHT/dH][WIDTH/dW + 1];

    for (int i = 0; i < HEIGHT/dH; i++)
        plano[i][WIDTH/dW] = '\n';
    plano[HEIGHT/dH][WIDTH/dW] = '\0'; // Esto marca el final de una cadena/arreglo

    mapa j1(28, 0, 0, 0);
    j1.esconderCursor();
    float fps = 24.0f; //valor en flotante 0.416
    float dt = 1.0f/fps;
    float acumular = 0.0f;

    clock_t inicio = clock(); //tiempo donde se ejecuta el programa

    bool game = true;

    int dir = 0;

    j1.pasar();

    while (game) {

    	clock_t final = clock(); //el final tenga el valor de procesamiento
    	acumular += float(final - inicio)/CLOCKS_PER_SEC; //tiempo que pasa entre creacion de variables
    	inicio = final; //cicla

    	if(acumular >= 0.2f) acumular = 2.0f;

    	while (acumular >= dt){
    		if(GetKeyState(VK_UP)&0x8000){//llama al teclado en lugar de un gets
    			j1.dir2();
    			dir = 1;
    		}
    		if(GetKeyState(VK_DOWN)&0x8000){//llama al teclado en lugar de un gets
    			j1.dir2();
    			dir = 3;
    		    		}
    		if(GetKeyState(VK_RIGHT)&0x8000){//llama al teclado en lugar de un gets
    			j1.dir2();
    			dir = 2;
    		    		}
    		if(GetKeyState(VK_LEFT)&0x8000){//llama al teclado en lugar de un gets
    			j1.dir2();
    			dir = 4;
    		    		}
    		if(GetKeyState(VK_ESCAPE)&0x8000){//llama al teclado en lugar de un gets
    		    	game = false;
    		    		}
    		j1.ejecucion(dir);
    		acumular -= dt;
    	}
        for (int i = 0; i < HEIGHT/dH; i++) {
            for (int j = 0; j < WIDTH/dW; j++) {
                plano[i][j] = ' ';
            }
        }
        j1.Pmapa(plano);
        j1.draw(plano);
        gotoxy(0, 0);
        puts(plano[0]);
    }
}

