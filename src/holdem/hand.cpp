#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>

#include "deck.h"
#include "hand.h"
#include "../../machine_gen_code/lookupBestHandPrimes.h"
// #include "../../machine_gen_code/switchBestHandPrimes.h"




/*
  Routines to set class variables
*/



int hand::ASetCardsFull(int cards_in[2][7])
{

  /*
    Set the hands cards from an input ARRAY that contains
        card_in[0][:] :: The face values of the ith cards
	card_in[1][:] :: The suit values of the ith cards

    Though some error checks are carried out the length of input arrays is not checked, this is
    as we wish to reduce cost as much as possible. Therefore, care must be taken when calling 
    this function as giving arrays of less than 7 may cause unexpected results.

    Returns
    =======
      Error codes returned from function, 0 means everything ran smoothly.
        -1 ::: Invalid card face value outside range of [1,14] given as an input.
        -2 ::: Invalid card suit value outside range of [1,4] given as an input.
  */
  
  // Check each card for errors in face or suit value
  for ( int i=0 ; i<7 ; i++ ) {
    
    // If card value is 1, i.e. ace, then switch this to a 14
    // Also check for invalid card face value
    // Using switch as it's a bit more verbose but slightly more efficient
    // than a few if statements
    switch(cards_in[0][i]) {
    case 1 : cardsFace_[i] = 14; break;
    case 2 : cardsFace_[i] =  2; break;
    case 3 : cardsFace_[i] =  3; break;
    case 4 : cardsFace_[i] =  4; break;
    case 5 : cardsFace_[i] =  5; break;
    case 6 : cardsFace_[i] =  6; break;
    case 7 : cardsFace_[i] =  7; break;
    case 8 : cardsFace_[i] =  8; break;
    case 9 : cardsFace_[i] =  9; break;
    case 10: cardsFace_[i] = 10; break;
    case 11: cardsFace_[i] = 11; break;
    case 12: cardsFace_[i] = 12; break;
    case 13: cardsFace_[i] = 13; break;
    case 14: cardsFace_[i] = 14; break;
    default: return -1; // Error code -1
    }

    // Check the suit values are valid, i.e. in [1,4]
    if (cards_in[1][i]!=1 && cards_in[1][i]!=2 && cards_in[1][i]!=3 && cards_in[1][i]!=4) {
      return -2; // Error code -2
    } else {
      cardsSuit_[i] = cards_in[1][i];
    }
    
  }

  // We have now read the cards in
  isCards_ = true;
  
  // Completed, return success
  return 0;
  
}



int hand::SetCardsFull(std::vector<int> face_in, std::vector<int> suit_in)
{

  /*
    Set the hand cards using two input VECTORS, this routine takes in one vector of the
    face values and one of the respective suit values.

    Though some error checks are carried out the length of input vectors is not checked, 
    this is as we wish to reduce cost as much as possible. Therefore, care must be taken 
    when calling this function as giving arrays of less than 7 may cause unexpected results.

    Error Codes
    ===========
      Error codes returned from function, 0 means everything ran smoothly.
        -1 ::: Invalid card face value outside range of [1,14] given as an input.
        -2 ::: Invalid card suit value outside range of [1,4] given as an input.
  */

  // Temporary vector for setting the prime values
  std::vector<int> setTmp;
  
  // Check each card for errors in face or suit value
  for ( int i=0 ; i<7 ; i++ ) {
    
    // If card value is 1, i.e. ace, then switch this to a 14
    // Also check for invalid card face value
    // Using switch as it's a bit more verbose but slightly more efficient
    // than a few if statements
    switch(face_in[i]) {
    case 1 : cardsFace_[i] = 14; break;
    case 2 : cardsFace_[i] =  2; break;
    case 3 : cardsFace_[i] =  3; break;
    case 4 : cardsFace_[i] =  4; break;
    case 5 : cardsFace_[i] =  5; break;
    case 6 : cardsFace_[i] =  6; break;
    case 7 : cardsFace_[i] =  7; break;
    case 8 : cardsFace_[i] =  8; break;
    case 9 : cardsFace_[i] =  9; break;
    case 10: cardsFace_[i] = 10; break;
    case 11: cardsFace_[i] = 11; break;
    case 12: cardsFace_[i] = 12; break;
    case 13: cardsFace_[i] = 13; break;
    case 14: cardsFace_[i] = 14; break;
    default: return -1; // Error code -1
    }

    // Check the suit values are valid, i.e. in [1,4]
    if (suit_in[i]!=1 && suit_in[i]!=2 && suit_in[i]!=3 && suit_in[i]!=4) {
      return -2; // Error code -2
    } else {
      cardsSuit_[i] = suit_in[i];
    }
    
  }
  
  // We have now read the cards in
  isCards_ = true;
  
  // Completed, return success
  return 0;
  
}



