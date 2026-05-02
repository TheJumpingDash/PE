#ifndef MIXERFUNCS_H
#define MIXERFUNCS_H
#include <vector>
using namespace std;

//i aquestes funcions barrejen el deck 1 cop
void cut_once(vector<int>& cards, const int nCardsCut);
void cut_and_shuffle(vector<int>& cards, const int nCardsCut);
void randomize(vector<int>& cards);
//...


#endif