#define DIR_PERFILES "perfiles.dat"
#define DIR_NIVELES "niveles.dat"
#define DIR_PUNTAJES "puntajes.dat"

#define FPS 50

#include "allegro.h"

#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cmath>

#include "clases/Fondo.hpp"

#include "clases/Objetos.hpp"
#include "clases/Asteroides.hpp"
#include "clases/Disparos.hpp"
#include "clases/Naves.hpp"
#include "clases/Jugador.hpp"
#include "clases/Bonus.hpp"
#include "clases/Fireball.hpp"

#include "clases/Perfil.hpp"
#include "clases/Nivel.hpp"
#include "clases/Puntajes.hpp"

FONT *font_menu_titulo;
FONT *font_menu_subtitulo;
BITMAP *bg_menu;

void cerrarJuego();

#include "include/Utils.hpp"
#include "include/Menu.hpp"

int VACIO=0;

void iniciarJuego(Perfil&,Nivel&,Jugador&);
void finalizarJuego();
void mostrarPuntajes(Nivel);

int main(){
    /*ARRANQUE*/
    Perfil perfil;
    Nivel nivel;
    Jugador jugador;

    allegro_init();
    install_keyboard();//INSTALA key[] true = PRESIONADO false = LIBERADO
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, 0);
    set_color_depth(16);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,640,480,0,0); //CONFIGURA LA PANTALLA
    set_window_title("SKYFALL");
    srand(time(NULL));

    font_menu_titulo=load_font("fonts/menu_titulo.pcx", NULL, NULL);
    font_menu_subtitulo=load_font("fonts/menu_subtitulo.pcx", NULL, NULL);
    bg_menu=load_bitmap("img/menu.bmp",NULL);

    while(1){
        /*MENU*/
        menu(perfil,nivel,jugador);
        /*JUEGO*/
        //char msg[128];
        //itoa(jugador.getX(),msg,10);
        //allegro_message(msg);
        iniciarJuego(perfil,nivel,jugador);
        mostrarPuntajes(nivel);
    }

    cerrarJuego();
    return 0;
}
END_OF_MAIN();

