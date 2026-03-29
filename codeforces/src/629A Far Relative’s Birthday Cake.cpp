//
// Created by Psy.C on 2026/3/29.
//
/**
逐个读取每个位置的字符并存储到s[i][j]
外层循环遍历每一行：从第1行到第n行
初始化计数器：将c重置为0，用于统计当前行的'C'数量
内层循环遍历当前行的所有列：检查每个位置是否为'C'
统计'C'的数量：如果当前位置是'C'，计数器c加1
计算组合数并累加：c*(c-1)/2是数学公式，表示从c个'C'中任选2个的组合数，即同列的两个'C'能形成多少对

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 105;
int n, c, t;
char s[N][N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> s[i][j];
    for (int i = 1; i <= n; ++i) {
        c = 0;
        for (int j = 1; j <= n; ++j)
            if (s[i][j] == 'C') c++;
        t += c*(c-1)/2;
    }
    for (int j = 1; j <= n; ++j) {
        c = 0;
        for (int i = 1; i <= n; ++i)
            if (s[i][j] == 'C') c++;
        t += c*(c-1)/2;
    }
    cout << t;
    return 0;
}