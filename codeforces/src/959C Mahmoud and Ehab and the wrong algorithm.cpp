//
// Created by Psy.C on 2026/10/20.
//
/**
顶点数太少（≤5）时，直接输出 -1，表示满足条件的构造不存在。
说明这个构造题的合法条件是 n ≥ 6 才可能有解
固定输出三条边：1-2、1-3、1-4（点 1 与 2、3、4 相连）。
对 i = 5..n：输出边 2-i（点 2 与 5..n 相连）。
边数统计：

固定 3 条（1-2, 1-3, 1-4）
再加上 n-4 条（2-5, 2-6, ..., 2-n）
第一组总边数 = 3 + (n-4) = n-1 条
这组边本身就是一个以 1、2 为"双中心"的树：1 连 2、3、4；2 连 1、5..n
对 i = 2..n：输出边 1-i（点 1 与 2..n 都相连）。
共 n-1 条边，形成以点 1 为中心的星形图（star graph）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;


int main() {
    fast;
    int n; cin >> n;
    if (n <= 5) cout << "-1\n";
    else {
        cout << "1 2\n";
        cout << "1 3\n";
        cout << "1 4\n";
        for (int i = 5; i <= n; ++i) cout << "2 " << i << '\n';
    }
    for (int i = 2; i <= n; ++i) cout << "1 " << i << '\n';
    return 0;
}