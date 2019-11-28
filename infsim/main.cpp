

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <random>
#include "tokenize.h"
#include "WorldClass.h"
#include "disease.h"

//I: infected
//H: healthy
//D: deceased
//R: recovered (only when immunity true)
//N: newly infected this loop, is temporary

using namespace std;

//set up a random number generator; this merseinne twister is a better pseudorandom
random_device rd;
mt19937 mt(rd());
uniform_real_distribution<double> dist(0,1);

double randdouble();//generates a random double

void getdisease(double& inf, double& die, double& recov, bool& immun){
        // gets the specifics of the disease from the user
        string immin;
        cout << "enter disease stats:" << endl;
        cout << "chance of infection: ";
        cin >> inf;
        if(!cin.good()) {
            //checks for invalid input(all remaining such conditional blocks
            //are the same purpose
            cout << endl <<red<< "bad input" << reset<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            //remove all remaining characters and error states from input stream
            //so that more input can be taken
            cout<<endl;
            return getdisease(inf, die, recov, immun);
        }
        cout << "chance of death: ";
        cin >> die;
        if(!cin.good()) {
            cout << endl <<red<< "bad input" <<reset<< endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<endl;
            return getdisease(inf, die, recov, immun);
        }
        cout << "chance of recovery: ";
        cin >> recov;
        if(!cin.good()) {
            cout << endl <<red<< "bad input" << reset<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<endl;
            return getdisease(inf, die, recov, immun);
        }
        cout << "immunity for recovered (yes/no): ";
        cin >> immin;
        if (immin == "yes") {
            immun = true;
        } else if (immin == "no") {
            immun = false;
        } else {//illegal answer
            cout << endl <<red<< "bad input" <<reset<< endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<endl;
            return getdisease(inf, die, recov, immun);
        }
        if(!(inf>=0&&inf<=1&&die>=0&&die<=1&&recov>=0&&recov<=1)){
            //probabilities only allowed in [0,1] interval
            cout<<endl<<red<<"weights out of range."<<reset<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<endl;
            return getdisease(inf, die, recov, immun);
        }


    }

void trytoget(World& world, Disease& d, char* element){
    //attempts to get the disease provided there are infected neighbors
    bool u = *world.upneighbor(element)=='I';
    bool r = *world.rightneighbor(element)=='I';
    bool da = *world.downneighbor(element)=='I';
    bool l = *world.leftneighbor(element)=='I';
    if(*element != 'H') return;//only do this for healthy individuals

    if(u||r||da||l){
        if(randdouble()<=d.getchance()){

            world.setelement(element, 'N');
            //temporarily marked as N
            //necessary because newly infected should not influence others this loop
        }

    }else{
        return;
    }

}

void trytodie(World& world, Disease& d, char* element){
    //attempts to die for infected
    if(*element != 'I') return;
    if(randdouble()<= d.diechance()){
        world.setelement(element, 'D');
    }else{
        return;
    }
}

void trytorecov(World& world, Disease& d, char* element){
    //attempts to recover for the infected
    if(*element != 'I') return;
    if(randdouble()<= d.recovchance()){
        if(d.isimmune()){
            world.setelement(element, 'R');
        }else{
            world.setelement(element, 'H');
        }
    }else{
        return;
    }
}

void updateworld(World& world){
    //at the end of the loop, goes through and updates all N to become I
    for(char* it = world.begin(); it!=world.end(); it++){
        if(*it=='N'){
            world.setelement(it, 'I');
        }
    }
}

void gothroughaloop(World& world, Disease& d){
    //go through and attempt to get, die, and recover for all elements
    for(char* it = world.begin(); it!=world.end(); it++){
        trytoget(world, d, it);
        trytodie(world, d, it);
        trytorecov(world, d, it);

    }
    updateworld(world);

}

bool eradicated(World& world){
    //check if no infected are left, or all are infected.
    int something = 0;
    for(char* it = world.begin(); it!=world.end(); it++){
        if(*it == 'I'){
            something++;
        }
    }
    if(something == world.numofelements()) return true;
    return something==0;
}

void takeinit(World& world, Disease& d){
    //take the initial infected from the user
    int numofsites;
    cout<<"enter number of initial infected sites: ";
    cin>>numofsites;
    if(!cin.good()){
        cout << endl <<red<< "bad input" << reset<< endl;
        cout<<endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return takeinit(world, d);
    }

    cout<<"input the sites:"<<endl;
    std::vector<pair<int, int> > coords;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for(int i=0; i<numofsites;i++){
        std::string input;
        std::pair<int, int> coord;


        getline(cin, input);
        std::vector<string> inputstring = split(input);
        if(inputstring.size()!=2){
            //check that input is a valid coordinate
            cout<<red<<"bad input"<<reset<<endl;
            cout<<endl;
            return takeinit(world, d);
        }
        try{
            int i,j;
            i = stoi(inputstring[0]);
            j= stoi(inputstring[1]);
            if(!(i<world.rows()&&j<world.columns())){
                //check that the coordinates are within bounds
                cout<<red<<"out of bounds or bad input"<<reset<<endl;
                cout<<endl;
                return takeinit(world, d);
            }
            coord.first= stoi(inputstring[0]);
            coord.second = stoi(inputstring[1]);
            coords.push_back(coord);
        }catch(exception& e){
            //catch any exception stemming from wrong inputs above
            cout<<red<<"bad input"<<reset<<endl;
            cout<<endl;
        return takeinit(world, d);
        }
    }
    //load the initial infected into the world
    std::vector<pair<int, int> >::iterator ite;
    for(ite = coords.begin(); ite!=coords.end(); ite++){
        int x = ite->first, y= ite->second;
        world.setelement(world.getelementptr(x, y), 'I');
    }

}

void tofile(World& world){
    //checks if saving to a file is wanted
    cout<<reset<<"do you want to save to file (no/yes filename): "<<endl;
    string in;
    getline(cin, in);

    if(in =="no")return;
    vector<string> files = split(in);
    if(files[0] == "yes"){
        world.outputcurrenttofile(files[1]);
        cout<<blue<<"output complete."<<reset<<endl;

    }else{
        cout<<red<<"illegal input"<<reset<<endl;
        cout<<endl;
        return tofile(world);
    }
}


int main() {


    cout<<"enter number of rows, number of columns"<<endl;
    string in;
    getline(cin, in);
    int i, j;



    vector<string> vin = split(in);
    if(vin.size()!=2){
        //check for valid coordinate
        cout<<red<<"bad input"<<reset<<endl<<endl;
        return main();
    }
    i=stoi(vin[0]);
    j=stoi(vin[1]);
    if(i>35||j>70){
        //maximum rendering in terminal is 35 rows and 70 columns
        //anything above this size not allowed
        cout<<red<<"too big"<<reset<<endl;
        cout<<endl;
        return main();
    }


    World world(i, j);//create world
    double inf, die, recov;
    bool immun;
    getdisease(inf, die, recov, immun);
    Disease disease(inf, die, recov, immun);


    takeinit(world, disease);
    cout<<endl;

    world.outputcurrenttoconsole();


    while(!eradicated(world)) {

        gothroughaloop(world, disease);
        world.outputcurrenttoconsole();
    }

    tofile(world);


    return 0;
}

double randdouble(){
    return dist(mt);
}