int hand::SetCardsFullP(std::vector<int> face_in, std::vector<int> suit_in, std::vector<int> full_in)
{

  /*
    Set the hand cards using two input VECTORS, this routine takes in one vector of the
    face values and one of the respective suit values.

    This routine sets only the prime card values in the hand based on the prime inputs.

    Though some error checks are carried out the length of input vectors is not checked, 
    this is as we wish to reduce cost as much as possible. Therefore, care must be taken 
    when calling this function as giving arrays of less than 7 may cause unexpected results.

    Error Codes
    ===========
      Error codes returned from function, 0 means everything ran smoothly.
        -1 ::: Invalid card face value outside range of [1,14] given as an input.
        -2 ::: Invalid card suit value outside range of [1,4] given as an input.
  */

  // Temporary vector for setting the prime values
  std::vector<int> setTmp;
  
  // Check each card for errors in face or suit value
  for ( int i=0 ; i<7 ; i++ ) {
    
    // If card value is 1, i.e. ace, then switch this to a 14
    // Also check for invalid card face value
    // Using switch as it's a bit more verbose but slightly more efficient
    // than a few if statements
    switch(face_in[i]) {
    case 2 : cardsFaceP_[i] = 2 ; break;
    case 3 : cardsFaceP_[i] = 3 ; break;
    case 5 : cardsFaceP_[i] = 5 ; break;
    case 7 : cardsFaceP_[i] = 7 ; break;
    case 11: cardsFaceP_[i] = 11; break;
    case 13: cardsFaceP_[i] = 13; break;
    case 17: cardsFaceP_[i] = 17; break;
    case 19: cardsFaceP_[i] = 19; break;
    case 23: cardsFaceP_[i] = 23; break;
    case 29: cardsFaceP_[i] = 29; break;
    case 31: cardsFaceP_[i] = 31; break;
    case 37: cardsFaceP_[i] = 37; break;
    case 41: cardsFaceP_[i] = 41; break;
    default: return -1; // Error code -1
    }

    // Check the suit values are valid, i.e. in [1,4]
    if (suit_in[i]!=2 && suit_in[i]!=3 && suit_in[i]!=5 && suit_in[i]!=7) {
      return -2; // Error code -2
    } else {
      cardsSuit_[i] = suit_in[i];
    }

    // And set the full prime value
    cardsFullP_[i] = full_in[i];
    
  }
  
  // We have now read the cards in
  isCards_ = true;
  
  // Completed, return success
  return 0;
  
}





int hand::SetCardsFullA(std::vector<int> face_in, std::vector<int> suit_in)
{

  /*
    Set the hand cards using two input VECTORS, this routine takes in one vector of the
    face values and one of the respective suit values.

    This takes in standard face and hand vlaues but also calcualtes the prime values and
    also sets them.

    Though some error checks are carried out the length of input vectors is not checked, 
    this is as we wish to reduce cost as much as possible. Therefore, care must be taken 
    when calling this function as giving arrays of less than 7 may cause unexpected results.

    Error Codes
    ===========
      Error codes returned from function, 0 means everything ran smoothly.
        -1 ::: Invalid card face value outside range of [1,14] given as an input.
        -2 ::: Invalid card suit value outside range of [1,4] given as an input.
  */

  // Temporary vector for setting the prime values
  std::vector<int> setTmp;
  
  // Check each card for errors in face or suit value
  for ( int i=0 ; i<7 ; i++ ) {
    
    // If card value is 1, i.e. ace, then switch this to a 14
    // Also check for invalid card face value
    // Using switch as it's a bit more verbose but slightly more efficient
    // than a few if statements
    switch(face_in[i]) {
    case 1 : cardsFace_[i] = 14; break;
    case 2 : cardsFace_[i] =  2; break;
    case 3 : cardsFace_[i] =  3; break;
    case 4 : cardsFace_[i] =  4; break;
    case 5 : cardsFace_[i] =  5; break;
    case 6 : cardsFace_[i] =  6; break;
    case 7 : cardsFace_[i] =  7; break;
    case 8 : cardsFace_[i] =  8; break;
    case 9 : cardsFace_[i] =  9; break;
    case 10: cardsFace_[i] = 10; break;
    case 11: cardsFace_[i] = 11; break;
    case 12: cardsFace_[i] = 12; break;
    case 13: cardsFace_[i] = 13; break;
    case 14: cardsFace_[i] = 14; break;
    default: return -1; // Error code -1
    }

    // Check the suit values are valid, i.e. in [1,4]
    if (suit_in[i]!=1 && suit_in[i]!=2 && suit_in[i]!=3 && suit_in[i]!=4) {
      return -2; // Error code -2
    } else {
      cardsSuit_[i] = suit_in[i];
    }

    // Get the prime values of the current card
    setTmp = card2prime(cardsFace_[i],cardsSuit_[i]);
    cardsFaceP_[i] = setTmp[0];
    cardsSuitP_[i] = setTmp[1];
    cardsFullP_[i] = setTmp[2];
    
  }
  
  // We have now read the cards in
  isCards_ = true;
  
  // Completed, return success
  return 0;
  
}


