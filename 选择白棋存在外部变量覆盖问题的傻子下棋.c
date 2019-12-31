#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 15
#define CHARSIZE 4
#define MAXLINE 1000

void initRecordBoard(void);
void recordtoDisplayArray(void);
void displayBoard(void);

//棋盘使用的是GBK编码，每一个中文字符占用2个字节。

//棋盘基本模板
char aInitDisplayBoardArray[SIZE][SIZE * CHARSIZE + 1] = {
    "┏┯┯┯┯┯┯┯┯┯┯┯┯┯┓", "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨", "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨", "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
    "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨", "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨", "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨", "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
    "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨", "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨", "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨", "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
    "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨", "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨", "┗┷┷┷┷┷┷┷┷┷┷┷┷┷┛"};
//此数组用于显示棋盘
char aDisplayBoardArray[SIZE][SIZE * CHARSIZE + 1];

char play1Pic[] = "●";  //黑棋子;
char play1CurrentPic[] = "▲";

char play2Pic[] = "◎";  //白棋子;
char play2CurrentPic[] = "△";

//此数组用于记录棋盘格局
int aRecordBoard[SIZE][SIZE];
int current_row, current_col;
int input(char current_player);
char judge(int aRecordBoard[15][15], int i, int j, char current_player);
int ren_ren(int aRecordBoard[15][15], char current_player);
int strategy_1(int aRecordBoard[15][15], char current_player);
int strategy_2(int aRecordBoard[15][15], char current_player);
void Move(int n, int* x, int* y);

int main(int argc, char* argv[]) {
    printf("Welcome to FiveInRow, written by Tangyufei\n");
    int Mode;
    printf("Mode choose:1 for ren_ren,2 for ren_computer\n");
    printf("Print q to quit anytime you want\n");
    scanf("%d", &Mode);
    if (Mode == 1) {
        char current_player;
        int ren;
        ren = ren_ren(aRecordBoard, current_player);
    } else if (Mode == 2) {
        int n;
        if (argc != 2 || (n = atoi(argv[1])) <= 0) {
            printf("Usage: ./FiveInRow n \n");
            printf("1 for XingXing, 2 for ShaZi, 3 for high\n");
            return 1;
        }
        n = atoi(argv[1]);
        if (n == 1) {
            printf("ren_computer with strategy: 1\n");
            char current_player;
            int strategy1;
            strategy1 = strategy_1(aRecordBoard, current_player);
        } else if (n == 2) {
            printf("ren_computer with strategy: 2\n");
            char current_player;
            int strategy2;
            strategy2 = strategy_2(aRecordBoard, current_player);
        } else if (n == 3)
            printf("ren_computer with strategy: 3\n");
        else if (n >= 4)
            printf("n is too large, it should be no more than 3\n");
        return 0;
    } else if (Mode != 1 && Mode != 2)
        printf("Mode choose,only 1 or 2\n");
    return 0;
}

int ren_ren(int aRecordBoard[15][15], char current_player) {
    int isquit = 0;
    int is_win;
    initRecordBoard();
    recordtoDisplayArray();
    displayBoard();
    current_player = 2;
    isquit = input(current_player);
    if (isquit == 1) return 0;
    displayBoard();
    is_win = judge(aRecordBoard, current_row, current_col, current_player);
    while (!is_win) {
        current_player = (current_player) % 2 + 1;
        isquit = input(current_player);
        if (isquit == 1) return 0;
        displayBoard();
        is_win = judge(aRecordBoard, current_row, current_col, current_player);
    }
    return 0;
}

