#include <iostream>
#include <string>
using std::string;
using std::getline;
#include <fstream>
using std::endl;
using std::cin;
using std::cout;
using namespace std;

char board[9] = {'1','2','3','4','5','6','7','8','9'};
bool keepPlaying =true;
bool endGame = false;
char playFirst;
char who;

void make_board(){
    int num = 0;
    cout << " --- --- ---" << endl;
    for (int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            cout << "| " << board[num] << " ";
            num++;
        }
        cout << "|" << endl;
        cout << " --- --- ---" << endl << endl;
    }
}// makes board

char playerMove(){
    bool validNum = false;
    bool ok = false;
    while(!(validNum)){
        int input;
        while(!(ok)){
            cout << "\nPlease type one of the numbers on the screen: " << endl;
            cin >> input;
            if(cin.fail() || (static_cast<int>(input) != input)){
                cout << "Please type a valid number. The number should be one of the numbers on the board.\n" << endl;
                cin.clear();
                cin.ignore(100, '\n');
            }else {ok=true;}
        }//get a valid input which is an integer

        for(int i =0; i < 9; i++){
            char ch = input +'0';
            if(ch == board[i]){
                validNum = true;
                cout<< endl << endl;
                return ch;
            }
        }// checks if the input is on the board
        if (!(validNum)) {
            cout << "Please type a valid number. The number that you are trying to enter should be able to see on the board.\n" << endl;
        }
        ok = false;
    }
}// player's mark

char whoFirst(){
    bool ok = false;
    while(!(ok)){
        cout<< "Do you want to start first [Y|N]? ";
        cin >> playFirst;
        playFirst = toupper(playFirst);
        if (playFirst == 'Y' || playFirst == 'N') {
            ok = true;
            cin.clear();
            cin.ignore(100,'\n');
            return playFirst;
        }else{
            cout << "Please enter Y or N.\n" << endl;
            cin.clear();
            cin.ignore(100,'\n');
        }
    }

}

void updateBoard(char who, char input){
    for(int i =0; i < 9; i++){
        if(input == board[i] && who == 'X'){
            board[i] = who;
            make_board();
        }
        else if(input == board[i] && who == 'O'){
            board[i] = who;
            make_board();
        }
    }
}

void again(){
    bool ok = false;
    char playAgain;
    while(!(ok)){
        cout << "Would you like to play this game again? [Y/N] " << endl;
        cin >> playAgain;
        playAgain = toupper(playAgain);
        keepPlaying = false;
        if (playAgain == 'Y'){
            ok = true;
        }
        else if (playAgain == 'N') {
            ok = true;
            endGame = true;
            cout << "Thank you for playing this game with me! It was fun!" << endl;
        }else{
            cout << "Please enter Y or N.\n" << endl;
            cin.clear();
            cin.ignore(100,'\n');
        }
    }
}

void checkWin(string who){
    if(((board[0] == board[1]) && (board[0] == board[2])) || ((board[0] == board[3]) && (board[0] == board[6])) || ((board[0] == board[4]) && (board[0] == board[8])) || ((board[1] == board[4]) && (board[1] == board[7])) || ((board[2] == board[5]) && (board[2] == board[8])) || ((board[3] == board[4]) && (board[3] == board[5])) || ((board[6] == board[7]) && (board[6] == board[8])) || ((board[2] == board[4]) && (board[2] == board[6]))){
        cout << who << " won the game!\n" << endl;
        again();
    }
    else{
        bool conti = true;
        for(int i = 0; i < 9; i++){
            if((board[i] != 'O') && (board[i] != 'X')){
                return;
            }
        }
        cout << "\n\nThe game is over\n" << "You tied the game!\n\n" << endl;
        again();

    }
}

char twoSame(char who,char opposite){
    char boardNum;
    for(int i=1; i<8; i+=3){
        if((board[i-1] == board[i]) && (board[i-1] == who) && (board[i+1] != who) && (board[i+1] != opposite)){
            boardNum = i+2+'0';
            return boardNum;
        }else if((board[i-1] == board[i+1]) && (board[i-1] == who) && (board[i] != who) && (board[i] != opposite)){
            boardNum = i+1+'0';
            return boardNum;
        }else if((board[i] == board[i+1]) && (board[i] == who) && (board[i-1] != who) && (board[i-1] != opposite)){
            boardNum = i+'0';
            return boardNum;
        }
    }// checking if there are two same 'who's (horizontally)
    for(int j=0; j<3; j++){
        if((board[j] == board[j+3]) && (board[j] == who) && (board[j+6] != who) && (board[j+6] != opposite)){
            boardNum = j+7+'0';
            return boardNum;
        }
        else if((board[j] == board[j+6]) && (board[j] == who) && (board[j+3] != who) && (board[j+3] != opposite)){
            boardNum = j+4+'0';
            return boardNum;
        }
        else if((board[j+3] == board[j+6]) && (board[j] == who) && (board[j] != who) && (board[j] != opposite)){
            boardNum = j+1+'0';
            return boardNum;
        }
    }// checking if there are two same 'O's (vertically)
    if((board[0] == board[4]) && (board[0] == who) && (board[8] != who) && (board[8] != opposite)){
        boardNum = 8+1+'0';
        return boardNum;
    }else if((board[0] == board[8]) && (board[0] == who) && (board[4] != who) && (board[4] != opposite)){
        boardNum = 4+1+'0';
        return boardNum;
    }else if((board[4] == board[8]) && (board[4] == who) && (board[0] != who) && (board[0] != opposite)){
        boardNum = 1+'0';
        return boardNum;
    } // checking if there are two same 'who's (left-top -> right-bottom)

    if((board[2] == board[4]) && (board[2] == who) && (board[6] != who) && (board[6] != opposite)){
        boardNum = 6 +1+'0';
        return boardNum;
    }else if((board[2] == board[6]) && (board[2] == who) && (board[4] != who) && (board[4] != opposite)){
        boardNum = 4 +1+'0';
        return boardNum;
    }else if((board[4] == board[6]) && (board[4] == who) && (board[2] != who) && (board[2] != opposite)){
        boardNum = 2+1+'0';
        return boardNum;
    } // checking if there are two same 'who's (right-top -> left-bottom)
}

