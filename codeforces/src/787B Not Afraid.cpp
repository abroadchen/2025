//
// Created by Psy.C on 2026/9/14.
//
/**
v 存储当前子句的所有文字。check() 的功能：

遍历每个负数文字 v[i]（即 -x，表示变量 x 取假）。
若同时存在它的正对应 -v[i]（即 x，表示变量 x 取真），则返回 true。
含义：一个子句（析取式）中，如果同时出现了 x 和 -x，那么这个子句必然为真（无论 x 取什么值，总有一个文字为真）。这样的子句叫 「恒真子句」，不会对整体可满足性造成任何限制

读取 n（变量个数）和 m（子句个数）。
对每个子句，读入 k 个文字存入 v。
若某一子句不是恒真子句（check() 返回 false），则 flag = false。
全部子句都是恒真子句 → 输出 NO；否则输出 YES
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

vector<int> v;
bool check() {
    int len = v.size();
    for (int i = 0; i < len; ++i) {
        if (v[i] < 0) {
            if (ranges::find(v, -v[i]) != v.end())
                return true;
        }
    }
    return false;
}

bool flag = true;
int main() {
    fast;
    int n, m; cin >> n >> m;
    for (int i = 0, k; i < m; ++i) {
        v.clear(); cin >> k;
        for (int j = 0, x; j < k; ++j) {
            cin >> x; v.push_back(x);
        }
        if (!check()) flag = false;
    }
    if (flag) cout << "NO\n"; else cout << "YES\n";
    return 0;
}