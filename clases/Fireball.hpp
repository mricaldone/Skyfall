#ifndef FIREBALL_HPP_INCLUDED
#define FIREBALL_HPP_INCLUDED

class FireBall{
private:
    BITMAP* bmp;
    BITMAP* ori;
    int cut;
    int con;
    int tim_con;
    int tim_max;
    bool display;
    int vx,x,vy,y,w,h,r;
public:
    FireBall(){
        bmp=load_bitmap("img/fireball.bmp",NULL);
        ori=load_bitmap("img/fireball.bmp",NULL);
        cut=32;
        con=0;
        tim_con=0;
        tim_max=2;
        display=false;
        x=0;
        y=0;
        vy=0;
        vx=0;
        h=51;
        w=20;
        //r=0;
        nextFrame();
    }
    void mover(){
        x+=vx;
        y+=vy;
        if(x<0-w || y<0-h || x>SCREEN_W || y>SCREEN_H){display=false;}
    }
    void imprimir(BITMAP* destino){
        if(!display){return;}
        rotate_sprite(destino,bmp,x,y,itofix(r));
        tim_con++;
        nextFrame();
    }
    void nextFrame(){
        if(tim_con%tim_max!=0){return;}
        if(con>3){con=0;}
        destroy_bitmap(bmp);
        bmp=create_bitmap(w,h);
        clear_to_color(bmp,makecol(255,0,255));
        draw_sprite(bmp,ori,-con*w,0);
        con++;
        tim_con=0;
    }
    bool getDisplay(){return display;}
    int getH(){return h;}
    void setX(int v){x=v;}
    void setY(int v){y=v;}
    void setVX(int v){vx=v;}
    void setVY(int v){vy=v;}
    void setR(int v){r=v;}
    void setDisplay(bool v){display=v;}
};

#endif // FIREBALL_HPP_INCLUDED
