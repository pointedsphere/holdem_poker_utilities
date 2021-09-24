
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
  */
  
private:
  
  // The cards to use in the hand
  int cards_[2][7];

public:
  
  // Set the cards private array from a full array
  int setCards(int cards[2][7]);
  
  
};

#endif
