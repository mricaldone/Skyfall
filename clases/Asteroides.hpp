#ifndef ASTEROIDES_HPP_INCLUDED
#define ASTEROIDES_HPP_INCLUDED

class Asteroide: public Objeto{
    private:
        int salud;
        int premio;
    public:
        Asteroide();
        int getSalud(){return salud;}
        int getPremio(){return premio;}
        void setSalud(int v){salud=v;}
        void decSalud(int v){salud-=v;}
        void crearAsteroide();
};

Asteroide::Asteroide(){
    salud=0;
    setBMP("img/asteroide.bmp");
}

void Asteroide::crearAsteroide(){
    if(display){return;}
    int aux=rand()%40+30;
    cambiarTamano(aux,aux);
    x=rand()%SCREEN_W;
    y=-bmp->h;
    r=rand()%359;
    vx=rand()%4-2;
    vy=rand()%12+6;
    vr=rand()%20-10;
    salud=aux-25;
    premio=aux%10;
    display=true;
}

#endif // ASTEROIDES_HPP_INCLUDED
