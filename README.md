# NIM GAME

In NIM game, two players take turns removing objects from distinct piles. On each turn, a player must remove at least one object, and may remove any number of objects provided they all come from the same pile. The goal of the game is to take the last object.

In my game, players can play in different modes:
  1. Human VS Human
  2. AIPlayer VS Human
  3. SmartAIPlayer VS Human

Players can also choose who will go first:
  1. The first player
  2. The second player
  3. Randomly
  
In folder "game":
- Player.h & Player.cpp : define class Player and its member functions - base class 
- AIPlayer.h & AIPlayer.cpp : define a type of player - AIPlayer (computer which removes objects randomly) - derived class
- SmartAIPlayer.h & SmartAIPlayer.cpp : define a type of player - SmartAIPlayer (computer which plays to win) - derived class
- HumanPlayer.h & HumanPlayer.cpp : define a type of player - human - derived class
- game.h & game.cpp : define class Game and its member functions
- Stones.txt : Data for different levels of game : number of piles and number of objects 
- withoutSDL.cpp : game runs on the console without using SDL - I have finished it.
- main.cpp : using SDL but it is in the process of completing.
