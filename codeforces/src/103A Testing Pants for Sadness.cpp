//
// Created by Psy.C on 2025/11/12.
//
//对于第i个数字m（从0开始计数），它对结果的贡献是(m-1)*(i+1)+1
#include <iostream>
using namespace std;

typedef long long ll;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    ll n, t(0); cin>>n;
    for (ll i = 0, m; i < n; ++i) {
        cin>>m;
        t += (m - 1) * (i + 1) + 1;
    }
    cout << t << '\n';
    return 0;
}