#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

bool verificarArchivos(){
    FILE *p;
    p=fopen(DIR_NIVELES,"rb");
    if(p==NULL){
        textout_centre_ex(screen,font,"NO SE PUDO ABRIR EL ARCHIVO DE NIVELES",SCREEN_W/2,SCREEN_H/2,makecol(255,0,0),makecol(0,0,0));
        esperarTeclado();
        return false;
    }
    fclose(p);
    p=fopen(DIR_PERFILES,"rb");
    if(p==NULL){
        textout_centre_ex(screen,font,"NO SE PUDO ABRIR EL ARCHIVO DE PERFILES",SCREEN_W/2,SCREEN_H/2,makecol(255,0,0),makecol(0,0,0));
        esperarTeclado();
        return false;
    }
    fclose(p);
    p=fopen(DIR_PUNTAJES,"rb");
    if(p==NULL){
        textout_centre_ex(screen,font,"NO SE PUDO ABRIR EL ARCHIVO DE PUNTAJES",SCREEN_W/2,SCREEN_H/2,makecol(255,0,0),makecol(0,0,0));
        esperarTeclado();
        return false;
    }
    fclose(p);
    return true;
}

void menuSeleccionPerfil(Perfil &perfil){

    int pos=0;
    Perfil regs[5];
    regs[0].cargarPerfil(0);
    regs[1].cargarPerfil(1);
    regs[2].cargarPerfil(2);
    regs[3].cargarPerfil(3);
    regs[4].cargarPerfil(4);
    int col,i,vertical=250;
    char nom[32];

    blit(bg_menu,screen,0,0,0,0,bg_menu->w,bg_menu->h);
    textout_centre_ex(screen,font_menu_titulo,"SELECCIONE PERFIL",SCREEN_W/2,vertical,makecol(220,220,220),makecol(0,0,0));

    do{
        for(i=0;i<5;i++){
            if(regs[i].getBorrado()){
                strcpy(nom,"[vacio]");
                if(pos==i){col=makecol(0,180,0);}
                else{col=makecol(90,90,90);}
            }else{
                strcpy(nom,regs[i].getNombre());
                if(pos==i){col=makecol(0,220,0);}
                else{col=makecol(180,180,180);}
            }
            textout_centre_ex(screen,font_menu_subtitulo,nom,SCREEN_W/2,vertical+40+i*20,col,makecol(0,0,0));
        }
        if(pos==i){col=makecol(0,220,0);}
        else{col=makecol(220,220,220);}
        textout_centre_ex(screen,font_menu_titulo,"SALIR",SCREEN_W/2,vertical+45+i*20,col,makecol(0,0,0));

        /* SELECTOR */
        //textout_ex(screen,font_menu_subtitulo,">",20,vertical+40+20*pos,makecol(220,220,220),makecol(0,0,0));
        clear_keybuf();
        readkey();
        //textout_ex(screen,font_menu_subtitulo," ",20,vertical+40+20*pos,makecol(220,220,220),makecol(0,0,0));

        if(key[KEY_UP]){pos--;}
        if(key[KEY_DOWN]){pos++;}
        if(pos<0){pos=0;}
        if(pos>5){pos=5;}
    }while(!key[KEY_ENTER]);
    if(pos==5){cerrarJuego();}

    clear_keybuf();
    perfil=regs[pos];
    return;
}

