#ifndef JUGADOR_HPP_INCLUDED
#define JUGADOR_HPP_INCLUDED

class Jugador: public Nave{
    public:
        void obtenerTeclado();
        void crearJugador(int,int);
};

void Jugador::obtenerTeclado(){
    if(display){
        if(key[KEY_LEFT] && x>0){
            x-=10;
        }
        if(key[KEY_RIGHT] && x<SCREEN_W-bmp->w){
            x+=10;
        }
    }
}

void Jugador::crearJugador(int vRaza,int cod){
    definirNave(vRaza,cod);
    y=SCREEN_H-100;
    x=SCREEN_W/2-bmp->w/2;
    r=180;
    display=true;
}

#endif // JUGADOR_HPP_INCLUDED
