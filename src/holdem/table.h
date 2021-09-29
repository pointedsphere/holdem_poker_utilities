
#ifndef TABLE_H_
#define TABLE_H_

#include <vector>

#include "deck.h"
#include "hand.h"





/*
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                      PLAYER CLASS
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/

class player
{

  /*

    The class which holds the variables that pertain to the players, inc hold cards

    Note: This could go into the hand class, but we will hard copy this to save setting
          it each time we loop for a Monte Carlo simulation, so we want to keep minimal
	  ammount of data in this class as possible.

  */

public:
  // Let everything about the hold cards be public (which is a touch unusual for the hold)

  // Constructor
  player() {
    numHKnown = 0; // Initially we do not know any hold cards
    numWins=0;     // Nor have we won (yet...)
    for (int Playeri=0; Playeri<10; Playeri++) {
      // Never won any way yet
      winHandCtr.push_back(0);
    }
  }

  int numHKnown; // The number of hold cards known, either 0, 1 or 2

  // Vectors contianing face and suit values of hold cards
  std::vector<int> holdFace;
  std::vector<int> holdSuit;

  // Wins data
  int numWins;
  std::vector<int> winHandCtr;
  
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


  std::vector<int> flopS_;
  int turnF_;
  int turnS_;
  int riverF_;
  int riverS_;

  bool flopSet_;
  bool turnSet_;
  bool riverSet_;
  
public:

  // MAKE THE FOLLOWING PRIVATE AFTER TESTING
  std::vector<int> flopF_;
  deck D_; // We need a deck on the table
  std::vector<hand>   H_; // A vector of HANDS
  std::vector<player> P_; // A vector of PLAYERS


  
  // Constructor
  table(int numPlayers) {

    noPlayersSet_ = false;    // Initially no players set
    D_.setDeckFull();         // Initially we have a full deck
    setNoPlayers(numPlayers); // Set up all the vectors etc for the number of players

    // No table cards set initially
    flopSet_  = false;
    turnSet_  = false;
    riverSet_ = false;
    
  }

  // Initialise players
  int setNoPlayers(int noP);

  // Set hold cards when known, this also removes the cards from the deck
  int setHoldCards(int playerAdd, std::vector<int> holdInF, std::vector<int> holdInS);

  // Set the flop, turn and river
  int setFlop(std::vector<int> flopInF, std::vector<int> flopInS);
  int setTurn(int turnInF, int turnInS);
  int setRiver(int riverInF, int riverInS);

  // Deal random cards to the flop turn and river (if not currently set)
  int dealFlopTrunRiver();
  
};


#endif

