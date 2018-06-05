#ifndef BONUS_HPP_INCLUDED
#define BONUS_HPP_INCLUDED

class BonusEnergia: public Objeto{
    private:
    int val_en;
    public:
    BonusEnergia();
    void setValEn(int v){val_en=v;}
    int getValEn(){return tipo;}
};

BonusEnergia::BonusEnergia(){
    setBMP("img/energy.bmp");
}

#endif // BONUS_HPP_INCLUDED
