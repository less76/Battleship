// Battleship.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include <iostream>
#include <string>
using namespace std;

class Battleship {
private:
	char row;
	char column;
	int first;
	int hit;
	char game_board[10][10];
	char invisible_board[10][10];
	int skip[5];
	string *destroyed;
	char *table;
	int table_size;
	int ships_size;

public:
	Battleship();
	~Battleship();
	void Display(int);
	void addEntry(string);
	string *getEntry();
	void addTable(char);
	void Display_game();
	void Check();
	int Ships(int, char);
	void setrow(char);
	char getrow();
	void setfirst(int);
	int getfirst();
	void sethit(int);
	int gethit();
	void setcolumn(char);
	char getcoulmn();
	void setship_size(int);
	int getship_size();
	void settable_size(int);
	int gettable_size();

	friend istream& operator >> (istream& is, Battleship& input);
	friend ostream& operator << (ostream& os, const Battleship& output);
};

string *Battleship::getEntry() {
	return destroyed;
}

void Battleship::addTable(char newEntry) {
	
	char *new_array = new char[gettable_size() + 1];

	if (gettable_size() == 0) {
		*new_array = newEntry;
		table = new_array;
		//cout << *table << endl;
	}

	else {

		for (int i = 0; i < gettable_size(); i++) {
			*new_array++ = *table++;
		}

		*new_array = newEntry;
		new_array -= gettable_size();

		table = new_array;

		/*for (int i = 0; i < gettable_size(); i++) {
			cout << *table++ << endl;
		}

		cout << *table << endl;

		table -= gettable_size();*/

	}

	table_size++;
}

void Battleship::settable_size(int table_size) {
	this->table_size = table_size;
}

int Battleship::gettable_size() {
	return this->table_size;
}

void Battleship::setship_size(int ships_size) {
	this->ships_size = ships_size;
}

int Battleship::getship_size() {
	return this->ships_size;
}

void Battleship::addEntry(string newEntry) {

	string *new_array = new string[getship_size() + 1];

	if (getship_size() == 0) {
		*new_array = newEntry;
		destroyed = new_array;
		//cout << *destroyed << endl;
	}

	else {

		for (int i = 0; i < getship_size(); i++) {
			*new_array++ = *destroyed++;
		}

		*new_array = newEntry;
		new_array -= getship_size();

		destroyed = new_array;

		/*for (int i = 0; i < getship_size(); i++) {
			cout << *destroyed++ << endl;
		}

		cout << *destroyed << endl;

		destroyed -= getship_size();*/

	}

	ships_size++;
}

void Battleship::Check() {

	string ships_name[5] = {
	"Carrier", "Battleship", "Cruiser", "Submarine","Destroyer"
	};

	int ships[5] = {
		5,4,3,3,2
	};
	
	for (int i = 0; i < gettable_size(); i++) {
		if (table[i] == 'C') {
			ships[0]--;
		}

		if (table[i] == 'B') {
			ships[1]--;
		}

		if (table[i] == 'R') {
			ships[2]--;
		}

		if (table[i] == 'S') {
			ships[3]--;
		}

		if (table[i] == 'D') {
			ships[4]--;
		}
	}

	for (int i = 0; i < 5; i++) {
		if (ships[i] == 0 && skip[i] == 0) {
			cout <<"You sunk my " << ships_name[i] << endl;
			addEntry(ships_name[i]);
			skip[i] = 1;
		}
	}

}

void Battleship::sethit(int hit) {
	this->hit = hit;
}

int Battleship::gethit() {
	return this->hit;
}

