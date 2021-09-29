
#ifndef DECK_H_
#define DECK_H_

#include <algorithm>
#include <random>
#include <vector>


class deck
{

private:

  // Master deck variables
  bool deckSet_;
  std::vector<int> deckFace_;
  std::vector<int> deckSuit_;

  // The index array, used for dealing/shuffling cards
  bool indexSet_;
  std::vector<int> deckIndex_;

  // To keep track of the deck
  int numCards_;
  bool deckShuffled_;
  
public:

  // Constructor
  deck() {
    
    // We start with 52 cards
    numCards_ = 52;
    deckSet_ = false;
    
    // Set the array of indexes of the deck, for use with shuffling
    indexSet_ = false;
    setDeckIndex(52);

    // Not yet shuffled
    deckShuffled_ = false;

    // Not yeat dealt
    dealDone_ = false;
    numDealt_ = 0;
    
  }
  
  // Populate fullDeckFace and fullDeckSuit with all 52 cards
  void setDeckFull();

  // Populate the deck, but without the cards given as input
  int setDeckPartial(std::vector<int> igFace, std::vector<int> igSuit);
  
  // Set the deck indexes
  void setDeckIndex(int maxIndex);
  
  // Remove some input cards from the deck
  int remCards(std::vector<int> remFace, std::vector<int> remSuit);
  int remCard(int remFace, int remSuit);

  // Shuffle the indexes of the known cards
  void shuffleI();

  // Deal cards to dealFace_ and dealSuit_. Note: This destroys the vectors if they
  // have previously been set
  int dealCards(int numToDeal);
  void remDealtCards();

  // Class values for dealing the cards
  bool dealDone_;
  int  numDealt_;
  std::vector<int> dealFace_;
  std::vector<int> dealSuit_;
  
  // C++ get functions
  bool getDeckSet();
  bool getDeckShuffled();
  std::vector<int> getDeckFace();
  std::vector<int> getDeckSuit();
  std::vector<int> getDeckIndex();
  int getNumCards();
  std::vector<int> getDealFace();
  std::vector<int> getDealSuit();
  
};

#endif
