//
// Created by Psy.C on 2026/11/25.
//

/**
真正学会的起点..
a[1..2n]：每个元素是 {t, p}，其中 p 是原始下标。
cmp：按 t 升序排序；t 相同则按 p 升序。即按时间排序
初始化答案：前两个最早的事件对应的原始位置 a[1].p 与 a[2].p，从起点（位置 1）出发到达这两个位置
每两个成一组（时间相邻的两个点 a[i].p、a[i+1].p 是新出现的两个点）。
k1,k2 是上一组两个点各自的位置，m1,m2 是这一组两个点的位置。
两种"配对顺序"：
abs(m1-k2)+abs(m2-k1)：机器1去 m1（从上组另一个 k2 出发）、机器2去 m2（从 k1 出发）——交叉。
abs(m1-k1)+abs(m2-k2)：机器1从 k1→m1、机器2从 k2→m2——不交叉。
取 min，累加到 ans，表示这两台机器本轮移动的最小总距离
输出最小总路程
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e5+10;

struct node { int t, p; } a[N<<1];
bool cmp(node x, node y) {
    if (x.t != y.t) return x.t < y.t;
    return x.p < y.p;
}
inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n;
ll ans;
int main() {
    fast;
    n = rd();
    for (int i = 1; i <= n*2; i++) { a[i].t = rd(); a[i].p = i; }
    sort(a+1, a+1+n*2, cmp);
    ans = a[1].p + a[2].p - 2;
    for (int i = 3; i <= n*2; i += 2) {
        int m1 = a[i].p, m2 = a[i+1].p, k1 = a[i-1].p, k2 = a[i-2].p;
        ans += min(abs(m1-k2)+abs(m2-k1),abs(m1-k1)+abs(m2-k2));
    }
    cout << ans;
    return 0;
}