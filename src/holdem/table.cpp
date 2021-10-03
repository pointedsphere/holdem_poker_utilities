#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>

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

    RETURNS
    =======
        0  :: Success!
	-2 :: Adding a card to the players hold would take number of hold cards above 2.
	-3 :: playerAdd exceeds number of players at table.

  */

  // We cant have more than two hold cards
  if (P_[playerAdd].numHoldKnown>1) return -2;

  // Player must exist at the table
  if (playerAdd>=noPlayers_) return -3;

  // Check if face and suit are valid values
  if (holdInF<1 || holdInF>14) {
    std::cout << "ERROR : In setHoldCard the face value of the card is outside the valid range [1,14]"
	      << std::endl;
    exit (EXIT_FAILURE);
  }
  if (holdInS<1 || holdInS>4) {
    std::cout << "ERROR : In setHoldCard the suit value of the card is outside the valid range [1,4]"
	      << std::endl;
    exit (EXIT_FAILURE);
  }

  // Assign the known hold cards
  P_[playerAdd].numHoldKnown++; // Note we now know one more hold card
  P_[playerAdd].numHoldDealt++; // This known card is dealt
  totHoldsKnown_++;               // Increment the total known holds

  // Add the cards to the relevant hold and save as known cards
  P_[playerAdd].holdFace.push_back(holdInF);
  P_[playerAdd].holdSuit.push_back(holdInS);
  P_[playerAdd].holdFaceKnown.push_back(holdInF);
  P_[playerAdd].holdSuitKnown.push_back(holdInS);
  
  // Then remove the known hold card from the deck
  D_.remCard(holdInF,holdInS);
  
  return 0;
  
}



