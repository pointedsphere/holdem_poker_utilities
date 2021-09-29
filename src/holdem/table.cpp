#include <iostream>
#include <vector>

#include "table.h"
#include "hand.h"



/*
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                      HOLD CLASS
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
    P_.push_back(hand());
    H_.push_back(hold());
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
  H_[playerAdd].numKnown = holdInF.size();
  for (int i=0; i<H_[playerAdd].numKnown; i++) {
    // Add the cards to the relevant hold
    H_[playerAdd].holdFace.push_back(holdInF[i]);
    H_[playerAdd].holdSuit.push_back(holdInS[i]);
  }

  // Then remove the known hold cards from the deck
  D_.remCards(holdInF,holdInS);
  
  return 0;
  
}


