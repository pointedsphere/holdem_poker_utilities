#include <iostream>
#include <stdlib.h>
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
    Populate the class arrays deckFace_ and deckSuit_ with the face and suit values of all 52
    cards in a deck.
   */

  // Check if the deck has been set, if it has discard the old deck before populating
  if (deckSet_==true) deckIndex_.clear();
  if (deckSet_==true) deckFace_.clear();
  if (deckSet_==true) deckSuit_.clear();
  if (deckSet_==true) deckFaceP_.clear();
  if (deckSet_==true) deckSuitP_.clear();
  if (deckSet_==true) deckFullP_.clear();
  
  // Do for the 4 suits
  for (int s=1; s<5; s++) {
    // Do for each card in the current suit
    for (int f=2; f<15; f++) {
      // Add all the cards
      deckFace_.push_back(f);
      deckSuit_.push_back(s);
    }
  }

  // Now explicitly set the prime versions of the deck
  deckFullP_.push_back(2);
  deckFullP_.push_back(3);
  deckFullP_.push_back(5);
  deckFullP_.push_back(7);
  deckFullP_.push_back(11);
  deckFullP_.push_back(13);
  deckFullP_.push_back(17);
  deckFullP_.push_back(19);
  deckFullP_.push_back(23);
  deckFullP_.push_back(29);
  deckFullP_.push_back(31);
  deckFullP_.push_back(37);
  deckFullP_.push_back(41);
  deckFullP_.push_back(43);
  deckFullP_.push_back(47);
  deckFullP_.push_back(53);
  deckFullP_.push_back(59);
  deckFullP_.push_back(61);
  deckFullP_.push_back(67);
  deckFullP_.push_back(71);
  deckFullP_.push_back(73);
  deckFullP_.push_back(79);
  deckFullP_.push_back(83);
  deckFullP_.push_back(89);
  deckFullP_.push_back(97);
  deckFullP_.push_back(101);
  deckFullP_.push_back(103);
  deckFullP_.push_back(107);
  deckFullP_.push_back(109);
  deckFullP_.push_back(113);
  deckFullP_.push_back(127);
  deckFullP_.push_back(131);
  deckFullP_.push_back(137);
  deckFullP_.push_back(139);
  deckFullP_.push_back(149);
  deckFullP_.push_back(151);
  deckFullP_.push_back(157);
  deckFullP_.push_back(163);
  deckFullP_.push_back(167);
  deckFullP_.push_back(173);
  deckFullP_.push_back(179);
  deckFullP_.push_back(181);
  deckFullP_.push_back(191);
  deckFullP_.push_back(193);
  deckFullP_.push_back(197);
  deckFullP_.push_back(199);
  deckFullP_.push_back(211);
  deckFullP_.push_back(223);
  deckFullP_.push_back(227);
  deckFullP_.push_back(229);
  deckFullP_.push_back(233);
  deckFullP_.push_back(239);
  
  // Now set the prime deck face and suit values based on the first 13 and 4 prime numbers respectivley
  for (int i=0; i<4; i++) {
    for (int j=0; j<13; j++) {
      deckFaceP_.push_back(deckFullP_[j]);
      deckSuitP_.push_back(deckFullP_[i]);
    }
  }
  
  // Set number of cards to 52 for the full deck
  numCards_     = 52;
  indexSet_     = false;
  setDeckIndex(52);
  deckShuffled_ = false;
  dealDone_     = false;
  numDealt_     = 0;

  // And now the deck is set
  deckSet_ = true;
  
}



int deck::setDeckPartial(std::vector<int> igFace, std::vector<int> igSuit)
{

  /*
    Populate the class arrays deckFace_ and deckSuit_ with the face and suit values of all 52
    cards in a deck, ignoring any cards given in the igFace and igSuit inputs.

    NOTE: This routine does have error checks and converts face value 1=>14 as it is assumed 
          it will not be called often.
    
    Inputs:
        igFace :: Vector continaing face values of the cards not to add to deck.
        igSuit :: Vector continaing suit values of the cards not to add to deck.

    Returns:
         0 :: Success!
        -1 :: The face and suit input arrays are of different sizes
	-2 :: There would be less than 0 cards left in the deck after removing these cards
   */

  int deckPartialSize;
  
  // Check that the input arrays are the same size
  if (igFace.size()!=igSuit.size()) {
    return -1; // Return error
  }

  // Check that some cards will be left in the deck
  if (igFace.size()>52) {
    return -2; // Return error
  }
  
  // Change igFace values from 1 => 14, just incase input is given with ace value as 1
  deckPartialSize=igFace.size();
  for (int i=0; i<deckPartialSize; i++) {
    if (igFace[i]==1) igFace[i]=14;
  }

  // Create a full deck
  setDeckFull();
  
  remCards(igFace, igSuit);

  return 0; // Success
  
}



