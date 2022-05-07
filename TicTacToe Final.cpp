#include <iostream>
#include <ctime>
// Anthony Feliciano MAC125
using namespace std;


class TicTacToe {
public:
    int  space = 9;
    char board[9];
    char player;
    char setPlayer();
    void Reset();
    int Menu(int gameType);
    void drawBoard();
    bool blankSpace(int position);
    void playerMove(int position, char player);
    char whoseTurn();
    void switchTurn();
    bool checkifWin(char* board, char p);
    bool checkifTie(char* board, char p);
    int checkPossibleWin(char* board, char player, int position);
    void humanVsHuman();
    void humanVsMachine();
    void machineVsMachine();

private:
    char getPlayer();
    const char playerx = 'X';
    const char playero = 'O';
    const char blank = '_';
};

char TicTacToe::getPlayer() {                                               //grab from private class
    player = playerx;
    return player;
}

char TicTacToe::setPlayer() {
    return getPlayer();
}

void TicTacToe::Reset() {                                                   //set board as blanks
    for (int i = 0; i < space; i++) {
        board[i] = blank;
    }
}

int TicTacToe::Menu(int gameType) {                                         //asks user for a number and chooses the gameType based off it

    cout << "Welcome to my game!\nChoose the type of game you want to play.\nHuman vs Human = 1\nHuman vs Machine = 2\nMachine vs Machine = 3";
    cin >> gameType;
    return gameType;
}

void TicTacToe::drawBoard() {                                               //draws board 

    for (int i = 0; i < space; i++) {
        cout << board[i];
        if (i % 3 == 2)
            cout << endl;
    }
}

bool TicTacToe::blankSpace(int position) {
    return board[position] == blank;
}

void TicTacToe::playerMove(int position, char player) {
    if (blankSpace(position))
        board[position] = player;
}

char TicTacToe::whoseTurn() {
    return player;
}

void TicTacToe::switchTurn() {
    if (player == playerx)
        player = playero;
    else
        player = playerx;
}

bool TicTacToe::checkifWin(char* board, char p) {                                              //if player x or player o has 3 spots in a row the function is true                            
    const int WINS[8][3]{                                                                     //and game will end
        {0,1,2},{3,4,5},{6,7,8},{0,4,8},{2,4,6},{0,3,6},{1,4,7},{2,5,8}
    };

    for (int combo = 0; combo < 8; combo++)
        if (board[WINS[combo][0]] == p && board[WINS[combo][1]] == p && board[WINS[combo][2]] == p) {
            cout << "winner is " << p << endl;
            return true;
        }

    return false;
}

bool TicTacToe::checkifTie(char* board, char p) {                                             //if there is no win and the board is filled theres a tie.
    int spotTaken = 0;
    for (int i = 0; i < space; i++) {
        if (board[i] == playerx || board[i] == playero)                                       // reads entire board and adds 1 to spotTaken if there is a x or o
            spotTaken++;                                                                      // in any spot
    }
    if (spotTaken == 9 && checkifWin(board, player) == false) {                               // when spotTaken = 9 that means the board is filled with x's and
        cout << "Its a tie!";                                                                 // o's and if there is no winner that means there is a tie.
        return true;
    }
    return false;
}

