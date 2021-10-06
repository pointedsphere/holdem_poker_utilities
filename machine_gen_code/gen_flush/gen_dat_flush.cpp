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

  // Temporary values for checking if a flush exists
  std::vector<int> tmpArr;
  int count2;
  int count3;
  int count5;
  int count7;
  
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
  outfile.open ("flush.dat");
  
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

			    // Calcualte the product of the prime suit values
			    tmp = primeSuit[a] * primeSuit[b] * primeSuit[c] * primeSuit[d] \
			      * primeSuit[e] * primeSuit[f] * primeSuit[g];

			    // Only consider further if we have not considred this prome product
			    if (std::find(primeProd.begin(), primeProd.end(), tmp) == primeProd.end()) {

			      // Append current prime product to the array of considered prime product
			      primeProd.push_back(tmp);

			      // Count the number of suits that are 2,3,5 and 7 by first constructing a vector
			      tmpArr.push_back(primeSuit[a]);
			      tmpArr.push_back(primeSuit[b]);
			      tmpArr.push_back(primeSuit[c]);
			      tmpArr.push_back(primeSuit[d]);
			      tmpArr.push_back(primeSuit[e]);
			      tmpArr.push_back(primeSuit[f]);
			      tmpArr.push_back(primeSuit[g]);

			      count2 = std::count(tmpArr.begin(), tmpArr.end(), 2);
			      count3 = std::count(tmpArr.begin(), tmpArr.end(), 3);
			      count5 = std::count(tmpArr.begin(), tmpArr.end(), 5);
			      count7 = std::count(tmpArr.begin(), tmpArr.end(), 7);
			      
			      if (count2>4 || count3>4 || count5>4 || count7>4) {
				outHandCode.push_back(6);       // Hand code 6 for flush
				outPrimeProduct.push_back(tmp); // Prime product that gives flush
				arrSize++;                      // And keep track of size of arrays
			      }
			      
			      // Empty out that old tmp array
			      tmpArr.clear();
			      
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
    
    for (int o=0; o<arrSize; o++) {
      outfile << outPrimeProduct[o] << " , " << outHandCode[o] << "\n";
    }
    // Written this data so clear arrays before next `a' loop
    outHandCode.clear();
    outPrimeProduct.clear();
    arrSize=0;
  }

  outfile.close();
  
  return 0;
  
}




