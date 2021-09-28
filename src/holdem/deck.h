
#ifndef DECK_H_
#define DECK_H_

#include <algorithm>
#include <random>
#include <vector>


class deck
{

private:

  bool deckSet;
  std::vector<int> deckFace;
  std::vector<int> deckSuit;
  bool indexSet;
  std::vector<int> deckIndex;

  int numCards;

  bool deckShuffled;


  bool dealDone;
  int  numDealt;
  std::vector<int> dealFace;
  std::vector<int> dealSuit;
  
public:

  // Constructor
  deck() {
    
    // We start with 52 cards
    numCards = 52;
    deckSet = false;
    
    // Set the array of indexes of the deck, for use with shuffling
    indexSet = false;
    setDeckIndex(52);

    // Not yet shuffled
    deckShuffled = false;

    // Not yeat dealt
    dealDone = false;
    numDealt = 0;
    
  }
  
  // Populate fullDeckFace and fullDeckSuit with all 52 cards
  void setDeckFull();

  // Populate the deck, but without the cards given as input
  int setDeckPartial(std::vector<int> igFace, std::vector<int> igSuit);
  
  // Set the deck indexes
  void setDeckIndex(int maxIndex);
  
  // Remove some input cards from the deck
  int remCards(std::vector<int> remFace, std::vector<int> remSuit);

  // Shuffle the indexes of the known cards
  void shuffleI();

  // Deal cards to dealFace and dealSuit. Note: This destroys the vectors if they
  // have previously been set
  int dealCards(int numToDeal);
  
  // C++ get functions
  bool getDeckSet();
  std::vector<int> getDeckFace();
  std::vector<int> getDeckSuit();
  std::vector<int> getDeckIndex();
  int getNumCards();
  std::vector<int> getDealFace();
  std::vector<int> getDealSuit();
  
};

#endif
