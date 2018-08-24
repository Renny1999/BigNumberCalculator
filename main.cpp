#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <stack>
#include "tree.h"
#include "handyfunctions.h"
#include "bignumber.h"

using namespace std;


string convert2postfix(string str);

int main()
{
//    string str = "( 1 + 2 ) * 3 - ( 4 - 5 ) * ( 6 + 7 )";
//    string s = convert2postfix(str);

//    Tree t(s);

//    t.print(t.root);
//    BigNumber a("365");
//    BigNumber b("5");
//    BigNumber c("3");
//    cout<<(a/b*b)<<endl;

    return 0;
}

string convert2postfix(string str){
    vector<string> v = split(str, " ");
    stack<string> opStack;
    vector<string> postfix;
    map<string, int> m;
    m["("] = 0;
    m["+"] = 1;
    m["-"] = 1;
    m["*"] = 2;
    m["/"] = 2;

    for(int i = 0; i < v.size(); i++){
        string token = v.at(i);
        if(isNum(token)){
            postfix.push_back(token);
        }else if(token == "("){
            opStack.push(token);
        }else if(token == ")"){
            string topToken = opStack.top();
            opStack.pop();
            while(topToken != "("){
                postfix.push_back(topToken);
                topToken = opStack.top();
                opStack.pop();
            }
        }else{  //if it's an operator
            while(!opStack.empty() && m[opStack.top()] >= m[token]){
                postfix.push_back(opStack.top());
                opStack.pop();
            }
            opStack.push(token);
        }
    }
    while(!opStack.empty()){
        postfix.push_back(opStack.top());
        opStack.pop();
    }

    string output = "";
    for(int i = 0; i < postfix.size(); i++){
        if(i != postfix.size()-1){
            output+=postfix.at(i)+" ";
        }else{
            output+=postfix.at(i);
        }
    }

    return output;
}

