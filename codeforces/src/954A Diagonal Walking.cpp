//
// Created by Psy.C on 2026/10/19.
//
/**
遍历每个位置，若当前位置与下一字符构成 "UR" 或 "RU"，则这对可以合并：cnt+1，并把这两个位置标记为空格（防止被重复计数）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e6+10;

char a[N];
int main() {
    fast;
    int n, cnt = 0; scanf("%d", &n); scanf("%s", a+1);
    for (int i = 1; i <= n; ++i) {
        if ((a[i]=='U'&&a[i+1]=='R')||(a[i]=='R'&&a[i+1]=='U')) {
            cnt++;
            a[i] = ' '; a[i+1] = ' ';
        }
    }
    cout << n - cnt;
    return 0;
}