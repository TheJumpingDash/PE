#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <functional>
#include "mixednessFuncs.hh"
#include "mixerFuncs.hh"


using namespace std;

int ATTEMPTS = 100; //number of attemps recorded onto the csv
int CUTS = 1;        //amount of times the cut/other mixing alg is applied
 

int main(){
    ofstream outFile("result.csv"); //file in bin folder
    for (int i = 0; i < ATTEMPTS; i++){
        vector<int> deck(52);
        for (int j = 0; j < 52; j++) deck[j] = j;
        
        for(int j = 0; j < CUTS; j++){
            randomize(deck);  //here goes the function that does the mixing
            for (int k = 0; k < 52; k++ ){
                cout << deck[k] << " ";
            }
            cout << endl;
        }
        double value = avg_dist_to_neighbour(deck); //here goes the mixer function
        outFile << value << "\n";
    }
}
