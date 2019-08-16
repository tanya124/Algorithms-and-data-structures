#include <iostream>

using std::cin;
using std::cout;

template <typename T>
class Treap{
public:
    Treap();
    ~Treap();

    Treap(const Treap& rhs) = delete;
    Treap& operator=(const Treap& rhs) = delete;

    void add(T key, int priority);
    int get_width(int arr_size) const;
    int height() const;
    void clear();

private:
    struct Node{
        Node* left;
        Node* right;
        int key;
        int priority;
    };
    Node* root;

    void split(Node* node, T key, Node*& left, Node*& right);
    void heightRec(Node* node, int height, int& max) const;
    void recInOrder(Node* node, int lvl, int* arr) const;
    void clearRec(Node * node);
};

template <typename T>
Treap<T>::Treap(): root(nullptr){}


template <typename T>
Treap<T>::~Treap(){
    clear();
}

template <typename T>
void Treap<T>::add( T key, int priority){
    Node *left = nullptr;
    Node *right = nullptr;
    Node *tmp = new Node;

    Node *node = root;
    Node *node_parent = nullptr;

    while (node != nullptr && priority <= node->priority){
        node_parent = node;
        node = (key < node->key)?(node->left):(node->right);
    }

    split(node, key, left, right);

    if(node_parent == nullptr) {
        root = tmp;
    }
    else if(key < node_parent->key) {
        node_parent->left = tmp;
    }
    else {
        node_parent->right = tmp;
    }

    tmp->left = left;
    tmp->right = right;
    tmp->key = key;
    tmp->priority = priority;
}

template <typename T>
void Treap<T>::split(Node* node, T key, Node*& left, Node*& right){
    if(node == nullptr){
        left = nullptr;
        right = nullptr;
    }
    else if(node->key < key){
        split(node->right, key, node->right, right);
        left = node;
    }
    else{
        split(node->left, key, left, node->left);
        right = node;
    }
}

template <typename T>
int Treap<T>::height() const{
    int max = 0;
    heightRec(root, 1, max);
    return max;
}

template <typename T>
void Treap<T>::heightRec(Node* node, int height, int & max) const{
    if(node == nullptr)
        return;
    if(height > max)
        max = height;

    heightRec(node->left, height + 1, max);
    heightRec(node->right, height + 1, max);
}

template <typename T>
void Treap<T>::recInOrder(Node* node, int lvl, int* arr) const{
    if (node == nullptr)
        return;

    recInOrder(node->left, lvl + 1, arr);
    arr[lvl]++;
    recInOrder(node->right, lvl + 1, arr);
}

template <typename T>
int Treap<T>::get_width(int arr_size) const{
    int* arr = new int [arr_size];
    recInOrder(root, 0, arr);
    int Max = 0;

    for (int i = 0; i < arr_size; ++i)
        Max = (arr[i] > Max ? arr[i]: Max);

    return Max;
}

template <typename T>
void Treap<T>::clear(){
    clearRec(root);
}

template <typename T>
void Treap<T>::clearRec(Node* node){
    if (node == nullptr)
        return;

    clearRec(node->left);
    clearRec(node->right);
    delete node;
}


template<typename T>
class BST{
public:
    BST();
    ~BST();

    BST(const BST& rhs) = delete;
    BST& operator=(const BST& rhs) = delete;

    void add(T key);
    void clear();
    int get_width(int arr_size) const;
    int height() const;

private:
    struct Node{
        Node* left;
        Node* right;
        T key;
    };

    Node* root;

    void clearRec(Node* node);
    void heightRec(Node* node, int height, int & max) const;
    void recInOrder(Node* node, int lvl, int* arr) const;
};

template <typename T>
BST<T>::BST(): root(nullptr){}


template <typename T>
BST<T>::~BST(){
    clear();
}


template <typename T>
int BST<T>::height() const{
    int max = 0;
    heightRec(root, 1, max);
    return max;
}


template <typename T>
void BST<T>::heightRec(Node * node, int height, int & max) const{
    if(node == nullptr)
        return;

    if(height > max)
        max = height;

    heightRec(node->left, height + 1, max);
    heightRec(node->right, height + 1, max);
}


template <typename T>
void BST<T>::add(T key){
    Node* tmp = new Node;
    tmp->left = nullptr;
    tmp->right = nullptr;
    tmp->key = key;

    if(root == nullptr){
        root = tmp;
        return;
    }

    Node* node = root;
    while((key < node->key && node->left != nullptr) || (key > node->key && node->right != nullptr)){
        node = (key < node->key)?(node->left):(node->right);
    }
    if(key < node->key) {
        node->left = tmp;
    } else {
        node->right = tmp;
    }
}


template <typename T>
void BST<T>::recInOrder(Node* node, int lvl, int* arr) const{
    if (node == nullptr)
        return;

    recInOrder(node->left, lvl + 1, arr);
    arr[lvl]++;
    recInOrder(node->right, lvl + 1, arr);
}


template <typename T>
int BST<T>::get_width(int arr_size) const{
    int* arr = new int [arr_size];
    recInOrder(root, 0, arr);
    int Max = 0;

    for (int i = 0; i < arr_size; ++i)
        Max = (arr[i] > Max ? arr[i]: Max);

    return Max;
}


template <typename T>
void BST<T>::clear(){
    clearRec(root);
    root = nullptr;
}


template <typename T>
void BST<T>::clearRec(Node * node){
    if(node == nullptr)
        return;

    clearRec(node->left);
    clearRec(node->right);
    delete node;
}


int main() {
    BST<int>bst;
    Treap <int> treap;

    int n, key, priority;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> key >> priority;
        treap.add(key,priority);
        bst.add(key);
    }
    cout <<treap.get_width(treap.height()) - bst.get_width(bst.height());
}
