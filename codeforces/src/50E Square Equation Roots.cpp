//
// Created by Psy.C on 2025/10/14.
//
/*
*从结果中减去2 * max(m - b, 0)
如果m >= b，则减去2*(m-b)；否则减去0
这一步是在修正之前的过度计算
 *
*计算c = i² - j² = (i+j)(i-j)
这代表两个平方数的差
*如果c > m，则跳出内层循环
因为j递减，c会增大，后续的c都会大于m
 *
*统计vis数组中true的个数并加到结果中
count函数计算范围内值为true的元素个数
 *
 *
 */
#include <ios>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

void solve() {
    int n, m; cin >> n >> m;
    ll res = 2ll * n * m;
    vector<bool> vis(2*n);
    for (int i = 1; i <= n; ++i) {
        ll b = (ll)i * i;
        res -= 2 * max(m - b, 0ll);
        for (int j = i - 1; j >= 0; --j) {
            ll c = b - (ll)j * j;
            if (c > m) break;
            vis[i + j] = vis[i - j] = true;
            res -= 2;
        }
    }
    res += count(vis.begin(), vis.end(), true);
    cout << res << '\n';
}


int main() {

    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    solve();
    return 0;
}