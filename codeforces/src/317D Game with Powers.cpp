//
// Created by Psy.C on 2026/1/6.
//

#include <iostream>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100000
using namespace std;

int sg[] = {
    0,1,2,1,4,3,2,1,5,6,2,1,8,7,5,9,8,7,3,4,7,4,2,1,10,9,3,6,11,12
};

int main() {
    fast;
    int n; cin >> n;
    if (n == 1) return cout << "Vasya\n", 0;
    const int m = static_cast<int>(sqrt(n + 0.5));//+0.5是为了避免浮点精度问题
    int res = sg[1], dif = 0; bool vis[N] = {};
    for (int i = 2; i <= m; ++i) if (!vis[i]) {
        int k = 0;
        for (ll j = i; j <= n; j *= i) {//计算i的幂次，从i^1到不超过n的最高次幂
            if (j <= m) vis[j] = true; else dif++;
            k++;//计算i的幂次个数
        }
        res ^= sg[k];//使用异或运算合并所有子问题的SG值
    }
    if ((n-m-dif)&1) res ^= sg[1];
    cout << (res ? "Vasya" : "Petya") << '\n';
    return 0;
}