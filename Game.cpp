/*
	Jarrett Philips
	Blackjack
	Game definitions
*/

#include <iostream>
#include <string>

#include "Game.h"

using namespace std;

/*
	Constructors
*/
Game::Game(){

}

/*
	Destructors
*/
Game::~Game(){

}

/*
	Functions
*/
void Game::set(Player *player1, int numberOfDecksInput){
	dealer = new Player;
	dealer->playerID = 0;
	//Creates a loop of players
	Player *current = player1;
	while(current->next != NULL){
		current = current->next;
	}
	current->next = player1;
	rootPlayer = player1;
	currentPlayer = player1;
	numberOfDecks = numberOfDecksInput;
	buildDeck();
}

//Collects 2 cards from deck, displays 1
void Game::startDealersTurn(){
	cout << "Starting dealer's turn" << endl;
	//Erase previous hand
	dealer->playerRootCard = NULL;

	//Create a new hand
	Card *a = drawCard();
	Card *b = drawCard();
	a->next = b;
	dealer->playerRootCard = a;

	cout << "==============================" << endl;
	cout << "Dealer's Cards:" << endl;
	cout << a->rank << " of " << a->suit << " : " << "****" << " of " << "****" << endl;
	cout << "==============================" << endl;

	Player *current = rootPlayer;
	while(current != NULL){
		//Erases previous hand
		current->playerRootCard = NULL;

		//Creates a new hand
		Card *c = drawCard();
		Card *d = drawCard();
		c->next = d;

		current->playerRootCard = c;
	}
}

//Displays other card, takes another card if total value is < 16
void Game::finishDealersTurn(){
	cout << "Finishing dealer's turn" << endl;
}

bool Game::playersTurn(Player *player){ //Basic hit or pass cycle
	cout << "Player " << endl;
	return true;
}

void Game::determineWinnings(){

}

void Game::buildDeck(){ //Creates a randomized deck of cards
	string suits[4] = {"Hearts", "Clubs", "Diamonds", "Spades"};
	string ranks[13] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eignt", "Nine", "Ten", "Jack", "Queen", "King"};
	int values[13] = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
	
	int totalCards = numberOfDecks * 52;
	int currentDeckLength = 0;

	Card *tmpRoot = NULL;

	for(int i = 0; i < numberOfDecks; i ++){ //For each deck

		for(int j = 0; j < 4; j ++){ //For each suit

			for(int k = 0; k < 13; k ++){ //For each rank
				Card *tmp =  new Card;
				tmp->rank = ranks[k];
				tmp->suit = suits[j];
				tmp->value = values[k];
				tmp->next = NULL;
				//cout << "Created " << tmp->rank << " of " << tmp->suit << " for deck " << i << "." << endl;

				//Adds to a linked list
				if(tmpRoot == NULL){
					tmpRoot = tmp;
				} else {
					/*
					//Adds cards in order
					Card *current = tmpRoot;
					while(current->next != NULL){
						current = current->next;
					}
					current->next = tmp;
					*/
					//Adds cards randomly
					int x = rand() % currentDeckLength;
					if(x == 0){
						x = 1;
					}

					Card *current = tmpRoot;

					for(int l = 0; l < x - 1; l ++){
						current = current->next;
					}
					tmp->next = current->next;
					current->next = tmp;
				}

				currentDeckLength ++;
 			}
		}
	}

	int x = rand() % currentDeckLength;
	if(x == 0){
		x = 1;
	}

	//Randomized root
	Card *current = tmpRoot;

	for(int l = 0; l < x - 1; l ++){
		current = current->next;
	}
	Card *newRoot = tmpRoot->next; 
	tmpRoot->next = current->next;
	current->next = tmpRoot;

	/*
	//Outputs current deck structure
	cout << "==============" << endl;
	cout << "Current Deck" << endl;
	cout << "==============" << endl;
	current = newRoot;
	
	while(current != NULL){
		cout << current->rank << " of " << current->suit << endl;
		current = current->next;
	}
	*/

	rootCard = newRoot;
}

Card * Game::drawCard(){
	if(rootCard == NULL){
		buildDeck();
		cout << "Reshuffling deck" << endl;
	}

	Card *c = rootCard;
	rootCard = rootCard->next;
	c->next = NULL;
	return c;
}

Player * Game::getNextPlayer(){
	Player *p = currentPlayer;
	currentPlayer = currentPlayer->next;
	return p;
}

