#include <iostream>
#include "board.h"
#include <cstdlib>
#include <ctime>
using namespace std;

typedef int* Intptr;

Board::Board()
{
    size = 0;
    p = NULL;
    score = 0;
    over = false;
}

Board::Board (int ray_size)
{
    srand (time(0));
    size = ray_size;
    // Declaring the 2D array for board
    p = new Intptr[size];
    for (int i = 0; i < size; i++)
    {
        p[i] = new int[size];
    }

    // Initializing 2D array to 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            p[i][j] = 0;
        }
    }

    //initial_tiles();
    
    // initializes game score to 0
    score = 0;

    over = false;
}

Board::~Board ()
{
    for (int i = 0; i < size; i++)
    {
        delete[] p[i];
    }
    delete[] p;
}


void Board::move_tiles(char key)
{
    if (key == 'w')
        shift_up();     
    else if (key == 's')
        shift_down();
    else if (key == 'a')
        shift_left();
    else if (key == 'd')
        shift_right();
    return; 
}

void Board:: shift_up ()
{
    for (int j = 0; j < size; j++)
        {
            /*
            Boolean and first for loop checks whether entire row
            is empty. If it is then the row is done and next i is
            looked at.
            */
            bool row_done = true;
            for (int i = 0; i < size; i++)
            {
                if (p[i][j] != 0)
                row_done = false;   
            }
            /*
            If statement that moves every element in the row and combines
            elements accordingly
            */
            if (row_done == false)
            {
                for (int k = 1; k < size; k++)
                {
                    if (p[k-1][j] == p[k][j] && p[k-1][j] != 0)
                    {
                        // Adds the tiles together
                        p[k-1][j] = p[k-1][j] * 2;
                        // Adds to current score
                        score = score + p[k-1][j];
                        for (int h = k; h <= size-1; h++)
                        {
                            if (h < size -1)
                                p[h][j] = p[h+1][j];
                            else if (h == (size -1))
                                p[h][j] = 0;
                        }
                    }
                    /*
                    If statement shifts row if previous tile is empty
                    */
                    row_done = true;
                    if (p[k-1][j] == 0)
                    {   
                        for (int h = k; h < size; h++)
                        {
                            if (p[h][j] != 0)
                                row_done = false;
                            // Shifts elements
                            p[h-1][j] = p[h][j];
                            if (h == (size -1))
                                p[h][j] = 0;
                        }
                    }
                    // Shifts row if current tile is empty and previous tile
                    // is not.
                    else if (p[k][j] == 0 && p[k-1][j] != 0)  
                    {
                        for (int h = k+1; h < size; h++)
                        {
                            if (p[h][j] != 0)
                                row_done = false;
                            // Shifts elements
                            p[h-1][j] = p[h][j];
                            if (h == (size -1))
                                p[h][j] = 0;
                        } 
                    }  
                    // Resets k value in the case that one of element equals 0
                    if (row_done == false)    
                        k--;
                }
            }
        }
    return;
}

void Board:: shift_down ()
{
    for (int j = size -1; j >= 0; j--)
        {
            //Boolean and first for loop 
            bool row_done = true;
            for (int i = size -1; i >= 0; i--)
            {
                if (p[i][j] != 0)
                row_done = false;   
            }
            // Moves elements if non-zero values in row
            if (row_done == false)
            {
                for (int k = (size - 2); k >= 0; k--)
                {
                    // Adding tiles and adjusting scores
                    if (p[k+1][j] == p[k][j] && p[k+1][j] != 0)
                    {
                        // Adds the tiles 
                        p[k+1][j] = p[k+1][j] * 2;
                        // Adds to current score
                        score = score + p[k+1][j];
                        for (int h = k; h >= 0; h--)
                        {
                            if (h > 0)
                                p[h][j] = p[h-1][j];
                            else if (h == 0)
                                p[h][j] = 0;
                        }
                    }
                    // If statement shifting rows 
                    row_done = true;
                    if (p[k+1][j] == 0)
                    {   
                        for (int h = k; h >= 0; h--)
                        {
                            if (p[h][j] != 0)
                                row_done = false;
                            // Shifts elements
                            p[h+1][j] = p[h][j];
                            if (h == 0)
                                p[h][j] = 0;
                        } 
                    } 
                    else if (p[k][j] == 0 && p[k+1][j] != 0)
                    {   
                        for (int h = k-1; h >= 0; h--)
                        {
                            if (p[h][j] != 0)
                                row_done = false;
                            // Shifts elements
                            p[h+1][j] = p[h][j];
                            if (h == 0)
                                p[h][j] = 0;
                        } 
                    } 
                    // Resuts k if needed
                    if (row_done == false)    
                        k++; 
                }

            }
        }
    return;
}

