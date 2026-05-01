#include <vector>
#include <random>
#include <algorithm>
using namespace std;
typedef array<int,52> arr52;
unsigned int seed = 12346;
mt19937 rng(seed); 

void cut_once(vector<int>& cards, const int nCardsCut){

    uniform_int_distribution<int> cutDist(0, 52-nCardsCut);
    int placeOfCut = cutDist(rng);
    int cutDestination;

    //evitem que el lloc on van a parar les cartes sigui massa a prop del lloc on hem tallat originalment.
    //per a això, definim un rang de +-5 cartes en què no podem reintroduir el tall. 
    //Aquest 5 és arbitrari, feel free to cambiar-ho.
    int cardBuffer = 5;
    int rangeMax = 52 - nCardsCut - (2 * cardBuffer);

    if (rangeMax <= 0){ //si el tall és massa gran, potser no hi ha llocs disponibles per posar-ho amb el buffer-> ho fem sense buffer
        std::uniform_int_distribution<int> simpleDist(0, 52 - nCardsCut);
        cutDestination = simpleDist(rng);
    }else{
        std::uniform_int_distribution<int> destDist(0, rangeMax);
        cutDestination = destDist(rng);
        if (cutDestination >= placeOfCut-cardBuffer) cutDestination += 2*cardBuffer; 
    }

    

    auto first = cards.begin() + placeOfCut;
    auto last  = cards.begin() + placeOfCut + nCardsCut;
    auto dest  = cards.begin() + cutDestination;
    if (dest < first) rotate(dest, first, last);
    else if (dest > last) rotate(first, last, dest);

}

void randomize(vector<int>& cards){
    vector<int> result(52);
    iota(result.begin(), result.end(), 0);
    for(int i = 0; i < 52; i++){
        uniform_int_distribution<int> card(0,51-i);
        int rndCard = card(rng);
        cards[i] = result[rndCard];
        result.erase(result.begin() + rndCard);
    }
}
