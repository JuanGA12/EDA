#include "QuadTree.h"
#include <iostream>
#include <vector>
#include <sstream>

QuadTree generateQuadTree (const string& fileName) {
    fstream file;
    file.open(fileName,ios::in);
    try {
        if(file.is_open()){
            file.seekg(0,ios::beg);
            stringstream ss;
            string inputLine;
            // version
            getline(file,inputLine);
            // comment
            getline(file,inputLine);
            ss << file.rdbuf();
            //size
            int rows,cols;
            ss >> cols >> rows;
            //max value
            int max_v;
            ss >> max_v;
            int array[rows][cols];

            QuadTree quad (cols, rows);
            for(int row = rows-1; row >= 0; row--) {
                for (int col = 0; col < cols; ++col) {
                    ss >> array[row][col];
                    quad.insert({static_cast<uint16_t>(col), static_cast<uint16_t>(row)}, black,static_cast<uint16_t>(array[row][col]));
                }
            }
            file.close();
            return quad;
        }else throw logic_error("No se pudo abrir el archivo .pgm");
    }
    catch (std::exception &e) {
        cout << e.what() << endl;
    }
}

void write (QuadTree & quad, const string& fileName) {
    vector<Node*> blackNodes;
    quad.fillBlackNodes(quad.root, blackNodes);

    fstream file;
    file.open(fileName,ios::out | ios::binary);
    try {
        if(file.is_open()){
            file.seekg(0,ios::beg);
            for(auto &i : blackNodes) {
                file.write((char *) (&i->start.x), sizeof(uint16_t));
                file.write((char *) (&i->start.y), sizeof(uint16_t));
                file.write((char *) (&i->end.x), sizeof(uint16_t));
                file.write((char *) (&i->end.y), sizeof(uint16_t));
                file.write((char *) (&i->point.x), sizeof(uint16_t));
                file.write((char *) (&i->point.y), sizeof(uint16_t));
                file.write((char *) (&i->data), sizeof(uint16_t));
            }
            file.close();
        } else throw logic_error("No se pudo abrir el archivo .dat");
    }
    catch (std::exception &e) {
        cout << e.what() << endl;
    }
}

void generateImage (const string& fileName, const string& imageName, Point maxValue) {

    int N = maxValue.y;
    int M = maxValue.x;
    int matrix[N][M];
    //std::fill( *matrix, *matrix + N * M, 255 );

    fstream file;
    file.open(fileName,ios::binary | ios::in);
    try{
        if(file.is_open()){
            file.seekg(0,ios::beg);
            uint16_t sx,sy,ex,ey,px,py,data;
            while(file.good()){
                file.read((char *) (&sx), sizeof(uint16_t));
                file.read((char *) (&sy), sizeof(uint16_t));
                file.read((char *) (&ex), sizeof(uint16_t));
                file.read((char *) (&ey), sizeof(uint16_t));
                file.read((char *) (&px), sizeof(uint16_t));
                file.read((char *) (&py), sizeof(uint16_t));
                file.read((char *) (&data), sizeof(uint16_t));
                for(int i = sx; i <= ex; i++ ){
                    for(int j = sy; j <= ey; j++){
                        matrix[i][j] = data;
                    }
                }
            }
            file.close();
        }else throw logic_error("No se pudo abrir el archivo .dat");
    }
    catch (std::exception &e) {
        cout << e.what() << endl;
    }
/*
    int N = maxValue.y;
    int M = maxValue.x;
    int matrix[N][M];
*/
    file.open(imageName,ios::binary | ios::out);
    try {
        if(file.is_open()){
            file << "P2\n";
            file << "# QuadTree\n";
            file << N <<" "<< M <<"\n";
            file << 255 << "\n";
            for (int i = N - 1 ; i >= 0; i--) {
                for (int j = 0; j < M; j++)
                    file << matrix[j][i]<<" ";
                file << "\n";
            }
            file.close();
        }else throw logic_error("No se pudo abrir el archivo .pgm");
    }
    catch (std::exception &e) {
        cout << e.what() << endl;
    }
}
int getSize(const string& fileName){
    int size;
    fstream file;
    file.open(fileName, ios::binary | ios::in);
    try {
        if(file.is_open()){
            file.seekg(0,ios::end);
            size = file.tellg();
            file.close();
            return size;
        }else throw logic_error("No se pudo abrir el archivo para ver el tamaño");
    }
    catch (std::exception &e) {
        cout << e.what() << endl;
    }
    return -1;
}