//
// Created by Psy.C on 2026/10/17.
//
/**
n：当前要缩小的数；k：除法除数；a：做一次「−1」的代价；b：做一次「÷k」的代价；ans：总代价
while (n != 1)：只要还没降到 1 就继续。
ans += n%k*a; n = n-n%k;：先处理"余数部分"——先用逐次减 1 把 n 变成 k 的整数倍（需要减 n%k 次，每次代价 a，故加 (n%k)*a）。这一步总是划算，因为除法除法必须先让 n 是 k 的倍数才能整除，把非倍数部分用 −1 清掉。
然后比较两种继续方式的代价：
b > (n-n/k)*a：即「这一次除法代价 b」>「若不用除法、改为一路 −1 从 n 减到 n/k 的代价」。
(n-n/k) 是「从 n 一路减 1 到 n/k」需要的减次数。若这个更便宜（a*n 便宜），说明除法不划算，直接 ans += (n-1)*a（一路减 1 到 1）然后 break 退出循环。
否则（除法划算）：n = n/k; ans += b; 执行一次除法，代价 b。
最后输出 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, k, a, b, ans;
int main() {
    fast;
    cin >> n >> k >> a >> b;
    while (n != 1) {
        ans += n%k*a; n = n-n%k;
        if (b > (n-n/k)*a) {
            ans += (n-1)*a;
            break;
        } else {
            n = n/k;
            ans += b;
        }
    }
    cout << ans;
    return 0;
}