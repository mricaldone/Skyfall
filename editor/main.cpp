#define DIR_PERFILES "perfiles.dat"
#define DIR_NIVELES "niveles.dat"
#define DIR_PUNTAJES "puntajes.dat"

#include <iostream>

using namespace std;

#include <cstdlib>
#include <cstring>
#include <cstdio>

#include "../clases/Perfil.hpp"
#include "../clases/Nivel.hpp"
#include "../clases/Puntajes.hpp"

void submenuListarPuntajes(){
    system("cls");
    FILE *p;
    Puntaje reg;
    p=fopen(DIR_PUNTAJES,"rb");
    if(p==NULL){return;}
    while(fread(&reg,sizeof(Puntaje),1,p)==1){
        cout << "NIVEL: " << reg.getNivel();
        cout << " RAZA: " << reg.getRaza();
        cout << " PUNTAJE: " << reg.getPuntaje();
        cout << " NOMBRE: " << reg.getNombre();
        cout << endl;
    }
    fclose(p);
    system("pause>nul");
    return;
}
void submenuAgregarPuntaje(){
    system("cls");
    cout << "AGREGAR PUNTAJE" << endl;
    cout << "---------------------------" << endl;
    Puntaje reg;
    char nombre[32];
    int raza,pos,nivel,puntaje;
    cout << "POSICION: ";
    cin >> pos;
    cout << "RAZA: ";
    cin >> raza;
    reg.setRaza(raza);
    cout << "NIVEL: ";
    cin >> nivel;
    reg.setNivel(nivel);
    cout << "NOMBRE: ";
    cin >> nombre;
    reg.setNombre(nombre);
    cout << "PUNTAJE: ";
    cin >> puntaje
    ;
    reg.setPuntaje(puntaje);
    cout << endl;
    if(reg.guardarPuntaje(pos)){
        cout << "PUNTAJE AGREGADO CORRECTAMENTE" << endl;
    }else{
        cout << "EL PUNTAJE NO PUDO SER AGREGADO" << endl;
    }
    system("pause>nul");
}

void submenuAgregarPerfil(){
    system("cls");
    cout << "AGREGAR PERFIL" << endl;
    cout << "---------------------------" << endl;
    Perfil reg;
    reg.inicializarPerfil();
    char nombre[32];
    int raza,id,nivel,creditos;
    cout << "SLOT: ";
    cin >> id;
    cout << "NOMBRE: ";
    cin >> nombre;
    reg.setNombre(nombre);
    cout << "RAZA: ";
    cin >> raza;
    reg.setRaza(raza);
    cout << "NIVEL MAXIMO: ";
    cin >> nivel;
    reg.setMaxNivel(nivel);
    cout << "CREDITOS: ";
    cin >> creditos;
    reg.setCreditos(creditos);
    cout << endl;
    //reg.setCreditos(0);
    //reg.setMaxNivel(0);
    reg.setBorrado(false);
    if(reg.guardarPerfil(id)){
        cout << "PERFIL AGREGADO CORRECTAMENTE" << endl;
    }else{
        cout << "EL PERFIL NO PUDO SER AGREGADO" << endl;
    }
    system("pause>nul");
}

void submenuListarPerfiles(){
    system("cls");
    cout << "LISTADO DE PERFILES" << endl;
    cout << "---------------------------" << endl;
    FILE *p;
    Perfil reg;
    p=fopen(DIR_PERFILES,"rb");
    if(p==NULL){cout << "NO SE PUDO LEER EL ARCHIVO DE PERFILES" << endl;}else{
    while(fread(&reg,sizeof reg,1,p)==1){
        if(!reg.getBorrado()){
            cout << "ID: " << reg.getSlot() << endl;
            cout << "NOMBRE: " << reg.getNombre() << endl;
            cout << "RAZA: " << reg.getRaza() << endl;
            cout << "CREDITOS: " << reg.getCreditos() << endl;
            cout << "NIVEL MAXIMO: " << reg.getMaxNivel() << endl;
            cout << endl;
        }
    }
    fclose(p);}
    system("pause>nul");
}

void submenuBorrarPerfil(){
    int slot;
    Perfil perfil;
    system("cls");
    cout << "BORRAR PERFIL" << endl;
    cout << "---------------------------" << endl;
    cout << "SLOT: ";
    cin  >> slot;
    if(perfil.cargarPerfil(slot)){
        perfil.setBorrado(true);
        perfil.guardarPerfil(slot);
        cout << endl << "PERFIL BORRADO CORRECTAMENTE";
    }else{
        cout << endl << "EL PERFIL NO EXISTE";
    }
    return;
}

