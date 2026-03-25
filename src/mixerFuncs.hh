#ifndef MIXERFUNCS_H
#define MIXERFUNCS_H
#include <array>
using namespace std;
typedef array<int,52> arr52;

//i aquestes funcions barrejen el deck 1 cop
void cut_once(arr52& cards, const int nCardsCut);
void in_between_shuffle(arr52& cards, const int nCardsCut);
//...


#endif