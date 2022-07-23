#include "clase.h"

bool Node :: isLeaf(){
    return this->left == nullptr && this->right == nullptr;
}

void Node :: printAllNodes(fstream &file){
    file << "\"" << this << "\" [\n";
    file << "\tlabel = \"" << this->key <<"\\n grado: "<<this->height << "\\n hoja: "<<this->isLeaf() <<" \"\n]\n";
    if(this->left != nullptr){
        this->left->printAllNodes(file);
    }
    if(this->right != nullptr){
        this->right->printAllNodes(file);
    }
}

void Node :: printNodesConexiones(fstream &file){
    if(this->left != nullptr){
        file << "\"" << this << "\"->";
        file << "\"" << left << "\";\n";
        this->left->printNodesConexiones(file);
    }
    if(this->right != nullptr){
        file << "\"" << this << "\"->";
        file << "\"" << right << "\";\n";
        this->right->printNodesConexiones(file);
    }
}

void Node :: killSelf() {

    if (left){
        left->killSelf();
    }
    else if (right){
        right->killSelf();
    }
    delete this;

}