int table::setHoldCards(int playerAdd, std::vector<int> holdInF, std::vector<int> holdInS)
{

  /*
    Set the hold card for the current class (player), and the number of hold cards known.

    RETURNS
    =======
        0  :: Success!
	-1 :: Input vectors holdInF and holdInS are of different lengths.
	-2 :: adding cards in holdInF would take number of cards in player hold above 2.
	-3 :: playerAdd exceeds number of players at table.

  */
  
  // Check input arrays, they need to be the same size
  if (holdInF.size()!=holdInS.size()) return -1;

  // We can't have more than two hold cards
  if (holdInF.size()+P_[playerAdd].numHoldKnown>2) return -2;

  // Player must exist at the table
  if (playerAdd>=noPlayers_) return -3;
  
  // Assign the known hold cards
  P_[playerAdd].numHoldKnown += holdInF.size(); // Note the number of hold cards in the player hold
  P_[playerAdd].numHoldDealt += holdInF.size(); // Note the number of hold cards dealt to the player
  totHoldsKnown_ += holdInF.size();  // Add the current number of hold cards to the total known
  for (int i=0; i<P_[playerAdd].numHoldKnown; i++) {
    // Check that the input cards are valid face and sut values
    if (holdInF[i]<1 || holdInF[i]>14) {
      std::cout << "ERROR : In setHoldCards a face value of a card is outside the valid range [1,14]"
		<< std::endl;
      exit (EXIT_FAILURE);
    }
    if (holdInS[i]<1 || holdInS[i]>4) {
      std::cout << "ERROR : In setHoldCards a suit value of a card is outside the valid range [1,4]"
		<< std::endl;
      exit (EXIT_FAILURE);
    }
    // Add the cards to the relevant hold and to save the hold cards
    P_[playerAdd].holdFace.push_back(holdInF[i]);
    P_[playerAdd].holdSuit.push_back(holdInS[i]);
    P_[playerAdd].holdFaceKnown.push_back(holdInF[i]);
    P_[playerAdd].holdSuitKnown.push_back(holdInS[i]);
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
        0  :: Success!
	-1 :: flopInF wrong size (/=3)
	-2 :: flopInS wrong size (/=3)
	-3 :: Error removing cards from the deck, possibly not currently in deck
	-4 :: Flop already set
  */
  
  // Error checks
  if (flopInF.size()!=3) return -1;
  if (flopInS.size()!=3) return -2;
  if (flopSet_==true)    return -4;
  for (int erri=0; erri<3; erri++) {
    // Check that the input cards are valid face and sut values
    if (flopInF[erri]<1 || flopInF[erri]>14) {
      std::cout << "ERROR : In setFlop a face value of a card is outside the valid range [1,14]"
		<< std::endl;
      exit (EXIT_FAILURE);
    }
    if (flopInS[erri]<1 || flopInS[erri]>4) {
      std::cout << "ERROR : In setFlop a suit value of a card is outside the valid range [1,4]"
		<< std::endl;
      exit (EXIT_FAILURE);
    }
  }
  
  // Set the class variables
  flopF_ = flopInF;
  flopS_ = flopInS;

  // Remove the cards from array
  int D_stat;
  D_stat = D_.remCards(flopF_,flopS_);
  if(D_stat!=0) return -3;
  
  flopSet_   = true;
  flopDealt_ = true;
  return 0;
  
}



int table::setTurn(int turnInF, int turnInS)
{

  /*
    Set the turn card for the table, removing the cards from the deck once set.

    RETURNS
    =======
        0  :: Success!
	-3 :: Error removing cards from the deck, possibly not currently in deck
	-4 :: Trun already set
  */

  // Error checks
  if (turnSet_==true) return -4;
  if (turnInF<1 || turnInF>14) {
    std::cout << "ERROR : In setTurn the face value of the card is outside the valid range [1,14]"
	      << std::endl;
    exit (EXIT_FAILURE);
  }
  if (turnInS<1 || turnInS>4) {
    std::cout << "ERROR : In setTurn the suit value of the card is outside the valid range [1,4]"
	      << std::endl;
    exit (EXIT_FAILURE);
  }
    
  // Set the class variables
  turnF_ = turnInF;
  turnS_ = turnInS;

  // Remove the cards from array
  int D_stat;
  D_stat = D_.remCard(turnF_,turnS_);
  if(D_stat!=0) return -3;
  
  turnSet_   = true;
  turnDealt_ = true;
  return 0;
  
}



int table::setRiver(int riverInF, int riverInS)
{

  /*
    Set the turn card for the table, removing the cards from the deck once set.

    RETURNS
    =======
        0  :: Success!
	-3 :: Error removing cards from the deck, possibly not currently in deck
	-4 :: River already set
  */

  // Error checks
  if (riverSet_==true) return -4;  
  if (riverInF<1 || riverInF>14) {
    std::cout << "ERROR : In setRiver ther face value of the card is outside the valid range [1,14]"
	      << std::endl;
    exit (EXIT_FAILURE);
  }
  if (riverInS<1 || riverInS>4) {
    std::cout << "ERROR : In setRiver the suit value of the card is outside the valid range [1,4]"
	      << std::endl;
    exit (EXIT_FAILURE);
  }
  
  // Set the class variables
  riverF_ = riverInF;
  riverS_ = riverInS;

  // Remove the cards from array
  int D_stat;
  D_stat = D_.remCard(riverF_,riverS_);
  if(D_stat!=0) return -3;
  
  riverSet_   = true;
  riverDealt_ = true;
  return 0;
  
}





/*
  
  Deal cards that are unknown

  During dealing the cards we do not remove them from the deck. This allws us to repeat the
  deal quickly.

  MAY BE WORTH ADDING A FUNCTION TO REMOVE ALL THE CARDS IN THE FLOP, TURN, RIVER AND ALL HOLDS
  FROM THE DECK.

*/




void table::shuffleDeckIndex()
{

  D_.shuffleI();
  
}




int table::dealFlopTurnRiver()
{

  /*

    Deal the flop, turn and river arrays for the table if they aren't currently setflop

    RETURNS
    =======
        0 :: Success!
	1 :: Nothing to do, the turn, flop and river are set. So sort of success...

  */
  
  // If the flop, turn and river are set, then there is nothing left to do, so stop here
  if (flopDealt_==true && turnDealt_==true && riverDealt_==true) return 1;

  // If cards not shuffled, then shuffle
  if (D_.getDeckShuffled()==false) D_.shuffleI();
  
  // Then find the number of cards we need to add, and deal these out to the deck class arrays
  // dealFace_ and dealSuit_
  int numToDeal=0;
  if (flopDealt_==false)  numToDeal+=3;
  if (turnDealt_==false)  numToDeal++;
  if (riverDealt_==false) numToDeal++;

  // Now deal out the number of required cards to the dealFace_ and dealSuit_ arrays
  D_.dealCards(numToDeal);
  
  // Set the cards from the single dealt array of numToDeal cards
  int FTRiter=0;
  // Start with the flop
  if (flopDealt_==false) {
    for (int FTRi=0; FTRi<3; FTRi++) {      
      flopF_.push_back(D_.dealFace_[FTRiter]);
      flopS_.push_back(D_.dealSuit_[FTRiter]);
      FTRiter++;
    }
    flopDealt_=true;
  }
  // Then the turn
  if (turnDealt_==false) {
    turnF_   = D_.dealFace_[FTRiter];
    turnS_   = D_.dealSuit_[FTRiter];
    turnDealt_ = true;
    FTRiter++;
  }
  // Finally the river
  if (riverDealt_==false) {
    riverF_   = D_.dealFace_[FTRiter];
    riverS_   = D_.dealSuit_[FTRiter];
    riverDealt_ = true;
  }
  
  return 0;
  
}




int table::dealHold(int player)
{

  /*

    Deal the hold cards to the current player, that is if any cards are needed to be dealt

    RETURNS
    =======
        0  :: Success!
	1  :: Nothing to do, the turn, flop and river are set. So sort of success...
	-1 :: 

  */

  // If we have 2 cards in the hold then exit, we can't deal any more
  if (P_[player].numHoldDealt==2) return 1;

  // Check desired player is at the table
  if (player>=noPlayers_) return -1;
  
  // If cards not shuffled, then shuffle
  if (D_.getDeckShuffled()==false) D_.shuffleI();
  
  // Then find the number of cards we need to add, and deal these out to the deck class arrays
  // dealFace_ and dealSuit_
  int numToDeal;
  numToDeal = 2-P_[player].numHoldDealt;
  
  // Now deal out the number of required cards to the dealFace_ and dealSuit_ arrays
  D_.dealCards(numToDeal);
  
  // Now set the hold cards for the given player
  int dealIter = 0;
  for (int np=P_[player].numHoldDealt; np<2; np++) {
    P_[player].holdFace.push_back(D_.dealFace_[dealIter]);
    P_[player].holdSuit.push_back(D_.dealSuit_[dealIter]);
    P_[player].numHoldDealt++;
    dealIter++;
  }
  
  return 0;
  
}




int table::dealAll()
{

  /*
 
    Deal cards to all hands.

    This routine starts by dealing the flop, turn and river (if they are not already dealt).
    It then assigns each hand using the flop turn and river, taking any known hold cards and 
    combining with some randomly dealt cards to fill all unknown holds.

  */

  int dStat; // deal status

  // Set the deck index before dealing
  D_.setDeckIndex(D_.getNumCards());

  // Shuffle cards before dealing things out
  D_.shuffleI();
  
  // Initially check if the flop turn and river are set, if not this routine sets them
  dStat = dealFlopTurnRiver();
  
  // Now deal up all the players hold cards, and after this set the players full hand (including the
  // flop, turn and river
  for (int p=0; p<noPlayers_; p++) {
    dealHold(p);
    H_[p].SetCards(P_[p].holdFace, P_[p].holdSuit, flopF_, flopS_, turnF_, turnS_, riverF_, riverS_);
  }
  
  handsDealt_=true;
  return 0; // Success
  
}





int table::findWinner()
{

  /*
    Find the winner at the table, add this to the player object win counter and win hand type
    counter variables. Also return an integer of the winning player

    RETURNS
    =======
        >0 :: Success, return the player that has won or 0 if more than one has drawn
	-1 :: Hands have not been dealt, so no one can win (yet)

  */

  int fWStat;
  
  // Can only run if hands have been dealt
  if (handsDealt_==false) return -1;
  
  // Find the best hand in each 7 card hand
  for (int fWi=0; fWi<noPlayers_; fWi++) {
    fWStat = H_[fWi].findBestHand();
    handCodeArr_.push_back(H_[fWi].getHandCode());
    P_[fWi].handFoundCtr[H_[fWi].getHandCode()-1]++;
  }

  // Iterare the number of runs
  numRuns_++;
  
  // Check for the best hand at the table
  for (int hc=10; hc>0; hc--) {

    // First see how many times the current hand code occurs at the table
    numOccurances_ = count(handCodeArr_.begin(), handCodeArr_.end(), hc);

    if (numOccurances_==0) {
      
      // There are no occurences of this hand code, so check the next one down
      continue;

    } else if (numOccurances_==1) {

      // We only have one card with this hand cose, so this hand has won
      drawIntTmp_ = std::distance(handCodeArr_.begin(), std::find(handCodeArr_.begin(),handCodeArr_.end(),hc));
      // Then note the in in the for the player
      P_[drawIntTmp_].numWins++;           // Increment players win counter
      P_[drawIntTmp_].winCodesCtr[hc-1]++; // Increment iterator of win codes

      handCodeArr_.clear(); // Release un-needed memory
      return drawIntTmp_;   // We are now done, we've found a winner!
      
    } else {
      
      // We have more then one player with the same hand type, so we must compare the exact hands
      // This depends on what type of hand it is
      switch(hc) {


	
      case 10: // Royal Flush

	// Two or more royal flushes draw
	for (int ip=0; ip<noPlayers_; ip++) {
	  if (H_[ip].handCode==hc) {
	    P_[ip].numDraw++;            // Iterate number of draws
	    P_[ip].drawCodesCtr[hc-1]++; // Iterate hand type drawn with
	  }
	}

	handCodeArr_.clear(); // Release un-needed memory
	return 0; // Found the drawn straight flushes


	
      case 9: // Straight Flush

	// Loop through all hands and check for highest cards in all stright flushes
	cntHCforHC(4, 9);
	
	// If there is only one of this 4 of a kind return it
	if (numHighCardI_==1) {
	  for (ip=0; ip<noPlayers_; ip++) {
	    if (H_[ip].handCode==9 && H_[ip].bestFace[4]==highCardI_) {
	      P_[ip].numWins++;           // Iterate number of wins
	      P_[ip].winCodesCtr[hc-1]++; // Iterate hand type wins with
	      
	      handCodeArr_.clear(); // Release un-needed memory
	      return ip;            // Only one best hand, so return here
	    }
	  }
	} else {
	  // Otherwise we have a draw, so note the draw values for each drawing player
	  
	  for (ip=0; ip<noPlayers_; ip++) {
	    if (H_[ip].handCode==9 && H_[ip].bestFace[4]==highCardI_) {
	      P_[ip].numDraw++;            // Iterate number of draws
	      P_[ip].drawCodesCtr[hc-1]++; // Iterate hand type drawn with
	    }
	  }

	  handCodeArr_.clear(); // Release un-needed memory
	  return 0; // Return the draw integer
	}


	
      case 8: // Four of a kind

	// We know there are more than one four of a kind, the highest value of the four of a
	// kind always wins, there can be no draw for four of a kind

	// Loop through all hands and check for highest four of a kind, storing in class tmp variables
	cntHCforHC(4, 8);
	
	// If there is only one of this 4 of a kind return it
	if (numHighCardI_==1) {
	  for (ip=0; ip<noPlayers_; ip++) {
	    if (H_[ip].handCode==8 && H_[ip].bestFace[4]==highCardI_) {
	      P_[ip].numWins++;           // Iterate number of wins
	      P_[ip].winCodesCtr[hc-1]++; // Iterate hand type wins with
	      
	      handCodeArr_.clear(); // Release un-needed memory
	      return ip;            // Only one best hand, so return here
	    }
	  }
	} else {
	  // Otherwise we have a draw, so note the draw values for each drawing player
	  
	  for (ip=0; ip<noPlayers_; ip++) {
	    if (H_[ip].handCode==8 && H_[ip].bestFace[4]==highCardI_) {
	      P_[ip].numDraw++;            // Iterate number of draws
	      P_[ip].drawCodesCtr[hc-1]++; // Iterate hand type drawn with
	    }
	  }

	  handCodeArr_.clear(); // Release un-needed memory
	  return 0; // Return the draw integer
	}

	
      case 7: // Full House

	// We know there is more than one full house. We first check the three of a kinds, if
	// one is larger than that hand wins, if not then check the pair, if they're also the
	// same then we have a draw

	// Find the value of the highest three of a kind and the player(s) who have it
	cntHCforHC(4, 7);
	
	// If only one has the highest 3 of a kind then we have a winner
	if (numHighCardI_==1) {
	  for (ip=0; ip<noPlayers_; ip++) {
	    if (H_[ip].handCode==7 && H_[ip].bestFace[4]==highCardI_) {
	      P_[ip].numWins++;           // Iterate number of wins
	      P_[ip].winCodesCtr[hc-1]++; // Iterate hand type wins with
	      
	      handCodeArr_.clear(); // Release un-needed memory
	      return ip;            // Only one best hand, so return here
	    }
	  } 
	}
	
	// We only reach this point if more than one player has an identical 3 of a kind, so
	// now we look for highest pair
	cntHCforHC(0, 7);
	
	// If only one has the highest pair then this player is the winner
	if (numHighCardI_==1) {
	  for (ip=0; ip<noPlayers_; ip++) {
	    if (H_[ip].handCode==7 && H_[ip].bestFace[0]==highCardI_) {
	      P_[ip].numWins++;           // Iterate number of wins
	      P_[ip].winCodesCtr[hc-1]++; // Iterate hand type wins with
	      
	      handCodeArr_.clear(); // Release un-needed memory
	      return ip;            // Only one best hand, so return here
	    }
	  }
	} else {
	  // Otherwise we have a draw, so note the draw values for each drawing player
	  
	  for (ip=0; ip<noPlayers_; ip++) {
	    if (H_[ip].handCode==7 && H_[ip].bestFace[0]==highCardI_) {
	      P_[ip].numDraw++;            // Iterate number of draws
	      P_[ip].drawCodesCtr[hc-1]++; // Iterate hand type drawn with
	    }
	  }

	  handCodeArr_.clear(); // Release un-needed memory
	  return 0; // Return the draw integer
	}


	
      case 6: // Flush
	
	// We have more than one flush, so we need to find the highest card in the flush
	// Hand with the highest card wins, regardless as to what other cards are
	// This is in essence searching for the player with the high card but only
	// considering those players with a flush
	
	drawIntTmp_ = searchForHighCard(6);

	// Now check if there is a draw
	if (drawIntTmp_>-1) {

	  // If searchForHighCard returns a non-negative integer then one player has won
	  // with player index the returned value of searchForHighCard
	  P_[drawIntTmp_].numWins++;
	  P_[drawIntTmp_].winCodesCtr[hc-1]++; // Iterate hand type wins with
	      
	  handCodeArr_.clear(); // Release un-needed memory
	  return drawIntTmp_;   // Only one best hand, so return here

	} else {

	  // Otherwise we have a draw, with all drawn players given by index returned
	  // by searchForHighCard into the class variable tTmpVec_
	  int tmpVecSize=tTmpVec_.size();
	  for (ip=0; ip<tmpVecSize; ip++) {
	    P_[tTmpVec_[ip]].numDraw++;            // Iterate number of draws
	    P_[tTmpVec_[ip]].drawCodesCtr[hc-1]++; // Iterate hand type drawn with
	  }
	  handCodeArr_.clear(); // Release un-needed memory
	  return 0;             // Return the draw integer
	}


	
      case 5: // Straight

	// We have more than one straight, so we need to see which one has the highest high card
	cntHCforHC(4, 5);
	
	// If only one has this high card it wins
	if (numHighCardI_==1) {
	  
	  for (ip=0; ip<noPlayers_; ip++) {
	    if (H_[ip].handCode==5 && H_[ip].bestFace[4]==highCardI_) {
	      P_[ip].numWins++;           // Iterate number of wins
	      P_[ip].winCodesCtr[hc-1]++; // Iterate hand type wins with
	      
	      handCodeArr_.clear(); // Release un-needed memory
	      return ip;            // Only one best hand, so return here
	    }
	  }

	} else {
	  // Otherwise we draw

	  for (ip=0; ip<noPlayers_; ip++) {
	    if (H_[ip].handCode==5 && H_[ip].bestFace[4]==highCardI_) {
	      P_[ip].numDraw++;            // Iterate number of draws
	      P_[ip].drawCodesCtr[hc-1]++; // Iterate hand type drawn with
	    }
	  }

	  handCodeArr_.clear(); // Release un-needed memory
	  return 0; // Return the draw integer

	}


	
      case 4: // Three of a kind
	
	// We have more than one three of a kind, highest 3 of a kind wins before looking at kickers
	cntHCforHC(4, 4);

	// If only one has this high card it wins
	if (numHighCardI_==1) {
	  
	  for (ip=0; ip<noPlayers_; ip++) {
	    if (H_[ip].handCode==4 && H_[ip].bestFace[4]==highCardI_) {
	      P_[ip].numWins++;           // Iterate number of wins
	      P_[ip].winCodesCtr[hc-1]++; // Iterate hand type wins with
	      
	      handCodeArr_.clear(); // Release un-needed memory
	      return ip;            // Only one best hand, so return here
	    }
	  }
	}

	// We need a few more variables to check the kickers
	int threeKindCheck3;
	threeKindCheck3 = highCardI_;

	// If more than one hand shares the same three of a kind check the highest kicker
	cntHCforHC(1, 4);

	// If only one has this high card kicker
	if (numHighCardI_==1) {
	  
	  for (ip=0; ip<noPlayers_; ip++) {
	    if (H_[ip].handCode==4 && H_[ip].bestFace[1]==highCardI_
		&& H_[ip].bestFace[4]==threeKindCheck3) {
	      P_[ip].numWins++;           // Iterate number of wins
	      P_[ip].winCodesCtr[hc-1]++; // Iterate hand type wins with
	      
	      handCodeArr_.clear(); // Release un-needed memory
	      return ip;            // Only one best hand, so return here
	    }
	  }
	}

	// Now check the final kicker if we still haven't got a winner
	int threeKindCheckK;
	threeKindCheckK = highCardI_;

	// Count the number of identical highest kickers
	cntHCforHC(0, 4);
	
	// If only one has this high card kicker
	if (numHighCardI_==1) {
	  
	  for (ip=0; ip<noPlayers_; ip++) {
	    if (H_[ip].handCode==4 && H_[ip].bestFace[0]==highCardI_
		&& H_[ip].bestFace[4]==threeKindCheck3 && H_[ip].bestFace[1]==threeKindCheckK) {
	      P_[ip].numWins++;           // Iterate number of wins
	      P_[ip].winCodesCtr[hc-1]++; // Iterate hand type wins with
	      
	      handCodeArr_.clear(); // Release un-needed memory
	      return ip;            // Only one best hand, so return here
	    }
	  }
	}
	

	// If we still haven't found a winner then we have a draw
	for (ip=0; ip<noPlayers_; ip++) {
	  if (H_[ip].handCode==4 && H_[ip].bestFace[0]==highCardI_
		&& H_[ip].bestFace[4]==threeKindCheck3 && H_[ip].bestFace[1]==threeKindCheckK) {
	    P_[ip].numDraw++;            // Iterate number of draws
	    P_[ip].drawCodesCtr[hc-1]++; // Iterate hand type drawn with
	  }
	}

	handCodeArr_.clear(); // Release un-needed memory
	return 0; // Return the draw integer



      case 3: // Two pair
	
	// We must now check the highest pair, the lowest pair and the single kicker

	// First we check the highest pair
	cntHCforHC(4, 3);

	// If only one has this high card it wins
	if (numHighCardI_==1) {
	  
	  for (ip=0; ip<noPlayers_; ip++) {
	    if (H_[ip].handCode==3 && H_[ip].bestFace[4]==highCardI_) {
	      P_[ip].numWins++;           // Iterate number of wins
	      P_[ip].winCodesCtr[hc-1]++; // Iterate hand type wins with
	      
	      handCodeArr_.clear(); // Release un-needed memory
	      return ip;            // Only one best hand, so return here
	    }
	  }
	}

	// We now store the highest pair face value and check the lower pair
	int twoPairHigh;
	twoPairHigh = highCardI_;

	cntHCforHC(2, 3);

	// If only one has this low pair face value
	if (numHighCardI_==1) {
	  
	  for (ip=0; ip<noPlayers_; ip++) {
	    if (H_[ip].handCode==3 && H_[ip].bestFace[2]==highCardI_
		&& H_[ip].bestFace[4]==twoPairHigh) {
	      P_[ip].numWins++;           // Iterate number of wins
	      P_[ip].winCodesCtr[hc-1]++; // Iterate hand type wins with
	      
	      handCodeArr_.clear(); // Release un-needed memory
	      return ip;            // Only one best hand, so return here
	    }
	  }
	}

	// We now store the low pair for the check of the final kicker
	int twoPairLow;
	twoPairLow = highCardI_;

	cntHCforHC(0, 3);

	// If only one has this low pair face value
	if (numHighCardI_==1) {
	  
	  for (ip=0; ip<noPlayers_; ip++) {
	    if (H_[ip].handCode==3 && H_[ip].bestFace[0]==highCardI_
		&& H_[ip].bestFace[4]==twoPairHigh && H_[ip].bestFace[2]==twoPairLow) {
	      P_[ip].numWins++;           // Iterate number of wins
	      P_[ip].winCodesCtr[hc-1]++; // Iterate hand type wins with
	      
	      handCodeArr_.clear(); // Release un-needed memory
	      return ip;            // Only one best hand, so return here
	    }
	  }
	}

      	// If we still haven't found a winner then we have a draw
	for (ip=0; ip<noPlayers_; ip++) {
	  if (H_[ip].handCode==3 && H_[ip].bestFace[0]==highCardI_
		&& H_[ip].bestFace[4]==twoPairHigh && H_[ip].bestFace[2]==twoPairLow) {
	    P_[ip].numDraw++;            // Iterate number of draws
	    P_[ip].drawCodesCtr[hc-1]++; // Iterate hand type drawn with
	  }
	}

	handCodeArr_.clear(); // Release un-needed memory
	return 0; // Return the draw integer



      case 2: // Pair

	// For a single pair we must check the pair, then the three kickers
	// First we check the highest pair
	cntHCforHC(4, 2);

	// If only one has this high card it wins
	if (numHighCardI_==1) {
	  
	  for (ip=0; ip<noPlayers_; ip++) {
	    if (H_[ip].handCode==2 && H_[ip].bestFace[4]==highCardI_) {
	      P_[ip].numWins++;           // Iterate number of wins
	      P_[ip].winCodesCtr[hc-1]++; // Iterate hand type wins with
	      
	      handCodeArr_.clear(); // Release un-needed memory
	      return ip;            // Only one best hand, so return here
	    }
	  }
	}

	// Now check the highest kicker, where we also need it to be a kicker for a highest pair
	int pairPval;
	pairPval = highCardI_;

	cntHCforHC(2, 2);

	// If only one has this high card it wins
	if (numHighCardI_==1) {
	  
	  for (ip=0; ip<noPlayers_; ip++) {
	    if (H_[ip].handCode==2 && H_[ip].bestFace[4]==pairPval
		&& H_[ip].bestFace[2]==highCardI_) {
	      P_[ip].numWins++;           // Iterate number of wins
	      P_[ip].winCodesCtr[hc-1]++; // Iterate hand type wins with
	      
	      handCodeArr_.clear(); // Release un-needed memory
	      return ip;            // Only one best hand, so return here
	    }
	  }
	}

	// Check the next highest kicker, where we also need it to be a kicker for a highest pair
	int pairK1val;
	pairK1val = highCardI_;

	cntHCforHC(1, 2);

	// If only one has this high card it wins
	if (numHighCardI_==1) {
	  
	  for (ip=0; ip<noPlayers_; ip++) {
	    if (H_[ip].handCode==2 && H_[ip].bestFace[4]==pairPval
		&& H_[ip].bestFace[2]==pairK1val && H_[ip].bestFace[1]==highCardI_) {
	      P_[ip].numWins++;           // Iterate number of wins
	      P_[ip].winCodesCtr[hc-1]++; // Iterate hand type wins with
	      
	      handCodeArr_.clear(); // Release un-needed memory
	      return ip;            // Only one best hand, so return here
	    }
	  }
	}

	// Check the smallest kicker, where we also need it to be a kicker for a highest pair
	int pairK2val;
	pairK2val = highCardI_;

	cntHCforHC(0, 2);

	// If only one has this high card it wins
	if (numHighCardI_==1) {
	  
	  for (ip=0; ip<noPlayers_; ip++) {
	    if (H_[ip].handCode==2 && H_[ip].bestFace[4]==pairPval
		&& H_[ip].bestFace[2]==pairK1val && H_[ip].bestFace[1]==pairK2val
		&& H_[ip].bestFace[0]==highCardI_) {
	      P_[ip].numWins++;           // Iterate number of wins
	      P_[ip].winCodesCtr[hc-1]++; // Iterate hand type wins with
	      
	      handCodeArr_.clear(); // Release un-needed memory
	      return ip;            // Only one best hand, so return here
	    }
	  }
	}

      	// If we still haven't found a winner then we have a draw
	for (ip=0; ip<noPlayers_; ip++) {
	  if (H_[ip].handCode==2 && H_[ip].bestFace[4]==pairPval
		&& H_[ip].bestFace[2]==pairK1val && H_[ip].bestFace[1]==pairK2val
		&& H_[ip].bestFace[0]==highCardI_) {
	    P_[ip].numDraw++;            // Iterate number of draws
	    P_[ip].drawCodesCtr[hc-1]++; // Iterate hand type drawn with
	  }
	}

	handCodeArr_.clear(); // Release un-needed memory
	return 0; // Return the draw integer



      case 1: // High Card

	// We have a nice function for this one, so we just use that like we did for the flush
	drawIntTmp_ = searchForHighCard(1);

	// Now check if there is a draw
	if (drawIntTmp_>-1) {

	  // If searchForHighCard returns a non-negative integer then one player has won
	  // with player index the returned value of searchForHighCard
	  P_[drawIntTmp_].numWins++;
	  P_[drawIntTmp_].winCodesCtr[hc-1]++; // Iterate hand type wins with
	      
	  handCodeArr_.clear(); // Release un-needed memory
	  return drawIntTmp_;   // Only one best hand, so return here

	} else {

	  // Otherwise we have a draw, with all drawn players given by index returned
	  // by searchForHighCard into the class variable tTmpVec_
	  int tmpVecSize=tTmpVec_.size();
	  for (ip=0; ip<tmpVecSize; ip++) {
	    P_[tTmpVec_[ip]].numDraw++;            // Iterate number of draws
	    P_[tTmpVec_[ip]].drawCodesCtr[hc-1]++; // Iterate hand type drawn with
	  }
	  handCodeArr_.clear(); // Release un-needed memory
	  return 0;             // Return the draw integer
	}

	
	





	
      }
      
    }

  }
  
  return -10; // We shouldn't get to here, so return -10 for major error
  
};





void table::cntHCforHC(int index, int HC) {

  /*
    Loop over all the hands for all the players, find the highest card at a given
    index in the best hand for all players with a given hand code. Also return the
    number of cards with this vaue at the index for hands with hand code HC

    Returns are indirect, with the class variables highCardI_ and numHighCardI_ set
    by this routine for face value of highest card and the number of times it occurs
    in hands where handCode==HC.

    This is used for checking draws, i.e. checking or high cards for similar hands
  */

  highCardI_=-1;
  numHighCardI_=0;
  
  // Loop over all players
  for (ip=0; ip<noPlayers_; ip++) {

    // Only take account of those with a full house
    if (H_[ip].handCode==HC) {

      // Either count an identical 3 of a kind or note new highest three of a kind
      if (H_[ip].bestFace[index]>highCardI_) {
	highCardI_=H_[ip].bestFace[index];
	numHighCardI_=1;
      } else if (H_[ip].bestFace[index]==highCardI_) {
        numHighCardI_++;
      }

    }

  }

}





int table::searchForHighCard(int HC)
{

  /*

    Find and return the index of the player with the best hand if we assume the handCode given
    by HC is a high card. This is given as an input to allow for comparison of flushes also.

    RETURNS
    =======
        -1  :: Draw, stored all in tTmpVec_ class variable
	>-1 :: Index of winning player
    
   */

  int HCIs;
  int HCbest;
  std::vector<int> HCIv;
  
  // Get indexes of the players with the handCode HC
  HCIs=0;
  for (int iq=0; iq<noPlayers_; iq++) {
    if (H_[iq].handCode==HC) {
      HCIv.push_back(iq);
      HCIs++;
    }
  }

  // Loop over all hands looking for highest unique high card
  for (int iq=4; iq>-1; iq--) {

    // Find the best high card in high card arrays
    HCbest=-1;
    for (int ir=0; ir<HCIs; ir++) {
      if (H_[HCIv[ir]].bestFace[iq]>HCbest) {
	HCbest = H_[HCIv[ir]].bestFace[iq];
      } 
    }
    
    // Remove any players from the mix who do not have the best high card or kicker
    for (int ir=0; ir<HCIs; ir++) {
      if (H_[HCIv[ir]].bestFace[iq]!=HCbest) {
	HCIv.erase(HCIv.begin()+ir);
	HCIs--;
      }
    }

    // If we only have one card left, this player has the best high card hand with handCode HC
    if (HCIs==1) {
      return HCIv[0];
    }

    // If we get to the end and we still have players in it's a draw
    if (iq==0) {
      tTmpVec_.clear();
      for (int ir=0; ir<HCIs; ir++) {
	tTmpVec_.push_back(HCIv[ir]);
      }
      return -1;
    }
    
  }

  return -1000; // Should not reach here
  
};







int table::resetTableToKnown()
{

  /*
    
    Reset the table to only have the known cards, this allows for re-dealing fresh random cards
    whilst keeping the known cards.

  */
   
  // Look first at the cards on the table
  if (flopSet_==false) {
    if (flopDealt_==true) {
      flopDealt_=false;
      flopF_.clear();
      flopS_.clear();
      D_.itNumCardsInDeck(3);
    }
  }
  if (turnSet_==false) {
    if (turnDealt_==true) {
      turnDealt_=false;
      turnF_=-1;
      turnS_=-1;
      D_.itNumCardsInDeck(1);
    }
  }
  if (riverSet_==false) {
    if (riverDealt_==true) {
      riverDealt_=false;
      riverF_=-1;
      riverS_=-1;
      D_.itNumCardsInDeck(1);
    }
  }

  for (int p=0; p<noPlayers_; p++) {
    // Now loop through and discard all dealt cards (that are not known a priori) from the holds
    if (P_[p].numHoldKnown==0) {
      // If there are no known hold cards then clear all the hold arrays
      P_[p].holdFace.clear();
      P_[p].holdSuit.clear();
      P_[p].numHoldDealt=0;
      D_.itNumCardsInDeck(2);
    } else if (P_[p].numHoldKnown==1) {
      // If one card is known then just remove the last dealt card from the hold
      P_[p].holdFace.pop_back();
      P_[p].holdSuit.pop_back();
      P_[p].numHoldDealt--;
      D_.itNumCardsInDeck(1);
    } // Don't need to take any action if both hold cards are known for a player
  }
  
  return 0;
  
};



int table::resetTable()
{

  /*
    
    Reset the table to only have the known cards, this allows for re-dealing fresh random cards
    whilst keeping the known cards.

  */
   
  // Look first at the cards on the table
  flopSet_=false;
  if (flopDealt_==true) {
    flopDealt_=false;
    flopF_.clear();
    flopS_.clear();
  }
  
  turnSet_=false;
  if (turnDealt_==true) {
    turnDealt_=false;
    turnF_=-1;
    turnS_=-1;
  }
    
  riverSet_=false;
  if (riverDealt_==true) {
    riverDealt_=false;
    riverF_=-1;
    riverS_=-1;
  }

  for (int p=0; p<noPlayers_; p++) {
    // Now loop through and discard all players and reset everything
    P_[p].numHoldKnown = 0;
    P_[p].numHoldDealt = 0;
    P_[p].numWins      = 0;
    P_[p].numDraw      = 0;
    P_[p].holdFace.clear();
    P_[p].holdSuit.clear();
    P_[p].holdFaceKnown.clear();
    P_[p].holdSuitKnown.clear();
    P_[p].winCodesCtr.clear();
    P_[p].drawCodesCtr.clear();
    P_[p].handFoundCtr.clear();
    for (int Pi=0; Pi<10; Pi++) {
      // Never won any way yet
      P_[p].winCodesCtr.push_back(0);
      P_[p].drawCodesCtr.push_back(0);
      P_[p].handFoundCtr.push_back(0);
    }
  }
  totHoldsKnown_ = 0;

  // Reset the deck to a full deck
  D_.setDeckFull();
  
  return 0;
  
};



void table::MC(int numMC)
{

  /*
    Run a Monte Carlo simulation by taking the known cards, dealing out other cards (from a
    shuffled deck). Then finding a winner and finally resetting the table to just the known cards.
    This Monte Carlo simulation is ran numMC times.
   */

  int MCstat;
  
  for (int Nmc=0; Nmc<numMC; Nmc++) {
    MCstat = dealAll();
    MCstat = findWinner();
    MCstat = resetTableToKnown();
  }
  
}




/*
  
  Return values from the table

*/




std::vector<int> table::getPlayerHoldFace(int playerPP)
{

  return P_[playerPP].holdFace;
  
};
std::vector<int> table::getPlayerHoldSuit(int playerPP)
{

  return P_[playerPP].holdSuit;
  
};
std::vector<int> table::getWins()
{

  std::vector<int> getTmp;
  for (int g=0; g<noPlayers_; g++) {
    getTmp.push_back(P_[g].numWins);
  }
  return getTmp;
  
};
std::vector<double> table::getWinsP()
{

  std::vector<double> getTmp;
  for (int g=0; g<noPlayers_; g++) {    
    getTmp.push_back((double)P_[g].numWins/(double)numRuns_);
  }
  return getTmp;
  
};
std::vector<int> table::getDraws()
{

  std::vector<int> getTmp;
  for (int g=0; g<noPlayers_; g++) {
    getTmp.push_back(P_[g].numDraw);
  }
  return getTmp;
  
};
std::vector<double> table::getDrawsP()
{

  std::vector<double> getTmp;
  for (int g=0; g<noPlayers_; g++) {    
    getTmp.push_back((double)P_[g].numDraw/(double)numRuns_);
  }
  return getTmp;
  
};
std::vector<int> table::getWinsPP(int playerPP)
{

  std::vector<int> getTmp;
  for (int g=0; g<10; g++) {
    getTmp.push_back(P_[playerPP].winCodesCtr[g]);
  }
  return getTmp;
  
};
std::vector<double> table::getWinsPPp(int playerPP)
{

  std::vector<double> getTmp;
  for (int g=0; g<10; g++) {
    getTmp.push_back((double)P_[playerPP].winCodesCtr[g]/(double)numRuns_);
  }
  return getTmp;
  
};
std::vector<int> table::getDrawsPP(int playerPP)
{

  std::vector<int> getTmp;
  for (int g=0; g<10; g++) {
    getTmp.push_back(P_[playerPP].drawCodesCtr[g]);
  }
  return getTmp;
  
};
std::vector<double> table::getDrawsPPp(int playerPP)
{

  std::vector<double> getTmp;
  for (int g=0; g<10; g++) {
    getTmp.push_back((double)P_[playerPP].drawCodesCtr[g]/(double)numRuns_);
  }
  return getTmp;
  
};
std::vector<int> table::getHandsPP(int playerPP)
{

  std::vector<int> getTmp;
  for (int g=0; g<10; g++) {
    getTmp.push_back(P_[playerPP].handFoundCtr[g]);
  }
  return getTmp;
  
};
std::vector<double> table::getHandsPPp(int playerPP)
{

  std::vector<double> getTmp;
  for (int g=0; g<10; g++) {
    getTmp.push_back((double)P_[playerPP].handFoundCtr[g]/(double)numRuns_);
  }
  return getTmp;
  
};
int table::getNumCardsInDeck()
{

  return D_.getNumCards();
  
}
int table::getNumRuns()
{

  return numRuns_;
  
}






