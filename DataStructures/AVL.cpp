/*Дано число N и N строк. Каждая строка содержит команду добавления или удаления натуральных чисел,
 а также запрос на получение k-ой порядковой статистики. Команда добавления числа A задается положительным числом A,
 команда удаления числа A задается отрицательным числом “-A”.
 Запрос на получение k-ой порядковой статистики задается числом k. Требуемая скорость выполнения запроса - O(log n).*/

#include <iostream>

using std::max;
using std::cin;
using std::cout;

template <typename T>
class AVL{
public:
    AVL();
    ~AVL();
    AVL(const T& a) = delete;
    AVL& operator=(const T& a) = delete;


    void add(T key);
    void remove(T key);
    int KStat(int k) const;
    void clear();

private:
    struct Node{
        Node* left = nullptr;
        Node* right = nullptr;
        T key;
        int height;
        int size_leftTree; 

        Node(T key): key{key}, height{0}, size_leftTree{0} {}
    };

    void fixHeight(Node* &node);
    void deleteFatherLeft(Node* node);
    void deleteFatherRight(Node* node);
    void rotLeft(Node* &p, Node* &node, bool left_right);
    void rotRight(Node* &p, Node* &node, bool left_right);
    void big_rotLeft(Node* &p, Node* &node, bool left_right);
    void big_rotRight(Node* &p, Node* &node, bool left_right);
    void balance(Node* &p, Node* &node, bool left_right);
    void recAdd(Node* &p, T key, Node* &node, bool left_right);
    void recRemove(Node* &p, T key, Node* &node, bool left_right);
    void find_remove(Node* &Root, Node* &p, Node* &node);
    int KStatistics(int k, Node* node) const;
    void clearRec(Node* node);

    Node* root;
};


template <typename T>
AVL<T>::AVL(): root(nullptr){}

template <typename T>
AVL<T>::~AVL(){
    clear();
}


template <typename T>
void AVL<T>::clear(){
    clearRec(root);
    root = nullptr;
}

template <typename T>
void AVL<T>::clearRec(Node* node){
    if(node == nullptr)
        return;
    
    clearRec(node->left);
    clearRec(node->right);
    delete node;
}

template <typename T>
void AVL<T>::rotLeft(Node* &p, Node* &node, bool left_right){//малый левый поворот
    Node* a = node->right;
    node->right = node->right->left;
    a->left = node;

    fixHeight(node);
    fixHeight(a);

    a->size_leftTree += node->size_leftTree + 1;
    if (node == root) {
        root = a;
    } else {
        (left_right ? p->right = a : p->left = a);
    }
}

template <typename T>
void AVL<T>::rotRight(Node* &p, Node* &node, bool left_right){ //малый правый поворот
    Node* a = node->left;
    node->left = node->left->right;
    a->right = node;

    fixHeight(node);
    fixHeight(a);

    node->size_leftTree -= a->size_leftTree + 1;
    if (node == root) {
        root = a;
    } else {
        (left_right ? p->right = a : p->left = a);
    }
}

template <typename T>
void AVL<T>::big_rotLeft(Node* &p, Node* &node, bool left_right){
    rotRight(node, node->right, true);
    rotLeft(p, node, left_right);
}

template <typename T>
void AVL<T>::big_rotRight(Node* &p, Node* &node, bool left_right){
    rotLeft(node, node->left, false);
    rotRight(p, node, left_right);
}

template <typename T>
void AVL<T>::balance(Node* &p, Node* &node, bool left_right){
    if(node->left == nullptr && node->height == 2){
        if(node->right->right == nullptr) {
            big_rotLeft(p, node, left_right);
        } else {
            rotLeft(p, node, left_right);
        }
        return;
    }

    if(node->left == nullptr)
        return;

    if(node->right == nullptr && node->height == 2){
        if(node->left->left == nullptr) {
            big_rotRight(p, node, left_right);
        } else {
            rotRight(p, node, left_right);
        }
        return;
    }

    if(node->right == nullptr)
        return;

    if(node->left->height == node->right->height - 2){
        if(node->right->right->height < node->right->left->height) {
            big_rotLeft(p, node, left_right);
        } else {
            rotLeft(p, node, left_right);
        }
        return;
    }
    if(node->left->height == node->right->height + 2){
        if(node->left->left->height < node->left->right->height) {
            big_rotRight(p, node, left_right);
        } else {
            rotRight(p, node, left_right);
        }
        return;
    }
}

