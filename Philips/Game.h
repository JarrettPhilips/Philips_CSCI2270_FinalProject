/*
	Jarrett Philips
	BlackJack
	Game header
*/

#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>

struct Card{
	std::string rank;
	std::string suit;
	int value;
	Card *next;
	Card *previous;
};

struct Player{
	int playerID;
	int money;
	Card *playerRootCard;
	Player *next;
	bool done;
	int totalValue;
	int bet;
    
    Player(int in_id, int in_money){
        playerID = in_id;
        playerRootCard = NULL;
        next = NULL;
        done = false;
        money = in_money;
    }
};


class Game{
public:
	Game();
	~Game();
	void set(Player *player1, int numberOfDecks);
	void startDealersTurn();
	void finishDealersTurn();
	bool playersTurn(Player *player);
	Player * getNextPlayer();
	void determineWinnings();
	void displayFunds();
	void collectBets();
	void checkForBrokePlayers();
	bool checkForGameOver();
private:
	int numberOfDecks;
	Player *rootPlayer;
	Player *dealer;
	Player *currentPlayer;
	Card *rootCard;
	void buildDeck();
	Card * drawCard();
};

#endif // GAME_H