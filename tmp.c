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
