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
int main(){
    string yn;
    cout << "Would you like to play a game of blackjack? y/n" << endl;
    getline(cin, yn);
    if(yn == "y" || yn == "yes"){
        int numberOfPlayers;
        int numberOfDecks;
        int startingMoney;
        string input;
        cout << RESET << "Enter number of players: ";
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
            } else {
                Player *current = root;
                while(current->next != NULL){
                    current = current->next;
                }
                current->next = tmp;
            }
        }
        Game g;
        g.set(root, numberOfDecks);
        bool running = true;
        int round = 1;
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
    else {
        cout << "Have a nice day" << endl;
    }
}