void Board:: shift_left ()
{
    for (int i = 0; i < size; i++)
        {
            // Boolean and first for-loop
            bool row_done = true;
            for (int j = 0; j < size; j++)
            {
                if (p[i][j] != 0)
                row_done = false;   
            }
           // Moves elements if non-zero values in row
            if (row_done == false)
            {

                for (int k = 1; k < size; k++)
                {
                    // Adding tiles and adjusting score
                    if (p[i][k-1] == p[i][k] && p[i][k-1]!=0)
                    {
                        // Adds the tiles together
                        p[i][k-1] = p[i][k-1] * 2;
                        // Adds to current score
                        score = score + p[i][k-1];
                        for (int h = k; h < size; h++)
                        {
                            p[i][h] = p[i][h+1];
                            if (h == (size -1))
                                p[i][h] = 0;
                        }
                    }
                    // If statement shifting rows 
                    row_done = true;
                    if (p[i][k-1] == 0)
                    {   
                        for (int h = k; h < size; h++)
                        {
                            if (p[i][h] != 0)
                                row_done = false;
                            // Shifts elements
                            p[i][h-1] = p[i][h];
                            if (h == (size -1))
                                p[i][h] = 0;
                        }
                    }  
                    else if (p[i][k] == 0 && p[i][k-1]!=0)
                    {   
                        for (int h = k+1; h < size; h++)
                        {
                            if (p[i][h] != 0)
                                row_done = false;
                            // Shifts elements
                            p[i][h-1] = p[i][h];
                            if (h == (size -1))
                                p[i][h] = 0;
                        }
                    }  
                    
                    // if (p[i][k] == 0 && p[i][k-1] != 0)
                    //     k--;
                    if (row_done == false)    
                        k--;         
                }
            }
        }
    return;
}

void Board:: shift_right ()
{
    for (int i = size -1; i >= 0; i--)
        {
            //Boolean and first for loop
            bool row_done = true;
            for (int j = size -1; j >= 0; j--)
            {
                if (p[i][j] != 0)
                row_done = false;   
            }
            // Moves elements if non-zero values in row
            if (row_done == false)
            {
                for (int k = (size -2); k >= 0; k--)
                {
                    if (p[i][k+1] == p[i][k] && p[i][k+1] != 0)
                    {
                        // Adds the tiles together
                        p[i][k+1] = p[i][k+1] * 2;
                        // Adds to current score
                        score = score + p[i][k+1];
                        for (int h = k; h >= 0; h--)
                        {
                            if (h > 0)
                                p[i][h] = p[i][h-1];
                            else if (h == 0)
                                p[i][h] = 0;
                        }
                    }
                    // Shifts row
                    row_done = true;
                    if (p[i][k+1] == 0)
                    {   
                        for (int h = k; h >= 0; h--)
                        {
                            if (p[i][h] != 0)
                                row_done = false;
                            // Shifts elements
                            p[i][h+1] = p[i][h];
                            if (h == 0)
                                p[i][h] = 0;
                        } 
                        
                    }  
                    else if (p[i][k] == 0 && p[i][k+1] != 0)
                    {   
                        for (int h = k-1; h >= 0; h--)
                        {
                            if (p[i][h] != 0)
                                row_done = false;
                            // Shifts elements
                            p[i][h+1] = p[i][h];
                            if (h == 0)
                                p[i][h] = 0;
                        } 
                    }  
                    // Adding tiles and adjusting score
                    
                    // Resets k if non-zero value
                    // if (p[i][k] == 0 && p[i][k+1] != 0)
                    //     k++;
                    if (row_done == false)    
                        k++;    
                }

            }
        }
    return;
}


