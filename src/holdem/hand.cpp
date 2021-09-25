#include <iostream>
#include <algorithm>

#include "hand.h"





// Assign the hand, including some minor error checks of the cards formats
// Do this from the full hand as single array
int hand::setCards(int cards[2][7])
{

  /*
    Error Codes
    ===========
        -1 ::: Invalid card face value outside range of [1,14] given as an input.
        -2 ::: Invalid card suit value outside range of [1,4] given as an input.
  */
  
  // Check each card for errors in face or suit value
  for ( int i=0 ; i<7 ; i++ ) {
    
    // If card value is 1, i.e. ace, then switch this to a 14
    // Also check for invalid card face value
    // Using switch as it's a bit more verbose but slightly more efficient
    // than a few if statements
    switch(cards[0][i]) {
    case 1 : cards_face_[i] = 14; break;
    case 2 : cards_face_[i] =  2; break;
    case 3 : cards_face_[i] =  3; break;
    case 4 : cards_face_[i] =  4; break;
    case 5 : cards_face_[i] =  5; break;
    case 6 : cards_face_[i] =  6; break;
    case 7 : cards_face_[i] =  7; break;
    case 8 : cards_face_[i] =  8; break;
    case 9 : cards_face_[i] =  9; break;
    case 10: cards_face_[i] = 10; break;
    case 11: cards_face_[i] = 11; break;
    case 12: cards_face_[i] = 12; break;
    case 13: cards_face_[i] = 13; break;
    case 14: cards_face_[i] = 14; break;
    default: return -1; // Error code -1
    }

    // Check the suit values are valid, i.e. in [1,4]
    if (cards[1][i]!=1 && cards[1][i]!=2 && cards[1][i]!=3 && cards[1][i]!=4) {
      return -2; // Error code -2
    } else {
      cards_suit_[i] = cards[1][i];
    }
    
  }

  // We have now read the cards in
  isCards_ = true;
  
  // Completed, return success
  return 0;
  
}

// Assign the hand, including some minor error checks of the cards formats
// Do this from the full hand as single array
int hand::setCards(int hole[2][2], int flop[2][3], int turn[2][1], int river[2][1])
{

  /*
    Error Codes
    ===========
        -1 ::: Invalid card face value outside range of [1,14] given as an input.
        -2 ::: Invalid card suit value outside range of [1,4] given as an input.
  */

  int tmp_face;
  int tmp_suit;
    
  // Check each card for errors in face or suit value
  for ( int i=0 ; i<7 ; i++ ) {

    // Set temp values by iterating through the hole, flop, turn and river
    switch(i) {
    case 1: tmp_face= hole[0][0]; tmp_suit= hole[1][0]; break;
    case 2: tmp_face= hole[0][1]; tmp_suit= hole[1][1]; break;
    case 3: tmp_face= flop[0][0]; tmp_suit= flop[1][0]; break;
    case 4: tmp_face= flop[0][1]; tmp_suit= flop[1][1]; break;
    case 5: tmp_face= flop[0][2]; tmp_suit= flop[1][2]; break;
    case 6: tmp_face= turn[0][0]; tmp_suit= turn[1][0]; break;
    case 7: tmp_face=river[0][0]; tmp_suit=river[1][0]; break;
    }
    
    // If card value is 1, i.e. ace, then switch this to a 14
    // Also check for invalid card face value
    // Using switch as it's a bit more verbose but slightly more efficient
    // than a few if statements
    switch(tmp_face) {
    case 1 : cards_face_[i] = 14; break;
    case 2 : cards_face_[i] =  2; break;
    case 3 : cards_face_[i] =  3; break;
    case 4 : cards_face_[i] =  4; break;
    case 5 : cards_face_[i] =  5; break;
    case 6 : cards_face_[i] =  6; break;
    case 7 : cards_face_[i] =  7; break;
    case 8 : cards_face_[i] =  8; break;
    case 9 : cards_face_[i] =  9; break;
    case 10: cards_face_[i] = 10; break;
    case 11: cards_face_[i] = 11; break;
    case 12: cards_face_[i] = 12; break;
    case 13: cards_face_[i] = 13; break;
    case 14: cards_face_[i] = 14; break;
    default: return -1; // Error code -1
    }

    // Check the suit values are valid, i.e. in [1,4]
    if (tmp_suit!=1 && tmp_suit!=2 && tmp_suit!=3 && tmp_suit!=4) {
      return -2; // Error code -2
    } else {
      cards_suit_[i] = tmp_suit;
    }
    
  }

  // We have now read the cards in
  isCards_ = true;
  
  // Completed, return success
  return 0;
  
}






