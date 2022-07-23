#include <vector>
#include "clase.h"

using namespace std;

Node* RTree :: find_by_key(int key){
    if (!root) return nullptr;
    Node** node = &this->root;
    while(*node){
        if((*node)->key == key && (*node)->isLeaf())
            return *node;
        else
            node = (key > (*node)->key) ? &(*node)->right : &(*node)->left;
    }
    return nullptr;
}

int RTree :: setHeight(Node* &root_){
    if(!root_)
        return 0;
    else{
        int height_left = setHeight(root_->left);
        int height_right = setHeight(root_->right);
        return 1 + std::max(height_left,height_right);
    }
}

void RTree :: preOrd(Node* &node){
    if(node){
        cout << node->key << " ";
        preOrd(node->left);
        preOrd(node->right);
    }
}

int RTree :: balanceFactor(Node* &root_){
    if(!root_)
        return 0;
    else {
        int height_left = setHeight(root_->left);
        int height_right = setHeight(root_->right);
        return height_right - height_left;
    }
}

void RTree :: rightR (Node* &node){
    auto parent = node->left;
    auto left = parent->right;

    parent->right = node;
    node->left = left;

    node->height = setHeight(node);
    parent->height = setHeight(parent);

    if(node == this->root)
        this->root = parent;

    node = parent;
}

void RTree :: leftR (Node* &node){

    auto parent = node->right;
    auto right = parent->left;

    parent->left = node;
    node->right = right;

    node->height = setHeight(node);
    parent->height = setHeight(parent);

    if(node == this->root)
        this->root = parent;

    node = parent;
}

Node* RTree :: insert_(Node* &node, int key, int x, int y, Node* &toInsert){

    if (!node) {
        node = new Node(key, x, y);
        this->nodes++;
        return node;
    }
    if (key < node->key) {
        if (!node->left)
            toInsert = new Node (key, x, y);
        node->left = insert_(node->left, key, x, y,toInsert);
    }
    else if (key >= node->key) {

        if (!node->right)
            toInsert = new Node (node->key, node->x, node->y);
        node->right = insert_(node->right, key, x, y,toInsert);
    }
    else
        return node;

    node->height = setHeight(node);

    if (nodes > 2 && nodes % 2 == 1) {

        int balf = balanceFactor(node);

        if(balf > 1 && key < node->right->key) {
            rightR(node->right);
            leftR(node);
        }

        else if(balf < -1 && key >= node->left->key) {
            leftR(node->left);
            rightR(node);
        }

        else if(balf > 1 && key >= node->right->key)
            leftR(node);

        else if(balf < -1 && key < node->left->key)
            rightR(node);
    }

    return node;
}

void RTree :: generatePDF() {
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

bool RTree :: insertKey(int key, int x, int y){
    if(x < 0 or y < 0)
        throw out_of_range ("Index invalido");
    else{
        Node * toInsert = nullptr;
        insert_(this->root, key, x, y,toInsert);
        if (nodes > 1)
            insert_(this->root, toInsert->key, toInsert->x, toInsert->y, toInsert);
        return true;
    }
}

bool RTree :: insert(int x, int y, bool isX){
    return isX ? insertKey(x, x, y) : insertKey(y, x, y);
}

void RTree :: preOrder(){
    preOrd(this->root);
}

void RTree :: split(Node** &node, int x1, int x2){
    node = &this->root;
    while(*node) {
        if (x1 > ((*node)->key) && x2 > ((*node)->key))
            node = &(*node)->right;
        else if (x1 <= ((*node)->key) && x2 <= ((*node)->key))
            node = &(*node)->left;
        else break;
    }
}

void RTree :: searchRange(Node* &node, int x1, int x2, vector<Node*> &vector) {
    if(node) {
        if (!node->left && !node->right && node->key >= x1 && node->key <= x2)
            vector.push_back(node);
        else {
            if (node->key < x1)
                searchRange(node->right, x1, x2, vector);
            else if (node->key >= x2)
                searchRange(node->left, x1, x2, vector);
            else if (node->key >= x1 && node->key < x2) {
                searchRange(node->left, x1, x2, vector);
                searchRange(node->right, x1, x2, vector);
            }
        }
    }
}

vector<Node*> RTree :: search(Point p1, Point p2) {
    Node **tmp = nullptr;
    split(tmp, p1.x, p2.x);
    vector<Node*> vector;
    searchRange(*tmp, p1.x, p2.x, vector);

    std::vector<Node*> n_vector;
    for(auto nod : vector)
        searchRange(nod->tree->root, p1.y, p2.y, n_vector);
    return n_vector;
}

vector<Point> RTree :: generateFromFile(const string& fileName){
    ifstream from(fileName);
    vector<Point> points;
    vector<Point> input;
    string line;
    int i = 0;
    if (from.is_open()){
        for(int j = 0; j < 3; j++){
            getline(from, line);
            if(j<2){
                stringstream stream(line);
                string value, x, y;
                while (getline(stream, value, ' ')) {
                    if (i == 0) {x = value; i++;}
                    else {y = value; i--;}
                }
                input.push_back({stoi(x), stoi(y)});
            }
        }
        while(getline(from, line)) {
            stringstream stream(line);
            string value, x, y;
            while (getline(stream, value, ' ')) {
                if (i == 0) {x = value; i++;}
                else {y = value; i--;}
            }
            points.push_back({stoi(x), stoi(y)});
        }
    }
    from.close();
    std::sort(points.begin(), points.end(), [](Point a, Point b){ return a.x < b.x; });
    insertPoints(points);
    return input;
}

void RTree :: searchOutFile(const string& fileName, Point p1, Point p2) {
    ofstream file(fileName);
    auto vector = this->search(p1, p2);
    if (file.is_open()) {
        for (auto e : vector)
            file << e->x << " " << e->y << '\n';
    }
    file.close();
}

void RTree :: insertPoints(const vector<Point>& points){
    for(auto point : points){
        auto aux = this->find_by_key(point.x);
        if(!aux)
            this->insertKey(point.x, point.x, point.y);
        else
            aux->tree->insertKey(point.y, point.x, point.y);
    }
    this->generatePDF();//Print PDF
    this->createYtree(this->root);
}

void RTree :: insertPointsY (const vector<Point>& points){
    for(auto point : points)
       this->insertKey(point.y, point.x, point.y);
}

vector<Point> RTree :: createYtree(Node* &node){
    if (!node->left && !node->right) {
        vector<Point> points;
        points.push_back({node->x, node->y});
        node->tree->insertKey(node->y, node->x, node->y);
        return points;
    } else {
        vector<Point> pointsLeft;
        vector<Point> pointsRight;
        pointsLeft = createYtree(node->left);
        pointsRight = createYtree(node->right);
        for (auto pointRight : pointsRight)
            pointsLeft.push_back(pointRight);
        node->tree->insertPointsY(pointsLeft);
        return pointsLeft;
    }
}