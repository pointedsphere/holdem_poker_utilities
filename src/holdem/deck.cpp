#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

#include "deck.h"





/*
  Building the initial deck (or the part we don't know about
*/

// Set the full decks class variables with all 52 cards in order
void deck::setDeckFull()
{
  // Do for the 4 suits
  for (int s=1; s<5; s++) {
    for (int f=2; f<15; f++) {
      deckFace.push_back(f);
      deckSuit.push_back(s);
    }
  }
};

// Set the deck index values
void deck::setDeckIndex(int maxIndex)
{
  // Do for the 4 suits
  for (int i=0; i<maxIndex; i++) {
    deckIndex.push_back(i);
  }
};


// Remove input cards from the deck
// Not remFace and remSuit must be of the same length. For cost reasons we do not
// check, though ideally we would
int deck::remCardsFromDeck(std::vector<int> remFace, std::vector<int> remSuit)
{

  /* 
     Returns:
          0 : Success!
         -1 : Card to remove from deck not actually in the deck.
  */
  
  for (int i=0; i<remFace.size(); i++) {
    for (int j=0; j<53; j++) {
      if (j==53) return -1; // overflow error
      if (remFace[i]==1) remFace[i]=14; // Check for aces
      // Now check each card in the deck against the current one to remove
      if (remFace[i]==deckFace[j] && remSuit[i]==deckSuit[j]) {
	// then delete and break to the next card to remove
	deckFace.erase(deckFace.begin()+j);
	deckSuit.erase(deckSuit.begin()+j);
	numCards=numCards-1;
	break;
      }
    }
  }

  // If we have shiffled the cards we need new index values as we could have an index
  // outside the range of where the cards now exist
  if (deckShuffled==true) setDeckIndex(numCards);
  
  return 0; // Success!
  
};



/*
  Getting things from the deck
*/

std::vector<int> deck::getDeckFace()
{
  return deckFace;
};
std::vector<int> deck::getDeckSuit()
{
  return deckSuit;
};
std::vector<int> deck::getDeckIndex()
{
  return deckIndex;
};
int deck::getNumCards()
{
  return numCards;
};
std::vector<int> deck::getDealFace()
{
  return dealFace;
};
std::vector<int> deck::getDealSuit()
{
  return dealSuit;
};


/*
  Randomising/shuffling and dealing the deck
*/

// Suffle the index array, where there is one index for each of the cards left in the deck
// so we use this to draw random cards from the deck (or what is left of it)
void deck::shuffleIndex()
{
  
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  shuffle(deckIndex.begin(), deckIndex.begin()+numCards, std::default_random_engine(seed));
  deckShuffled = true;
  
};

// Deal N cards from the deck, this is done by just pulling the last N cards from the deck
// based on the indexes in deckIndex. So if deckIndex has not been shuffled the cards will
// not be randomised
// Note: As we wish to return two sets of values (as vectors) a vector of face values and
//       a vector of relevant suit values we actually set the class based variables dealFace
//       and dealSuit, which are private and in their raw state must be accessed with the
//       get functions getDealFace and getDealSuit
int deck::dealCards(int numToDeal)
{

  // If we have previously dealt then destroy the deal vectors
  if (dealDone==true) {
    dealFace.clear();
    dealSuit.clear();
  }

  // Now deal the cards, starting from the end of the shuffled index array
  for (int i=numCards-1; i>=numCards-numToDeal; i--) {
    dealFace.push_back(deckFace[deckIndex[i]]);
    dealSuit.push_back(deckSuit[deckIndex[i]]);
  }

  // Update general and return success
  numDealt = numToDeal;
  numCards = numCards - numToDeal;
  dealDone = true;
  return 0; // Success!!
  
}







