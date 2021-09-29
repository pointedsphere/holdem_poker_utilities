
#ifndef TABLE_H_
#define TABLE_H_

#include <vector>

#include "deck.h"
#include "hand.h"





/*
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                      HOLD CLASS
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/

class player
{

  /*

    The class which holds just two hold cards

    Note: This could go into the hand class, but we will hard copy this to save setting
          it each time we loop for a Monte Carlo simulation, so we want to keep minimal
	  ammount of data in this class as possible.

  */

public:
  // Let everything about the hold cards be public (which is a touch unusual for the hold)

  // Constructor
  player() {
    numHKnown = 0;
  }

  int numHKnown; // The number of hold cards known, either 0, 1 or 2

  // Vectors contianing face and suit values of hold cards
  std::vector<int> holdFace;
  std::vector<int> holdSuit;
  
};





/*
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                     TABLE CLASS
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/

class table
{

private:

  int noPlayers_;    // Number of players at table
  int noPlayersSet_; // Has the number of players been set





  
public:


  // MAKE THE FOLLOWING PRIVATE AFTER TESTING

  deck D_; // We need a deck on the table
  
  std::vector<hand>   H_; // A vector of hands

  std::vector<player> P_; // A vector of players



  
  
  
  // Constructor
  table(int numPlayers) {

    noPlayersSet_ = false;    // Initially no players set
    D_.setDeckFull();         // Initially we have a full deck
    setNoPlayers(numPlayers); // Set up all the vectors etc for the number of players
    
  }

  // Initialise players
  int setNoPlayers(int noP);

  // Set hold cards when known, this also removes the cards from the deck
  int setHoldCards(int playerAdd, std::vector<int> holdInF, std::vector<int> holdInS);

  
};


#endif

