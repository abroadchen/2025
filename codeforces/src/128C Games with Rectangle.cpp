//
// Created by Psy.C on 2025/11/18.
//

#include <vector>
#include <iostream>
using namespace std;

typedef long long ll;
const int mod = 1e9 + 7;

ll calc(int n, int k) {
    if (k == 0) return 1;//不进行任何操作
    vector<ll> a(n + 1, 0); a[n] = 1;
    for (int i = 1; i <= k; ++i) {
        vector<ll> t1(n + 2, 0), t2(n + 2, 0);
        for (int j = n; j >= 1; --j) {
            t1[j] = (t1[j + 1] + a[j]) % mod;//后缀和
            t2[j] = (t2[j + 1] + (ll)(j - 1) * a[j]) % mod;//加权后缀和
        }
        vector<ll> cur(n + 1, 0);
        for (int j = 1; j <= n - 2; ++j) {
            if (j + 2 <= n) {
                cur[j] = (t2[j + 2] - j * t1[j + 2]) % mod;
                if (cur[j] < 0) cur[j] += mod;
            }
        }
        a = cur;//将当前结果cur赋值给a，作为下一轮迭代的输入
    }
    ll tot = 0;
    for (int i = 1; i <= n; ++i) tot = (tot + a[i]) % mod;//向量a中所有元素的和
    return tot;
}


int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, m, k; cin >> n >> m >> k;
    ll x = calc(n, k), y = calc(m, k);
    cout << x * y % mod << '\n';
    return 0;
}