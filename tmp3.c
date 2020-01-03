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
