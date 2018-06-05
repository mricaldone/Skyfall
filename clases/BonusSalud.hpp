#ifndef BONUSSALUD_HPP_INCLUDED
#define BONUSSALUD_HPP_INCLUDED

class BonusSalud: public Objeto{
    private:
    int val_sa;
    public:
    BonusSalud();
    void setValSa(int v){val_sa=v;}
    int getValSa(){return val_sa;}
    bool crearBonus(const Enemigo&);
};

BonusSalud::BonusSalud(){
    val_sa=20;
    setBMP("img/repair.bmp");
}

bool BonusSalud::crearBonus(const Enemigo &en){
    if(display){return false;}
    display=true;
    x=en.getMidX()-getW()/2;
    y=en.getMidY()-getH()/2;
    r=rand()%360;
    vy=en.getVY();
    vx=en.getVX();
    vr=rand()%20-5;
    return true;
}

#endif // BONUSSALUD_HPP_INCLUDED
