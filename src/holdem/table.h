
#ifndef TABLE_H_
#define TABLE_H_

#include <vector>

#include "deck.h"
#include "hand.h"





class hold
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
  hold() {
    noHoldKnown = 0;
  }

  int noHoldKnown; // The number of hold cards known, either 0, 1 or 2

  // Vectors contianing face and suit values of hold cards
  std::vector<int> holdFace;
  std::vector<int> holdSuit;

  // Set the hold cards
  void setHoldCards(std::vector<int> holdInF, std::vector<int> holdInS, int noKnown);
  
};





class table
{

private:

  int noPlayers_;    // Number of players at table
  int noPlayersSet_; // Has the number of players been set

  deck D_; // We need a deck on the table

  std::vector<hand> P_; // A vector of players hands

  std::vector<hold> H_; // A vector of each players hold cards (known and unknown)
  
public:
  
  // Constructor
  table() {

    noPlayersSet_ = false; // Initially no players set
    D_.setDeckFull(); // Initially we have a full deck
    
  }

  // Initialise players
  int setNoPlayers(int noP);
  
};


#endif

