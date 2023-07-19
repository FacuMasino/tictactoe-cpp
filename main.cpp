#include <iostream>

using namespace std;

void drawBoard(bool [][3][2]);
void askUser(int, bool [][3][2]);
bool boardFull(bool [][3][2]);
bool writeBoard(int, int, int, bool [][3][2]);
int gameState(int, int, int, bool [][3][2]);
bool convertPos(int, int &, int &);

int main(void) {
    bool board[3][3][2] {};

    drawBoard(board);
    askUser(0, board);

    system("pause");
    return 0;
}

void askUser(int nPlayer, bool board[][3][2]) {
    int pos, row, col, lastPlayer, state = 0;
    // states
    // 0 = en desarrollo, 1 = hay ganador, -1 = empate
    while(state == 0) {
        cout << "[Jugador # " << nPlayer+1 << "]" << "Ingrese su posicion [1-9]: ";
        cin >> pos;
        if(convertPos(pos, row, col)) {
            // If board was written
            if(writeBoard(row, col, nPlayer, board)) {
                lastPlayer = nPlayer;
                nPlayer = (nPlayer == 0) ? 1 : 0;
            }
            state = gameState(row,col, lastPlayer, board);
        } else {
            cout << "Posicion incorrecta." << endl;
        }
    }
    if(state == 1) {
        cout << "El jugador #" << lastPlayer << " gana!" << endl;
    } else {
        cout << "Empate!" << endl;
    }
    
}

// Verify if board is full
bool boardFull(bool board[][3][2]) {
    int busyPos = 0;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(board[i][j][0] || board[i][j][1]) {
                busyPos++;
            }
        }
    }
    if(busyPos < 9) {
        return false;
    }
    return true;
}

bool writeBoard (int row, int col, int nPlayer, bool board[][3][2]) {
    int nextPlayer = (nPlayer > 0) ? 0 : 1;
    if(!board[row][col][nPlayer] && !board[row][col][nextPlayer]) {
        board[row][col][nPlayer] = true;
        drawBoard(board);
        return true;
    } else {
        cout << "Esa posicion no esta disponible." << endl;
    }
    return false;
}

int gameState(int row, int col, int nPlayer, bool board [][3][2]) {
    bool isWinner = true; // winner flag
    // check row
    for(int i = 0; i < 3; i++) {
        if(board[row][i][nPlayer] && isWinner) {
            isWinner = true;
        } else {
            isWinner = false;
        }
    }
    if(isWinner) {
        return isWinner;
    }

    // check column
    isWinner = true; // reset flag
    for(int i = 0; i < 3; i++) {
        if(board[i][col][nPlayer] && isWinner) {
            isWinner = true;
        } else {
            isWinner = false;
        }
    }

    // check diagonals
    if(board[2][0][nPlayer] && board[1][1][nPlayer] && board[0][2][nPlayer]) {
        isWinner = true;
    } else if (board[0][0][nPlayer] && board[1][1][nPlayer] && board[2][2][nPlayer]) {
        isWinner = true;
    }

    // check deadheat
    if(boardFull(board)) {
        return -1;
    }

    return isWinner;
}

bool convertPos(int pos, int &row, int &col) {
    // Posicion incorrecta
    if(pos <= 0 || pos > 9) {
        return false;
    }
    // Posicion correcta
    if(pos <= 3) {
        row = 0;
        col = pos - 1;
    } else if (pos <= 6) {
        row = 1;
        col = pos - 4;
    } else {
        row = 2;
        col = pos - 7;
    }
    return true;
}

void drawBoard(bool board[][3][2]) {
    system("cls");
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            cout << "[";
            if(!board[i][j][0] && !board[i][j][1]) {
                cout << " ";
            } else if (board[i][j][0]) {
                cout << "O";
            } else {
                cout << "X";
            }
            cout << "]";
        }
        cout << endl;
    }
}