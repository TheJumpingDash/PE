#ifndef MIXEDNESSFUNCS_H
#define MIXEDNESSFUNCS_H

#include <vector>
using namespace std;

//aquestes funcions diuen com de ben barrejar està el deck

double avg_dist_to_neighbour(const vector<int>& cards); 
double cards_higher_than_they_should(const vector<int>& cards);
double emmas_epic_fitness_score(const vector<int>& cards);



#endif