int hand::ASetCards(int hole[2][2], int flop[2][3], int turn[2][1], int river[2][1])
{

  /*
    Assign the hand from 4 input ARRAYS that contain the hole, flop, turn and river cards.
    The 0 row of each array contains the face values and the 1 row contains their respective
    suit values.

    This routine also carries out some basic input error checks, but not thourogh ones as it
    will likely be called multiple times so we need to minimise cost. Note the sizes of input 
    arrays is not checked (for cost reasons) so we must ensure that the correct sizes arrays
    are given as inputs otherwise unusual behaviour may result.

    Returns
    =======
      Error codes returned from function, 0 means everything ran smoothly.
        -1 ::: Invalid card face value outside range of [1,14] given as an input.
        -2 ::: Invalid card suit value outside range of [1,4] given as an input.
  */

  int tmp_face;
  int tmp_suit;
    
  // Check each card for errors in face or suit value
  for ( int i=0 ; i<7 ; i++ ) {

    // Set temp values by iterating through the hole, flop, turn and river
    switch(i) {
    case 0: tmp_face= hole[0][0]; tmp_suit= hole[1][0]; break;
    case 1: tmp_face= hole[0][1]; tmp_suit= hole[1][1]; break;
    case 2: tmp_face= flop[0][0]; tmp_suit= flop[1][0]; break;
    case 3: tmp_face= flop[0][1]; tmp_suit= flop[1][1]; break;
    case 4: tmp_face= flop[0][2]; tmp_suit= flop[1][2]; break;
    case 5: tmp_face= turn[0][0]; tmp_suit= turn[1][0]; break;
    case 6: tmp_face=river[0][0]; tmp_suit=river[1][0]; break;
    }
    
    // If card value is 1, i.e. ace, then switch this to a 14
    // Also check for invalid card face value
    // Using switch as it's a bit more verbose but slightly more efficient
    // than a few if statements
    switch(tmp_face) {
    case 1 : cardsFace_[i] = 14; break;
    case 2 : cardsFace_[i] =  2; break;
    case 3 : cardsFace_[i] =  3; break;
    case 4 : cardsFace_[i] =  4; break;
    case 5 : cardsFace_[i] =  5; break;
    case 6 : cardsFace_[i] =  6; break;
    case 7 : cardsFace_[i] =  7; break;
    case 8 : cardsFace_[i] =  8; break;
    case 9 : cardsFace_[i] =  9; break;
    case 10: cardsFace_[i] = 10; break;
    case 11: cardsFace_[i] = 11; break;
    case 12: cardsFace_[i] = 12; break;
    case 13: cardsFace_[i] = 13; break;
    case 14: cardsFace_[i] = 14; break;
    default: return -1; // Error code -1
    }

    // Check the suit values are valid, i.e. in [1,4]
    if (tmp_suit!=1 && tmp_suit!=2 && tmp_suit!=3 && tmp_suit!=4) {
      return -2; // Error code -2
    } else {
      cardsSuit_[i] = tmp_suit;
    }
    
  }

  // We have now read the cards in
  isCards_ = true;
  
  // Completed, return success
  return 0;
  
}



int hand::SetCards(std::vector<int> hole_F, std::vector<int> hole_S, std::vector<int> flop_F,
		std::vector<int> flop_S, int turn_F, int turn_S, int river_F, int river_S)
{

  /*
    Assign the hand from VECTORS containing the hole and flop cards (one for the face _F and
    the other for the suit _S values, with each ith element of each vector referencing the
    same card. The turn and river are set with an integer, with one for the face value and the
    other for the suit.
  
    This routine also carries out some basic input error checks, but not thourogh ones as it
    will likely be called multiple times so we need to minimise cost. Note the sizes of input 
    vectors is not checked (for cost reasons) so we must ensure that the correct sizes arrays
    are given as inputs otherwise unusual behaviour may result.

    Error Codes
    ===========
      Error codes returned from function, 0 means everything ran smoothly.
        -1 ::: Invalid card face value outside range of [1,14] given as an input.
        -2 ::: Invalid card suit value outside range of [1,4] given as an input.
  */

  // Temporary vector for setting the prime values
  std::vector<int> setTmp;
  int tmp_face;
  int tmp_suit;
  
  // Error check for the size ofo the input vectors
  if (hole_F.size()!=2) {
    std::cout << "ERROR : Vector input hole_F to SetCards of incorrect size" << std::endl;
    exit (EXIT_FAILURE);
  } else if (hole_S.size()!=2) {
    std::cout << "ERROR : Vector input hole_S to SetCards of incorrect size" << std::endl;
    exit (EXIT_FAILURE);
  } else if (flop_F.size()!=3) {
    std::cout << "ERROR : Vector input flop_F to SetCards of incorrect size" << std::endl;
    exit (EXIT_FAILURE);
  } else if (flop_S.size()!=3) {
    std::cout << "ERROR : Vector input flop_S to SetCards of incorrect size" << std::endl;
    exit (EXIT_FAILURE);
  }
  
  // Check each card for errors in face or suit value
  for ( int i=0 ; i<7 ; i++ ) {

    // Set temp values by iterating through the hole, flop, turn and river
    switch(i) {
    case 0: tmp_face= hole_F[0]; tmp_suit= hole_S[0]; break;
    case 1: tmp_face= hole_F[1]; tmp_suit= hole_S[1]; break;
    case 2: tmp_face= flop_F[0]; tmp_suit= flop_S[0]; break;
    case 3: tmp_face= flop_F[1]; tmp_suit= flop_S[1]; break;
    case 4: tmp_face= flop_F[2]; tmp_suit= flop_S[2]; break;
    case 5: tmp_face= turn_F;    tmp_suit= turn_S;    break;
    case 6: tmp_face=river_F;    tmp_suit=river_S;    break;
    }
    
    // If card value is 1, i.e. ace, then switch this to a 14
    // Also check for invalid card face value
    // Using switch as it's a bit more verbose but slightly more efficient
    // than a few if statements
    switch(tmp_face) {
    case 1 : cardsFace_[i] = 14; break;
    case 2 : cardsFace_[i] =  2; break;
    case 3 : cardsFace_[i] =  3; break;
    case 4 : cardsFace_[i] =  4; break;
    case 5 : cardsFace_[i] =  5; break;
    case 6 : cardsFace_[i] =  6; break;
    case 7 : cardsFace_[i] =  7; break;
    case 8 : cardsFace_[i] =  8; break;
    case 9 : cardsFace_[i] =  9; break;
    case 10: cardsFace_[i] = 10; break;
    case 11: cardsFace_[i] = 11; break;
    case 12: cardsFace_[i] = 12; break;
    case 13: cardsFace_[i] = 13; break;
    case 14: cardsFace_[i] = 14; break;
    default: return -1; // Error code -1
    }

    // Check the suit values are valid, i.e. in [1,4]
    if (tmp_suit!=1 && tmp_suit!=2 && tmp_suit!=3 && tmp_suit!=4) {
      return -2; // Error code -2
    } else {
      cardsSuit_[i] = tmp_suit;
    }
    
  }

  // We have now read the cards in
  isCards_ = true;
  
  // Completed, return success
  return 0;
  
}




