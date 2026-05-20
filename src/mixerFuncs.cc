#include <vector>
#include <array>
#include <random>
#include <algorithm>
#include <iterator>
using namespace std;
typedef array<int,52> arr52;
unsigned int seed = 12346;
mt19937 rng(seed); 

void get_cut_place_and_destination(const int nCardsCut, int& cutPlace, int& destination){
    uniform_int_distribution<int> cutDist(0, 52-nCardsCut);
    cutPlace = cutDist(rng);

    //evitem que el lloc on van a parar les cartes sigui massa a prop del lloc on hem tallat originalment.
    //per a això, definim un rang de +-5 cartes en què no podem reintroduir el tall. 
    //Aquest 5 és arbitrari, feel free to cambiar-ho.
    int cardBuffer = 5;
    int rangeMax = 52 - nCardsCut - (2 * cardBuffer);

    if (rangeMax <= 0){ //si el tall és massa gran, potser no hi ha llocs disponibles per posar-ho amb el buffer-> ho fem sense buffer
        uniform_int_distribution<int> simpleDist(0, 52 - nCardsCut);
        destination = simpleDist(rng);
    }else{
        uniform_int_distribution<int> destDist(0, rangeMax);
        destination = destDist(rng);
        if (destination >= cutPlace-cardBuffer) destination += 2*cardBuffer + nCardsCut; 
    }
}

void riffle_shuffle(vector<int>& cards, const double p){ //p és la probabilitat de no canviar
    std::bernoulli_distribution dist(1-p);
    arr52 input;
    for (int i = 0; i < 52; i++) input[i] = cards[i];
    bool offset = 0;
    int i1 = 0, i2 = 26;
    for (int i = 0; i < 52; i++){
        if (dist(rng)) offset = !offset;
        if (i1 >= 26) {
            offset = 1; 
        } else if (i2 >= 52) {
            offset = 0; 
        }

        if (offset){
            cards[i] = input[i2];
            i2++;
        } else{
            cards[i] = input[i1];
            i1++;
        }     
    } 
}

void cut_once(vector<int>& cards, const int nCardsCut){
    int cutPlace, destination;
    get_cut_place_and_destination(nCardsCut, cutPlace, destination);

    auto first = cards.begin() + cutPlace;
    auto last  = cards.begin() + cutPlace + nCardsCut;
    auto dest  = cards.begin() + destination;
    if (dest < first) rotate(dest, first, last);
    else if (dest > last) rotate(first, last, dest);

}

void cut_and_shuffle(vector<int>& cards, const int nCardsCut){
    int cutPlace, destination;
    get_cut_place_and_destination(nCardsCut, cutPlace, destination);

    auto first = cards.begin() + cutPlace;
    auto last  = cards.begin() + cutPlace + nCardsCut;
    //creem un vector amb els elements a inserir:
    vector<int> cutVector(make_move_iterator(first), make_move_iterator(last)); 
    cards.erase(first, last);

    int offset = (cutPlace < destination) ? -nCardsCut : 0;
    int index = destination + offset;

    int cardsAfterDest = cards.size() - index;
    int split = min(nCardsCut, cardsAfterDest);

    for(int i = 0; i < nCardsCut; i++){
        cards.insert(cards.begin() + index, cutVector[i]);
        index += (i < split ? 2 : 1);
    }
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
