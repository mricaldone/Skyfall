#ifndef ENEMIGO_HPP_INCLUDED
#define ENEMIGO_HPP_INCLUDED

class Enemigo: public Nave{
    public:
        bool crearEnemigo(int,int);
};

bool Enemigo::crearEnemigo(int vRaza,int dif){
    if(display){return false;}
    if(vRaza==1){vRaza=2;}else{vRaza=1;}
    definirNave(vRaza,rand()%dif+1);
    x=rand()%SCREEN_W;
    y=-getH();
    vy=rand()%9+7;
    display=true;
    return true;
}

#endif // ENEMIGO_HPP_INCLUDED
