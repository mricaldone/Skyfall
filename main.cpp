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
#include "clases/Enemigo.hpp"
#include "clases/BonusSalud.hpp"
#include "clases/BonusEnergia.hpp"

#include "clases/Perfil.hpp"
#include "clases/Nivel.hpp"
#include "clases/Puntajes.hpp"

FONT *font_menu_titulo;
FONT *font_menu_subtitulo;
BITMAP *bg_menu;

void cerrarJuego();

#include "include/Utils.hpp"
#include "include/Menu.hpp"
#include "include/Interfaz.hpp"
#include "include/Juego.hpp"

void iniciarJuego(Perfil&,Nivel&,Jugador&);
void finalizarJuego();
void mostrarPuntajes(Nivel);

int main(){
    /*ARRANQUE*/
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

    Perfil perfil;
    Nivel nivel;
    Jugador jugador;

while(1){
    if(!verificarArchivos()){cerrarJuego();return 0;}

    menuSeleccionPerfil(perfil);//DEVUELVE UN PERFIL BORRADO=TRUE SI SE ELIGIO UN SLOT VACIO
    if(perfil.getBorrado()){
        menuCrearNombre(perfil);
        menuSeleccionarRaza(perfil);
        perfil.inicializarPerfil();
        perfil.guardarPerfil();
    }

    while(menuPrincipal(nivel,perfil,jugador)){
        iniciarJuego(perfil,nivel,jugador);
        mostrarPuntajes(nivel);
    }
}
    cerrarJuego();
    return 0;
}
END_OF_MAIN();

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
    destroy_bitmap(bg_menu);
    destroy_font(font_menu_subtitulo);
    destroy_font(font_menu_titulo);
    clear_keybuf();
    remove_keyboard();
    clear(screen);
    allegro_exit();
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
        }
    }
    textout_centre_ex(screen,font,"PRESIONE ESCAPE PARA CONTINUAR",SCREEN_W/2,vertical+12*30, makecol(220,220,220),-1);
    do{
        clear_keybuf();
        readkey();
    }while(!key[KEY_ESC]);
    return;
}
