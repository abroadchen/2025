//
// Created by Psy.C on 2026/2/15.
//
/**
索引 j | 区间长度 | 区间范围        | 含义
-------|---------|----------------|------------------
  0    |   2⁰=1  |  [i, i]        | 单个元素 [arr[i]]
  1    |   2¹=2  |  [i, i+1]      | 2个元素 [arr[i], arr[i+1]]
  2    |   2²=4  |  [i, i+3]      | 4个元素 [arr[i], ..., arr[i+3]]
  3    |   2³=8  |  [i, i+7]      | 8个元素 [arr[i], ..., arr[i+7]]

预处理：O(n log n)
单次查询：理论上O(1)，但当前实现为O(log n)
总体：O(n log n + q log n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100009
using namespace std;

inline int gcd(const int x, const int y) {
    return y == 0 ? x : gcd(y, x % y);
}

int n, st[N][20];
inline void init() {// [i, i+2^j-1] 区间
    for (int i = n - 1; i > 0; --i)
        for (int j = 1; i + (1<<j) <= n; ++j)
            st[i][j] = gcd(gcd(st[i][j], st[i][j-1]), st[i+(1<<(j-1))][j-1]);
}

inline int get(const int l, const int r) {
    int res = st[l][0];
    for (int k = 0; l + (1<<k) <= r; ++k)
        res = gcd(gcd(res, st[l][k]), st[r-(1<<k)+1][k]);
    return res;
}

map<int, int> pos;//值 -> 索引映射
vector<int> f[N];//位置列表
int main() {
    fast;
    cin >> n;
    for (int i = 1, cnt = 0; i <= n; ++i) {
        cin >> st[i][0];
        if (!pos.contains(st[i][0])) cnt++, pos[st[i][0]] = cnt;
        f[pos[st[i][0]]].push_back(i);
    }
    init();
    int t; cin >> t;
    for (int i = 1, l, r; i <= t; ++i) {
        cin >> l >> r;
        int key = get(l, r);
        const int k = pos[key],
        d = ranges::upper_bound(f[k], r) - ranges::lower_bound(f[k], l);//区间内出现次数
        cout << r - l - d + 1 << '\n';
    }
    return 0;
}