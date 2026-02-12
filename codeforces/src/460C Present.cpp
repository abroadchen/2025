//
// Created by Psy.C on 2026/2/12.
//
/**
n：元素数量
w：窗口大小
m：允许的最大操作次数
a：数值数组
cur：影响位置i的当前累积增加值
sum：已使用的总操作数

a[i]：原始值
cur：前面操作对该位置的累积影响
a[i] + cur：当前位置的实际值
如果实际值小于目标值x，就需要补充


时间复杂度为O(n log(最大值))
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, w, m;
vector<ll> a;
bool ok(const ll x) {
    vector<ll> s(n+1, 0);//每个位置需要增加的次数
    for (ll i = 0, cur = 0, sum = 0; i < n; ++i) {
        //移除超出窗口范围的影响
        cur -= i >= w ? s[i-w] : 0;//移除s[i-w]的影响（滑动窗口边界）
        if (x > a[i] + cur) {//当前位置仍低于目标值x
            s[i] = x - cur - a[i];//所需数量
            cur += s[i];
            sum += s[i];
        }
        if (sum > m) return false;
    }
    return true;
}

int main() {
    fast;
    cin >> n >> m >> w; a.resize(n+1);
    for (int i = 0; i < n; ++i) cin >> a[i];
    ll l = 1, r = 1e14, ans = 0;
    while (l <= r) {
        if (const ll mid = (l + r)>>1; ok(mid)) { ans = mid; l = mid + 1; }
        else r = mid - 1;
    }
    cout << ans << '\n';
    return 0;
}