void deck::setDeckIndex(int maxIndex)
{

  /*
    Set the index array, which is initially an array of integers from 0 to maxIndex-1
    If it is already set then destroy the data in it and start again.

    Inputs:
        maxIndex :: The number of elements that will be created in deckIndex_ from 0
	            to maxIndex-1.
  */
  
  // If the index array is already set, discard all data in it
  if (indexSet_==true) deckIndex_.clear();
  
  // Now populate all the index values in ascending order
  for (int i=0; i<maxIndex; i++) {
    deckIndex_.push_back(i);
  }

  deckShuffled_ = false; // No longer got the shuffled indexes
  indexSet_     = true;  // The indes is however now set
  
}



int deck::remCards(std::vector<int> remFace, std::vector<int> remSuit)
{

  /* 
     Remove the cards given in remFace and remSuit from the current deck.

     NOTE: No error checks are carried out as this routine may need to be called multiple times,
           so remFace and remSuit MUST be of the same size. Also deckFace_ and deckSuit_ MUST have
	   been set prior to calling this function.

     Returns:
          0 : Success!
  */

  int remFaceSize=remFace.size();
  int faceToRem;
  int suitToRem;
  for (int i=0; i<remFaceSize; i++) {

    // Set the face and suit values to integers to allow for ace checking and less lookups
    faceToRem = remFace[i];
    if (faceToRem==1) faceToRem=14;
    suitToRem = remSuit[i];
    
    for (int j=0; j<53; j++) {

      if (j==53) {
	// Exit everything with an error if a card not in the deck is requested for removal
	std::cout << "ERROR : remCard requested to remove card not in deck with face value "
		  << faceToRem << " and suit value " << suitToRem << "." << std::endl;;
	exit (EXIT_FAILURE);
      }
      
      // Now check each card in the deck against the current one to remove
      if (faceToRem==deckFace_[j] && suitToRem==deckSuit_[j]) {
	// then delete and break to the next card to remove
	deckFace_.erase(deckFace_.begin()+j);
	deckSuit_.erase(deckSuit_.begin()+j);
	// Also delete from the prime representations
	deckFaceP_.erase(deckFaceP_.begin()+j);	
	deckSuitP_.erase(deckSuitP_.begin()+j);
	deckFullP_.erase(deckFullP_.begin()+j);
	numCards_=numCards_-1;
	break;
      }
    }
  }

  // If we have shuffled the cards we need new index values as we could have an index
  // outside the range of where the cards now exist
  if (deckShuffled_==true) setDeckIndex(numCards_);
  
  return 0; // Success!
  
}



int deck::remCard(int remFace, int remSuit)
{

  /* 
     Remove the card given in remFace and remSuit from the current deck.

     NOTE: No error checks are carried out as this routine may need to be called multiple times,
           so remFace and remSuit MUST be of the same size. Also deckFace_ and deckSuit_ MUST have
	   been set prior to calling this function.

     Returns:
          0 : Success!
         -1 : Card to remove from deck not actually in the deck.
  */
  
  for (int j=0; j<53; j++) {
    if (j==53) return -1; // overflow error
    if (remFace==1) remFace=14; // Check for aces
    // Now check each card in the deck against the current one to remove
    if (remFace==deckFace_[j] && remSuit==deckSuit_[j]) {
      // then delete and break to the next card to remove
      deckFace_.erase(deckFace_.begin()+j);
      deckSuit_.erase(deckSuit_.begin()+j);
      // Also delete from the prime representations
      deckFaceP_.erase(deckFaceP_.begin()+j);	
      deckSuitP_.erase(deckSuitP_.begin()+j);
      deckFullP_.erase(deckFullP_.begin()+j);
      numCards_=numCards_-1;
      break;
    }
  }

  // If we have shuffled the cards we need new index values as we could have an index
  // outside the range of where the cards now exist
  if (deckShuffled_==true) setDeckIndex(numCards_);
  
  return 0; // Success!
  
}



void deck::itNumCardsInDeck(int deckIter)
{

  /*
    Iterate the number of cards in the deck based on input number.

    This is used during resets of a table, to essentially put cards dealt out back into the deck.
  */

  numCards_+=deckIter;
  
}




/*
  Getting things from the deck
*/

bool deck::getDeckSet()
{
  return deckSet_;
}
bool deck::getDeckShuffled()
{
  return deckShuffled_;
}
std::vector<int> deck::getDeckFace()
{
  return deckFace_;
}
std::vector<int> deck::getDeckSuit()
{
  return deckSuit_;
}
std::vector<int> deck::getDeckIndex()
{
  return deckIndex_;
}
int deck::getNumCards()
{
  return numCards_;
}
std::vector<int> deck::getDealFace()
{
  return dealFace_;
}
std::vector<int> deck::getDealSuit()
{
  return dealSuit_;
}



/*
  Randomising/shuffling and dealing the deck
*/



