#include <iostream>
#include <vector>

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



// Remove input cards from the deck
// Not remFace and remSuit must be of the same length. For cost reasons we do not
// check, though ideally we would
int deck::remCardsFromDeck(std::vector<int> remFace, std::vector<int> remSuit)
{

  /* 
     Returns:
          0 : Success!
         -1 : Card to remove from deck not in deck.
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
	break;
      }
    }
  }

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
