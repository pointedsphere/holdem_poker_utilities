
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
    numHoldKnown = 0; // Initially we do not know any hold cards
    numHoldDealt = 0; // Nor have we dealt any
    numWins=0;        // Nor have we won (yet...)
    numDraw=0;        // Nor have we drawn (yet...)
    for (int Playeri=0; Playeri<10; Playeri++) {
      // Never won any way yet
      winCodesCtr.push_back(0);
      drawCodesCtr.push_back(0);
      handFoundCtr.push_back(0);
    }
  }

  int numHoldDealt; // The number of hold cards known, either 0, 1 or 2
  int numHoldKnown; // The number of hold cards currently dealt to the player

  // Vectors contianing face and suit values of hold cards
  std::vector<int> holdFace;
  std::vector<int> holdSuit;

  // Vectors containing the known components of the holds
  std::vector<int> holdFaceKnown;
  std::vector<int> holdSuitKnown;

  // Total number of wins and drawsfor this player
  int numWins;
  int numDraw;
  
  // each ith element corresponds handCode-1
  std::vector<int> winCodesCtr;  // Number of times this player won with the given hand
  std::vector<int> drawCodesCtr; // Number of times this player drawn with given hand
  std::vector<int> handFoundCtr; // Number of times the given hand has occured for this player
  
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
  
  int totHoldsKnown_; // Total number of hold cards

  int numRuns_;

  deck D_;                // We need a deck on the table
  std::vector<hand>   H_; // A vector of HANDS
  std::vector<player> P_; // A vector of PLAYERS


  // Shared table cards
  std::vector<int> flopF_;
  std::vector<int> flopS_;
  int turnF_;
  int turnS_;
  int riverF_;
  int riverS_;

  // Check if shared table cards set
  bool flopSet_;
  bool turnSet_;
  bool riverSet_;
  bool flopDealt_;
  bool turnDealt_;
  bool riverDealt_;

  bool handsDealt_; // Have hands been dealt or not

  // Results from countin the number of occurences of highest card in best hand index
  int highCardI_;
  int numHighCardI_;

  // Temporary class variables, used here to save on repeated allocation during checking for winners

  // General
  int ip;                            // Iterator
  int numOccurances_;                // Number of occurances of a given handCode
  int drawIntTmp_;                   // a temp integer for draw calculations
  std::vector<int> handCodeArr_;     // Array of all handCodes, the higher the handCode better the hand
  std::vector<int> tTmpVec_;         // A general use temporary vector for use in hand checking
  
public:
  
  // Constructor
  table(int numPlayers) {

    noPlayersSet_ = false;    // Initially no players set
    D_.setDeckFull();         // Initially we have a full deck
    setNoPlayers(numPlayers); // Set up all the vectors etc for the number of players
    totHoldsKnown_=0;         // Total hold cards known is initially zero
    numRuns_=0;               // Not carried out any runs initially
    // No table cards set initially
    flopSet_    = false;
    flopDealt_  = false;
    turnSet_    = false;
    turnDealt_  = false;
    riverSet_   = false;
    riverDealt_ = false;
    turnF_=-1;
    turnS_=-1;
    riverF_=-1;
    riverS_=-1;

    handsDealt_ = false; // Hands not initially set
    
  }

  // Initialise players
  int setNoPlayers(int noP);

  // Set hold cards when known, this also removes the cards from the deck
  int setHoldCards(int playerAdd, std::vector<int> holdInF, std::vector<int> holdInS);
  int setHoldCard (int playerAdd, int holdInF, int holdInS);

  // Set the flop, turn and river
  int setFlop(std::vector<int> flopInF, std::vector<int> flopInS);
  int setTurn(int turnInF, int turnInS);
  int setRiver(int riverInF, int riverInS);

  // Shuffle the deck on the table
  void shuffleDeckIndex();
  
  // Deal random cards to the flop turn and river (if not currently set)
  int dealFlopTurnRiver();

  // Deal the hold cards
  int dealHold(int player);
  
  // Set the hands arrays by dealing random cards to `fill up' hold cards
  int dealAll();

  // Find who won and with what
  int findWinner();

  // Find the highest card at a given index over all the best hands in the H_ hands with
  // a given hand code. Also count the number of times this card occurs with the given
  // handCode.
  void cntHCforHC(int index, int HC); // count high card for hand count

  // Search all players hands for a high card, with restriction to one handCode
  int searchForHighCard(int HC);

  // Reset the table to just the known cards to allow for re-dealing
  int resetTableToKnown();

  // Reset the table completely
  int resetTable();

  // Run Monte Carlo
  void MC(int numMC);
  
  // Get functions
  std::vector<int>    getPlayerHoldFace(int PlayerPP);
  std::vector<int>    getPlayerHoldSuit(int PlayerPP);
  int                 getNumRuns();
  std::vector<int>    getWins();
  std::vector<double> getWinsP();
  std::vector<int>    getDraws();
  std::vector<double> getDrawsP();
  std::vector<int>    getWinsPP(int playerPP);
  std::vector<double> getWinsPPp(int playerPP);
  std::vector<int>    getDrawsPP(int playerPP);
  std::vector<double> getDrawsPPp(int playerPP);
  std::vector<int>    getHandsPP(int playerPP);
  std::vector<double> getHandsPPp(int playerPP);
  int getNumCardsInDeck();

  
};


#endif

