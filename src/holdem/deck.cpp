#include <iostream>
#include <vector>

#include "deck.h"






/*
  Building the initial deck (or the part we don't know about
*/

// Set the full decks class variables with all 52 cards in order
void deck::setDeckFull()
{
  // Do for the 4 suits
  for (int s=1; s<5; s++) {
    for (int f=2; f<15; f++) {
      deckFace.push_back(f);
      deckSuit.push_back(s);
    }
  }
};






/*
  Getting things from the deck
*/

std::vector<int> deck::getDeckFace()
{
  return deckFace;
};
std::vector<int> deck::getDeckSuit()
{
  return deckSuit;
};
