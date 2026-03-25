#ifndef MIXEDNESSFUNCS_H
#define MIXEDNESSFUNCS_H

#include <array>
using namespace std;
typedef array<int,52> arr52;

//aquestes funcions diuen com de ben barrejar està el deck

double avg_dist_to_neighbour(const arr52& cards); 
double cards_higher_than_they_should(const arr52& cards);
double emmas_epic_fitness_score(const arr52& cards);



#endif