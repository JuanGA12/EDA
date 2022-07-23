#include "QuadTree.h"
#include <iostream>
#include <vector>
using namespace std;

Node :: Node (Point start, Point end) : start(start), end(end) {
    ul = nullptr;
    ur = nullptr;
    dl = nullptr;
    dr = nullptr;
    state = white;
}

bool Node ::childrenEmpty() {
    if (ul || ur || dl || dr) return false;
    return true;
}

QuadTree :: QuadTree (int x, int y) {
    root = new Node({0, 0}, {static_cast<uint16_t>(x-1), static_cast<uint16_t>(y-1)});
}

bool QuadTree :: downRange(Node* node, Point p) {

    return p.y >= node->start.y && p.y <= (node->start.y + node->end.y)/2;
}

bool QuadTree :: leftRange(Node* node, Point p) {

    return p.x >= node->start.x && p.x <= (node->start.x + node->end.x)/2;
}

void QuadTree::insert(Point p, color c, uint16_t data) {
    if (c == white) return;
    insert_black(root, p,data);
}

Node* QuadTree :: searchRange(Node* node, Point p){
    bool down = downRange(node, p);
    bool left = leftRange(node, p);
    if (down && left)
        return node->dl;
    else if (down && !left)
        return node->dr;
    else if (!down && left)
        return node->ul;
    else
        return node->ur;

}

void QuadTree :: split(Node* node) {
    node->ul = new Node({node->start.x, (node->start.y + node->end.y)/2 + 1}, {(node->start.x + node->end.x)/2, node->end.y});
    node->ur = new Node({(node->start.x + node->end.x)/2 + 1, (node->start.y + node->end.y)/2 + 1}, {node->end.x, node->end.y});
    node->dl = new Node({node->start.x, node->start.y}, {(node->start.x + node->end.x)/2, (node->start.y + node->end.y)/2});
    node->dr = new Node({(node->start.x + node->end.x)/2 + 1, node->start.y}, {node->end.x, (node->start.y + node->end.y)/2});
    Point current = node->point;
    node->state = white;
    insert_black(node,current,node->data);
}

void QuadTree::insert_black(Node * node, Point p,uint16_t data) {

    if (node->childrenEmpty()) {
        // no colision
        if (node->state == white) {
            node->state = black;
            node->point = p;
            node->data = data;
        }
        // colision
        else {
            //si es que ya existe el punto y no se debe reemplazar
            if (node->start.x == node->end.x && node->start.y == node->end.y) return;
            split(node);
            insert_black(node, p, data);
        }
    }
    else {
        auto next = searchRange(node, p);
        insert_black(next, p, data);
    }

}

void Node :: printNodesConexiones(fstream &file){
    if(this->ul != nullptr){
        file << "\"" << this << "\"->";
        file << "\"" << ul << "\";\n";
        this->ul->printNodesConexiones(file);
    }
    if(this->ur != nullptr){
        file << "\"" << this << "\"->";
        file << "\"" << ur << "\";\n";
        this->ur->printNodesConexiones(file);
    }
    if(this->dl != nullptr){
        file << "\"" << this << "\"->";
        file << "\"" << dl << "\";\n";
        this->dl->printNodesConexiones(file);
    }
    if(this->dr != nullptr){
        file << "\"" << this << "\"->";
        file << "\"" << dr << "\";\n";
        this->dr->printNodesConexiones(file);
    }
}

void Node :: printAllNodes(fstream &file){
    file << "\"" << this << "\" [\n";
    file << "\tlabel = \"" <<"\\ P: "<< this->point.x<<","<<this->point.y<<" \\ c: "<< this->state <<"\\ s: "<<this->start.x <<","
         << this->start.y << "\\ e: "<<this->end.x <<"," << this->end.y <<" \"\n]\n";
    if(this->ul != nullptr){
        this->ul->printAllNodes(file);
    }
    if(this->ur != nullptr){
        this->ur->printAllNodes(file);
    }
    if(this->dl != nullptr){
        this->dl->printAllNodes(file);
    }
    if(this->dr != nullptr){
        this->dr->printAllNodes(file);
    }
}

void QuadTree::generatePDF() {
    fstream file("graph.vz", fstream::out | fstream::trunc);
    if (file.is_open()) {
        file << "digraph G\n";
        file << "{\n";
        root->printAllNodes(file);
        root->printNodesConexiones(file);
        file << "}\n";
        file.close();
        system("dot -Tpdf graph.vz -o graph.pdf");
    }
}

void QuadTree:: fillBlackNodes(Node* &node, vector<Node*> &blackNodes){
    if (node->ul and node->ur and node->dl and node->dr){
        if(node->ul->state == black and node->ur->state == black and node->dl->state == black and node->dr->state == black){
            blackNodes.push_back(node);
            return;
        }
    }
    if(node->ul) fillBlackNodes(node->ul, blackNodes);
    if(node->ur) fillBlackNodes(node->ur, blackNodes);
    if(node->dl) fillBlackNodes(node->dl, blackNodes);
    if(node->dr) fillBlackNodes(node->dr, blackNodes);
}
