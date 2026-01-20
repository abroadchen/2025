//
// Created by Psy.C on 2026/1/20.
//
///每次随机：O(n log n + √a_max)//数组中最大元素
///总体：O(12 × (n log n + √a_max))
#include <iostream>
#include <random>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 1000005
#define M 8000
using namespace std;

ll gcd(ll a, ll b) {
    if (!a || !b) return a|b;//当其中一个数为0时，GCD就是另一个数
    const int t = __builtin_ctzll(a|b);//x的尾部连续0的个数
    a >>= __builtin_ctzll(a);//去除a的因子2 反复除以2直到a变为奇数
    do {
        b >>= __builtin_ctzll(b);
        if (a > b) { const ll x = b; b = a; a = x; }
        b -= a;
    } while (b);
    return a << t;//将之前提取的公共因子2^t乘回去
}

int cnt, tp;//cnt：小因数计数，tp：大因数计数
ll d[M], t[M];//d[]：存储因数，t[]：临时存储大因数
void get(const ll x) {//获取x的所有因数
    cnt = tp = 0;
    for (int i = 1; 1ll*i*i <= x; ++i) if (x % i == 0) {
        d[++cnt] = i;
        if (x/i != i) t[++tp] = x/i;
    }
    while (tp) d[++cnt] = t[tp--];//将大因数倒序添加到d数组中，保持升序
}


random_device rd;
mt19937 gen(rd());

int main() {
    fast;
    int n; cin >> n;
    ll a[N], tot[M], ans = 1;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int q = 1; q <= 12; ++q) {
        const int id = static_cast<int>(gen() % n + 1);
        get(a[id]);//获取选定元素的因数
        for (int i = 1; i <= cnt; ++i) tot[i] = 0;
        for (int i = 1; i <= n; ++i)//对每个元素计算与选定元素的GCD
            //找到GCD在因数数组中的位置并计数
            ++tot[lower_bound(d + 1, d + cnt + 1, gcd(a[id], a[i]))-d];
        for (int i = cnt; i; --i) {
            if (d[i] < ans) break;
            int s = static_cast<int>(tot[i]);//：统计包含因数d[i]的元素个数
            for (int j = i + 1; j <= cnt; ++j) if (d[j] % d[i] == 0) {
                s += static_cast<int>(tot[j]);//如果d[j]是d[i]的倍数，累加计数
            }
            if (s * 2 >= n) ans = d[i];//满足条件的元素占比≥1/2，更新答案
        }
    }
    cout << ans << '\n';
    return 0;
}