#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 15
// A safe choice
#define CHARSIZE 4
#define DISPLAY_SIZE (SIZE * CHARSIZE)
#define MAXLINE 1000
// indicate an empty space on the board; 255 is never used as a player marker
#define EMPTY 0

// function pointer for strategies
// char player, inputX[], inputY[]
typedef void (*strategy)(char, int[], int[]);

//棋盘使用的是GBK编码，每一个中文字符占用2个字节。

//棋盘基本模板
char aInitDisplayBoardArray[SIZE][DISPLAY_SIZE + 1] = {
    "┏┯┯┯┯┯┯┯┯┯┯┯┯┯┓", "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨", "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨", "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
    "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨", "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨", "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨", "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
    "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨", "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨", "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨", "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
    "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨", "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨", "┗┷┷┷┷┷┷┷┷┷┷┷┷┷┛"};
//此数组用于显示棋盘
char aDisplayBoardArray[SIZE][DISPLAY_SIZE + 1];

char play1Pic[] = "●";  //黑棋子;
char play1CurrentPic[] = "▲";

char play2Pic[] = "◎";  //白棋子;
char play2CurrentPic[] = "△";

//此数组用于记录棋盘格局
int aRecordBoard[SIZE][SIZE];
int current_row = -1;
int current_col = -1;

// used for fgets & sscanf for input
char buff[MAXLINE];

void PvP();
void PvE(strategy func);
void XingXingMove(char current_player, int[], int[]);
void ShaZiMove(char current_player, int inputX[], int inputY[]);
void defence(char current_player);

int inputGetInt();
char validPos(int x, int y);
char validMove(int x, int y);
int input(char current_player);
void initRecordBoard(void);
void recordtoDisplayArray(void);
void displayBoard(void);

char checkEndGame(char current_player, int x, int y);
char judge(int i, int j);

void move(int n, int* x, int* y);

char checkForbiddenMoves(int x, int y);
char checkDoubleThree(int x, int y);
char checkDoubleFour(int x, int y);
char checkOverline(int x, int y);

int main(int argc, char* argv[]) {
    printf("Welcome to FiveInRow, written by Tang Yufei\n");
    printf(
        "Choose Play Mode:\n"
        "  1 for PvP (player vs player),\n"
        "  2 for PvE (player vs computer)\n");
    printf("Key in q to quit anytime you want\n");

    initRecordBoard();
    switch (inputGetInt()) {
        case 1:
            PvP();
            break;
        case 2:
            if (argc != 2) {
                printf("Usage: ./FiveInRow n \n");
                printf("1 for XingXing, 2 for ShaZi, 3 for High\n");
                return 1;  // error code: 1
            }

            int strategy_selection = atoi(argv[1]);
            strategy func = NULL;
            switch (strategy_selection) {
                case 1:
                    printf("PvE with strategy: 1 XingXing\n");
                    func = XingXingMove;
                    break;
                case 2:
                    printf("PvE with strategy: 2 ShaZi\n");
                    func = ShaZiMove;
                    break;
                case 3:
                    printf("PvE with strategy: 3 High\n");
                    break;
                default:
                    printf("n is invalid, it should be 1, 2, or 3\n");
                    return 1;
            }
            PvE(func);
            break;
        default:
            printf("Mode choose,only 1 or 2\n");
            return 1;
    }
    return 0;
}

void PvP() {
    for (int current_player = 2;
         !input(current_player) &&
         !checkEndGame(current_player, current_row, current_col);
         current_player ^= 3) {
    }
}

void PvE(strategy func) {
    int choice = 0;
    int current_player = 0;
    int x[(SIZE * SIZE) + 2] = {0, -1};  // x[0] is the number of turns elapsed
    int y[(SIZE * SIZE) + 2] = {0, -1};  // save the history of previous moves

    printf("Choice:1 for white and 2 for black.\n");
    choice = inputGetInt();
    if (choice != 1 && choice != 2) {
        printf("Wrong input. Quit.\n");
        return;
    }

    x[0] = 1;  // x[0] is the number of turns elapsed
    int turns = x[0];
    if (choice == 1) {
        current_player = 2;
        x[turns] = 8;
        y[turns] = 8;
        aRecordBoard[x[turns]][y[turns]] = current_player;
    }

    for (current_player = 2;
         !checkEndGame(current_player ^ 3, current_row, current_col);
         current_player ^= 3) {
        if (current_player == choice) {
            if (input(current_player)) {  // quit when ret != 0
                return;
            }
        } else {
            func(current_player, x, y);
        }
    }
}

// ignore last 2 arguments
void XingXingMove(char current_player, int _[], int __[]) {
    do {
        current_row = rand() % SIZE;
        current_col = rand() % SIZE;
    } while (aRecordBoard[current_row][current_col] != EMPTY);
    aRecordBoard[current_row][current_col] = current_player;
}

void ShaZiMove(char current_player, int inputX[], int inputY[]) {
    // player take black, in the first turn:
    if (inputX[1] == -1 && inputY[1] == -1) {
        inputX[1] = current_row;
        inputY[1] = current_col;
    }
    // start with last move
    for (int turns = inputX[0]; turns > 0; --turns) {
        int n = 0;
        int x = inputX[turns];
        int y = inputY[turns];
        do {
            x = inputX[turns];
            y = inputY[turns];
            move(n, &x, &y);
            n = n + 1;
        } while (n < 8 && !validMove(x, y));
        if (aRecordBoard[x][y] == EMPTY) {
            aRecordBoard[x][y] = current_player;
            turns = inputX[0] = inputX[0] + 1;
            inputX[turns] = current_row = x;
            inputY[turns] = current_col = y;
            return;
        }
    }
    XingXingMove(current_player, inputX, inputY);
}

