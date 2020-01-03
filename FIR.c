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

int inputGetInt();
char validateMove(int x, int y);
int input(char current_player);
void initRecordBoard(void);
void recordtoDisplayArray(void);
void displayBoard(void);

char judge(int i, int j, char current_player);
char judge_line(int i, int j);
char judge_row(int i, int j);
char judge_up_down(int i, int j);
char judge_down_up(int i, int j);

void Move(int n, int* x, int* y);

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
         !judge(current_row, current_col, current_player);
         current_player ^= 3) {
    }
}

void PvE(strategy func) {
    int choice = 0;
    int current_player = 0;
    int x[3] = {0};
    int y[3] = {0};

    printf("Choice:1 for white and 2 for black.\n");
    choice = inputGetInt();
    if (choice != 1 && choice != 2) {
        printf("Wrong input. Quit.\n");
        return;
    }

    if (choice == 1) {
        current_player = 2;
        x[1] = x[2] = 8;
        y[1] = y[2] = 8;
        aRecordBoard[x[current_player]][y[current_player]] = current_player;
    }

    for (current_player = 2;
         !judge(current_row, current_col, current_player ^ 3);
         current_player ^= 3) {
        if (current_player == choice) {
            if (input(current_player)) {  // quit when ret != 0
                return;
            }
        } else {
            func(current_player, x, y);
        }
        x[current_player] = current_row;
        y[current_player] = current_col;
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
    int x[3], y[3];

    // start with 2: black
    for (int i = 2; i > 0; i--) {
        int n = 0;
        do {
            for (int i = 1; i < 3; i++) {
                x[i] = inputX[i];
                y[i] = inputY[i];
            }
            Move(n, &x[i], &y[i]);
            n = n + 1;
        } while (n < 8 && !validateMove(x[i], y[i]));
        if (aRecordBoard[x[i]][y[i]] == EMPTY) {
            aRecordBoard[x[i]][y[i]] = current_player;
            current_row = x[i];
            current_col = y[i];
            return;
        }
    }
    XingXingMove(current_player, inputX, inputY);
}

int inputGetInt() {
    fgets(buff, MAXLINE - 1, stdin);
    return atoi(buff);
}

char validateMove(int x, int y) {
    if (x >= 0 && x < SIZE && y >= 0 && y < SIZE &&
        aRecordBoard[x][y] == EMPTY) {
        return 1;
    }
    return 0;
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
        if (validateMove(x, y)) {
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

char judge(int i, int j, char current_player) {
    char a, b, c, d;

    a = judge_line(i, j);
    b = judge_row(i, j);
    c = judge_up_down(i, j);
    d = judge_down_up(i, j);
    if (a == 1 || b == 1 || c == 1 || d == 1) {
        displayBoard();
        if (current_player == 1)
            printf("White win!\n");
        else if (current_player == 2)
            printf("Black win!\n");
        return 1;
    }
    return 0;
}
char judge_line(int i, int j) {
    int count = 1;
    int k = j;
    while (k >= 0) {
        if (aRecordBoard[i][--k] == aRecordBoard[i][j])
            count++;
        else
            break;
    }
    k = j;
    while (j < SIZE) {
        if (aRecordBoard[i][++k] == aRecordBoard[i][j])
            count++;
        else
            break;
    }
    if (count >= 5)
        return 1;
    else
        return 0;
}
char judge_row(int i, int j) {
    int count = 1;
    int k = i;
    while (k >= 0) {
        if (aRecordBoard[--k][j] == aRecordBoard[i][j])
            count++;
        else
            break;
    }
    k = i;
    while (i < SIZE) {
        if (aRecordBoard[++k][j] == aRecordBoard[i][j])
            count++;
        else
            break;
    }
    if (count >= 5)
        return 1;
    else
        return 0;
}
char judge_down_up(int i, int j) {
    int count = 1;
    int k = i, l = j;
    while (k >= 0 && l < SIZE) {
        if (aRecordBoard[--k][++l] == aRecordBoard[i][j])
            count++;
        else
            break;
    }
    k = i, l = j;
    while (k < SIZE && l >= 0) {
        if (aRecordBoard[++k][--l] == aRecordBoard[i][j])
            count++;
        else
            break;
    }
    if (count >= 5)
        return 1;
    else
        return 0;
}
char judge_up_down(int i, int j) {
    int count = 1;
    int k = i, l = j;
    while (k < SIZE && l < SIZE) {
        if (aRecordBoard[++k][++l] == aRecordBoard[i][j])
            count++;
        else
            break;
    }
    k = i, l = j;
    while (k >= 0 && l >= 0) {
        if (aRecordBoard[--k][--l] == aRecordBoard[i][j])
            count++;
        else
            break;
    }
    if (count >= 5)
        return 1;
    else
        return 0;
}

void Move(int n, int* i, int* j) {
    switch (n) {
        case 0:
            *j = *j + 1;
            break;  // 	5	6	7
        case 1:
            *i = *i + 1, *j = *j + 1;
            break;  //	4	*	0
        case 2:
            *i = *i + 1;
            break;  //	3	2	1
        case 3:
            *i = *i + 1;
            *j = *j - 1;
            break;
        case 4:
            *j = *j - 1;
            break;
        case 5:
            *i = *i - 1;
            *j = *j - 1;
            break;
        case 6:
            *i = *i - 1;
            break;
        case 7:
            *i = *i - 1;
            *j = *j + 1;
            break;
    }
}