void iniciarJuego(Perfil &perfil,Nivel &nivel,Jugador &jugador){
    Fondo bg;

    BITMAP* aux;
    BITMAP* buffer=create_bitmap(SCREEN_W,SCREEN_H);

    BITMAP* explosion=create_bitmap(40,40);
    clear_to_color(explosion, makecol(255, 0, 255));

    aux=load_bitmap("img/explosion.bmp",NULL);
    stretch_sprite(explosion, aux, 0, 0, 40, 40);

    SAMPLE* sfx_laser=load_sample("sfx/laser.wav");
    SAMPLE* sfx_explosion=load_sample("sfx/explosion.wav");

    const int maxAst=nivel.getCntAst();
    const int chaAst=nivel.getChaAst();
    Asteroides asteroides[maxAst];

    const int maxBol=0;
    const int chaBol=20;
    FireBall bolas[maxBol];

    const int maxEne=nivel.getCntEne();
    const int chaEne=nivel.getChaEne();//0.3%
    Naves enemigos[maxEne];

    const int maxBon=20;
    const int chaBon=1000;//max 1000%
    Bonus bonus[maxBon];

    const int maxDiEn=20;
    Disparos diEnemigo[maxDiEn];
    cambiarImagen(diEnemigo,"img/proyAzul.bmp",maxDiEn);

    const int maxDiJu=20;
    Disparos diJugador[maxDiJu];
    cambiarImagen(diJugador,"img/proyVerde.bmp",maxDiJu);
    int cDispPausa=0;

    const int maxDiAl=0;
    const int chaDiAl=1000;
    Disparos diAliado[maxDiAl];
    cambiarImagen(diAliado,"img/proyRojo.bmp",maxDiAl);

    int distancia=2000;
    const int tmax=20;

    int c=0;

    int puntaje=0;
    int turbulencia=0;
    int tiempo_salida=50;

    clock_t t;

    while(!key[KEY_ESC] && tiempo_salida>0){
        t=clock();

        clear_keybuf();
        /* FONDO */
        bg.copiarFondo(buffer);

        /* DESPLAZAMIENTO DE OBJETOS */
        for(int i=0;i<tmax;i++){
            for(int j=0;j<tmax;j++){
                /* INTERACCION JUGADOR - BONUS */
                if(j<1 && i<maxBon){
                    interaccionJugadorBonus(jugador,bonus[i]);
                }
                /* INTERACCION DISPARO ENEMIGO - NAVE */
                if(j<maxDiEn && i<1){
                    interaccionDisparoObjeto(diEnemigo[j],jugador,turbulencia,VACIO);
                }
                /* INTERACCION DISPARO ALIADO - ENEMIGO */
                if(j<maxDiAl && i<maxEne){
                    interaccionDisparoObjeto(diAliado[j],enemigos[i],turbulencia,VACIO);
                }
                /* INTERACCION DISPARO ALIADO - ASTEROIDE */
                if(j<maxDiAl && i<maxAst){
                    interaccionDisparoObjeto(diAliado[j],asteroides[i],turbulencia,VACIO);
                }
                /* INTERACCION DISPARO ENEMIGO - ASTEROIDE */
                if(j<maxDiEn && i<maxAst){
                    interaccionDisparoObjeto(diEnemigo[j],asteroides[i],turbulencia,VACIO);
                }
                /* INTERACCION DISPARO JUGADOR - ENEMIGO */
                if(j<maxDiJu && i<maxEne){
                    interaccionDisparoObjeto(diJugador[j],enemigos[i],turbulencia,puntaje);
                }
                /* INTERACCION DISPARO JUGADOR - ASTEROIDE */
                if(j<maxDiJu && i<maxAst){
                    interaccionDisparoObjeto(diJugador[j],asteroides[i],turbulencia,puntaje);
                }
                /* INTERACCION ENEMIGO - NAVE */
                if(j<maxEne && i<1){
                    interaccionObjetoObjeto(enemigos[j],jugador,turbulencia);
                }
                /* INTERACCION ASTEROIDE - NAVE */
                if(j<maxAst && i<1){
                    interaccionObjetoObjeto(asteroides[j],jugador,turbulencia);
                }
                /* OBJETIVO ENEMIGO - ASTEROIDE */
                if(j<maxEne && i<maxAst){
                    if(esObjetivo(enemigos[j],asteroides[i])){
                        /* CREAR DISPARO ENEMIGO */
                        if(maxDiEn>0){
                            if(!diEnemigo[c%maxDiEn].getDisplay() && c%5==0){
                                //crearDisparoEnemigo(diEnemigo[c%(maxDiEn-1)],enemigos[j].getMidX(),enemigos[j].getMidY(),enemigos[j].getVY());
                                diEnemigo[c%maxDiEn].crearDisparo(enemigos[j].getMidX(),enemigos[j].getMidY(),0,enemigos[j].getVY()+10,10);
                                reproducirSonido(sfx_laser);
                            }
                        }
                    }
                }
                /* OBJETIVO ENEMIGO - NAVE */
                if(j<maxEne && i<1){
                    if(esObjetivo(enemigos[j],jugador)){
                        /* CREAR DISPARO ENEMIGO */
                        if(maxDiEn>0){
                            if(!diEnemigo[c%maxDiEn].getDisplay() && c%5==0){
                                //crearDisparoEnemigo(diEnemigo[c%(maxDiEn-1)],enemigos[j].getMidX(),enemigos[j].getMidY(),enemigos[j].getVY());
                                diEnemigo[c%maxDiEn].crearDisparo(enemigos[j].getMidX(),enemigos[j].getMidY(),0,enemigos[j].getVY()+10,10);
                                reproducirSonido(sfx_laser);
                            }
                        }
                    }
                }
            }
            /* MOVER O CREAR BOLAS */
            if(i<maxBol){
                if(!bolas[i].getDisplay() && rand()%1000<=chaBol){
                    crearBola(bolas[i]);
                }
                if(bolas[i].getDisplay()){
                    bolas[i].mover();
                    bolas[i].imprimir(buffer);
                }
            }
            /* MOVER O CREAR ASTEROIDES */
            if(i<maxAst){
                if(!asteroides[i].getDisplay() && rand()%1000<=chaAst){
                    crearAsteroide(asteroides[i]);
                }
                if(asteroides[i].getDisplay()){
                    if(asteroides[i].getPDEF()>0){
                        asteroides[i].mover();
                        asteroides[i].imprimir(buffer);
                    }else{
                        asteroides[i].setDisplay(false);
                        dibujarExplosion(buffer, explosion, asteroides[i].getMidX(), asteroides[i].getMidY());
                        reproducirSonido(sfx_explosion);
                        turbulencia=20;
                        /*CREAR BONUS DE ENERGIA*/
                        if(maxBon>0){
                        if(!bonus[c%maxBon].getDisplay() && rand()%1000<=chaBon){
                            bonus[c%maxBon].setTipo(1);
                            bonus[c%maxBon].setDisplay(true);
                            bonus[c%maxBon].setX(asteroides[i].getMidX()-bonus[c%maxBon].getW()/2);
                            bonus[c%maxBon].setY(asteroides[i].getMidY()-bonus[c%maxBon].getH()/2);
                            bonus[c%maxBon].setR(asteroides[i].getR());
                            bonus[c%maxBon].setVY(asteroides[i].getVY());
                            bonus[c%maxBon].setVX(asteroides[i].getVX());
                            bonus[c%maxBon].setVR(asteroides[i].getVR());
                            bonus[c%maxBon].setPremio(50);
                        }
                        }
                    }
                }
            }
            /* MOVER BONUS */
            if(i<maxBon){
                bonus[i].mover();
                bonus[i].imprimir(buffer);
            }
            /* MOVER O CREAR ENEMIGOS */
            if(i<maxEne){
                if(!enemigos[i].getDisplay() && rand()%1000<=chaEne){
                    crearEnemigo(enemigos[i]);
                }
                if(enemigos[i].getDisplay()){
                    if(enemigos[i].getPDEF()>0){
                        enemigos[i].mover();
                        enemigos[i].imprimir(buffer);
                    }else{
                        enemigos[i].setDisplay(false);
                        dibujarExplosion(buffer, explosion, enemigos[i].getMidX(), enemigos[i].getMidY());
                        reproducirSonido(sfx_explosion);
                        turbulencia=20;
                        /*CREAR BONUS DE SALUD*/
                        if(maxBon>0){
                        if(!bonus[c%maxBon].getDisplay() && rand()%1000<=chaBon){
                            bonus[c%maxBon].setTipo(2);
                            bonus[c%maxBon].setDisplay(true);
                            bonus[c%maxBon].setX(enemigos[i].getMidX()-bonus[c%maxBon].getW()/2);
                            bonus[c%maxBon].setY(enemigos[i].getMidY()-bonus[c%maxBon].getH()/2);
                            bonus[c%maxBon].setR(rand()%180);
                            bonus[c%maxBon].setVY(enemigos[i].getVY());
                            bonus[c%maxBon].setVX(enemigos[i].getVX());
                            bonus[c%maxBon].setVR(rand()%20-5);
                            bonus[c%maxBon].setPremio(10);
                        }
                        }
                    }
                }
            }
            /* MOVER O CREAR DISPAROS ALIADOS */
            if(i<maxDiAl){
                if(!diAliado[i].getDisplay() && rand()%1000<=chaDiAl){
                    //crearDisparoAliado(diAliado[i]);
                    diAliado[i].crearDisparo(rand()%SCREEN_W,SCREEN_H,0,-10,10);
                }
                if(diAliado[i].getDisplay()){
                    diAliado[i].mover();
                    diAliado[i].imprimir(buffer);
                }
            }
            /* MOVER O CREAR DISPAROS JUGADOR */
            if(i<maxDiJu){
                if(!diJugador[i].getDisplay() && key[KEY_SPACE] && cDispPausa==0 && jugador.getDisplay() && jugador.getEnergia()>0){
                    //crearDisparoJugador(diJugador[i],jugador.getMidX(),jugador.getMidY());
                    diJugador[i].crearDisparo(jugador.getMidX(),jugador.getMidY(),0,-10,10);
                    reproducirSonido(sfx_laser);
                    cDispPausa=5;
                    jugador.decEnergia(1);
                }
                if(diJugador[i].getDisplay()){
                    diJugador[i].mover();
                    diJugador[i].imprimir(buffer);
                }
            }
            /* MOVER DISPAROS ENEMIGOS */
            if(i<maxDiEn){
                if(diEnemigo[i].getDisplay()){
                    diEnemigo[i].mover();
                    diEnemigo[i].imprimir(buffer);
                }
            }
            /* MODIFICAR NAVE */
            if(i<1){
                jugador.obtenerTeclado();
                if(jugador.getDisplay()){
                    if(jugador.getPDEF()<=0){
                        jugador.setDisplay(false);
                        dibujarExplosion(buffer, explosion, jugador.getMidX(), jugador.getMidY());
                        reproducirSonido(sfx_explosion);
                        turbulencia=30;
                    }
                }
                if(cDispPausa>0){cDispPausa--;}
                jugador.imprimir(buffer);
            }
        }
        /* END */
        c++;
        if(c>=1000/FPS){c=0;}
        if(distancia>0 && jugador.getDisplay()){distancia--;}
        //if(distancia<=0 || !jugador.getDisplay()){tiempo_salida--;}
        /* IMPRIMIR TODO */
        acquire_screen();
        if(turbulencia<=0){
            draw_sprite(screen, buffer, 0, 0);
        }else{
            draw_sprite(screen, buffer, rand()%turbulencia/3, rand()%turbulencia/3);
            turbulencia--;
        }
        textprintf_ex(screen, font, 10, 10, makecol(255, 100, 200), -1, "Distancia: %d", distancia);
        textprintf_ex(screen, font, 10, 30, makecol(255, 100, 200), -1, "Energia: %d", jugador.getEnergia());
        textprintf_ex(screen, font, 10, 50, makecol(255, 100, 200), -1, "Puntaje: %d", puntaje);
        textprintf_ex(screen, font, 10, 70, makecol(255, 100, 200), -1, "Salud: %d", jugador.getPDEF());
        if(!jugador.getDisplay()){
            textout_centre_ex(screen, font, "JUEGO TERMINADO",SCREEN_W/2,SCREEN_H/2,makecol(255,100,200),-1);
            textout_centre_ex(screen, font, "PRESIONE ESC PARA SALIR",SCREEN_W/2,SCREEN_H-30,makecol(200,200,200),-1);
        }
        release_screen();
        /* IMPRIMIR END */
        t=FPS-(clock()-t)*1000/CLOCKS_PER_SEC;
        if(t<0){t=0;}
        rest(t);
    }
    destroy_bitmap(explosion);
    destroy_bitmap(aux);
    destroy_bitmap(buffer);
    destroy_sample(sfx_explosion);
    destroy_sample(sfx_laser);

    perfil.addCreditos(puntaje);
    perfil.guardarPerfil(perfil.getID());
    Puntaje pts;
    pts.setNivel(nivel.getNivel());
    pts.setNombre(perfil.getNombre());
    pts.setPuntaje(puntaje);
    pts.setRaza(nivel.getRaza());
    pts.guardarPuntaje(pts.proximaPosicion());

    clear_keybuf();
    return;
}
END_OF_FUNCTION(iniciarJuego);

