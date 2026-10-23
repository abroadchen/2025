//
// Created by Psy.C on 2026/10/22.
//
/**
dfs(x, sum, m)：
x 表示当前处理到的左侧位置（第 x 个元素，已用操作 m 调整过）。
sum 是已累积的操作数。
m 是 a[x] 采用的操作（0/1/2 → +0/-1/+1）。
剪枝：若 sum 已 ≥ mn 则没必要继续。
终止：x == n 表示处理完，更新 mn。
循环枚举 a[x+1] 的操作 i：
当 x==1 时，用 (a[1]+op[m])-(a[2]+op[i]) 计算出公差 pre（由前两个元素决定）。
否则要求 (a[x]+op[m]) - (a[x+1]+op[i]) == pre，即相邻差保持同一公差，否则跳过这种 i。
若 i==0（不改 a[x+1]）则操作数不变，否则 +1。
注意：m 是"上一层对 a[x] 的操作"，i 是"本层对 a[x+1] 的操作"，两者再与上一层确定的 pre 校验

n ≤ 2 直接输出 0（任何两个数都能构成等差数列）。
从三个初始调用开始：dfs(1,0,0)（a[1] 不改）、dfs(1,1,1)（a[1]−1）、dfs(1,1,2)（a[1]+1），枚举第一个元素的所有调整。
若 mn 仍为 INT_MAX（没有任何方案成功），输出 -1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e5+5;

int mn = INT_MAX, n, pre, a[N], op[3] = {0,-1,1};
void dfs(int x, int sum, int m) {
    if (sum >= mn) return;
    if (x == n) { mn = min(mn, sum); return; }
    for (int i = 0; i < 3; i++) {
        if (x == 1) pre = (a[1]+op[m])-(a[2]+op[i]);
        else {
            if ((a[x]+op[m])-(a[x+1]+op[i]) != pre) continue;
        }
        if (i == 0) dfs(x+1, sum, i);
        else dfs(x+1, sum+1, i);
    }
}

int main() {
    fast;
    cin >> n;
    if (n <= 2) { cout << 0; return 0; }//任意两数可直接成等差
    for (int i = 1; i <= n; i++) cin >> a[i];
    dfs(1, 0, 0); dfs(1, 1, 1); dfs(1, 1, 2);
    if (mn == INT_MAX) { cout << -1; return 0; }
    cout << mn;
    return 0;
}