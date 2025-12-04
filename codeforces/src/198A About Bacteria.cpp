//
// Created by Psy.C on 2025/12/3.
//
/*
 *
 *如果当前结果res大于等于目标值t，则记录当前步数i为答案，并跳出循环
 *按照递推公式更新res：res = res * k + b
 *
*从f(0)=1开始，按照递推公式逐步计算f(i)
找到第一个使得f(i)≥t的i值，记为ans
如果f(ans)=t，则答案为n-ans
如果f(ans)>t，则答案为n-ans+1
 *
*n+1 表示一个"不可能达到"的步数
因为循环最多执行 n+1 次（从 0 到 n），所以真实的答案一定在 0 到 n 之间
如果循环结束后 ans 仍然是 n+1，说明在 0 到 n 的范围内没有找到满足条件的解
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    int k, b, n, t; cin >> k >> b >> n >> t;
    ll res = 1; int ans = n + 1;
    for (int i = 0; i <= n; ++i) {
        if (res >= t) { ans = i; break; }
        res = res * k + b;
    }
    if (res == t) cout << n - ans << '\n';
    else cout << n - ans + 1 << '\n';
    return 0;
}