int hand::SetCardsP(std::vector<int> hole_F, std::vector<int> hole_S, std::vector<int> hole_A, \
		    std::vector<int> flop_F, std::vector<int> flop_S, std::vector<int> flop_A, \
		    int turn_F,  int turn_S,  int turn_A, \
		    int river_F, int river_S, int river_A )
{

  /*
    Assign the hand from VECTORS containing the hole and flop cards (one for the face _F and
    the other for the suit _S values, with each ith element of each vector referencing the
    same card. The turn and river are set with an integer, with one for the face value and the
    other for the suit.
  
    Only set the prime card values in the hand, based on all the inputs, which must be of the
    prime values only

    This routine also carries out some basic input error checks, but not thourogh ones as it
    will likely be called multiple times so we need to minimise cost. Note the sizes of input 
    vectors is not checked (for cost reasons) so we must ensure that the correct sizes arrays
    are given as inputs otherwise unusual behaviour may result.

    Error Codes
    ===========
      Error codes returned from function, 0 means everything ran smoothly.
        -1 ::: Invalid card face value outside range of [1,14] given as an input.
        -2 ::: Invalid card suit value outside range of [1,4] given as an input.
  */

  // Temporary vector for setting the prime values
  std::vector<int> setTmp;
  int tmp_face;
  int tmp_suit;
  int tmp_full;
  
  // Error check for the size ofo the input vectors
  if (hole_F.size()!=2) {
    std::cout << "ERROR : Vector input hole_F to SetCardsP of incorrect size" << std::endl;
    exit (EXIT_FAILURE);
  } else if (hole_S.size()!=2) {
    std::cout << "ERROR : Vector input hole_S to SetCardsP of incorrect size" << std::endl;
    exit (EXIT_FAILURE);
  } else if (hole_A.size()!=2) {
    std::cout << "ERROR : Vector input hole_A to SetCardsP of incorrect size" << std::endl;
    exit (EXIT_FAILURE);
  } else if (flop_F.size()!=3) {
    std::cout << "ERROR : Vector input flop_F to SetCardsP of incorrect size" << std::endl;
    exit (EXIT_FAILURE);
  } else if (flop_S.size()!=3) {
    std::cout << "ERROR : Vector input flop_S to SetCardsP of incorrect size" << std::endl;
    exit (EXIT_FAILURE);
  } else if (flop_A.size()!=3) {
    std::cout << "ERROR : Vector input flop_A to SetCardsP of incorrect size" << std::endl;
    exit (EXIT_FAILURE);
  }
  
  // Check each card for errors in face or suit value
  for ( int i=0 ; i<7 ; i++ ) {

    // Set temp values by iterating through the hole, flop, turn and river
    switch(i) {
    case 0: tmp_face= hole_F[0]; tmp_suit= hole_S[0]; tmp_full= hole_A[0]; break;
    case 1: tmp_face= hole_F[1]; tmp_suit= hole_S[1]; tmp_full= hole_A[1]; break;
    case 2: tmp_face= flop_F[0]; tmp_suit= flop_S[0]; tmp_full= flop_A[0]; break;
    case 3: tmp_face= flop_F[1]; tmp_suit= flop_S[1]; tmp_full= flop_A[1]; break;
    case 4: tmp_face= flop_F[2]; tmp_suit= flop_S[2]; tmp_full= flop_A[2]; break;
    case 5: tmp_face= turn_F;    tmp_suit= turn_S;    tmp_full= turn_A;    break;
    case 6: tmp_face=river_F;    tmp_suit=river_S;    tmp_full=river_A;    break;
    }
    
    // If card value is 1, i.e. ace, then switch this to a 14
    // Also check for invalid card face value
    // Using switch as it's a bit more verbose but slightly more efficient
    // than a few if statements
    switch(tmp_face) {
    case 2 : cardsFaceP_[i] = 2 ; break;
    case 3 : cardsFaceP_[i] = 3 ; break;
    case 5 : cardsFaceP_[i] = 5 ; break;
    case 7 : cardsFaceP_[i] = 7 ; break;
    case 11: cardsFaceP_[i] = 11; break;
    case 13: cardsFaceP_[i] = 13; break;
    case 17: cardsFaceP_[i] = 17; break;
    case 19: cardsFaceP_[i] = 19; break;
    case 23: cardsFaceP_[i] = 23; break;
    case 29: cardsFaceP_[i] = 29; break;
    case 31: cardsFaceP_[i] = 31; break;
    case 37: cardsFaceP_[i] = 37; break;
    case 41: cardsFaceP_[i] = 41; break;
    default: return -1; // Error code -1
    }

    // Check the suit values are valid, i.e. in [1,4]
    if (tmp_suit!=2 && tmp_suit!=3 && tmp_suit!=5 && tmp_suit!=7) {
      return -2; // Error code -2
    } else {
      cardsSuitP_[i] = tmp_suit;
    }

    // And set the full prime card value
    cardsFullP_[i] = tmp_full;
    
  }

  // We have now read the cards in
  isCards_ = true;
  
  // Completed, return success
  return 0;
  
}






