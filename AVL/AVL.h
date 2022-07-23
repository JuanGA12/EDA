//
// Created by Juan Antonio Gálvez Ccopa on 17/05/21.
//

#ifndef AVL_AVL_H
#define AVL_AVL_H

#include <algorithm>
#include "Node.h"

using namespace std;
template <typename T>
class AVLtree {
public:
    Node<T> *root;
    int nodes;
private:
    bool find_by_key(Node<T>** &node, int key){
        node = &this->root;
        while(*node){
            if((*node)->key == key){
                return true;
            }else{
                node = (key > (*node)->key) ? &(*node)->right : &(*node)->left;
            }
        }
        return false;
    }
    int setHeight(Node<T>* &root_){
        if(!root_){
            return 0;
        }else{
            int height_left = setHeight(root_->left);
            int height_right = setHeight(root_->right);
            return 1 + std::max(height_left,height_right);
        }
    }
    void preOrd(Node<T>* &node){
        if(node){
            cout << node->key << " ";
            preOrd(node->left);
            preOrd(node->right);
        }
    }
    int balanceFactor(Node<T>* &root_){
        if(!root_){
            return 0;
        }else{
            int height_left = setHeight(root_->left);
            int height_right = setHeight(root_->right);
            return height_right - height_left;
        }
    }
    void rightR (Node<T>* &node){
        auto parent = node->left;
        auto left = parent->right;


        parent->right = node;
        node->left = left;

        node->height = setHeight(node);
        parent->height = setHeight(parent);

        if(node == this->root) {
            this->root = parent;
        }
        node = parent;
    }

    void leftR (Node<T>* &node){
        auto parent = node->right;
        auto right = parent->left;


        parent->left = node;
        node->right = right;

        node->height = setHeight(node);
        parent->height = setHeight(parent);

        if(node == this->root) {
            this->root = parent;
        }
        node = parent;
    }
    Node<T>* insert_(Node<T>* &node, int key, T data){

        if (!node) {
            node = new Node<T>(key, data);
            this->nodes++;
            return node;
        }

        if (key < node->key) {
            node->left = insert_(node->left, key, data);
        }
        else if (key >= node->key)
            node->right = insert_(node->right, key,data);
        else
            return node;

        node->height = setHeight(node);
        int balf = balanceFactor(node);

        //RIGHT LEFT CASE
        if(balf > 1 && key < node->right->key){
            rightR(node->right);
            leftR(node);
            return node;
        }
        //LEFT RIGHT CASE
        if(balf < -1 && key >= node->left->key) {
            leftR(node->left);
            rightR(node);
            return node;
        }

        //RIGHT RIGHT CASE
        if(balf > 1 && key > node->right->key){
            leftR(node);
            return node;
        }
        //LEFT LEFT CASE
        if(balf < -1 && key < node->left->key){
            rightR(node);
            return node;
        }

        return node;
    }
public:
    AVLtree() : root(nullptr), nodes(0) {};

    bool insert(int key, T data){
        if( key<0 ){
            throw out_of_range ("Key invalido");
        }else{

                insert_(this->root, key, data);
                return true;

            //return ( find_by_key(tmp, key) ) ? (*tmp)->data = data, false : insertar(tmp, key, data);
        }
    }
    void preOrder(){
        preOrd(this->root);
    }
};
#endif //AVL_AVL_H
