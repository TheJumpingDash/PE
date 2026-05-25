#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <functional>
#include <sstream>    
#include "mixednessFuncs.hh"
#include "mixerFuncs.hh"

using namespace std;

// VERSIÓ AMB CUT SHUFFLE

int RANGE = 30;     //rang de nombre de vegades que executem la funció
int ATTEMPTS = 1000; //quantitat d'intents que es guarda al CSV per cada nombre de vegades que executem la funció
double CUT_SIZE = 0.95; //nombre d'arxius generats, un per cada tamany de tall
int main(){

    for (double prob = 0.05; prob < CUT_SIZE; prob+= 0.05){
        
        stringstream ss;
        ss << prob;
        string filename = string("riffle_shannon_") + ss.str() + string(".csv");
        
        ofstream outFile(filename); //arxiu CSV a la carpeta "bin"
        for (int TIMES_SHUFFLED = 1; TIMES_SHUFFLED < RANGE; TIMES_SHUFFLED++){
            for (int i = 0; i < ATTEMPTS; i++){
                vector<int> deck(52);
                for (int j = 0; j < 52; j++) deck[j] = j;
                
                for(int j = 0; j < TIMES_SHUFFLED; j++){
                    riffle_shuffle(deck, prob);  //aquí va la mixing function
                }
                double value = shannon_entropy(deck); //aquí va la mixedness function
                outFile << ((i!=0) ? "," : "") << value;
            }
            outFile << "\n";
        }
    }

}

// VERSIÓ AMB RIFFLE SHUFFLE

// int RANGE = 100;       // rang de nombre de vegades que executem la funció
// int ATTEMPTS = 1000;  // quantitat d'intents que es guarda al CSV per cada nombre de vegades que executem la funció

// int main() {

//     for (int cut_size = 1; cut_size < 31; cut_size++) {

//         stringstream ss;
//         ss << cut_size;
//         string filename = string("cut_once_shannon_") + ss.str() + string(".csv");

//         ofstream outFile(filename);

//         for (int TIMES_SHUFFLED = 1; TIMES_SHUFFLED < RANGE; TIMES_SHUFFLED++) {
//             for (int i = 0; i < ATTEMPTS; i++) {

//                 vector<int> deck(52);
//                 for (int j = 0; j < 52; j++) deck[j] = j;

//                 for (int j = 0; j < TIMES_SHUFFLED; j++) {
//                     cut_once(deck, cut_size); // deck is passed as parameter
//                 }

//                 double value = shannon_entropy(deck);
//                 outFile << ((i != 0) ? "," : "") << value;
//             }
//             outFile << "\n";
//         }
//     }

//     return 0;
// }