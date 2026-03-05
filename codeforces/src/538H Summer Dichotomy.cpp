//
// Created by Psy.C on 2026/3/5.
//
/**
l[N], r[N]: 存储每个元素的区间范围
ok函数：检查值x是否在第i个元素的区间[l[i], r[i]]内
e[N]: 邻接表存储图
c[N]: 染色数组（0=未染色，1=颜色1，2=颜色2）
dfs: 二分图染色算法，确保相邻节点颜色不同

t, T: 总和的下界和上界
n: 元素数量
m: 约束数量

对已染色的连通块进行二分图验证
对未染色的节点，先染色为1，然后进行二分图验证
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1e5+1, inf = 1e9+1;

int l[N], r[N];
inline bool ok(const int x, const int i) {
    return l[i] <= x && x <= r[i];
}

vector<int> e[N];
int c[N];
bool dfs(const int x) {
    for (const auto y : e[x]) {
        if (!c[y]) {
            c[y] = 3 - c[x];
            if (!dfs(y)) return false;
        }
        else if (c[x] == c[y])
            return false;
    }
    return true;
}

void rd(int& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

int t, T, n, m;
int main() {
    rd(t), rd(T), rd(n), rd(m);
    int n1 = inf, n2 = -1;
    for (int i = 1; i <= n; ++i)
        rd(l[i]), rd(r[i]), n1 = min(n1, r[i]), n2 = max(n2, l[i]);
    if (n1 + n2 < t) n2 = t - n1;
    if (n1 + n2 > T) n1 = T - n2;
    if (n1 < 0 || n2 < 0) return puts("IMPOSSIBLE"), 0;
    for (int i = 1; i <= n; ++i) {
        bool o1 = ok(n1, i), o2 = ok(n2, i);
        if (!o1 && !o2) return puts("IMPOSSIBLE"), 0;
        if (o1 && !o2) c[i] = 1;
        if (!o1 && o2) c[i] = 2;
    }
    for (int i = 1, x, y; i <= m; ++i)
        rd(x), rd(y), e[x].push_back(y), e[y].push_back(x);
    for (int i = 1; i <= n; ++i)
        if (c[i] && !dfs(i)) return puts("IMPOSSIBLE"), 0;
    for (int i = 1; i <= n; ++i) {
        if (!c[i]) {
            c[i] = 1;
            if (!dfs(i)) return puts("IMPOSSIBLE"), 0;
        }
    }
    string ans;
    for (int i = 1; i <= n; ++i) ans += c[i] + '0';
    puts("POSSIBLE");
    cout << n1 << ' ' << n2 << '\n';
    cout << ans << '\n';
    return 0;
}