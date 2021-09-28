
#ifndef DECK_H_
#define DECK_H_

#include <algorithm>
#include <random>
#include <vector>


class deck
{

private:

  std::vector<int> deckFace;
  std::vector<int> deckSuit;

  std::vector<int> deckIndex;

  int numCards;
  
public:

  // Constructor
  deck() {
    
    // We start with 52 cards
    numCards = 52;
    
    // Set the array of indexes of the deck, for use with shuffling
    setDeckIndex(52);

  }
  
  // Populate fullDeckFace and fullDeckSuit with all 52 cards
  void setDeckFull();

  // Set the deck indexes
  void setDeckIndex(int maxIndex);
  
  // Remove some input cards from the deck
  int remCardsFromDeck(std::vector<int> remFace, std::vector<int> remSuit);

  // Shuffle the indexes of the known cards
  void shuffleIndex();
  
  // C++ get functions
  std::vector<int> getDeckFace();
  std::vector<int> getDeckSuit();
  std::vector<int> getDeckIndex();
  int getNumCards();
  
};

#endif