char computerMove(){
    char boardNum;

    // checking if there are two same 'O's
    boardNum = twoSame('O','X');
    for(int i =0; i < 9; i++){
        if(boardNum == board[i]){return boardNum;}
    }
    // checking if there are two same 'X's
    boardNum =twoSame('X','O');
    for(int i =0; i < 9; i++){
        if(boardNum == board[i]){return boardNum;}
    }
    //if starts first, do center attack first
    if(playFirst == 'Y'){
        if(board[4] != 'O' && board[4] != 'X'){
            boardNum = 5 + '0';
            return boardNum;
        } // take center first if it is empty since it has four ways to fill three squares
        if(board[0] != 'O' && board[0] != 'X' && board[2] != 'O' && board[2] != 'X' && board[6] != 'O' && board[6] != 'X' && board[8] != 'O' && board[8] != 'X'){return 1+ '0';}
        //if the player does not take any corner, take corner.
        if(board[2] != 'O' && board[2] != 'X'){return 3 + '0';}
        else if(board[0] != 'O' && board[0] != 'X'){return 1 + '0';}
        else if(board[6] != 'O' && board[6] != 'X'){return 7 + '0';}
        else if(board[8] != 'O' && board[8] != 'X'){return 9 + '0';}
        else if(board[1] != 'O' && board[1] != 'X'){return 2 + '0';}
        else if(board[3] != 'O' && board[3] != 'X'){return 4 + '0';}
        else if(board[5] != 'O' && board[5] != 'X'){return 6 + '0';}
        else if(board[7] != 'O' && board[7] != 'X'){return 7 + '0';}


    }
    else{
        if(board[4] != 'O' && board[4] != 'X'){
            boardNum = 5 + '0';
            return boardNum;
        }else {
            if(board[0] != 'O' && board[0] != 'X' && board[2] != 'O' && board[2] != 'X' && board[6] != 'O' && board[6] != 'X' && board[8] != 'O' && board[8] != 'X'){return 1+ '0';}
        }
        if(board[2] != 'O' && board[2] != 'X'){return 3+ '0';}
        else if(board[0] != 'O' && board[0] != 'X'){return 1+ '0';}
        else if(board[6] != 'O' && board[6] != 'X'){return 7+ '0';}
        else if(board[8] != 'O' && board[8] != 'X'){return 9+ '0';}
        else if(board[1] != 'O' && board[1] != 'X'){return 2 + '0';}
        else if(board[3] != 'O' && board[3] != 'X'){return 4 + '0';}
        else if(board[5] != 'O' && board[5] != 'X'){return 6 + '0';}
        else if(board[7] != 'O' && board[7] != 'X'){return 7 + '0';}
    }


}


void reset(){
    for(int i = 0; i<sizeof(board); i++){
        board[i] = i+1+'0';
    }
}




int main(){

    while (!endGame){
        make_board();
        who = whoFirst();
        if(who=='Y'){
            while(keepPlaying){
                char chr = playerMove();
                cout << "\n\nThis is the updated board!\n" << endl;
                updateBoard('X',chr);
                checkWin("You");
                if(!keepPlaying){break;}
                cout << "\n\nThe computer played like this:\n" << endl;
                char come = computerMove();
                updateBoard('O',come);
                checkWin("The Computer");
            }
        }
        else{
            while(keepPlaying){
                cout << "\n\nThe computer played like this:\n" << endl;
                char come = computerMove();
                updateBoard('O',come);
                checkWin("The Computer");
                if(!keepPlaying){break;}
                char chr = playerMove();
                cout << "\n\nThis is the updated board!\n" << endl;
                updateBoard('X',chr);
                checkWin("You");
            }
        }
        if(!endGame) {
            reset();
            keepPlaying =true;
        }
    }

}

