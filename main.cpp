#include <allegro.h>
#include <iostream>
#include <stdlib.h>
#include <conio.h>

using namespace std;

void mover_avion(float &cx, float &cy, float &vx, float &vy);
void mover_torre(float &x,float &y, float &bx, float &by);
bool verificar_colision(float ax, float ay, float aw, float ah, float bx, float by, float bw, float bh);

int main()
{
    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,700,450,0,0);

    BITMAP* buffer=create_bitmap(700,450);
    BITMAP* avion=load_bitmap("nave.bmp",NULL);
    BITMAP* torre=load_bitmap("torre.bmp",NULL);
    BITMAP* nube1=load_bitmap("nube.bmp",NULL);

    float cx, cy,x,y;//posición avion y torre
    float vx,vy,bx,by; //gravedad y movimientos
    cx = 100, cy = 200;
    x=350, y=200;
    vx = vy = bx = by = 0; //inicializar en 0 para evitar parpadeo de imagenes o alternacion
    int puntos = 0; // Inicializa el contador de puntos

    while (!key[KEY_ESC])
    {

     clear_to_color(buffer, 0x64D1F7);
     masked_blit(avion,buffer,25,45,cx,cy,75,35);
     masked_blit(torre,buffer,332,100,x,y,56,420);

    int nubeX = x + 300; // Ajusta según sea necesario
    int nubeY = -10; // Ajusta según sea necesario
    masked_blit(nube1, buffer, 30, 90, nubeX, nubeY, 300, 180);

    blit(buffer,screen,0,0,0,0,700,450);

    mover_avion(cx,cy,vx,vy);
    mover_torre(x,y,bx,by);

    rest(10);

     if (key[KEY_UP]){
             masked_blit(avion, buffer, 25, 45, cx, cy -= 10, 75, 35);
            // Dibuja la torre en el buffer
            masked_blit(torre, buffer, 332, 100, x, y, 56, 420);
            // Dibuja el buffer en la pantalla
            masked_blit(nube1, buffer, 30, 90, nubeX, nubeY, 300, 180);
            blit(buffer, screen, 0, 0, 0, 0, 700, 450);
        //blit(avion,screen,0,0,cx,cy-=10,410,190);
    }
    if (verificar_colision(cx, cy, 75, 35, x, y, 56, 420) || verificar_colision(cx, cy, 75, 35, nubeX, nubeY, 300, 180)) {
    textout_ex(screen, font, "GAME OVER", 700 / 2 - 100, 450 / 2 - 20, makecol(255, 255, 0), -1);
    rest(2000); // Espera 2 segundos antes de salir
    break;
        }
        // Mueve la nube hacia la izquierda y reinicia su posición después de completar el ciclo
        nubeX -= 0.5;
        if (nubeX < -300)
        {
            nubeX = 900;
        }
    rest (10);
    }
    destroy_bitmap(buffer);
    destroy_bitmap(avion);
    destroy_bitmap(torre);
    destroy_bitmap(nube1);
    return 0;
}
END_OF_MAIN();

void mover_avion(float &cx, float &cy, float &vx, float &vy){
    float ax, ay;
    ax = 0;
    ay = 0.005;

    vx += ax;
    vy += ay;

    cx += vx;
    cy += vy;
}
void mover_torre(float &x, float &y, float &bx, float &by) {
   float ex, ey;
   ex = -0.02;
   ey = 0;

   bx += ex;
   by += ey;

   x += bx;
   y += by;

if (x < -56) {
        x = 700; //bucle del edificio
    }
}
// Función para verificar la colisión entre las figuras
bool verificar_colision(float ax, float ay, float aw, float ah, float bx, float by, float bw, float bh) {
    return ax < bx + bw && ax + aw > bx && ay < by + bh && ay + ah > by;
}
