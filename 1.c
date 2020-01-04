#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 15
#define CHARSIZE 2
#define MAXLEN 1000
void initRecordBorard(void);
void recordtoDisplayArray(void);
void displayBoard(void);
int win(int p, int q, int c);  //判断输赢；
void defence(void);  //人机对战时，电脑执白棋，为保守方；
void attack(void);   //人机对战时，电脑执黑棋，为进攻方；
int changlianjinshou(int p, int q, int c);     //判断长连禁手；
int shuanghuosanjinshou(int p, int q, int c);  //判断双活三禁手；
int sisijinshou(int p, int q, int c);          //判断四四禁手；
int checkUnbrokenFour(int p, int q, int c);    //判断是否形成活四；
int checkBrokenFour(int p, int q, int c);      //判断是否形成冲四；
int checkUnbrokenThree(int p, int q, int c);   //判断是否形成活三；
int checkUnbrokenTwo(int p, int q, int c);     //判断是否形成活二；
int defence_score(int p, int q, int c);        //己方计算保守得分；
int attack_score(int p, int q, int c);  //换成对方的棋子，计算对方的进攻得分；
void yiwei(int n, int *i, int *j);
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
int aRecordBoard[SIZE][SIZE];  // remember the state of the pic
int p = -1;
int q = -1;
int *x_max, *y_max;
int x_c = 1, y_c = 1;
int main() {
    int a, b, k, c = 0;
    initRecordBorard();
    printf("~~work of tangyufei~~\n");
    printf("if you wan to quit, please put in q\n");
    printf("with another player input 1\nwith computer input 2\n");
    scanf("%d", &a);  //从键盘上读入游戏模式选择；
    if (a == 1) {     //人人对战；
        for (k = 0; k < MAXLEN; k++) {
            int n1 = 0, n2 = 0, m1 = 0, m2 = 0, m3 = 0;
            if (c == 0) {  // c=0表示先手；
                printf("player with black pic:\n");
                if ((n1 = getchar()) == 10) {  //用getchar函数从键盘上读入坐标；
                    n1 = getchar();
                    n2 = getchar();
                } else {
                    n2 = getchar();
                }
                if (n1 == 'q') {
                    return 0;
                }
                if (n2 != ' ') {
                    p = (n1 - 48) * 10 + (n2 - 48);
                    m1 = getchar();
                } else {
                    p = n1 - 48;
                }
                m2 = getchar();
                m3 = getchar();
                if (m2 >= 'A' && m2 <= 'O') {
                    q = m2 - 'A' + 1;
                } else {
                    if (m3 != 10) {
                        q = (m2 - 48) * 10 + (m3 - 48);
                    } else {
                        q = (m2 - 48);
                    }
                }
                if (p > SIZE || q > SIZE) {
                    printf("Input Wrong\n");
                }
                aRecordBoard[p][q] = 1;
                recordtoDisplayArray();
                displayBoard();
                getchar();
                printf("the player put at %d %d\n", p, q);
                if (win(p, q, 1) &&
                    (changlianjinshou(p, q, 1) != 1)) {  //判断输赢；
                    printf("BLACK WIN\n");
                    return 0;
                }
                if (changlianjinshou(p, q, 1) || sisijinshou(p, q, 1) ||
                    shuanghuosanjinshou(p, q, 1)) {  //判断禁手；
                    printf("WHITE WIN\n");
                    return 0;
                }
                c = 1;
            } else if (c == 1) {  // c=1表示后手；
                n1 = 0, n2 = 0, m1 = 0, m2 = 0, m3 = 0;
                printf("player with white pic:\n");
                n1 = getchar();
                n2 = getchar();  //用getchar函数从键盘上读入坐标；
                if (n1 == 'q') {
                    return 0;
                }
                if (n2 != ' ') {
                    p = (n1 - 48) * 10 + (n2 - 48);
                    m1 = getchar();
                } else {
                    p = n1 - 48;
                }
                m2 = getchar();
                m3 = getchar();
                if (m2 >= 'A' && m2 <= 'O') {
                    q = m2 - 'A' + 1;
                } else {
                    if (m3 != 10) {
                        q = (m2 - 48) * 10 + (m3 - 48);
                    } else {
                        q = (m2 - 48);
                    }
                }
                if (p > SIZE || q > SIZE) {
                    printf("Input Wrong\n");
                }
                aRecordBoard[p][q] = 2;
                recordtoDisplayArray();
                displayBoard();
                getchar();
                printf("the player put at %d %d\n", p, q);
                if (win(p, q, 2)) {  //判断输赢；
                    printf("WHITE WIN\n");
                }
                c = 0;
            }
        }
    } else if (a == 2) {  //人机对战
        int d;            //玩家选择先手or后手；
        printf("play with black pic input 1\nplay with white pic input 2\n");
        scanf("%d", &d);
        if (d == 1) {  //玩家先手，执黑棋；
            for (k = 0; k < MAXLEN; k++) {
                int n1 = 0, n2 = 0, m1 = 0, m2 = 0, m3 = 0;
                if (c == 0) {  //玩家下棋；
                    printf("player:\n");
                    if ((n1 = getchar()) ==
                        10) {  //用getchar函数从键盘上读入坐标；
                        n1 = getchar();
                        n2 = getchar();
                    } else {
                        n2 = getchar();
                    }
                    if (n1 == 'q') {
                        return 0;
                    }
                    if (n2 != ' ') {
                        p = (n1 - 48) * 10 + (n2 - 48);
                        m1 = getchar();
                    } else {
                        p = n1 - 48;
                    }
                    m2 = getchar();
                    m3 = getchar();
                    if (m2 >= 'A' && m2 <= 'O') {
                        q = m2 - 'A' + 1;
                    } else {
                        if (m3 != 10) {
                            q = (m2 - 48) * 10 + (m3 - 48);
                        } else {
                            q = (m2 - 48);
                        }
                    }
                    if (p > SIZE || q > SIZE) {
                        printf("Input Wrong\n");
                    }
                    aRecordBoard[p][q] = 1;
                    recordtoDisplayArray();
                    displayBoard();
                    getchar();
                    printf("the player put at %d %d\n", p, q);
                    if (win(p, q, 1) &&
                        (changlianjinshou(p, q, 1) != 1)) {  //判断输赢；
                        printf("Player WIN\n");
                        return 0;
                    }
                    if (changlianjinshou(p, q, 1) || sisijinshou(p, q, 1) ||
                        shuanghuosanjinshou(p, q, 1)) {  //判断禁手；
                        printf("Computer Win\n");
                        return 0;
                    }
                    c = 1;
                } else if (c == 1) {  //电脑下棋；
                    printf("Computer:\n");
                    defence();
                    p = *x_max;
                    q = *y_max;
                    aRecordBoard[p][q] = 2;
                    recordtoDisplayArray();
                    displayBoard();
                    getchar();
                    printf("the computer put at %d %d\n", p, q);
                    if (win(p, q, 2)) {
                        printf("Computer WIN\n");
                        return 0;
                    }
                    c = 0;
                }
            }
        } else if (d == 2) {         //玩家后手，执白棋；
            aRecordBoard[8][8] = 1;  //在中心处下子；
            recordtoDisplayArray();
            displayBoard();
            printf("the computer put at 8 8\n");
            for (k = 0; k < MAXLEN; k++) {
                int n1 = 0, n2 = 0, m1 = 0, m2 = 0, m3 = 0;
                if (c == 0) {  //玩家下棋；
                    printf("Player:\n");
                    if ((n1 = getchar()) == 10) {
                        n1 = getchar();
                        n2 = getchar();
                    } else {
                        n2 = getchar();
                    }
                    if (n1 == 'q') {
                        return 0;
                    }
                    if (n2 != ' ') {
                        p = (n1 - 48) * 10 + (n2 - 48);
                        m1 = getchar();
                    } else {
                        p = n1 - 48;
                    }
                    m2 = getchar();
                    m3 = getchar();
                    if (m2 >= 'A' && m2 <= 'O') {
                        q = m2 - 'A' + 1;
                    } else {
                        if (m3 != 10) {
                            q = (m2 - 48) * 10 + (m3 - 48);
                        } else {
                            q = (m2 - 48);
                        }
                    }
                    if (p > SIZE || q > SIZE) {
                        printf("Input Wrong\n");
                    }
                    aRecordBoard[p][q] = 2;
                    recordtoDisplayArray();
                    displayBoard();
                    getchar();
                    printf("the player put at %d %d\n", p, q);
                    if (win(p, q, 2)) {
                        printf("player WIN\n");
                        return 0;
                    }
                    c = 1;
                }
                if (c == 1) {  //电脑下棋；
                    attack();
                    p = *x_max;
                    q = *y_max;
                    aRecordBoard[p][q] = 1;
                    recordtoDisplayArray();
                    displayBoard();
                    getchar();
                    printf("the computer put at %d %d\n", p, q);
                    if (win(p, q, 1)) {
                        printf("Computer WIN\n");
                        return 0;
                    }
                    c = 0;
                }
            }
        }
    }
}

