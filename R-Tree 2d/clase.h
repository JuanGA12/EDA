#ifndef AVL_CLASE_H
#define AVL_CLASE_H

#include <iostream>
#include <algorithm>
#include <list>
#include <sstream>
#include <fstream>

using namespace std;

struct Point{
    int x;
    int y;
};

class Node;

class RTree {

public:

    Node *root;
    int nodes;

private:

    Node* find_by_key(int key);
    int setHeight(Node* &root_);
    void preOrd(Node* &node);
    int balanceFactor(Node* &root_);
    void rightR (Node* &node);
    void leftR (Node* &node);
    Node *insert_(Node *&node, int key, int x, int y,Node *&toInsert);
    bool insertKey(int key, int x, int y);

public:

    RTree() : root(nullptr), nodes(0){};

    void generatePDF();
    bool insert(int x, int y,bool isX);
    void preOrder();
    void split(Node** &node, int x1, int x2);
    vector<Node*> search(Point p1, Point p2);
    void searchRange(Node* &node, int x1, int x2, vector<Node*> &list);
    vector<Point> createYtree(Node *&node);
    void insertPoints(const vector<Point>& points);
    void insertPointsY(const vector<Point>& points);
    vector<Point> generateFromFile(const string& fileName);
    void searchOutFile(const string& fileName, Point p1, Point p2);
};

class Node {

public:

    int key;
    int x;
    int y;
    int height;
    Node* left;
    Node* right;
    RTree* tree;

    Node(int key, int x, int y): height(1), key(key){
        left = nullptr;
        right = nullptr;
        this->x = x;
        this->y = y;
        this->tree = new RTree();
    }

    bool isLeaf();
    void printAllNodes(fstream &file);
    void printNodesConexiones(fstream &file);
    void killSelf();

    friend class RTree;
};



#endif //AVL_CLASE_H
