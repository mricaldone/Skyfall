#include "allegro.h"
#include "Objetos.hpp"

Objetos::Objetos(){
    x=0;
    y=0;
    r=0;
    vx=0;
    vy=0;
    vr=0;
    pdef=0;
    patk=0;
    display=false;
}
/*
Objetos::Objetos(const Objetos& obj){
    bmp=create_bitmap(obj.bmp->w,obj.bmp->h);
    draw_sprite(bmp, obj.bmp, 0, 0);
    ori=create_bitmap(obj.ori->w,obj.ori->h);
    draw_sprite(ori, obj.ori, 0, 0);
    x=obj.x;
    y=obj.y;
    r=obj.r;
    vx=obj.vx;
    vy=obj.vy;
    vr=obj.vr;
    patk=obj.patk;
    pdef=obj.pdef;
    display=obj.display;
}
*/
void Objetos::imprimir(BITMAP* destino){
    if(!display){return;}
    rotate_sprite(destino,bmp,x,y,itofix(r));
}

void Objetos::mover(){
    x+=vx;
    y+=vy;
    r+=vr;
    if(x<0-(bmp->w) || y<0-(bmp->h) || x>SCREEN_W || y>SCREEN_H){display=false;}
}

void Objetos::iniciar(const char* img){
    bmp=load_bitmap(img,NULL);
    ori=load_bitmap(img,NULL);
}

void Objetos::cambiarTamano(int ancho,int alto){
    destroy_bitmap(bmp);
    bmp=create_bitmap(ancho, alto);
    clear_to_color(bmp, makecol(255, 0, 255));
    stretch_sprite(bmp, ori, 0, 0, ancho, alto);
}

void Objetos::destruir(){
    destroy_bitmap(bmp);
    destroy_bitmap(ori);
}

Objetos::~Objetos(){
    destroy_bitmap(bmp);
    destroy_bitmap(ori);
}




