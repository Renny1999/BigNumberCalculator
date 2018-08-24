#include "handyfunctions.h"
#include <iostream>

using namespace std;

vector<string> split(string input, string s){
    vector<string> output;
    int start = 0;
    string str = input+s;
    string temp = "";
    while(start < str.length() - s.length()+1){
        string letter = str.substr(start,s.length());
        if(letter != s){
            temp+=letter;
            start++;
        }else{
            output.push_back(temp);
            temp = "";
            start+=s.length();
        }
    }
    return output;
}

bool isNum(string str){
    if(str == "-"){
        return false;
    }

    int i;
    if(str.substr(0,1) == "-"){
        i = 1;
    }else{
        i = 0;
    }
    bool firstDot = false;
    for(i; i < str.length(); i++){
        if(str.substr(i,1) == "."){
            if(!firstDot){
                firstDot = true;
            }else{
                return false;
            }
        }else if(!std::isdigit(str.substr(i,1)[0])){
            return false;
        }else{
            continue;
        }
    }
    return true;
}
