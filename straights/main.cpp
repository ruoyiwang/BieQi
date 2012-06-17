#include <sstream>
#include <string>
#include <iostream>
#include <vector>

#include "Command.h"
#include "Table.h"
#include "Referee.h"
#include "Player.h"

using namespace std;

Player invitePlayer(int i){
	string command;

	while (1){
		cout << "Is player "<<  i <<"  a human(h) or a computer(c)?" << endl;
		cin >> command;

		if (command[0] == 'c')
			return CompPlayer();
		else if (command[0] == 'h')
			return HumanPlayer();
	}
	
}

int main(int argc, char* argv[]){
	if (argc > 1){
		int randSeed;
		istringstream(argv[1]) >> randSeed;

		srand(randSeed);
	}

	vector<Player> playerList;
	Table cardTable;
	Referee referee;

	// 1. Invite Players
	for(int i = 1; i<5;i++)
		playerList[i] = invitePlayer(i);
	
	// 2. Shufﬂing and Dealing


}