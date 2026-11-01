//
// Created by Psy.C on 2026/11/1.
//

/**
真正学会的起点..
用试除法求 x 的不同质因子（每个质因子只存一次），并排序。返回值通过引用参数 top 传出个数
用平方根枚举法求出 x 的全部因子（成对入表，避免重复），再排序。这里得到的是 m 的所有因子，存入全局 fs
处理 x*y 可能爆 long long 的情况：用 double 估算商，做浮点矫正后再取模。这是竞赛里常见的"快速模乘"技巧
用二进制幂，结合 mul 实现模下快速幂，用于后面判断 t^k ≡ 1 (mod d)
利用 m 的质因子表 pri，按公式
φ
(
x
)
=
x
∏
p
∣
x
(
1
−
1
p
)
φ(x)=x∏
p∣x
​
 (1−
p
1
​
 ) 计算欧拉函数。由于 m 的质因子已预存，可对任意 x 快速求值
先求
φ
(
m
)
φ(m) 并分解其质因子。
对每个因子 d = fs[i]，其单位群阶为
f
=
φ
(
d
)
f=φ(d)。通过反复尝试除以质因子 fac[j]，只要 t^{l/fac[j]} ≡ 1 (mod d) 就继续缩小，从而求出 t 在模 d 下的阶 l。
累加 f/l，即每个因子贡献的
φ
(
d
)
/
o
r
d
d
(
t
)
φ(d)/ord
d
​
 (t)，最后返回总和
读入 m、t，预处理因子表和质因子表，输出 solve() 的结果
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e5+10;

void prim(ll x, ll pri[], int &top) {
    top = 0;
    for (ll i = 2; i*i <= x; i++)
        if (x%i == 0) {
            pri[++top] = i;
            while (x%i == 0) x/=i;
        }
    if (x != 1) pri[++top] = x;
    sort(pri+1, pri+top+1);
}
void get(ll x, ll fac[], int &top) {
    top = 0;
    for (ll i = 1; i*i <= x; i++)
        if (x%i == 0) {
            fac[++top] = i;
            if (i*i != x) fac[++top] = x/i;
        }
    sort(fac+1, fac+top+1);
}
ll mul(ll x, ll y, ll mod) {
    ll res = (x*y-(ll)((double)x*y/mod+0.1)*mod)%mod;
    if (res < 0) res += mod;
    return res;
}
ll ksm(ll x, ll y, ll mod) {
    x %= mod;
    ll res = 1;
    while (y) {
        if (y&1ll) res=mul(res,x,mod);
        x=mul(x,x,mod);
        y>>=1ll;
    }
    return res;
}

int tot;
ll pri[N];
ll eul(ll x) {
    for (int i = 1; i <= tot; i++)
        if (x%pri[i] == 0) x=x/pri[i]*(pri[i]-1ll);
    return x;
}

ll m, fac[N], fs[N], t;
int cnt;
ll solve() {
    ll e = eul(m), res = 0;
    int x = 0;
    if (e > 1) prim(e, fac, x); else fac[++x] = 1;//对 phi(m) 做质因数分解
    for (int i = 1; i <= cnt; i++) {//遍历 m 的每个因子 fs[i]
        ll f = eul(fs[i]), l = f;
        if (l > 1) {
            for (int j = 1; j <= x; j++)//用 phi(m) 的质因子尝试约简阶
                while (l%fac[j] == 0 && ksm(t, l/fac[j], fs[i]) == 1)
                    l /= fac[j];
        }
        res = res + f/l;//f / order = phi(d) / ord_d(t)
    }
    return res;
}

int main() {
    fast;
    cin >> m >> t; get(m, fs, cnt); prim(m, pri, tot);
    cout << solve();
    return 0;
}