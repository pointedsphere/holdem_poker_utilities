#ifndef LOOKUPBESTHANDPRIMES_H_
#define LOOKUPBESTHANDPRIMES_H_

#include <vector>
#include <unordered_map>

// An structure to store the two lookup values of interest
struct handDat {
  int HC;
  long long int MFVP;
};


std::vector<long long int> lookupBestHandPrimes(\
                  int AP1, int AP2, int AP3, int AP4, int AP5, int AP6, int AP7,\
                  int FP1, int FP2, int FP3, int FP4, int FP5, int FP6, int FP7,\
                  int SP1, int SP2, int SP3, int SP4, int SP5, int SP6, int SP7);

const extern std::unordered_map< long long int, const handDat > RSF;
const extern std::unordered_map< long int, const handDat > FKFH;
const extern std::unordered_map< long int, const handDat > Fl;
const extern std::unordered_map< long int, const handDat > RemHands;

#endif
