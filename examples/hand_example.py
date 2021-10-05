import holdEm

H = holdEm.hand()

stat = H.SetCardsFull((1,2,4,6,8,14,6),(1,2,3,4,2,4,3))
print("Stat: ", stat)
print("All cards face vals: ", H.getCardsFace())
print("All cards suit vals: ", H.getCardsSuit())

H.findBestHand()
print("Stat: ", stat)
print("Best hand code: ", H.getHandCode())
print("Best hand face: ", H.getBestFace())
print("Best hand suit: ", H.getBestSuit())
