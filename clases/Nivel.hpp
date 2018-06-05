#ifndef NIVEL_HPP_INCLUDED
#define NIVEL_HPP_INCLUDED

class Nivel{
    private:
        int id;
        int raza;
        int nivel;
        int cntEne;
        int chaEne;
        int difEne;
        int cntAst;
        int chaAst;
        int cntDiAl;
        int chaDiAl;
        int cntBonSa;
        int chaBonSa;
        int cntBonEn;
        int chaBonEn;
        int distancia;
    public:
        bool cargarNivel(int);
        bool guardarNivel(int);

        void setRaza(int v){raza=v;}
        void setNivel(int v){nivel=v;}
        void setCntEne(int v){cntEne=v;}
        void setChaEne(int v){chaEne=v;}
        void setDifEne(int v){if(v>4){v=4;}if(v<1){v=1;}difEne=v;}
        void setCntAst(int v){cntAst=v;}
        void setChaAst(int v){chaAst=v;}
        void setCntDiAl(int v){cntDiAl=v;}
        void setChaDiAl(int v){chaDiAl=v;}
        void setCntBonSa(int v){cntBonSa=v;}
        void setChaBonSa(int v){chaBonSa=v;}
        void setCntBonEn(int v){cntBonEn=v;}
        void setChaBonEn(int v){chaBonEn=v;}
        void setDistancia(int v){distancia=v;}

        int getID(){return id;}
        int getRaza(){return raza;}
        int getNivel(){return nivel;}
        int getCntEne(){return cntEne;}
        int getChaEne(){return chaEne;}
        int getDifEne(){return difEne;}
        int getCntAst(){return cntAst;}
        int getChaAst(){return chaAst;}
        int getCntDiAl(){return cntDiAl;}
        int getChaDiAl(){return chaDiAl;}
        int getCntBonSa(){return cntBonSa;}
        int getChaBonSa(){return chaBonSa;}
        int getCntBonEn(){return cntBonEn;}
        int getChaBonEn(){return chaBonEn;}
        int getDistancia(){return distancia;}

};

bool Nivel::cargarNivel(int pos){
    FILE *p;
    p=fopen(DIR_NIVELES,"rb");
    if(p==NULL){return false;}
    fseek(p,pos*sizeof(Nivel),SEEK_SET);
    fread(this,sizeof(Nivel),1,p);
    fclose(p);
    id=pos;
    return true;
}

bool Nivel::guardarNivel(int pos){
    FILE *p;
    id=pos;
    p=fopen(DIR_NIVELES,"rb+");
    if(p==NULL){return false;}
    fseek(p,pos*sizeof(Nivel),SEEK_SET);
    fwrite(this,sizeof(Nivel),1,p);
    fclose(p);
    return true;
}

#endif // NIVEL_HPP_INCLUDED
