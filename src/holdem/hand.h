
#ifndef HOLDEMHAND_H_
#define HOLDEMHAND_H_

#include <iostream>
#include <vector>

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
  int cardsFace_[7];
  int cardsSuit_[7];
  
  // Have the cards been read or not
  bool isCards_;
  
public:

  /* Hand descriptor where
n    -1  ::: No hand, i.e. not yet checked
n     1  ::: High card
y     2  ::: Pair
y     3  ::: Two pair
y     4  ::: Three of a kind
y     5  ::: Straight
y     6  ::: Flush
y     7  ::: Full house
y     8  ::: 4 of a kind
y     9  ::: Straight flush
y     10 ::: Royal Flush
  */
  
  int hand_code;

  /* 
     The best hand, which is ordered in a special way for each hand one has.
     Note: best_face is the face values of the best hand from the given cards
           and best_suit are the corresponding suit values for each ith card in 
	   best_face

     Royal Flush:
         { 10, J, Q, K, A }

     Straight Flush:
         In ascending order, e.g. { 3, 4, 5, 6, 7 }

     Four of a Kind:
         Last 4 elements of array are the 4 of a kind cards and first is the odd one
	 e.g. face values in order { 3, 6, 6, 6, 6 }

     Full House:
         The three of a kind elemnts are the last in the array
	 e.g. face values in order { 3, 3, 6, 6, 6 }

     Flush:
         Flush values of highest face cards of flush suit in ascending order
	 e.g. face values in order { 2, 4, 7, 8, 9 }

     Straight:
         Straight cards in ascending order
	 e.g. face values in order { 4, 5, 6, 7, 8 }
	 Note: If an Ace is part of the straight then we have cards in order
	 { 14, 2, 3, 4, 5 }
     
     Three of a kind:
         Three of a kind as the final elements in best_hands, with two highest cards not
	 in the three of a kind in ascending order in index 0 and 1, i.e.
	 e.g. { 2, 13, 4, 4, 4 }

     Two Pair:
         The two pairs in ascending order as the last 4 elements of the array with element
	 0 being the highest card not in a pair
	 e.g. { 7, 2, 2, 10, 10 }

     Pair:
         Store the single pair in the final two elements of the array and ascending high
	 cards in all lower elements
	 e.g. { 2, 4, 6, 5, 5 }

     High Card:
         Return the highest face value cards in ascending order

  */
  int bestFace[5];
  int bestSuit[5];  
  
  // Constructor for initial variables
  // NOTE: Initial values for all face values set to -1 which signifies no hand.
  hand() {
    isCards_ = false; // On initialisation we haven't read the cards in

    // Also, on initialisation we do not have a hand
    hand_code = -1;

    for (int i=0; i<5; i++) {
      bestFace[i] = -1;
      bestSuit[i] = -1;
    }
  }
  
  // Set the cards private array from a full array
  int setCardsFull(int face_in[7], int suit_in[7]);
  // Or for the arrays split into hole, flop, turn and river
  int setCards(int hole[2][2], int flop[2][3], int turn[2][1], int river[2][1]);

  // Set the cards using a vector, used for python wrapping
  int pSetCardsFull(std::vector<int> face_in, std::vector<int> suit_in);
  
  // Get the best hand that can be made from the current cards in cards_face_ and cards_suit_
  int findBestHand();

  // Sort the cards_face_ and cards_suit_ arrays such cards_face_ is in ascending order
  void sortCards();

  // Check for a straight and return the high card of the straight or -1 for no straight
  int getStraight(int S_cards[], int hand_size);

  // Get variables from the class
  std::vector<int> getCardsFace();
  std::vector<int> getCardsSuit();
  std::vector<int> getBestFace();
  std::vector<int> getBestSuit();
  
};

#endif
