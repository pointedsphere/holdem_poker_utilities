# Texas Holdem Poker Utilities

A C++ library of utilities for calculations involving Texas HoldEm poker.

**NOTE: This library is under very active development, as such this documentation is very rough.**

This program (and the python module that can be compiled with ``make python``) contain two methods of finding a 5 card holdem hand from 7 cards, the winner from multiple hands and from this a Monte Carlo simulation. One is a 'brute-force' implementation that compares each hand and a second that utilizes prime card values and a series of lookup tables.

The naive 'brute-force' implementation, though slow, is easy to read and modify. Furthermore, it is easy to run step by step and pull out information ad-hoc. This method is only really useful if this very in depth analysis is desirable. If not, the prime method of Monte Carlo simulation is preferable (``MCP``), which gives win/loose/draw statistics for each player and each hand type the player can have.

## General use and compilation

This C++ library is a general purpose C++ library for use with Texas HoldEm poker game analysis which can also be compiled for use as a Python module.

In order to compile for C++ one should run ``make``.

To compile as the python library ``holdEm`` the pybind11 module is required. This can be installed following [the installation instructions here](https://pybind11.readthedocs.io/en/stable/installing.html) (concisely running ``pip install pybind11`` with pip  or ``brew install pybind11`` for a global homebrew install). Once pybind11 is installed simply run ``make python`` and the module file will be compiled, which can then be imported to any python script.

**Note:** as this library is under active development compilation has not been tested in many different environments (yet).

### Compile times

The lookup tables cause compilation to be non-trivial with ``-O3`` optimisation, approximately 45 mins. If one wishes to have a quick play with the scripts just change ``-O3`` to ``-O0`` in the makefile and compile (though this will drastically and negatively effect cost).














## (Prime) Method for Finding and Comparing Hands

The 'brute force' method, though useful, is far from optimal. Though other methods have been proposed in the past (for example [The Two Plus Two Evaluator](https://www.codingthewheel.com/archives/poker-hand-evaluator-roundup/#2p2)) they often require rather large lookup tables (~200MB), which is not ideal.

So, here we use our own method, created for brevity, a truncated prime method.

This works on the basis of assigning 2 prime numbers to a card. One in reference to the face value of the card and another to the suit value. We do this by ordering the cards in ascending order, based on suit values [1,4] and then face values [2,14] (where ace == 14). We then assign a prime number in {2,3,5,7} to each suit value (``PS``), assign a prime number in {2,3,5,7,11,13,17,19,23,29,31,37,41} to each face value (``PF``), i.e. the ith card given by the ith element of the following arrays

```
F = {
    2,3,4,5,6,7,8,9,10,11,12,13,14,
    2,3,4,5,6,7,8,9,10,11,12,13,14,
    2,3,4,5,6,7,8,9,10,11,12,13,14,
    2,3,4,5,6,7,8,9,10,11,12,13,14};

S = {
    1,1,1,1,1,1,1,1,1,1,1,1,1,
    2,2,2,2,2,2,2,2,2,2,2,2,2,
    3,3,3,3,3,3,3,3,3,3,3,3,3,
    4,4,4,4,4,4,4,4,4,4,4,4,4};

PS= { 
    2,2,2,2,2,2,2,2,2,2,2,2,2, 
    3,3,3,3,3,3,3,3,3,3,3,3,3, 
    5,5,5,5,5,5,5,5,5,5,5,5,5, 
    7,7,7,7,7,7,7,7,7,7,7,7,7 };

PF = { 
    2,3,5,7,11,13,17,19,23,29,31,37,41,    
    2,3,5,7,11,13,17,19,23,29,31,37,41,    
    2,3,5,7,11,13,17,19,23,29,31,37,41,    
    2,3,5,7,11,13,17,19,23,29,31,37,41 };
```

where ``F`` is the face value of a card, ``S`` is the suit and ``PS`` and ``PF`` are the prime face and suit values. For example the king of clubs can be given by

```
F[11] = 13 , S[11]=1 , PS[11]=2 , PF[11]=37
```

We then utilise the `brute-force' method to generate code containing lookup tables from which we can find the hand type (or hand code, or *HC*) where
-  ``HC=1 `` :: High card
-  ``HC=2 `` :: Pair
-  ``HC=3 `` :: Two pair
-  ``HC=4 `` :: Three of a kind
-  ``HC=5 `` :: Straight
-  ``HC=6 `` :: Flush
-  ``HC=7 `` :: Full house
-  ``HC=8 `` :: 4 of a kind
-  ``HC=9 `` :: Straight flush
-  ``HC=10`` :: Royal Flush

We also find a value we refer to as a hand rank (or *HR*) where if two hands have the same *HC* then the hand with the largest *HR* wins. This is explained in more detail in a later section.

To carry out the prime method we first  use the product of the prime suit values for all 7 cards in a hand, checking this product against a switch function to check for a flush (and find the suit of the flush). If there is a flush we then check for a straight or royal flush by checking the product of the face values of the cards in the hand that are of the suit that constitutes the flush. We then return the hand code and rank using this product as the hash table key (if we have a straight or royal flush).

We then use the product of all prime face values as the key to check for a full house or 4 of a kind against another lookup table.

Then, iff we have a flush, we compare the product of all prime face values of cards in the hand that are of the suit that constitutes the flush. This product is used as the key for the hash table lookup and this step is ignored if we don't have a flush.

For all lower hands we consider the product of all prime face values as the key for the lookup table.

In this way, using a switch statement for the flush check of suit values and 4 hash tables we can check for a hand in 7 cards using ~50000 lines of code (given in ``machine_gen_code/lookupBestHandPrimes.cpp``). This routine is machine generated first by generating 4 data files (using ``.cpp`` scripts in ``machine_gen_code/gen_face_hands``, ``machine_gen_code/gen_flush`` and ``machine_gen_code/gen_straight_royal_flush``). We then parse this data into the requisite ``.cpp`` and ``.h`` files using ``machine_gen_code/parseDataToFunctionLookup.py``

### Comparing Hands With The Same Hand Code

Consider two players, *P1* and *P2*, and assume they both have the same hand code (*HC*). As we know the *HC* we can find the best hand of the same *HC* by looking at a modified face value product (*MFVP*) that is also returned by the table lookup.

The function ``lookupBestHandPrimes`` in ``machine_gen_code/lookupBestHandPrimes.cpp`` returns both the *HC* and the *MFVP* of a hand (from the lookup table), where *MFVP* is calculated differently for each type of hand. It is calculated in such a way that if *P1* and *P2* have the same *HC* they can compare *MFVP* values, the largest of which wins (and equality signifies a draw). This will work for any *N>1* players, as long as their *HC* is identical. The method for *MFVP* calculation is given below for each *HC*.

Throughout this section we refer to prime face and suit values as the requisite card values for each card from ``PS`` and ``PF``. Also let us assume that from the 'brute-force' method we know the 5 cards within a 7 card hand that constitute the best hand.

#### Step 1 : Checking for a flush (any flush)

We can first check to see if the 7 card hand contains a 5,6 or 7 card flush. We do this by looking at the product of only the prime suit values. If we do not have a flush of any sort there is no need to check for a straight flush, royal flush or flush hand.

#### Royal flush, straight flush and flush

For any of the flush hands we calculate the *MFVP* as the product of the prime face values which have the suit that constitutes the flush.

#### Four of a kind

Let us consider the non-prime face values of the card in the hand when we know we have a four of a kind. Let ``f4`` be the non-prime face value of the 4 cards in the four of a kind and ``fk`` be the face value of the kicker. Then let

```
f4P = 2^(f4+11)
fkP = 2^(fk-2)
```

such that ``f4P`` is one of 13 values in [2^13 , 2^25] and ``fkP`` is one of 13 values in [2^0 , 2^12]. Such that ``f4P+fkP`` is a 26 bit binary value where the lowest 13 bits correspond to the kicker face value and the largest 13 correspond to the 4 of kind face value. We then take

```
MFVP = f4P + fkP
```

where the highest of these values for players with 4 of a kind wins (and equality means a draw).

### Full House

Calculation of *MFVP* for the full house is much that same as for Four of a kind, where we treat the face value for the three of a kind in the same way as with the four of a kind face value. We then treat the pair face value like the kicker value in four of a kind.

### Straight

In the case of any straight hand the *MFVP* is simply the face value of the highest card in the straight.

### Three of a kind

We approach three of a kind in a similar way to 4 of a kind, except there are two kickers here. We treat the three of a kind like the 4 of a kind value, then add this to the two 13 bit kicker values.

I.e. let ``f3`` be the face value of the three of a kind and let ``k1`` and ``k2`` be the face values of the kickers (all in [2,14]), then we calculate

```
MFVP = 2^(f3+11) + 2^(k1-2) + 2^(k2-2)
```

such that *MFVP* is a 26 bit integer. The lowest 13 bits of *MFVP* correspond to the two kickers and the last 13 bits correspond to the three of a kind (note; the kickers cannot have the same face value, otherwise we would have a full house).

Again the highest *MFVP* wins when comparing players with three of a kind, and equality signifies a draw.

### Two Pair

Two pair has 3 'rankings' of cards within it, the higher pair, the lower pair and then the kicker, as such we utilise a 39 bit integer. Here the lowest 13 bits correspond to the kicker, the next 13 bits to the low pair and the highest 13 bits to the high pair.

Let ``p1``, ``p2`` and ``k1`` be the face value of the highest pair, lowest pair and kicker respectively (all in [2,14]). Then

```
MFVP = 2^(p1+24) + 2^(p2+11) + 2^(k1-2)
```

Again highest *MFVP* wins between hands with two pair.

### One Pair

A single pair requires a 26 bit integer, the lowest 13 bits are the sum of the 3 kicker values in binary representation and the last 13 represent the pair (note; all kicker face values must be distinct or we would have a better hand than one pair).

Let ``p1`` be the face value of the pair (in [2,14]) and let ``k1``, ``k2`` and ``k3`` be the face values of the kickers (again in [2,14]). Then

```
MFVP = 2^(p1+11) + 2^(k1-2) + 2^(k2-2) + 2^(k3-2)
```

Again highest *MFVP* wins for multiple hands with one pair.

### High Card

As the only ranking we care about here is the highest card, and we are guaranteed that the suit does not matter and no repeated face values we just take the sum of the 5 cards in the hand (in binary representation) to give a 13 bit MFVP.

Let ``k1``, ``k2``, ``k3``, ``k4`` and ``k5`` be the 5 face values of the cards in the hand (all in [2,14]). Then

```
MFVP = 2^(k1-2) + 2^(k2-2) + 2^(k3-2) + 2^(k4-2) + 2^(k5-2)
```

Where highest *MFVP* wins.














### General Notes

- As the exact suit doesn't matter in HoldEm suits are referred to by integers [1,4], which suit is which is of no consequence as long as each suit is consistently referred to by the same integer throughout.
- Each face value card is referred to by an integer, with [2,10] being self explanatory. 11, 12 and 13 refer to Jack, Queen and King respectively. An Ace is given the value 14.
- For brevity throughout we let S=Spades, D=Diamonds, H=Hearts and C=Clubs and refer to cards by number and letter, e.g. 5H is the 5 of hearts and AS is the ace of spades.

### General use

Consider the state of the table with 3 players after the flop, where our hand is KS KD, (for some reason) we know another players hold is QH QD and the flop is 5H, 6S, 10D. We then wish to fun a Monte Carlo sim over 10^6 iterations to see what happens here, this can be done in Python (after compiling the module with ``make python``) with:

```
import holdEm

Np  = 3       # Number of players
Nmc = 1000000 # Numer of monte carlo loops

# Initialise table class, with N players
T = holdEm.table(Np)

# Set player one hold to As Kc
stat = T.setHoldCards(0,(13,13),(1,2))

# Set player two hold to Ah Qd
stat = T.setHoldCards(1,(12,12),(3,4))

# Set the flop to 5h, 6s, 10d
stat = T.setFlop((5,6,10),(3,1,4))

# Run a Monte Carlo simulation
T.MC(Nmc)

# Get data from the Monte Carlo simulator
wins  = T.getWins()
winsP = T.getWinsP()
draw  = T.getDraws()
drawP = T.getDrawsP()

# Print the array of the win probabilities
print("\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n")
for p in range(Np):
    print("player ", p, " | Win count : ", "{:9}".format(wins[p]), " | Win prob : ", "{:2.4f}".format(winsP[p]), \
        " | Draw count : ", "{:9}".format(draw[p]), " | Draw prob : ", "{:2.4f}".format(drawP[p]))
    
# Print the hands for each player
for p in range(Np):
    print("\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n")
    winsPP  = T.getWinsPP(p)
    winsPPp = T.getWinsPPp(p)
    drawPP  = T.getDrawsPP(p)
    drawPPp = T.getDrawsPPp(p)
    handPP  = T.getHandsPP(p)
    handPPp = T.getHandsPPp(p)
    for h in range(10):
        print("player ", p, " | hand code : ", "{:2}".format(h+1), \
              " | win count : ",   "{:9}".format(winsPP[h]), " | win prob : ",   "{:2.4f}".format(winsPPp[h]), \
              " | draw count : ",  "{:9}".format(drawPP[h]), " | draw prob : ",  "{:2.4f}".format(drawPPp[h]), \
              " | occur count : ", "{:9}".format(handPP[h]), " | occur prob : ", "{:2.4f}".format(handPPp[h]))
print("\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n")
```

Where this script can be found in ``examples/MC_example.py``.





















## C++ Use



### ``hand`` Class

The hand class is the basic class that takes in the 2 hole cards of a given player along with the 5 cards from the flop, turn and river. It can then calculate the best HoldEm hand that exists within those 7 cards.

#### Class var : ``int[7]`` : ``cardsFace_``

The face value of the 7 cards from the hole, flop turn and river. Note the suit for each ith card is represented by the ith value of the cardsSuit_ array.

#### Class var : ``int[7]`` : ``cardsSuit_``

The suit value of the 7 cards from the hole, flop turn and river. Note the face value for each ith card is represented by the ith value of the cardsSuit_ array.

#### Class var : ``int`` : ``handCode``

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

#### Class var : ``int[5]`` : ``bestFace_``

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

#### Class var : ``int[5]`` : ``bestSuit_``

The suit integers where each ith element of ``bestSuit_`` gives the suit of the ith card in  ``bestFace_``.

#### Class fn : ``int[2][7]->int`` : ``setCardsFull``

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

#### Class fn : ``int[2][2],int[2][3],int[2][1],int[2][1]->int`` : ``setCards``

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

#### Class fn : ``void`` : ``sortCards``

Sort the cards (if set) in the ``cardsFace_`` and ``cardsSuit_`` values such that the face values are in ascending order, with ace=14 as the highest card.

#### Class fn : ``none->int`` : ``findBestHand``

Use the cards stored in ``cardsFace_`` and ``cardsSuit_`` to find the best 5 card Texas HoldEm hand possible. Populate the ``bestFace_`` and ``bestSuit_`` class arrays and the ``handCode`` class variable. Returns 0 on success.

####  Full example

After compiling with ``make`` we set the cards as in ``setCards`` definition, then find the best cards and print them out with out main.cpp file
```
#include<iostream>

#include "src/holdem/hand.h"
#include "src/holdem/deck.h"

int main() {

  int stat; // status variable
  hand H;   // Initialise a hand class

  // Declare the input arrays to set the cards in the hand
  int ArrHoleF[2] = {3,4};
  int ArrHoleS[2] = {1,3};
  int ArrFlopF[3] = {14,9,3};
  int ArrFlopS[3] = {1,4,3};
  int turnF = 8;
  int turnS = 3;
  int riverF = 1;
  int riverS = 2;

  // Convert arrays to vectors
  std::vector<int> holeF(ArrHoleF, ArrHoleF + sizeof(ArrHoleF) / sizeof(ArrHoleF[0]) );
  std::vector<int> holeS(ArrHoleS, ArrHoleS + sizeof(ArrHoleS) / sizeof(ArrHoleS[0]) );
  std::vector<int> flopF(ArrFlopF, ArrFlopF + sizeof(ArrFlopF) / sizeof(ArrFlopF[0]) );
  std::vector<int> flopS(ArrFlopS, ArrFlopS + sizeof(ArrFlopS) / sizeof(ArrFlopS[0]) );

  // Set the cards within the class
  stat = H.SetCards(holeF,holeS,flopF,flopS,turnF,turnS,riverF,riverS);
  std::cout << "status a: " << stat << std::endl;

  // Find the best hand in the given 7 cards
  stat = H.findBestHand();
  std::cout << "status b: " << stat << std::endl;

  // Print out the best hand
  std::cout << "hand code: " << H.handCode << std::endl;
  std::vector<int> F = H.getBestFace();
  std::vector<int> S = H.getBestSuit();
  for(int i=0; i<5; i++) {
    std::cout << "Card " << i+1 << " ::: face: " << F[i] << " , suit: " << S[i] << std::endl;
  }
  
  return 0;
  
}
```








### ``deck`` Class

This is the class where we store the cards in the deck (or those left in the deck at least), and where we deal those cards from.

#### Class var : private : ``bool`` : ``deckSet_``

Has the deck been initialised.

#### Class var : private : ``vector<int>`` : ``deckFace_``

The face values of the cards in the deck, each ith element has a corresponding suit value in ``deckSuit_``.

#### Class var : private : ``vector<int>`` : ``deckSuit_``

The face values of the cards in the deck, each ith element has a corresponding face value in ``deckFace_``.

#### Class var : private : ``bool`` : ``indexSet_``

Has the array ``deckIndex_`` been initialised.

#### Class var : private : ``vector<int>`` : ``deckIndex_``

An indexing array, containing all the integers in ``[0,numCards-1]``. This is the array that is shuffled in order to pull random cards from the ``deckFace_`` and ``deckSuit_`` arrays.

#### Class var : private : ``int`` : ``numCards_``

The number of cards left in the deck (i.e. 52 minus the number of cards removed).

#### Class var : private : ``bool`` : ``deckShuffled_``

Has the index array been shuffled.

#### Class var : private : ``bool`` : ``dealDone_``

Has a deal been done at some point, i.e. do the vectors ``dealFace_`` and ``dealSuit_`` contain data.

#### Class var : private : ``int`` : ``numDealt_``

The number of cards that have been dealt into the vectors ``dealFace_`` and ``dealSuit_``.

#### Class var : private : ``vector<int>`` : ``dealFace_``

Then face values of the cards pulled to the array ``deckFace_``. Note: each card has a corresponding face value in ``dealSuit_``. 

#### Class var : private : ``vector<int>`` : ``dealSuit_``

Then face values of the cards pulled to the array ``deckSuit_``. Note: each card has a corresponding face value in ``dealFace``. 

#### Class fn : ``void`` : ``setDeckFull``

Destroy any data in the ``deckFace_`` and ``deckSuit_`` vectors, then populate them with 52 cards sequentially.

#### Class fn : ``vector<int>, vector<int> -> int`` : ``setDeckPartial``

Destroy any data in the ``deckFace_`` and ``deckSuit_`` vectors, then populate the deck with 52 cards minus those given in input vectors, the inputs are (in order)
- ``igFace`` :: ``vector<int>`` :: The face values of the cards not to add to deck.
- ``igSuit`` :: ``vector<int>`` :: The suit values of the cards not to add to deck.

Returns:
- 0 :: Function completed successfully.
- -1 :: The arrays ``igFace`` and ``igSuit`` are of different lengths
- -2 :: The arrays ``igFace`` and ``igSuit`` have a size of 52 or greater, we need to leave at least 1 card in the deck.

Note: We require ``igFace.size()==igSuit.size()``.

Note: On completion of this routine ``deckFace_.size()=(52-igFace.size())``.

Note: There are no input error checks performed in this routine. This is a cost measure as it will likely be called many times, so we must be careful with this routine.

#### Class fn : ``int -> void`` : ``setDeckIndex``

Destroy any data in ``deckIndex_`` then repopulate based on input integer ``maxIndex`` such that ``deckIndex_`` is an array of length ``maxIndex`` containing all the integers in ``[0,maxIndex-1]``.

#### Class fn : ``vector<int>, vector<int> -> int`` : ``remCards``

Remove cards from the deck, i.e. strip the cards given in input vectors from the vectors ``deckFace_`` and ``deckSuit_``. Inputs are
- ``remFace`` :: ``vector<int>`` :: The face values of the cards to remove from the deck.
- ``remSuit`` :: ``vector<int>`` :: The suit values of the cards to remove from the deck. Note each ith element of ``remSuit`` is the suit of the ith element of ``remFace``.

Note: No error checks are done on inputs as this routine will be called many times, so be careful with calling this routine.

#### Class fn : ``void`` : ``shuffleI``

Shuffle the array ``deckIndex_``.

#### Class fn : ``int -> int`` : ``dealCards``

Deal cards from the ``deckFace_`` and ``deckSuit_`` vectors into the ``dealFace_`` and ``dealSuit_`` vectors.

Note: if ``deckIndex_`` has not been shuffled (i.e. ``deckShuffled_==false``) this function will just pull cards from the end of the deck vectors sequentially.

Note: if ``deckIndex_`` has been shuffled and then some cards have been removed from ``deckFace_`` and ``deckSuit_`` with ``remCards`` and ``shuffleI`` has not been called again then this array may return cards no longer in the deck. To avoid this once ``remCards`` has been called then call ``setDeckIndex(numCards_)`` followed by ``shuffleI()``.

Note: dealCards does not delete dealt cards from the deck array, this is so we can run multiple times with the same partial deck after setting known cards.

#### Class fn : ``void -> bool`` : ``getDeckSet``

Return ``deckSet_``.

#### Class fn : ``void -> vector<int>`` : ``getDeckFace``

Return ``deckFace_``.

#### Class fn : ``void -> vector<int>`` : ``getDeckSuit`

Return ``deckSuit_``.

#### Class fn : ``void -> vector<int>`` : ``getDeckIndex`

Return ``deckIndex_``.

#### Class fn : ``void -> int`` : ``getNumCards`

Return ``numCards_``.

#### Class fn : ``void -> vector<int>`` : ``getDealFace`

Return ``dealFace_``.

#### Class fn : ``void -> vector<int>`` : ``getDealSuit`

Return ``dealSuit_``.

#### Example

An example of the use of the ``deck`` array is given below. Here we initialise the deck without AS, 3D, 4H. We then remove AC, 2C, 6C, 7H from the deck, printing the deck as it is along with the shuffled index array.

Then we deal a hand of 2 cards and print, then deal a hand of 5 cards and print.

Note this can be found at ``examples/deck_example.cpp``.

```
#include<iostream>

#include "src/holdem/hand.h"
#include "src/holdem/deck.h"

int main() {

  // Initialise the deck class
  deck D;

  // Iniailtise the deck, but without AS, 3D, 4H
  static const int igFarr[] = {1,3,4};
  static const int igSarr[] = {1,4,3};  
  std::vector<int> igF(igFarr, igFarr + sizeof(igFarr) / sizeof(igFarr[0]) );
  std::vector<int> igS(igSarr, igSarr + sizeof(igSarr) / sizeof(igSarr[0]) );
  D.setDeckPartial(igF,igS);

  // Remove AC, 2C, 6C, 7H from the deck
  static const int Farr[] = {1,2,6,7};
  static const int Sarr[] = {2,2,2,3};  
  std::vector<int> RF(Farr, Farr + sizeof(Farr) / sizeof(Farr[0]) );
  std::vector<int> RS(Sarr, Sarr + sizeof(Sarr) / sizeof(Sarr[0]) );
  D.remCards(RF,RS);

  // Get face and deck values as well as the index array shuffled
  std::vector<int> F;
  F = D.getDeckFace();
  std::vector<int> S;
  S = D.getDeckSuit();
  
  D.shuffleI();
  std::vector<int> Index;
  Index = D.getDeckIndex();

  // Print the cards
  for (int i=0; i<D.getNumCards(); i++) {
    std::cout << "card i " << F[i] << "   " << S[i] << "  " << Index[i] << std::endl;
  }
  std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;

  // Deal a hand of cards
  std::vector<int> DF;
  std::vector<int> DS;
  D.dealCards(2);
  DF = D.getDealFace();
  DS = D.getDealSuit();

  // Print the dealt hand
  std::cout << "First hand of 2 cards:" << std::endl;
  for (int i=0; i<2; i++) {
    std::cout << "card i, Face val: " << DF[i] << ", Suit val: " << DS[i] << std::endl;
  }
  std::cout <<  "Num cards left in deck: " << D.getNumCards() << std::endl;
  
  std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;

  // Deal a second hand of 5 cards
  D.dealCards(5);
  DF = D.getDealFace();
  DS = D.getDealSuit();

  // Print the dealt hand
  std::cout << "Second hand of 5 cards:" <<std::endl;
  for (int i=0; i<5; i++) {
    std::cout << "card i, Face val: " << DF[i] << ", Suit val: " << DS[i] << std::endl;
  }
  std::cout <<  "Num cards left in deck: " << D.getNumCards() << std::endl;
  
  return 0;
  
}
```






### ``table`` Class

A class that contains everything we would find at a table (excluding bets), with players (numbered from 0), a deck and table cards. It is within this class we can deal cards from a deck to multiple players holds and to the table cards. Furthermore we can assess the winner at the table (either with perfect information or by dealing from a shuffled deck) and run a Monte Carlo simulation.

In general we use this routine by setting any known cards, then dealing random cards to fill up any unknown cards, then we find the winner from all cards and record.

#### Class fn : ``int->int`` : ``setNoPlayers``

Set the number of players at the table, minimum 2 players. No hard coded maximum but eventually we will run out of cards to deal which will cause an exit with an error.

Return ``-1`` if input is less than 2 and ``0`` on successful completion.

#### Class fn : ``int,vector<int>,vector<int>->int`` : ``setHoldCards``

Set the hold cards of a given player.

Inputs:
1. Integer, the players number (where players are indexed from 0) for whom to set the hold cards.
2. Integer, vector, the face values of the hold cards for the player.
3. Integer, vector, the suit values of the hold cards for the player.

The input indexes must be of length 3.

Return ``0`` on success, ``-1`` if input vectors are of differing lengths, ``-2`` if input vectors have more than 2 elements and ``-3`` if the input player does not exist at the table.

Note: All cards set are removed from the deck.

#### Class fn : ``int,int,int->int`` : ``setHoldCard``

The same as ``setHoldCards``, but this routine sets a single card in the players hold (adding it a known hold card if present).

Note: All cards set are removed from the deck.

#### Class fn : ``vector<int>,vector<int>->int`` : ``setFlop``

Similar to ``setHoldCards``, this sets the flop values on the table for all players with two input vectors being face then suit values of the flop cards.

Note: All cards set are removed from the deck.

#### Class fn : ``int,int->int`` : ``setTurn``

Similar to ``setHoldCard``, this sets the turn values on the table for all players with two input integers being face then suit values of the turn card.

Note: All cards set are removed from the deck.

#### Class fn : ``int,int->int`` : ``setTurn``

Similar to ``setHoldCard``, this sets the river values on the table for all players with two input integers being face then suit values of the river card.

Note: All cards set are removed from the deck.

#### Class fn : ``void`` : ``shuffleDeckIndex``

Shuffle the index values for the cards left in the deck.

#### Class fn : ``void->int`` : ``dealFlopTurnRiver``

Deal cards to the flop turn and river from the deck. This is done by shuffling an array of indexes pointing to each remaining card in the deck (if not already shuffled), then using this to deal cards to the flopTurnRiver. This adds to the cards that may have been set by earlier routines.

Note: Once a routine has been used that involves shuffling the index array (like this one) do not use any of the set routines. Nor should the deck index be shuffled again.

Return ``0`` on success or ``1`` if the flop, turn & river have all been set.

#### Class fn : ``int->int`` : ``dealHold``

Deal hold cards to the player given by input integer (player indexing starts at 0). This will deal the hold up to 2 cards, or do nothing if the player has 2 cards set in their hold. This adds to the cards that may have been set by earlier routines.

Returns ``0`` on success, ``1`` if there are already 2 cards in the players hold or ``-1`` if the player given by input integer is not at the table.

#### Class fn : ``void->int`` : ``dealAll``

Deal the flop, turn and river (by filling up any space where cards have not been set). Then deal the hold cards (that have not been set) to all players at the table.

Return ``0`` on success.

#### Class fn : ``void->int`` : ``findWinner``

Find a winner from all hands at the table. Return ``0`` if it is a draw with a return of ``>0`` is player who won. Wins/losses/draws/hands are recorded internally and can be recovered with get functions (see below).

Return ``>0`` on success and ``-1`` if required cards (i.e. all holds and flop, turn & river) have not been either set or dealt.

#### Class fn : ``void->int`` : ``resetTableToKnown``

Reset the table to the state where only cards that have been specifically set are left on the table. I.e. return any cards that have been dealt back to the deck.

#### Class fn : ``void->int`` : ``resetTable``

Completely reset the table to its initial state, destroying all data.

#### Class fn : ``int->void`` : ``MC``

Run a Monte Carlo simulation, this can be done after setting any cards one wishes (which remain constant over all Monte Carlo sims). This is done for a number of loops specified with the input integer.

#### Class fn : ``int->void`` : ``MCP``

Run a Monte Carlo simulation using the prime method, this can be done after setting any cards one wishes (which remain constant over all Monte Carlo sims). This is done for a number of loops specified with the input integer. This should be more efficient than using ``MC``.

#### Class fn : ``void->int`` : ``getNumRuns``

Find the number of Monte Carlo runs that have been carried out. I.e. the number of times the routine ``findWinner`` has been successfully called.

#### Class fn : ``void->vector<int>`` : ``getWins``

Return an array of the number of times each player has won, where each ith element refers to player i.

#### Class fn : ``void->vector<double>`` : ``getWinsP``

Return an array of the number of times each player has won divided by total number of runs, where each ith element refers to player i.

#### Class fn : ``void->vector<int>`` : ``getDraws``

Return an array of the number of times each player has drawn, where each ith element refers to player i.

#### Class fn : ``void->vector<double>`` : ``getDrawsP``

Return an array of the number of times each player has drawn divided by total number of runs, where each ith element refers to player i.

#### Class fn : ``int->vector<int>`` : ``getWinsPP``

Return an array of the number of times the player given by the input integer has won with each of the 10 hand types. Let the return array be given by ``A=getWinsPP(1)`` then ``A.size()==10`` and:

- ``A(0)`` : Num high card wins.
- ``A(1)`` : Num one pair wins.
- ``A(2)`` : Num two pair wins.
- ``A(3)`` : Num three of a kind wins.
- ``A(4)`` : Num straight wins.
- ``A(5)`` : Num flush wins.
- ``A(6)`` : Num full house wins.
- ``A(7)`` : Num four of a kind wins.
- ``A(8)`` : Num straight flush wins.
- ``A(9)`` : Num royal flush wins.

#### Class fn : ``int->vector<double>`` : ``getWinsPPp``

Return an array of the number of times the player given by the input integer has won with each of the 10 hand types divided by the total number of runs (see ``getWinsPP``).

#### Class fn : ``int->vector<int>`` : ``getDrawsPP``

Return an array of the number of times the player given by the input integer has tied with each of the 10 hand types. Let the return array be given by ``A=getWinsPP(1)`` then ``A.size()==10`` and:

- ``A(0)`` : Num high card wins.
- ``A(1)`` : Num one pair wins.
- ``A(2)`` : Num two pair wins.
- ``A(3)`` : Num three of a kind wins.
- ``A(4)`` : Num straight wins.
- ``A(5)`` : Num flush wins.
- ``A(6)`` : Num full house wins.
- ``A(7)`` : Num four of a kind wins.
- ``A(8)`` : Num straight flush wins.
- ``A(9)`` : Num royal flush wins.

#### Class fn : ``int->vector<double>`` : ``getDrawsPPp``

Return an array of the number of times the player given by the input integer has tied with each of the 10 hand types divided by the total number of runs (see ``getDrawsPP``).

#### Class fn : ``int->vector<int>`` : ``getHandsPP``

Return an array of the number of times the player given by the input integer has finished a game with each of the 10 hand types. Let the return array be given by ``A=getWinsPP(1)`` then ``A.size()==10`` and

- ``A(0)`` : Num high card wins.
- ``A(1)`` : Num one pair wins.
- ``A(2)`` : Num two pair wins.
- ``A(3)`` : Num three of a kind wins.
- ``A(4)`` : Num straight wins.
- ``A(5)`` : Num flush wins.
- ``A(6)`` : Num full house wins.
- ``A(7)`` : Num four of a kind wins.
- ``A(8)`` : Num straight flush wins.
- ``A(9)`` : Num royal flush wins.

#### Class fn : ``int->vector<double>`` : ``getHandsPPp``

Return an array of the number of times the player given by the input integer has finished a game with each of the 10 hand types divided by the total number of runs (see ``getHandsPP``).

#### Class fn : ``void->int`` : ``getNumCardsInDeck``

Return the number of cards `left in the deck', i.e. 52 minus the number of set cards minus the number of dealt cards.

















## Python Use

To compile for Python run ``make python`` and import the module ``holdEm``. In this section we approach just the python usage, ignoring the exact structure of the C++ routines.











### ``hand`` Class

This works as the Python version of the hand class from C++ docs, where we set the 7 cards from the hold, flop, turn and river and then find the best 5 card HoldEm hand from these cards.

#### Class fn : ``int[7],int[7]->int`` : ``pSetCardsFull``

Set the cards in the hand and on the table, where the first input array refers to the face values of the cards and the second to the suit values. Return 0 on success. For example we set the hand AS, 2C, 4H, 6D, 8C, AD, 6H with
```
H = holdEm.hand()
stat = H.pSetCardsFull((1,2,4,6,8,14,6),(1,2,3,4,2,4,3))
```

#### Class fn : ``int[2],int[2],int[3],int[3],int,int,int,int->int`` : ``pSetCards``

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

#### Class fn : ``None->int[7]`` : ``getCardsFace``

Return the face values of the 7 cards from the hole, flop, turn and river.

#### Class fn : ``None->int[7]`` : ``getCardsSuit``

Return the suit values of the 7 cards from the hole, flop, turn and river.

#### Class fn : ``none->int`` : ``findBestHand``

Use the cards set with ``pSetCards`` or ``pSetCardsFull`` after either of these routines has been ran to find the best 5 card Texas HoldEm hand possible. Returns 0 on success. The calculated hands can then be returned with the following routines.

#### Class fn : ``None->int`` : ``getHandCode``

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

#### Class fn : ``None->int[5]`` : ``getBestFace``

Return the face value of the cards that make up the best hand found with ``findBestHand``. See section on ``bestFace_`` for a more in depth description.

#### Class fn : ``None->int[5]`` : ``getBestSuit``

Return the suit values of the cards that make up the best hand found with ``findBestHand``. Note each ith element of the returned array is the suit of the corresponding face value returned with ``getBestFace``.

####  Example

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























### ``deck`` Class

The Python wrapping of the C++ ``deck`` class, note class variables are exactly the same as in the C++ case and as such are omitted here.

#### Class fn : ``void`` : ``setDeckFull``

Populate the deck with 52 cards, not shuffled.

#### Class fn : ``int[],int[]->int`` : ``setDeckFull``

Initialise the deck of cards with all 52 cards excluding those given in the two input arrays, where these arrays are (respectively)
- ``igFace`` :: The face values of the cards not to add to deck.
- ``igSuit`` :: The suit values of the cards not to add to deck.

Return 0 on success and -1 if the face and suit input arrays are of differing sizes.

#### Class fn : ``int->void`` : ``setDeckIndex``

Set the deck index array based on input ``maxIndex``, such that the deckIndex array is of length ``maxIndex`` with all integers in ``[0,maxIndex-1]`` represented.

This is the array that is shuffled, and its initialisation is required in order to deal cards from the deck.

#### Class fn : ``int[],int[]->int`` : ``remCards``

Remove the cards given in the two input arrays from the deck, where the two inputs are (respectively)
- ``remFace`` :: The face values of the cards to remove from the deck.
- ``remSuit`` :: The suit values of the cards to remove from the deck. Note each ith element of ``remSuit`` is the suit of the ith element of ``remFace``.

Returns 0 on success and -1 if the card to be removed from the deck is not actually in the deck.

#### Class fn : ``void`` : ``shuffleI``

Shuffle the index array, this must be done between calls to ``remCards`` and ``dealCards``.

#### Class fn : ``int -> int`` : ``dealCards``

Deal cards from the ``deckFace_`` and ``deckSuit_`` vectors into the ``dealFace_`` and ``dealSuit_`` vectors.

Note: if ``deckIndex_`` has not been shuffled (i.e. ``deckShuffled_==false``) this function will just pull cards from the end of the deck vectors sequentially.

Note: if ``deckIndex_`` has been shuffled and then some cards have been removed from ``deckFace_`` and ``deckSuit_`` with ``remCards`` and ``shuffleI`` has not been called again then this array may return cards no longer in the deck. To avoid this once ``remCards`` has been called then call ``setDeckIndex(numCards_)`` followed by ``shuffleI()``.

#### Class fn : ``void -> bool`` : ``getDeckSet``

Return ``deckSet_``.

#### Class fn : ``void -> int[]`` : ``getDeckFace``

Return ``deckFace_``.

#### Class fn : ``void -> int[]`` : ``getDeckSuit`

Return ``deckSuit_``.

#### Class fn : ``void -> int[]`` : ``getDeckIndex`

Return ``deckIndex_``.

#### Class fn : ``void -> int`` : ``getNumCards`

Return ``numCards_``.

#### Class fn : ``void -> int[]`` : ``getDealFace`

Return ``dealFace_``.

#### Class fn : ``void -> int[]`` : ``getDealSuit`

Return ``dealSuit_``.

#### Example

The below example is a Python script that uses the ``holdEm`` module (compiled with ``make python``) and the ``deck`` class. Here we first initialise a deck without 3S and 4C, then remove AH and 2D from the deck and print the remaining cards in the deck.

We then shuffle the indexes and deal 40 shuffled cards into one hand and 10 shuffled cards into another, printing these hands.

This python script can be found in ``examples/deck_example.py``.

```
import holdEm

# Class initialisation
D = holdEm.deck()

# Initialise a deck without a 3S and 4C
D.setDeckPartial((3,4),(1,2))

# Now remove the AH, 2D from the deck
D.remCards((1,2),(3,4))

# Get all the cards to have a look at
faces = D.getDeckFace()
suits = D.getDeckSuit()

print("\nNum cards in deck ", len(faces), "\n")
for i in range(len(faces)):
    print("Card ", i, " : ", faces[i], "     ", suits[i])

# Shuffle the cards
D.shuffleI()
    
# Deal one hand
stat = D.dealCards(40)
print("\nCurrent status ", stat ,"\n")
hand1Face = D.getDealFace()
hand1Suit = D.getDealSuit()

# Deal second hand
stat = D.dealCards(10)
print("\nCurrent status ", stat ,"\n")
hand2Face = D.getDealFace()
hand2Suit = D.getDealSuit()

# Print both hands
print("\n\n\nHand 1:\n")
for i in range(len(hand1Face)):
    print("Card ", i+1, " : ", hand1Face[i], "     ", hand1Suit[i])

# Print both hands
print("\n\n\nHand 2:\n")
for i in range(len(hand2Face)):
    print("Card ", i+1, " : ", hand2Face[i], "     ", hand2Suit[i])
```