int hand::SetCardsA(std::vector<int> hole_F, std::vector<int> hole_S, std::vector<int> flop_F,
		std::vector<int> flop_S, int turn_F, int turn_S, int river_F, int river_S)
{

  /*
    Assign the hand from VECTORS containing the hole and flop cards (one for the face _F and
    the other for the suit _S values, with each ith element of each vector referencing the
    same card. The turn and river are set with an integer, with one for the face value and the
    other for the suit.
  
    This sets both the standard and prime values, calcualting the prime values from the non-
    prime face and suit input values.

    This routine also carries out some basic input error checks, but not thourogh ones as it
    will likely be called multiple times so we need to minimise cost. Note the sizes of input 
    vectors is not checked (for cost reasons) so we must ensure that the correct sizes arrays
    are given as inputs otherwise unusual behaviour may result.

    Error Codes
    ===========
      Error codes returned from function, 0 means everything ran smoothly.
        -1 ::: Invalid card face value outside range of [1,14] given as an input.
        -2 ::: Invalid card suit value outside range of [1,4] given as an input.
  */

  // Temporary vector for setting the prime values
  std::vector<int> setTmp;
  int tmp_face;
  int tmp_suit;
  
  // Error check for the size ofo the input vectors
  if (hole_F.size()!=2) {
    std::cout << "ERROR : Vector input hole_F to SetCards of incorrect size" << std::endl;
    exit (EXIT_FAILURE);
  } else if (hole_S.size()!=2) {
    std::cout << "ERROR : Vector input hole_S to SetCards of incorrect size" << std::endl;
    exit (EXIT_FAILURE);
  } else if (flop_F.size()!=3) {
    std::cout << "ERROR : Vector input flop_F to SetCards of incorrect size" << std::endl;
    exit (EXIT_FAILURE);
  } else if (flop_S.size()!=3) {
    std::cout << "ERROR : Vector input flop_S to SetCards of incorrect size" << std::endl;
    exit (EXIT_FAILURE);
  }
  
  // Check each card for errors in face or suit value
  for ( int i=0 ; i<7 ; i++ ) {

    // Set temp values by iterating through the hole, flop, turn and river
    switch(i) {
    case 0: tmp_face= hole_F[0]; tmp_suit= hole_S[0]; break;
    case 1: tmp_face= hole_F[1]; tmp_suit= hole_S[1]; break;
    case 2: tmp_face= flop_F[0]; tmp_suit= flop_S[0]; break;
    case 3: tmp_face= flop_F[1]; tmp_suit= flop_S[1]; break;
    case 4: tmp_face= flop_F[2]; tmp_suit= flop_S[2]; break;
    case 5: tmp_face= turn_F;    tmp_suit= turn_S;    break;
    case 6: tmp_face=river_F;    tmp_suit=river_S;    break;
    }
    
    // If card value is 1, i.e. ace, then switch this to a 14
    // Also check for invalid card face value
    // Using switch as it's a bit more verbose but slightly more efficient
    // than a few if statements
    switch(tmp_face) {
    case 1 : cardsFace_[i] = 14; break;
    case 2 : cardsFace_[i] =  2; break;
    case 3 : cardsFace_[i] =  3; break;
    case 4 : cardsFace_[i] =  4; break;
    case 5 : cardsFace_[i] =  5; break;
    case 6 : cardsFace_[i] =  6; break;
    case 7 : cardsFace_[i] =  7; break;
    case 8 : cardsFace_[i] =  8; break;
    case 9 : cardsFace_[i] =  9; break;
    case 10: cardsFace_[i] = 10; break;
    case 11: cardsFace_[i] = 11; break;
    case 12: cardsFace_[i] = 12; break;
    case 13: cardsFace_[i] = 13; break;
    case 14: cardsFace_[i] = 14; break;
    default: return -1; // Error code -1
    }

    // Check the suit values are valid, i.e. in [1,4]
    if (tmp_suit!=1 && tmp_suit!=2 && tmp_suit!=3 && tmp_suit!=4) {
      return -2; // Error code -2
    } else {
      cardsSuit_[i] = tmp_suit;
    }

    // Get the prime values of the current card
    setTmp = card2prime(cardsFace_[i],cardsSuit_[i]);
    cardsFaceP_[i] = setTmp[0];
    cardsSuitP_[i] = setTmp[1];
    cardsFullP_[i] = setTmp[2];
    
  }

  // We have now read the cards in
  isCards_ = true;
  
  // Completed, return success
  return 0;
  
}







/*
  Routines to get class variables
*/

