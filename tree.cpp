#include <iostream>
#include <cstdlib>
#include "tree.h"
#include <vector>
#include <stack>
using namespace std;

Tree::Tree(string str){

    stack<Node*> s;

    int start = 0;
    while(start < str.length()){
        int end = start;
        while(end < str.length() && str.substr(end, 1) != " "){
            end++;
        }
        string data = str.substr(start, end-start+1);
        tokens.push_back(data);
        start = end+1;
        try{
            stod(data);
            Node* n = new Node;
            n->data = data;
            n->left = nullptr;
            n->right = nullptr;

            s.push(n);

        }catch(exception e){
            //if it's a token
            Node* n = new Node;
            Node* right = s.top();
            s.pop();
            Node* left = s.top();
            s.pop();

            n->data = data;
            n->left = left;
            n->right = right;

            s.push(n);
            root = n;
        }
    }
}

Tree::~Tree(){
    destruct(this->root);
}

void Tree::insert(string data){
    cout<<"stub"<<endl;
}

void Tree::print(Node* root){
    //move to the left most
    if(root->left != nullptr){
        print(root->left);
    }
    if(root->right != nullptr){
        print(root->right);
    }

    cout<<root->data<<endl;
}

void Tree::destruct(Node *root){
    if(root->left){
        Tree::destruct(root->left);
    }
    if(root->right){
        Tree::destruct(root->right);
    }
    delete root;
}

double Tree::evaluate(){}

void Tree::printTokens(){
    for(std::vector<string>::iterator it = this->tokens.begin();
        it != tokens.end(); it++){
        cout<<*it<<endl;
    }
}

vector<string> Tree::getTokens(){
    return this->tokens;
}













