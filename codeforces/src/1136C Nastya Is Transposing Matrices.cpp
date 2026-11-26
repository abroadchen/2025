//
// Created by Psy.C on 2026/11/26.
//

/**
真正学会的起点..
i+j 的范围：i∈[1,n], j∈[1,m]，最小 2，最大 n+m。数组开 M=1005（≥ n+m+1）够用。
x[i+j] 存矩阵 a 中"和为 i+j"的所有元素，y[i+j] 存 b 中对应元素
读入 A、B，然后把每个位置按「下标和 i+j」分桶。所有 i+j 相同的格子放入同一集合
对每个桶 i（即每个下标和）：

排序 a、b 的该桶元素。
长度不同 → NO。
逐位不同 → NO。
全部相同 → 该桶可匹配。
全部桶通过 → YES
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define int long long
using namespace std;

constexpr int N = 505, M = 1005;
inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, m, a[N][N], b[N][N];
vector<int> x[M], y[M];//M 个桶, 按下标和 i+j 分组存元素
signed main() {
    fast;
    n = rd(), m = rd();
    rep(i,n) rep(j,m) a[i][j] = rd();
    rep(i,n) rep(j,m) b[i][j] = rd();
    rep(i,n) rep(j,m) x[i+j].push_back(a[i][j]);
    rep(i,n) rep(j,m) y[i+j].push_back(b[i][j]);
    rep(i,n+m) {
        ranges::sort(x[i]); ranges::sort(y[i]);
        if (x[i].size() != y[i].size()) { cout << "NO"; return 0; }
        for (int j = 0; j < x[i].size(); j++)
            if (x[i][j] != y[i][j]) { cout << "NO"; return 0; }
    }
    cout << "YES";
    return 0;
}