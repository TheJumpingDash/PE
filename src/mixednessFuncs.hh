#ifndef MIXEDNESSFUNCS_H
#define MIXEDNESSFUNCS_H

#include <vector>
using namespace std;

//aquestes funcions diuen com de ben barrejar està el deck

double avg_dist_to_neighbour(const vector<int>& cards); 
double shannon_entropy(const vector<int>& cards);

#endif