void Board::initial_tiles()
{
    for (int i = 0; i < 2; i++)
    {
        //Randomizes tile to be added
        int row = rand() % size;
        int column = rand() % size; 
        //Confirms that no two similar tiles are set to 2
        if (p[row][column] == 0)
        {    
            p[row][column] = 2;
        }        
        /* 
        Else statement used to decrease increment
        of i in case the second tile chosen for 
        initiation is same as first. Allows another 
        randomization to occur.
        */
        else
            --i;
    }   
    return;
}

void Board::add_tiles()
{
    // Boolean to keep track of whether tile has been added successfully
    bool added = false;
    do
    {
        int row = rand() % size;
        int column = rand() % size; 
        if (p[row][column] == 0)
        {   
            // Randomizes number to be added
            int num = rand() % 10 + 1;
            // Chances for making both a 2 and 4.
            if (num <= 9)
            {
                p[row][column] = 2;
            }
            else 
            {
                p[row][column] = 4;
            }
            added = true;
        }
    } while (added == false);
    return;
}


void Board::display_board()
{
    cout << "Your score is: " << score << endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (p[i][j] != 0)
            {
                cout << p[i][j];
                // Determines number of spaces to keep grid spacing constant
                int num_spaces = 4;
                if (p[i][j]/10 >= 1)
                    num_spaces --;
                if (p[i][j]/100 >= 1)
                    num_spaces --;
                if (p[i][j]/1000 >= 1)
                    num_spaces--;
                for (int n = 0; n < num_spaces; n++)
                {
                    cout << " ";
                }     
            }
            
            else 
            /*
            I chose to use an underscore instead of an x 
            as it makes the interface and game look cleaner. 
            I hope that's ok
            */
            cout << "_    ";
        }
        cout << "\n" << "\n";
    }
    return;
}

bool Board::game_over()
{
    // Boolean over determines when game is over.
    bool over = true;
    // Determine if 4 edge cases are over.
    if (p[0][0] == p[1][0] || p[0][0] == p[0][1])
        over = false;
    else if (p[size-1][0] == p[size -2][0] || p[size-1][0] == p[size-1][1])
        over = false;
    else if (p[0][size-1] == p[0][size -2] || p[0][size-1] == p[1][size-1])
        over = false;
    else if (p[size-1][size-1] == p[size -2][size -1] ||
             p[size-1][size-1] == p[size-1][size-2])
        over = false;
    // Determine if left side is over
    for (int i = 1; i < size -1; i++)
    {
        if (   p[i][0] == p[i-1][0] 
            || p[i][0] == p[i][1] 
            || p[i][0] == p[i+1][0])
            over = false;
    }
    // Determine if right side is over
    for (int i = 1; i < size -1; i++)
    {
        if (   p[i][size-1] == p[i-1][size-1] 
            || p[i][size-1] == p[i][size-2] 
            || p[i][size-1] == p[i+1][size-1])
            over = false;
    }
    // Determine if top side is over
    for (int j = 1; j < size -1; j++)
    {
        if (   p[0][j] == p[0][j-1] 
            || p[0][j] == p[1][j]
            || p[0][j] == p[0][j+1])
            over = false;
    }
    // Determine if bottom side is over
    for (int j = 1; j < size -1; j++)
    {
        if (   p[size-1][j] == p[size-1][j-1] 
            || p[size-1][j] == p[size-2][j]
            || p[size-1][j] == p[size-1][j+1])
            over = false;
    }
    // Determine if the middle matrix is over
    for (int i = 1; i < size -1; i++)
    {
        for (int j = 1; j < size -1; j++)
        {
            if (   p[i][j] == p[i-1][j]
                || p[i][j] == p[i+1][j]
                || p[i][j] == p[i][j-1]
                || p[i][j] == p[i][j+1])
                over = false;
        }
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (p[i][j] == 0)
            over = false;
        }
    }
    return over;
}

int Board::get_score()
{
    return score;
}

