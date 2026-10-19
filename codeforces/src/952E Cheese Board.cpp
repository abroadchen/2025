//
// Created by Psy.C on 2026/10/18.
//
/**
统计两类方块数量：s = soft 个数，h = 另一类个数
找到最小 i 使得：i² ≥ n（棋盘格数足够装全部 n 块）且 ceil(i²/2) ≥ mx（每类方块不能相邻/同色冲突，棋盘按棋盘格黑白着色，一类方块只能放在同色格）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int n, s, h, mx;
string s1, s2;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> s1 >> s2;
        if (s2 == "soft") ++s; else ++h;
    }
    if (s > h) mx = s; else mx = h;
    for (int i = 1; i <= n; ++i) {
        int k = (i*i+1)>>1;
        if (i*i >= n && k >= mx) {//总格数要≥n，且单色容量≥mx
            cout << i << '\n';
            return 0;
        }
    }
    return 0;
}