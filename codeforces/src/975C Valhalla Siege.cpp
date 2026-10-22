//
// Created by Psy.C on 2026/10/22.
//
/**
N：数组最大容量。
n：目标个数；q：操作次数。
a[N]：每个目标的血量。
sum[N]：前缀和，sum[i] = a[1]+...+a[i]。
k[N]：每次操作的攻击量。
t：累计总伤害
读入 n、q。
读入 n 个血量 a[i]，同时构建前缀和 sum[i] = sum[i-1] + a[i]（sum[0] = 0）。前缀和单调不减，便于二分。
读入 q 次攻击量存入 k[]
① t += k[i]：把本次攻击量累加到累计伤害 t。
② 特殊情况——全部清空
sum[n] 是所有目标总血量。
若累计伤害 t ≥ 总血量，说明所有目标都被打光了。
此时把累计伤害归零（t=0）‍，并输出 n——代表"清空后所有目标重新出现/全部存活"（题意通常为：一轮扫荡后全部重生）
③ 一般情况——二分求剩余数
upper_bound(sum+1, sum+1+n, t)：在有序前缀和 sum[1..n] 里找第一个 > t 的位置。
减去 sum（得到下标），再 -1：得到"最后一个 ≤ t 的前缀和下标"，即被伤害 t 完全干掉的目标个数。
具体：upper_bound 返回指针指向某元素，-sum 得到其在数组中的下标 pos；pos-1 就是最后一个被完全消灭的目标下标（因为前缀和 ≤ t 的那些目标都被消灭）。
于是 n - (pos-1) = 剩余存活的目标数，即从最后一个被杀目标之后开始还活着的个数。
输出这个差值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 2e5+7;

int n, q;
ll a[N], sum[N], k[N], t;
int main() {
    fast;
    cin >> n >> q;
    rep(i,n) cin >> a[i], sum[i] = sum[i-1] + a[i];
    rep(i,q) cin >> k[i];
    rep(i,q) {
        t += k[i];
        if (t >= sum[n]) t = 0, cout << n << '\n';
        else cout << n-int(upper_bound(sum+1,sum+1+n,t)-sum-1) << '\n';
    }
    return 0;
}