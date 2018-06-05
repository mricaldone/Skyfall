#ifndef PUNTAJES_HPP_INCLUDED
#define PUNTAJES_HPP_INCLUDED

class Puntaje{
    private:
        int nivel;
        int raza;
        char nombre[32];
        int puntaje;
    public:
        Puntaje();
        bool guardarPuntaje(int);
        bool cargarPuntaje(int);
        //int proximaPosicion();
        bool agregarPuntaje();

        int getRaza(){return raza;}
        int getNivel(){return nivel;}
        char *getNombre(){return nombre;}
        int getPuntaje(){return puntaje;}

        void setRaza(int v){raza=v;}
        void setNivel(int v){nivel=v;}
        void setNombre(char *v){strcpy(nombre,v);}
        void setPuntaje(int v){puntaje=v;}
};

Puntaje::Puntaje(){
    nivel=0;
    raza=0;
    strcpy(nombre,"");
    puntaje=0;
}

bool Puntaje::agregarPuntaje(){
    FILE *p;
    p=fopen(DIR_PUNTAJES,"ab");
    if(p==NULL){return false;}
    fwrite(this,sizeof(Puntaje),1,p);
    fclose(p);
    return true;
}

bool Puntaje::guardarPuntaje(int pos){
    FILE *p;
    p=fopen(DIR_PUNTAJES,"rb+");
    if(p==NULL){return false;}
    fseek(p,pos*sizeof(Puntaje),SEEK_SET);
    fwrite(this,sizeof(Puntaje),1,p);
    fclose(p);
    return true;
}

bool Puntaje::cargarPuntaje(int pos){
    FILE *p;
    p=fopen(DIR_PUNTAJES,"rb");
    if(p==NULL){return false;}
    fseek(p,pos*sizeof(Puntaje),SEEK_SET);
    //char msg[256];
    //itoa(pos,msg,10);
    //allegro_message(msg);
    fread(this,sizeof(Puntaje),1,p);
    fclose(p);
    return true;
}
/*
int Puntaje::proximaPosicion(){
    int pos;
    FILE *p;
    p=fopen(DIR_PUNTAJES,"rb");
    if(p==NULL){return 0;}
    fseek(p,0,SEEK_END);
    pos=ftell(p)/sizeof(Perfil);
    fclose(p);
    return pos;
}
*/
Puntaje obtenerPuntaje(int posicion,int vRaza,int vNivel,int tam_list=10){
    FILE *p;
    Puntaje *listado;
    Puntaje reg;
    p=fopen(DIR_PUNTAJES,"rb");
    fseek(p,0,SEEK_END);
    int tam=ftell(p)/sizeof(Puntaje);
    //if(tam<tam_list){tam=tam_list;}
    if(posicion>tam_list-1){posicion=tam_list-1;}
    listado=new Puntaje[tam];
    fseek(p,0,SEEK_SET);
    if(p==NULL){return reg;}
    int i=0;
    while(fread(&reg,sizeof(Puntaje),1,p)==1){
        if(reg.getRaza()==vRaza && reg.getNivel()==vNivel){
            listado[i]=reg;
            i++;
        }
    }
    Puntaje treg;
    for(int a=0;a<tam-1;a++){
        for(int b=a+1;b<tam;b++){
            if(listado[b].getPuntaje()>listado[a].getPuntaje()){
                treg=listado[a];
                listado[a]=listado[b];
                listado[b]=treg;
            }
        }
    }
    /*
    for (int a=1; a<tam; a++){
        for (int b=0 ; b<tam - 1; b++){
           if (listado[b].getPuntaje()<listado[b+1].getPuntaje()){
                treg=listado[b];
                listado[b]=listado[b+1];
                listado[b+1]=treg;
           }
        }
    }
    */
    reg=listado[posicion];
    delete listado;
    fclose(p);
    return reg;
}

#endif // PUNTAJES_HPP_INCLUDED
