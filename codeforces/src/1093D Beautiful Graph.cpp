//
// Created by Psy.C on 2026/11/18.
//

/**
真正学会的起点..
l[i]：点 i 的颜色，取值 1 或 2（0 表示未染色）。
v[i]：邻接表。
ans：方案数（连乘）
通过交换一个空队列来快速清空全局 q
ans 初始为 1，p 标记是否仍为二分图
清空每点颜色标记与邻接表
存双向边。
对每个连通分量从任一点 BFS，交替染 1/2。
若某条边两端被染相同颜色 → 矛盾 → 不是二分图，输出 0 并终止。
统计该分量内颜色 1 的点数 v1、颜色 2 的点数 v2
孤立点（v1+v2==1，只有一个点）：它没有约束，可以有 3 种染色选择（此题语境下是在三种颜色中任取），乘 3。
非孤立连通分量：拥有 v1 个"颜色1"点、v2 个"颜色2"点。由于哪些点归哪类是确定的，但哪一类对应"颜色1/颜色2"的整体标号有两种对调可能；不过这里计算的是 2^v1 + 2^v2，它表示：若把该分量看成一个整体，它对外能贡献的方案数 —— 取自"从颜色1类或颜色2类中各自任选子集"的计数，反映每个分量提供给全局的独立选择维度
始终是二分图则输出方案数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 3e5+10, mod = 998244353;

ll ksm(int x, int num) {
    if (num == 1) return x;
    ll sum = ksm(x,num/2)%mod;
    if (num%2) return sum*sum%mod*x%mod;
    return sum*sum%mod;
}

queue<int> q;
void clear() { queue<int> o; swap(q,o); }

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int T, n, m, l[N];
ll ans;
vector<int> v[N];
int main() {
    fast;
    T = rd();
    while (T--) {
        n = rd(), m = rd(), ans = 1; bool p = 1;
        rep(i,n) l[i] = 0;
        rep(i,n) vector<int>().swap(v[i]);
        rep(i,m) {
            int a1 = rd(), a2 = rd();
            v[a1].push_back(a2); v[a2].push_back(a1);
        }
        for (int i = 1; i <= n && p; i++) {
            if (l[i]) continue;//已染过，跳过
            int v1 = 1, v2 = 0; clear(), q.push(i), l[i] = 1;//从一个未染色点开始 BFS
            while (p && !q.empty()) {
                int x = q.front(); q.pop();
                if (!v[x].empty()) {
                    for (int j = 0; j < v[x].size(); j++) {
                        if (l[x] == l[v[x][j]]) {//相邻同色 → 非二分图
                            p = 0, cout << "0\n";
                            break;
                        }
                        if (!l[v[x][j]]) {
                            l[v[x][j]] = l[x] == 1 ? 2 : 1, q.push(v[x][j]);//染相反色
                            if (l[x] == 1) v2++; else v1++;
                        }
                    }
                }
            }
            if (v1 + v2 == 1) ans = ans * 3 % mod;
            else ans = ans * (ksm(2, v1) + ksm(2, v2) % mod) % mod;
        }
        if (p) cout << ans << '\n';
    }
    return 0;
}