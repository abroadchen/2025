//
// Created by Psy.C on 2026/2/28.
//
/**
N = 101：数组最大长度，M = 1e5：循环周期上限
n, m：两个数组的长度
q：每次输入的数量
a[N], b[N]：布尔数组，标记位置是否被占用
x：临时输入变量

读入n和m
读入q，然后读入q个位置，标记到数组a中
再读入q，然后读入q个位置，标记到数组b中
遍历前M个位置
i%n：在数组a中的位置（循环索引）
i%m：在数组b中的位置（循环索引）
如果a[i%n]或b[i%m]有一个为1，则将两者都设为1
这表示在循环过程中，如果任一数组的某位置被标记，则两个数组对应位置都要被标记
f1：标记数组a中是否有0（未被标记的位置）
f2：标记数组b中是否有0（未被标记的位置）
遍历数组a和b，检查是否所有位置都被标记为1

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 101, M = 1e5;
int n, m, q, a[N], b[N], x;
int main() {
    fast;
    cin >> n >> m;
    cin >> q;
    for (int i = 0; i < q; ++i) { cin >> x; a[x] = 1; }
    cin >> q;
    for (int i = 0; i < q; ++i) { cin >> x; b[x] = 1; }
    for (int i = 0; i < M; ++i)
        if (a[i%n] || b[i%m]) a[i%n] = b[i%m] = 1;
    int f1 = 0, f2 = 0;
    for (int i = 0; i < n; ++i)
        if (a[i] == 0) f1 = 1;
    for (int i = 0; i < m; ++i)
        if (b[i] == 0) f2 = 1;
    if (f1 == 0 && f2 == 0) cout << "Yes\n"; else cout << "No\n";
    return 0;
}