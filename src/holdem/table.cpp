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

  During initialisation we remove cards from the deck arrays

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
    D_.setDeckFull();    // Reset the deck to 52 cards
    D_.setDeckIndex(52); // Set the deck index for 52 cards
    P_.clear();          // Delete player objects
    H_.clear();          // Delete hand objects
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



int table::setHoldCard(int playerAdd, int holdInF, int holdInS)
{

  /*
    Add a hold card to the ``playerAdd'' players hold.

  */

  // We cant have more than two hold cards
  if (P_[playerAdd-1].numHKnown>1) return -1;
  
  // Assign the known hold cards
  P_[playerAdd-1].numHKnown++; // Note we now know one more hold card
  totHoldsKnown_++;            // Increment the total known holds

  // Add the cards to the relevant hold
  P_[playerAdd-1].holdFace.push_back(holdInF);
  P_[playerAdd-1].holdSuit.push_back(holdInS);

  // Then remove the known hold card from the deck
  D_.remCard(holdInF,holdInS);
  
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
  P_[playerAdd-1].numHKnown = holdInF.size();   // Note the number of hold cards in the player hold
  totHoldsKnown_=totHoldsKnown_+holdInF.size(); // Add the current number of hold cards to the total known
  for (int i=0; i<P_[playerAdd-1].numHKnown; i++) {
    // Add the cards to the relevant hold
    P_[playerAdd-1].holdFace.push_back(holdInF[i]);
    P_[playerAdd-1].holdSuit.push_back(holdInS[i]);
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
  
  // Then find the number of cards we need to add, and deal these out to the deck class arrays
  // dealFace_ and dealSuit_
  int numToDeal=0;
  if (flopSet_==false)  numToDeal = numToDeal + 3;
  if (turnSet_==false)  numToDeal++;
  if (riverSet_==false) numToDeal++;

  // Now deal out the number of required cards to the dealFace_ and dealSuit_ arrays
  D_.dealCards(numToDeal);
  
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



int table::dealAllHands()
{

  /*
    Deal cards to all hands.

    This routine starts by dealing the flop turn and river (if they are not already dealt).
    It then assigns each hand using the flop turn and river, taking any known hold cards and 
    combining with some randomly dealt cards to fill all unknown holds.
   */

  int dStat; // deal stat integer
  
  // Initially check if the flop turn and river are set, if not this routine sets them
  dStat = dealFlopTrunRiver();

  // If deck isnt shuffled then shuffle
  if (D_.getDeckShuffled()==false) D_.shuffleI();
  
  // Now deal some new cards to the deck deal class vectors, based on the total number of
  // hold cards (noPlayers*2) minus number known hold cards (totHoldsKnown)
  D_.dealCards((noPlayers_*2)-totHoldsKnown_);
  
  // Now loop through the hands, dealing flop values if needed
  int HDealI=0;                 // Which card from the dealt stack should we deal
  std::vector<int> holdFaceTmp; // Temp face array
  std::vector<int> holdSuitTmp; // Temp suit array

  for (int h=0; h<noPlayers_; h++) {

    switch (P_[h].numHKnown) {
    case 2:
      
      // If there are two known flop cards for the current playerwe do not need to deal any
      // cards nor do we need to use the temporary hold buffer arrays
      H_[h].SetCards(P_[h].holdFace, P_[h].holdSuit, flopF_, flopS_, turnF_, turnS_, riverF_, riverS_);

    default:

      // If there are less than 2 known hold cards we must deal up to two, we do this using the temporary
      // arrays so we can reuse the same player object over multiple hand setting for a Monte Carlo sim
      holdFaceTmp = P_[h].holdFace;
      holdSuitTmp = P_[h].holdSuit;

      // Then deal up the hold, such that there are two cards in the current players temporary hold
      for (int q=P_[h].numHKnown; q<2; q++) {
	
	holdFaceTmp.push_back(D_.dealFace_[HDealI]);
	holdSuitTmp.push_back(D_.dealSuit_[HDealI]);
	HDealI++;
      }

      // Now set the hand from this temp hold
      H_[h].SetCards(holdFaceTmp, holdSuitTmp, flopF_, flopS_, turnF_, turnS_, riverF_, riverS_);

      // And as we are done with the temp vectors clear them
      holdFaceTmp.clear();
      holdSuitTmp.clear();
      
    }
    
  }

  handsDealt_=true;
  return 0; // Success
  
}



int table::findWinner()
{

  /*
    Find the winner at the table, add this to the player object win counter and win hand type
    counter variables. Also return an integer of the winning player
  */

  return 0;
  
}



