#ifndef PERFIL_HPP_INCLUDED
#define PERFIL_HPP_INCLUDED

class Perfil{
private:
    int slot;
    char nombre[32];
    int raza;
    int creditos;
    int max_nivel;
    bool nave[4];
    bool borrado;
public:
    void addCreditos(int v){creditos+=v;}
    void decCreditos(int v){creditos-=v;}

    void setNombre(char *v){strcpy(nombre,v);}
    void setRaza(int v){raza=v;}
    void setCreditos(int v){creditos=v;}
    void setMaxNivel(int v){max_nivel=v;}
    void setBorrado(bool v){borrado=v;}

    void actNave(int p){nave[p]=true;}//ACTIVAR NAVE

    int getSlot(){return slot;}
    int getRaza(){return raza;}
    char* getNombre(){return nombre;}
    int getCreditos(){return creditos;}
    bool getBorrado(){return borrado;}
    int getMaxNivel(){return max_nivel;}
    bool getNave(int p){return nave[p];}

    bool guardarPerfil(int);
    bool cargarPerfil(int);
    bool crearPerfil(const char*);
    void inicializarPerfil();
    Perfil();
};

Perfil::Perfil(){
    inicializarPerfil();
    raza=0;
    nombre[0]='\n';
    slot=0;
}

void Perfil::inicializarPerfil(){
    creditos=0;
    max_nivel=0;
    nave[0]=true;
    nave[1]=false;
    nave[2]=false;
    nave[3]=false;
    borrado=false;
}

bool Perfil::cargarPerfil(int pos){
    FILE *p;
    p=fopen(DIR_PERFILES,"rb");
    if(p==NULL){return false;}
    fseek(p,pos*sizeof(Perfil),SEEK_SET);
    if(fread(this,sizeof(Perfil),1,p)!=1){borrado=true;}
    fclose(p);
    slot=pos;
    return true;
}

bool Perfil::guardarPerfil(int pos=-1){
    if(pos==-1){pos=slot;}
    FILE *p;
    slot=pos;
    p=fopen(DIR_PERFILES,"rb+");
    if(p==NULL){return false;}
    fseek(p,pos*sizeof(Perfil),SEEK_SET);
    fwrite(this,sizeof(Perfil),1,p);
    fclose(p);
    return true;
}

bool Perfil::crearPerfil(const char *nom){
    FILE *p;
    strcpy(nombre,nom);
    //creditos=0;
    //max_nivel=0;
    inicializarPerfil();
    p=fopen(DIR_PERFILES,"rb+");
    if(p==NULL){return false;}
    fseek(p,0,SEEK_END);
    slot=ftell(p)/sizeof(Perfil);
    fwrite(this,sizeof(Perfil),1,p);
    fclose(p);
    return true;
}

#endif // PERFIL_HPP_INCLUDED
