//
// Created by Psy.C on 2026/11/25.
//

/**
真正学会的起点..
a[i],b[i]：每组的两列数据（比如键和值）。
h[M]：展开后每个位置的半径/跨度 h。
cnt：展开后的总位置数。
L[i], R[i]：位置 i 能覆盖的左右边界。
q[M]：单调栈/队列，存位置下标。
v[i]：位置 i 的权值；dp[i]：前 i 个的最优解
读 n 组，每组先有长度 len，然后 len 个 a、len 个 b
把给定 id 组、乘以系数 mul 后，展平成一个长序列：
h[cnt] = a 值（作为覆盖半径）
v[cnt] = b 值 × mul（作为权值）
维护一个单调栈，栈内 i-h[i] 递增（左端点递增）。
弹掉那些"被当前 i 完全包含"的栈顶（i-h[i] 更靠左），使栈保持覆盖效率。
然后 L[i]：若栈空或当前左端点更靠左，取自身左界 max(1, i-h[i]+1)；否则继承栈顶的 L[q[r]]（因为被更大范围覆盖）。
结果：每个 i 得到它能覆盖的最左边界 L[i]
反向做同样的单调栈，这次管右端点 i+h[i] 递增。
得到每个 i 能覆盖的最右边界 R[i]。
至此 [L[i], R[i]] 是位置 i 的完整覆盖区间
求 dp[i]：
先假设选 i 覆盖到当前位置：贡献 = dp[L[i]-1] + v[i]。
单调栈维护候选，弹掉 R < i 的（覆盖不到当前位置的）。
用栈顶候选试试：dp[q[r]-1] + v[q[r]]，取 min。
若当前 i 比栈顶更优（dp[i-1]+v[i] 更小），入栈作为更优候选。
最终 dp[cnt] 即覆盖全部 cnt 个位置的最小代价
*/
#include <bits/stdc++.h>
#define rep(i,n) for (int i=1; i<=(n); ++i)
#define ll long long
using namespace std;

constexpr int N = 3e5+5, M = 1e7+5;
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
int n, m, k, h[M], cnt, l = 1, r, q[M], L[M], R[M];
vector<ll> a[N], b[N];
ll v[M], dp[M];
int main() {
    read(n); read(m);
    for (int i = 1, len, x; i <= n; i++) {
        read(len);
        rep(j,len) read(x), a[i].push_back(x);
        rep(j,len) read(x), b[i].push_back(x);
    }
    read(k);
    for (int i = 1, id, mul; i <= k; i++) {
        read(id), read(mul);
        const int len = a[id].size();
        for (int j = 0; j < len; j++) h[++cnt] = a[id][j], v[cnt] = b[id][j]*mul;
    }
    rep(i,cnt) {
        while (l <= r && i-h[i] <= q[r]-h[q[r]]) r--;
        if (l > r || i-h[i] >= q[r]) L[i] = max(1,i-h[i]+1);
        else L[i] = L[q[r]];
        q[++r] = i;
    }
    l = 1, r = 0;
    for (int i = cnt; i >= 1; i--) {
        while (l <= r && i+h[i] >= q[r]+h[q[r]]) r--;
        if (l > r || i+h[i] <= q[r]) R[i] = min(cnt,i+h[i]-1);
        else R[i] = R[q[r]];
        q[++r] = i;
    }
    r = 0;
    rep(i,cnt) {
        dp[i] = dp[L[i]-1] + v[i];
        while (r && R[q[r]] < i) r--;
        if (r) dp[i] = min(dp[i],dp[q[r]-1]+v[q[r]]);
        if (!r || dp[i-1]+v[i] < dp[q[r]-1]+v[q[r]]) q[++r] = i;
    }
    write(dp[cnt]);
    return 0;
}