//
// Created by hello on 10/30/19.
//

#ifndef DATACOMPARE_TOKENIZE_H
#define DATACOMPARE_TOKENIZE_H

#include <iostream>
#include <vector>
#include <algorithm>
//tokenizes with whitespace as delim
bool space(char c){
    return isspace(c);
}
bool notspacee(char c){
    return !isspace(c);
}

std::vector<std::string> split(const std::string& input){
    using namespace std;


    typedef string::const_iterator ite;
    vector<string> out;
    ite i = input.begin();
    while( i != input.end()){
        i = find_if(i, input.end(), notspacee);
        ite j = find_if(i, input.end(), space);
        if (i != input.end()){
            out.push_back(string(i, j));
        }
        i=j;
    }
    return out;

}


#endif //DATACOMPARE_TOKENIZE_H