void finalizarJuego(){
    clear_to_color(screen, makecol(0, 0, 0));
    textout_centre_ex(screen, font, "PRESIONE ENTER PARA CONTINUAR",SCREEN_W / 2, SCREEN_H / 2,makecol(255, 100, 200), makecol(0, 0, 0));
    while(!key[KEY_ENTER]){
        rest(10);
    }
    return;
}
END_OF_FUNCTION(finalizarJuego);

void cerrarJuego(){
    remove_keyboard();
    //clear(screen);
    allegro_exit();
    //BOTON_CERRAR=true;
    return;
}
END_OF_FUNCTION(cerrarJuego);

void mostrarPuntajes(Nivel nvl){
    Puntaje reg;
    clear_to_color(screen,makecol(0,0,0));
    int i,vertical=(SCREEN_H-12*30)/2;
    for(i=0;i<10;i++){
        reg=obtenerPuntaje(i,nvl.getRaza(),nvl.getNivel());
        if(reg.getPuntaje()!=0){
        textprintf_centre_ex(screen,font_menu_subtitulo,SCREEN_W/2,vertical+i*30, makecol(255,255,0),-1,"%s %d",reg.getNombre(),reg.getPuntaje());
    }}
    textout_centre_ex(screen,font,"PRESIONE UNA TECLA PARA CONTINUAR",SCREEN_W/2,vertical+12*30, makecol(220,220,220),-1);
    esperarTeclado();
    return;
}
