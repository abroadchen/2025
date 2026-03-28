//
// Created by Psy.C on 2026/3/27.
//
/**
p[]: 位置, m: 圆形长度, a[]: 值/权重
n: 计数, q[]: 排序索引, nt[]/lt[]: 圆形链表的下一个/上一个
{步数, 索引} 对

 */
#include <ranges>
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int N = 1e5+5, inf = 1e9;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int p[N], m, a[N];
///元素x到达元素y需要多少次移动
int get(int x, int y) {
    if (x == y) return inf;
    int d = (p[y] - p[x] + m) % m;//x 到 y 的距离（圆形方式）
    if (y < x) d = (d + a[y]) % m;
    if (d <= a[x]) return 1;//可以一步移动
    if (a[x] <= a[y]) return inf;//无法移动
    return (d - a[y] - 1) / (a[x] - a[y]) + 1;//所需步数
}

int n, q[N], nt[N], lt[N];
set<ii> s;
int main() {
    fast;
    n = rd(), m = rd();
    for (int i = 1; i <= n; ++i)
        p[i] = rd()-1, a[i] = rd(), q[i] = i;
    sort(&q[1], &q[n + 1], [](int x, int y) {
        return p[x] < p[y];
    });
    for (int i = 1; i <= n; ++i)
        nt[q[i]] = q[i+1], lt[q[i]] = q[i-1];//建立下一个/前一个链接
    nt[q[n]] = q[1], lt[q[1]] = q[n];//连接两端形成圆形结构
    for (int i = 1; i <= n; ++i)
        s.insert({get(i, nt[i]), i});//插入相邻元素之间的初始距离
    while (true) {
        auto [fst, snd] = *s.begin();
        if (fst == inf) break;//没有更多可移动的了
        int v = snd; s.erase(s.begin());//处理最近的配对
        //从集合中删除受影响的条目
        s.erase({get(nt[v], nt[nt[v]]), nt[v]});
        if (!s.empty())
            s.erase({get(lt[v], v), lt[v]});
        p[v] += fst, p[v] %= m; --a[v];//移动位置并减少值
        nt[v] = nt[nt[v]]; lt[nt[v]] = v;//从链中移除下一个元素
        //将新距离添加回集合
        s.insert({get(lt[v], v), lt[v]});
        s.insert({get(v, nt[v]), v});
    }
    cout << s.size() << '\n';
    for (const auto &val: s | views::values)
        cout << val << ' ';
    cout << '\n';
    return 0;
}