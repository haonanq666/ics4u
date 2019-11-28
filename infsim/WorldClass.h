

#ifndef INFSIM_WORLDCLASS_H
#define INFSIM_WORLDCLASS_H

#include <fstream>
#include <chrono>
#include <thread>

//the ANSI escape sequences for different colored text
const std::string reset =  "\033[0m";
const std::string red = "\033[31m";
const std::string green = "\033[32m";
const std::string blue = "\033[34m";

class World {
public:
    World(int rows, int columns);

    ~World(){//destructor, simply free up the memory.
        delete[] worldsave;
    }

    void outputcurrenttofile(std::string filename){
        //outputs the contents of simulation to a txt file
        std::string filepath = "output/";
        std::string fullpath = filepath + filename + ".txt";

        std::ofstream outfile(fullpath);
        for(int i = 0; i<numofrows; i++){
            for(int k=0; k<numofcolumns; k++) {



                outfile <<  *(worldsave + i*numofcolumns+k) << " ";

            }
            outfile<<std::endl;

        }

    }

    void outputcurrenttoconsole(){
        for(int l=0; l<35; l++){
            std::cout<<std::endl;
        }
        //newlines added to flush the terminal display

        for(int i = 0; i<numofrows; i++){
            for(int k=0; k<numofcolumns; k++) {
                std::string thing;
                //depending on the letter, different color used for better viewing
                if (*(worldsave + i*numofcolumns +k) == 'H') {
                    thing = reset;
                } else if (*(worldsave + i*numofcolumns +k) == 'I') {
                    thing = green;
                } else if (*(worldsave + i*numofcolumns +k) == 'D') {
                    thing = red;
                } else if (*(worldsave + i*numofcolumns +k) == 'R') {
                    thing = blue;
                }


                std::cout << thing << *(worldsave + i*numofcolumns+k) << " ";

            }
            std::cout<<std::endl;

        }
        //delays the program for one second so that the current frame gets to be rendered
        //and fully seen by the user
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));


    }
    char* getelementptr(int i, int j) {
        // 1 2 3
        // 4 5 6
        // 7 8 9
        //returns a pointer given an index

        char* p = (worldsave + i * numofrows + j);

        return p;
    }

    void setelement(char* element, char newchar){
        //assigns value to element
        *element = newchar;
    }
    int rows(){
        return numofrows;
    }
    int columns(){
        return numofcolumns;
    }

//    1 2 3 4
//    5 6 7 8
//    9 0 1 2

    //when checking for neighbors the border elements were considered specially
    //since they lack one or many neighbors.
    char* upneighbor(char* element){
        char* n = element - numofcolumns;
        if(n>=worldsave&&n<worldsave+numofcolumns*numofrows)return n;
        else return obchar;
    }
    char* downneighbor(char* element){
        char* n = element + numofcolumns;
        if(n>=worldsave&&n<worldsave+numofcolumns*numofrows)return n;
        else return obchar;
    }
    char* leftneighbor(char* element){
        char* n = element -1;
        if((n-worldsave+1)%numofcolumns==0)return obchar;
        else if(n>=worldsave&&n<worldsave+numofcolumns*numofrows)return n;
        else return obchar;
    }
    char* rightneighbor(char* element){
        char* n = element +1;
        if((n-worldsave)%numofcolumns==0)return obchar;
        else if(n>=worldsave&&n<worldsave+numofcolumns*numofrows)return n;
        else return obchar;
    }
    int numofelements(){
        return numofcolumns*numofrows;
    }

    char* begin(){
        //first memory location
        return worldsave;
    }
    char* end(){
        //last memory location (arrays are contiguous)
        return (worldsave+numofrows*numofcolumns);
    }

private:
    char* worldsave;
    char* obchar;
    int numofrows;
    int numofcolumns;


};

World::World(int rows, int columns){
    //constructor that sets up the initial world circumstances
    numofrows = rows;
    numofcolumns = columns;
    worldsave = new char[rows*columns];
    obchar = new char('O');
    for(int i = 0; i<rows*columns; i++){
        *(worldsave+i) = 'H';

    }
}



#endif //INFSIM_WORLDCLASS_H
