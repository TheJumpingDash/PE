#include <algorithm>
#include <cstdlib>
#include <vector>
#include <cmath>
using namespace std;
typedef array<int,52> arr52;

double avg_dist_to_neighbour(const vector<int>& cards){
    int sum = 0;
    for(int i = 0; i < 52; i++){
        int lowDist = 0, highDist = 0, j = 0;
        bool foundLow=0, foundHigh=0;
        while((!foundLow || !foundHigh) && j < 52){
            if (cards[j] == cards[i]-1){
                foundLow = true;
                lowDist = abs(j-i);
            }
            if (cards[j] == cards[i]+1){
                foundLow = true;
                lowDist = abs(j-i);
            }
            j++;
        }

        sum += lowDist;
        sum += highDist;
        if (!foundLow) sum += highDist; //volem contar per dos als extrems perquè la mitjana de una baralla sense barrejar sigui 1
        if (!foundHigh) sum += lowDist;
    }
    return sum / 104.0;
}
double shannon_entropy(const vector<int>& cards){
    double entropy = 0.0;
    for (int i = 0; i < 51; i++){
        int currentCard = cards[i];
        int nextCard = cards[(i + 1) % 52];
        double diff = fabs(currentCard - nextCard);
        double pK = diff / 52.0;
        entropy += -pK * log(pK);
    }
    return entropy;
}