//初始化棋盘格局
void initRecordBorard(void) {
    //通过双重循环，将aRecordBoard清0
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            aRecordBoard[i][j] = 0;
        }
    }
}
//将aRecordBoard中记录的棋子位置，转化到aDisplayBoardArray中
void recordtoDisplayArray(void) {
    int m,
        n;  //第一步：将aInitDisplayBoardArray中记录的空棋盘，复制到aDisplayBoardArray中
    for (m = 0; m < SIZE; m++) {
        for (n = 0; n < CHARSIZE * SIZE + 1; n++) {
            aDisplayBoardArray[m][n] = aInitDisplayBoardArray[m][n];
        }
    }
    int i, j, k;
    k = 0;  //第二步：扫描aRecordBoard，当遇到非0的元素，将●或者◎复制到aDisplayBoardArray的相应位置上
    for (i = 1; i <= SIZE; i++) {
        for (j = 1; j <= SIZE; j++) {
            if (aRecordBoard[i][j] == 1) {
                for (k = 0; k <= 1; k++) {
                    aDisplayBoardArray[SIZE - i][(j - 1) * CHARSIZE + k] =
                        play1Pic[k];
                }
            } else if (aRecordBoard[i][j] == 2) {
                for (k = 0; k <= 1; k++) {
                    aDisplayBoardArray[SIZE - i][(j - 1) * CHARSIZE + k] =
                        play2Pic[k];
                }
            }
        }
    }
    if (aRecordBoard[p][q] == 1) {
        aDisplayBoardArray[SIZE - p][2 * (q - 1)] = play1CurrentPic[0];
        aDisplayBoardArray[SIZE - p][2 * (q - 1) + 1] = play1CurrentPic[1];
    } else if (aRecordBoard[p][q] == 2) {
        aDisplayBoardArray[SIZE - p][2 * (q - 1)] = play2CurrentPic[0];
        aDisplayBoardArray[SIZE - p][2 * (q - 1) + 1] = play2CurrentPic[1];
    }
}
void displayBoard(void) {  //显示棋盘格局
    int i, j;
    system("clear");  //第一步：清屏
    for (i = 0; i < SIZE; i++) {
        if (i <= 5) {
            printf("%d", SIZE - i);
        } else if (i > 5) {
            printf(" %d", SIZE - i);
        }
        for (j = 0; j < SIZE * CHARSIZE + 1;
             j++) {  //将aDisplayBoardArray输出到屏幕上
            printf("%c", aDisplayBoardArray[i][j]);
        }
        printf("\n");
    }
    printf("   A B C D E F G H I J K L M N O \n");
}
int win(int a, int b, int current_player)  //判断输赢；
{
    int n = 1, m, P, Q;
    P = a;
    Q = b;
    while (n != 5) {
        m = 0;
        while (aRecordBoard[a][b] == current_player) {
            m++;
            if (m == 5) {
                return 1;
            }
            yiwei(n, &a, &b);
            if (a < 1 || a > 15 || b < 1 || b > 15) {
                break;
            }
        }
        n += 4;
        m -= 1;
        a = P;
        b = Q;
        while (aRecordBoard[a][b] == current_player) {
            m++;
            if (m == 5) {
                return 1;
            }
            yiwei(n, &a, &b);
            if (a < 1 || a > 15 || b < 1 || b > 15) {
                break;
            }
        }
        n -= 3;
        a = P;
        b = Q;
    }
    return 0;
}
void yiwei(int n, int *i,
           int *j)  //以（i,j）为中心，绕上下、左右、左斜、右斜四个方向扫描；
{
    switch (n) {
        case 1:
            *i += 1;
            break;
        case 2:
            *i += 1;
            *j += 1;
            break;
        case 3:
            *j += 1;
            break;
        case 4:
            *i -= 1;
            *j += 1;
            break;
        case 5:
            *i -= 1;
            break;
        case 6:
            *i -= 1;
            *j -= 1;
            break;
        case 7:
            *j -= 1;
            break;
        case 8:
            *i += 1;
            *j -= 1;
            break;
    }
}
int changlianjinshou(
    int a, int b,
    int c)  //判断长连禁手，以（i，j）为中心的四个方向连续超过5个即为长连；
{
    int n = 1, m, P, Q;
    int jifang = 0, duifang = 0;
    P = a;
    Q = b;
    if (c == 1) {
        jifang = 1;
        duifang = 2;
    } else if (c == 2) {
        jifang = 2;
        duifang = 1;
    }
    while (n != 5) {
        m = 0;
        while (aRecordBoard[a][b] == jifang) {
            m++;
            if (m > 5) {
                return 1;
            }
            yiwei(n, &a, &b);
            if (a < 1 || a > 15 || b < 1 || b > 15) {
                break;
            }
        }
        n += 4;
        m -= 1;
        a = P;
        b = Q;
        while (aRecordBoard[a][b] == jifang) {
            m++;
            if (m > 5) {
                return 1;
            }
            yiwei(n, &a, &b);
            if (a < 1 || a > 15 || b < 1 || b > 15) {
                break;
            }
        }
        n -= 3;
        a = P;
        b = Q;
    }
    return 0;
}
int shuanghuosanjinshou(int a, int b, int c) {
    //判断双活三禁手，在四个方向中的两个有活三，即为双活三；
    // a，b为坐标，c代表棋子的类型，c=1为黑子，c=0为白子；
    //以后的循环情况与此函数的循环情况基本相同，不再赘述;
    int n = 1, m, P, Q, huosan = 0, liangduan1, liangduan2, temp,
        kong;  // liangduan1，liangduan2用来判断是活三还是冲三；
    int jifang = 0, duifang = 0, chenghuosi;
    P = a;
    Q = b;
    if (c == 1) {
        jifang = 1;
        duifang = 2;
    } else if (c == 2) {
        jifang = 2;
        duifang = 1;
    }
    while (n != 5) {
        m = 0;
        liangduan1 = -1;
        liangduan2 = -1;
        temp = 0;
        kong = 0;
        chenghuosi = 0;
        while (aRecordBoard[a][b] == jifang &&
               temp <= 3) {  // temp用来记录向每个方向已经判断了多少步；
            m++;
            yiwei(n, &a, &b);
            temp += 1;
            if (a < 1 || a > 15 || b < 1 || b > 15) {
                liangduan1 = 1;
                break;
            }
            if (aRecordBoard[a][b] == 0) {
                aRecordBoard[a][b] = jifang;
                if (checkUnbrokenFour(a, b, jifang) ==
                    1) {  //在空位上填上己方的子，观察是否为活四
                    chenghuosi += 1;
                }
                aRecordBoard[a][b] = 0;
                yiwei(n, &a, &b);
                temp += 1;
                if (aRecordBoard[a][b] == jifang) {
                    kong += 1;
                    continue;  //出现没有子的情况，再往后看一下后面的棋形；
                }
                liangduan1 = 0;
                break;
            }
        }
        n += 4;
        m -= 1;
        a = P;
        b = Q;
        temp = 0;
        while (aRecordBoard[a][b] == jifang && temp <= 3) {
            m++;
            yiwei(n, &a, &b);
            temp += 1;
            if (a < 1 || a > 15 || b < 1 || b > 15) {
                liangduan2 = 1;
                break;
            }
            if (aRecordBoard[a][b] == 0) {
                aRecordBoard[a][b] = jifang;
                if (checkUnbrokenFour(a, b, jifang) == 1) {
                    chenghuosi += 1;
                }
                aRecordBoard[a][b] = 0;
                yiwei(n, &a, &b);
                temp += 1;
                if (aRecordBoard[a][b] == jifang) {
                    kong += 1;
                    continue;
                }
                liangduan2 = 0;
                break;
            }
        }
        if (m == 3 && liangduan1 == 0 && liangduan2 == 0 && kong < 2 &&
            chenghuosi >=
                1) {  //两端为空，并且中间最多有一个空白位置，则为活三；
            huosan += 1;
            if (huosan == 2) {
                return 1;
            }
        }
        n -= 3;
        a = P;
        b = Q;
    }
    return 0;
}
int sisijinshou(int a, int b, int c)  //判断四四禁手；
{
    int i, j, n = 1, m, P, Q, huosi = 0, chongsi = 0, liangduan1, liangduan2;
    int jifang = 0, duifang = 0;
    int K[SIZE], L[SIZE];  //用来记录空白位置距离中心棋子的距离；
    float temp;
    P = a;
    Q = b;
    if (c == 1) {
        jifang = 1;
        duifang = 2;
    } else if (c == 2) {
        jifang = 2;
        duifang = 1;
    }
    while (n != 5) {
        for (i = 0, j = 0; i < SIZE, j < SIZE; i++, j++) {
            K[i] = 0;
            L[j] = 0;
        }
        m = 0;
        liangduan1 = -1;
        liangduan2 = -1;
        temp = 0.0;
        while (
            aRecordBoard[a][b] == jifang &&
            temp <
                4.0) {  // temp用来记录向每个方向已经判断了多少步，出现0.6是用来讨论出现空位置的情况；
            m++;
            yiwei(n, &a, &b);
            temp += 1.0;
            if (a < 1 || a > 15 || b < 1 || b > 15) {
                liangduan1 = 1;
                break;
            }
            if (aRecordBoard[a][b] == 0) {
                temp += 0.6;
                K[m] = a;
                L[m] = b;
                yiwei(n, &a, &b);
                if (aRecordBoard[a][b] == jifang) {
                    continue;
                }
                liangduan1 = 0;
                break;
            }
            if (aRecordBoard[a][b] == duifang) {
                liangduan1 = 1;
                break;
            }
        }
        n += 4;
        m -= 1;
        a = P;
        b = Q;
        temp = 0;
        while (aRecordBoard[a][b] == jifang && temp < 4.0) {
            m++;
            yiwei(n, &a, &b);
            temp += 1.0;
            if (a < 1 || a > 15 || b < 1 || b > 15) {
                liangduan2 = 1;
                break;
            }
            if (aRecordBoard[a][b] == 0) {
                temp += 0.6;
                K[m] = a;
                L[m] = b;
                yiwei(n, &a, &b);
                if (aRecordBoard[a][b] == jifang) {
                    continue;
                }
                liangduan2 = 0;
                break;
            }
            if (aRecordBoard[a][b] == duifang) {
                liangduan2 = 1;
                break;
            }
        }
        if (m == 4 && liangduan1 == 0 && liangduan2 == 0) {
            huosi += 1;
            if (huosi == 2) {
                return 1;
            }
        }
        if (m == 4 && ((liangduan1 == 1 && liangduan2 == 0) ||
                       (liangduan1 == 0 && liangduan2 == 1))) {
            chongsi += 1;
            if (chongsi == 2) {
                return 1;
            }
        }
        if (chongsi + huosi == 2) {
            return 1;
        }
        n -= 3;
        a = P;
        b = Q;  //以下是特殊的四四禁手的情况，即出现在一个方向上，不是在两个方向上的双四；
        if (m == 5 &&
            (K[2] - 2 == a || K[2] + 2 == a || L[2] - 2 == b ||
             L[2] + 2 == b) &&
            (K[4] - 2 == a || K[4] + 2 == a || L[4] - 2 == b ||
             L[4] + 2 == b)) {
            return 1;
        }
        if (m == 6 && (((K[1] - 1 == a || K[1] + 1 == a || L[1] - 1 == b ||
                         L[1] + 1 == b) &&
                        (K[4] - 2 == a || K[4] + 2 == a || L[4] - 2 == b ||
                         L[4] + 2 == b)) ||
                       ((K[2] - 2 == a || K[2] + 2 == a || L[2] - 2 == b ||
                         L[2] + 2 == b) &&
                        (K[4] - 1 == a || K[4] + 1 == a || L[4] - 1 == b ||
                         L[4] + 1 == b)))) {
            return 1;
        }
        if (m == 7 &&
            (K[1] - 1 == a || K[1] + 1 == a || L[1] - 1 == b ||
             L[1] + 1 == b) &&
            (K[4] - 1 == a || K[4] + 1 == a || L[4] - 1 == b ||
             L[4] + 1 == b)) {
            return 1;
        }
    }
    return 0;
}
int checkUnbrokenFour(int a, int b,
                      int c)  //判断在（a，b）处下子，是否形成活四；
{
    int i, j, n = 1, m, P, Q, huosi = 0, chongsi = 0, liangduan1, liangduan2;
    int jifang = 0, duifang = 0;
    float temp;
    P = a;
    Q = b;
    if (c == 1) {
        jifang = 1;
        duifang = 2;
    } else if (c == 2) {
        jifang = 2;
        duifang = 1;
    }
    while (n != 5) {
        m = 0;
        liangduan1 = -1;
        liangduan2 = -1;
        temp = 0.0;
        while (aRecordBoard[a][b] == jifang && temp < 4.0) {
            m++;
            yiwei(n, &a, &b);
            temp += 1.0;
            if (a < 1 || a > 15 || b < 1 || b > 15) {
                liangduan1 = 1;
                break;
            }
            if (aRecordBoard[a][b] == 0) {
                liangduan1 = 0;
                break;
            }
            if (aRecordBoard[a][b] == duifang) {
                liangduan1 = 1;
                break;
            }
        }
        n += 4;
        m -= 1;
        a = P;
        b = Q;
        temp = 0;
        while (aRecordBoard[a][b] == jifang && temp < 4.0) {
            m++;
            yiwei(n, &a, &b);
            temp += 1.0;
            if (a < 1 || a > 15 || b < 1 || b > 15) {
                liangduan2 = 1;
                break;
            }
            if (aRecordBoard[a][b] == 0) {
                liangduan2 = 0;
                break;
            }
            if (aRecordBoard[a][b] == duifang) {
                liangduan2 = 1;
                break;
            }
        }
        if (m == 4 && liangduan1 == 0 && liangduan2 == 0) {
            huosi += 1;
        }
        n -= 3;
        a = P;
        b = Q;
    }
    return huosi;
}
int checkBrokenFour(int a, int b, int c)  //判断在（a，b）处下子，是否形成冲四；
{
    int i, j, n = 1, m, P, Q, huosi = 0, chongsi = 0, liangduan1, liangduan2,
              kong;
    int jifang = 0, duifang = 0;
    int K[SIZE], L[SIZE];
    float temp;
    P = a;
    Q = b;
    if (c == 1) {
        jifang = 1;
        duifang = 2;
    } else if (c == 2) {
        jifang = 2;
        duifang = 1;
    }
    while (n != 5) {
        for (i = 0, j = 0; i < SIZE, j < SIZE; i++, j++) {
            K[i] = 0;
            L[j] = 0;
        }
        m = 0;
        liangduan1 = -1;
        liangduan2 = -1;
        temp = 0.0;
        kong = 0;
        while (
            aRecordBoard[a][b] == jifang &&
            temp <
                4.0) {  // temp用来记录向每个方向已经判断了多少步，出现0.6是用来讨论出现空位置的情况；
            m++;
            yiwei(n, &a, &b);
            temp += 1.0;
            if (a < 1 || a > 15 || b < 1 || b > 15) {
                liangduan1 = 1;
                break;
            }
            if (aRecordBoard[a][b] == 0) {
                temp += 0.6;
                K[m] = a;
                L[m] = b;
                yiwei(n, &a, &b);
                if (aRecordBoard[a][b] == jifang) {
                    kong += 1;
                    continue;
                }
                liangduan1 = 0;
            }
            if (aRecordBoard[a][b] == duifang) {
                liangduan1 = 1;
                break;
            }
        }
        n += 4;
        m -= 1;
        a = P;
        b = Q;
        temp = 0;
        while (aRecordBoard[a][b] == jifang && temp < 4.0) {
            m++;
            yiwei(n, &a, &b);
            temp += 1.0;
            if (a < 1 || a > 15 || b < 1 || b > 15) {
                liangduan2 = 1;
                break;
            }
            if (aRecordBoard[a][b] == 0) {
                temp += 0.6;
                K[m] = a;
                L[m] = b;
                yiwei(n, &a, &b);
                if (aRecordBoard[a][b] == jifang) {
                    kong += 1;
                    continue;
                }
                liangduan2 = 0;
            }
            if (aRecordBoard[a][b] == duifang) {
                liangduan2 = 1;
                break;
            }
        }
        if (m == 4 &&
            ((liangduan1 == 1 && liangduan2 == 0) ||
             (liangduan1 == 0 && liangduan2 == 1)) &&
            kong < 2) {
            chongsi += 1;
        }
        n -= 3;
        a = P;
        b = Q;
    }
    return chongsi;
}
int checkUnbrokenThree(int a, int b,
                       int c)  //判断在（a，b）处下子，是否形成活三；
{
    int n = 1, m, P, Q, huosan = 0, liangduan1, liangduan2, temp, kong;
    int jifang = 0, duifang = 0, chenghuosi;
    P = a;
    Q = b;
    if (c == 1) {
        jifang = 1;
        duifang = 2;
    } else if (c == 2) {
        jifang = 2;
        duifang = 1;
    }
    while (n != 5) {
        m = 0;
        liangduan1 = -1;
        liangduan2 = -1;
        temp = 0;
        kong = 0;
        chenghuosi = 0;
        while (aRecordBoard[a][b] == jifang && temp <= 3) {
            m++;
            yiwei(n, &a, &b);
            temp += 1;
            if (a < 1 || a > 15 || b < 1 || b > 15) {
                liangduan1 = 1;
                break;
            }
            if (aRecordBoard[a][b] == 0) {
                aRecordBoard[a][b] = jifang;
                if (checkUnbrokenFour(a, b, jifang) == 1) {
                    chenghuosi += 1;
                }
                aRecordBoard[a][b] = 0;
                yiwei(n, &a, &b);
                temp += 1;
                if (aRecordBoard[a][b] == jifang) {
                    kong += 1;
                    continue;
                }
                liangduan1 = 0;
                break;
            }
        }
        n += 4;
        m -= 1;
        a = P;
        b = Q;
        temp = 0;
        while (aRecordBoard[a][b] == jifang && temp <= 3) {
            m++;
            yiwei(n, &a, &b);
            temp += 1;
            if (a < 1 || a > 15 || b < 1 || b > 15) {
                liangduan2 = 1;
                break;
            }
            if (aRecordBoard[a][b] == 0) {
                aRecordBoard[a][b] = jifang;
                if (checkUnbrokenFour(a, b, jifang) == 1) {
                    chenghuosi += 1;
                }
                aRecordBoard[a][b] = 0;
                yiwei(n, &a, &b);
                temp += 1;
                if (aRecordBoard[a][b] == jifang) {
                    kong += 1;
                    continue;
                }
                liangduan2 = 0;
                break;
            }
        }
        if (m == 3 && liangduan1 == 0 && liangduan2 == 0 && kong < 2 &&
            chenghuosi >= 1) {
            huosan += 1;
        }
        n -= 3;
        a = P;
        b = Q;
    }
    return huosan;
}
int checkUnbrokenTwo(int a, int b, int c)  //判断是否形成活二；
{
    int n = 1, m, P, Q, l, liangduan1, liangduan2,
        temp;  // l是用来记录连续的子数；
    int jifang = -1, duifang = -1;
    P = a;
    Q = b;
    if (c == 1) {
        jifang = 1;
        duifang = 2;
    } else if (c == 2) {
        jifang = 2;
        duifang = 1;
    }
    while (n != 5) {
        m = 0;
        l = 0;
        liangduan1 = -1;
        liangduan2 = -1;
        temp = 0;
        while (aRecordBoard[a][b] == jifang && temp < 2) {
            m++;
            temp += 1;
            yiwei(n, &a, &b);
            if (a < 1 || a > 15 || b < 1 || b > 15) {
                liangduan1 = 1;
                break;
            }
            if (aRecordBoard[a][b] == jifang) {
                yiwei(n, &a, &b);
                temp += 1;
                if (aRecordBoard[a][b] == 0) {
                    l++;
                    break;
                }
            } else if (aRecordBoard[a][b] == 0) {
                yiwei(n, &a, &b);
                temp += 1;
                if (aRecordBoard[a][b] == 0) {
                    l++;
                    liangduan1 = 0;
                    break;
                }
            }
        }
        n += 4;
        m -= 1;
        a = P;
        b = Q;
        temp = 0;
        while (aRecordBoard[a][b] == jifang && temp < 2) {
            m++;
            yiwei(n, &a, &b);
            temp += 1;
            if (a < 1 || a > 15 || b < 1 || b > 15) {
                liangduan2 = 1;
                break;
            }
            if (aRecordBoard[a][b] == 0) {
                yiwei(n, &a, &b);
                temp += 1;
                if (aRecordBoard[a][b] == 0) {
                    l++;
                    liangduan2 = 0;
                }
                if (l == 2 && liangduan2 == 0 && liangduan1 == -1) {
                    return 1;
                }
            } else if (aRecordBoard[a][b] == jifang) {
                yiwei(n, &a, &b);
                temp += 1;
                if (aRecordBoard[a][b] == 0) {
                    l++;
                }
                if (l == 2 && liangduan1 == 0 && liangduan2 == -1) {
                    return 1;
                }
            }
        }
        n -= 3;
        a = P;
        b = Q;
    }
    return 0;
}
void defence(void)  //电脑执白棋，为保守方；
{
    int i, j, m, n, temp1 = 0, temp2 = 0, reset = 0;
    int c1[SIZE + 1][SIZE + 1], c2 = 0, e1[SIZE + 1][SIZE + 1], e2 = 0,
                                d1[SIZE + 1][SIZE + 1], d2 = 0;
    int a1[SIZE + 1][SIZE + 1], a2[SIZE + 1][SIZE + 1], a11[SIZE + 1][SIZE + 1],
        a12[SIZE + 1][SIZE + 1], a111, a112;
    int jizhi_x1 = 1, jizhi_y1 = 1, jizhi_x2 = 1, jizhi_y2 = 1;
    int x_c = 1;
    int y_c = 1;
    for (i = 1; i <= SIZE; i++) {
        for (j = 1; j <= SIZE; j++) {
            c1[i][j] = 0;
            e1[i][j] = 0;
            d1[i][j] = 0;
            a1[i][j] = 0;
            a2[i][j] = 0;
            a11[i][j] = 0;
            a12[i][j] = 0;
        }
    }
    int x_current1 = 0;
    int y_current1 = 0;
    for (x_c = 1; x_c <= SIZE; x_c++) {  //扫描整个棋盘，给没有子的位置评分；
        for (y_c = 1; y_c <= SIZE; y_c++) {
            if (aRecordBoard[x_c][y_c] == 0) {
                a1[x_c][y_c] =
                    defence_score(x_c, y_c, 2);  //计算此处落下己方子的得分；
                a2[x_c][y_c] =
                    attack_score(x_c, y_c, 1);  //计算此处落下对方子的得分；
            } else if (aRecordBoard[x_c][y_c] == 1)
                ;
            else if (aRecordBoard[x_c][y_c] == 2)
                ;
            c1[x_c][y_c] = a1[x_c][y_c] + a2[x_c][y_c];
            if (c1[x_c][y_c] > c2 || (c1[x_c][y_c] == c2 &&
                                      a1[x_c][y_c] == a2[jizhi_x1][jizhi_y1])) {
                c2 = c1[x_c][y_c];
                x_current1 = x_c;
                y_current1 = y_c;
                jizhi_x1 = x_c;
                jizhi_y1 = y_c;  // TODO: current!!!
                if (c1[x_c][y_c] >= 400000 ||
                    c1[x_c][y_c] ==
                        -1) {  //如果此时对方出现活三或比活三更紧急的情况，或者出现禁手，不再向下看对方的落子位置；
                    x_max = &x_current1;
                    y_max = &y_current1;  // max!!!
                    temp1 = 1;
                    temp2 = 1;
                    reset = 0;
                }
                printf("c[%d][%d]=%d c2=%d \n", x_c, y_c, c1[x_c][y_c], c2);
            }
        }
    }
    int x_current2 = 0;
    int y_current2 = 0;
    while (temp1 < 1) {  //向后预测对方的落子位置；
        aRecordBoard[x_current1][y_current1] = 2;
        x_c = 1;
        y_c = 1;
        for (x_c = 1; x_c <= SIZE; x_c++) {
            for (y_c = 1; y_c <= SIZE; y_c++) {
                if (aRecordBoard[x_c][y_c] == 0) {
                    a11[x_c][y_c] = defence_score(x_c, y_c, 1);
                    a12[x_c][y_c] = attack_score(x_c, y_c, 2);
                } else if (aRecordBoard[x_c][y_c] == 1)
                    ;
                else if (aRecordBoard[x_c][y_c] == 2)
                    ;
                if (a11[x_c][y_c] != -1) {
                    d1[x_c][y_c] = a11[x_c][y_c] + a12[x_c][y_c];
                } else if (a11[x_c][y_c] == -1) {
                    d1[x_c][y_c] = 0;
                }
                if (d1[x_c][y_c] > d2 ||
                    (d1[x_c][y_c] == d2 &&
                     a11[x_c][y_c] ==
                         a12[jizhi_x2]
                            [jizhi_y2])) {  //如果两处评分相等，但是攻击的分数大于防守的分数就立刻就选择进攻位下子
                    d2 = d1[x_c][y_c];
                    x_current2 = x_c;
                    y_current2 = y_c;
                    jizhi_x2 = x_c;
                    jizhi_y2 = y_c;
                    printf("d2=%d d1[%d][%d]=%d ", d2, x_c, y_c, d1[x_c][y_c]);
                }
            }
        }
        temp1++;
        reset = 1;
    }
    int x_current3 = 0;
    int y_current3 = 0;
    while (temp2 < 1) {  //预测完以后，在落己方子，e2记录整体总评分；
        aRecordBoard[x_current2][y_current2] = 1;
        x_c = 1;
        y_c = 1;
        for (x_c = 1; x_c <= SIZE; x_c++) {
            for (y_c = 1; y_c <= SIZE; y_c++) {
                a111 = 0;
                a112 = 0;
                if (aRecordBoard[x_c][y_c] == 0) {
                    a111 = defence_score(x_c, y_c, 2);
                    a112 = attack_score(x_c, y_c, 1);
                } else if (aRecordBoard[x_c][y_c] == 1)
                    ;
                else if (aRecordBoard[x_c][y_c] == 2)
                    ;
                e1[x_c][y_c] = a111 + a112;
                if ((0.6 * d1[x_c][y_c] + 0.5 * e1[x_c][y_c] + c1[x_c][y_c]) >
                    e2) {
                    e2 = 0.6 * d1[x_c][y_c] + 0.5 * e1[x_c][y_c] + c1[x_c][y_c];
                    x_current3 = x_c;
                    y_current3 = y_c;
                    x_max = &x_current3;
                    y_max = &y_current3;
                    printf("e[%d][%d]=%d e2=%d\n", x_c, y_c, e1[x_c][y_c], e2);
                }
            }
        }
        temp2++;
        reset = 1;
    }
    if (reset == 1) {
        aRecordBoard[x_current1][y_current1] = 0;
        aRecordBoard[x_current2][y_current2] = 0;
    }
}
void attack(void)  //电脑执黑棋，为进攻方；
{
    int i, j, m, n, reset = 0, temp1 = 0, temp2 = 0;
    int c1[SIZE + 1][SIZE + 1], c2 = 0, e1[SIZE + 1][SIZE + 1], e2 = 0,
                                d1[SIZE + 1][SIZE + 1], d2 = 0;
    int a1[SIZE + 1][SIZE + 1], a2[SIZE + 1][SIZE + 1], a11[SIZE + 1][SIZE + 1],
        a12[SIZE + 1][SIZE + 1], a111, a112;
    int jizhi_x1 = 1, jizhi_y1 = 1, jizhi_x2 = 1, jizhi_y2 = 1;
    x_c = 1;
    y_c = 1;
    for (i = 1; i <= SIZE; i++) {
        for (j = 0; j <= SIZE; j++) {
            c1[i][j] = 0;
            e1[i][j] = 0;
            d1[i][j] = 0;
            a1[i][j] = 0;
            a2[i][j] = 0;
            a11[i][j] = 0;
            a12[i][j] = 0;
        }
    }
    int x_current1 = 0;
    int y_current1 = 0;
    for (x_c = 1; x_c <= SIZE; x_c++) {  //扫描整个棋盘，给没有子的位置评分；
        for (y_c = 1; y_c <= SIZE; y_c++) {
            if (aRecordBoard[x_c][y_c] == 0) {
                a1[x_c][y_c] =
                    defence_score(x_c, y_c, 1);  //计算此处落下己方子的得分；
                a2[x_c][y_c] =
                    attack_score(x_c, y_c, 2);  //计算此处落下对方子的得分；
            } else if (aRecordBoard[x_c][y_c] == 1)
                ;
            else if (aRecordBoard[x_c][y_c] == 2)
                ;
            if (a1[x_c][y_c] != -1) {
                c1[x_c][y_c] = a1[x_c][y_c] + a2[x_c][y_c];
            } else if (a1[x_c][y_c] == -1) {
                c1[x_c][y_c] = 0;
            }
            if (c1[x_c][y_c] > c2) {
                c2 = c1[x_c][y_c];
                x_current1 = x_c;
                y_current1 = y_c;
                jizhi_x1 = x_c;
                jizhi_y1 = y_c;
                if (c1[x_c][y_c] >= 400000 ||
                    c1[x_c][y_c] ==
                        -1) {  //如果此时对方出现活三或比活三更紧急，或者为禁手等情况，不再向下看对方的落子位置；
                    x_max = &x_current1;
                    y_max = &y_current1;
                    temp1 = 1;
                    temp2 = 1;
                    reset = 0;
                }
                printf("c[%d][%d]=%d c2=%d \n", x_c, y_c, c1[x_c][y_c], c2);
            }
        }
    }
    int x_current2 = 0;
    int y_current2 = 0;
    while (temp1 < 1) {  //向后预测对方的落子位置；
        aRecordBoard[x_current1][y_current1] = 1;
        x_c = 1;
        y_c = 1;
        for (x_c = 1; x_c <= SIZE; x_c++) {
            for (y_c = 1; y_c <= SIZE; y_c++) {
                if (aRecordBoard[x_c][y_c] == 0) {
                    a11[x_c][y_c] = defence_score(x_c, y_c, 2);
                    a12[x_c][y_c] = attack_score(x_c, y_c, 1);
                } else if (aRecordBoard[x_c][y_c] == 1)
                    ;
                else if (aRecordBoard[x_c][y_c] == 2)
                    ;
                d1[x_c][y_c] = a11[x_c][y_c] + a12[x_c][y_c];
                if (d1[x_c][y_c] > d2) {
                    d2 = d1[x_c][y_c];
                    x_current2 = x_c;
                    y_current2 = y_c;
                    jizhi_x2 = x_c;
                    jizhi_y2 = y_c;
                    printf("d[%d][%d]=%d d2=%d ", x_c, y_c, d1[x_c][y_c], d2);
                }
            }
        }
        temp1++;
        reset = 1;
    }
    int x_current3 = 0;
    int y_current3 = 0;
    while (temp2 < 1) {  //预测完以后，在落己方子，e2记录整体总评分；
        aRecordBoard[x_current2][y_current2] = 2;
        x_c = 1;
        y_c = 1;
        for (x_c = 1; x_c <= SIZE; x_c++) {
            for (y_c = 1; y_c <= SIZE; y_c++) {
                a111 = 0;
                a112 = 0;
                if (aRecordBoard[x_c][y_c] == 0) {
                    a111 = defence_score(x_c, y_c, 1);
                    a112 = attack_score(x_c, y_c, 2);
                } else if (aRecordBoard[x_c][y_c] == 1)
                    ;
                else if (aRecordBoard[x_c][y_c] == 2)
                    ;
                if (a111 != -1) {
                    e1[x_c][y_c] = a111 + a112;
                } else if (a111 == -1) {
                    e1[x_c][y_c] = 0;
                }
                if ((0.6 * d1[x_c][y_c] + 0.5 * e1[x_c][y_c] + c1[x_c][y_c]) >
                    e2) {
                    e2 = 0.6 * d1[x_c][y_c] + 0.5 * e1[x_c][y_c] + c1[x_c][y_c];
                    x_current3 = x_c;
                    y_current3 = y_c;
                    x_max = &x_current3;
                    y_max = &y_current3;
                    printf("e[%d][%d]=%d e2=%d\n", x_c, y_c, e1[x_c][y_c], e2);
                }
            }
        }
        temp2++;
        reset = 1;
    }
    if (reset == 1) {
        aRecordBoard[x_current1][y_current1] = 0;
        aRecordBoard[x_current2][y_current2] = 0;
    }
}
int defence_score(int a, int b, int c)  //己方子的防守得分；
{
    int dscore = 0;
    aRecordBoard[a][b] = c;
    if (c == 1 && win(a, b, c)) {
        if (changlianjinshou(a, b, c)) {
            dscore = -1;
            aRecordBoard[a][b] = 0;
            return dscore;
        } else {
            dscore = 5000000;  //黑棋赢，且无禁手
            aRecordBoard[a][b] = 0;
            return dscore;
        }
    } else if (c == 2 && win(a, b, c)) {
        dscore = 5000000;  //白棋赢；
        aRecordBoard[a][b] = 0;
        return dscore;
    }
    if (c == 2 && sisijinshou(a, b, c)) {
        dscore = 4000000;  //白棋出现“双活四”
        aRecordBoard[a][b] = 0;
        return dscore;
    } else if (c == 1 && (sisijinshou(a, b, c) || changlianjinshou(a, b, c))) {
        dscore = -1;  //黑棋出现双活四禁手；
        aRecordBoard[a][b] = 0;
        return dscore;
    }
    if (c == 1 &&
        ((checkUnbrokenFour(a, b, c) == 1 || checkBrokenFour(a, b, c) == 1) &&
         checkUnbrokenThree(a, b, c) == 1)) {
        dscore += 600000;  //出现三、四的情况；
    } else if (c == 2 && ((checkUnbrokenFour(a, b, c) == 1 ||
                           checkBrokenFour(a, b, c) == 1) &&
                          checkUnbrokenThree(a, b, c) >= 1)) {
        dscore += 600000;
    }
    if (checkUnbrokenFour(a, b, c) == 1) {
        dscore += 800000;  //出现活四；
        aRecordBoard[a][b] = 0;
        return dscore;
    }
    if (checkBrokenFour(a, b, c) == 1) {
        dscore += 35000;  //出现冲四；
    }
    if (c == 2 && shuanghuosanjinshou(a, b, c)) {
        dscore += 400000;  //白棋出现“双活三”
        aRecordBoard[a][b] = 0;
        return dscore;
    } else if (c == 1 && shuanghuosanjinshou(a, b, c)) {
        dscore = -1;  //黑棋出现双活三禁手；
        aRecordBoard[a][b] = 0;
        return dscore;
    }
    if (checkUnbrokenThree(a, b, c) == 1) {
        dscore += 60000;  //出现活三；
        aRecordBoard[a][b] = 0;
        return dscore;
    }
    if (checkUnbrokenTwo(a, b, c) == 1) {
        dscore += 20000;  //出现活二；
    }
    aRecordBoard[a][b] = 0;
    return dscore;
}
int attack_score(int a, int b,
                 int c)  //用对方子的进攻得分，评分方式与defence_score相同；
{
    int dscore = 0;
    aRecordBoard[a][b] = c;
    if (c == 1 && win(a, b, c)) {
        if (changlianjinshou(a, b, c)) {
            dscore = -1;
            aRecordBoard[a][b] = 0;
            return dscore;
        } else {
            dscore = 5000000;
            aRecordBoard[a][b] = 0;
            return dscore;
        }
    } else if (c == 2 && win(a, b, c)) {
        dscore = 5000000;
        aRecordBoard[a][b] = 0;
        return dscore;
    }
    if (c == 2 && sisijinshou(a, b, c)) {
        dscore = 4000000;
        aRecordBoard[a][b] = 0;
        return dscore;
    } else if (c == 1 && (sisijinshou(a, b, c) || changlianjinshou(a, b, c))) {
        dscore = -1;
        aRecordBoard[a][b] = 0;
        return dscore;
    }
    if (c == 1 &&
        ((checkUnbrokenFour(a, b, c) == 1 || checkBrokenFour(a, b, c) == 1) &&
         checkUnbrokenThree(a, b, c) == 1)) {
        dscore += 600000;
    } else if (c == 2 && ((checkUnbrokenFour(a, b, c) == 1 ||
                           checkBrokenFour(a, b, c) == 1) &&
                          checkUnbrokenThree(a, b, c) >= 1)) {
        dscore += 600000;
    }
    if (checkUnbrokenFour(a, b, c) == 1) {
        dscore += 800000;
        aRecordBoard[a][b] = 0;
        return dscore;
    }
    if (checkBrokenFour(a, b, c) == 1) {
        dscore += 35000;
    }
    if (c == 2 && shuanghuosanjinshou(a, b, c)) {
        dscore += 400000;
        aRecordBoard[a][b] = 0;
        return dscore;
    } else if (c == 1 && shuanghuosanjinshou(a, b, c)) {
        dscore = -1;
        aRecordBoard[a][b] = 0;
        return dscore;
    }
    if (checkUnbrokenThree(a, b, c) == 1) {
        dscore += 60000;
        aRecordBoard[a][b] = 0;
        return dscore;
    }
    if (checkUnbrokenTwo(a, b, c) == 1) {
        dscore += 20000;
    }
    aRecordBoard[a][b] = 0;
    return dscore;
}
