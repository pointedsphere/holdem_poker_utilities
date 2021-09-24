
#ifndef HOLDEMHAND_H_
#define HOLDEMHAND_H_

class hand
{

  /* 
     A Class to hold a hand of cards, this contains the hole, flop turn and river
     meaning it works on 7 cards. 

     This class and its contained variables works only with full knowledge of a
     hand. Any Monte Carlo like simulations etc must be done outside of this hand.

     A card is split into two integers representing first the face value then the suit.

     Suits are given in integer value in [1,4], though which suit is which is irrelevant
     as long as THE SUIT NUMBER ARE CONSISTANT throughout any program.

     The face value used is 2 to 10 for face values in [2,10], then we use
         11: jack
	 12: queen
	 13: king
	 14: ace

     The individual hand checking routines can be called independantly. This means they should
     NOT be used to find all the hands as it is more costly than running the getAllHands routine.
         - for example checking for two pair also checks for a pair, therefore if we wish to 
	   check for both a pair and two pair it suffices to only run getTwoPair
  */
  
private:
  // Note a _ postfix means a private variable
  
  // The cards to use in the hand
  int cards_face_[7];
  int cards_suit_[7];

  // Have the cards been read or not
  bool isCards_;
  
public:

  // Constructor for initial variables
  // NOTE: Initial values for all face values set to -1 which signifies no hand.
  hand() {
    isCards_ = false; // On initialisation we haven't read the cards in

    // Also, on initialisation we do not have a hand

    // Single pair
    hasPair = false;
    pairVal = -1;

    // Two pair
    hasTwoPair = false;
    twoPairHigh = -1;
    twoPairLow  = -1;
    twoPairHighCard = -1;
  }
  
  // Set the cards private array from a full array
  int setCards(int cards[2][7]);
  
  // Find the high card from the current hand
  int highCard;
  void getHighCard();

  // Find if there is a pair, and if there's at least one record it along with the face value of highest pair
  bool hasPair;
  int pairVal;
  void getPair();

  // Find if there is two pair, and if there is record the face value of the two highest pairs
  bool hasTwoPair;
  int twoPairHigh;
  int twoPairLow;
  int twoPairHighCard;
  void getTwoPair();
  
  
};

#endif
