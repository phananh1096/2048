#include <iostream>
#include <iostream>
using namespace std;
// Design was approved by Maxwell

typedef int* Intptr;

class Board
{
public: 
	
	/*
    Default Constructor sets value of pointer to 
	int pointer p to NULL
    */
	Board();

	/* 
    Constructor sets value of pointer to int pointer
	to new int array. Loops through array to initiate
	elements of the 2D array to 0. 
    */
	Board(int);

	// Destructor eliminates elements in 2D dynamic array
	~Board ();

	/* 
    Void function reads in character and decides 
    Which direction to shift board. Calls on respective shift 
    function 
    */
	void move_tiles(char);

    //Setter function that shifts board up
    void shift_up();

    //Setter function that shifts board down
    void shift_down();

    //Setter function that shifts board left
    void shift_left();

    //Setter function that shifts board right
    void shift_right();

	/*
    Setter Void function initially changes the values of 2
	tiles in the empty array to 2 before it is printed
	Is called once at start of program
    */
	void initial_tiles();

	/*
    Setter Void function randomizes chance for 2 or 4, 
	then loops through 2D file, stores all empty (0) 
	tiles' coordinates into 2 arrays (one for row 
	and one for column)
	
	Function then randomizes an index from 0 to the 
	last index and chooses one index and changes value 
	to either 2 or 4.
    */
	void add_tiles();

	// Void function prints out board.
	void display_board();

	// Boolean function game_over to check if game is over
	bool game_over();

    // Int function that returns score
    int get_score();

    // **Extra credit
    void hint();

private: 	
	// Integer for the size of array
	int size;
	// Pointer to int pointer used to 
	// make 2D array through constructor.
	Intptr *p;
	// Score for the current board class.
	int score;
	//Boolean to determine if game is over.
	bool over;
    // Boolean to determine if tile is added
    bool add_tile;

};