#ifndef BONUSENERGIA_HPP_INCLUDED
#define BONUSENERGIA_HPP_INCLUDED

class BonusEnergia: public Objeto{
    private:
    int val_en;
    public:
    BonusEnergia();
    void setValEn(int v){val_en=v;}
    int getValEn(){return val_en;}
    bool crearBonus(const Asteroide&);
};

BonusEnergia::BonusEnergia(){
    val_en=50;
    setBMP("img/energy.bmp");
}

bool BonusEnergia::crearBonus(const Asteroide &as){
    if(display){return false;}
    display=true;
    x=as.getMidX()-getW()/2;
    y=as.getMidY()-getH()/2;
    r=as.getR();
    vx=as.getVX();
    vy=as.getVY();
    vr=as.getVR();
    return true;
}

#endif // BONUSENERGIA_HPP_INCLUDED
