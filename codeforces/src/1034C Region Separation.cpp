//
// Created by Psy.C on 2026/11/4.
//

/**
真正学会的起点..
a[i]：节点 i 的点权。
f[i]：节点 i 的父节点编号（树结构）。
sum[i]：子树 i 的所有点权之和
这个 check 会临时改坏全局 sum[]（先拷贝 a 再累加），所以它依赖调用方在当前旧 sum[] 没被污染的情况下、且后续还会重新自底向上算 sum（见 main 中每次调用 check 前的逻辑）。它的作用是判断：能否把整棵树切成若干块，使每块点权和都等于 m。

做法：从叶子（n）向根（1）遍历，若某子树和恰好等于 m，就"切掉"这一块（清零，不再向上传）；否则把和累加到父节点；只要任何父节点和超过 m 就直接失败
mx：最大点权。
读入点权 a[i]。
读入 f[i]（i 从 2..n，节点 1 是根）。
从 n 到 1（自底向上）把每个节点的点权累加进自己的子树和，并传给父节点——得到每个节点的子树点权和
枚举每个节点 i，若其子树和 sum[i] >= mx（不小于最大点权，才能容纳单个节点）‍且能整除根的总和 sum[1]（sum[1] % sum[i] == 0），就把该节点和作为候选值存入 d[]。
d 是候选"每块点权和"集合（必须能整除总和，等分才可能）。
排序 + unique 去重
从大的候选值往小遍历。
若 check(n, d[i]) 通过（整棵树能切成若干块，每块和 = d[i]），则：
dp[i] = 1（自身作为一种合法方案）。
对于后面比它大的 d[j]，若 d[j] 是 d[i] 的倍数，则 dp[i] += dp[j]（继承更大块的合法切割方案）。
注意 dp 数组初始未清零，此处 dp[i] = 1 是赋值而非累加，dp[j] 需是之前算过的值。
累加到 ans
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e6+5, M = 26887;

int a[N], f[N];
ll sum[N];
inline ll check(int n, ll m) {
    for (int i = 0; i <= n; i++) sum[i] = a[i];
    for (int i = n; i >= 1; i--) {
        if (sum[i] == m) sum[i] = 0;
        sum[f[i]] += sum[i];
        if (sum[f[i]] > m) return false;
    }
    return true;
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

ll d[N];
int dp[M];
int main() {
    fast;
    int n = rd(), mx = 0, cnt = 0, ans = 0;
    for (int i = 1; i <= n; i++) {
        a[i] = rd();
        mx = max(mx, a[i]);
    }
    for (int i = 2; i <= n; i++) f[i] = rd();
    for (int i = n; i >= 1; i--) {
        sum[i] += a[i];
        sum[f[i]] += sum[i];
    }
    for (int i = 1; i <= n; i++)
        if (sum[i] >= mx && sum[1]%sum[i] == 0) d[++cnt] = sum[i];
    sort(d+1, d+cnt+1);
    cnt = unique(d+1,d+cnt+1) - d - 1;
    for (int i = cnt; i >= 1; i--)
        if (check(n, d[i])) {
            dp[i] = 1;
            for (int j = i+1; j < cnt; j++)
                if (d[j]%d[i] == 0) dp[i] += dp[j];
            ans += dp[i];
        }
    cout << ans;
    return 0;
}