int strategy_1(int aRecordBoard[15][15], char current_player) {
    int isquit = 0;
    int is_win = 0;
    int XingXingMove(char current_player);
    initRecordBoard();
    recordtoDisplayArray();
    displayBoard();
    int Choice;
    printf("Choice:1 for white and 2 for black.\n");
    scanf("%d", &Choice);
    current_player = Choice;
    if (Choice == 2) {
        current_player = 1;
        while (!is_win) {
            current_player = (current_player) % 2 + 1;
            isquit = input(current_player);
            if (isquit == 1) return 0;
            displayBoard();
            is_win =
                judge(aRecordBoard, current_row, current_col, current_player);
            if (is_win == 0) {
                current_player = (current_player) % 2 + 1;
                int XingXing;
                XingXing = XingXingMove(current_player);
                displayBoard();
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
            int XingXing;
            XingXing = XingXingMove(current_player);
            displayBoard();
            is_win =
                judge(aRecordBoard, current_row, current_col, current_player);
            if (is_win == 0) {
                current_player = (current_player) % 2 + 1;
                isquit = input(current_player);
                if (isquit == 1) return 0;
                displayBoard();
                is_win = judge(aRecordBoard, current_row, current_col,
                               current_player);
            } else
                break;
        }
    }
    return 0;
}

int ShaZiMove(int aRecordBoard[15][15], int x1, int y1, int x2, int y2,
              char current_player) {
    void Move(int n, int* i, int* j);
    int XingXingMove(char current_player);
    int n = 0;
    int tempx1 = x1, tempx2 = x2, tempy1 = y1, tempy2 = y2;
    while (n < 8) {
        x2 = tempx2, y2 = tempy2;
        Move(n, &x2, &y2);
        n = n + 1;
        if (x2 < 0 || x2 > 14 || y2 < 0 || y2 > 14) continue;
        if (aRecordBoard[x2][y2] == 0) break;
    }
    if (aRecordBoard[x2][y2] == 0) {
        aRecordBoard[x2][y2] = current_player;
        recordtoDisplayArray();
        displayBoard();
        return 0;
    } else {
        n = 0;
        while (n < 8) {
            x1 = tempx1, y1 = tempy1;
            Move(n, &x1, &y1);
            n = n + 1;
            if (x1 < 0 || x1 > 14 || y1 < 0 || y1 > 14) continue;
            if (aRecordBoard[x1][y1] == 0) break;
        }
        if (aRecordBoard[x1][y1] == 0) {
            aRecordBoard[x1][y1] = current_player;
            recordtoDisplayArray();
            displayBoard();
            return 0;
        } else {
            int XingXing;
            XingXing = XingXingMove(current_player);
        }
    }
}

int strategy_2(int aRecordBoard[15][15], char current_player) {
    int isquit = 0;
    int is_win = 0;
    int x1, x2, y1, y2;
    int ShaZiMove(int aRecordBoard[15][15], int x1, int y1, int x2, int y2,
                  char current_player);
    initRecordBoard();
    recordtoDisplayArray();
    displayBoard();
    int Choice;
    printf("Choice:1 for white and 2 for black.\n");
    scanf("%d", &Choice);
    current_player = Choice;
    if (Choice == 2) {
        current_player = 2;
        isquit = input(current_player);
        if (isquit == 1) return 0;
        displayBoard();
        x2 = current_row;
        y2 = current_col;
        current_player = (current_player) % 2 + 1;
        int ShaZi;
        x1 = x2;
        y1 = y2;
        ShaZi = ShaZiMove(aRecordBoard, x1, y1, x2, y2, current_player);
        displayBoard();
        x1 = current_col;
        y1 = current_col;
        is_win = judge(aRecordBoard, current_row, current_col, current_player);
        while (!is_win) {
            current_player = (current_player) % 2 + 1;
            isquit = input(current_player);
            if (isquit == 1) return 0;
            displayBoard();
            x2 = current_row;
            y2 = current_col;
            is_win =
                judge(aRecordBoard, current_row, current_col, current_player);
            if (is_win == 0) {
                current_player = (current_player) % 2 + 1;
                int ShaZi;
                ShaZi = ShaZiMove(aRecordBoard, x1, y1, x2, y2, current_player);
                displayBoard();
                x1 = current_row;
                y1 = current_col;
                is_win = judge(aRecordBoard, current_row, current_col,
                               current_player);
            } else {
                break;
            }
        }
    }
    if (Choice == 1) {
        current_player = 2;
        aRecordBoard[8][8] = 2;
        recordtoDisplayArray();
        displayBoard();
        x2 = 8, y2 = 8;
        current_player = current_player % 2 + 1;
        isquit = input(current_player);
        if (isquit == 1) return 0;
        displayBoard();
        x1 = current_row;
        y1 = current_col;
        while (1) {
            current_player = 2;
            int ShaZi;
            ShaZi = ShaZiMove(aRecordBoard, x1, y1, x2, y2, current_player);
            displayBoard();
            x2 = current_row;
            y2 = current_col;
            is_win =
                judge(aRecordBoard, current_row, current_col, current_player);
            if (is_win == 0) {
                current_player = 1;
                isquit = input(current_player);
                if (isquit == 1) return 0;
                displayBoard();
                x1 = current_row;
                y1 = current_col;
                is_win = judge(aRecordBoard, current_row, current_col,
                               current_player);
            } else {
                break;
            }
        }
    }
    return 0;
}

int XingXingMove(char current_player) {
    while (1) {
        current_row = rand() % 15;
        current_col = rand() % 15;
        if (aRecordBoard[current_row][current_col] == 0) break;
    }
    aRecordBoard[current_row][current_col] = current_player;
    recordtoDisplayArray();
    displayBoard();
    return 0;
}

// return 1 when need to quit, 0 if not;
// will recordtoDisplayArray and displayBoard
int input(char current_player) {
    printf("Input your cheese:\n");
    char d;
    int n;
    do {
        scanf("%c", &d);
        if (d == 'q') {
            printf("Player %d quit!\n", current_player);
            return 1;
        } else {
            scanf("%d", &n);
            if ((('A' <= d && d <= 'O') || ('a' <= d && d <= 'o')) && 1 <= n &&
                n <= 15) {
                if ('A' <= d && d <= 'O') {
                    current_row = 15 - n;
                    current_col = d - 'A';
                    if (aRecordBoard[current_row][current_col] == 0)
                        aRecordBoard[current_row][current_col] = current_player;
                    else {
                        printf("Position occupied!\n");
                        input(current_player);
                    }
                }
                if ('a' <= d && d <= 'o') {
                    current_row = 15 - n;
                    current_col = d - 'a';
                    if (aRecordBoard[current_row][current_col] == 0)
                        aRecordBoard[current_row][current_col] = current_player;
                    else {
                        printf("Position occupied!\n");
                        input(current_player);
                    }
                }
                recordtoDisplayArray();
                displayBoard();
                getchar();  // remove '\n'
                return 0;
            } else {
                printf("Please input again:\n");
            }
        }
    } while (1);
}

//初始化棋盘格局
void initRecordBoard(void) {
    //通过双重循环，将aRecordBoard清0
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < CHARSIZE; j++) aRecordBoard[i][j] = 0;
    }
}
//将aRecordBoard中记录的棋子位置，转化到aDisplayBoardArray中
void recordtoDisplayArray(void) {
    //第一步：将aInitDisplayBoardArray中记录的空棋盘，复制到aDisplayBoardArray中
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE * 2 + 1; j++)
            aDisplayBoardArray[i][j] = aInitDisplayBoardArray[i][j];
    }
    //第二步：扫描aRecordBoard，当遇到非0的元素，将●或者◎复制到aDisplayBoardArray的相应位置上
    //注意：aDisplayBoardArray所记录的字符是中文字符，每个字符占2个字节。●和◎也是中文字符，每个也占2个字节。
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            if (aRecordBoard[i][j] == 1) {
                aDisplayBoardArray[i][2 * j] = play1Pic[0];
                aDisplayBoardArray[i][2 * j + 1] = play1Pic[1];
            } else if (aRecordBoard[i][j] == 2) {
                aDisplayBoardArray[i][2 * j] = play2Pic[0];
                aDisplayBoardArray[i][2 * j + 1] = play2Pic[1];
            }
    }
}