bool menuSeleccionNave(Perfil &perfil,Jugador &jugador){
    int pos,col,vertical,selw,selh,i;
    BITMAP *nv[4];
    char nn[4][32];
    int precio[4];
    switch(perfil.getRaza()){
        case 1:
        strcpy(nn[0],"img/navHumano_1.bmp");
        nv[0]=load_bitmap(nn[0],NULL);
        if(perfil.getNave(0)){precio[0]=0;}else{precio[0]=0;}
        strcpy(nn[1],"img/navHumano_2.bmp");
        nv[1]=load_bitmap(nn[1],NULL);
        if(perfil.getNave(1)){precio[1]=0;}else{precio[1]=200;}
        strcpy(nn[2],"img/navHumano_3.bmp");
        nv[2]=load_bitmap(nn[2],NULL);
        if(perfil.getNave(2)){precio[2]=0;}else{precio[2]=400;}
        strcpy(nn[3],"img/navHumano_4.bmp");
        nv[3]=load_bitmap(nn[3],NULL);
        if(perfil.getNave(3)){precio[3]=0;}else{precio[3]=800;}
        break;
        case 2:
        strcpy(nn[0],"img/navAlien_1.bmp");
        nv[0]=load_bitmap(nn[0],NULL);
        if(perfil.getNave(0)){precio[0]=0;}else{precio[0]=0;}
        strcpy(nn[1],"img/navAlien_2.bmp");
        nv[1]=load_bitmap(nn[1],NULL);
        if(perfil.getNave(1)){precio[1]=0;}else{precio[1]=200;}
        strcpy(nn[2],"img/navAlien_3.bmp");
        nv[2]=load_bitmap(nn[2],NULL);
        if(perfil.getNave(2)){precio[2]=0;}else{precio[2]=400;}
        strcpy(nn[3],"img/navAlien_4.bmp");
        nv[3]=load_bitmap(nn[3],NULL);
        if(perfil.getNave(3)){precio[3]=0;}else{precio[3]=800;}
        break;
    }

    blit(bg_menu,screen,0,0,0,0,bg_menu->w,bg_menu->h);
    pos=0;
    vertical=240;
    selw=250;
    selh=40;
    textprintf_centre_ex(screen, font_menu_subtitulo, SCREEN_W/2, vertical-30, makecol(220,220,220), makecol(0,0,0), "CREDITOS: %d", perfil.getCreditos());
    do{
        for(i=0;i<4;i++){
            if(precio[i]<=perfil.getCreditos()){if(pos==i){col=makecol(0,220,0);}else{col=makecol(30,30,30);}}
            else{if(pos==i){col=makecol(220,0,0);}else{col=makecol(30,30,30);}}
            rectfill(screen, (SCREEN_W/2)-(selw/2), vertical+selh*i+5, (SCREEN_W/2)+(selw/2), vertical+selh*i+selh, col);
            stretch_sprite(screen,nv[i],(SCREEN_W/2)-(selw/2)+1,vertical+selh*i+5+1,selh-8,selh-8);
            textprintf_ex(screen, font_menu_subtitulo, (SCREEN_W/2)-(selw/2)+selh, vertical+selh*i+5+1, makecol(220,220,220), -1, "Precio: %d", precio[i]);
        }
        if(pos==4){col=makecol(0,220,0);}else{col=makecol(220,220,220);}
        textout_centre_ex(screen,font_menu_titulo,"CANCELAR",SCREEN_W/2,vertical+selh*i+5,col,makecol(0,0,0));
        /* SELECTOR */
        clear_keybuf();
        readkey();
        if(key[KEY_UP]){pos--;}
        if(key[KEY_DOWN]){pos++;}
        if(pos<0){pos=0;}
        if(pos>4){pos=4;}
    }while(!key[KEY_ENTER] || (perfil.getCreditos()<precio[pos] && pos!=4));
    destroy_bitmap(nv[0]);
    destroy_bitmap(nv[1]);
    destroy_bitmap(nv[2]);
    destroy_bitmap(nv[3]);
    clear_keybuf();
    if(pos==4){return false;}
    /*LISTO*/
    perfil.decCreditos(precio[pos]);
    perfil.actNave(pos);
    jugador.crearJugador(perfil.getRaza(),pos+1);
    return true;
}

