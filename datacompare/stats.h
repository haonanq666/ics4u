//
// Created by hello on 10/31/19.
//

#ifndef DATACOMPARE_STATS_H
#define DATACOMPARE_STATS_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>

double median(std::vector<double>& indata){
    using namespace std;
    double median;
    sort(indata.begin(), indata.end());
    if(indata.size()%2 == 0){
        median = (indata[indata.size()/2] + indata[(indata.size()/2 )+1])/2;

    }else{
        median = indata[ceil(indata.size()/2)];
    }
    return median;
}

double mean(std::vector<double>& indata){
    using namespace std;
    double mean;
    vector<double>::iterator iter;
    for(iter = indata.begin(); iter < indata.end(); iter ++){
        mean += *iter;
    }
    mean = mean/(indata.size());
    return mean;

}

std::map<double, int> frequency(std::vector<double>& indata){
    using namespace std;
    map<double, int> count;
    vector<double>::iterator iter;
    for(iter = indata.begin(); iter<indata.end(); iter++){
        count[*iter]++;
    }

    return count;
}

double mode(std::vector<double>& indata){
    //gets a mode, not all
    using namespace std;
    map<double, int> data = frequency(indata);
    int currentmax = 0;
    double max;
    map<double, int>::iterator iter;
    for(iter = data.begin(); iter != data.end(); iter++){
        if(iter -> second > currentmax){
            currentmax = iter->second;
            max = iter-> first;
        }
    }
    return max;
}

double stddev(std::vector<double>& indata) {
    //without bessel correction
    using namespace std;
    double element = 0;
    double u = mean(indata);

    vector<double>::iterator iter;
    for (iter = indata.begin(); iter < indata.end(); iter++) {
        element += pow((*iter - u), 2);
    }
    double dev = sqrt(element/indata.size());
    return dev;
}



#endif //DATACOMPARE_STATS_H
