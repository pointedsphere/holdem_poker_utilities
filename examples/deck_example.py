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
for i in range(len(faces)):
    print("Card ", i, " : ", faces[i], "     ", suits[i])

# Shuffle the cards
D.shuffleI()
    
# Deal one hand
stat = D.dealCards(40)
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
    print("Card ", i+1, " : ", hand1Face[i], "     ", hand1Suit[i])

# Print both hands
print("\n\n\nHand 2:\n")
for i in range(len(hand2Face)):
    print("Card ", i+1, " : ", hand2Face[i], "     ", hand2Suit[i])



