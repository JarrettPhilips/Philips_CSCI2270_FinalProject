/*
	Jarrett Philips
	Blackjack
	Main
*/

#include <iostream>
#include <string>
#include <fstream>

#include "Game.h"

using namespace std;

/*
	Functions
*/

/*
	Main
*/
int main(){
	//cout << "Hello World!" << endl;
	//Set up
	int numberOfPlayers;
	int numberOfDecks;
	int startingMoney;
	string input;

	cout << "Enter number of players: ";
	getline(cin, input);
	numberOfPlayers = stoi(input);

	cout << "Enter amount of money each player will start with: ";
	getline(cin, input);
	startingMoney = stoi(input);

	cout << "Enter number of decks: ";
	getline(cin, input);
	numberOfDecks = stoi(input);

	cout << "Setting up a game with with " << numberOfPlayers << " players each with $" << startingMoney << " and " << numberOfDecks << " decks..." << endl;

	Player *root = NULL;

	for(int i = 0; i < numberOfPlayers; i ++){
		Player *tmp = new Player;
		tmp->money = startingMoney;
		tmp->playerID = i + 1;

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

	Game g;
	g.set(root, numberOfDecks);
	bool running = true;
	int round = 1;

	//Main game loop
	while(running){
		cout << "===================" << endl;
		cout << "Beginning Round " << round << endl; 
		cout << "===================" << endl;

		g.startDealersTurn();

		for(int i = 0; i < numberOfPlayers; i ++){
			Player *p = g.getNextPlayer();
			g.playersTurn(p);
		}

		g.finishDealersTurn();

		running = false;
		round ++;
	}
}