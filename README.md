# Blackjack - Data Structures Final Project
**Jarrett Philips**

### Project Summary
A simple Blackjack dealer. 

The game is a fairly standard version of blackjack, involving a dealer (run by the program), and 1+ players. The game can also be run with any number of decks desired. The game follows the common rules of blackjack, the goal is to beat the dealer's hand while not going over 21 points in value. Currently, Ace's are always considered 11 points. There are also no bonus winnings for having a "natural jack".

### Running
1. Navigate to folder containing source files in terminal
2. Compile source with "g++ Main.cpp Game.cpp"
3. To execute, run "./a.out"
4. The program will lead you through the final steps of setting up a game to your liking

### System Requirements
Project has only been run on Mac and C++ 11, but should operate on any operating system. There are some color and screen clearing options that may or may not be functional on other operating systems. There should not be any hardware requirements, outside of having a computer capable of compiling and running C++ source code.

### Dependencies
This project requires no external dependencies.

#### Group Members
Jarrett Philips
#### Contributors
N/A

## Open	Issues
- Occasionally a "Bus Error: 10" occurs after the start of the dealer's turn on round 1
	- Simply reinitiating the ./a.out file seems to fix it
- Occasionally there is a "segmentation fault: 11" error, cause unknown
	- Simply reinitiating the ./a.out file seems to fix it

## Fixed Issues
- FIXED Cards generate in random order, but always the same random order
	- FIX; Incorrent use of rand() function