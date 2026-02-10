//
// Created by Psy.C on 2026/2/10.
//
/**
将连续区间[0,1]分成m份
每份长度为1/m
用离散求和近似连续积分

时间复杂度：O(m)，需要计算m次幂运算
空间复杂度：O(1)，只使用常数空间
 */
#include <iostream>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

double m, n, ans;

int main() {
    fast;
    cin >> m >> n;
    for (int i = 1; i <= m; ++i) {
        ans += i*(pow(i/m, n) - pow((i-1)/m, n));//区间[(i-1)/m, i/m]的概率密度
    }
    printf("%.12lf\n", ans);
    return 0;
}