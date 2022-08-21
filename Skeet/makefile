###############################################################
# Program:
#     Project 09, Skeet
#     Brother Comeau, CS165
# Author:
#     Dane Artis
# Summary:
#     This is the skeet game and allows the user to shoot at 
#     three types of birds to be able to kill them for points. 
#     One bird gives negative points. 
# Above and Beyond
#     I added the ability for a user to be able to restart the 
#	  game or quit the game when they either win or lose. The 
#	  user will lose if their score goes negative. The user 
#	  wins if they reach 50 points. I also added another bird 
#	  that takes 10 hits to kill and yields a total of 15 
#	  points for a kill. 
###############################################################


LFLAGS = -lglut -lGLU -lGL

###############################################################
# Build the main game
###############################################################
a.out: driver.o game.o uiInteract.o uiDraw.o point.o rifle.o velocity.o bird.o bullet.o flyingobject.o standardbird.o toughbird.o sacredbird.o bigbird.o
	g++ driver.o game.o uiInteract.o uiDraw.o point.o rifle.o velocity.o bird.o bullet.o flyingobject.o standardbird.o toughbird.o sacredbird.o bigbird.o $(LFLAGS)

###############################################################
# Individual files
#    uiDraw.o      Draw polygons on the screen and do all OpenGL graphics
#    uiInteract.o  Handles input events
#    point.o       The position on the screen
#    ground.o      Handles the ground / world
#    game.o        Handles the game interaction
###############################################################
uiDraw.o: uiDraw.cpp uiDraw.h point.h
	g++ -c uiDraw.cpp

uiInteract.o: uiInteract.cpp uiInteract.h
	g++ -c uiInteract.cpp

point.o: point.cpp point.h
	g++ -c point.cpp

game.o: game.cpp uiDraw.h uiInteract.h point.h rifle.h bullet.h bird.h
	g++ -c game.cpp

driver.o: game.h uiInteract.h driver.cpp
	g++ -c driver.cpp

rifle.o: rifle.h point.h uiDraw.h rifle.cpp
	g++ -c rifle.cpp

#######################################################################
# ADD YOUR ADDITIONAL RULES HERE!
#
# Then, don't forget to add them to the dependecy list for a.out above.
#######################################################################
velocity.o: velocity.cpp velocity.h
	g++ -c velocity.cpp

flyingobject.o: flyingobject.cpp flyingobject.h
	g++ -c flyingobject.cpp

bullet.o: bullet.cpp bullet.h flyingobject.h uiDraw.h point.h velocity.h
	g++ -c bullet.cpp

bird.o: bird.cpp bird.h flyingobject.h uiDraw.h point.h velocity.h 
	g++ -c bird.cpp

standardbird.o: standardbird.cpp standardbird.h bird.h
	g++ -c standardbird.cpp

toughbird.o: toughbird.cpp toughbird.h bird.h
	g++ -c toughbird.cpp

sacredbird.o: sacredbird.cpp sacredbird.h bird.h
	g++ -c sacredbird.cpp

bigbird.o: bigbird.cpp bigbird.h bird.h
	g++ -c bigbird.cpp

###############################################################
# General rules
###############################################################
clean:
	rm a.out *.o
