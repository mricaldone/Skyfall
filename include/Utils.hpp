#ifndef UTILS_HPP_INCLUDED
#define UTILS_HPP_INCLUDED

#define PI 3.14159265

bool colision(const Objeto &obj1,const Objeto &obj2){
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

bool esObjetivo(const Objeto &obj1,const Objeto &obj2){
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

void interaccionDisparoNave(Disparo &di,Enemigo &nv,int &turbulencia,int &puntaje){
    if(!di.getDisplay() || !nv.getDisplay()){return;}
    if(colision(di,nv)){
        di.setDisplay(false);
        nv.decSalud(di.getPoder());
        turbulencia=10;
        if(nv.getSalud()<=0){puntaje+=nv.getPremio();}
    }
}

void interaccionDisparoNave(Disparo &di,Jugador &nv,int &turbulencia,int &puntaje){
    if(!di.getDisplay() || !nv.getDisplay()){return;}
    if(colision(di,nv)){
        di.setDisplay(false);
        nv.decSalud(di.getPoder());
        turbulencia=10;
    }
}

void interaccionDisparoAsteroide(Disparo &di,Asteroide &as,int &turbulencia,int &puntaje){
    if(!di.getDisplay() || !as.getDisplay()){return;}
    if(colision(di,as)){
        di.setDisplay(false);
        as.decSalud(di.getPoder());
        turbulencia=5;
        if(as.getSalud()<=0){puntaje+=as.getPremio();}
    }
}

void interaccionDisparoAsteroide2(Disparo &di,Asteroide &as,int &turbulencia){
    if(!di.getDisplay() || !as.getDisplay()){return;}
    if(colision(di,as)){
        di.setDisplay(false);
        as.decSalud(di.getPoder());
        turbulencia=5;
    }
}

void interaccionObjetoJugador(Asteroide &ob1,Jugador &ob2,int &turbulencia){
    if(!ob1.getDisplay() || !ob2.getDisplay()){return;}
    if(colision(ob1,ob2)){
        ob1.setSalud(0);
        ob2.decSalud(ob1.getW());
        turbulencia=20;
    }
}

void interaccionObjetoJugador(Enemigo &ob1,Jugador &ob2,int &turbulencia){
    if(!ob1.getDisplay() || !ob2.getDisplay()){return;}
    if(colision(ob1,ob2)){
        ob1.setSalud(0);
        ob2.setSalud(0);
        turbulencia=20;
    }
}

void interaccionJugadorBonus(Jugador &ob1,BonusEnergia &ob2){
    if(!ob1.getDisplay() || !ob2.getDisplay()){return;}
    if(colision(ob1,ob2)){
        ob1.addEnergia(ob2.getValEn());
        ob2.setDisplay(false);
    }
}
void interaccionJugadorBonus(Jugador &ob1,BonusSalud &ob2){
    if(!ob1.getDisplay() || !ob2.getDisplay()){return;}
    if(colision(ob1,ob2)){
        ob1.addSalud(ob2.getValSa());
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
/*
void crearAsteroide(Asteroide &obj){
    int auxInt=rand()%40+30;
    obj.cambiarTamano(auxInt,auxInt);
    obj.setX(rand()%SCREEN_W);
    obj.setY(-obj.getH());
    obj.setR(rand()%359);
    obj.setVX(rand()%4-2);
    obj.setVY(rand()%12+6);
    obj.setVR(rand()%20-10);
    obj.setSalud(auxInt-25);
    obj.setDisplay(true);
}
*/
/*
void crearEnemigo(Enemigo &obj){
    obj.setX(rand()%SCREEN_W);
    obj.setY(-obj.getH());
    obj.setVY(rand()%9+7);
    obj.setSalud(30);
    obj.setDisplay(true);
    obj.setPremio(10);
}
*/
void cambiarImagenDisparo(Disparo *obj,const char* dir,int tam){
    for(int i=0;i<tam;i++){
        obj[i].setBMP(dir);
    }
}

void reproducirSonido(SAMPLE* &sfx){
    play_sample(sfx, 255, 128, 1000, 0);
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
