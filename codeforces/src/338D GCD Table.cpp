//
// Created by Psy.C on 2026/1/11.
//
/**
* lcm(a, b) = (a × b) / gcd(a, b)
所以 lcm(lcm, b[i]) = (lcm × b[i]) / gcd(lcm, b[i]) = (lcm × b[i]) / d
因此 lcm(lcm, b[i]) / lcm = b[i] / d
 *
* 直接计算 lcm * b[i] 会包含重复的公因子
除以 gcd(lcm, b[i]) 去除重复因子
 *lcm = lcm * m = lcm * (b[i] / gcd(lcm, b[i]))
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 10000
using namespace std;

///求解 ax + by = gcd(a,b) 的解
ll dfs(const ll a, const ll b, ll& x, ll& y) {
    if (!b) { x = 1, y = 0; return a; }//返回gcd(a,0)=a
    const ll d = dfs(b, a % b, y, x);//递归求解 bx' + (a%b)y' = gcd(b,a%b)
    y -= a / b * x;//调整解以满足原方程
    return d;//返回最大公约数
}

/// (x * p) % mod
ll ksm(ll x, ll p, const ll mod) {
    ll res = 0;
    for (; p; p>>=1, x = (x + x) % mod) {
        if (p&1) res = (res + x) % mod;
    }
    return res;
}

///x ≡ a[i] (mod b[i])
int k; ll n;
ll ex_crt(const ll *a, const ll *b, ll& lcm) {//a为余数数组，b为模数数组
    ll res = a[1]; lcm = b[1];//初始化结果和最小公倍数
    for (int i = 2; i <= k; ++i) {//从第二个方程开始处理
        ll x, y; const ll c = ((a[i]-res)%b[i]+b[i])%b[i],//确保结果在 [0, b[i]-1] 范围内
        d = dfs(lcm, b[i], x, y), m = b[i] / d;
        if (c % d) return -1;
        x = ksm(x, c / d, m);
        res += lcm * x;//res + lcm * t ≡ a[i] (mod b[i])
        lcm *= m;
        if (lcm > n) return -1;
        res = (res + lcm) % lcm;//规范化结果 确保 res 在范围 [0, lcm-1] 内
    }
    return res == 0 ? lcm : res;
}

ll gcd(const ll a, const ll b) { return !b ? a : gcd(b, a % b); }

int main() {
    fast;
    ll m, a[N+5], b[N+5], x; cin >> n >> m >> k;
    for (int i = 1; i <= k; ++i) {
        cin >> a[i];
        b[i] = ((1-i)%a[i] + a[i]) % a[i];//确保结果在 [0, a[i]-1] 范围内
    }
    const ll y = ex_crt(b, a, x);
    if (y == -1 || y > m - k + 1) { cout << "NO\n"; return 0; }
    for (int i = 1; i <= k; ++i) if (gcd(x, y + i - 1) != a[i]) {
        cout << "NO\n"; return 0;
    }
    cout << "YES\n";
    return 0;
}