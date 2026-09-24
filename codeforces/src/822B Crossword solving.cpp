//
// Created by Psy.C on 2026/9/23.
//
/**
读入 n, m 和两个字符串。
在开头加哨兵字符 "#"，使下标从 1 开始（1 基索引）
外层循环 i 从 1 到 m-n+1：a 的开头对齐到 b[i] 的所有可能起点。
内层：逐字符比较 a[j] 与 b[k]（k = i, i+1, ...），对不相等计数 cnt。
若 cnt 小于当前最小 mn：
更新 mn，清空 ans，重置 idx。
再次遍历，把所有失配的 a 下标 j 存入 ans
输出最小失配数 mn，换行。
输出失配位置的列表（在 a 中的下标）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e3+5, inf = 1e9;
int n, m, mn(inf), ans[N], idx;
string a, b;
int main() {
    fast;
    cin >> n >> m >> a >> b; a = "#"+a; b = "#"+b;
    for (int i = 1; i <= m-n+1; ++i) {
        int cnt = 0;
        for (int j = 1, k = i; j <= n; ++j, ++k)
            if (a[j] != b[k]) cnt++;
        if (mn > cnt) {
            mn = cnt;
            memset(ans, 0, sizeof ans);
            idx = 0;
            for (int j = 1, k = i; j <= n; ++j, ++k)
                if (a[j] != b[k]) ans[++idx] = j;
        }
    }
    cout << mn << '\n';
    for (int i = 1; i <= idx; ++i) cout << ans[i] << ' ';
    return 0;
}