int Battleship::Ships(int ship, char vert) {
	int blocked = 0;
	
	int tiles[5] = {
		5,4,3,3,2
	};

	char ships[5] = {
		'C','B','R','S','D'
	};

	if (vert == '1') {
			
		for (int i = 0; i < tiles[ship]; i++) {
			if (game_board[(row - 0x30) + i][column - 0x30] != NULL || (row - 0x30) + i >= 10) {
				cout << "Sorry interferance from unknown object try another location" << endl;
				blocked = 1;
				return 1;
				//break;
			}
		}

		if (blocked == 0) {
			for (int i = 0; i < tiles[ship]; i++) {
				game_board[(row - 0x30) + i][column - 0x30] = ships[ship];
			}
			return 0;
		}

	}

	if (vert == '0') {
		for (int i = 0; i < tiles[ship]; i++) {
			if (game_board[row - 0x30][(column - 0x30) + i] != NULL || (column - 0x30) + i >= 10) {
				cout << "Sorry interferance from unknown object try another location" << endl;
				blocked = 1;
				return 1;
				//break;
			}

		}

		if (blocked == 0) {
			for (int i = 0; i < tiles[ship]; i++) {
				game_board[row - 0x30][(column - 0x30) + i] = ships[ship];
			}
			return 0;
		}
	}

	else {
		cout << "Not an option " << endl;
		return 1;
	}

}

void Battleship::Display_game() {

	for (int i = 0; i < 10; i++) {
		cout << "|";
		for (int j = 0; j < 10; j++) {
			cout << "|" << game_board[i][j] << "|";
		}
		cout << "|" << endl;
	}

}

void Battleship::Display(int dis) {

	if (first == 0) {
		for (int i = 0; i < 10; i++) {
			cout << "|";
			for (int j = 0; j < 10; j++) {
				cout << "|" << invisible_board[i][j] << "|";
			}
			cout << "|" << endl;
		}
	}

	else {

		if (game_board[row - 0x30][column - 0x30] == NULL) {
			cout << "MISS" << endl;
			invisible_board[row - 0x30][column - 0x30] = 'O';
			hit = 0;
		}

		else {

			if (dis == 1) {
				addTable(game_board[row - 0x30][column - 0x30]);
			}
			
			cout << "HIT" << endl;
			invisible_board[row - 0x30][column - 0x30] = 'X';
			
			hit = 1;
			game_board[row - 0x30][column - 0x30] = 'A';
		}

		for (int i = 0; i < 10; i++) {
			cout << "|";
			for (int j = 0; j < 10; j++) {
				cout << "|" << invisible_board[i][j] << "|";
			}
			cout << "|" << endl;
		}

	}

	first = 1;
	
}

istream& operator >> (istream& is, Battleship& input) {
	
	//row and column are switched from normal point of view

	int good = 0;
	
	while (good == 0) {
		cout << "Enter the row location" << endl;
		is >> input.column;

		if (input.column == 'x' || input.column == 'X') {
			
			if (input.getship_size() >= 1) {

				string *pointer = input.getEntry();

				for (int i = 0; i < input.getship_size() - 1; i++) {
					cout << *pointer++ << endl;
				}
				cout << *pointer << endl;
			}
		}

		if (input.column - 0x30 > 9) {
			cout << "Row not within board range try again" << endl;
			good = 0;
		}

		else {
			good = 1;
		}
	}

	good = 0;

	while (good == 0) {
		cout << "Enter the column location" << endl;
		is >> input.row;

		if (input.row - 0x30 > 9) {
			cout << "Coulumn not within board range try again" << endl;
			good = 0;
		}

		else {
			good = 1;
		}
	}

	return is;
}

ostream& operator << (ostream& os, const Battleship& output) {
	cout << "The location you picked was \n";
	os << output.column << "," << output.row << endl;
	return os;
}

Battleship::Battleship() {

	this->row = 0;
	this->column = 0;
	this->first = 0;
	this->hit = 0;
	this->ships_size = 0;
	this->table_size = 0;

	for (int i = 0; i < 5; i++) {
		skip[i] = 0;
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			game_board[i][j] = 0;
		}
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			invisible_board[i][j] = 0;
		}
	}
	
	destroyed = NULL;
	table = NULL;
}

