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
int current_row, current_col;

// used for fgets & sscanf for input
char buff[MAXLINE];

void ren_ren(int aRecordBoard[SIZE][SIZE], char current_player);
void strategy_1(int aRecordBoard[SIZE][SIZE], char current_player);
void XingXingMove(char current_player);
void strategy_2(int aRecordBoard[SIZE][SIZE], char current_player);
void ShaZiMove(int aRecordBoard[SIZE][SIZE], int inputX[3], int inputY[3],
               char current_player);

int inputGetInt();
int input(char current_player);
void initRecordBoard(void);
void recordtoDisplayArray(void);
void displayBoard(void);

char judge(int aRecordBoard[SIZE][SIZE], int i, int j, char current_player);
char judge_line(int aRecordBoard[SIZE][SIZE], int i, int j);
char judge_row(int aRecordBoard[SIZE][SIZE], int i, int j);
char judge_up_down(int aRecordBoard[SIZE][SIZE], int i, int j);
char judge_down_up(int aRecordBoard[SIZE][SIZE], int i, int j);

void Move(int n, int* x, int* y);

int main(int argc, char* argv[]) {
    int Mode;
    char current_player;
    printf("Welcome to FiveInRow, written by Tang Yufei\n");
    printf("Mode choose:1 for ren_ren,2 for ren_computer\n");
    printf("Print q to quit anytime you want\n");
    Mode = inputGetInt();
    if (Mode == 1) {
        ren_ren(aRecordBoard, current_player);
    } else if (Mode == 2) {
        int n;
        if (argc != 2 || (n = atoi(argv[1])) <= 0) {
            printf("Usage: ./FiveInRow n \n");
            printf("1 for XingXing, 2 for ShaZi, 3 for high\n");
            return 1;  // error code: 1
        }
        n = atoi(argv[1]);
        if (n == 1) {
            printf("ren_computer with strategy: 1\n");
            strategy_1(aRecordBoard, current_player);
        } else if (n == 2) {
            printf("ren_computer with strategy: 2\n");
            strategy_2(aRecordBoard, current_player);
        } else if (n == 3) {
            printf("ren_computer with strategy: 3\n");
        } else if (n >= 4) {
            printf("n is too large, it should be no more than 3\n");
        }
        return 0;
    } else if (Mode != 1 && Mode != 2) {
        printf("Mode choose,only 1 or 2\n");
    }
    return 0;
}

void ren_ren(int aRecordBoard[SIZE][SIZE], char current_player) {
    int isquit = 0;
    int is_win;

    initRecordBoard();
    current_player = 2;
    isquit = input(current_player);
    if (isquit == 1) return;
    is_win = judge(aRecordBoard, current_row, current_col, current_player);
    while (!is_win) {
        current_player = (current_player) % 2 + 1;
        isquit = input(current_player);
        if (isquit == 1) return;
        is_win = judge(aRecordBoard, current_row, current_col, current_player);
    }
    return;
}

void strategy_1(int aRecordBoard[SIZE][SIZE], char current_player) {
    int isquit = 0;
    int is_win = 0;
    int Choice;

    initRecordBoard();

    printf("Choice:1 for white and 2 for black.\n");
    // scanf("%d", &Choice);
    Choice = inputGetInt();
    current_player = Choice;

    if (Choice == 2) {
        current_player = 1;
        while (!is_win) {
            current_player = (current_player) % 2 + 1;
            isquit = input(current_player);
            if (isquit == 1) return;
            is_win =
                judge(aRecordBoard, current_row, current_col, current_player);
            if (is_win == 0) {
                current_player = (current_player) % 2 + 1;
                XingXingMove(current_player);
                is_win = judge(aRecordBoard, current_row, current_col,
                               current_player);
            } else {
                break;
            }
        }
    }
    if (Choice == 1) {
        while (!is_win) {
            current_player = (current_player) % 2 + 1;
            XingXingMove(current_player);
            is_win =
                judge(aRecordBoard, current_row, current_col, current_player);
            if (is_win == 0) {
                current_player = (current_player) % 2 + 1;
                isquit = input(current_player);
                if (isquit == 1) return;
                is_win = judge(aRecordBoard, current_row, current_col,
                               current_player);
            } else
                break;
        }
    }
    return;
}