bool menuSeleccionNivel(Nivel &nvl,Perfil &perfil,Jugador &jugador){
    FILE *p;
    Nivel reg;
    p=fopen(DIR_NIVELES,"rb");
    if(p==NULL){return false;}
    fseek(p,0,SEEK_END);
    Nivel *nivel;
    nivel=new Nivel[ftell(p)/sizeof(Nivel)];
    fseek(p,0,SEEK_SET);
    int creg=0;
    while(fread(&reg,sizeof reg,1,p)==1){
        if(perfil.getRaza()==reg.getRaza()){
            nivel[creg]=reg;
            creg++;
        }
    }
    fclose(p);
    //char msg[10];
    //allegro_message(itoa(sizeof *nivel/sizeof(Nivel),msg,10));
    //nivel[0].cargarNivel(0);

    char num[4];
    char nom[16];
    int i,col,pos,vertical=250;
do{
    blit(bg_menu,screen,0,0,0,0,bg_menu->w,bg_menu->h);
    textout_centre_ex(screen,font_menu_titulo,"SELECCIONE MISION",SCREEN_W/2,vertical,makecol(220,220,220),makecol(0,0,0));

    pos=0;
    do{
        for(i=0;i<creg;i++){
            itoa(i+1,num,10);
            strcpy(nom,"MISION ");
            strcat(nom,num);
            if(i<perfil.getMaxNivel()+1){if(pos==i){col=makecol(0,220,0);}else{col=makecol(220,220,220);}}
            else{if(pos==i){col=makecol(255,0,0);}else{col=makecol(90,90,90);}}
            textout_centre_ex(screen,font_menu_subtitulo,nom,SCREEN_W/2,vertical+40+i*20,col,makecol(0,0,0));
        }

        if(pos==i){col=makecol(0,220,0);}else{col=makecol(220,220,220);}
        textout_centre_ex(screen,font_menu_titulo,"VOLVER",SCREEN_W/2,vertical+40+i*20,col,makecol(0,0,0));

        /* SELECTOR */
        clear_keybuf();
        readkey();
        if(key[KEY_UP]){pos--;}
        if(key[KEY_DOWN]){pos++;}
        if(pos<0){pos=0;}
        if(pos>creg){pos=creg;}
    }while(!key[KEY_ENTER] || (pos>perfil.getMaxNivel() && pos!=creg));

    clear_keybuf();

    if(pos==creg){return false;}
    if(menuSeleccionNave(perfil,jugador)){nvl=nivel[pos];return true;}
}while(pos!=creg);
    return false;
}

void menuCrearNombre(Perfil &p){
    char nom[32];
    int vertical=280;

    blit(bg_menu,screen,0,0,0,0,bg_menu->w,bg_menu->h);
    textout_centre_ex(screen,font_menu_titulo,"INGRESE SU NOMBRE:",SCREEN_W/2,vertical,makecol(220,220,220),makecol(0,0,0));
    do{
        getText(nom,32,SCREEN_W/2,vertical+30,makecol(0,255,0),font_menu_subtitulo,true);
    }while(strlen(nom)<3);
    p.setNombre(nom);

    return;
}

void menuSeleccionarRaza(Perfil &p){
    int pos,col,vertical;

    blit(bg_menu,screen,0,0,0,0,bg_menu->w,bg_menu->h);
    pos=0;
    vertical=280;
    do{
        if(pos==0){col=makecol(0,220,0);}else{col=makecol(220,220,220);}
        textout_centre_ex(screen,font_menu_titulo,"HUMANOS",SCREEN_W/2,vertical,col,makecol(0,0,0));
        if(pos==1){col=makecol(0,220,0);}else{col=makecol(220,220,220);}
        textout_centre_ex(screen,font_menu_titulo,"ALIENS",SCREEN_W/2,vertical+30,col,makecol(0,0,0));
        /* SELECTOR */
        clear_keybuf();
        readkey();
        if(key[KEY_UP]){pos--;}
        if(key[KEY_DOWN]){pos++;}
        if(pos<0){pos=0;}
        if(pos>1){pos=1;}
    }while(!key[KEY_ENTER]);

    clear_keybuf();
    p.setRaza(pos+1);
    return;
}

void borrarPerfil(Perfil &p){
    p.setBorrado(true);
    p.guardarPerfil();
    return;
}

void menuMensaje(char *msg,int ms=1500){
    blit(bg_menu,screen,0,0,0,0,bg_menu->w,bg_menu->h);
    textout_centre_ex(screen,font_menu_titulo,msg,SCREEN_W/2,SCREEN_H/2+50,makecol(255,255,0),makecol(0,0,0));
    rest(ms);
    return;
}

