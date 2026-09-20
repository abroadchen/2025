//
// Created by Psy.C on 2026/9/20.
//
/**
ans 是全局字符数组，用来存放构造出的字符串
fill_n 把 ans 的前 n 个位置全部填成 'a'。
即初始时 ans = "aaaa...a"（n 个 a
从 i = 2 开始扫描到 n-1。
判断 ans[i] 与 ans[i-2]（相隔 2 的两个位置）是否相同。
若相同，就把 ans[i] 改成 'b'，破坏"间隔 2 相同"这个条件
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5;
char ans[N];
int main() {
    fast;
    int n;
    while (cin >> n) {
        fill_n(ans, n, 'a');
        for (int i = 2; i < n; ++i)
            if (ans[i] == ans[i-2])
                ans[i] = 'b';
        cout << ans << '\n';
    }
    return 0;
}