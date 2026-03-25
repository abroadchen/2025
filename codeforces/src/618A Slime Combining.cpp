//
// Created by Psy.C on 2026/3/25.
//
///O(log n)，需要处理n的每一位
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 205;
int n, ans[N], cnt;
int main() {
    fast;
    cin >> n;
    int x = 0;//位置计数器
    while (n) {
        x++;
        if (n&1) ans[++cnt] = x;//记录当前位位置
        n >>= 1;
    }
    //从后往前输出所有记录的位置（按从高到低的顺序）
    for (int i = cnt; i >= 1; --i)
        cout << ans[i] << ' ';
    return 0;
}