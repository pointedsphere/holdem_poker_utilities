#include <iostream>
#include <algorithm>

#include "hand.h"





// Assign the hand, including some minor error checks of the cards formats
int hand::setCards(int cards[2][7])
{

  /*
    Error Codes
    ===========
    - -1 ::: Invalid card face value outside range of [1,14] given as input.
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
// Note : We check each face value as this is slightly more cost effective than
//        using if statements to avoid checking each card for a pair and possibly 
//        doubling up the checks as there are only 7 cards.
void hand::getPairVal()
{
  int numFace; // Number of cards of this face value in hand
  for (int i=0; i<7; i++) {
    // Count the number of occurences of the face value of the ith card in the had
    numFace = std::count(cards_face_, cards_face_+7, cards_face_[i]);
    // If the ith card is part of a pair, and higher than any other pair write to output
    // NOTE: We consider any pair, including that part of 3 of a kind as a pair
    if (numFace > 1 && cards_face_[i] > pairVal) {
      hasPair = true;           // We have a pair!
      pairVal = cards_face_[i]; // With this face value!
    }
  }
}

