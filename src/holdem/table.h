
#ifndef TABLE_H_
#define TABLE_H_

#include <vector>

class table
{

private:

  int noPlayers;    // Number of players at table
  int noPlayersSet; // Has the number of players been set
  
public:

  // Constructor
  table() {

    noPlayersSet = false; // Initially no players set
    
  }
  
};


#endif

