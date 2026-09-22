//
// Created by Psy.C on 2026/9/22.
//
/**
预计算所有阶乘对模 1e9+7 的值，供组合数 C(n,k) 使用
用费马小定理 x^(p-2) mod p 求 x 在模素数 p=1e9+7 下的逆元。因为 mod 是素数且 x 非0，所以成立
C(n,k) = n! / (k!(n-k)!)，除法用逆元实现
反复"相邻交替加减合并"得到的最终值，其系数是对称的。这里构造的是一半的系数（n/2 项），然后利用对称性生成全部 n 项。
规律：
系数数组关于中点对称：c[n-1-i] = ±c[i]
c[0], c[1], ..., c[n/2-1] 由组合数 C(tn-1, i) 给出，其中 tn = n/2
具体符号规则：
前半部分系数依次为 C(tn-1, 0), C(tn-1, 1), ..., C(tn-1, tn-1)
后半部分（对称镜像）的符号取决于 tn 的奇偶：
若 tn 为奇数：镜像部分同号（c[idx] = c[idx-1]）
若 tn 为偶数：镜像部分取反（c[idx] = -c[idx-1]）
get() 里的系数对称规律 θ(n/2) 只在 偶数长度 时才使得系数正好是 C(tn-1, i) 这样的对称组合。当 n 是奇数时，先手动做一轮相邻交替加减合并（把 n 个变成 n-1 个，即偶数个），再调用 get()。
合并方向是从左到右交替加减：a[i] = a[i] + (-1)^i * a[i+1]
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+5, mod = 1e9+7;

ll fac[N];
void init() {
    fac[0] = fac[1] = 1;
    for (int i = 2; i < N; ++i)
        fac[i] = i*fac[i-1]%mod;
}
ll ksm(ll x) {
    int n = mod-2;
    ll ans = 1, t = x;
    while (n) {
        if (n&1) ans = ans*t%mod;
        t = t*t%mod;
        n >>= 1;
    }
    return ans;
}
ll C(ll n, ll k) {
    //n! (n-k)! * k! y 的逆元
    ll x = fac[n], y = fac[n-k]*fac[k]%mod; y = ksm(y);
    return x*y%mod;
}

ll c[N], a[N];
int get(int n) {
    int tn = n/2, idx = 0;
    for (int i = 0; i < tn; ++i) {
        c[idx++] = C(tn-1, i);
        if (tn&1) c[idx] = c[idx-1];
        else c[idx] = -c[idx-1];
        ++idx;
    }
    ll ans = 0;
    for (int i = 0; i < n; ++i)
        ans = (ans+c[i]*a[i])%mod;
    return (ans+mod)%mod;
}

int main() {
    fast;
    int n; init();
    while (cin >> n) {
        for (int i = 0; i < n; ++i) cin >> a[i];
        if (n == 1) { cout << a[0] << '\n'; continue; }//单元素直接输出
        if (n&1) {//n 为奇数：先做一轮"相邻合并"变成偶数长度
            int flag = 1;
            for (int i = 0; i < n-1; ++i) {
                a[i] = a[i]+flag*a[i+1];//交替 + - + -
                flag *= -1;
            }
            --n;//长度减1，现在 n 为偶数
        }
        cout << get(n) << '\n';//偶数长度交给 get() 处理
    }
    return 0;
}