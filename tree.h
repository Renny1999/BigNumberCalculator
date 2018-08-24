#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <vector>
#include <string>

struct Node{
    Node* left;
    Node* right;
    std::string data;
};

class Tree{
public:
    Node* root;

    Tree(std::string);
    ~Tree();
    void insert(std::string data);
    void print(Node* root);
    double evaluate();
    void printTokens();
    std::vector<std::string> getTokens();
private:
    void destruct(Node* root);
    std::vector<std::string> tokens;
};

#endif // TREE_H
