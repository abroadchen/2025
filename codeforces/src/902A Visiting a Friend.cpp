//
// Created by Psy.C on 2026/10/10.
//
/**
a[0]=true：位置 0 一开始被"覆盖"（可到达/已填充）
读入两个数 n、m。通常含义是：给定 n 个区间，要求检查区间 [0, m] 是否都被覆盖（能覆盖整个范围）
循环读入 n 个区间 [x, y]。
关键逻辑：只有当 a[x] 为 true 时（即区间左端点 x 已可达/已覆盖），才把 [x, y] 全部标记为 true。
这意味着：这个区间必须"接得上"已覆盖的起点才会生效。这是一种贪心/连锁传递的思维——只有从已经被触达的位置才能继续往后铺开区间
扫描 [0, m]，只要有任意一个位置仍为 false（未被覆盖），就输出 NO 结束。
若 [0, m] 全部为 true，输出 YES
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+10;
bool a[N];
int main() {
    fast;
    int n, m; cin >> n >> m;
    a[0] = true;
    for (int i = 1, x, y; i <= n; ++i) {
        cin >> x >> y;
        if (a[x]) { for (int j = x; j <= y; ++j) a[j] = true; }
    }
    for (int i = 0; i <= m; ++i)
        if (a[i] == false) { cout << "NO\n"; return 0; }
    cout << "YES";
    return 0;
}