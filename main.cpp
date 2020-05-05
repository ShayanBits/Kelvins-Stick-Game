#include <iostream>
#include <string>
using namespace std;

class GameBoard {
private:
	int numOfSticks;

public:
	/* Constructor: initialize numOfSticks */
	GameBoard(int numOfSticks) {
		// Complete the member function
		this->numOfSticks = 21;
	}
	/* Display the board on the screen */
	void display() {
		// Complete the member function
		for (int i = 0; i < numOfSticks / 5; i++) {
			for (int j = 0; j < 5; j++) {
				cout << "|";
			}
			cout << " ";
		}
		for (int i = 0; i < numOfSticks % 5; i++) {
			cout << "|";
		}
	}

	/* Return the number of sticks */
	int getNumOfSticks() {
		// Complete the member function
		return numOfSticks;
	}

	/* Remove the given number of sticks, return true if there are enough sticks to remove, otherwise return false */
	bool removeSticks(int numOfSticksToRemove) {
		// Complete the member function
		if (numOfSticks > numOfSticksToRemove) {
			numOfSticks = numOfSticks - numOfSticksToRemove;
			return true;
		}

		else if (numOfSticks < numOfSticksToRemove) {
			return false;
		}

	}
};


/* Hint: What is the purpose of this class? */
class Player {
protected:
	string name;
public:
	/* Constructor */
	Player() {
		/* Hint: You may not need to type anything in here. */
	}

	/* Return the name of the player */
	string getName() {

		return name;
	}

	/* Let the player pick up 1 to 4 sticks */
	virtual void pickupSticks(GameBoard* board) {
		/* Hint: You may not need to type anything in here. */
	}
};


/* Define a HumanPlayer class here
   In Part 1, you can assume that the user input must be valid (i.e, 1 to 4 and there are enough sticks)
   You are welcome to add the error checking in Part 2 */
class HumanPlayer : public Player {
public:
	int numpick;
	void setName(string NAME) {
		this->name = NAME;
	}
	virtual void pickupSticks(GameBoard* board) {
		cout << getName()<<", please enter the number of sticks to pick up (1 to 4):";
		cin >> numpick;
		board->removeSticks(numpick);
	}
};

/* Define a ComputerPlayer class here
   In Part 1, the computer uses the following strategy:
		If the number of sticks left is 1, pick 1 stick (lose)
		If the number of sticks left is 2 to 5, make it 1 stick left (win)
		Otherwise,
			If the number of sticks is odd, pick 1 stick
			If the number of sticks is even, pick 2 sticks

   You are welcome to design and implement a better AI in Part 2 */
class ComputerPlayer : public Player {
public:
	void setName(string NAME) {
		this->name = NAME;
	}
	virtual void pickupSticks(GameBoard* board) {
		if ((*board).getNumOfSticks() == 1) {
		cout << "Computer picks up 1 stick(s)";
		board->removeSticks(1);
		}
		else if ((*board).getNumOfSticks() >= 2 && (*board).getNumOfSticks() <= 5) {
		cout << "Computer picks up " << (*board).getNumOfSticks() - 1 << "stick(s)";
		board->removeSticks((*board).getNumOfSticks() - 1);
		}
		else {
			if ((*board).getNumOfSticks() % 2 == 0) {
		cout << "Computer picks up 2 stick(s)";
		board->removeSticks(2);
			}
			else if ((*board).getNumOfSticks() % 2 != 0) {
		cout << "Computer picks up 1 stick(s)";
		board->removeSticks(1);
			}
		}

	}
};


class SticksGame {
private:
	Player* player1;         // a pointer to the first player
	Player* player2;         // a pointer to the second player
	Player* currentPlayer;   // a pointer to the current player
	GameBoard* board;        // a pointer to the game board
	int round = 1;
public:
	/* Constructor: create the player objects and the board object, set the current player */
	SticksGame(int numOfPlayers) {
		// Complete the constructor
		HumanPlayer humplayer1;
		HumanPlayer humplayer2;
		ComputerPlayer computerPlayer;
		board = new GameBoard(21);
			if (numOfPlayers == 1) {
				player1 = &humplayer1;
				humplayer1.setName("Player1");
				player2 = &computerPlayer;
				computerPlayer.setName("Computer");
			}
			else if (numOfPlayers == 2) {
				player1 = &humplayer1;
				humplayer1.setName("Player1");
				player2 = &humplayer2;
				humplayer2.setName("Player2");
			}
			currentPlayer = player1;
	}

	/* Called once in main() */
	void start() {
		// Complete the member function
		do {
			(*board).display();

			if (round%2==0) {
				currentPlayer = player2;
			}
			else if (round % 2 != 0) {
				currentPlayer = player1;
			}
			(*currentPlayer).pickupSticks(board);
			round++;
		} while ((*board).getNumOfSticks() != 0);
		if (round% 2 == 0) {
			cout << (*player1).getName() << " wins";
		}
		else if (round % 2 != 0) {
			cout << (*player2).getName << " wins";
		}

	}
};

/* The main function */
int main() {
	int numOfPlayers;
	cout << "How many players (1 or 2)?" << endl;
	cin >> numOfPlayers;
	SticksGame game(numOfPlayers);
	game.start();
	return 0;
}