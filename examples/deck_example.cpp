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
