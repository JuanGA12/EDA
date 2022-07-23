#include "Archivos.h"
int main() {

    QuadTree quad = generateQuadTree("dragon.pgm");
    //quad.generatePDF();
    write(quad, "out.dat");
    generateImage("out.dat", "dragon_new.pgm",
                  {static_cast<uint16_t>(quad.root->end.x+1),
                   static_cast<uint16_t>(quad.root->end.y+1)});

    int img_in = getSize("dragon.pgm");
    int img_out = getSize("dragon_new.pgm");
    int data_out = getSize("out.dat");

    cout <<"Tamaño de la estructura en disco: "<<data_out<<(data_out == 1 ?" byte": " bytes")<<"\n";
    cout <<"Tamaño de la imagen original: "<<img_in<<(img_in == 1 ?" byte": " bytes")<<"\n";
    cout <<"Tamaño de la imagen en base al QuadTree: "<<img_out<<(img_out == 1 ?" byte": " bytes")<<"\n";
    float compre = static_cast<float>(img_in)/static_cast<float>(data_out);
    cout <<"Relacion de compresion: "<<compre<<(compre == 1 ? " byte": " bytes");
    return 0;
}