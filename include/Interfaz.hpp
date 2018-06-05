#ifndef INTERFAZ_HPP_INCLUDED
#define INTERFAZ_HPP_INCLUDED

void barraSalud(const int vSalud,const int vMax,BITMAP* &out,BITMAP* &b1,BITMAP* &b2){
    const int w=150;
    const int h=15;
    const int y=10;
    //rectfill(out, SCREEN_W-w-10, y, SCREEN_W-10, y+10, makecol(255,0,0));
    stretch_sprite(out, b1, SCREEN_W-w-10, y, w, h);
    int a=w*vSalud/vMax;
    stretch_sprite(out, b2, SCREEN_W-a-10, y, a, h);
    //rectfill(out, SCREEN_W-a-10, y, SCREEN_W-10, y+10, makecol(0,255,0));
    textprintf_right_ex(out, font, SCREEN_W-20, y+5, makecol(230, 100, 0), -1, "%d/%d", vSalud, vMax);
}

void barraEnergia(const int vEnergia,const int vMax,BITMAP* &out,BITMAP* &b1,BITMAP* &b2){
    const int w=150;
    const int h=15;
    const int y=35;
    //rectfill(out, SCREEN_W-w-10, y, SCREEN_W-10, y+10, makecol(0,128,255));
    stretch_sprite(out, b1, SCREEN_W-w-10, y, w, h);
    int a=w*vEnergia/vMax;
    stretch_sprite(out, b2, SCREEN_W-a-10, y, a, h);
    //rectfill(out, SCREEN_W-a-10, y, SCREEN_W-10, y+10, makecol(255,255,0));
    textprintf_right_ex(out, font, SCREEN_W-20, y+5, makecol(230, 100, 0), -1, "%d/%d", vEnergia, vMax);
}

#endif // INTERFAZ_HPP_INCLUDED