std::vector<int> hand::getCardsFace()
{
  std::vector<int> getCF(7);
  for (int i=0; i<7; i++) {
    getCF[i] = cardsFace_[i];
  }
  return getCF; 
}
std::vector<int> hand::getCardsSuit()
{
  std::vector<int> getCS(7);
  for (int i=0; i<7; i++) {
    getCS[i] = cardsSuit_[i];
  }
  return getCS; 
}
std::vector<int> hand::getCardsFaceP()
{
  std::vector<int> getCF(7);
  for (int i=0; i<7; i++) {
    getCF[i] = cardsFaceP_[i];
  }
  return getCF; 
}
std::vector<int> hand::getCardsSuitP()
{
  std::vector<int> getCS(7);
  for (int i=0; i<7; i++) {
    getCS[i] = cardsSuitP_[i];
  }
  return getCS; 
}
std::vector<int> hand::getCardsFullP()
{
  std::vector<int> getCS(7);
  for (int i=0; i<7; i++) {
    getCS[i] = cardsFullP_[i];
  }
  return getCS; 
}
std::vector<int> hand::getBestFace()
{
  std::vector<int> getBF(5);
  for (int i=0; i<5; i++) {
    getBF[i] = bestFace[i];
  }
  return getBF; 
}
std::vector<int> hand::getBestSuit()
{
  std::vector<int> getBS(5);
  for (int i=0; i<5; i++) {
    getBS[i] = bestSuit[i];
  }
  return getBS; 
}
int hand::getHandCode()
{
  return handCode;
}
int hand::getHandPrimeRank()
{
  return handPrimeRank;
}




/*
  Routines to process data in class
 */



// Sort the cardsFace_ array such that it is in ascending order
// Also sort cardsSuit_ into the same order as cardsFace_ such that each
// ith element of cardsSuit_ is the suit of the ith card in cardsFace_
void hand::sortCards()
{
  
  std::pair<int, int> cardsFace_suit[7];
  for (int i = 0; i < 7; i++) {
    cardsFace_suit[i].first  = cardsFace_[i];
    cardsFace_suit[i].second = cardsSuit_[i];
  }
  sort(cardsFace_suit, cardsFace_suit + 7);
  for (int i = 0; i < 7; i++) {
    cardsFace_[i] = cardsFace_suit[i].first;
    cardsSuit_[i] = cardsFace_suit[i].second;
  }
  
}





