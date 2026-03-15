//
// Created by Psy.C on 2026/3/15.
//
/**
n：数组长度
k：幂次
x：乘数
ex[i]：存储x的i次幂
a[N]：输入数组
pre[i]：a[1]到a[i]的OR前缀
suf[i]：a[i]到a[n]的OR后缀
ex[0] = 1：x的0次幂
预计算x的各次幂：ex[i] = x^i
pre[i]：a[1] | a[2] | ... | a[i]
OR运算具有单调性：随着元素增多，结果不会减小
suf[i]：a[i] | a[i+1] | ... | a[n]
pre[i-1]：位置i之前所有元素的OR
suf[i+1]：位置i之后所有元素的OR
a[i]*ex[k]：位置i的元素乘以x^k

OR运算的性质：A | B ≥ max(A, B)
一旦某一位在OR运算中变为1，就永远保持1
所以最大化策略是将最大的数放在乘方后
pre[i-1] | suf[i+1]：固定不变的部分
a[i] * x^k：我们可以控制的部分
选择能使最终OR结果最大的i

时间复杂度
预处理：O(n + k)
枚举：O(n)
总体：O(n + k)
空间复杂度
O(n)：存储数组
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define mxx(x,y) x=max((x),(y))
using namespace std;
constexpr int N = 2e5+5;

int n, k, x;
ll ex[20], a[N], pre[N], suf[N];
int main() {
    fast;
    cin >> n >> k >> x; ex[0] = 1;
    for (int i = 1; i <= k; ++i) ex[i] = ex[i-1] * x;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) pre[i] = pre[i-1]|a[i];
    for (int i = n; i >= 1; --i) suf[i] = suf[i+1]|a[i];
    ll ans = 0;
    for (int i = 1; i <= n; ++i) mxx(ans, pre[i-1]|suf[i+1]|a[i]*ex[k]);
    cout << ans;
    return 0;
}