void XingXingMove(char current_player) {
    while (1) {
        current_row = rand() % SIZE;
        current_col = rand() % SIZE;
        if (aRecordBoard[current_row][current_col] == EMPTY) break;
    }
    aRecordBoard[current_row][current_col] = current_player;
}

void strategy_2(int aRecordBoard[SIZE][SIZE], char current_player) {
    int isquit = 0;
    int is_win = 0;
    int Choice;
    int x[3], y[3];

    initRecordBoard();

    printf("Choice:1 for white and 2 for black.\n");
    Choice = inputGetInt();

    if (Choice == 1) {
        current_player = 2;
        x[1] = x[2] = 8;
        y[1] = y[2] = 8;
        aRecordBoard[x[current_player]][y[current_player]] = current_player;
    }
    current_player = Choice;

    while (!is_win) {
        if (current_player == Choice) {
            isquit = input(current_player);
            if (isquit) return;
        } else {
            ShaZiMove(aRecordBoard, x, y, current_player);
        }
        x[current_player] = current_row;
        y[current_player] = current_col;
        is_win = judge(aRecordBoard, current_row, current_col, current_player);
        current_player = (current_player) % 2 + 1;
    }
}

void ShaZiMove(int aRecordBoard[SIZE][SIZE], int inputX[3], int inputY[3],
               char current_player) {
    int n = 0;
    int x[3], y[3];
    for (int i = 1; i < 3; i++) {
        x[i] = inputX[i];
        y[i] = inputY[i];
    }
    // start with 2: black
    for (int i = 2; i > 0; i--) {
        while (n < 8) {
            Move(n, &x[i], &y[i]);
            n = n + 1;
            if (x[i] < 0 || x[i] >= SIZE || y[i] < 0 || y[i] >= SIZE) continue;
            if (aRecordBoard[x[i]][y[i]] == EMPTY) break;
        }
        if (aRecordBoard[x[i]][y[i]] == EMPTY) {
            aRecordBoard[x[i]][y[i]] = current_player;
            current_row = x[i];
            current_col = y[i];
            return;
        }
    }
    XingXingMove(current_player);
}

int inputGetInt() {
    fgets(buff, MAXLINE - 1, stdin);
    return atoi(buff);
}

// return 1 when need to quit, 0 if not; will displayBoard
int input(char current_player) {
    char d;
    int n;

    displayBoard();

    do {
        printf("Input your cheese:\n");
        fgets(buff, MAXLINE - 1, stdin);
        if (buff[0] == '\n') {
            continue;
        }
        sscanf(buff, "%c", &d);
        d = toupper(d);
        if (d == 'Q') {
            printf("Player %d quit!\n", current_player);
            return 1;
        }
        n = atoi(buff + 1);
        if ('A' <= d && d <= 'O' && 1 <= n && n <= SIZE) {
            if ('A' <= d && d <= 'O') {
                current_row = SIZE - n;
                current_col = d - 'A';
                if (aRecordBoard[current_row][current_col] == EMPTY) {
                    aRecordBoard[current_row][current_col] = current_player;
                } else {
                    printf("Position occupied!\n");
                    continue;
                }
            }
            displayBoard();
            return 0;
        } else {
            printf("Please input again:\n");
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
}

char judge(int aRecordBoard[SIZE][SIZE], int i, int j, char current_player) {
    char a, b, c, d;

    a = judge_line(aRecordBoard, i, j);
    b = judge_row(aRecordBoard, i, j);
    c = judge_up_down(aRecordBoard, i, j);
    d = judge_down_up(aRecordBoard, i, j);
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
char judge_line(int aRecordBoard[SIZE][SIZE], int i, int j) {
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
char judge_row(int aRecordBoard[SIZE][SIZE], int i, int j) {
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
char judge_down_up(int aRecordBoard[SIZE][SIZE], int i, int j) {
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
char judge_up_down(int aRecordBoard[SIZE][SIZE], int i, int j) {
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
