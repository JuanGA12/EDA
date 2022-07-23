#ifndef QUADTREE_QUADTREE_H
#define QUADTREE_QUADTREE_H

#include <fstream>
#include <vector>
using namespace std;

enum color {
    black,
    white
};

struct Point {
    uint16_t x;
    uint16_t y;
};

class Node {

public:

    Node* ul;
    Node* ur;
    Node* dl;
    Node* dr;

    color state;
    Point start;
    Point end;
    Point point;
    uint16_t data;
    Node (Point start, Point end);

    bool childrenEmpty ();
    void printAllNodes(fstream &file);
    void printNodesConexiones(fstream &file);

};

class QuadTree {

    void insert_black (Node* node, Point p, uint16_t data);
    void split(Node* node);
    Node* searchRange(Node* node, Point p);
    bool downRange(Node* node, Point p);
    bool leftRange(Node* node, Point p);

public:
    Node* root;
    QuadTree (int x, int y);
    void insert (Point p, color c, uint16_t data);
    void generatePDF();
    void fillBlackNodes(Node* &node, vector<Node*> &blackNodes);

};


#endif //QUADTREE_QUADTREE_H
