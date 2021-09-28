# Texas Holdem Poker Utilities

A C++ library of utilities for calculations involving Texas HoldEm poker.

**NOTE:** This library is under very active development.



## General use

This C++ library is being written to be used as a general purpose C++ library for use with Texas HoldEm poker game analysis that can also be compiled for use as a Python module.

In order to compile one may run ``make`` and to compile as a python library run ``make python``.

### Notes

- As the exact suit doesn't matter in HoldEm suits are referred to by integers [1,4], which suit is which is of no consequence as long as each suit is consistently referred to by the same integer throughout.
- Each face value card is referred to by an integer, with [2,10] being self explanatory. 11, 12 and 13 refer to Jack, Queen and King respectively. An Ace is given the value 14.
- For brevity throughout we let S=Spades, D=Diamonds, H=Hearts and C=Clubs and refer to cards by number and letter, e.g. 5H is the 5 of hearts and AS is the ace of spades.





## C++ Use



### Hand Class

The hand class is the basic class that takes in the 2 hole cards of a given player along with the 5 cards from the flop, turn and river. It can then calculate the best HoldEm hand that exists within those 7 cards.

###### Class var : ``int[7]`` : ``cardsFace_``

The face value of the 7 cards from the hole, flop turn and river. Note the suit for each ith card is represented by the ith value of the cardsSuit_ array.

###### Class var : ``int[7]`` : ``cardsSuit_``

The suit value of the 7 cards from the hole, flop turn and river. Note the face value for each ith card is represented by the ith value of the cardsSuit_ array.

###### Class var : ``int`` : ``handCode``

An integer that (once set) gives the code for the best hand available from the cards in ``cardsFace_`` and ``cardsSuit`` where:
- -1  :: No hand, i.e. not yet checked
-  1  :: High card
-  2  :: Pair
-  3  :: Two pair
-  4  :: Three of a kind
-  5  :: Straight
-  6  :: Flush
-  7  :: Full house
-  8  :: 4 of a kind
-  9  :: Straight flush
-  10 :: Royal Flush

Note: ``if handCode==-1`` then the best hand from the cards in ``cardsFace_`` and ``cardsSuit`` has not yet been calculated.

###### Class var : ``int[5]`` : ``bestFace_``

The 5 cards (once set) that give the hand given in ``handCode``, only available. Note for each hand they will be ordered such that
- Royal Flush: { 10, J, Q, K, A }
- Straight Flush: In ascending order, e.g. { 3, 4, 5, 6, 7 }
- Four of a Kind: Last 4 elements of array are the 4 of a kind cards and first is the odd one e.g. face values in order { 3, 6, 6, 6, 6 }
- Full House: The three of a kind elements are the last in the array e.g. face values in order { 3, 3, 6, 6, 6 }
- Flush: Flush values of highest face cards of flush suit in ascending order e.g. face values in order { 2, 4, 7, 8, 9 }
- Straight: Straight cards in ascending order e.g. face values in order { 4, 5, 6, 7, 8 }. Note: If an Ace is part of the straight then we have cards in order { 14, 2, 3, 4, 5 }
-  Three of a kind: Three of a kind as the final elements in``bestFace``, with two highest cards not in the three of a kind in ascending order in index 0 and 1, e.g. { 2, 13, 4, 4, 4 }
-  Two Pair: The two pairs in ascending order as the last 4 elements of the array with element 0 being the highest card not in a pair e.g. { 7, 2, 2, 10, 10 }
-  Pair: Store the single pair in the final two elements of the array and ascending high cards in all lower elements e.g. { 2, 4, 6, 5, 5 }
-  High Card: Return the highest face value cards in ascending order e.g. { 2, 4, 6, 7, 9, 10 }

###### Class var : ``int[5]`` : ``bestSuit_``

The suit integers where each ith element of ``bestSuit_`` gives the suit of the ith card in  ``bestFace_``.

###### Class fn : ``int[2][7]->int`` : ``setCardsFull``

Set the values of ``cardsFace_`` and ``cardsSuit_`` based on the input array where ``cards_in[0][:]`` are the 7 face values of the cards and ``cards_in[1][:]`` are the 7 suit values of the cards.

Returns: 
- 0 :: success.
- -1 :: invalid card face value given.
- -2 :: invalid card suit value given.

Note: Each ith element of ``cards_in[0][:]`` must match a face value with a suit value given in ``cards_in[1][:]``. For example ``cards_in[0][3]`` and ``cards_in[1][3]`` must refer to the face and suit values (respectively) of a single card.

Note: Though throught the program we refer to ace cards with the integer 14, when setting we can use either 1 or 14.

**Example**, if one had the cards: 
- hole  :: 3S, 4D
- flop  :: AS, 9H, KD
- turn  :: 8D
- river :: AC

One would set this by calling
```
  int stat;
  hand H;
  int cards[2][7] = {{3,4,14,9,13,8,1},{1,3,1,4,3,3,2}};
  stat = H.setCardsFull(cards);
```

###### Class fn : ``int[2][2],int[2][3],int[2][1],int[2][1]->int`` : ``setCards``

Set the values of ``cardsFace_`` and ``cardsSuit_`` based on the input arrays where the four input arrays are (in order):
- ``hole[2][2]`` :: The 2 hole cards.
- ``flop[2][3]`` :: The 3 flop cards.
- ``turn[2][1]`` :: The single turn card.
- ``river[2][1]`` :: The single river card.

As in the case of ``setCardsFull`` the first row refers to the face value of the card and the second to the suit for each respective card. Returns
- 0 :: success.
- -1 :: invalid card face value given.
- -2 :: invalid card suit value given.

