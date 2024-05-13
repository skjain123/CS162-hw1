/******************************************************
** Program: shooting_hoop.cpp
** Author: Sunil Jain
** Date: 10/15/2023
** Description: A simulation of a basketball shooting game with 2 players.
** Input: where is the money ball rack for each player and if the user(s) want to play again.
** Output: prompts for input, whose turn it is, 7 racks, 5 balls/scores for each rack, total player score, and who won at the end.
**         -> reprompts for invalid inputs.
******************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

//defining sizes that are constant for the game -- how many racks there are and # of balls per rack
#define RACK_SIZE 7
#define BALL_SIZE 5

/**
 * Function Name: isNum
 * Description: checks the user input for any characters that is not a number to determine 
 * if it can be converted to an int usin stoi()
 * Parameters: the user input
 * Pre-Conditions: used correctly within the play_again loop
 * Post-Conditions: outputs clearly
*/
bool isNum(string input) {
    for (int i = 0; i < input.length(); i++) {
        if (!isdigit(input.at(i))) return false; //is entire user input a digit?
    }

    return true;
}

/**
 * Function Name: prompts
 * Description: prompts the user based on what needs to be checked -- money rack position and play again inputs
 * Parameters: a string holding whick input to prompt for
 * Pre-Conditions: correct check variable passed
 * Post-Conditions: outputs clearly
*/
void prompts(string check) {
    if (check == "money_rack") {
        cout << "which position do you want the money ball rack to be? (1-5): ";
    } else if (check == "play_again") {
        cout << endl << "Do you want to play again? (1-yes, 0-no): ";
    }
}

/**
 * Function Name: check_input
 * Description: checks if user input is an integer, and within the set limits for that input
 * Parameters: a string holding what input to check for, an integer to edit, and the low/high limits 
 * Pre-Conditions: edits correct variable and prompts user correctly
 * Post-Conditions: outputs a reprompt when neccessary.
*/
void check_input(string check, int& output, int low, int high) {

    string var = "";
    bool valid = false; //change when user inputs correctly

    while (!valid) { //while not valid
        
        //prompts and gets user input
        prompts(check);
        cin >> var; 

        //input is valid if it is a number and within the high/low limits
        if (!isNum(var)) {
            cout << "Invalid Input, please enter a number!" << endl;
        } else {
            output = stoi(var);
            if ((output >= low && output <= high) || (high <= 0 && output >= low)) {
                valid = true;
            } else cout << endl << "Invalid Input, please enter a number (" << low << "-" << high << ")." << endl;
        }
    }
}

/**
 * Function Name: setup_racks
 * Description: names all the racks either reg, money, starry. based on these we can add/output scores and marks differently,
 * also gets input from user on where they want the money rack to be
 * Parameters: a string array holding rack names
 * Pre-Conditions: none
 * Post-Conditions: names the racks correctly according to the user input and the locations of the starry ball pedestals
*/
void setup_racks(string racks[]) {
    int pos = 0;

    check_input("money_rack", pos, 1, 5);
    
    //name all racks except starry positions regular 
    for (int i = 0; i < RACK_SIZE; i++) {
        if (i != 2 && i != 5) {
            racks[i] = "reg";
        } else racks[i] = "starry";
    }

    //skip starry pedestal positions to match correct money rack
    if (pos-1 >= 2) pos++;
    if (pos-1 >= 5) pos++;
    racks[pos-1] = "money";

}

/**
 * Function Name: mark_score
 * Description: generates the 50% chance success/fail for each ball and outputs accordingly
 * Parameters: a array holding the scores of each ball, success character, fail character,
 * and the score to edit (unique to each rack type), 
 * Pre-Conditions: used correctly within the play_again loop
 * Post-Conditions: outputs clearly
*/
string mark_score(int score_array[], char success, char fail, int& score, char last) {
    string output = " ";

    //for each ball output either success/fail mark
    for (int i = 0; i < BALL_SIZE; i++) {
        if (score_array[i] == 0) {
            output += " ";
        } else {
            if (rand() % 2) { //even/odd number simulating 50% randomness
                if (i == BALL_SIZE-1) {
                    output += last;
                } else {
                    output += success;
                }
                score += score_array[i];
            } else {
                output += fail;
            }
        }
        output += " ";
    }
    
    return output += "| " + to_string(score) + " pts"; //return output for each rack
}

