#pragma region

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

string green = "\033[32m";
string yellow = "\033[33m";
string red = "\033[31m";
string blue = "\033[34m";
string reset = "\033[0m";

string player1 = red + "X" + reset;
string player2 = blue + "O" + reset;

vector<string> board = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
string winner = "";
string current_player;
bool game_is_active;
int turn = 1;
#pragma endregion

void display_board()
{
    cout << "\n" << board[0] << " | " << board[1] << " | " << board[2] << "\n" << board[3] << " | " << board[4] << " | " << board[5] << "\n" << board[6] << " | " << board[7] << " | " << board[8] << "\n";
}

void input_turn() 
{
    string position;
    cout << current_player << "'s turn.\nChoose a spot between 1-9: ";
    cin >> position;
    while (true)
    {
        if (position != "1" && position != "2" && position != "3" && position != "4" && position != "5" && position != "6" && position != "7" && position != "8" && position != "9")
        {
            cout << "Invalid. Choose a number between 1-9: ";
            cin >> position;
            continue;
        }
        else if (board[stoi(position) - 1] == player1 || board[stoi(position) - 1] == player2)
        {
            cout << "That spot in the board is not empty, try again: ";
            cin >> position;
            continue;
        }
        board[stoi(position) - 1] = current_player;
        break;
    }
}

void check_for_winner()
{
    bool row_1 = board[0] == board[1] && board[1] == board[2];
    bool row_2 = board[3] == board[4] && board[4] == board[5];
    bool row_3 = board[6] == board[7] && board[7] == board[8];
    bool col_1 = board[0] == board[3] && board[3] == board[6];
    bool col_2 = board[1] == board[4] && board[4] == board[7];
    bool col_3 = board[2] == board[5] && board[5] == board[8];
    bool dia_1 = board[0] == board[4] && board[4] == board[8];
    bool dia_2 = board[2] == board[4] && board[4] == board[6];
    if (row_1 || row_2 || row_3 || col_1 || col_2 || col_3 || dia_1 || dia_2)
    {
        if (row_1 || col_1)
        {
            winner = board[0];
        }
        else if (row_2 || col_2 || dia_1 || dia_2)
        {
            winner = board[4];
        }
        else
        {
            winner = board[8];
        }
        game_is_active = false;
    }
}

// return false if a string contains non digit characters.
bool is_string_digit(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if (not isdigit(str[i]))
        {
            return false;
        }
    }
    return true;
}

// Does vector<string> have any digits?
bool any_digits_vector(vector<string> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        if (is_string_digit(vec[i]))
        {
            return true;
        }
    }
    // This vector has NO strings whom are entirely a digit.
    return false;
}

void check_for_tie()
{
    if (not any_digits_vector(board)) 
    {
         // there aren't any digits left in board, the entire board is taken up
        game_is_active = false;
    }
}

void switch_player() 
{
    if (current_player == player1)
        current_player = player2;
    else
        current_player = player1;
}

int main()
{
    // Reset variables
    board = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
    winner = "";
    current_player = player1;
    game_is_active = true;
    turn = 1;

    // Start of game
    display_board();
    while (game_is_active)
    {
        input_turn();
        display_board();
        check_for_winner();
        check_for_tie();
        switch_player();
    }
    if (winner == player1 || winner == player2)
    {
        cout << winner << yellow << " won the game!\n" << reset;
    }
    else {
        cout << yellow << "The game ended in a tie!\n" << reset;
    }
}