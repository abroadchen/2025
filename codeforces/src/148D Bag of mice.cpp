//
// Created by Psy.C on 2025/11/22.
//
/*
 *白球数量w和黑球数量b
 *prob[i][j][k] 表示剩i个白球、j个黑球时，当前玩家在状态k下的获胜概率
 *k=0: 当前玩家先手 k=1: 当前玩家后手
 *
 *边界条件：只有白球时，先手玩家必胜
 *
 *计算先手状态的获胜概率：
 *要么直接抽到白球获胜(概率win)
 *要么抽到黑球(概率lose)，轮到对方先手，自己变成后手
 *
 *计算后手状态的获胜概率
 *抽到黑球后，对方会拿走一个球
 *
 *后手获胜概率 = 抽到黑球的概率 ×
 *[对方拿白球的概率 × 新状态下先手获胜概率 +
 *对方拿黑球的概率 × 新状态下先手获胜概率]
 *
 *
 *
 */
#include <cstdio>
using namespace std;

int main() {
    int w, b; scanf("%d %d\n",&w,&b);
    double prob[w+1][b+1][2];

    for (int i = 0; i <= w; ++i) {
        for (int j = 0; j <= b; ++j) {
            for (int k = 0; k <= 1; ++k)
                prob[i][j][k] = 0.;
        }
    }
    for (int i = 1; i <= w; ++i) prob[i][0][0] = 1;
    for (int i = 1; i <= w; ++i) {
        for (int j = 1; j <= b; ++j) {
            double win = 1. * i / (i + j),//抽到白球概率
            lose = 1. - win;//抽到黑球概率
            prob[i][j][0] = win + lose * prob[i][j-1][1];
            double ans1 = j >= 2 ? 1. * i / (i + j - 1) : 1.,//对方拿白球的概率
            ans2 = 1. - ans1;//对方拿黑球的概率
            prob[i][j][1] = lose * (ans1 * prob[i-1][j-1][0]+
                ans2 * (j >= 2 ? prob[i][j-2][0] : 0.));
        }
    }
    printf("%.12lf\n",prob[w][b][0]);
    return 0;
}