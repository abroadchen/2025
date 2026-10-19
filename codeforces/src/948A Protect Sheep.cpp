//
// Created by Psy.C on 2026/10/18.
//
/**
读入 r×c 网格到 a
对每个方格 'W'（狼），检查它四个方向是否紧邻 'S'（羊）：
上：a[i-1][j]
下：a[i+1][j]
左：a[i][j-1]
右：a[i][j+1]
若任意一个相邻格是 'S'，则 flg=0（说明存在狼直接挨着羊的情况，且这个相邻关系无法通过放栅栏消除，因为中间没有空地可放 D）。
为什么"狼羊直接相邻就 No"？
因为只有 . 能被改成 D。如果 W 和 S 本来就直接相邻（中间没有 .），那无论你在别处怎么放栅栏，这个相邻都去不掉 → 输出 No
若 flg==1（没有任何狼紧邻羊）：
输出 Yes；
把所有空地 . 全部改成 D（栅栏）。因为把全部空地都封上栅栏，必定能彻底隔开任何狼和羊（此时狼周围如果有空位就都是 D，不会出现 W-S 相邻）；由于已确认原本没有 W-S 直接相邻，全放 D 后依然没有 → 一定合法。
否则输出 No
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
using namespace std;

constexpr int N = 500;

int r, c;
char a[N][N+1];
int main() {
    fast;
    cin >> r >> c;
    rep(i,r) cin >> a[i];
    int flg = 1;
    for (int i = 0; i < r && flg; i++)
        for (int j = 0; j < c && flg; j++)
            if (a[i][j] == 'W') {
                if (i && a[i-1][j] == 'S') flg = 0;
                else if (i < r-1 && a[i+1][j] == 'S') flg = 0;
                else if (j && a[i][j-1] == 'S') flg = 0;
                else if (j < c-1 && a[i][j+1] == 'S') flg = 0;
            }
    if (flg) {
        cout << "Yes\n";
        rep(i,r) {
            rep(j,c) {
                if (a[i][j] == '.') cout << 'D';
                else cout << a[i][j];
            }
            cout << '\n';
        }
    } else cout << "No\n";
    return 0;
}