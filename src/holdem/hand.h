
#ifndef HOLDEMHAND_H_
#define HOLDEMHAND_H_

class hand
{

  /* 
     A Class to hold a hand of cards, this contains the hole, flop, turn and river
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

  /* Hand descriptor where
n     0  ::: No hand, i.e. not yet checked
n     1  ::: High card
n     2  ::: Pair
n     3  ::: Two pair
n     4  ::: Three of a kind
n     5  ::: Straight
n     6  ::: Flush
y     7  ::: Full house
y     8  ::: 4 of a kind
y     9  ::: Straight flush
y     10 ::: Royal Flush
  */
  int hand_code;

  // Straight flush values
  int straightFlushHighCard;

  // Four of a kind values
  int fourOfAKind4;  // The value of the four of a kind in four of a kind
  int fourOfAKindSpare; // The face value of the highest card in hand not in four of a kind

  // Full house values
  int fullHouse3; // The value of the 3 of a kind in the full house
  int fullHouse2; // The value of the pair in the full house
  
  // Three of a kind values
  int threeOfAKind3;     // The value of the 3 cards in 3 of a kind
  int threeOfAKindSpare[2]; // The highest cards, in ascending order, in hand that arent 3 of a kind

  // Two Pair Values
  int twoPairHigh;  // Highest face value pair in 2 pair
  int twoPairLow;   // Second highest pair in hand (if we have 2 pair)
  int twoPairSpare; // Non-paired card when have 2 pair

  // Pair values
  int pairVal;      // Value of pair if we only have a pair
  int pairSpare[3]; // In ascending face order, the non paired cards in the pair hand

  
  // Constructor for initial variables
  // NOTE: Initial values for all face values set to -1 which signifies no hand.
  hand() {
    isCards_ = false; // On initialisation we haven't read the cards in

    // Also, on initialisation we do not have a hand
    hand_code = -1;

    straightFlushHighCard = -1;
    
    fourOfAKind4          = -1;
    fourOfAKindSpare      = -1;

    fullHouse3 = -1;
    fullHouse2 = -1;
    
    threeOfAKind3         = -1;
    threeOfAKindSpare[0]     = -1;
    threeOfAKindSpare[1]     = -1;

    twoPairHigh = -1;
    twoPairLow = -1;
    twoPairSpare = -1;

    pairVal = -1;
    pairSpare[0] = -1;
    pairSpare[0] = -1;
    pairSpare[0] = -1;

    // // Single pair
    // hasPair = false;
    // pairVal = -1;

    // // Two pair
    // hasTwoPair = false;
    // twoPairHigh = -1;
    // twoPairLow  = -1;
    // twoPairHighCard = -1;
    
  }
  
  // Set the cards private array from a full array
  int setCards(int cards[2][7]);
  // Or for the arrays split into hole, flop, turn and river
  int setCards(int hole[2][2], int flop[2][3], int turn[2][1], int river[2][1]);
  
  // // Find the high card from the current hand
  // int highCard;
  // void getHighCard();

  // // Find if there is a pair, and if there's at least one record it along with the face value of highest pair
  // bool hasPair;
  // int pairVal;
  // void getPair();

  // // Find if there is two pair, and if there is record the face value of the two highest pairs
  // bool hasTwoPair;
  // int twoPairHigh;
  // int twoPairLow;
  // int twoPairHighCard;
  // void getTwoPair();

  // Get the best hand that can be made from the current cards in cards_face_ and cards_suit_
  int getBestHand();

  // Sort the cards_face_ and cards_suit_ arrays such cards_face_ is in ascending order
  void sortCards();

  // Check for a straight and return the high card of the straight or -1 for no straight
  int getStraight(int S_cards[], int hand_size);
  
};

#endif
