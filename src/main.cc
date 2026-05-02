#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <functional>
#include "mixednessFuncs.hh"
#include "mixerFuncs.hh"


using namespace std;

int RANGE = 50;     //rang de nombre de vegades que executem la funció
int ATTEMPTS = 1000; //quantitat d'intents que es guarda al CSV per cada nombre de vegades que executem la funció

int main(){

    for (int cutSize = 1; cutSize < 30; cutSize++){
        ofstream outFile(string("cut_and_shuffle") + to_string(cutSize) + string(".csv")); //arxiu CSV a la carpeta "bin"
        for (int TIMES_SHUFFLED = 1; TIMES_SHUFFLED < RANGE; TIMES_SHUFFLED++){
            for (int i = 0; i < ATTEMPTS; i++){
                vector<int> deck(52);
                for (int j = 0; j < 52; j++) deck[j] = j;
                
                for(int j = 0; j < TIMES_SHUFFLED; j++){
                    cut_and_shuffle(deck, cutSize);  //aquí va la mixing function
                }
                double value = shannon_entropy(deck); //aquí va la mixedness function
                outFile << ((i!=0) ? "," : "") << value;
            }
            outFile << "\n";
        }
    }  
}
