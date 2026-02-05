//
// Created by Psy.C on 2026/2/5.
//

#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100010
using namespace std;


int main() {
    fast;
    ll a[5];
    cin >> a[1] >> a[2] >> a[3] >> a[4];
    char str[N]; cin >> str;
    const ll len = static_cast<ll>(strlen(str)); ll s = 0;
    for (int i = 0; i < len; ++i) {
        const int t = str[i] - '0';//字符转换为对应的数字
        s += a[t];//获取该数字对应的权重值
    }
    cout << s << '\n';
    return 0;
}