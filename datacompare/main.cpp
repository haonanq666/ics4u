#include <iostream>
#include <fstream>
#include "tokenize.h"
#include <vector>
#include "stats.h"
#include <map>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;
void listpeople();
void list(string what);
void readfile();
string findhigh(string what);
string findlow(string what);
void find(string who, string what);

map<string, vector<double> > data; //map for storing element names and the vector
int main() {
    while(true){//repeats until chosen to be ended by user
    readfile();
    cout<<endl;
    cout << "please enter command" << endl;
    string input;
    getline(cin, input);

    vector<string> inputs = split(input);
    if(inputs.size()==0){
        continue;
    }
    if (inputs[0] == "find") {
        if (inputs[1] == "highest") {
            cout << findhigh(inputs[2]) << endl;
        } else if (inputs[1] == "lowest") {
            cout << findlow(inputs[2]) << endl;
        }else if(data.count(inputs[1])>0){
            find(inputs[1], inputs[2]);
        } else{
            cout<<"illegal input"<<endl;
        }

    } else if (inputs[0] == "list") {
        if (inputs[1] == "mean") {
            list("mean");
        } else if (inputs[1] == "median") {
            list("median");
        } else if (inputs[1] == "mode") {
            list("mode");
        } else if (inputs[1] == "stddev") {
            list("stddev");
        } else if (inputs[1]=="elements"){
            listpeople();
        }else{
            cout<<"illegal input"<<endl;
        }
    } else if (inputs[0] == "quit") {
        return 0;
        //quit the program
    } else {
        cout << "illegal input try again" << endl;
    }


}
}

void listpeople(){
    map<string, vector<double> >::iterator iter;
    for(iter=data.begin(); iter!=data.end(); iter++){
        cout << iter->first << endl;
    }
}

void readfile(){
    string input;
    string datapath = "../data.txt";
    //location of data file is datacompare/data.txt
    //executable is datacompare/cmake-build-debug/datacompare.cbp
    // go back one dir to find data.txt
    ifstream filein;
    filein.open(datapath);

    while(filein.good()){
        getline(filein, input);
        if(input==""){
            continue;
        }
        vector<string> temp = split(input);
        vector<double> pdata;
        vector<string>::iterator iter;
        for(iter = temp.begin()+1; iter<temp.end(); iter++){
            pdata.push_back(stod(iter->c_str()));
        }
        data[temp[0]] = pdata;
    }
}

void list(string what){
    //uses range based for loop to list all keys and the mean/median/mode/stddev of their value
    if(what =="mean"){
        for(auto& p : data){
            cout<<p.first<<": "<<mean(p.second)<<endl;
        }
    }else if(what=="median"){
        for(auto& p : data){
            cout<<p.first<<": "<<median(p.second)<<endl;
        }
    }else if(what=="mode"){
        for(auto& p : data){
            cout<<p.first<<": "<<mode(p.second)<<endl;
        }
    }else if(what=="stddev"){
        for(auto& p : data){
            cout<<p.first<<": "<<stddev(p.second)<<endl;
        }
    }
}

string findlow(string what){
    //pmax, cmax are actually pmin, cmin
    string pmax;
    double cmax;
    if(what =="mean"){
        for(auto& p : data){
            if(mean(p.second)<cmax){
                cmax = mean(p.second);
                pmax = p.first;

            }
        }
    }else if(what=="median"){
        for(auto& p : data){
            if(median(p.second)<cmax){
                cmax = median(p.second);
                pmax = p.first;

            }
        }
    }else if(what=="mode"){
        for(auto& p : data){
            if(mode(p.second)<cmax){
                cmax = mode(p.second);
                pmax = p.first;

            }
        }
    }else if(what=="stddev"){
        for(auto& p : data){
            if(stddev(p.second)<cmax){
                cmax = stddev(p.second);
                pmax = p.first;

            }
        }
    }else{
        return "illegal input";
    }
    return pmax;
}

string findhigh(string what){
    string pmax;
    double cmax;
    if(what =="mean"){
        for(auto& p : data){
            if(mean(p.second)>cmax){
                cmax = mean(p.second);
                pmax = p.first;

            }
        }
    }else if(what=="median"){
        for(auto& p : data){
            if(median(p.second)>cmax){
                cmax = median(p.second);
                pmax = p.first;

            }
        }
    }else if(what=="mode"){
        for(auto& p : data){
            if(mode(p.second)>cmax){
                cmax = mode(p.second);
                pmax = p.first;

            }
        }
    }else if(what=="stddev"){
        for(auto& p : data){
            if(stddev(p.second)>cmax){
                cmax = stddev(p.second);
                pmax = p.first;

            }
        }
    }else{
        return "illegal input";
    }
    return pmax;
}

void find(string who, string what){
    if(data.count(who)>0){//check if "who" exists in data
        if(what =="mean"){
            cout<<mean(data[who])<<endl;
        }else if(what=="median"){
            cout<<median(data[who])<<endl;
        }else if(what=="mode"){
            cout<<mode(data[who])<<endl;
        }else if(what=="stddev") {
            cout << stddev(data[who]) << endl;
        }else if(what=="frequency"){
            map<double, int> freq = frequency(data[who]);
            int maxstringlen=0;
            for(auto& p:freq){
                //get how much to pad
                string a = to_string(p.first);
                string::iterator end = remove(a.begin(), a.end(), ' ');
                a.erase(end, a.end());
                if(a.size()>maxstringlen){
                    maxstringlen = a.size();
                }

            }
            for(auto& f:freq) {
                cout << left << setw(maxstringlen + 1) << f.first << ":" << f.second << endl;
            }
        }else{
            cout<<"illegal input"<<endl;
        }
    }
}