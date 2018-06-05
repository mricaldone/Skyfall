#ifndef UTILS_HPP_INCLUDED
#define UTILS_HPP_INCLUDED

#define PI 3.14159265

bool colision(const Objetos &obj1,const Objetos &obj2){
    if(!obj1.getDisplay() || !obj2.getDisplay()){return false;}
    int w1=obj1.getW();
    int h1=obj1.getH();
    int x1=obj1.getX();
    int y1=obj1.getY();
    int w2=obj2.getW();
    int h2=obj2.getH();
    int x2=obj2.getX();
    int y2=obj2.getY();
    if(
       (
       (x1>=x2 && x1<=x2+w2)
       ||
       (x2>=x1 && x2<=x1+w1)
        )&&(
       (y1>=y2 && y1<=y2+h2)
       ||
       (y2>=y1 && y2<=y1+h1)
        )
    ){
        return true;
    }
    return false;
}

void dibujarExplosion(BITMAP* &destino,BITMAP* &fuente,int x,int y){
    x-=fuente->w/2;
    y-=fuente->h/2;
    draw_sprite(destino, fuente, x, y);
}

bool esObjetivo(const Objetos &obj1,const Objetos &obj2){
    if(!obj1.getDisplay() || !obj2.getDisplay()){return false;}
    int w1=obj1.getW();
    int x1=obj1.getX();
    int w2=obj2.getW();
    int x2=obj2.getX();
    if((x1>=x2 && x1<=x2+w2)||(x2>=x1 && x2<=x1+w1)){
        return true;
    }
    return false;
}

void interaccionDisparoObjeto(Disparos &di,Objetos &ob,int &turbulencia,int &puntaje){
    if(!di.getDisplay() || !ob.getDisplay()){return;}
    if(colision(di,ob)){
        di.setDisplay(false);
        ob.decPDEF(di.getPATK());
        turbulencia=10;
        if(ob.getPDEF()<=0){puntaje+=ob.getPTS();}
    }
}

void interaccionObjetoObjeto(Objetos &ob1,Objetos &ob2,int &turbulencia){
    if(!ob1.getDisplay() || !ob2.getDisplay()){return;}
    if(colision(ob1,ob2)){
        ob1.setPDEF(0);
        ob2.setPDEF(0);
        turbulencia=20;
    }
}

void interaccionJugadorBonus(Jugador &ob1,Bonus &ob2){
    if(!ob1.getDisplay() || !ob2.getDisplay()){return;}
    if(colision(ob1,ob2)){
            switch(ob2.getTipo()){
            case 1:
                ob1.addEnergia(ob2.getPremio());
                break;
            case 2:
                ob1.addPDEF(ob2.getPremio());
                break;
            }
        ob2.setPremio(0);
        ob2.setDisplay(false);
    }
}
/*
void crearDisparoAliado(Disparos &obj){
    obj.setX(rand()%SCREEN_W);
    obj.setY(SCREEN_H);
    obj.setVX(0);
    obj.setVY(-10);
    obj.setPATK(10);
    obj.setDisplay(true);
}

void crearDisparoJugador(Disparos &obj,int x,int y){
    obj.setX(x-obj.getW()/2);
    obj.setY(y-obj.getH()/2);
    obj.setVX(0);
    obj.setVY(-10);
    obj.setPATK(10);
    obj.setDisplay(true);
}

void crearDisparoEnemigo(Disparos &obj,int x,int y,int vy){
    obj.setX(x-obj.getW()/2);
    obj.setY(y-obj.getH()/2);
    obj.setVX(0);
    obj.setVY(10+vy);
    obj.setPATK(10);
    obj.setDisplay(true);
}
*/
void crearAsteroide(Objetos &obj){
    int auxInt=rand()%40+30;
    obj.cambiarTamano(auxInt,auxInt);
    obj.setX(rand()%SCREEN_W);
    obj.setY(-obj.getH());
    obj.setR(rand()%359);
    obj.setVX(rand()%4-2);
    obj.setVY(rand()%12+6);
    obj.setVR(rand()%20-10);
    obj.setPDEF(auxInt-25);
    obj.setDisplay(true);
    obj.setPTS(1);
}

void crearEnemigo(Objetos &obj){
    obj.setX(rand()%SCREEN_W);
    obj.setY(-obj.getH());
    obj.setVY(rand()%9+7);
    obj.setPDEF(30);
    obj.setDisplay(true);
    obj.setPTS(10);
}

void cambiarImagen(Objetos *obj,const char* dir,int tam){
    for(int i=0;i<tam;i++){
        obj[i].iniciar(dir);
    }
}

void reproducirSonido(SAMPLE* &sfx){
    //play_sample(sfx, 255, 128, 1000, 0);
}

void crearBola(FireBall &obj){
    obj.setX(rand()%SCREEN_W);
    obj.setY(-obj.getH());
    int dx=1;
    int dy=15+rand()%5;
    obj.setVX(dx);
    obj.setVY(dy);
    obj.setR(-5);
    obj.setDisplay(true);
}

void getText(char* salida,int tam,int x,int y,int color,FONT* &fuente,bool center=false){
    char ASCII;
    int pos=0;
    int tw=text_length(fuente, "W")*tam;
    int th=text_height(fuente);

    if(center){rectfill(screen, (SCREEN_W/2)-(tw/2), y, (SCREEN_W/2)+(tw/2), y+th, makecol(0,0,0));}
    else{rectfill(screen, x, y, x+tw, y+th, makecol(0,0,0));}

    do{
        clear_keybuf();
        ASCII=readkey()&0xff;
        if(ASCII==8){pos--;}
        if(pos<0){pos=0;}
        if((ASCII==95 || (ASCII>=65 && ASCII<=90) || (ASCII>=97 && ASCII<=122)) && pos<tam){salida[pos]=ASCII;pos++;}
        //32 A 126
        salida[pos]='\0';

        if(center){
            rectfill(screen, (SCREEN_W/2)-(tw/2), y, (SCREEN_W/2)+(tw/2), y+th, makecol(0,0,0));
            textprintf_centre_ex(screen, fuente, x, y, color, -1, salida);
        }else{
            rectfill(screen, x, y, x+tw, y+th, makecol(0,0,0));
            textprintf_ex(screen, fuente, x, y, color, -1, salida);
        }
    }while(!key[KEY_ENTER]);
}

void esperarTeclado(){
    clear_keybuf();
    readkey();
    clear_keybuf();
}

#endif // UTILS_HPP_INCLUDED