**Example**, if one had the same cards as in the ``setCardsFull`` example, they could be set into the class instance ``H`` with
```
  int stat;
  hand H;
  int hole[2][2] = {{3,4},{1,3}};
  int flop[2][3] = {{14,9,13},{1,4,3}};
  int turn[2][1] = {{8},{3}};
  int river[2][1]= {{1},{2}};  
  stat = H.setCards(hole,flop,turn,river);
```

###### Class fn : ``void`` : ``sortCards``

Sort the cards (if set) in the ``cardsFace_`` and ``cardsSuit_`` values such that the face values are in ascending order, with ace=14 as the highest card.

###### Class fn : ``none->int`` : ``findBestHand``

Use the cards stored in ``cardsFace_`` and ``cardsSuit_`` to find the best 5 card Texas HoldEm hand possible. Populate the ``bestFace_`` and ``bestSuit_`` class arrays and the ``handCode`` class variable. Returns 0 on success.

####  Full example

After compiling with ``make`` we set the cards as in ``setCards`` definition, then find the best cards and print them out with out main.cpp file
```
#include<iostream>
#include "src/holdem/hand.h"

int main() {
  int stat;
  hand H;
  int hole[2][2] = {{3,4},{1,3}};
  int flop[2][3] = {{14,9,13},{1,4,3}};
  int turn[2][1] = {{8},{3}};
  int river[2][1]= {{1},{2}};
  
  stat = H.setCards(hole,flop,turn,river);
  std::cout << "status a: " << stat << std::endl;
  stat = H.findBestHand();
  std::cout << "status b: " << stat << std::endl;
  std::cout << "hand code: " << H.handCode << std::endl;
  std::vector<int> T = H.getCardsFace();
  for(int i=0; i<5; i++) {
    std::cout << H.bestFace[i] << "   " << T[i] << std::endl;
  }
  return 0;
}
```









## Python Use

To compile for Python run ``make python`` and import the module ``holdEm``. In this section we approach just the python usage, ignoring the exact structure of the C++ routines.


### Hand Class

This works as the Python version of the hand class from C++ docs, where we set the 7 cards from the hold, flop, turn and river and then find the best 5 card HoldEm hand from these cards.

###### Class fn : ``int[7],int[7]->int`` : ``pSetCardsFull``

Set the cards in the hand and on the table, where the first input array refers to the face values of the cards and the second to the suit values. Return 0 on success. For example we set the hand AS, 2C, 4H, 6D, 8C, AD, 6H with
```
H = holdEm.hand()
stat = H.pSetCardsFull((1,2,4,6,8,14,6),(1,2,3,4,2,4,3))
```

###### Class fn : ``int[2],int[2],int[3],int[3],int,int,int,int->int`` : ``pSetCards``

Set the cards in the hand based on the hole, flop, turn and river arrays separately where the input arrays in order are
- ``holeF`` : ``int[2]`` : The face values of the 2 hole cards.
- ``holeS`` : ``int[2]`` : The suit values of the 2 hole cards.
- ``flopF`` : ``int[3]`` The face values of the 3 flop cards.
- ``flopS`` : ``int[3]`` The suit values of the 3 flop cards.
- ``turnF`` : ``int`` The face value of the single turn card.
- ``turnS`` : ``int`` The suit value of the single turn card.
- ``riverF`` : ``int`` The face value of the single river card.
- ``riverS`` : ``int`` The suit value of the single river card.

For example we can set the hand AS, 2C, 4H, 6D, 8C, AD, 6H with
```
H = holdEm.hand()
stat = H.pSetCards((1,2),(1,2),(4,6,8),(3,4,2),14,4,6,3)
```

###### Class fn : ``None->int[7]`` : ``getCardsFace``

Return the face values of the 7 cards from the hole, flop, turn and river.

###### Class fn : ``None->int[7]`` : ``getCardsSuit``

Return the suit values of the 7 cards from the hole, flop, turn and river.

###### Class fn : ``none->int`` : ``findBestHand``

Use the cards set with ``pSetCards`` or ``pSetCardsFull`` after either of these routines has been ran to find the best 5 card Texas HoldEm hand possible. Returns 0 on success. The calculated hands can then be returned with the following routines.

###### Class fn : ``None->int`` : ``getHandCode``

Get the hand code of the best 5 card hand found with ``findBestHand``, where
- -1  :: No hand, i.e. not yet checked
-  1  :: High card
-  2  :: Pair
-  3  :: Two pair
-  4  :: Three of a kind
-  5  :: Straight
-  6  :: Flush
-  7  :: Full house
-  8  :: 4 of a kind
-  9  :: Straight flush
-  10 :: Royal Flush

###### Class fn : ``None->int[5]`` : ``getBestFace``

Return the face value of the cards that make up the best hand found with ``findBestHand``. See section on ``bestFace_`` for a more in depth description.

###### Class fn : ``None->int[5]`` : ``getBestSuit``

Return the suit values of the cards that make up the best hand found with ``findBestHand``. Note each ith element of the returned array is the suit of the corresponding face value returned with ``getBestFace``.









####  Full example

If we have the cards in the hold, flop, turn and river of AS, 2C, 4H, 6D, 8C, AD and 6H, then we can set these and check for the best hand with
```
import holdEm

H = holdEm.hand()

stat = H.pSetCardsFull((1,2,4,6,8,14,6),(1,2,3,4,2,4,3))
print("Stat: ", stat)
print("All cards face vals: ", H.getCardsFace())
print("All cards suit vals: ", H.getCardsSuit())

H.findBestHand()
print("Stat: ", stat)
print("Best hand code: ", H.getHandCode())
print("Best hand face: ", H.getBestFace())
print("Best hand suit: ", H.getBestSuit())
```




