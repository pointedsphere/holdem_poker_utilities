#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

#include "deck.h"





/*
  Building the initial deck (or the part we don't know about
*/

void deck::setDeckFull()
{

  /*
    Populate the class arrays deckFace and deckSuit with the face and suit values of all 52
    cards in a deck.
   */

  // Check if the deck has been set, if it has discard the old deck before populating
  if (deckSet==true) deckIndex.clear();
  
  // Do for the 4 suits
  for (int s=1; s<5; s++) {
    // Do for each card in the current suit
    for (int f=2; f<15; f++) {
      // Add all the cards
      deckFace.push_back(f);
      deckSuit.push_back(s);
    }
  }
  
  deckSet = true;
  
};

int deck::setDeckPartial(std::vector<int> igFace, std::vector<int> igSuit)
{

  /*
    Populate the class arrays deckFace and deckSuit with the face and suit values of all 52
    cards in a deck, ignoring any cards given in the igFace and igSuit inputs.

    NOTE: This routine does have error checks and converts face value 1=>14 as it is assumed 
          it will not be called often.
    
    Inputs:
        igFace :: Vector continaing face values of the cards not to add to deck.
        igSuit :: Vector continaing suit values of the cards not to add to deck.

    Returns:
         0 :: Success!
        -1 :: The face and suit input arrays are of different sizes
   */

  // Check if the deck has been set, if it has discard the old deck before populating
  if (deckSet==true) deckIndex.clear();
  
  // Check that the input arrays are the same size
  if (igFace.size()!=igSuit.size()) {
    return -1; // Return error
  }

  // Change igFace values from 1 => 14, just incase input is given with ace value as 1
  for (int i=0; i<igFace.size(); i++) {
    if (igFace[i]==1) igFace[i]=14;
  }
  
  // Do for the 4 suits
  for (int s=1; s<5; s++) {
    // Do for each card in the current suit
    for (int f=2; f<15; f++) {
      // Check each of the ignore vector elements to see if the current card to be added should
      // be ignored or not
      for (int i=0; i<igFace.size(); i++) {
	if (igFace[i]==f && igSuit[i]==s) {
	  numCards--;
	  break;
	} else if (i==igFace.size()-1) {
	  deckFace.push_back(f);
	  deckSuit.push_back(s);
	  break;
	}
      }
    }
  }

  deckSet = true;
  return 0; // Success
  
};

// Set the deck index values
void deck::setDeckIndex(int maxIndex)
{

  /*
    Set the index array, which is initially an array of integers from 0 to maxIndex-1
    If it is already set then destroy the data in it and start again.

    Inputs:
        maxIndex :: The number of elements that will be created in deckIndex from 0
	            to maxIndex-1.
  */
  
  // If the index array is already set, discard all data in it
  if (indexSet==true) deckIndex.clear();
  
  // Now populate all the index values in ascending order
  for (int i=0; i<maxIndex; i++) {
    deckIndex.push_back(i);
  }
  
  indexSet = true;
  
};



int deck::remCards(std::vector<int> remFace, std::vector<int> remSuit)
{

  /* 
     Remove the cards given in remFace and remSuit from the current deck.

     NOTE: No error checks are carried out as this routine may need to be called multiple times,
           so remFace and remSuit MUST be of the same size. Also deckFace and deckSuit MUST have
	   been set prior to calling this function.

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

bool deck::getDeckSet()
{
  return deckSet;
};
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
void deck::shuffleI()
{

  /*
    Suffle the index array, where there is one index for each of the cards left in the deck
    so we use this to draw random cards from the deck (or what is left of it).

    NOTE: This routine may need to be called many times, so no error checks are carried out
          here.
  */
  
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  shuffle(deckIndex.begin(), deckIndex.begin()+numCards, std::default_random_engine(seed));
  deckShuffled = true;
  
};


int deck::dealCards(int numToDeal)
{

  /*

    Deal N cards from the deck, this is done by just pulling the last N cards from the deck
    based on the indexes in deckIndex. So if deckIndex has not been shuffled the cards will
    not be randomised.

    NOTE: If numCards is incorrectly set, or the shuffle was done when numCards is larger 
          than it currently is this routine may deal cards that are no longer in the deck.
	  This could be avoided with an error check, however this would increace the cost
	  of this routine.

    NOTE: As we wish to return two sets of values (as vectors) a vector of face values and
          a vector of relevant suit values we actually set the class based variables dealFace
	  and dealSuit, which are private and in their raw state must be accessed with the
	  get functions getDealFace and getDealSuit

    RETURNS:
    --------
        0  :: Success
	-1 :: Number of cards requested from deal greater than number of cards left in deck

   */
  
  // If we have previously dealt then destroy the deal vectors
  if (dealDone==true) {
    dealFace.clear();
    dealSuit.clear();
  }

  // If the number of cards asked to deal is more than that left in deck return with an error
  if (numCards<numToDeal) return -1;
  
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







