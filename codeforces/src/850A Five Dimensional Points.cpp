//
// Created by Psy.C on 2026/9/29.
//
/**
在 5 维欧氏空间中，可以证明好点的个数至多只有 11 个（这是一个几何结论：从一点出发两两夹角都 ≥ 90°，即都是非锐角，在 d 维空间中这样的"蚂蚁/方向"至多约 2d 个，对 d=5 至多 11）。所以当 n > 11 时必然没有好点，直接输出 0。
这个剪枝让最坏情况下的 O(n³) 扫描变成 O(11³)，非常快

对每个点 i，枚举两两不同的 j, k，计算两个向量的点积
这是向量 (P_i−P_j) 与 (P_i−P_k) 的点积。

若 t > 0 → 夹角为锐角 → 点 i 是坏点（bad），flag=true，跳出。
若对所有 j, k 都 t ≤ 0（非锐角）‍ → 点 i 是好点（good），加入 pos[]。
先输出好点个数 cnt，再逐个输出好点的下标（按输入顺序），每个一行。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e3+5;
struct node { int a[5]; } p[N];
int pos[N];
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i)
        for (int& j : p[i].a) cin >> j;
    if (n > 11) return cout << "0\n", 0;
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        bool flag = false;
        for (int j = 1; j <= n; ++j) {
            if (i == j) continue;
            for (int k = j+1; k <= n; ++k) {
                if (i == k) continue;
                int t = 0;
                for (int h = 0; h < 5; ++h)
                    t += (p[i].a[h]-p[j].a[h])*(p[i].a[h]-p[k].a[h]);
                if (t > 0) { flag = true; break; }
            }
            if (flag) break;
        }
        if (!flag) pos[++cnt] = i;
    }
    cout << cnt << '\n';
    for (int i = 1; i <= cnt; ++i) cout << pos[i] << '\n';
    return 0;
}