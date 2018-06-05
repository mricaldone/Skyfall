#ifndef NAVES_HPP_INCLUDED
#define NAVES_HPP_INCLUDED

class Nave: public Objeto{
    private:
        int salud;
        int poder;
        int energia;
        int max_salud;
        int max_energia;
        int premio;
    public:
        Nave();
        void definirNave(int,int);

        void setSalud(int v){salud=v;}
        void setEnergia(int v){energia=v;}
        void setPoder(int v){poder=v;}
        void setPremio(int v){premio=v;}

        int getSalud(){return salud;}
        int getEnergia(){return energia;}
        int getPoder(){return poder;}
        int getMaxSalud(){return max_salud;}
        int getMaxEnergia(){return max_energia;}
        int getPremio(){return premio;}

        void addSalud(int);
        void addEnergia(int v);

        void decSalud(int);
        void decEnergia(int v);
};

Nave::Nave(){
    salud=0;
    poder=0;
    energia=0;
    max_salud=0;
    max_energia=0;
    premio=0;
}

void Nave::addSalud(int v){
    if(v<0){return;}
    if(salud+v<=max_salud){
        salud+=v;
    }else{
        salud=max_salud;
    }
}

void Nave::decSalud(int v){
    if(v<0){return;}
    if(salud-v>=0){
        salud-=v;
    }else{
        salud=0;
    }
}

void Nave::addEnergia(int v){
    if(v<0){return;}
    if(energia+v<=max_energia){
        energia+=v;
    }else{
        energia=max_energia;
    }
}

void Nave::decEnergia(int v){
    if(v<0){return;}
    if(energia-v>=0){
        energia-=v;
    }else{
        energia=0;
    }
}

void Nave::definirNave(int vRaza,int cod){
    switch(vRaza){
        case 1:
            switch(cod){
                case 1:setBMP("img/navHumano_1.bmp");premio=10;max_salud=60;salud=max_salud;poder=10;max_energia=150;energia=max_energia;break;
                case 2:setBMP("img/navHumano_2.bmp");premio=20;max_salud=110;salud=max_salud;poder=15;max_energia=200;energia=max_energia;break;
                case 3:setBMP("img/navHumano_3.bmp");premio=40;max_salud=160;salud=max_salud;poder=20;max_energia=250;energia=max_energia;break;
                case 4:setBMP("img/navHumano_4.bmp");premio=80;max_salud=210;salud=max_salud;poder=25;max_energia=300;energia=max_energia;break;
            }
        break;
        case 2:
            switch(cod){
                case 1:setBMP("img/navAlien_1.bmp");premio=10;max_salud=30;salud=max_salud;poder=20;max_energia=150;energia=max_energia;break;
                case 2:setBMP("img/navAlien_2.bmp");premio=20;max_salud=55;salud=max_salud;poder=30;max_energia=200;energia=max_energia;break;
                case 3:setBMP("img/navAlien_3.bmp");premio=40;max_salud=80;salud=max_salud;poder=40;max_energia=250;energia=max_energia;break;
                case 4:setBMP("img/navAlien_4.bmp");premio=80;max_salud=105;salud=max_salud;poder=50;max_energia=300;energia=max_energia;break;
            }
        break;
    }
}

#endif // NAVES_HPP_INCLUDED
