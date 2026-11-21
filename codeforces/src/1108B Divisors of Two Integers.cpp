//
// Created by Psy.C on 2026/11/21.
//

/**
真正学会的起点..
a[M]：存 n 个数（M 用作大小，见下面的注意点）。
num[N]：布尔标记，记录某个具体数值是否已出现过（num[val]）。
vis[M]：布尔标记，记录下标 i 是否被"选中为因子担保"
对每个 i：
若 a[n] % a[i] == 0（即 a[i] 是最大值 a[n] 的因子）：
若该数值 a[i] 还没被 num 标记过（num[a[i]] == 0）：
vis[i] = 1：标记这个下标 i 为"已被选为因子"。
num[a[i]] = 1：标记该数值出现过。
作用：保证所有能整除最大值的因子中，每个数值只选一个代表（重复值只标记第一个即最小的那个下标）
先输出 a[n]（最大值）后跟一个空格。
从后往前（i = n → 1）找第一个 !vis[i]（即没被标记为因子代表的数）输出并结束。
因为从后往前，找到的第一个未标记者数值最大。
若全部被标记（不可能，除非 n=1 之类边界），则无输出直接返回
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=(n); ++i)
using namespace std;

constexpr int N = 1e5+5, M = 130;
inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int a[M];
bool num[N], vis[M];
int main() {
    fast;
    int n = rd();
    rep(i,n) a[i] = rd();
    sort(a+1,a+n+1);
    rep(i,n) if (a[n]%a[i] == 0) { if (num[a[i]] == 0) { vis[i] = 1; num[a[i]] = 1; } }
    cout << a[n] << ' ';
    for (int i = n; i >= 1; i--) if (!vis[i]) { cout << a[i] << '\n'; return 0; }
    return 0;
}