template <typename T>
void AVL<T>::add(T key){
    recAdd(root, key, root, true);
}

template <typename T>
void AVL<T>::recAdd(Node* &p, T key, Node* &node, bool left_right){
    if (node != nullptr && node->key == key)
        return;
    
    if (node == nullptr) {
        node = new Node{key};
    } else {
        if (node->key > key){
            recAdd(node, key, node->left, false);
            ++node->size_leftTree;
        }
        else {
            recAdd(node, key, node->right, true);
        }

        fixHeight(node);
        balance(p, node, left_right);
    }
}

template <typename T>
void AVL<T>::fixHeight(Node* &node){
    if (node->left != nullptr) {
        if (node->right != nullptr) {
            node->height = max(node->left->height, node->right->height) + 1;
        } else {
            node->height = node->left->height + 1;
        }
    } else if (node->right != nullptr) {
        node->height = node->right->height + 1;
    } else {
        node->height = 0;
    }
}

template <typename T>
void AVL<T>::find_remove(Node* &Root, Node* &p, Node* &node){
    if (node->right != nullptr){
        find_remove(Root, node, node->right);
        fixHeight(node); 
        balance(p, node, bool(Root != p));
    }
    else{
        Root->key = node->key; 
        Root->size_leftTree = Root->size_leftTree - 1;
        recRemove(p, Root->key, node, bool(Root != p));
    }
}

template <typename T>
void AVL<T>::remove(T key){
    recRemove(root, key, root, true);
}

template <typename T>
void AVL<T>::recRemove(Node* &p, T key, Node* &node, bool left_right){
    if (node == nullptr)
        return;
    
    if (node->key == key) {
        if (node->right == nullptr)
            if (node->left == nullptr) {
                Node **temp = &node;
                (left_right ? p->right = nullptr : p->left = nullptr);
                delete *temp;
                return;
            } else {
                deleteFatherLeft(node);
            }
        else if (node->left == nullptr) {
            deleteFatherRight(node);
        } else
            find_remove(node, node, node->left);
    } else if (node->key > key){
        recRemove(node, key, node->left, false);
        node->size_leftTree--;
    } else {
        recRemove(node, key, node->right, true);
    }

    fixHeight(node);
    balance(p, node, left_right);
}

template <typename T>
void AVL<T>::deleteFatherLeft(Node* node){
    Node** temp = &node->left;
    node->key = (*temp)->key;
    node->size_leftTree = (*temp)->size_leftTree;
    node->height = (*temp)->height;
    node->right = (*temp)->right;
    node->left = (*temp)->left;
    delete *temp;
}

template <typename T>
void AVL<T>::deleteFatherRight(Node* node){
    Node** temp = &node->right;
    node->key = (*temp)->key;
    node->size_leftTree = (*temp)->size_leftTree;
    node->height = (*temp)->height;
    node->left = (*temp)->left;
    node->right = (*temp)->right;
    delete *temp;
}

template <typename T>
int AVL<T>::KStat(int k) const{
    return KStatistics(k, root);
}

template <typename T>
int AVL<T>::KStatistics(int k, Node* node) const{
    while(k != node->size_leftTree){ 
        if(node->size_leftTree < k){
            k = k - (node->size_leftTree + 1);    
            node = node->right;    
        } else {
            node = node->left;
        }
    }
    return node->key;
}

int main(){
    int N, key, k;
    cin >> N;
    AVL <int> avl;
    for(int i = 0; i < N; ++i)
    {
        cin >> key >> k;
        if (key > 0)
            avl.add(key);
        else
            avl.remove(-key);
        cout << avl.KStat(k) << " ";
    }
    return 0;
}