// Get the high card from the current cards_ in the hand
void hand::getHighCard()
{
  
  // After only checking the first card, the first must be the highest
  highCard = cards_face_[0];
  // Now compare this first card baselign highest card value against all others
  for (int i=1; i<7; i++) {
    if (highCard<cards_face_[i]) highCard=cards_face_[i];
  }
  // And we have our high card face value
  
}





// Check if the hand contains a pair, if so record the pair in hasPair boolean
// also record the face value of the highest pair.
// Note : We check only for pairs, so though a three of a kind contains a pair
//        this function will not find it.
void hand::getPair()
{
  
  int numFace; // Number of cards of this face value in hand
  for (int i=0; i<7; i++) {
    // Count the number of occurences of the face value of the ith card in the had
    numFace = std::count(cards_face_, cards_face_+7, cards_face_[i]);
    // If the ith card is part of a pair, and higher than any other pair write to output
    // NOTE: We consider any pair, including that part of 3 of a kind as a pair
    if (numFace == 2 && cards_face_[i] > pairVal) {
      hasPair = true;           // We have a pair!
      pairVal = cards_face_[i]; // With this face value!
    }
  }
  
}





// Check if the hand has two pair in it, if so record the two pair in hasTwoPair boolean
// also record the face values of the two pair, highest and lowest
void hand::getTwoPair()
{
  
  // First check for a single pair, as we need at least one pair to have two pair
  getPair();
  // So only check if we have at least a pair
  if (hasPair==true) {
    // Now check for a pair that is not the pair found by getPair()
  
    int numFace;       // Number of cards of this face value in hand

    for (int i=0; i<7; i++) {
      // Count the number of occurences of the face value of the ith card in the had
      numFace = std::count(cards_face_, cards_face_+7, cards_face_[i]);    
      if (numFace == 2 && cards_face_[i] > twoPairLow && cards_face_[i] != pairVal) {
	hasTwoPair = true;           // We have another (lower valued) pair!
        twoPairLow = cards_face_[i]; // With this face value!
      }
    }
    
    // If we have two pair copy over the higher value from initial pair search and find
    // remaining high card value
    if(hasTwoPair==true) {
      twoPairHigh = pairVal;
      for (int i=0; i<7; i++) {
	if (twoPairHighCard<cards_face_[i] && cards_face_[i]!=twoPairHigh && cards_face_[i]!=twoPairLow) {
	  // Save the highest card not in a pair
	  twoPairHighCard=cards_face_[i];
	}
      }
    }
    
  } 
}







// Sort the cards_face_ array such that it is in ascending order
// Also sort cards_suit_ into the same order as cards_face_ such that each
// ith element of cards_suit_ is the suit of the ith card in cards_face_
void hand::sortCards()
{

  std::pair<int, int> cards_face_suit[7];
  for (int i = 0; i < 7; i++) {
    cards_face_suit[i].first  = cards_face_[i];
    cards_face_suit[i].second = cards_suit_[i];
  }
  sort(cards_face_suit, cards_face_suit + 7);
  for (int i = 0; i < 7; i++) {
    cards_face_[i] = cards_face_suit[i].first;
    cards_suit_[i] = cards_face_suit[i].second;
  }
  
}







int hand::getBestHand()
{

  // Routine variables
  bool gotStraight=false;
  int  straightHighCard=-1;
  bool gotFlush   =false;
  int  flushCards[5];
  int  flushSuit;

  // Number of cards in each suit
  int num_suit_1;
  int num_suit_2;
  int num_suit_3;
  int num_suit_4;
  
  // The first step is to sort the cards in the hand into ascending order
  sortCards();


  /*
    Check for a straight
  */
  
  int straight_tmp=0;
  int straight_dif;
  // If the hand contains an ace and lowest face is a 2 we must also consider a straight 
  // containing Ace then 2, so we have one subsiquent pair before looping if this is the case
  if ( cards_face_[0]==2 && cards_face_[6]==14 ) straight_tmp=1;
  
  // Iterate through the hand checking for a straight of any suit, only check difference between
  // subsiquent cards, 4 subsiquent pairs
  for (int i=0; i<6; i++) {
    
    // Check difference between adjacent cards sorted by face value
    straight_dif = cards_face_[i+1] - cards_face_[i];
    // If straight_diff==0 then face values are the same, so ignore
    // If straight_diff==1 then we have two subsiquent face values so iterate
    // If straight_diff>1 then non subsiquent face values so reset
    if (straight_dif==1) {
      straight_tmp++;
    } else if (straight_dif>1) {
      straight_tmp=0;
    }

    // If straight_tmp>=4 we have a stright!
    if (straight_tmp>3) {
      gotStraight = true;
      straightHighCard = cards_face_[i+1];
    }
    
  }
  
  return 0;
  
}



