//
// Created by Psy.C on 2026/1/17.
//
///最小公倍数（两个字符串模式的重复周期）
/// // i%g: 位置i在周期g中的相对位置
// y[i]-'a': 将字符转换为0-25的数字(0='a', 1='b', ...)
// cnt[i%g][y[i]-'a']++: 在位置i%g统计字符y[i]的出现次数
// n * lx: 总长度
// n * lx / t: 重复周期的次数
// ans * (n * lx / t): 最终答案
#include <iostream>
#include <algorithm>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 1000005
using namespace std;


int main() {
    fast;
    ll n, m; char x[N], y[N];
    cin >> n >> m >> x >> y;
    ll lx = static_cast<ll>(strlen(x)), ly = static_cast<ll>(strlen(y));
    const ll g = __gcd(lx, ly), t = lx * ly / g;//长度的最大公约数g和最小公倍数t
    int cnt[N][26]={};//在模式位置i%g处字符c出现次数
    //y字符串中每个位置模g后对应字符的出现次数
    for (int i = 0; i < ly; ++i) cnt[i%g][y[i]-'a']++;
    ll ans = t;
    for (int i = 0; i < lx; ++i) ans -= cnt[i%g][x[i]-'a'];//减去x中字符在对应位置出现的次数
    cout << ans * (n * lx / t) << '\n';
    return 0;
}