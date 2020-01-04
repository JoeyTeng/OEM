for (x_c = 1; x_c <= SIZE; x_c++) {  //扫描整个棋盘，给没有子的位置评分；
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
        if ((0.6 * d1[x_c][y_c] + 0.5 * e1[x_c][y_c] + c1[x_c][y_c]) > e2) {
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