int TicTacToe::checkPossibleWin(char* board, char player, int position) {                       // if the opponent is about to win or lose the player will try
    int startTime = time(0);                                                                  // to go to the winning spot or prevent the opponent from winning
    srand(time(0));                                                                           // if there is no threat of loss and no win the player will use a                                                                         // random move                                                                                                                
    const int WINS[8][3]{ {0,1,2},{3,4,5},{6,7,8},{0,4,8},{2,4,6},{0,3,6},{1,4,7},{2,5,8} };    //random move
    int botMove = 0;
    int typeOfWin = 0;

    while (checkifWin(board, player) == false) {
        for (int combo = 0; combo < 8; combo++) {
            if (board[WINS[combo][0]] == playerx && board[WINS[combo][1]] == playerx && board[WINS[combo][2]] == blank) {
                botMove = WINS[combo][2];
                typeOfWin = 1;
            }

            if (board[WINS[combo][0]] == playerx && board[WINS[combo][2]] == playerx && board[WINS[combo][1]] == blank) {
                botMove = WINS[combo][1];
                typeOfWin = 2;
            }
            if (board[WINS[combo][1]] == playerx && board[WINS[combo][2]] == playerx && board[WINS[combo][0]] == blank) {
                botMove = WINS[combo][0];
                typeOfWin = 3;
            }

            if (board[WINS[combo][0]] == playero && board[WINS[combo][1]] == playero && board[WINS[combo][2]] == blank) {
                botMove = WINS[combo][2];
                typeOfWin = 4;
            }

            if (board[WINS[combo][0]] == playero && board[WINS[combo][2]] == playero && board[WINS[combo][1]] == blank) {
                botMove = WINS[combo][1];
                typeOfWin = 5;
            }
            if (board[WINS[combo][1]] == playero && board[WINS[combo][2]] == playero && board[WINS[combo][0]] == blank) {
                botMove = WINS[combo][0];
                typeOfWin = 6;
            }
        }
        if (typeOfWin > 3) {
            if (board[botMove] == blank) {
                return botMove;
                break;
            }
        }
        else if (typeOfWin > 0) {

            if (board[botMove] == blank) {
                return botMove;
                break;
            }
        }
        else if (typeOfWin == 0) {
            botMove = (rand() % 9);
            if (board[botMove] == blank) {
                return botMove;
                break;
            }
        }

    }

    return 0;
}

void TicTacToe::humanVsHuman() {                                                              // gives a game where two humans can face eachother
    int move = 0;

    player = playerx;
    int rounds = 9;
    for (int turn = 0; turn <= rounds; turn++) {
        drawBoard();
        cout << "Your move: " << whoseTurn() << ":\n\n\n";
        cin >> move;
        if (1 <= move <= 9 && board[move] == blank)
            playerMove(move, player);
        else {
            cout << "invalid move";
            rounds++;
        }

        if (checkifWin(board, player) == true) {
            drawBoard();
            break;
        }
        if (checkifTie(board, player) == true) {
            drawBoard();
            break;
        }
        switchTurn();

    }
}

void TicTacToe::humanVsMachine() {                                                             // gives a game where human plays the ai  
    int move = 0;
    player = playerx;
    int rounds = 9;
    for (int turn = 0; turn <= rounds; turn++) {
        drawBoard();
        cout << "Your move: " << whoseTurn() << ":\n\n\n";
        if (player == playerx) {
            cin >> move;
            if (1 <= move <= 9 && board[move] == blank)
                playerMove(move, player);
            else {
                cout << "invalid move";
                rounds++;
            }
        }
        else {
            if (1 <= checkPossibleWin(board, player, move) <= 9 && board[checkPossibleWin(board, player, move)] == blank)
                playerMove(checkPossibleWin(board, player, move), player);


            else {
                cout << "invalid move\n\n";
                rounds++;
            }
        }
        if (checkifWin(board, player) == true) {
            drawBoard();
            break;
        }
        if (checkifTie(board, player) == true) {
            drawBoard();
            break;
        }
        switchTurn();
    }
}



void TicTacToe::machineVsMachine() {                                                       //gives a game where ai plays against another ai  
    int move = 0;
    player = playerx;
    int rounds = 9;
    for (int turn = 0; turn <= rounds; turn++) {
        drawBoard();
        cout << "Your move: " << whoseTurn() << ":\n\n\n";
        if (1 <= checkPossibleWin(board, player, move) <= 9 && board[checkPossibleWin(board, player, move)] == blank)
            playerMove(checkPossibleWin(board, player, move), player);
        else {
            cout << "invalid move\n\n";
            rounds++;
        }

        if (checkifWin(board, player) == true) {
            drawBoard();
            break;
        }
        if (checkifTie(board, player) == true) {
            drawBoard();
            break;
        }
        switchTurn();
    }
}

int main()
{
    TicTacToe playGame;
    playGame.player = playGame.setPlayer();
    int gameType = 0;
    playGame.Reset();

    gameType = playGame.Menu(gameType);

    if (gameType == 1)                                                                       // user decided what opponent hes going to play against.
        playGame.humanVsHuman();
    else if (gameType == 2)
        playGame.humanVsMachine();
    else if (gameType == 3)
        playGame.machineVsMachine();
    else
        cout << "invalid";



}