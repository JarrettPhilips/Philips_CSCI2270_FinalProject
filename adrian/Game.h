#ifndef GAME_H
#define GAME_H

#include <string>

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