Battleship::~Battleship() {

	for (int i = 0; i < 10; i++) {
		delete[] game_board[i];
	}
	delete[] game_board;

	for (int i = 0; i < 10; i++) {
		delete[] invisible_board[i];
	}
	delete[] invisible_board;

	delete[]destroyed;
}

void Battleship::setrow(char row) {
	this->row = row;
}

char Battleship::getrow() {
	return this->row;
}

void Battleship::setcolumn(char column) {
	this->column = column;
}

char Battleship::getcoulmn() {
	return this->column;
}

void Battleship::setfirst(int first) {
	this->first = first;
}

int Battleship::getfirst() {
	return this->first;
}

int main()
{
	Battleship player1, player2;
	char vert;
	int blocked = 0;
	string ships[5] = {
		"Carrier", "Battleship", "Cruiser", "Submarine","Destroyer"
	};
	
	
	cout << "Setup your ships if your new to this game you may directions step by step" << endl;
	cout << "If not you may type values in order of row, column, vert" << endl;

	cout << "Its player 1's turn ";
	
	for (int i = 0; i < 5; i++) {

		
		cout << "where do you want to put your " << ships[i] << endl;
		player1.Display_game();
		cin >> player1;
		
		cout << "Type in 1 for verircal and 0 for horizontal" << endl;
		cin >> vert;
		cout << player1;

		blocked = player1.Ships(i, vert);
				
		if (blocked == 1)
		{
			i--;
		}

	}

	cin.ignore();
	cout << "Player 1 your table looks like this take a picture press enter when ready" << endl;

	player1.Display_game();
	cin.ignore();
	cout << "\033[2J\033[H";

	cout << "Setup your ships if your new to this game you may directions step by step" << endl;
	cout << "If not you may type values in order of row, column, vert" << endl;
	cout << "Its player 2's turn ";

	for (int i = 0; i < 5; i++) {

		cout << "Where do you want to put your " << ships[i] << endl;
		player2.Display_game();
		cin >> player2;

		cout << "Type in 1 for verircal and 0 for horizontal" << endl;
		cin >> vert;

		int blocked = player2.Ships(i, vert);

		if (blocked == 1)
		{
			i--;
		}

	}

	cin.ignore();
	cout << "Player 2 your table looks like this take a picture press enter when ready" << endl;

	player2.Display_game();
	cin.ignore();
	cout << "\033[2J\033[H";

	cout << "Its player 1's turn " << endl;
	player2.Display(0);
	cin >> player2;
	player2.Display(1);
	cin.ignore();
	cout << "Player 1 at position " << player2 << "your board looks like this press enter to proceed" << endl;
	cin.ignore();
	cout << "\033[2J\033[H";

	while (blocked == 0) {

		if (player1.gethit() == 1 || player2.gethit() == 0) {
			cout << "Its player 2's turn " << endl;
			player1.Display(0);
			player1.Check();
			cin >> player1;
			player1.Display(1);
			cin.ignore();
			cout << "Player 2 at position " << player1 << "your board looks like this press enter to proceed" << endl;
			cin.ignore();
			cout << "\033[2J\033[H";
			player2.sethit(0);

			if (player1.getship_size() >= 1) {
				cout << "Press x to view ships detroyed" << endl;
			}

			if (player1.getship_size() == 5) {
				cout << "Player 2 you WIN ships destroyed" << endl;
			}
		}
		

		if (player2.gethit() == 1 || player1.gethit() == 0) {
			cout << "Its player 1's turn " << endl;
			player2.Display(0);
			player2.Check();
			cin >> player2;
			player2.Display(1);
			cin.ignore();
			cout << "Player 1 at position " << player2 << "your board looks like this press enter to proceed" << endl;
			cin.ignore();
			cout << "\033[2J\033[H";
			player1.sethit(0);

			if (player2.getship_size() >= 1) {
				cout << "Press x to view ships detroyed" << endl;
			}

			if (player2.getship_size() == 5) {
				cout << "Player 1 you WIN ships destroyed" << endl;
			}
		}
	}

	return 0;
}