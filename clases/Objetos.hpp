#ifndef OBJETOS_HPP_INCLUDED
#define OBJETOS_HPP_INCLUDED

class Objeto{

    protected:
    BITMAP* bmp;
    BITMAP* ori;
    int x,y,r,vx,vy,vr;
    bool display;

    public:
    Objeto();
    //Objetos(const Objetos&);
    void imprimir(BITMAP*);
    void mover();
    ~Objeto();

    void destruir();//???
    void setBMP(const char*);
    void cambiarTamano(int, int);

    int getX() const{return x;}
    int getY() const{return y;}
    int getR() const{return r;}
    int getH() const{return bmp->h;}
    int getW() const{return bmp->w;}
    int getVX() const{return vx;}
    int getVY() const{return vy;}
    int getVR() const{return vr;}
    int getMidX() const{return x+bmp->w/2;}
    int getMidY() const{return y+bmp->h/2;}
    bool getDisplay() const{return display;}

    void setX(int v){x=v;}
    void setY(int v){y=v;}
    void setR(int v){r=v;}
    void setVX(int v){vx=v;}
    void setVY(int v){vy=v;}
    void setVR(int v){vr=v;}
    void setDisplay(bool v){display=v;}
};

Objeto::Objeto(){
    bmp=create_bitmap(1,1);//???
    ori=create_bitmap(1,1);//???
    x=0;
    y=0;
    r=0;
    vx=0;
    vy=0;
    vr=0;
    display=false;
}
/*
Objetos::Objetos(const Objetos& obj){
    bmp=create_bitmap(obj.bmp->w,obj.bmp->h);
    draw_sprite(bmp, obj.bmp, 0, 0);
    ori=create_bitmap(obj.ori->w,obj.ori->h);
    draw_sprite(ori, obj.ori, 0, 0);
    x=obj.x;
    y=obj.y;
    r=obj.r;
    vx=obj.vx;
    vy=obj.vy;
    vr=obj.vr;
    patk=obj.patk;
    pdef=obj.pdef;
    display=obj.display;
}
*/
void Objeto::imprimir(BITMAP* destino){
    if(!display){return;}
    float aux=(r*256)/360;
    rotate_sprite(destino,bmp,x,y,ftofix(aux));
}

void Objeto::mover(){
    x+=vx;
    y+=vy;
    r+=vr;
    if(x<0-(bmp->w) || y<0-(bmp->h) || x>SCREEN_W || y>SCREEN_H){display=false;}
}

void Objeto::setBMP(const char* img){
    destroy_bitmap(bmp);
    bmp=load_bitmap(img,NULL);
    destroy_bitmap(ori);
    ori=load_bitmap(img,NULL);
}

void Objeto::cambiarTamano(int ancho,int alto){
    destroy_bitmap(bmp);
    bmp=create_bitmap(ancho, alto);
    clear_to_color(bmp, makecol(255, 0, 255));
    stretch_sprite(bmp, ori, 0, 0, ancho, alto);
}

void Objeto::destruir(){
    destroy_bitmap(bmp);
    destroy_bitmap(ori);
}

Objeto::~Objeto(){
    destroy_bitmap(bmp);
    destroy_bitmap(ori);
}

#endif // OBJETOS_HPP_INCLUDED
