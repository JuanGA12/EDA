//
// Created by Juan Antonio Gálvez Ccopa on 17/05/21.
//

#ifndef AVL_NODE_H
#define AVL_NODE_H

template <typename T>
class Node {
public:
    T data;
    int key;
    int height;
    Node<T>* left;
    Node<T>* right;

    Node(int key, T data): height(1), data(data), key(key){
        left = nullptr;
        right = nullptr;
    }

    void killSelf();

    template<class>
    friend class AVLtree;

    template<class>
    friend class Iterator;


};
template <typename T>
void Node<T>::killSelf() {

    if (left){
        left->killSelf();
    }
    else if (right){
        right->killSelf();
    }
    delete this;

}

#endif //AVL_NODE_H
