#include <string>
#include <fstream>
#include <functional>
#include <array>
#include "mixednessFuncs.hh"
#include "mixerFuncs.hh"


using namespace std;
typedef array<int,52> arr52;

int ATTEMPTS = 1000; //number of attemps recorded onto the csv
int CUTS = 5;        //this is the amount of times the cut/other mixing alg is applied
 

int main(){
    ofstream outFile("result.csv");
    for (int i = 0; i < ATTEMPTS; i++){
        arr52 deck;
        for (int j = 0; j < 52; j++) deck[j] = j;
        
        for(int j = 0; j < CUTS; j++){
            cut_once(deck,7);  //here goes the function that does the mixing
        }
        double value = avg_dist_to_neighbour(deck); //here goes the mixer function
        outFile << value << "\n";
    }
}
