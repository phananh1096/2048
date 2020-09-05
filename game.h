#include <iostream>
#include <fstream>
#include <string>
using namespace std;
// Design was approved by Maxwell.

typedef string* Stringptr;
typedef int* Intptr;

class Game
{
public: 
	// Constructor will read in the high score file
	// and initialize two arrays: a string array and 
	// an int array for names and scores respectively
	// Array size is +1 larger than number of entries 
	// to accomodate for score from current game
	Game();
    Game(string);

	// Destructor to eliminate elements of dynamic
	// array
	~Game();

	// getter function displays the highest score which
	// is the first element in the int array
	int get_topscore();

	// void function displays the top 5 scores which
	// is the first five elements in the int array
	void get_topfive();

	// setter function that takes the input score, 
	// loops through all elements, compares value to
	// inputted int. If higher, moves remaining elements 
	// down one index and adds current score to current
	// index for both string and int array. 
	void set_newscore(int);

private: 	
	// Two pointers for string and int array.
	Stringptr names;
	Intptr score;
    string player_name;
    int count;
};