//
// Created by Psy.C on 2026/9/18.
//
/**
每条"物品"有三个属性：p（价格/编号）、a（第一种颜色）、b（第二种颜色）。
s[1..3]：三个 set<int>，分别表示颜色 1、2、3 对应的物品集合（set 自动升序、去重）
读入 n 件商品的价格和两种颜色。
每件商品同时属于两种颜色：既加入 s[a] 又加入 s[b]。这样某个颜色可能包含多件商品，价格升序存在 set 里
依次进行 m 次购买请求，每次指定颜色 k：
若 s[k] 为空（该颜色没有可用商品），输出 -1。
否则取该颜色 set 的最小价格 ans 出售，输出它。
关键：卖出后要从所有 3 个颜色的 set 中都删掉这件商品（因为它可能同时属于其他颜色，卖了就不能再出现在别的颜色队列里）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+1;
struct node {int p, a, b; } c[N];
set<int> s[4];
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> c[i].p;
    for (int i = 1; i <= n; ++i) cin >> c[i].a;
    for (int i = 1; i <= n; ++i) cin >> c[i].b;
    for (int i = 1; i <= n; ++i) {
        s[c[i].a].insert(c[i].p);
        s[c[i].b].insert(c[i].p);
    }
    int m; cin >> m;
    for (int j = 1, k; j <= m; ++j) {
        cin >> k;
        if (s[k].empty()) cout << "-1 ";
        else {
            int ans = *(s[k].begin());
            cout << ans << ' ';
            for (int i = 1; i <= 3; ++i) s[i].erase(ans);
        }
    }
    return 0;
}