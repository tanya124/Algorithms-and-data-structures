#include <iostream>
#include <stack>

using std::cin;
using std::cout;
using std::stack;


template <typename T>
class BST{
public:
    BST();
    ~BST();

    void add(T key);
    void InOrder() const;
    void clear();

private:
    struct Node{
        Node* left;
        Node* right;
        T key;
    };
	
    Node* root;

    void clearRec(Node *node);
};

template <typename T>
BST<T>::BST(): root(nullptr){}

template <typename T>
BST<T>::~BST(){
    clear();
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
    while(key < node->key && node->left != nullptr || key > node->key && node->right != nullptr){ 
        node = (key < node->key)?(node->left):(node->right);
    }
    if(key < node->key) 
        node->left = tmp;
    else
        node->right = tmp;
}

template <typename T>
void BST<T>::InOrder() const{
         stack <Node*> stack_;
		 
         while (root != nullptr || !stack_.empty()){
             if (!stack_.empty()){    
                 root = stack_.top();
                 stack_.pop();
                 cout <<root->key<<" ";
                 if (root->right != nullptr)  
                     root = root->right;
                 else                     
                     root = nullptr;
             }
             while (root != nullptr){ 
                 stack_.push(root);
                 root = root->left;
             }
         }
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


int main(){
    BST <int> bst;
    int n, key;
    cin >> n;
	
    for(int i = 0; i < n; i++){
        cin >> key;
        bst.add(key);
    }
	
    bst.InOrder();
}
