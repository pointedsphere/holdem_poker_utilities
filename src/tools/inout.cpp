#include<iostream>
#include <fstream>

#include "inout.h"



int write_1D(double write_arr[], int arr_len, std::string fname_out) {
  /* 

     Write the 1D input array, double array version.
     
     INPUTS:
     - write_arr :: Double 1D array, of length arr_len.
     - arr_len   :: Integer, length of array write_arr.
     - fname_out :: String, output filename.

     RETURNS:
     - 0 :: Successful write.
     - 1 :: ERROR :: cannot open file.

   */

  
  // open the output file
  std::ofstream outfile (fname_out);

  // only run if we can open the file
  if (outfile.is_open())
  {
    // Iterare through and write each elment of the row
    for(int count = 0; count < arr_len; count ++) {
        outfile << write_arr[count] << " " ;
    }
    // And we're done, so close everything
    outfile.close();
    return 0;
    
  }
  else {
    // Return with non 0 status as failed to open file
    std::cout << "Unable to open file";
    return 1;
    
  }
  
}



int write_1D(int write_arr[], int arr_len, std::string fname_out) {

  /* 

     Write the 1D input array, integer array version.
     
     INPUTS:
     - write_arr :: Double 1D array, of length arr_len.
     - arr_len   :: Integer, length of array write_arr.
     - fname_out :: String, output filename.

     RETURNS:
     - 0 :: Successful write.
     - 1 :: ERROR :: cannot open file.

   */
  
  // open the output file
  std::ofstream outfile (fname_out);

  // only run if we can open the file
  if (outfile.is_open())
  {
    // Iterare through and write each elment of the row
    for(int count = 0; count < arr_len; count ++) {
        outfile << write_arr[count] << " " ;
    }
    // And we're done, so close everything
    outfile.close();
    return 0;
    
  }
  else {
    // Return with non 0 status as failed to open file
    std::cout << "Unable to open file";
    return 1;
    
  }
  
}



