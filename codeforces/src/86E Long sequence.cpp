//
// Created by Psy.C on 2025/11/8.
//
/*
 *定义模乘函数，使用__int128避免溢出
*定义模幂函数，使用快速幂算法：
初始化结果res为1，底数b对m取模
当指数e大于0时循环：
如果e是奇数，将当前b乘入结果
将b平方并对m取模
e右移一位（除以2）
 *
*Miller-Rabin素性测试函数：
小于2的数不是素数
检查是否在已知小素数列表中
偶数（除了2）不是素数
将n-1分解为d×2^s的形式
*对每个基数a进行Miller-Rabin测试：
如果a等于n，返回true
计算a^d mod n
如果结果是1或n-1，继续下一个基数
否则进行s-1次平方操作，检查是否得到n-1
如果都不能得到n-1，说明n是合数
 *
*Pollard's rho因数分解算法：
如果n是偶数，返回2
初始化随机起点x,y和参数c
定义函数f(x) = (x² + c) mod n
使用Floyd判圈算法寻找因子：
x每次走一步，y每次走两步
计算gcd(|x-y|, n)，如果大于1则找到因子
 *
*递归因数分解函数：
如果n为1，返回
如果n是素数，加入因子列表
否则使用rho算法找到因子p
递归分解p和n/p
 *
*获取n的所有不同质因子：
调用fac进行因数分解
排序因子列表
去除重复因子
返回因子列表
 *
*计算多项式的度数：
从最高位开始查找第一个非零系数
返回其位置，如果没有则返回-1
 *
*多项式模运算：
计算多项式a除以多项式p的余式
当a的度数大于等于p的度数时：
将p左移适当位数与a的最高项对齐
使用异或运算进行减法（在GF(2)中加法等于减法）
返回余式
 *
*多项式乘法：
如果a的度数小于0（零多项式），返回零多项式
对a的每一项，如果系数非零，则将b左移相应位数加到结果中
返回乘积结果
 *
*项式模幂运算：
初始化结果为1，底数对模取余
使用快速幂算法计算b^e mod p
每次乘法后都进行模运算
 *
*读取参数k
计算n = 2^k - 1
初始化随机数生成器
获取n的质因子分解
创建基多项式x（只有x¹项系数为1）
*无限循环寻找本原多项式：
构造候选多项式rp：
设置最高位和最低位为1（保证是k次首一多项式）
随机设置中间位
如果汉明重量（1的个数）是偶数，跳过
将rp转换为多项式形式
*检查是否为本原多项式：
首先检查x^n ≡ 1 (mod p)
然后对每个质因子x，检查x^(n/x) ≢ 1 (mod p)
如果都满足，则是本原多项式
*如果找到本原多项式：
输出多项式的系数（从高次到低次）
输出反馈多项式的系数（1后跟k-1个0）
 *
 */
#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include <bitset>
using namespace std;

typedef long long ll;
using poly = bitset<128>;
int k;

ll mmul(ll a, ll b, ll m) { return (__int128)a * b % m; }

ll mpow(ll b, ll e, ll m) {
    ll res(1); b %= m;
    while (e > 0) {
        if (e & 1) res = mmul(res, b, m);
        b = mmul(b, b, m);
        e >>= 1;
    }
    return res;
}

bool ispr(ll n) {
    if (n < 2) return false;
    ll b[] = {2,3,5,7,11,13,17,19,23,29,31,37};
    for (ll x : b) if (n == x) return true;
    if (n % 2 == 0) return false;
    ll d(n - 1); int s(0);
    while ((d&1) == 0) { d >>= 1; s++; }
    for (ll a : b) {
        if (n == a) return true;
        ll x = mpow(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool ok = true;
        for (int r = 1; r < s; ++r) {
            x = mmul(x, x, n);
            if (x == n - 1) { ok = false; break; }
        }
        if (ok) return false;
    }
    return true;
}

ll rho(ll n, ll s, mt19937_64& rng) {
    if (n % 2 == 0) return 2;
    ll x = rng() % (n - 2) + 2, y = x, c = s, d = 1;
    auto f = [&](ll v) { return (mmul(v, v, n) + c) % n; };
    while (d == 1) { x = f(x); y = f(f(y)); d = __gcd(abs(x - y), n); }
    return d;
}


void fac(ll n, vector<ll>& f, mt19937_64& rng) {
    if (n == 1) return;
    if (ispr(n)) { f.push_back(n); return; }
    ll p = n;
    while (p == n) p = rho(n, rng() % (n - 1) + 1, rng);
    fac(p, f, rng);
    fac(n / p, f, rng);
}

vector<ll> getf(ll n, mt19937_64& rng) {
    vector<ll> f;
    fac(n, f, rng);
    sort(f.begin(), f.end());
    f.erase(unique(f.begin(), f.end()), f.end());
    return f;
}

int deg(const poly& p) {
    for (int i = 127; i >= 0; --i) if (p[i]) return i;
    return -1;
}

poly pmod(poly a, const poly& p) {
    int dp = deg(p), da;
    while ((da = deg(a)) >= dp) a ^= (p << (da - dp));
    return a;
}

poly mul(const poly& a, const poly& b) {
    poly res; int da = deg(a);
    if (da < 0) return res;
    for (int i = 0; i <= da; ++i) if (a[i]) res ^= b << i;
    return res;
}


poly powe(poly b, ll e, const poly& p) {
    poly res; res[0] = 1; b = pmod(b, p);
    while (e > 0) {
        if (e & 1) res = pmod(mul(res, b), p);
        b = pmod(mul(b, b), p);
        e >>= 1;
    }
    return res;
}


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> k;
    ll n = (1ull << k) - 1;
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    vector<ll> pfac = getf(n, rng);
    poly base_x; base_x[1] = 1;
    while (true) {
        ll rp = (1ull << k) | 1;
        if (k > 1) { ll rb = rng(); rp |= (rb << 1) & ((1ull << k) - 2); }
        if (__builtin_popcountll(rp) % 2 == 0) continue;
        poly p(rp);
        if (powe(base_x, n, p) != poly(1)) continue;
        bool ok = true;
        for (ll x : pfac) {
            if (powe(base_x, n / x, p) == poly(1)) {
                ok = false;
                break;
            }
        }
        if (ok) {
            for (int i = k - 1; i >= 0; --i) {
                cout << p[i] << (i == 0 ? "" : " ");
            }
            cout << '\n';
            cout << 1;
            for (int i = 1; i < k; ++i) cout << " " << 0;
            cout << '\n';
            return 0;
        }
    }
    return 0;
}