/**
 * Function Name: build_output
 * Description: responsible for most outputs to the user-- rack fail/successes, rack scores, and the player's total score
 * Parameters: the name of the current rack, the current rack number, and the player's score
 * Pre-Conditions: correct rack name passed
 * Post-Conditions: outputs clearly and gives the correct score for each rack
*/
void build_output(string rack, int& rack_num, int& total_score) {

    string output = "";

    int score = 0;

    //different success marks and fail mark to output for each different rack type
    char rMark = 'O';
    char pMark = 'W';
    char mMark = 'M';
    char fail = 'X';
    
    //different ways to add scores and ouput results for each different rack type
    int rScore[BALL_SIZE] = {1,1,1,1,2};
    int mScore[BALL_SIZE] = {2,2,2,2,2};
    int pScore[BALL_SIZE] = {3,0,0,0,0};

    //differentiate rack types and ouput accordingly
    if (rack == "reg") {
        output += "Rack " + to_string(rack_num++) + ": " + mark_score(rScore, rMark, fail, score, mMark);
    } else if (rack == "money") {
        output += "Rack " + to_string(rack_num++) + ": " + mark_score(mScore, mMark, fail, score, mMark);
    } else {
        output += "Starry: " + mark_score(pScore, pMark, fail, score, ' ');
    }

    //edit player final score
    total_score += score;
    
    cout << output << endl;
}

/**
 * Function Name: play
 * Description: returns a score for the player to whom this function is called to
 * Parameters: none
 * Pre-Conditions: called to assign a score to player_1 and player_2
 * Post-Conditions: outputs the correct score
*/
int play() {

    //creating the names for the racks
    string racks[RACK_SIZE];
    setup_racks(racks);

    //player score to return
    int total_score = 0;

    //counting the racks (separate from starry)
    int rack_num = 1;

    //for each rack output ball results and rack score
    for (int i = 0; i < RACK_SIZE; i++) {
        build_output(racks[i], rack_num, total_score);
    }

    return total_score;
}

/**
 * Function Name: output_winner
 * Description: takes scores for two players and compares them to determine a tie or who won.
 * Parameters: scores for player_1 and player_2
 * Pre-Conditions: used to output which player won the game
 * Post-Conditions: outputs correct winner or tie situation
*/
void output_winner(int player_1, int player_2) {
    if (player_1 == player_2) {
        cout << "It is a tie between players 1 and 2!" << endl;
    } else if (player_1 > player_2) {
        cout << "Player 1 wins!" << endl;
    } else {
        cout << "Player 2 wins!" << endl;
    }
}


/**
 * Function Name: get_players
 * Description: generates scores for two players and compares them to determine a tie or who won.
 * Parameters: none
 * Pre-Conditions: used correctly within the play_again loop
 * Post-Conditions: outputs clearly
*/
void get_players() {
    int player_1;
    int player_2;

    //player 1
    cout << endl << "It is player 1's turn!" << endl;
    player_1 = play();
    cout << endl << "Total: " << player_1 << " pts" << endl << endl;

    //player 2
    cout << endl << "It is player 2's turn!" << endl;
    player_2 = play();
    cout << endl << "Total: " << player_2 << " pts" << endl;

    //who won
    output_winner(player_1, player_2);
}

int main() {
    srand(time(NULL));
    int play_again = true;

    //while the player wants to play again continue, initially set to true.
    while (play_again) {
        get_players();
        check_input("play_again", play_again, 0, 1); //prompting for playing again
    }

    return 0;
}