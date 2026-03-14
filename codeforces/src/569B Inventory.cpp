//
// Created by Psy.C on 2026/3/13.
//
/**
a[N]：原输入序列
b[N]：标记数组，记录1~n中哪些数字已被使用
c[N]：标记数组，记录哪些位置需要替换

如果a[i]未被使用且在1~n范围内，标记b[a[i]]=1
否则标记c[i]=1（表示该位置需要替换）
从i=1开始遍历，x初始化为1
对于需要替换的位置（c[i]==1）：
找到最小的未使用数字x（通过while循环跳过已使用的数字）
将a[i]替换为x
标记b[x]=1表示x已被使用

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;
int n, a[N], b[N], c[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (b[a[i]] == 0 && a[i] <= n) b[a[i]] = 1;
        else c[i] = 1;
    }
    for (int i = 1, x = 1; i <= n; ++i) {
        if (c[i] == 1) {
            while (b[x]) x++;
            a[i] = x; b[x] = 1;
        }
    }
    for (int i = 1; i < n; ++i) cout << a[i] << ' ';
    cout << a[n] << '\n';
    return 0;
}