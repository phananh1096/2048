#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "game.h"
using namespace std;

typedef string* Stringptr;
typedef int* Intptr;

	// Constructor will read in the high score file
	// and initialize two arrays: a string array and 
	// an int array for names and scores respectively
	// Array size is +1 larger than number of entries 
	// to accomodate for score from current game
Game::Game()
{
	names = NULL;
	score = NULL;
	count = 0;
}

Game::Game(string name)
{
	ifstream instream;
    instream.open("high_score.txt");
    if (!instream.is_open( ))
    {   
        // If file doesn't exist, makes new file with 5 empty names and score 0
    	cout << "Error. Maybe file doesn't exist yet." << endl
    		 << "Will now create new high score file." << endl;
    	ofstream outstream;
    	outstream.open("high_score.txt");
		if (outstream.fail( ))
	    {
	        cout << "Output file opening failed." << endl;
	        exit(1);
	    }
	    for (int i = 0; i < 5; i++)
	    {
	    	outstream << "EmptyName   0" << endl;
	    }
	    outstream << "-1";
	    outstream.close();
        // Reopens newly created file.
        instream.open("high_score.txt");
        if (!instream.is_open())
        {
            cout << "Input file opening failed." << endl;
            exit(1);
        }
    }
	// Loops through file to determine how many entries
	count = 0;
	while (!instream.eof())
	{
		string temp = "empty";
		getline (instream, temp);	
		if (temp != "-1")
			count ++;
	}
	instream.close();
	/*
	Instantiates dynamic arrays. Size is count + a 
	as one extra for current score entry.
	*/
	names = new string[(count + 1)];
	score = new int[(count + 1)];
	instream.open("high_score.txt");
    if (!instream.is_open( ))
    {
    	cout << "Error reading file" << endl;
        exit(1);
    }
    // Loops through file and fills in arrays
    while (!instream.eof())
    {	
    	string temp = "empty";
    	int temp_num = 0;
    	for (int i = 0; i < count; i++)
    	{
    		// Reads in name
	  		instream >> temp;
	    	if (temp != "-1")
	    	{
	    		names[i] = temp;
	    	}
	    	// Reads in score
	    	instream >> temp_num;
	    	if (temp_num != -1)
	    	{
	    		score[i] = temp_num;
	    	}
    	}
    	// Read in sentinel value to achieve eof.
    	string sentinel;
    	instream >> sentinel;
    }
    instream.close();
	// Sets player name
	player_name = name;
}

Game::~Game()
{
	delete[] names;
	delete[] score;
}

int Game::get_topscore()
{
	return score[0];
}

void Game::get_topfive()
{
    // returns top 5 elements of both score and name arrays
	cout << "Top 5 scores are: \n";
	for (int i = 0; i < 5; i++)
	{
		cout << names[i] << "   " << score[i] << endl;
	}
	return;
}
	
void Game::set_newscore(int player_score)
{
    /*
    Re-sorts name and score array by comparing values with
    current game score. Shifts the remaining elements down by
    one once current score has been sorted.
    */
	for (int i = 0; i < count; i ++)
	{
		if (player_score >= score[i])
		{
			for (int h = (count-1); h >= i; h--)
			{
				score[h+1] = score[h];
                names[h+1] = names[h];
			}
			// Replaces current value
			score[i] = player_score;
			names[i] = player_name;
			break;
		}	
	}
	// Write to file
	ofstream outstream;
	outstream.open("high_score.txt");
	if (outstream.fail( ))
    {
        cout << "Output file opening failed." << endl;
        exit(1);
    }
    // Writes all scores and corresponding names
    for (int i = 0; i < (count + 1); i++)
    {
    	outstream << names[i] << "    " << score[i] << endl;
    }
    // Writes sentinel value then closes file
    outstream << "-1";
    outstream.close();
	return;
}