void deck::shuffleI()
{

  /*
    Suffle the index array, where there is one index for each of the cards left in the deck
    so we use this to draw random cards from the deck (or what is left of it).

    NOTE: This routine may need to be called many times, so no error checks are carried out
          here.
  */
  
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  shuffle(deckIndex_.begin(), deckIndex_.end(), std::default_random_engine(seed));
  deckShuffled_ = true;
  
}



int deck::dealCards(int numToDeal)
{

  /*

    Deal N cards from the deck, this is done by just pulling the last N cards from the deck
    based on the indexes in deckIndex_. So if deckIndex_ has not been shuffled the cards will
    not be randomised.

    NOTE: If numCards_ is incorrectly set, or the shuffle was done when numCards_ is larger 
          than it currently is this routine may deal cards that are no longer in the deck.
	  This could be avoided with an error check, however this would increace the cost
	  of this routine.

    NOTE: As we wish to return two sets of values (as vectors) a vector of face values and
          a vector of relevant suit values we actually set the class based variables dealFace_
	  and dealSuit_, which are private and in their raw state must be accessed with the
	  get functions getDealFace and getDealSuit

    RETURNS:
    --------
        0  :: Success
	-1 :: Number of cards requested from deal greater than number of cards left in deck

   */
  
  // If we have previously dealt then destroy the deal vectors
  if (dealDone_==true) {
    dealFace_.clear();
    dealSuit_.clear();
    dealFaceP_.clear();
    dealSuitP_.clear();
    dealFullP_.clear();
  }

  // If the number of cards asked to deal is more than that left in deck return with an error
  if (numCards_<numToDeal) {
    std::cout << "ERROR : Number of cards to deal using dealCards more than the cards left in the deck.";
    exit (EXIT_FAILURE);
  }

  
  // Now deal the cards, starting from the end of the shuffled index array
  for (int i=numCards_-1; i>=numCards_-numToDeal; i--) {
    dealFace_.push_back(deckFace_[deckIndex_[i]]);
    dealSuit_.push_back(deckSuit_[deckIndex_[i]]);
    dealFaceP_.push_back(deckFaceP_[deckIndex_[i]]);
    dealSuitP_.push_back(deckSuitP_[deckIndex_[i]]);
    dealFullP_.push_back(deckFullP_[deckIndex_[i]]);
  }

  // Update general and return success
  numDealt_ = numToDeal;
  numCards_ = numCards_ - numToDeal;
  dealDone_ = true;
  return 0; // Success!!
  
}

 

void deck::remDealtCards()
{

  /*

    Remove the dealt cards from the deck array of cards, this will generally not need to be done
    as we will generally deal out all the cards then discard the deck, but it's here just in case

   */
  
  remCards(dealFace_,dealSuit_);
  numCards_=numCards_-dealSuit_.size();
  
}

// Standard face values
int cardFace[52] = {2,3,4,5,6,7,8,9,10,11,12,13,14,2,3,4,5,6,7,8,9,10,11,12,13,14,\
  2,3,4,5,6,7,8,9,10,11,12,13,14,2,3,4,5,6,7,8,9,10,11,12,13,14};

// Standard suit values
int cardSuit[52] = {\
  1,1,1,1,1,1,1,1,1,1,1,1,1,\
  2,2,2,2,2,2,2,2,2,2,2,2,2,\
  3,3,3,3,3,3,3,3,3,3,3,3,3,\
  4,4,4,4,4,4,4,4,4,4,4,4,4};

// Prime suit values
int primeSuit[52] = { \
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, \
  3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, \
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, \
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7 };

// Prime face values
int primeFace[52] = { \
  2,3,5,7,11,13,17,19,23,29,31,37,41,	\
  2,3,5,7,11,13,17,19,23,29,31,37,41,	\
  2,3,5,7,11,13,17,19,23,29,31,37,41,	\
  2,3,5,7,11,13,17,19,23,29,31,37,41 };

// Lowest 52 primes
int primes[52] = { \
  2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,	\
  109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227, \
  229,233,239 };

std::vector<int> card2prime(int inFace,int inSuit)
{

  /*
    
    Convert the input face and suit values of a card from the standard face and suit values to the
    prime values for face, suit and card.

    RETURNS
    =======
    Vector of length 3, where indexes correspond to:
      0 :: The prime value of the face of the card.
      1 :: The prime value of the suit of the card.
      2 :: The full prime value of the card.

   */
  
  std::vector<int> primed;
  int primI=0;

  // Find the index corresponding to the current card
  for (int jk=0; jk<52; jk++) {
    if (cardFace[jk]==inFace && cardSuit[jk]==inSuit) {
      primI = jk;
      break;
    }
  }

  // Now set the prime based on this value from the full deck

  std::cout << primI << std::endl;
  
  primed.push_back(primeFace[primI]);
  primed.push_back(primeSuit[primI]);
  primed.push_back(primes[primI]);

  return primed;
  
}




