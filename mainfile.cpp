#include<iostream>

#include "src/holdem/hand.h"

int main() {

  /*
    Initial example for the hand class.
  */
  
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
