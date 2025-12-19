//
// Created by Psy.C on 2025/12/18.
//
/*
*c1：用于统计字符'x'的个数，初始化为0
c2：用于统计字符'y'的个数，初始化为0
cnt：用于存储需要补充的字符数量
 *
*使用循环变量i从0到字符串长度-1
如果第i个字符是'x'，则c1加1
否则（即字符是'y'），c2加1
 *
*如果'x'的数量大于'y'的数量：
计算差值：cnt = c1 - c2
输出cnt个'x'字符来补足
否则（'y'的数量大于等于'x'的数量）：
计算差值：cnt = c2 - c1
输出cnt个'y'字符来补足
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    string s; cin>>s;
    const ll x = static_cast<ll>(s.size());
    int c1 = 0, c2 = 0, cnt;
    for (ll i = 0; i < x; ++i) {
        if (s[i] == 'x') c1++; else c2++;
    }
    if (c1 > c2) {
        cnt = c1 - c2;
        for (ll i = 0; i < cnt; ++i) cout << "x";
    } else {
        cnt = c2 - c1;
        for (ll i = 0; i < cnt; ++i) cout << "y";
    }
    return 0;
}