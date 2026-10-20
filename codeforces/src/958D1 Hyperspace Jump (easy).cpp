//
// Created by Psy.C on 2026/10/20.
//
/**
把 (a+b) 作为分子、c 作为分母，约分到最简（分子分母同除以 gcd）。
map<pair<int,int>, int> cnt 以约分后的 (x, y) 为键，统计出现次数。
t[i] 保存每个位置对应的分数对，方便最后按输入顺序输出
对每个元素 i，输出它所在分数对 t[i] 在整体中出现的次数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;

constexpr int N = 2e5+5;

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

map<ii, int> cnt;
ii t[N];
int main() {
    fast;
    int m = rd();
    for (int i = 1, a, b, c; i <= m; ++i) {
        a = rd(), b = rd(), c = rd();
        int x = a + b, y = c, g = gcd(x, y); x/=g, y/=g;
        cnt[{x, y}]++;
        t[i] = {x, y};
    }
    for (int i = 1; i <= m; ++i) cout << cnt[t[i]] << ' ';
    return 0;
}