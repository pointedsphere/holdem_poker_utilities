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






// // Get the high card from the current cards_ in the hand
// void hand::getHighCard()
// {
  
//   // After only checking the first card, the first must be the highest
//   highCard = cards_face_[0];
//   // Now compare this first card baselign highest card value against all others
//   for (int i=1; i<7; i++) {
//     if (highCard<cards_face_[i]) highCard=cards_face_[i];
//   }
//   // And we have our high card face value
  
// }





// // Check if the hand contains a pair, if so record the pair in hasPair boolean
// // also record the face value of the highest pair.
// // Note : We check only for pairs, so though a three of a kind contains a pair
// //        this function will not find it.
// void hand::getPair()
// {
  
//   int numFace; // Number of cards of this face value in hand
//   for (int i=0; i<7; i++) {
//     // Count the number of occurences of the face value of the ith card in the had
//     numFace = std::count(cards_face_, cards_face_+7, cards_face_[i]);
//     // If the ith card is part of a pair, and higher than any other pair write to output
//     // NOTE: We consider any pair, including that part of 3 of a kind as a pair
//     if (numFace == 2 && cards_face_[i] > pairVal) {
//       hasPair = true;           // We have a pair!
//       pairVal = cards_face_[i]; // With this face value!
//     }
//   }
  
// }





// // Check if the hand has two pair in it, if so record the two pair in hasTwoPair boolean
// // also record the face values of the two pair, highest and lowest
// void hand::getTwoPair()
// {
  
//   // First check for a single pair, as we need at least one pair to have two pair
//   getPair();
//   // So only check if we have at least a pair
//   if (hasPair==true) {
//     // Now check for a pair that is not the pair found by getPair()
  
//     int numFace;       // Number of cards of this face value in hand

//     for (int i=0; i<7; i++) {
//       // Count the number of occurences of the face value of the ith card in the had
//       numFace = std::count(cards_face_, cards_face_+7, cards_face_[i]);    
//       if (numFace == 2 && cards_face_[i] > twoPairLow && cards_face_[i] != pairVal) {
// 	hasTwoPair = true;           // We have another (lower valued) pair!
//         twoPairLow = cards_face_[i]; // With this face value!
//       }
//     }
    
//     // If we have two pair copy over the higher value from initial pair search and find
//     // remaining high card value
//     if(hasTwoPair==true) {
//       twoPairHigh = pairVal;
//       for (int i=0; i<7; i++) {
// 	if (twoPairHighCard<cards_face_[i] && cards_face_[i]!=twoPairHigh && cards_face_[i]!=twoPairLow) {
// 	  // Save the highest card not in a pair
// 	  twoPairHighCard=cards_face_[i];
// 	}
//       }
//     }
    
//   } 
// }







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





int hand::getStraight(int S_cards[], int hand_size)
{

  int straight_tmp=0;
  int straight_dif;
  bool gotStraight=false;
  int straightHighCard;
  // If the hand contains an ace and lowest face is a 2 we must also consider a straight 
  // containing Ace then 2, so we have one subsiquent pair before looping if this is the case
  if ( S_cards[0]==2 && S_cards[hand_size-1]==14 ) straight_tmp=1;
  
  // Iterate through the hand checking for a straight of any suit, only check difference between
  // subsiquent cards, >=4 subsiquent pairs means a straight
  for (int i=0; i<hand_size-1; i++) {
    
    // Check difference between adjacent cards sorted by face value
    straight_dif = S_cards[i+1] - S_cards[i];
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
      straightHighCard = S_cards[i+1];
    }
    
  }

  if (gotStraight==false) {
    return -1;
  } else {
    return straightHighCard;
  }
  
}






