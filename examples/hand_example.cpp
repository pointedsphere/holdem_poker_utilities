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
