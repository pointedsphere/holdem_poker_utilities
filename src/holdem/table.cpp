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
  P_[playerAdd].numHKnown = holdInF.size();
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
  flopF = flopInF;
  flopS = flopInS;

  // Remove the cards from array
  int D_stat;
  D_stat = D_.remCards(flopF,flopS);
  if(D_stat!=0) return -3;
  
  flopSet = true;
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
  turnF = turnInF;
  turnS = turnInS;

  // Remove the cards from array
  int D_stat;
  D_stat = D_.remCard(turnF,turnS);
  if(D_stat!=0) return -3;
  
  turnSet = true;
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
  riverF = riverInF;
  riverS = riverInS;

  // Remove the cards from array
  int D_stat;
  D_stat = D_.remCard(riverF,riverS);
  if(D_stat!=0) return -3;
  
  riverSet = true;
  return 0;
  
}


