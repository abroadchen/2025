//
// Created by Psy.C on 2026/11/27.
//

/**
真正学会的起点..
因为 n 只能通过乘 2、乘 3 得到 m，所以 m 必须是 n 的倍数（因子中没有别的数）。若 m % n != 0，直接不可能，输出 -1
n 已经等于 m，不需要任何操作，答案 0
k = m/n：倍数。
cnt：记录操作次数（每次 ×2 或 ×3 记为一次）
while (k%2==0)	只要 k 能被 2 整除，就除以 2 一次，操作次数 +1
while (k%3==0)	同理，对因子 3
这一步是在把倍数 k 里所有的 2 和 3 因子剥出来。剥出一个 2 因子就等于做了一次"×2"，剥出一个 3 因子就等于做了一次"×3"。cnt 累加的就是需要的总操作数
if (k != 1)	剥完 2 和 3 后 k 仍不是 1，说明倍数里含有其他质因子（比如 5、7…），无法只用 ×2、×3 达到 → 输出 -1
else	k==1，说明倍数完全由 2 和 3 组成，输出操作次数 cnt
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int n, m;
int main() {
    fast;
    while(cin>>n>>m) {
        if (m%n != 0) cout << "-1\n";
        else if (n == m) cout << "0\n";
        else {
            int k = m/n, cnt = 0;
            while (k%2 == 0) { cnt++; k /= 2; }
            while (k%3 == 0) { cnt++; k /= 3; }
            if (k != 1) cout << "-1\n";
            else cout << cnt << '\n';
        }
    }
    return 0;
}