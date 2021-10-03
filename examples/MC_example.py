import holdEm

Np  = 3       # Number of players
Nmc = 1000000 # Numer of monte carlo loops

# Initialise table class, with N players
T = holdEm.table(Np)

# Set player one hold to As Kc
stat = T.setHoldCards(0,(13,13),(1,2))

# Set player two hold to Ah Qd
stat = T.setHoldCards(1,(12,12),(3,4))

# Set the flop to 5h, 6s, 10d
stat = T.setFlop((5,6,10),(3,1,4))

# Run a Monte Carlo simulation
T.MC(Nmc)

# Get data from the Monte Carlo simulator
wins  = T.getWins()
winsP = T.getWinsP()
draw  = T.getDraws()
drawP = T.getDrawsP()

# Print the array of the win probabilities
print("\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n")
for p in range(Np):
    print("player ", p, " | Win count : ", "{:9}".format(wins[p]), " | Win prob : ", "{:2.4f}".format(winsP[p]), \
        " | Draw count : ", "{:9}".format(draw[p]), " | Draw prob : ", "{:2.4f}".format(drawP[p]))
    
# Print the hands for each player
for p in range(Np):
    print("\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n")
    winsPP  = T.getWinsPP(p)
    winsPPp = T.getWinsPPp(p)
    drawPP  = T.getDrawsPP(p)
    drawPPp = T.getDrawsPPp(p)
    handPP  = T.getHandsPP(p)
    handPPp = T.getHandsPPp(p)
    for h in range(10):
        print("player ", p, " | hand code : ", "{:2}".format(h+1), \
              " | win count : ",   "{:9}".format(winsPP[h]), " | win prob : ",   "{:2.4f}".format(winsPPp[h]), \
              " | draw count : ",  "{:9}".format(drawPP[h]), " | draw prob : ",  "{:2.4f}".format(drawPPp[h]), \
              " | occur count : ", "{:9}".format(handPP[h]), " | occur prob : ", "{:2.4f}".format(handPPp[h]))
print("\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n")


