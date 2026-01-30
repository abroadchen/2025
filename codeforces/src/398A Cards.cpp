//
// Created by Psy.C on 2026/1/30.
//
/**
 *
* x = b / k：平均分配时每段的基础大小
c = b % k：余数，前c段会多分配1个单位
b个单位平均分配到k组中，每组x个，有c组会多1个

ans：基础得分项
t：惩罚项，表示分配不均匀带来的损失  c组有(x+1)个单位，(k-c)组有x个单位
返回 ans - t：净得分
 *
*v：最优分割数
输出最优得分和对应的构造方案
 *
 *x（每组基本数量）和c（额外分配的组数）
 *
 *
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

ll b, a;
ll get(const ll k) {//分k段时的目标函数值
    const ll x = b / k, c = b % k,
    ans = (a - k + 2) * (a - k + 2) + (k - 2),
    t = c * (x + 1) * (x + 1) + (k - c) * x * x;
    return ans - t;
}

ll ans, v = 1;
void out() {
    cout << ans << '\n';
    const ll x = b / v, c = b % v;
    bool flag = false;//控制输出格式
    for (ll i = 1; i < v; ++i) {
        if (flag) cout << 'o';
        for (ll j = 0; j < x; ++j) cout << 'x';//x个字符'x'
        if (i <= c) cout << 'x';//前c组就有x+1个'x'，其余组有x个'x'
        flag = true;
    }
    for (ll i = 0; i < a - v + 2; ++i) cout << 'o';
    for (ll i = 0; i < x; ++i) cout << 'x';
    cout << '\n';
}

int main() {
    fast;
    ans = -inf;
    cin >> a >> b;
    if (a == 0) {
        cout << b * b * (-1) << '\n';
        for (ll i = 0; i < b; ++i) cout << 'x';
        cout << '\n';
        return 0;
    }
    for (ll i = 2; i <= a + 1; ++i) {
        if (const ll t = get(i); t > ans) ans = t, v = i;
    }
    out();
    return 0;
}