#ifndef JUEGO_HPP_INCLUDED
#define JUEGO_HPP_INCLUDED

void iniciarJuego(Perfil &perfil,Nivel &nivel,Jugador &jugador){
    Fondo bg;

    BITMAP* buffer=create_bitmap(SCREEN_W,SCREEN_H);

    BITMAP* explosion=create_bitmap(40,40);
    clear_to_color(explosion, makecol(255, 0, 255));

    BITMAP* aux=load_bitmap("img/explosion.bmp",NULL);
    stretch_sprite(explosion, aux, 0, 0, 40, 40);
    destroy_bitmap(aux);

    SAMPLE* sfx_laser=load_sample("sfx/laser.wav");
    SAMPLE* sfx_explosion=load_sample("sfx/explosion.wav");

    const int maxAst=nivel.getCntAst();
    const int chaAst=nivel.getChaAst();
    Asteroide asteroides[maxAst];

    const int maxEne=nivel.getCntEne();
    const int chaEne=nivel.getChaEne();//0.3%
    Enemigo enemigos[maxEne];

    const int maxBonEn=10;
    const int chaBonEn=1000;//max 1000%
    BonusEnergia bonusEn[maxBonEn];

    const int maxBonSa=10;
    const int chaBonSa=1000;//max 1000%
    BonusSalud bonusSa[maxBonSa];

    const int maxDiEn=20;
    Disparo diEnemigo[maxDiEn];
    switch(perfil.getRaza()){
        case 1:cambiarImagenDisparo(diEnemigo,"img/proyAzul.bmp",maxDiEn);break;
        case 2:cambiarImagenDisparo(diEnemigo,"img/proyVerde.bmp",maxDiEn);break;
    }

    const int maxDiJu=20;
    Disparo diJugador[maxDiJu];
    switch(perfil.getRaza()){
        case 1:cambiarImagenDisparo(diJugador,"img/proyVerde.bmp",maxDiJu);break;
        case 2:cambiarImagenDisparo(diJugador,"img/proyAzul.bmp",maxDiJu);break;
    }
    int cDispPausa=0;

    const int maxDiAl=20;
    const int chaDiAl=10;
    Disparo diAliado[maxDiAl];
    cambiarImagenDisparo(diAliado,"img/proyRojo.bmp",maxDiAl);

    int distancia=2000;
    const int tmax=20;

    int c=0;

    int puntaje=0;
    int turbulencia=0;
    int tiempo_salida=50;

    clock_t t;

    while(!key[KEY_ESC] && tiempo_salida>0){
        t=clock();

        clear_keybuf();
        /* FONDO */
        bg.copiarFondo(buffer);

        /* DESPLAZAMIENTO DE OBJETOS */
        for(int i=0;i<tmax;i++){
            for(int j=0;j<tmax;j++){
                /* INTERACCION JUGADOR - BONUS ENERGIA */
                if(j<1 && i<maxBonEn){
                    //interaccionJugadorBonus(jugador,bonusEn[i]);
                }
                /* INTERACCION JUGADOR - BONUS SALUD */
                if(j<1 && i<maxBonSa){
                    //interaccionJugadorBonus(jugador,bonusSa[i]);
                }
                /* INTERACCION DISPARO ENEMIGO - JUGADOR */
                if(j<maxDiEn && i<1){
                    //interaccionDisparoNave(diEnemigo[j],jugador,turbulencia,VACIO);
                }
                /* INTERACCION DISPARO ALIADO - ENEMIGO */
                if(j<maxDiAl && i<maxEne){
                    //interaccionDisparoNave(diAliado[j],enemigos[i],turbulencia,VACIO);
                }
                /* INTERACCION DISPARO ALIADO - ASTEROIDE */
                if(j<maxDiAl && i<maxAst){
                    //interaccionDisparoAsteroide(diAliado[j],asteroides[i],turbulencia);
                }
                /* INTERACCION DISPARO ENEMIGO - ASTEROIDE */
                if(j<maxDiEn && i<maxAst){
                    //interaccionDisparoAsteroide(diEnemigo[j],asteroides[i],turbulencia);
                }
                /* INTERACCION DISPARO JUGADOR - ENEMIGO */
                if(j<maxDiJu && i<maxEne){
                    //interaccionDisparoNave(diJugador[j],enemigos[i],turbulencia,puntaje);
                }
                /* INTERACCION DISPARO JUGADOR - ASTEROIDE */
                if(j<maxDiJu && i<maxAst){
                    interaccionDisparoAsteroide(diJugador[j],asteroides[i],turbulencia);
                }
                /* INTERACCION ENEMIGO - JUGADOR */
                if(j<maxEne && i<1){
                    //interaccionObjetoJugador(enemigos[j],jugador,turbulencia);
                }
                /* INTERACCION ASTEROIDE - JUGADOR */
                if(j<maxAst && i<1){
                    //interaccionObjetoJugador(asteroides[j],jugador,turbulencia);
                }
                /* OBJETIVO ENEMIGO - ASTEROIDE */
                if(j<maxEne && i<maxAst){
                    if(esObjetivo(enemigos[j],asteroides[i])){
                        /* CREAR DISPARO ENEMIGO */
                        if(maxDiEn>0){
                            if(!diEnemigo[c%maxDiEn].getDisplay() && c%5==0){
                                diEnemigo[c%maxDiEn].crearDisparo(enemigos[j].getMidX(),enemigos[j].getMidY(),0,enemigos[j].getVY()+10,enemigos[j].getPoder());
                                reproducirSonido(sfx_laser);
                            }
                        }
                    }
                }
                /* OBJETIVO ENEMIGO - NAVE */
                if(j<maxEne && i<1){
                    if(esObjetivo(enemigos[j],jugador)){
                        /* CREAR DISPARO ENEMIGO */
                        if(maxDiEn>0){
                            if(!diEnemigo[c%maxDiEn].getDisplay() && c%5==0){
                                diEnemigo[c%maxDiEn].crearDisparo(enemigos[j].getMidX(),enemigos[j].getMidY(),0,enemigos[j].getVY()+10,10);
                                reproducirSonido(sfx_laser);
                            }
                        }
                    }
                }
            }
            /* MOVER O CREAR ASTEROIDES */
            if(i<maxAst){
                if(rand()%1000<=chaAst){
                    asteroides[i].crearAsteroide();
                }
                if(asteroides[i].getDisplay()){
                    if(asteroides[i].getSalud()>0){
                        asteroides[i].mover();
                        asteroides[i].imprimir(buffer);
                    }else{
                        asteroides[i].setDisplay(false);
                        dibujarExplosion(buffer, explosion, asteroides[i].getMidX(), asteroides[i].getMidY());
                        reproducirSonido(sfx_explosion);
                        turbulencia=20;
                        /*CREAR BONUS DE ENERGIA*/
                        if(maxBonEn>0 && rand()%1000<=chaBonEn){
                            //bonusEn[c%maxBonEn].crearBonus(asteroides[i]);
                            bool cut=false;
                            for(int pos=0;pos<maxBonEn && !cut;pos++){
                                if(!bonusEn[pos].getDisplay()){
                                    bonusEn[pos].crearBonus(asteroides[i]);
                                    cut=true;
                                }
                            }
                        }
                    }
                }
            }
            /* MOVER BONUS SALUD */
            if(i<maxBonSa){
                bonusSa[i].mover();
                bonusSa[i].imprimir(buffer);
            }
            /* MOVER BONUS ENERGIA */
            if(i<maxBonEn){
                bonusEn[i].mover();
                bonusEn[i].imprimir(buffer);
            }
            /* MOVER O CREAR ENEMIGOS */
            if(i<maxEne){
                if(rand()%1000<=chaEne){
                    enemigos[i].crearEnemigo(perfil.getRaza());
                    //if(enemigos[i].crearEnemigo(perfil.getRaza())){
                    //char msg[128];
                    //itoa(enemigos[i].getY()+enemigos[i].getH(),msg,10);
                    //allegro_message(msg);}
                }
                if(enemigos[i].getDisplay()){
                    if(enemigos[i].getSalud()>0){
                        enemigos[i].mover();
                        enemigos[i].imprimir(buffer);
                    }else{
                        enemigos[i].setDisplay(false);
                        dibujarExplosion(buffer, explosion, enemigos[i].getMidX(), enemigos[i].getMidY());
                        reproducirSonido(sfx_explosion);
                        turbulencia=20;
                        /*CREAR BONUS DE SALUD*/
                        if(maxBonSa>0 && rand()%1000<=chaBonSa){
                            //bonusSa[c%maxBonSa].crearBonus(enemigos[i]);
                        }
                    }
                }
            }
            /* MOVER O CREAR DISPAROS ALIADOS */
            if(i<maxDiAl){
                if(rand()%1000<=chaDiAl){
                    diAliado[i].crearDisparo(rand()%SCREEN_W,SCREEN_H,0,-10,10);
                }
                if(diAliado[i].getDisplay()){
                    diAliado[i].mover();
                    diAliado[i].imprimir(buffer);
                }
            }
            /* MOVER O CREAR DISPAROS JUGADOR */
            if(i<maxDiJu){
                if(!diJugador[i].getDisplay() && key[KEY_SPACE] && cDispPausa==0 && jugador.getDisplay() && jugador.getEnergia()>0){
                    diJugador[i].crearDisparo(jugador.getMidX(),jugador.getMidY(),0,-10,jugador.getPoder());
                    reproducirSonido(sfx_laser);
                    cDispPausa=5;
                    jugador.decEnergia(1);
                }
                if(diJugador[i].getDisplay()){
                    diJugador[i].mover();
                    diJugador[i].imprimir(buffer);
                }
            }
            /* MOVER DISPAROS ENEMIGOS */
            if(i<maxDiEn){
                if(diEnemigo[i].getDisplay()){
                    diEnemigo[i].mover();
                    diEnemigo[i].imprimir(buffer);
                }
            }
            /* MODIFICAR NAVE */
            if(i<1){
                jugador.obtenerTeclado();
                if(jugador.getDisplay()){
                    if(jugador.getSalud()<=0){
                        //jugador.setDisplay(false);
                        //dibujarExplosion(buffer, explosion, jugador.getMidX(), jugador.getMidY());
                        //reproducirSonido(sfx_explosion);
                        //turbulencia=30;
                    }
                }
                if(cDispPausa>0){cDispPausa--;}
                jugador.imprimir(buffer);
            }
        }
        /* END */
        c++;
        if(c>=1000/FPS){c=0;}
        if(distancia>0 && jugador.getDisplay()){distancia--;}
        //if(distancia<=0 || !jugador.getDisplay()){tiempo_salida--;}
        /* IMPRIMIR TODO */
        acquire_screen();
        if(turbulencia<=0){
            draw_sprite(screen, buffer, 0, 0);
        }else{
            draw_sprite(screen, buffer, rand()%turbulencia/3, rand()%turbulencia/3);
            turbulencia--;
        }
        textprintf_ex(screen, font, 10, 10, makecol(255, 100, 200), -1, "Distancia: %d", distancia);
        textprintf_ex(screen, font, 10, 30, makecol(255, 100, 200), -1, "Energia: %d", jugador.getEnergia());
        textprintf_ex(screen, font, 10, 50, makecol(255, 100, 200), -1, "Puntaje: %d", puntaje);
        textprintf_ex(screen, font, 10, 70, makecol(255, 100, 200), -1, "Salud: %d", jugador.getSalud());
        if(!jugador.getDisplay()){
            textout_centre_ex(screen, font, "JUEGO TERMINADO",SCREEN_W/2,SCREEN_H/2,makecol(255,100,200),-1);
            textout_centre_ex(screen, font, "PRESIONE ESC PARA SALIR",SCREEN_W/2,SCREEN_H-30,makecol(200,200,200),-1);
        }
        release_screen();
        /* IMPRIMIR END */
        t=FPS-(clock()-t)*1000/CLOCKS_PER_SEC;
        if(t<0){t=0;}
        rest(t);
    }
    destroy_bitmap(explosion);
    destroy_bitmap(buffer);
    destroy_sample(sfx_explosion);
    destroy_sample(sfx_laser);

    perfil.addCreditos(puntaje);
    perfil.guardarPerfil(perfil.getSlot());
    Puntaje pts;
    pts.setNivel(nivel.getNivel());
    pts.setNombre(perfil.getNombre());
    pts.setPuntaje(puntaje);
    pts.setRaza(nivel.getRaza());
    pts.guardarPuntaje(pts.proximaPosicion());

    clear_keybuf();
    return;
}

#endif // JUEGO_HPP_INCLUDED
