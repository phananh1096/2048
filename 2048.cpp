#include <istream>
#include <iostream>
#include "board.h"
#include "game.h"
#include <stdio.h>
#include <cstdlib>
//#include "game.h"
using namespace std;

int main()
{
    
    cout << "Welcome, please enter your name without spaces." << endl;
    cout << "Name: ";
    string player_name;
    getline (cin, player_name);
    Game current_game(player_name);
    int size = 0;
    cout << "What would you like the size of the board to be? (max 7)" << endl;
    do
    {
        cin >> size;
        if (size >7 || size <= 1)
            cout << "Sorry, that's not a valid size. Please re-enter." << endl;
    }while (size > 7 || size <=1);
    int top_score = current_game.get_topscore();
    cout << "Starting game! High score is " << top_score
         << endl;
    Board current_board(size);
    current_board.initial_tiles();
    bool game_over = current_board.game_over();
    while (! game_over)
    {
        current_board.display_board();
        char key = '0';
        while (!(key == 'a' || key == 'w' || key == 's' || key == 'd'
            || key == 'h' || key == 'q'))
        {
            cout << "What direction to move board (w,a,s,d)?" << endl
              << "Press 'h' for top 5 scores and 'q' to quit" << endl;
            cin >> key;
            if (key == 'a' || key == 'w' || key == 's' || key == 'd')
            {
                current_board.move_tiles(key);
                if (current_board.game_over() == false)
                    current_board.add_tiles();
                if (current_board.game_over() == true)
                {
                    current_board.display_board();
                    cout << "Game over. No more moves left, "
                         << player_name << endl
                         << "Your score has been recorded." << endl;
                    game_over = true;
                }
            }
            else if( key == 'h')
            {
                current_game.get_topfive();
            }
            else if (key == 'q')
            { 
                game_over = true;
                cout << "You have chosen to exit, " << player_name << endl
                     << "Your score has been recorded."
                     << endl << endl;
            }
            else
            {
                cout << "Invalid key, please re-enter." << endl;
                current_board.display_board();
            }
        }
    }
    int score = current_board.get_score();
    cout << "Your score is: " << score << endl;
    current_game.set_newscore(score);
    current_game.get_topfive();
    cout << endl;

    return 0;
}