//显示棋盘格局
void displayBoard(void) {
    int i;
    //第一步：清屏
    system("clear");
    // system("clear");   //清屏
    //第二步：将aDisplayBoardArray输出到屏幕上
    for (i = 0; i < SIZE; i++) {
        printf("%2d", 15 - i);
        printf("%s\n", aDisplayBoardArray[i]);
    }
    //第三步：输出最下面的一行字母A B ....
    printf("  A B C D E F G H I J K L M N O\n");
}

char judge(int aRecordBoard[15][15], int i, int j, char current_player) {
    char judge_line(int aRecordBoard[15][15], int i, int j,
                    char current_player);
    char judge_row(int aRecordBoard[15][15], int i, int j, char current_player);
    char judge_up_down(int aRecordBoard[15][15], int i, int j,
                       char current_player);
    char judge_down_up(int aRecordBoard[15][15], int i, int j,
                       char current_player);
    char a, b, c, d;
    a = judge_line(aRecordBoard, i, j, current_player);
    b = judge_row(aRecordBoard, i, j, current_player);
    c = judge_up_down(aRecordBoard, i, j, current_player);
    d = judge_down_up(aRecordBoard, i, j, current_player);
    if (a == 1 || b == 1 || c == 1 || d == 1) {
        if (current_player == 1)
            printf("White win!\n");
        else if (current_player == 2)
            printf("Black win!\n");
        return 1;
    }
    return 0;
}
char judge_line(int aRecordBoard[15][15], int i, int j, char current_player) {
    int count = 1;
    int k = j;
    while (k >= 0) {
        if (aRecordBoard[i][--k] == aRecordBoard[i][j])
            count++;
        else
            break;
    }
    k = j;
    while (j <= 14) {
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
char judge_row(int aRecordBoard[15][15], int i, int j, char current_player) {
    int count = 1;
    int k = i;
    while (k >= 0) {
        if (aRecordBoard[--k][j] == aRecordBoard[i][j])
            count++;
        else
            break;
    }
    k = i;
    while (i <= 14) {
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
char judge_down_up(int aRecordBoard[15][15], int i, int j,
                   char current_player) {
    int count = 1;
    int k = i, l = j;
    while (k >= 0 && l <= 14) {
        if (aRecordBoard[--k][++l] == aRecordBoard[i][j])
            count++;
        else
            break;
    }
    k = i, l = j;
    while (k <= 14 && l >= 0) {
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
char judge_up_down(int aRecordBoard[15][15], int i, int j,
                   char current_player) {
    int count = 1;
    int k = i, l = j;
    while (k <= 14 && l <= 14) {
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