void submenuAgregarNivel(){
    system("cls");
    cout << "AGREGAR NIVEL" << endl;
    cout << "---------------------------" << endl;
    Nivel reg;
    int id,raza,nivel,chaEne,cntEne,chaAst,cntAst,input;
    cout << "ID: ";
    cin >> id;
    cout << "RAZA: ";
    cin >> raza;
    reg.setRaza(raza);
    cout << "NIVEL: ";
    cin >> nivel;
    reg.setNivel(nivel);
    cout << "DISTANCIA: ";
    cin >> input;
    reg.setDistancia(input);
    cout << "CANTIDAD ENEMIGOS: ";
    cin >> input;
    reg.setCntEne(input);
    if(input>0){
        cout << "CHANCE ENEMIGOS: ";
        cin >> input;
        reg.setChaEne(input);
        cout << "DIFICULTAD ENEMIGOS: ";
        cin >> input;
        reg.setDifEne(input);
    }else{
        reg.setChaEne(0);
        reg.setDifEne(1);
    }
    cout << "CANTIDAD ASTEROIDES: ";
    cin >> input;
    reg.setCntAst(input);
    if(input>0){
        cout << "CHANCE ASTEROIDES: ";
        cin >> input;
        reg.setChaAst(input);
    }else{
        reg.setChaAst(0);
    }
    cout << "CANTIDAD DE DISPAROS ALIADOS: ";
    cin >> input;
    reg.setCntDiAl(input);
    if(input>0){
        cout << "CHANCE DE DISPAROS ALIADOS: ";
        cin >> input;
        reg.setChaDiAl(input);
    }else{
        reg.setChaDiAl(0);
    }
    cout << "CANTIDAD DE BONUS DE SALUD: ";
    cin >> input;
    reg.setCntBonSa(input);
    if(input>0){
        cout << "CHANCE DE BONUS DE SALUD: ";
        cin >> input;
        reg.setChaBonSa(input);
    }else{
        reg.setChaBonSa(0);
    }
    cout << "CANTIDAD DE BONUS DE ENERGIA: ";
    cin >> input;
    reg.setCntBonEn(input);
    if(input>0){
        cout << "CHANCE DE BONUS DE ENERGIA: ";
        cin >> input;
        reg.setChaBonEn(input);
    }else{
        reg.setChaBonEn(0);
    }
    cout << endl;

    if(reg.guardarNivel(id)){
        cout << "NIVEL AGREGADO CORRECTAMENTE" << endl;
    }else{
        cout << "EL NIVEL NO PUDO SER AGREGADO" << endl;
    }
    system("pause>nul");
}

void submenuListarNiveles(){
    system("cls");
    cout << "LISTADO DE NIVELES" << endl;
    cout << "---------------------------" << endl;
    FILE *p;
    Nivel reg;
    p=fopen(DIR_NIVELES,"rb");
    if(p==NULL){cout << "NO SE PUDO LEER EL ARCHIVO DE NIVELES" << endl;}else{
    while(fread(&reg,sizeof reg,1,p)==1){
        cout << "ID: " << reg.getID() << endl;
        cout << "RAZA: " << reg.getRaza() << endl;
        cout << "NIVEL: " << reg.getNivel() << endl;
        cout << "DISTANCIA: " << reg.getDistancia() << endl;
        cout << "CANTIDAD DE ENEMIGOS: " << reg.getCntEne() << endl;
        cout << "CHANCE DE ENEMIGOS: " << reg.getChaEne() << endl;
        cout << "DIFICULTAD DE ENEMIGOS: " << reg.getDifEne() << endl;
        cout << "CANTIDAD DE ASTEROIDES: " << reg.getCntAst() << endl;
        cout << "CHANCE DE ASTEROIDES: " << reg.getChaAst() << endl;
        cout << "CANTIDAD DE BONUS DE SALUD: " << reg.getCntBonSa() << endl;
        cout << "CHANCE DE BONUS DE SALUD: " << reg.getChaBonSa() << endl;
        cout << "CANTIDAD DE BONUS DE ENERGIA: " << reg.getCntBonEn() << endl;
        cout << "CHANCE DE BONUS DE ENERGIA: " << reg.getChaBonEn() << endl;
        cout << "CANTIDAD DE DISPAROS ALIADOS: " << reg.getCntDiAl() << endl;
        cout << "CHANCE DE DISPAROS ALIADOS: " << reg.getChaDiAl() << endl;
        cout << endl;
    }
    fclose(p);}
    system("pause>nul");
}

int main(){
    system("color F0");
    char opcion;
    do{
        system("cls");
        cout << "MENU PRINCIPAL" << endl;
        cout << "---------------------------" << endl;
        cout << "1 - AGREGAR PERFIL" << endl;
        cout << "2 - LISTAR PERFILES" << endl;
        cout << "3 - BORRAR PERFIL" << endl;
        cout << "4 - AGREGAR NIVEL" << endl;
        cout << "5 - LISTAR NIVELES" << endl;
        cout << "6 - AGREGAR PUNTAJE" << endl;
        cout << "7 - LISTAR PUNTAJES" << endl;
        cout << endl;
        cout << "---------------------------" << endl;
        cout << "0 - SALIR" << endl;
        cout << endl;
        cout << "INGRESE OPCION: ";
        cin  >> opcion;
        switch(opcion){
            case '1':
                submenuAgregarPerfil();
            break;
            case '2':
                submenuListarPerfiles();
            break;
            case '3':
                submenuBorrarPerfil();
            break;
            case '4':
                submenuAgregarNivel();
            break;
            case '5':
                submenuListarNiveles();
            break;
            case '6':
                submenuAgregarPuntaje();
            break;
            case '7':
                submenuListarPuntajes();
            break;
        }
    }while(opcion!='0');
    return 0;
}
