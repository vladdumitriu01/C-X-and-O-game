
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

unsigned turn;
char gridChar(int i) {
    //function that switch between the players turn
    switch(i) {
        case -1:
            return 'X';
        case 0:
            return ' ';
        case 1:
            return 'O';
    }
}
void draw(int b[9])
{
    //function that draw the grid
    system("cls");
    cout<<endl;


    cout<<" Tic Tac Toe(3x3) game made by Vlad Dumitriu"<<endl;
    cout<<" Student number: S16102144" <<endl<<endl;
   	cout << "     |     |     " << endl;
	cout << "  " << gridChar(b[0]) << "  |  " << gridChar(b[1]) << "  |  " << gridChar(b[2]) << endl;

	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;

	cout << "  " << gridChar(b[3]) << "  |  " << gridChar(b[4]) << "  |  " << gridChar(b[5]) << endl;

	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;

	cout << "  " << gridChar(b[6]) << "  |  " << gridChar(b[7]) << "  |  " << gridChar(b[8]) << endl;

	cout << "     |     |     " << endl << endl;
}

int win(const int board[9]) {
    //determines if a player has won, returns 0 otherwise.
    unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i;
    for(i = 0; i < 8; ++i) {
        if(board[wins[i][0]] != 0 &&
           board[wins[i][0]] == board[wins[i][1]] &&
           board[wins[i][0]] == board[wins[i][2]])
            return board[wins[i][2]];
    }
    return 0;
}
int minimax(int board[9], int player) {
    //How is the position like for player (their turn) on board?
    int winner = win(board);
    if(winner != 0) return winner*player;

    int move = -1;
    int score = -2;//Losing moves are preferred to no move
    int i;
    for(i = 0; i < 9; ++i) {//For all moves,
        if(board[i] == 0) {//If legal,
            board[i] = player;//Try the move
            int thisScore = -minimax(board, player*-1);
            if(thisScore > score) {
                score = thisScore;
                move = i;
            }//Pick the one that's worst for the opponent
            board[i] = 0;//Reset board after try
        }
    }
    if(move == -1) return 0;
    return score;
}
void computerMove(int board[9]) {
    int move = -1;
    int score = -2;
    int i;
    for(i = 0; i < 9; ++i) {
        if(board[i] == 0) {
            board[i] = 1;
            int tempScore = -minimax(board, -1);
            board[i] = 0;
            if(tempScore > score) {
                score = tempScore;
                move = i;
            }
        }
    }
    //returns a score based on minimax tree at a given node.
    board[move] = 1;
}
void playerMove(int board[9]) {
    //the player selects a move
    int move = 0;
    do {
        cout<<"\nInput move ([1..9]): ";
        cin>> move;
        move--;
        cout<<"\n";
    } while (move >= 9 || move < 0 && board[move] == 0);
    board[move] = -1;
}
int chooseplayer2(int ab)
{

    if (ab==1)
        return 2;
    else return 1;
}
void ChoosePlayer(int board[9],int turn12)
{

     int move = 0;
    do {
        cout<<"\nInput move ([1..9]): ";
        cin>> move;
        move--;
        cout<<"\n";
    } while (move >= 9 || move < 0 && board[move] == 0);
    board[move] = turn12;
}
int main() {
    system("color F5"); // changes the color for the background and text
    int board[9] = {0,0,0,0,0,0,0,0,0};
    int gamemode;
    //computer squares are 1, player squares are -1.
    cout<<"Play agains a player or a computer? (1)Player vs Player   (2)Computer\n";
    cin>>gamemode;
    if(gamemode == 1)
    {
    draw(board);

        int player1=1;

       for(turn = 0; turn < 9 && win(board) == 0; ++turn)
         if(player1 %2 ==0)
         {
            draw(board);
            ChoosePlayer(board,1);
            player1 --;

         }
         else {
            draw(board);
            ChoosePlayer(board,-1);
            player1 ++;

         }
         draw(board);
         switch(win(board)) {
            case 0:
                printf("A draw. \n");
                break;
            case 1:
                draw(board);
                printf("Player 2 wins\n");
                break;
            case -1:
                printf("Player 1 wins!\n");
                break;
        }
    }
    else
    {
        cout<<"Computer: O, You: X\nPlay (1)st or (2)nd? ";
        int player=0;
        scanf("%d",&player);
        printf("\n");
        unsigned turn;
        for(turn = 0; turn < 9 && win(board) == 0; ++turn) {
            if((turn+player) % 2 == 0)
                computerMove(board);
            else {
                draw(board);
                playerMove(board);
            }
        }


        switch(win(board)) {
            case 0:
                printf("A draw. \n");
                break;
            case 1:
                draw(board);
                printf("You lose.\n");
                break;
            case -1:
                printf("You win. Inconceivable!\n");
                break;
        }
    }
}
