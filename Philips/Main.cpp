/*
	Jarrett Philips
	Blackjack
	Main
*/

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

#include <iostream>
#include <string>
#include <fstream>

#include "Game.h"

using namespace std;

/*
	Main
*/
int main(){
	//Set up
	int numberOfPlayers;
	int numberOfDecks;
	int startingMoney;
	string input;
    
    cout << RESET << "Enter number of players, up to 5: ";
    while (!(cin>>numberOfPlayers) || numberOfPlayers < 1 || numberOfPlayers > 6){ //for example
    cout << RESET << "Enter number of players, up to 5: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    
    cout << "Enter amount of money each player will start with, up to  a million dollars: ";
    while (!(cin>>startingMoney) || startingMoney < 1 || startingMoney > 100000000){
	cout << "Enter amount of money each player will start with, up to  a million dollars: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }

    cout << "Enter number of decks, up to 3: ";
    while (!(cin>>numberOfDecks) || numberOfDecks < 0 || numberOfDecks > 4) { //for example
	cout << "Enter number of decks, up to 3: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }

    
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    
	cout << "Setting up a game with with " << numberOfPlayers << " players each with $" << startingMoney << " and " << numberOfDecks << " decks..." << endl;

	Player *root = NULL;
    
    Game g;
	for(int i = 0; i < numberOfPlayers; i ++){
		Player *tmp = new Player(i, startingMoney);

		if(root == NULL){
			root = tmp;
			//cout << "setting player " << i << " to root" << endl;
		} else {
			Player *current = root;
			while(current->next != NULL){
				current = current->next;
			}
			current->next = tmp;
			//cout << "adding player " << i << " to end of list" << endl;
		}
	}

	g.set(root, numberOfDecks);
	bool running = true;
	int round = 1;

	//Main game loop
	while(running){
		system("clear");

		g.displayFunds();

		cout << MAGENTA;
		cout << "===================" << endl;
		cout << "Beginning Round " << round << endl; 
		cout << "===================" << endl;
		cout << RESET;

		g.collectBets();

		cout << YELLOW << "======== Starting Dealer's Turn ========" << RESET << endl;
		g.startDealersTurn();
		bool playersDone = false;

		//Cycles until all players are done
		while(playersDone == false){
			playersDone = true;
			for(int i = 0; i < numberOfPlayers; i ++){
				Player *p = g.getNextPlayer();
				if(p->done == false){
					cout << CYAN << "======== Player " << p->playerID << "'s Turn =========" << RESET << endl;
					g.playersTurn(p);
				}
			
				if(p->done == false){
					playersDone = false;
				}
			}
		}

		//Calculating final outcome of round
		cout << YELLOW << "======= Finishing Dealer's Turn ========" << RESET << endl;
		g.finishDealersTurn();

		g.determineWinnings();
		g.checkForBrokePlayers();
		running = g.checkForGameOver();

		if(running == true){
			bool readableInput = false;
			while(readableInput == false){
				cout << MAGENTA << "Begin a new round? (y/n) " << RESET;
				getline(cin, input);

				//Dictate action
				if(input == "y" || input == "yes"){
					readableInput = true;
				} else if(input == "n" || input == "no"){
					running = false;
					readableInput = true;
				} else {
					cout << "Unable to read players input" << endl;
				}
			}
		} else {
			cout << RED << "All players have lost all their money, game over" << RESET << endl;
		}

		round ++;
	}
	
	cout << "Thank you for playing!" << endl;
}