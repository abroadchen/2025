//
// Created by Psy.C on 2026/11/19.
//

/**
真正学会的起点..
典型的枚举 + 回溯：对每个位置分叉成两种符号。
当处理完全部 n 个（x = n+1）时，进入 check() 判断当前符号组合是否满足条件
计算带符号总和：v[i] 为 0 表示取正号，为 1 表示取负号。
若 sum % 360 == 0，置标志 f=1（已找到可行解）
读入，开始 DFS，最后按 f 标志输出结果

dfs(x+1)（第一次）：此时 v[x] 还是 0（默认/或上一轮恢复的 0），相当于这一路让 a[x] 取 + 号。
v[x] = 1：把 v[x] 的值改成 1，表示 a[x] 取负号。
dfs(x+1)（第二次）：以 v[x]=1 的状态去递归，相当于这一路让 a[x] 取 − 号。
v[x] = 0：递归回来后把 v[x] 还原成 0，保证同级其他分支（也就是上一层循环回来时）不受污染——这就是"回溯"
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= n; ++i)
using namespace std;

constexpr int N = 20, M = 360;

int n, a[N], v[N], f;
inline void check() {
    int sum = 0;
    rep(i,n) sum += a[i]*(v[i]?-1:1);
    if (sum%M == 0) f = 1;
}
inline void dfs(int x) {
    if (x == n+1) return check();
    dfs(x+1); v[x] = 1;//a[x] 取 "+"（v[x]=0）
    dfs(x+1); v[x] = 0;//a[x] 取 "−"（v[x]=1）
}


int main() {
    fast;
    cin >> n;
    rep(i,n) cin >> a[i];
    dfs(1);
    cout << (f?"YES":"NO");
    return 0;
}