import sys
import csv

outFile = "switchBestHandPrimes.cpp"

# Function header
with open(outFile, "a") as f:

    f.write("#include <vector>\n")
    f.write("#include <iostream>\n")
    f.write("#include <stdlib.h>\n\n")
    f.write("#include \"switchBestHandPrimes.h\"\n\n")
    
    f.write("std::vector<int> switchBestHandPrimes(int AP1, int AP2, int AP3, int AP4, int AP5, int AP6, int AP7,\\\n")
    f.write("                                      int FP1, int FP2, int FP3, int FP4, int FP5, int FP6, int FP7,\\\n ")
    f.write("                                     int SP1, int SP2, int SP3, int SP4, int SP5, int SP6, int SP7) \n{\n\n")
    f.write("  /*\n")
    f.write("    Return the integer Hand Code value from the input face and suit card values\n")
    f.write("    Prime values for all calrds {AP1,...,AP7} take a sequential form from 2 to ace\n")
    f.write("    for one suit then 2 to ace for the next suit, mapping each card to a\n")
    f.write("    prime in [2,239] i.e.\n")
    f.write("      2S == 2\n")
    f.write("      3S == 3\n")
    f.write("      4S == 5\n")
    f.write("      5S == 7\n")
    f.write("      ...\n")
    f.write("      KS == 37\n")
    f.write("      AS == 41\n")
    f.write("      2C == 43\n")
    f.write("      3C == 47\n")
    f.write("      ...\n")
    f.write("    and so on for all cards in the deck\n\n")
    f.write("    Face value inputs {FP1,...,FP7} must be the prime face values, the same regardless\n")
    f.write("    of suit value (prime val == face val):\n")
    f.write("      2  == 2\n")
    f.write("      3  == 3\n")
    f.write("      5  == 4\n")
    f.write("      7  == 5\n")
    f.write("      11 == 6\n")
    f.write("      13 == 7\n")
    f.write("      17 == 8\n")
    f.write("      19 == 9\n")
    f.write("      23 == 10\n")
    f.write("      29 == J\n")
    f.write("      31 == Q\n")
    f.write("      37 == K\n")
    f.write("      41 == A\n")
    f.write("    and suit value inputs {SP1,...SP7} are the prime suit values, the same regardless\n")
    f.write("    of face value (prime val == suit):\n")
    f.write("      2  == Spades\n")
    f.write("      3  == Clubs\n")
    f.write("      5  == Hearts\n")
    f.write("      7  == Diamonds\n\n")
    f.write("    Note: exact suit values chosen does not matter, as long as suit value is always a\n")
    f.write("          consistent unique prime in [2,7].\n")
    f.write("  */\n\n")



    #
    # Vector for output values
    #    Element 0 is hand code
    #    Element 1 is comparison product
    #
    f.write("  std::vector<int> HCvec;\n\n")
    
    

    #
    # Flush
    #

    f.write("  /*\n")
    f.write("    We first check for a flush as thsi requires a trivial amount of switch cases and will allow\n")
    f.write("    us to skip the check for straight and royal flush if we dont have any form of flush.\n")
    f.write("    this reuires the product of the prime suit values.\n")
    f.write("  */\n\n")
    
    # Initial switch declaration
    f.write("  // Boolean to note if we have a flush or not.\n")
    f.write("  bool gotFlush;\n\n")
    
    f.write("  // Calculate the product value required for the flush hands from suit primes,\n")
    f.write("  // I.e. product of card values from the ``suit prime'' deck.\n")
    f.write("  const long int SuitProd = (long)SP1 * (long)SP2 * (long)SP3\\\n")
    f.write("    * (long)SP4 * (long)SP5 * (long)SP6 * (long)SP7;\n\n")
    
    f.write("  // Then use a swich statement over all the possible full houses and 4 of a kinds.\n")
    f.write("  // Note: If we find one the function exits in this switch.\n")
    f.write("  // Note: Start with full house checks as they are more likely.\n")
    f.write("  switch(SuitProd) {\n")

    # Load the data from the data file for the suit only hands
    SuitArr = []
    with open("./gen_flush/flush_suit.dat", "r") as fIn:
        for l in fIn:
            if not l.startswith("//"):
                l = l.split(",")
                SuitArr.append((int(l[0]),int(l[1])))
                
    SuitArr = sorted(SuitArr, key=lambda tup: tup[0])

    # Write the switch cases first for full houses, all in this file are flushes
    for i in range(len(SuitArr)):
        f.write("    case ")
        f.write(str(SuitArr[i][0]))
        f.write(" : gotFlush = true;\n")
    f.write("    default : gotFlush = false;\n")

    # Now close that switch 
    f.write("  }\n\n\n\n")    


    
    #
    # Royal and straight flush checks
    #

    f.write("  /*\n")
    f.write("    We now check for the royal and straight flush, as this allows us to dicard the best hands outright.\n\n")

    f.write("    With our `primes' method we can only check for lower hands once we know there is no hand that\n")
    f.write("    relies on both suit and face values of the cards.\n\n")

    f.write("    This does require using the full prime card values, not just the suit and face values so\n")
    f.write("    we need 64 bit long long integers.\n")
    f.write("    NOTE: we only check if there is some form of flush.\n")
    f.write("  */\n\n")

    f.write("  // Only check for a striaght/royal flush if we have a flush of some sort.\n")
    f.write("  if (gotFlush==true) {\n\n")
    
    f.write("    // Calculate the product value required for the Royal and Straight Flush hands,\n")
    f.write("    // I.e. product of card values from the ``all prime'' deck.\n")
    f.write("    const long long int AllProd = (long long)AP1 * (long long)AP2 * (long long)AP3\\\n")
    f.write("      * (long long)AP4 * (long long)AP5 * (long long)AP6 * (long long)AP7;\n\n")
    
    f.write("    // Then use a swich statement over all the possible straight and royal flushes.\n")
    f.write("    // Note: If we find one the function exits in this switch.\n")
    f.write("    // Note: Start with straight flush checks as they are slightly more likely.\n")
    f.write("    switch(AllProd) {\n")

    # Load the data from the data file for the straight and royal flushes
    SRFarr = []
    with open("./gen_straight_royal_flush/straightRoyalFlush.dat", "r") as fIn:
        for l in fIn:
            if not l.startswith("//"):
                l = l.split(",")
                SRFarr.append((int(l[0]),int(l[1]),int(l[2])))
                
    SRFarr = sorted(SRFarr, key=lambda tup: tup[0])

    # Print the switch cases first for the straight flushes
    for i in range(len(SRFarr)):
        if (SRFarr[i][2]==9):
            f.write("    case ")
            f.write(str(SRFarr[i][0]))
            f.write(" : HCvec.push_back(")
            f.write(str(SRFarr[i][2]))
            f.write("); HCvec.push_back(")
            f.write(str(SRFarr[i][1]))
            f.write("); return HCvec;\n")

    # And then for the royal flushes
    for i in range(len(SRFarr)):
        if (SRFarr[i][2]==10):
            f.write("    case ")
            f.write(str(SRFarr[i][0]))
            f.write(" : HCvec.push_back(")
            f.write(str(SRFarr[i][2]))
            f.write("); HCvec.push_back(")
            f.write(str(SRFarr[i][1]))
            f.write("); return HCvec;\n")
            
    # Now close that switch and if
    f.write("    }\n\n")
    f.write("  }\n")

    
    #
    # Four of a kind and full house
    #

    f.write("  \n\n\n\n\n  /*\n")
    f.write("    We now check for four of a kind and full house, this requires the prime product from the\n")
    f.write("    prime face values of the cards only.\n")
    f.write("  */\n\n")
    
    # Initial switch declaration
    f.write("  // Calculate the product value required for the four of a kind and full house hands,\n")
    f.write("  // I.e. product of card values from the ``face prime'' deck.\n")
    f.write("  const long long int FaceProd = (long long)FP1 * (long long)FP2 * (long long)FP3\\\n")
    f.write("    * (long long)FP4 * (long long)FP5 * (long long)FP6 * (long long)FP7;\n\n")
    f.write("  // Then use a swich statement over all the possible full houses and 4 of a kinds.\n")
    f.write("  // Note: If we find one the function exits in this switch.\n")
    f.write("  // Note: Start with full house checks as they are more likely.\n")
    f.write("  switch(FaceProd) {\n")

    # Load the data from the data file for the face only hands
    FaceArr = []
    with open("./gen_face_hands/faceHands.dat", "r") as fIn:
        for l in fIn:
            if not l.startswith("//"):
                l = l.split(",")
                FaceArr.append((int(l[0]),int(l[1]),int(l[2])))
                
    FaceArr = sorted(FaceArr, key=lambda tup: tup[0])

    # Write the switch cases first for full houses
    for i in range(len(FaceArr)):
        if (FaceArr[i][2]==7):
            f.write("    case ")
            f.write(str(FaceArr[i][0]))
            f.write(" : HCvec.push_back(")
            f.write(str(FaceArr[i][2]))
            f.write("); HCvec.push_back(")
            f.write(str(FaceArr[i][1]))
            f.write("); return HCvec;\n")

    # And then check for 4 of a kind hands
    for i in range(len(FaceArr)):
        if (FaceArr[i][2]==8):
            f.write("    case ")
            f.write(str(FaceArr[i][0]))
            f.write(" : HCvec.push_back(")
            f.write(str(FaceArr[i][2]))
            f.write("); HCvec.push_back(")
            f.write(str(FaceArr[i][1]))
            f.write("); return HCvec;\n")

    # Now close that switch 
    f.write("  }")


    
    #
    # Flush
    #
    
    f.write("  \n\n\n\n\n  /*\n")
    f.write("    We now check for a flush, using boolean from previous check.\n")
    f.write("  */\n\n")

    # Load the data from the data file for the face only hands
    FlushFaceArr = []
    with open("./gen_flush/flush_face.dat", "r") as fIn:
        for l in fIn:
            if not l.startswith("//"):
                l = l.split(",")
                FlushFaceArr.append((int(l[0]),int(l[1]),int(l[2])))
                
    FlushFaceArr = sorted(FlushFaceArr, key=lambda tup: tup[0])

    # Only check if we have a flush
    f.write("  if (gotFlush==true) {\n")
    f.write("    switch(FaceProd) {\n")
    
    for i in range(len(FlushFaceArr)):
        if (FlushFaceArr[i][2]==6):
            f.write("      case ")
            f.write(str(FlushFaceArr[i][0]))
            f.write(" : HCvec.push_back(")
            f.write(str(FlushFaceArr[i][2]))
            f.write("); HCvec.push_back(")
            f.write(str(FlushFaceArr[i][1]))
            f.write("); return HCvec;\n")
    # Now close that switch
    f.write("    }\n")
    f.write("  }\n")



    
    #
    # Straight, 3 of a kind, 2 pair, pair
    #
    
    f.write("  \n\n\n\n\n  /*\n")
    f.write("    We now check for a straight, 3 of a kind, 2 pair and pair. If we can't find these hands\n")
    f.write("    then the only option left is a high card.\n")
    f.write("  */\n\n")
    
    # Initial switch declaration
    f.write("  // Use the previously found FaceArr,\n")
    f.write("  // Then use a swich statement over all the possible straight 2 of a kind and pairs hands.\n")
    f.write("  // Note: If we find one the function exits in this switch.\n")
    f.write("  // Note: Start with pair and work towards better hands.\n")
    f.write("  switch(FaceProd) {\n")
    
    # Write the pair case
    for i in range(len(FaceArr)):
        if (FaceArr[i][2]==2):
            f.write("    case ")
            f.write(str(FaceArr[i][0]))
            f.write(" : HCvec.push_back(")
            f.write(str(FaceArr[i][2]))
            f.write("); HCvec.push_back(")
            f.write(str(FaceArr[i][1]))
            f.write("); return HCvec;\n")

    # Then check for two pair
    for i in range(len(FaceArr)):
        if (FaceArr[i][2]==3):
            f.write("    case ")
            f.write(str(FaceArr[i][0]))
            f.write(" : HCvec.push_back(")
            f.write(str(FaceArr[i][2]))
            f.write("); HCvec.push_back(")
            f.write(str(FaceArr[i][1]))
            f.write("); return HCvec;\n")

    # Then check for three of a kind
    for i in range(len(FaceArr)):
        if (FaceArr[i][2]==4):
            f.write("    case ")
            f.write(str(FaceArr[i][0]))
            f.write(" : HCvec.push_back(")
            f.write(str(FaceArr[i][2]))
            f.write("); HCvec.push_back(")
            f.write(str(FaceArr[i][1]))
            f.write("); return HCvec;\n")

    # And then for a straight
    for i in range(len(FaceArr)):
        if (FaceArr[i][2]==5):
            f.write("    case ")
            f.write(str(FaceArr[i][0]))
            f.write(" : HCvec.push_back(")
            f.write(str(FaceArr[i][2]))
            f.write("); HCvec.push_back(")
            f.write(str(FaceArr[i][1]))
            f.write("); return HCvec;\n")

    # And finally for a high card
    for i in range(len(FaceArr)):
        if (FaceArr[i][2]==1):
            f.write("    case ")
            f.write(str(FaceArr[i][0]))
            f.write(" : HCvec.push_back(")
            f.write(str(FaceArr[i][2]))
            f.write("); HCvec.push_back(")
            f.write(str(FaceArr[i][1]))
            f.write("); return HCvec;\n")
            
    # Now close that switch 
    f.write("  }")  




    #
    # High card
    #
    
    f.write("  \n\n\n\n\n  /*\n")
    f.write("    If we have made it this far the only option left is that we have failed.\n")
    f.write("  */\n\n")

    f.write("  std::cout << \"ERROR : Unable to find a hand from given cards\" << std::endl;\n")
    f.write("  std::cout << \"        Current card prime values are:\" << std::endl;\n")
    f.write("    std::cout << \"        Face prime: \" << FP1")
    f.write("              << \"        Suit prime: \" << SP1")
    f.write("              << \"        Full prime: \" << AP1")
    f.write("              << std::endl;\n")
    f.write("    std::cout << \"        Face prime: \" << FP2")
    f.write("              << \"        Suit prime: \" << SP2")
    f.write("              << \"        Full prime: \" << AP2")
    f.write("              << std::endl;\n")
    f.write("    std::cout << \"        Face prime: \" << FP3")
    f.write("              << \"        Suit prime: \" << SP3")
    f.write("              << \"        Full prime: \" << AP3")
    f.write("              << std::endl;\n")
    f.write("    std::cout << \"        Face prime: \" << FP4")
    f.write("              << \"        Suit prime: \" << SP4")
    f.write("              << \"        Full prime: \" << AP4")
    f.write("              << std::endl;\n")
    f.write("    std::cout << \"        Face prime: \" << FP5")
    f.write("              << \"        Suit prime: \" << SP5")
    f.write("              << \"        Full prime: \" << AP5")
    f.write("              << std::endl;\n")
    f.write("    std::cout << \"        Face prime: \" << FP6")
    f.write("              << \"        Suit prime: \" << SP6")
    f.write("              << \"        Full prime: \" << AP6")
    f.write("              << std::endl;\n")
    f.write("    std::cout << \"        Face prime: \" << FP7")
    f.write("              << \"        Suit prime: \" << SP7")
    f.write("              << \"        Full prime: \" << AP7")
    f.write("              << std::endl;\n")
    f.write("  exit (EXIT_FAILURE);\n\n")
    
    f.write("  return HCvec;\n\n")

    # End of the function
    f.write("}\n\n\n\n")