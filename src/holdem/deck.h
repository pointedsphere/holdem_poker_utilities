
#ifndef DECK_H_
#define DECK_H_

#include <vector>

class deck
{

private:

  std::vector<int> deckFace;
  std::vector<int> deckSuit;
  
public:

  // Constructor
  deck() {

  }

  // Populate fullDeckFace and fullDeckSuit with all 52 cards
  void setDeckFull();

  // Remove some input cards from the deck
  int remCardsFromDeck(std::vector<int> remFace, std::vector<int> remSuit);
  
  // C++ get functions
  std::vector<int> getDeckFace();
  std::vector<int> getDeckSuit();
  
};

#endif
