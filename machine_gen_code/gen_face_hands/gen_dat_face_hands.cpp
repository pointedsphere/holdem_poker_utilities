#include <iostream>
#include  <fstream>
#include   <vector>
#include<algorithm>

#include "../../src/holdem/hand.h"

int main() {

  // Standard face values
  int cardFace[52] = {2,3,4,5,6,7,8,9,10,11,12,13,14,2,3,4,5,6,7,8,9,10,11,12,13,14,\
    2,3,4,5,6,7,8,9,10,11,12,13,14,2,3,4,5,6,7,8,9,10,11,12,13,14};

  // Standard suit values
  int cardSuit[52] = {\
    1,1,1,1,1,1,1,1,1,1,1,1,1,\
    2,2,2,2,2,2,2,2,2,2,2,2,2,\
    3,3,3,3,3,3,3,3,3,3,3,3,3,\
    4,4,4,4,4,4,4,4,4,4,4,4,4};

  // Prime suit values
  int primeSuit[52] = { \
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, \
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, \
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, \
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7 };

  // Prime face values
  int primeFace[52] = { \
    2,3,5,7,11,13,17,19,23,29,31,37,41,	\
    2,3,5,7,11,13,17,19,23,29,31,37,41,	\
    2,3,5,7,11,13,17,19,23,29,31,37,41,	\
    2,3,5,7,11,13,17,19,23,29,31,37,41 };

  // Lowest 52 primes
  int primes[52] = { \
    2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,	\
    109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227, \
    229,233,239 };

  // Initialise a hand class
  hand H;

  // Number of cards in a deck
  int numCards = 52;

  // Temporary integer for calcualtion of prime product
  long long int tmp;

  // Temporary values of the card face and suit values
  std::vector<int> faceTmp;
  std::vector<int> suitTmp;
  int HC;
  
  // A start for checkpoint continuation, 0 to start from scratch
  int aCont = 0;

  // The array of checked prime products
  std::vector<long long int> primeProd;

  // The output arrays
  std::vector<int>           outHandCode;
  std::vector<long long int> outPrimeProduct;

  // Keep track of array size
  int arrSize = 0;
  
  // Allow for opening of output file
  std::ofstream outfile;
  
  for (int a=aCont; a<numCards; a++) {

    std::cout << "\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n" << std::endl;
    std::cout << "Current a : " << a << "\n" << std::endl;
    
    for (int b=0; b<numCards; b++) {

      if (b<a) {

	std::cout << "Current b per done : " << ((double)b/(double)a)*(double)100 << std::endl;
	
	for (int c=0; c<numCards; c++) {

	  if (c<b) {

	    for (int d=0; d<numCards; d++) {

	      if (d<c) {

		for (int e=0; e<numCards; e++) {

		  if (e<d) {

		    for (int f=0; f<numCards; f++) {

		      if (f<e) {

			for (int g=0; g<numCards; g++) {

			  if (g<f) {

			    // Calcualte the product of the prime face values from primeFace
			    tmp = primeFace[a] * primeFace[b] * primeFace[c] * primeFace[d] \
			      * primeFace[e] * primeFace[f] * primeFace[g];

			    // Only consider further if we have not considred this prome product
			    if (std::find(primeProd.begin(), primeProd.end(), tmp) == primeProd.end()) {

			      // Append current prime product to the array of considered prime product
			      primeProd.push_back(tmp);

			      // Set the temp arrays of face and suit values
			      // Note: We arbitrerally omit the flushes by hard coding off suits
			      faceTmp.push_back(cardFace[a]);
  			      faceTmp.push_back(cardFace[b]);
			      faceTmp.push_back(cardFace[c]);
			      faceTmp.push_back(cardFace[d]);
			      faceTmp.push_back(cardFace[e]);
			      faceTmp.push_back(cardFace[f]);
			      faceTmp.push_back(cardFace[g]);
			      suitTmp.push_back(1);
  			      suitTmp.push_back(2);
			      suitTmp.push_back(3);
			      suitTmp.push_back(4);
			      suitTmp.push_back(1);
			      suitTmp.push_back(2);
			      suitTmp.push_back(3);
			      
			      // Then set the cards in the hand class and find the best hand
			      H.SetCardsFull(faceTmp,suitTmp);
			      H.findBestHand();
			      HC = H.handCode;
			      
			      /* Then we only record for :
				     Pair ============= 2
				     Two Pair ========= 3
				     Three of a kind == 4
				     Straight ========= 5
				     Full house ======= 7
				     Four of a kind === 8
			      */
			      if (HC==2 || HC==3 || HC==4 || HC==5 || HC==7 || HC==8) {
				outHandCode.push_back(HC);      // Copy the hand code
				outPrimeProduct.push_back(tmp); // Prime product that gives flush
				arrSize++;                      // And keep track of size of arrays
			      }
			      
			      // Empty out that old tmp arrays
			      faceTmp.clear();
			      suitTmp.clear();
			      
			    }

			  }
			}
		      }
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
    }

    // Write the output hand codes and prime products
    outfile.open ("faceHands.dat",std::ios_base::app); // first we need the file open (for appending)
    for (int o=0; o<arrSize; o++) {
      outfile <<  outPrimeProduct[o] << " , " << outHandCode[o] << "\n";
    }
    // Written this data so clear arrays before next `a' loop
    outHandCode.clear();
    outPrimeProduct.clear();
    arrSize=0;
    // Write a checkpoint
    outfile << "//++//++// CHECKPOINT a == " << a+1 << " //++//++//\n";
    // and close
    outfile.close();

  }
  
  return 0;
  
}




