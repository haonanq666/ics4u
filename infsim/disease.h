

#ifndef INFSIM_DISEASE_H
#define INFSIM_DISEASE_H

class Disease{
public:
    Disease(double get, double die, double recov, bool immun);
    double getchance(){
        return chancetoget;
    }

    double diechance(){
        return chancetodie;
    }

    double recovchance(){
        return chancetorecover;
    }
    bool isimmune(){
        //determines whether or not recovering from this disease makes one
        //immune to it in the future.
        return immunity;
    }


private:

    double chancetoget;
    double chancetodie;
    double chancetorecover;
    bool immunity;


};

Disease::Disease(double get, double die, double recov, bool immun) {
    chancetodie = die; //mortality rate of disease
    chancetoget = get; //probaility of tracing it.
    chancetorecover = recov;
    immunity = immun;
}

#endif //INFSIM_DISEASE_H
