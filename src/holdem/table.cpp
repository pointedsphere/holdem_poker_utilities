#include <iostream>
#include <vector>

#include "table.h"
#include "hand.h"



/*
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                      PLAYER CLASS
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/






/*
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                     TABLE CLASS
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/

/*
  Iitialise values/players
*/

int table::setNoPlayers(int noP)
{

  /*
    
    Set the number of players and initialise the array of hands class objects.

    Note: If the number of players has already been set then all this data will be destroyed
          then re-initialised.

    RETURNS
    =======
    Returns an integer error/status code
        0  :: Success!!
	-1 :: noP not in [2,12].

   */
  
  // There must be at least 2, and less than 12 players
  if (noP<2 || noP>12) return -1;

  // If number of players has already been set then destroy all that data
  if (noPlayersSet_==true) {
    D_.setDeckFull(); // Reset the deck to 52 cards
    P_.clear();
  } else {
    noPlayersSet_ = true;
  }
  
  // First set the number of players variable and not it is now set
  noPlayers_ = noP;

  // Now initialise the player class vector and the known hold cards for each player
  for (int i=0; i<noPlayers_; i++) {
    H_.push_back(hand());
    P_.push_back(player());
  }
  
  return 0;
  
}



int table::setHoldCards(int playerAdd, std::vector<int> holdInF, std::vector<int> holdInS)
{

  /*
    Set the hold card for the current class (player), and the number of hold cards known.
  */

  // Check input arrays
  if (holdInF.size()!=holdInS.size()) return -1;
  
  // Assign the known hold cards
  P_[playerAdd].numHKnown = holdInF.size();   // Note the number of hold cards in the player hold
  totHoldsKnown=totHoldsKnown+holdInF.size(); // Add the current number of hold cards to the total known
  for (int i=0; i<P_[playerAdd].numHKnown; i++) {
    // Add the cards to the relevant hold
    P_[playerAdd].holdFace.push_back(holdInF[i]);
    P_[playerAdd].holdSuit.push_back(holdInS[i]);
  }

  // Then remove the known hold cards from the deck
  D_.remCards(holdInF,holdInS);
  
  return 0;
  
}



int table::setFlop(std::vector<int> flopInF, std::vector<int> flopInS)
{

  /*
    Set the flop array for the table, removing the cards from the deck once set.

    RETURNS
    =======
        0 :: Success!
	-1 :: flopInF wrong size (/=3)
	-2 :: flopInS wrong size (/=3)
	-3 :: Error removing cards from the deck, possibly not currently in deck
  */

  // Error checks
  if (flopInF.size()!=3) return -1;
  if (flopInS.size()!=3) return -2;

  // Set the class variables
  flopF_ = flopInF;
  flopS_ = flopInS;

  // Remove the cards from array
  int D_stat;
  D_stat = D_.remCards(flopF_,flopS_);
  if(D_stat!=0) return -3;
  
  flopSet_ = true;
  return 0;
  
}



int table::setTurn(int turnInF, int turnInS)
{

  /*
    Set the turn card for the table, removing the cards from the deck once set.

    RETURNS
    =======
        0 :: Success!
	-3 :: Error removing cards from the deck, possibly not currently in deck
  */


  // Set the class variables
  turnF_ = turnInF;
  turnS_ = turnInS;

  // Remove the cards from array
  int D_stat;
  D_stat = D_.remCard(turnF_,turnS_);
  if(D_stat!=0) return -3;
  
  turnSet_ = true;
  return 0;
  
}



int table::setRiver(int riverInF, int riverInS)
{

  /*
    Set the turn card for the table, removing the cards from the deck once set.

    RETURNS
    =======
        0 :: Success!
	-3 :: Error removing cards from the deck, possibly not currently in deck
  */


  // Set the class variables
  riverF_ = riverInF;
  riverS_ = riverInS;

  // Remove the cards from array
  int D_stat;
  D_stat = D_.remCard(riverF_,riverS_);
  if(D_stat!=0) return -3;
  
  riverSet_ = true;
  return 0;
  
}





/*
  Deal cards that are unknown
*/



int table::dealFlopTrunRiver()
{

  /*

    Deal the flop, turn and river arrays for the table if they aren't currently setflop

    RETURNS
    =======
        0 :: Success!
	1 :: Nothing to do, the turn, flop and river are set. So sort of success...

  */

  // If the flop, turn and river are set, then there is nothing left to do, so stop here
  if (flopSet_==false && turnSet_==false && riverSet_==false) return 1;

  // If we have to deal some cards to the flop turn or river, then some have been dealt,
  // therefore we need to re initialise the index array
  D_.setDeckIndex(D_.getNumCards());
  
  // If deck isnt shuffled then shuffle
  if (D_.getDeckShuffled()==false) D_.shuffleI();

  std::vector<int> TEST = D_.getDeckIndex();

  for (int x=0; x<52; x++) {
    std::cout << "Index array : " << TEST[x] << std::endl;
  }
  
  // Then find the number of cards we need to add, and deal these out to the deck class arrays
  // dealFace_ and dealSuit_
  int numToDeal=0;
  if (flopSet_==false)  numToDeal = numToDeal + 3;
  if (turnSet_==false)  numToDeal++;
  if (riverSet_==false) numToDeal++;

  // Now deal out the number of required cards to the dealFace_ and dealSuit_ arrays
  D_.dealCards(numToDeal);

  for (int y=0; y<numToDeal; y++) {
    std::cout << "dealt face values : " << D_.dealFace_[y] << std::endl;
  }
  
  // Set the cards from the single dealt array of numToDeal cards
  int FTRiter=0;
  // Start with the flop
  if (flopSet_==false) {
    for (int FTRi=0; FTRi<3; FTRi++) {
      flopF_.push_back(D_.dealFace_[FTRiter]);
      flopS_.push_back(D_.dealSuit_[FTRiter]);
      FTRiter++;
    }
    flopSet_=true;
  }
  // Then the turn
  if (turnSet_==false) {
    turnF_   = D_.dealFace_[FTRiter];
    turnS_   = D_.dealSuit_[FTRiter];
    turnSet_ = true;
    FTRiter++;
  }
  // Finally the river
  if (riverSet_==false) {
    riverF_   = D_.dealFace_[FTRiter];
    riverS_   = D_.dealSuit_[FTRiter];
    riverSet_ = true;
  }
  
  return 0;
  
}

