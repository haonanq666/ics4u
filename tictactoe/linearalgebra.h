

#ifndef INC_5DTICTACTOE_LINEARALGEBRA_H
#define INC_5DTICTACTOE_LINEARALGEBRA_H


#include <iostream>
#include <string>
#include <cmath>

//std namespace should not be used at global level

std::vector<int> subtract(std::vector<int>& vec1, std::vector<int>& vec2){
    //elementwise subtraction of two vectors
    using namespace std;
    vector<int> a(5);
    for(int i=0; i<vec1.size();i++){
        int ai = vec1[i] - vec2[i];
        a[i] = ai;
    }
    return a;
}



double magnitude(std::vector<int>& vec){
    // uses pythagorean theorem to find magnitude of vector
    double num = 0;
    for(int i: vec){
        num += (pow(static_cast<double>(i), 2.0));
    }

    return sqrt(num);

}


#endif //INC_5DTICTACTOE_LINEARALGEBRA_H
