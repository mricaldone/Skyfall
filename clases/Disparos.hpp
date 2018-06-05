#ifndef DISPAROS_HPP_INCLUDED
#define DISPAROS_HPP_INCLUDED

class Disparo: public Objeto{
    private:
        int poder;
    public:
        Disparo();
        void setPoder(int v){poder=v;}
        int getPoder(){return poder;}
        bool crearDisparo(int,int,int,int,int);
};

Disparo::Disparo(){
    poder=0;
}

bool Disparo::crearDisparo(int posx,int posy,int velx,int vely,int powatk){
    if(display){return false;}
    x=posx-bmp->w/2;
    y=posy-bmp->h/2;
    vx=velx;
    vy=vely;
    poder=powatk;
    display=true;
    return true;
}

#endif // DISPAROS_HPP_INCLUDED
