//
// Created by Psy.C on 2026/11/23.
//

/**
真正学会的起点..
s1[i] = 前 i步横坐标（左右）累计位移；s2[i] = 纵坐标（上下）累计
起点 (x,y) + 周期总位移 × 完整周期数 + 余数部分的前缀位移 → 得到 id 时刻的强制位移位置。
剩余 id 步自由走，覆盖曼哈顿距离 ≤id 即可到达。
abs 曼哈顿距离 ≤id 返回 true
t 越大越容易到达（单调性成立），所以二分求最小可行时间。
初始 r = 1<<60（很大上限）。
输出最小 ans（若始终不可达则为 -1 的初值，视具体 –1 处理）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

constexpr int N = 1e6+10;

int x, y, s1[N], s2[N], n, xx, yy;
bool check(int id) {
    int sx = x + s1[n]*(id/n) + s1[id%n];
    int sy = y + s2[n]*(id/n) + s2[id%n];
    return abs(sx-xx) + abs(sy-yy) <= id;
}

string s;
int l, r, ans;
signed main() {
    fast;
    cin >> x >> y >> xx >> yy >> n >> s; s = ' ' + s;
    for (int i = 1; i <= n; i++) {
        s1[i] = s1[i-1], s2[i] = s2[i-1];
        if (s[i] == 'U') s2[i]++;
        else if (s[i] == 'D') s2[i]--;
        else if (s[i] == 'L') s1[i]--;
        else if (s[i] == 'R') s1[i]++;
    }
    l = 0, r = 1ll<<60, ans = -1;
    while (l <= r) {
        int mid = (l+r)>>1;
        if (check(mid)) ans = mid, r = mid-1;
        else l = mid+1;
    }
    cout << ans;
    return 0;
}