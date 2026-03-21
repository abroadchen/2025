//
// Created by Psy.C on 2026/3/21.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 15005, M = 1e3+5, K = 120005, mod = 1e9+7, base = 1e7+19;

vector<int> V[K];///线段树节点rt中包含的物品集合
void modify(int rt, int l, int r, int L, int R, int k) {//在时间区间[L,R]内添加物品k
    if (L > R) return;
    if (l >= L && R >= r) { V[rt].push_back(k); return; }
    int mid = (l + r) >> 1;
    if (mid >= L) modify(rt<<1, l, mid, L, R, k);
    if (mid < R) modify(rt<<1|1, mid+1, r, L, R, k);
}

int k, w[N], v[N];
void dfs(int rt, int l, int r, int f[]) {
    for (int i = 0; i < V[rt].size(); ++i) {//处理当前节点的所有物品
        int x = V[rt][i];
        for (int j = k; j >= w[x]; --j)//01背包转移
            f[j] = max(f[j], f[j-w[x]] + v[x]);
    }
    if (l == r) {
        if (l == 1) return;//跳过初始时刻
        int b = 1, sum = 0;
        ///通过哈希编码将整个状态数组压缩为一个整数
        for (int i = 1; i <= k; ++i) {
            sum = (sum + f[i]*b) % mod;//哈希编码
            b = b * base % mod;
        }
        cout << sum << '\n';
        return;
    }
    int mid = (l + r) >> 1, g[k+1];
    for (int i = 0; i <= k; ++i) g[i] = f[i];//复制状态
    dfs(rt<<1, l, mid, f); dfs(rt<<1|1, mid+1, r, g);
}

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

int n, cnt, st, l[N], r[N], q, p[M];
signed main() {
    fast;
    rd(n); rd(k); cnt = n; st = 1;
    for (int i = 1; i <= n; ++i) {
        rd(v[i]); rd(w[i]); l[i] = st;//读取初始物品
    }
    rd(q);
    while (q--) {
        int op, x, y; rd(op);
        if (op == 1) {//添加物品
            rd(x); rd(y);
            v[++cnt] = x; w[cnt] = y;
            l[cnt] = st+1;
        } else if (op == 2) {//删除物品
            rd(x); r[x] = st;
        } else st++;//时间推进
    }
    for (int i = 1; i <= cnt; ++i) {
        if (r[i]) modify(1, 1, st, l[i], r[i], i);//有时限的物品
        else modify(1, 1, st, l[i], st, i);//永久存在的物品
    }
    dfs(1, 1, st, p);
    return 0;
}