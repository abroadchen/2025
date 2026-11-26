//
// Created by Psy.C on 2026/11/26.
//

/**
真正学会的起点..
存储化简后斜率
读入 n 对 (a[i], b[i])
零向量 (0,0)：单独计 ans++（不与任何其他向量共线方向）。
g = gcd(|a|,|b|) 除以 g 得到最简比 (x,y)。
符号归一化：目的是让互为相反方向但同一直线的向量能映射到同一个 key。
例如 (1,1) 和 (-1,-1) 同一直线，统一成 (1,1)。
规则：若 x<0 且 y<0（第三象限）→ 翻成正；若 y>0 且 x<0（第二象限）→ 翻成 (正,负)。
这样方向相反但斜率相同的向量 key 一致。
y==0（水平向量）：统一 x=1，变成 (1,0)，避免出现 (-x,0)/(x,0) 歧义。
统计到 map 中
找出 count 最多的斜率组 mx。
输出 ans + mx：零向量数 + 同一斜率最多的向量数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
#define ii pair<int,int>
using namespace std;

constexpr int N = 2e5+5;
int n, a[N], b[N], ans, mx;
map<ii,int> mp;
int main() {
    fast;
    cin >> n;
    rep(i,n) cin >> a[i];
    rep(i,n) cin >> b[i];
    rep(i,n) {
        if (a[i] == 0) { if (b[i] == 0) ans++; }
        else {
            int g = __gcd(abs(a[i]), abs(b[i]));
            int x = a[i]/g, y = b[i]/g;
            if (x < 0 && y < 0) x = -x, y = -y;
            if (y > 0 && x < 0) x = -x, y = -y;
            if (y == 0) x = 1;
            mp[{x,y}]++;
        }
    }
    for (auto val : mp | views::values)
        mx = max(mx, val);
    cout << ans + mx << '\n';
    return 0;
}