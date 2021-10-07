
#ifndef HAND_H_
#define HAND_H_

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
     as long as THE SUIT NUMBER IS CONSISTANT throughout any program.

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
  int cardsFaceP_[7];
  int cardsSuitP_[7];
  int cardsFullP_[7];
  
  // Have the cards been read or not
  bool isCards_;
  
public:

  /* Hand descriptor where
     -1  ::: No hand, i.e. not yet checked
      1  ::: High card
      2  ::: Pair
      3  ::: Two pair
      4  ::: Three of a kind
      5  ::: Straight
      6  ::: Flush
      7  ::: Full house
      8  ::: 4 of a kind
      9  ::: Straight flush
      10 ::: Royal Flush
  */
  
  int handCode;

  /* 
     The best hand, which is ordered in a special way for each hand one has.
     Note: best_face is the face values of the best hand from the given cards
           and best_suit are the corresponding suit values for each ith card in 
	   best_face

     10 - Royal Flush:
         { 10, J, Q, K, A }

     9 - Straight Flush:
         In ascending order, e.g. { 3, 4, 5, 6, 7 }

     8 - Four of a Kind:
         Last 4 elements of array are the 4 of a kind cards and first is the odd one
	 e.g. face values in order { 3, 6, 6, 6, 6 }
p
     7 - Full House:
         The three of a kind elemnts are the last in the array
	 e.g. face values in order { 3, 3, 6, 6, 6 }

     6 - Flush:
         Flush values of highest face cards of flush suit in ascending order
	 e.g. face values in order { 2, 4, 7, 8, 9 }

     5 - Straight:
         Straight cards in ascending order
	 e.g. face values in order { 4, 5, 6, 7, 8 }
	 Note: If an Ace is part of the straight then we have cards in order
	 { 14, 2, 3, 4, 5 }
     
     4- Three of a kind:
         Three of a kind as the final elements in best_hands, with two highest cards not
	 in the three of a kind in ascending order in index 0 and 1
	 e.g. { 2, 13, 4, 4, 4 }

     3 - Two Pair:
         The two pairs in ascending order as the last 4 elements of the array with element
	 0 being the highest card not in a pair
	 e.g. { 7, 2, 2, 10, 10 }

     2 - Pair:
         Store the single pair in the final two elements of the array and ascending high
	 cards in all lower elements
	 e.g. { 2, 4, 6, 5, 5 }

     1- High Card:
         Return the highest face value cards in ascending order

  */
  int bestFace[5];
  int bestSuit[5];
  long long int handPrimeRank; // Prime product of 5 card hand
  
  // Constructor for initial variables
  // NOTE: Initial values for all face values set to -1 which signifies no hand.
  hand() {
    isCards_ = false; // On initialisation we haven't read the cards in

    // Also, on initialisation we do not have a hand
    handCode = -1;
    handPrimeRank = -1;

    for (int i=0; i<5; i++) {
      bestFace[i] = -1;
      bestSuit[i] = -1;
    }
  }

  /*
    Set the cards in the hand, first using routines faster in pure C++ and secondly
    with routines that are faster when wrapped with Python
  */
  
  // Set the cards private array from a full ARRAYS
  int ASetCardsFull(int cards_in[2][7]);
  // Or for the ARRAYS split into hole, flop, turn and river
  int ASetCards(int hole[2][2], int flop[2][3], int turn[2][1], int river[2][1]);

  // Set the cards using VECTORS
  int SetCardsFull(std::vector<int> face_in, std::vector<int> suit_in);
  int SetCards(std::vector<int> hole_F, std::vector<int> hole_S, std::vector<int> flop_F,
		std::vector<int> flop_S, int turn_F, int turn_S, int river_F, int river_S);
  
  // Get the best hand that can be made from the current cards in cards_face_ and cards_suit_
  int findBestHand();  // Find and populate the best hand and populate bestFace_ and bestSuit_
  int findBestHandP(); // Find best hand code using the prime method

  // Sort the cardsFace_ and cardsSuit_ arrays such cardsFace_ is in ascending order
  void sortCards();

  // Check for a straight and return the high card of the straight or -1 for no straight
  int getStraight(int S_cards[], int hand_size);

  // Get variables from the class
  std::vector<int> getCardsFace();
  std::vector<int> getCardsSuit();
  std::vector<int> getCardsFaceP();
  std::vector<int> getCardsSuitP();
  std::vector<int> getCardsFullP();
  std::vector<int> getBestFace();
  std::vector<int> getBestSuit();
  int getHandCode();
  int getHandPrimeRank();
  
};

#endif
