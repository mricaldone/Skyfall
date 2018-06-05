#ifndef FONDO_HPP_INCLUDED
#define FONDO_HPP_INCLUDED

class Fondo{
private:
    struct COORDENADA{
        int x;
        int y;
    };
    struct FONDO{
        BITMAP* img;
        COORDENADA pos;
        int vel;
    };
    FONDO bg[3];
public:
    void cargarImagenMosaico(BITMAP*&,char*,int,int);
    void copiarFondo(BITMAP*&);
    Fondo();
    ~Fondo();
};

Fondo::Fondo(){
    cargarImagenMosaico(bg[0].img,"img/galaxia0.bmp",640,960);
    bg[0].pos={0,-480};
    bg[0].vel=1;
    cargarImagenMosaico(bg[1].img,"img/galaxia1.bmp",640,960);
    bg[1].pos={0,-480};
    bg[1].vel=2;
    cargarImagenMosaico(bg[2].img,"img/galaxia2.bmp",640,960);
    bg[2].pos={0,-480};
    bg[2].vel=3;
}

void Fondo::cargarImagenMosaico(BITMAP* &salida,char *dir,int w,int h){
    salida=create_bitmap(w,h);
    clear_to_color(salida, makecol(255, 0, 255));
    BITMAP* imagen=load_bitmap(dir,NULL);
    for(int x=0;x<h/imagen->w;x++){
        for(int y=0;y<h/imagen->h;y++){
            draw_sprite(salida, imagen, x*imagen->w, y*imagen->h);
        }
    }
    destroy_bitmap(imagen);
    return;
}

void Fondo::copiarFondo(BITMAP* &salida){
    bg[0].pos.y+=bg[0].vel;
    if(bg[0].pos.y>=0){bg[0].pos.y-=480;}
    draw_sprite(salida, bg[0].img, 0, bg[0].pos.y);

    bg[1].pos.y+=bg[1].vel;
    if(bg[1].pos.y>=0){bg[1].pos.y-=480;}
    draw_sprite(salida, bg[1].img, 0, bg[1].pos.y);

    bg[2].pos.y+=bg[2].vel;
    if(bg[2].pos.y>=0){bg[2].pos.y-=480;}
    draw_sprite(salida, bg[2].img, 0, bg[2].pos.y);
}

Fondo::~Fondo(){
    destroy_bitmap(bg[0].img);
    destroy_bitmap(bg[1].img);
    destroy_bitmap(bg[2].img);
}
#endif // FONDO_HPP_INCLUDED
