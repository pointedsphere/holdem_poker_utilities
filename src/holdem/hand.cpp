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
    case 1 : cards_[0][i] = 14; break;
    case 2 : cards_[0][i] =  2; break;
    case 3 : cards_[0][i] =  3; break;
    case 4 : cards_[0][i] =  4; break;
    case 5 : cards_[0][i] =  5; break;
    case 6 : cards_[0][i] =  6; break;
    case 7 : cards_[0][i] =  7; break;
    case 8 : cards_[0][i] =  8; break;
    case 9 : cards_[0][i] =  9; break;
    case 10: cards_[0][i] = 10; break;
    case 11: cards_[0][i] = 11; break;
    case 12: cards_[0][i] = 12; break;
    case 13: cards_[0][i] = 13; break;
    case 14: cards_[0][i] = 14; break;
    default: return -1; // Error code -1
    }

    // Check the suit values are valid, i.e. in [1,4]
    if (cards[1][i]!=1 && cards[1][i]!=2 && cards[1][i]!=3 && cards[1][i]!=4) {
      return -2; // Error code -2
    } else {
      cards_[1][i] = cards[1][i];
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
  highCard = cards_[0][0];
  // Now compare this first card baselign highest card value against all others
  for (int i=1; i<7; i++) {
    if (highCard<cards_[0][i]) highCard=cards_[0][i];
  }
  // And we have our high card face value
}