int hand::getBestHand()
{

  // NOTE: A -1 as an integer variable means the hand in question has not been found

  
  
  // Routine variables

  // Straight info
  bool gotStraight=false;   // Do we have a straight
  int  straightHighCard=-1; // What's the highest card in the straight
  bool aceInStraight = false;
  
  // Flush info
  bool gotFlush =false; // Do we have a flush
  int  flushSize=-1; // Number of cards in the flush
  int  flushSuit=-1; // The suit of the flush
  // All the cards in the flush, will only contain flushSize non -1 values in the
  // first flushsize elements
  int  flushCards[7]={-1,-1,-1,-1,-1,-1,-1};

  // Straight flush info
  int straightFlushHighCard;

  // Four of a kind values
  int fourOfAKind4; // The value of the four of a kind in four of a kind

  // Three of a kind values
  int threeOfAKindFace;
  int threeOfAKindSuit[3];

  // Two Pair Values
  int twoPairLowFace;
  int twoPairLowSuit;
  int twoPairHighFace;
  int twoPairHighSuit;

  // Pair values
  int pairFace;
  int pairSuit;
  
  // Number of cards of each face value
  int  faceValCount[7];
  bool gotFourOfAKind  = false;
  bool gotThreeOfAKind = false;
  bool gotTwoPair      = false;
  bool gotPair         = false;

  
  // The first step is to sort the cards in the hand into ascending order
  sortCards();



  /*
    Check for a straight, we retrun to more calcualtions when we have checked more hands
  */
  straightHighCard = getStraight(cards_face_,7);
  if (straightHighCard>0) {
    gotStraight = true;
    if (straightHighCard==5) {
      // If the high card in a straight is a 5 then the low card is an ace
      aceInStraight = true;
    }
  }



  /*
    Check for a flush briefly, we return to more calcualtions when we have checked higher hands
  */

  int flush_tmp;
  int flush_i=0;
  for (int i=1; i<5; i++) {
    // Count number of cards of the ith suit
    flush_tmp = std::count(cards_suit_, cards_suit_+7, i);
    if (flush_tmp>4) {
      // If there are at least 5 of a given suit in a hand we have a flush
      gotFlush  = true;
      flushSuit = i;
      flushSize = flush_tmp;
      // Record all cards of the suit with the flush
      for (int j=0; j<7; j++) {
	if (cards_suit_[j]==flushSuit) {
	  flushCards[flush_i] = cards_face_[j];
	  flush_i++;
	}
      }
      break; // Can only have one flush, so may as well stop here
    }
  }


  
  /*
    Check for Straight/Royal flush
    NOTE: If we have a straight or royal flush we exit after this if statement
  */

  // Only bother checking for this if we have both a straight and a flush
  if (gotStraight==true && gotFlush==true) {
    int straightFlush_i=4;
    
    // Check the face values of the cards that are the suit of the flush for a straight
    straightFlushHighCard = getStraight(flushCards,flushSize);

    // If there is a straight in the flush cards we have a straight flush
    if (straightFlushHighCard>0) {

      if (straightFlushHighCard==14) {
	// If the high card of the flush straight is an ace we have a royal flush !!!
	hand_code = 10;

      } else {
	// Otherwise we just have a stright flush, still pretty good
	hand_code = 9;
      }

      // Copy over the cards from the stright to the best face/suit
      for (int i=flushSize-1; i>-1; i--) {
	// Note only copy over elements of the flush that are also in the straight
	// This accounts for 6 or 7 cards of same suit in hand
	if (flushCards[i] <= straightFlushHighCard && flushCards[i]>0) {
	  best_face[straightFlush_i] = flushCards[i];
	  best_suit[straightFlush_i] = flushSuit;
	  straightFlush_i--;
	  if (straightFlush_i==-1) break;
	}
      }

      return 0; // No point in checking for any lower hands, we have one of the two best hands
      
    }
        
  }



  /*
    Count the number of occurences of each face value in hand
    This gives info for Four of a kind, full house, three of a kind
    pair and two pair.
  */

  int suit3_i=0;
  for (int i=0; i<7; i++) {
    // Count number of times face value of current card appears in the current hand
    faceValCount[i] = std::count(cards_face_, cards_face_+7, cards_face_[i]);
    if (faceValCount[i]==4) {
      gotFourOfAKind  = true;           // We have 4 of a kind, pretty good!
      fourOfAKind4    = cards_face_[i]; // The face value of the four of a kind
    }
    if (faceValCount[i]==3) {
      if (cards_face_[i]!=threeOfAKindFace) suit3_i=0;
      gotThreeOfAKind           = true;           // Got three of a kind
      threeOfAKindFace          = cards_face_[i]; // Save the face val  of highest 3 of a kind
      threeOfAKindSuit[suit3_i] = cards_suit_[i]; // Save the suit vals of highest 3 of a kind
      suit3_i++;
    }
    if (faceValCount[i]==2) {
      // If we haven't seen a pair before we only have one pair (so far)
      // if we have we have two pair
      if (gotPair==false) {
	gotPair = true;
	pairFace = cards_face_[i];
	pairSuit = cards_face_[i];
      } else {
	gotTwoPair = true;
	twoPairLowFace = pairFace;
	twoPairLowSuit = pairSuit;
	pairFace = cards_face_[i];
	pairSuit = cards_suit_[i];
	twoPairHighFace = pairFace;
	twoPairHighSuit = pairSuit;
      }
    }
  }
  


  /*
    Four of a kind check
  */

  // Find the value of the spare card if we have 4 of a kind
  if (gotFourOfAKind==true) {
    // Copy out the four of a kind face values, we must have one of each suit so don't bother checking
    for (int i=1; i<5; i++) {
      best_face[i] = fourOfAKind4;
      best_suit[i] = i;
    }
    // Go backwards down the array, until we find the highest card that isn't the one
    // that is part of four of a kind
    for (int i=0; i<7; i++) {
      if (cards_face_[6-i]!=fourOfAKind4) {
        best_face[0] = cards_face_[6-i];
	best_suit[0] = cards_suit_[6-i];
	break;
      }
    }
    hand_code = 8;
    return 0; // We have 4 of a kind, no need to keep checking
  }
  


  /*
    Full house check
  */

  // We can check this from only the three of a kind and two pair
  if (gotThreeOfAKind==true && gotPair==true) {
    int fullHouse_i=0;
    // First copy over the three of a kind to best hand
    for (int i=0; i<3; i++) {
      best_face[i+2] = threeOfAKindFace;
      best_suit[i+2] = threeOfAKindSuit[i];
    }

    // Now copy over the highest pair, note we must search for the suits
    for (int i=0; i<7; i++) {
      if (cards_face_[i]==pairFace) {
	best_face[fullHouse_i] = cards_face_[i];
	best_suit[fullHouse_i] = cards_suit_[i];
	fullHouse_i++;
	if (fullHouse_i==2) break;
      }
    }
    
    hand_code = 7;
    return 0; // Full house, so we can exit now as we've checked for all better hands
    
  }
  




  /*
    Flush check
  */


  // We have previously checked for a flush, but we've now checked all the better hands
  // so if we have a flush exit with this as the best hand
  if (gotFlush==true) {
    
    int flush_tmp=4;
    for (int i=flushSize-1; i>0; i--) {
      best_face[flush_tmp] = flushCards[i];
      best_suit[flush_tmp] = flushSuit;
      flush_tmp--;
    }

    hand_code = 6;
    return 0;
    
  }


  return 0;
  
}