int hand::getStraight(int S_cards[], int hand_size)
{

  int straight_tmp;
  int straight_dif;
  bool gotStraight=false;
  int straightHighCard;
  int Si;

  // If hand_size is 7, i.e. checking all face cards for a straight, do a pre-check to see if
  // a straight is possible
  if (hand_size==7) {
    //    std::cout << ((S_cards[2]-S_cards[3])+(S_cards[3]-S_cards[4])) << std::endl;
    if (((S_cards[4]-S_cards[3])+(S_cards[3]-S_cards[2]))<0) return -1;
  }
  
  // If the hand contains an ace and lowest face is a 2 we must also consider a straight 
  // containing Ace then 2, so we have one subsiquent pair before looping if this is the case
  if ( S_cards[0]==2 && S_cards[hand_size-1]==14 ) {
    straight_tmp=1;
    Si=0;
  } else {
    straight_tmp=0;
    Si=0;
  }  
  
  // Iterate through the hand checking for a straight of any suit, only check difference between
  // subsiquent cards, >=4 subsiquent pairs means a straight
  for (int i=Si; i<hand_size-1; i++) {
    
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






int hand::findBestHand()
{

  /* 

     Get the best hand, use this to set the class variable handCode based on the hand we have.
     Also set the bestFace and bestSuit class variables with the face and suit values of the 
     cards that create the best hand (where each ith element is the face and corredsponding suit).

   */ 
  
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
  bool gotFourOfAKind  = false;
  int fourOfAKind4; // The face value of the four of a kind in four of a kind

  // Three of a kind values
  bool gotThreeOfAKind = false;
  int threeOfAKindFace;
  int threeOfAKindSuit[3];

  // Two Pair Values
  bool gotTwoPair = false;
  int twoPairLowFace;
  int twoPairLowSuit[2]={-1,-1};
  int twoPairHighFace;
  int twoPairHighSuit[2]={-1,-1};

  // Pair values
  bool gotPair = false;
  int pairFace;
  int pairSuit[2]={-1,-1};
  
  // Number of cards of each face value
  int faceValCount[7];

  
  
  // The first step is to sort the cards in the hand into ascending order
  sortCards();


  /*
    Check for a straight, we retrun to more calcualtions when we have checked more hands
  */
  straightHighCard = getStraight(cardsFace_,7);
  if (straightHighCard>0) {
    gotStraight = true;
    if (straightHighCard==5) {
      // If the high card in a straight is a 5 then the low card is an ace
      aceInStraight = true;
    }
  }

  /*
    Check for a flush, we return to more calcualtions when we have checked higher hands
    but we need this to check for straight/royal flush
  */

  int flush_tmp;
  int flush_i=0;
  for (int i=1; i<5; i++) {
    // Count number of cards of the ith suit
    flush_tmp = std::count(cardsSuit_, cardsSuit_+7, i);
    if (flush_tmp>4) {
      // If there are at least 5 of a given suit in a hand we have a flush
      gotFlush  = true;
      flushSuit = i;
      flushSize = flush_tmp;
      // Record all cards of the suit with the flush
      for (int j=0; j<7; j++) {
	if (cardsSuit_[j]==flushSuit) {
	  flushCards[flush_i] = cardsFace_[j];
	  flush_i++;
	}
      }
      break; // Can only have one flush, so may as well stop here
    }
  }


  
  /*
    Check for Straight/Royal flush
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
	handCode = 10;
	
      } else {
	// Otherwise we just have a stright flush, still pretty good
	handCode = 9;
      }

      // Copy over the cards from the stright to the best face/suit
      if (aceInStraight==true) {
	bestFace[0] = 14;
	bestSuit[0] = cardsSuit_[6];
      }
      for (int i=flushSize-1; i>-1; i--) {
	// Note only copy over elements of the flush that are also in the straight
	// This accounts for 6 or 7 cards of same suit in hand
	if (flushCards[i] <= straightFlushHighCard && flushCards[i]>0) {
	  bestFace[straightFlush_i] = flushCards[i];
	  bestSuit[straightFlush_i] = flushSuit;
	  straightFlush_i--;
	  if (straightFlush_i==-1) break;
	  if (straightFlush_i==0 && aceInStraight==true) break;
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
    // For cost reasons trying to reduce the number of calls to std::count
    // if (i==1) {
    //   // On the first card we must count the number of cards in the face
    //   faceValCount[i] = std::count(cardsFace_, cardsFace_+7, cardsFace_[i]);
    // } else if (cardsFace_[i]==cardsFace_[i-1]) {
    //   // If the current card face is the same as the last then just copy the count over
    //   faceValCount[i]=faceValCount[i-1];
    // } else {
    //   // Otherwise we have a new face value and must count again
    //   faceValCount[i] = std::count(cardsFace_, cardsFace_+7, cardsFace_[i]);
    // }

    // Quicker to run std::count on all face values rather than copying identical values
    faceValCount[i] = std::count(cardsFace_, cardsFace_+7, cardsFace_[i]);
    
    if (i==0 || cardsFace_[i-1]!=cardsFace_[i]) {
      // Only consider the first face value where there are multiple of the same face value
      
      if (faceValCount[i]==4) {
	gotFourOfAKind  = true;           // We have 4 of a kind, pretty good!
	fourOfAKind4    = cardsFace_[i]; // The face value of the four of a kind
      }
      if (faceValCount[i]==3) {
	if (cardsFace_[i]!=threeOfAKindFace) suit3_i=0;
	gotThreeOfAKind           = true;           // Got three of a kind
	threeOfAKindFace          = cardsFace_[i]; // Save the face val  of highest 3 of a kind
	threeOfAKindSuit[suit3_i] = cardsSuit_[i]; // Save the suit vals of highest 3 of a kind
	suit3_i++;
      }
      if (faceValCount[i]==2) {
	// If we haven't seen a pair before we only have one pair (so far)
	// if we have we have two pair

	// Note: we use the pair face value check to avoid writing the pair twice, where we
	//       recall cards are inascending order so pair is ith and i+1th card in hand
      
	if (gotPair==false) {
	  // The first time we encounter a pair, just save the one pair
	  gotPair     = true;      
	  pairFace    = cardsFace_[i];
	  pairSuit[0] = cardsSuit_[i];
	  pairSuit[1] = cardsSuit_[i+1];
	} else if (cardsFace_[i]!=pairFace) {
	  // When we encounter a second pair 
	  gotTwoPair         = true;
	  twoPairLowFace     = pairFace;
	  twoPairLowSuit[0]  = pairSuit[0];
	  twoPairLowSuit[1]  = pairSuit[1];
	  pairFace           = cardsFace_[i];
	  pairSuit[0]        = cardsSuit_[i];
	  pairSuit[1]        = cardsSuit_[i+1];
	  twoPairHighFace    = pairFace;
	  twoPairHighSuit[0] = pairSuit[0];
	  twoPairHighSuit[1] = pairSuit[1];
	}
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
      bestFace[i] = fourOfAKind4;
      bestSuit[i] = i;
    }
    // Go backwards down the array, until we find the highest card that isn't the one
    // that is part of four of a kind
    for (int i=0; i<7; i++) {
      if (cardsFace_[6-i]!=fourOfAKind4) {
        bestFace[0] = cardsFace_[6-i];
	bestSuit[0] = cardsSuit_[6-i];
	break;
      }
    }
    handCode = 8;
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
      bestFace[i+2] = threeOfAKindFace;
      bestSuit[i+2] = threeOfAKindSuit[i];
    }

    // Now copy over the highest pair, note we must search for the suits
    for (int i=0; i<7; i++) {
      if (cardsFace_[i]==pairFace) {
	bestFace[fullHouse_i] = cardsFace_[i];
	bestSuit[fullHouse_i] = cardsSuit_[i];
	fullHouse_i++;
	if (fullHouse_i==2) break;
      }
    }
    
    handCode = 7;
    return 0; // Full house, so we can exit now as we've checked for all better hands
    
  }
  


  /*
    Flush check
  */

  // We have previously checked for a flush, but we've now checked all the better hands
  // so if we have a flush exit with this as the best hand
  if (gotFlush==true) {
    
    int flush_tmp=4;
    for (int i=flushSize-1; i>-1; i--) {
      bestFace[flush_tmp] = flushCards[i];
      bestSuit[flush_tmp] = flushSuit;
      flush_tmp--;
      if (flush_tmp==-1) break;
    }

    handCode = 6;
    return 0;
    
  }



  /*
    Straight check
  */

  // We have previously checked for a flush, and we know we do not have a straight flush
  // So just copy out the stright cards along with their suits
  if (gotStraight==true) {

    int straight_i;
    int str_prev_card=-1;
    // For brevity seperate out the case of an ace in the stright and no ace in the staight
    if (aceInStraight==true) {
      // We know the ace is last in ascending hand (with face value 14) so set that
      bestFace[0] = 14;
      bestSuit[0] = cardsSuit_[6];
      // Now loop backwards adding subsiquent cards based on high card
      straight_i=4;
      for (int i=5; i>-1; i--) {
	if (cardsFace_[i]<straightHighCard+1 && cardsFace_[i]!=str_prev_card) {
	  bestFace[straight_i] = cardsFace_[i];
	  bestSuit[straight_i] = cardsSuit_[i];
	  str_prev_card = cardsFace_[i];
	  straight_i--;
	}
	if (straight_i==0) break;
      }
    } else {
      straight_i=4;
      for (int i=6; i>-1; i--) {
	if (cardsFace_[i]<straightHighCard+1 && cardsFace_[i]!=str_prev_card) {
	  bestFace[straight_i] = cardsFace_[i];
	  bestSuit[straight_i] = cardsSuit_[i];
	  str_prev_card = cardsFace_[i];
	  straight_i--;
	}
	if (straight_i==-1) break;
      }
    }

    handCode = 5;
    return 0;
    
  }



  /*
    Three of a kind check
  */

  if (gotThreeOfAKind==true) {

    // First copy over the three of a kind as these are known
    for (int i=2; i<5; i++) {
      bestFace[i] = threeOfAKindFace;
      bestSuit[i] = threeOfAKindSuit[i-2];
    }
    
    // Now find the remaining two cards, in ascending order
    int three_i=1;
    for (int i=6; i>-1; i--) {
      if (cardsFace_[i]!=threeOfAKindFace) {
	bestFace[three_i] = cardsFace_[i];
	bestSuit[three_i] = cardsSuit_[i];
	three_i--;
      }
      if (three_i==-1) break;
    }

    handCode = 4;
    return 0;
    
  }
  

  
  /*
    Two pair
  */

  if (gotTwoPair==true) {

    // Copy over the known pair values
    bestFace[1] = twoPairLowFace;
    bestFace[2] = twoPairLowFace;
    bestFace[3] = twoPairHighFace;
    bestFace[4] = twoPairHighFace;
    bestSuit[1] = twoPairLowSuit[1];
    bestSuit[2] = twoPairLowSuit[0];
    bestSuit[3] = twoPairHighSuit[1];
    bestSuit[4] = twoPairHighSuit[0];
    
    // Now look for highest card not in one of the two pairs
    for (int i=6; i>-1; i--) {
      if (cardsFace_[i]!=twoPairHighFace && cardsFace_[i]!=twoPairLowFace) {
	bestFace[0] = cardsFace_[i];
	bestSuit[0] = cardsSuit_[i];
	break;
      }
    }
    handCode = 3;
    return 0;
  }



  /*
    Pair
  */

  if (gotPair==true) {

    // First copy over the pair values
    bestFace[4] = pairFace;
    bestFace[3] = pairFace;
    bestSuit[4] = pairSuit[0];
    bestSuit[3] = pairSuit[1];

    // Now loop through to find the 3 highest cards not in a pair
    int pair_i=2;
    for (int i=6; i>-1; i--) {
      if (cardsFace_[i]!=pairFace) {
	bestFace[pair_i] = cardsFace_[i];
	bestSuit[pair_i] = cardsSuit_[i];
	pair_i--;
	if (pair_i==-1) break;
      }
    }
    handCode = 2;
    return 0;
  }



  /*
    High Card
  */

  // Finally just copy over all the highest cards in ascending order, as this is the best we have
  int high_i=4;
  for (int i=6; i>1; i--) {
    bestFace[high_i] = cardsFace_[i];
    bestSuit[high_i] = cardsSuit_[i];
    high_i--;
  }
  handCode = 1;
  return 0;
  
}





/*
  Find the hand code with the prime method
*/

int hand::findBestHandP()
{
  
  // Find the vector containing hand code and prime product/sum rank from the lookup table
  std::vector<long long int> tmpHC;
  tmpHC = lookupBestHandPrimes(\
      cardsFullP_[0],cardsFullP_[1],cardsFullP_[2],cardsFullP_[3],cardsFullP_[4],cardsFullP_[5],cardsFullP_[6],
      cardsFaceP_[0],cardsFaceP_[1],cardsFaceP_[2],cardsFaceP_[3],cardsFaceP_[4],cardsFaceP_[5],cardsFaceP_[6],
      cardsSuitP_[0],cardsSuitP_[1],cardsSuitP_[2],cardsSuitP_[3],cardsSuitP_[4],cardsSuitP_[5],cardsSuitP_[6]);

  // Set hand code and prime rank
  handCode = tmpHC[0];
  handPrimeRank = tmpHC[1];

  return 0;
  
}

int hand::findBestHandII(int c1, int c2, int c3, int c4, int c5, int c6, int c7)
{
  
  // Find the vector containing hand code and prime product/sum rank from the lookup table
  std::vector<long long int> tmpHC;
  tmpHC = lookupBestHandPrimes(\
       	   primes[c1],   primes[c2],   primes[c3],   primes[c4],   primes[c5],   primes[c6],   primes[c7],\
	   primeFace[c1],primeFace[c2],primeFace[c3],primeFace[c4],primeFace[c5],primeFace[c6],primeFace[c7],\
	   primeSuit[c1],primeSuit[c2],primeSuit[c3],primeSuit[c4],primeSuit[c5],primeSuit[c6],primeSuit[c7]);


  // Set hand code and prime rank
  handCode = tmpHC[0];
  handPrimeRank = tmpHC[1];

  return 0;
  
}


