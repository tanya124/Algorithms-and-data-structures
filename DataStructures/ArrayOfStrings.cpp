/*Реализуйте структуру данных “массив строк” на основе декартового дерева по неявному ключу*/

#include <iostream>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::string;
using std::make_pair;


class ImplicitTreap {
public:
    ImplicitTreap();
    ImplicitTreap(const ImplicitTreap&) = delete;
    void operator = ( ImplicitTreap&) = delete;
    ~ImplicitTreap();

    void InsertAt(int position, const string& data);
    void DeleteSector(int position1, int position2);
    string GetAt(int position) const;


private:
    struct Node{
        int size_tree;
        int priority;
        string data;
        Node* left;
        Node* right;

        Node(const string& data);

        void update_size();
    };

    void DeleteAt(int position);
    pair<Node*, Node*> split(Node* node, int position);
    Node* merge(Node* nodeL, Node* nodeR);
    void clear(Node* node);

    Node* root;
};

ImplicitTreap::ImplicitTreap(): root(nullptr){}

ImplicitTreap::~ImplicitTreap(){
    clear(root);
    root = nullptr;
}

void ImplicitTreap::clear(Node *node) {
    if (node == nullptr)
        return;
    clear(node->left);
    clear(node->right);
    delete node;
}

void ImplicitTreap::InsertAt(int position, const string& data){
    Node* node = new Node(data);
    pair<Node*, Node*> split_tree = split(root, position);
    root = merge(merge(split_tree.first, node), split_tree.second);
}

void ImplicitTreap::DeleteSector(int position1, int position2) {
    for(int i = position1; i <= position2; ++i){
        DeleteAt(i);
    }
}

void ImplicitTreap::DeleteAt(int position){
    pair<Node*, Node*> split_tree1 = split(root, position);
    pair<Node*, Node*> split_tree2 = split(split_tree1.second, 1);
    delete split_tree2.first;
    root = merge(split_tree1.first, split_tree2.second);
}

string ImplicitTreap::GetAt(int position) const{
    Node* node = root;
    bool found = false;
    int size_left_tree; 


    while(!found){
        if (node->left != nullptr){
            size_left_tree = node->left->size_tree;
        } else {
            size_left_tree = 0;
        }

        if(size_left_tree == position){
            found = true;
            break;
        }

        if (size_left_tree < position){
            position = position - (size_left_tree + 1);
            node = node->right;
        } else {
            node = node->left;
        }
    }

    return node->data;
}

pair<ImplicitTreap::Node*, ImplicitTreap::Node*> ImplicitTreap::split(Node* node, int position){
    if (node == nullptr)
        return pair<Node*, Node*>(nullptr, nullptr);


    int size_left_tree;
    if (node->left != nullptr){
        size_left_tree = node->left->size_tree;
    } else {
        size_left_tree = 0;
    }

    if (size_left_tree >= position) {
        pair<Node*, Node*> split_tree = split(node->left, position); 
        node->left = split_tree.second; 
        node->update_size();
        return make_pair(split_tree.first, node);
    }
    else { 
        pair<Node*, Node*> split_tree = split(node->right, position - size_left_tree - 1); 
        node->right = split_tree.first; 
        node->update_size();
        return make_pair(node, split_tree.second);
    }
}


ImplicitTreap::Node* ImplicitTreap::merge(Node* nodeL, Node* nodeR){
    if (nodeR == nullptr)
        return nodeL;

    if (nodeL == nullptr)
        return nodeR;

    if (nodeL->priority > nodeR->priority) {
        nodeL->right = merge(nodeL->right, nodeR);
        nodeL->update_size();
        return nodeL;
    }
    else {
        nodeR->left = merge(nodeL, nodeR->left);
        nodeR->update_size();
        return nodeR;
    }
}

ImplicitTreap::Node::Node(const string& data): data(data), priority(rand()), left(nullptr)
        , right(nullptr), size_tree(1){}



void ImplicitTreap::Node::update_size(){
    size_tree = 1;
    if (right != nullptr)
        size_tree += right->size_tree;
    if (left != nullptr)
        size_tree += left->size_tree;
}


int main() {
   int n;
   cin >> n;

    ImplicitTreap tree;

   for(int i = 0; i < n; ++i){
       char command;
       cin >> command;

       if(command == '+'){
           int position;
           string data;
           cin >> position >> data;
           tree.InsertAt(position, data);
       }
       else if (command == '-'){
           int pos1, pos2;
           cin >> pos1 >> pos2;
           tree.DeleteSector(pos1, pos2);
       }
       else if (command == '?'){
           int pos;
           cin >> pos;
           cout << tree.GetAt(pos) << endl;
       }

   }
}