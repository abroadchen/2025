//
// Created by Psy.C on 2026/4/16.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 605;

int a[N][N], m;
int check(int x, int y) {//第x行和第y行之间的曼哈顿距离
    int sum = 0;
    for (int i = 1; i <= m; ++i)//循环遍历每一列
        sum += abs(a[x][i] - a[y][i]);//累加对应位置元素差的绝对值
    return sum;
}

int q, n;
int main() {
    fast;
    cin >> q;
    while (q--) {
        cin >> n >> m;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                cin >> a[i][j];
        //第1行和第n行的距离小于中间两行的距离
        cout << (check(1, n) < check(n/2, n/2+1) ? "YES" : "NO") << '\n';
    }
    return 0;
}