int inputGetInt() {
    fgets(buff, MAXLINE - 1, stdin);
    return atoi(buff);
}

char validPos(int x, int y) {
    return (x >= 0 && x < SIZE && y >= 0 && y < SIZE);
}

char validMove(int x, int y) {
    return (validPos(x, y) && aRecordBoard[x][y] == EMPTY);
}

// return 1 when need to quit, 0 if not; will displayBoard
int input(char current_player) {
    displayBoard();

    do {
        printf("Input your cheese:\n");
        fgets(buff, MAXLINE - 1, stdin);
        if (buff[0] == '\n') {
            continue;
        }
        char d;
        sscanf(buff, "%c", &d);
        d = toupper(d);
        if (d == 'Q') {
            printf("Player %d quit!\n", current_player);
            return 1;
        }
        int n = atoi(buff + 1);
        int x = SIZE - n;
        int y = d - 'A';
        if (validMove(x, y)) {
            current_row = x;
            current_col = y;
            aRecordBoard[current_row][current_col] = current_player;
            displayBoard();
            return 0;
        } else {
            printf("Invalid Position! Please input again:\n");
        }
    } while (1);
}

//初始化棋盘格局
void initRecordBoard(void) {
    memset(aRecordBoard, EMPTY, sizeof(aRecordBoard));
}
//将aRecordBoard中记录的棋子位置，转化到aDisplayBoardArray中
void recordtoDisplayArray(void) {
    //第一步：将aInitDisplayBoardArray中记录的空棋盘，复制到aDisplayBoardArray中
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < DISPLAY_SIZE + 1; j++) {
            aDisplayBoardArray[i][j] = aInitDisplayBoardArray[i][j];
        }
    }
    //第二步：扫描aRecordBoard，当遇到非0的元素，将●或者◎复制到aDisplayBoardArray的相应位置上
    //注意：aDisplayBoardArray所记录的字符是中文字符，每个字符占2个字节。●和◎也是中文字符，每个也占2个字节。
    int sizeOfChar = strlen(play1Pic);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            char* playPic = NULL;
            if (aRecordBoard[i][j] == 1) {
                playPic = play1Pic;
            } else if (aRecordBoard[i][j] == 2) {
                playPic = play2Pic;
            } else {
                continue;
            }
            for (int k = 0; k < sizeOfChar; ++k) {
                aDisplayBoardArray[i][j * sizeOfChar + k] = playPic[k];
            }
        }
    }
}

//显示棋盘格局
void displayBoard(void) {
    recordtoDisplayArray();

    //第一步：清屏
    system("clear");
    //第二步：将aDisplayBoardArray输出到屏幕上
    for (int i = 0; i < SIZE; i++) {
        printf("%2d", SIZE - i);
        printf("%s\n", aDisplayBoardArray[i]);
    }
    //第三步：输出最下面的一行字母A B ....
    printf("  A B C D E F G H I J K L M N O\n");
    if (current_col != -1 && current_row != -1) {
        // do not print before first move
        printf("Last Move: %c%d\n", current_col + 'A', SIZE - current_row);
    }
}

char checkEndGame(char current_player, int x, int y) {
    char ret = judge(x, y);
    // Black made a forbidden move
    if (current_player == 2 && (ret == 2 || checkForbiddenMoves(x, y))) {
        displayBoard();
        printf("Black made an forbidden move!\n");
        printf("White win!\n");
        return 2;
    }
    if (ret) {
        displayBoard();
        if (current_player == 1) {
            printf("White win!\n");
        } else if (current_player == 2) {
            printf("Black win!\n");
        }
        return 1;
    }
    return 0;
}

char judge(int i, int j) {
    for (int n = 0, count = 0; n < 4; ++n, count = 0) {
        int currentX = i, currentY = j;

        for (; validPos(currentX, currentY) &&
               aRecordBoard[currentX][currentY] == aRecordBoard[i][j];
             move(n, &currentX, &currentY), count++) {
        }

        currentX = i;
        currentY = j;
        move(n + 4, &currentX, &currentY);  // ooposite direction

        for (; validPos(currentX, currentY) &&
               aRecordBoard[currentX][currentY] == aRecordBoard[i][j];
             move(n + 4, &currentX, &currentY),  // ooposite direction
             count++) {
        }

        if (count > 5) {
            return 2;  // forbidden move: overline
        }
        if (count == 5) {
            return 1;  // victory
        }
    }
    return 0;
}

void move(int n, int* i, int* j) {
    switch (n) {
        case 0:  // down
            *j = *j + 1;
            break;
        case 1:  // right-down
            *i = *i + 1, *j = *j + 1;
            break;
        case 2:  // right
            *i = *i + 1;
            break;
        case 3:  // right-up
            *i = *i + 1;
            *j = *j - 1;
            break;
        case 4:  // up
            *j = *j - 1;
            break;
        case 5:  // left-up
            *i = *i - 1;
            *j = *j - 1;
            break;
        case 6:  // left
            *i = *i - 1;
            break;
        case 7:  // left-down
            *i = *i - 1;
            *j = *j + 1;
            break;
    }
}

char checkForbiddenMoves(int x, int y) {
    // Forbidden rules does not apply to White (1).
    if (aRecordBoard[x][y] == 1) {
        return 0;
    }
    if (checkDoubleThree(x, y) || checkDoubleFour(x, y) ||
        checkOverline(x, y)) {
        return 1;
    }
    return 0;
}

// TODO:
char checkDoubleThree(int x, int y) { return 0; }

// TODO:
char checkDoubleFour(int x, int y) { return 0; }

// covered when checking victory, with ret == 2
char checkOverline(int x, int y) { return 0; }
