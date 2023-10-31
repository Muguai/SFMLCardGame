#include "Header/Shuffle.hpp"
#include <stdlib.h> 
#include <time.h>
#include <Header/Card.hpp>

using namespace std;

/*  permutedIndices()
    A function that returns an array with shuffled indices.
    input: A specified size, n.
    output: A random permutation of the array {0..n-1}.
*/

int* permutedIndices(const int n) {
    // 1. Init an array: arr = {0, 1, 2..n-1}
    int* arrayIndex = new int[n];
    for (int i = 0; i < n; i++) {
        arrayIndex[i] = i;
    }

    // 2. Seed the randomization:
    srand(time(NULL));

    // 3. Fisher Yates Shuffle:
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arrayIndex[i];
        arrayIndex[i] = arrayIndex[j];
        arrayIndex[j] = temp;
    }

    return arrayIndex;
}

/*  shuffleCards
    A function that takes in a deck and returns a shuffled
    deck using the permutedIndices function above as a
    help function.
    Input: deck, an array of cards.
    Output: newDeck, the same array of cards, with permuted indices.
*/

Card* shuffleCards(Card deck[], int n) {
    int* permutation = permutedIndices(n);
    Card* newDeck = new Card[n];
    for (int i = 0; i < n; i++) {
        newDeck[i] = deck[permutation[i]];
    }

    return newDeck;
}