//
// Created by Psy.C on 2026/11/19.
//

/**
真正学会的起点..
head[i] 是点 i 的邻接链表头，add 向前插入边 (a→b)，标准链式前向星
对每个点，s[n] 若为 -1（即"未知"）则递归计算它所有孩子的子树最小值，取 min 存入。
注意： 这只在 s[n] == -1 时才用子树 min 覆盖；而已知值的节点（可以为 inf）会直接返回。所以逻辑是"叶子或未赋值节点 = 其所有子树的最小值"，已赋值节点则保留原值。
inf = 1e9+5 被当作"极大/未定义"哨兵
遍历每个点 i，取 t1 = dfs(i)（i 子树最小值，若是叶子为 inf）、t2 = dfs(fa[i])（父子树最小值）。
对每条边累加 t1 - t2。
若某个节点的子树最小值小于其父的最小值（t2 > t1），则标记非法（flg），输出 -1
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

constexpr int N = 2e5+5, inf = 1e9+5;

int cnt, u[N], v[N], head[N], nxt[N];
inline void add(int a, int b) {
    u[++cnt] = a, v[cnt] = b, nxt[cnt] = head[a], head[a] = cnt;
}

ll s[N];
inline ll dfs(int n) {
    if (s[n] != -1) return s[n];
    int k = head[n];
    ll mn = inf;
    while (k != -1) mn = min(dfs(v[k]), mn), k = nxt[k];
    s[n] = mn;
    return s[n];
}

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}
template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}

int n, fa[N];
ll ans;
int main() {
    read(n);
    for (int i = 0; i <= n+1; i++) head[i] = -1;
    for (int i = 2, t; i <= n; ++i) read(t), add(t,i), fa[i] = t;
    for (int i = 1; i <= n; ++i) read(s[i]);
    int flg = 0;
    for (int i = 1, t1, t2; i <= n; ++i) {
        t1 = dfs(i), t2 = dfs(fa[i]);
        if (t1 != inf) {
            if (t2 > t1) flg = 1;
            ans += t1 - t2;
        }
    }
    if (flg) cout << "-1\n"; else write(ans);
    return 0;
}