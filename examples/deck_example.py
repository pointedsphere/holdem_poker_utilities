import holdEm

# Class initialisation
D = holdEm.deck()

# Initialise a deck without a 3S and 4C
D.setDeckPartial((3,4),(1,2))

# Now remove the AH, 2D from the deck
D.remCards((1,2),(3,4))

# Get all the cards to have a look at
faces = D.getDeckFace()
suits = D.getDeckSuit()

print("\nNum cards in deck ", len(faces), "\n")
print("Initial deck (without removed cards):")
for i in range(len(faces)):
    print("    Card ", "{0:2}".format(i), " : ", "{0:2}".format(faces[i]), "     ", "{0:2}".format(suits[i]))

# Shuffle the cards
D.shuffleI()
    
# Deal one hand
stat = D.dealCards(30)
print("\nCurrent status ", stat ,"\n")
hand1Face = D.getDealFace()
hand1Suit = D.getDealSuit()

# Deal second hand
stat = D.dealCards(10)
print("\nCurrent status ", stat ,"\n")
hand2Face = D.getDealFace()
hand2Suit = D.getDealSuit()

# Print both hands
print("\n\n\nHand 1:\n")
for i in range(len(hand1Face)):
    print("Card ", "{0:2}".format(i+1), " : ", "{0:2}".format(hand1Face[i]), "     ", "{0:2}".format(hand1Suit[i]))

# Print both hands
print("\n\n\nHand 2:\n")
for i in range(len(hand2Face)):
    print("Card ", "{0:2}".format(i+1), " : ", "{0:2}".format(hand2Face[i]), "     ", "{0:2}".format(hand2Suit[i]))

    