bool menuConfirmar(char *msg){
    int col,vertical;
    blit(bg_menu,screen,0,0,0,0,bg_menu->w,bg_menu->h);
    bool pos=false;
    vertical=280;
    textout_centre_ex(screen,font_menu_titulo,msg,SCREEN_W/2,vertical,makecol(255,255,0),makecol(0,0,0));
    do{
        if(pos){col=makecol(0,220,0);}else{col=makecol(220,220,220);}
        textout_centre_ex(screen,font_menu_titulo,"SI",SCREEN_W/2-100,vertical+30,col,makecol(0,0,0));
        if(!pos){col=makecol(0,220,0);}else{col=makecol(220,220,220);}
        textout_centre_ex(screen,font_menu_titulo,"NO",SCREEN_W/2+100,vertical+30,col,makecol(0,0,0));
        /* SELECTOR */
        clear_keybuf();
        readkey();
        if(key[KEY_LEFT] && !pos){pos=not pos;}
        if(key[KEY_RIGHT] && pos){pos=not pos;}
    }while(!key[KEY_ENTER]);
    clear_keybuf();
    return pos;
}

bool menuPrincipal(Nivel &nivel,Perfil &perfil,Jugador &jugador){
    int pos,col,vertical;
    pos=0;
    vertical=280;
                    //char msg[128];
                    //itoa(perfil.getCreditos(),msg,10);
                    //allegro_message(msg);
do{
    blit(bg_menu,screen,0,0,0,0,bg_menu->w,bg_menu->h);
    do{
        if(pos==0){col=makecol(0,220,0);}else{col=makecol(220,220,220);}
        textout_centre_ex(screen,font_menu_titulo,"JUGAR",SCREEN_W/2,vertical,col,makecol(0,0,0));
        if(pos==1){col=makecol(0,220,0);}else{col=makecol(220,220,220);}
        textout_centre_ex(screen,font_menu_titulo,"BORRAR PERFIL",SCREEN_W/2,vertical+30,col,makecol(0,0,0));
        if(pos==2){col=makecol(0,220,0);}else{col=makecol(220,220,220);}
        textout_centre_ex(screen,font_menu_titulo,"CERRAR PERFIL",SCREEN_W/2,vertical+60,col,makecol(0,0,0));
        if(pos==3){col=makecol(0,220,0);}else{col=makecol(220,220,220);}
        textout_centre_ex(screen,font_menu_titulo,"SALIR DEL JUEGO",SCREEN_W/2,vertical+120,col,makecol(0,0,0));
        /* SELECTOR */
        clear_keybuf();
        readkey();
        if(key[KEY_UP]){pos--;}
        if(key[KEY_DOWN]){pos++;}
        if(pos<0){pos=0;}
        if(pos>3){pos=3;}
    }while(!key[KEY_ENTER]);
    clear_keybuf();

    switch(pos){
        case 0:if(menuSeleccionNivel(nivel,perfil,jugador)){return true;};break;
        case 1:if(menuConfirmar("ESTA SEGURO?")){borrarPerfil(perfil);menuMensaje("PERFIL BORRADO");return false;}break;
        //case 2:return false;break;
        case 3:cerrarJuego();break;
    }

}while(pos!=2);
    return false;
}
/*
void menu(Perfil &perfil,Nivel &nivel,Jugador &jugador){
    if(!verificarArchivos()){cerrarJuego();}

    SELECCION_DE_PERFIL:
        menuSeleccionPerfil(perfil);//DEVUELVE UN PERFIL BORRADO=TRUE SI SE ELIGIO UN SLOT VACIO
        if(!perfil.getBorrado()){goto MENU_PRINCIPAL;}

    CREACION_DE_PERFIL:
        menuCrearNombre(perfil);
        menuSeleccionarRaza(perfil);
        perfil.inicializarPerfil();
        perfil.guardarPerfil();

    MENU_PRINCIPAL:
        switch(menuPrincipal()){
            case 0:goto SELECCION_DE_NIVEL;break;
            case 1:if(menuConfirmar("ESTA SEGURO?")){borrarPerfil(perfil);menuMensaje("PERFIL BORRADO");goto SELECCION_DE_PERFIL;}else{goto MENU_PRINCIPAL;}break;
            case 2:goto SELECCION_DE_PERFIL;break;
            case 3:cerrarJuego();break;
        }

    SELECCION_DE_NIVEL:
        if(!menuSeleccionNivel(nivel,perfil)){goto MENU_PRINCIPAL;}

    SELECCION_DE_NAVE:
        if(!menuSeleccionNave(perfil,jugador)){goto SELECCION_DE_NIVEL;}
    return;
}
*/
#endif // MENU_HPP_INCLUDED
