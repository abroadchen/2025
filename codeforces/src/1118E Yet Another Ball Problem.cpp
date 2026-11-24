//
// Created by Psy.C on 2026/11/24.
//

/**
真正学会的起点..
最多能画的合法边数 = k(k−1)/2（每一对只 1 条方向）。
代码用 k*(k-1) < n（等价于 k(k-1)/2 < n，因 n 为整数）判断：若想要的边数
n 超过最大可用数 → NO
num = n 计数还需多少边。
双重循环枚举每一对 (i,j)（i<j），对每一对输出两条互补方向：i j 和 j i。
每输出一条 num--，减到 0 就 return 0（正好构造满 n 条）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for (int i=j; i<k; i++)
#define ll long long
using namespace std;

ll n, k;
int main() {
    fast;
    cin >> n >> k;
    if (k*(k-1) < n) cout << "NO\n";
    else {
        int num = n;
        cout << "yes\n";
        rep(i,1,k) rep(j,i+1,k+1) {
            cout << i << ' ' << j << '\n';
            --num;
            if (num == 0) return 0;
            cout << j << ' ' << i << '\n';
            --num;
            if (num == 0) return 0;
        }
    }
    return 0;
}