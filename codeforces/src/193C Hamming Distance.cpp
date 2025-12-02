//
// Created by Psy.C on 2025/12/2.
//
/*
*检查t[1]到t[6]是否都非负：
使用all_of算法和lambda表达式
如果都非负，则ok为true
*如果当前解不合法且t[7]在合理范围内：
尝试调整t[7]的值来寻找可行解
 *
 *
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;

int a, b, c, d, e, f, t[8], mn;

int main() {
    fast;
    cin >> a >> b >> c >> d >> e >> f;
    if (((e+f-a-b)&1) || ((d+f-a-c)&1) || ((b+c-f)&1) ||
        ((d+e-b-c)&1) || ((a+c-e)&1) || ((a+b-d)&1)) {
        cout << -1; return 0;
    }
    t[1] = (e+f-a-b)>>1; t[2] = (d+f-a-c)>>1;
    t[3] = (b+c-f)>>1; t[4] = (d+e-b-c)>>1;
    t[5] = (a+c-e)>>1; t[6] = (a+b-d)>>1;
    bool ok = all_of(t + 1, t + 7, [](const int& x) {
        return x >= 0;
    });
    for (; !ok && t[7] <= a && t[7] <= b && t[7] <= c; ++t[7]) {
        t[1]++; t[2]++; t[3]--; t[4]++; t[5]--; t[6]--;
        ok |= all_of(t + 1, t + 7, [](const int& x) {
            return x >= 0;
        });//重新检查是否所有值都非负
    }
    if (!ok) { cout << -1; return 0; }
    cout << (mn = (d + e + f) / 2 + t[7]) << '\n';
    rep(i,mn) cout << 'a';
    cout << '\n';
    rep(i,t[1]+t[2]+t[3]) cout << 'a';
    rep(i,t[4]+t[5]+t[6]+t[7]) cout << 'b';
    cout << '\n';
    rep(i,t[1]) cout << 'a'; rep(i,t[2]+t[3]) cout << 'b';
    rep(i,t[4]+t[5]) cout << 'a'; rep(i,t[6]+t[7]) cout << 'b';
    cout << '\n';
    rep(i,t[1]) cout << 'b'; rep(i,t[2]) cout << 'a';
    rep(i,t[3]) cout << 'b'; rep(i,t[4]) cout << 'a';
    rep(i,t[5]) cout << 'b'; rep(i,t[6]) cout << 'a';
    rep(i,t[7]) cout << 'b';
    return 0;
}