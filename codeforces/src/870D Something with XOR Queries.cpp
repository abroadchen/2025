//
// Created by Psy.C on 2026/10/5.
//
/**
p0[i] = p_0 XOR b_i：固定行 0 问各列
b0[i] = p_i XOR b_0：固定列 0 问各行
假设
p
0
=
x
p
0
​
 =x，则由询问列0 的 b0 推出整个 p：
p
i
=
x
⊕
b
0
[
0
]
⊕
b
0
[
i
]
p
i
​
 =x⊕b
0
​
 [0]⊕b
0
​
 [i]
再假设
b
0
b
0
​
 ，由 p0 推出整个 b
valid 校验 p 与 b 都是排列（0 到 n-1 各出现一次且不越界）
最后用
p
[
b
[
i
]
]
=
i
p[b[i]]=i 这一交叉校验验证排列间的自洽性（若真满足
p
b
j
⊕
⋯
p
b
j
​

​
 ⊕⋯ 关系）
检查元素都不超过 n-1，且 0..n-1 每个恰好出现一次 → 是合法排列
第一段统计满足条件的 p 的个数 cnt
第二段实际输出一套可行的 p（输出第一组满足 ok 的

先输出 ! 行 + 可行方案个数
再输出一整套 p 排列，用空格分隔
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 5005;

int vis[N], n;
bool valid(const int *a) {
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < n; ++i) {
        if (a[i] >= n) return false;
        vis[a[i]]++;
    }
    for (int i = 0; i < n; ++i)
        if (vis[i] != 1) return false;
    return true;
}

int p[N], b0[N], b[N], p0[N];
bool ok(int x) {
    p[0] = x;
    for (int i = 1; i < n; ++i) p[i] = p[0]^b0[0]^b0[i];
    if (!valid(p)) return false;
    b[0] = p[0]^p0[0];
    for (int i = 1; i < n; ++i) b[i] = b[0]^p0[0]^p0[i];
    if (!valid(b)) return false;
    for (int i = 0; i < n; ++i)
        if (p[b[i]] != i) return false;
    return true;
}

int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cout << "? 0 " << i << endl;
        cin >> p0[i];
    }
    for (int i = 0; i < n; ++i) {
        cout << "? " << i << " 0" << endl;
        cin >> b0[i];
    }
    int cnt = 0;
    for (int i = 0; i < n; ++i)
        if (ok(i)) cnt++;
    cout << "!\n" << cnt << '\n';
    for (int i = 0; i < n; ++i) {
        if (ok(i)) {
            p[0] = i;
            cout << p[0] << ' ';
            for (int j = 1; j < n; ++j)
                cout << (p[0]^b0[0]^b0[j]) << ' ';
            break;
        }
    }
    cout << endl;
    return 0;
}