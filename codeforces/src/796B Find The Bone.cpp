//
// Created by Psy.C on 2026/9/17.
//
/**
h[i]：标记位置 i 是否有陷阱（1=有）。
p[i]：标记位置 i 是否当前有球（1=有
读入：n 位置总数，m 陷阱数，k 交换次数。
全组清零。
读入 m 个陷阱位置 x，并 h[x]=1 标记

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+5;
int h[N], p[N];
int main() {
    fast;
    int n, m, k; cin >> n >> m >> k;
    memset(h, 0, sizeof(h));
    memset(p, 0, sizeof(p));
    for (int i = 0, x; i < m; ++i) {
        cin >> x; h[x] = 1;
    }
    p[1] = 1;//球在位置 1
    //记录球当前位置
    int ans = 1, flag = 0;//是否已命中陷阱（游戏结束）
    if (h[1]) flag = 1;//若位置1本身就是陷阱，直接结束
    for (int i = 0, x, y; i < k; ++i) {
        cin >> x >> y;
        if (flag) continue;//已结束，跳过后续交换
        if (p[x]) { p[x] = 0; p[y] = 1; ans = y; }//球在x → 换到y
        else if (p[y]) { p[y] = 0; p[x] = 1; ans = x; }//球在y → 换到x
        if (h[ans]) flag = 1;//球到了陷阱位置 → 结束
    }
    cout << ans << '\n';
    return 0;
}