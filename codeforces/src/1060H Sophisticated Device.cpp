//
// Created by Psy.C on 2026/11/10.
//

/**
真正学会的起点..
ksm 用于求逆元（mod-2 次幂）、以及后面的 mod-1 次幂倍增。
fac/ifac 预计算组合数，用于构造下面"多点插值"的系数。
zp：零/常数寄存器，用 r0 自加清零、r1 置 1；op 是另一个备用寄存器。
t*：临时寄存器
当 d==2（二次），直接一条 ^ 搞定。
一般 d 时，用多项式插值实现平方：把 x^2 表示为某个 d 次多项式 Σ vl[i]·(x+i)^2，通过多次平方与加权累加逼近——这就是为何需要解出系数 vl[]
构造线性方程组：mt[j][i] = C(d,j)·ksm(i, d-j)，mt[j][d+1] = (j==2?1:0)。
解这个线性系统，得到插值权值 vl[i]（0≤i≤d），使得
这样 sqr 就能在不直接支持平方的机器上，用 (x+i)^2（每条一条 ^ 指令可实现）的加权和精确还原出 x^2
这里 zp 最终被构造成常数 1（op 可能是另一常数或非 0 值，供插值位移用）。用 mod-1 的二进制位来倍增累加，得到所需常数
add(1,2,3);    // reg3 = a+b
sqr(3);        // reg3 = (a+b)^2
sqr(1);        // reg1 = a^2
sqr(2);        // reg2 = b^2
sub(3,1);      // reg3 = (a+b)^2 - a^2
sub(3,2);      // reg3 = (a+b)^2 - a^2 - b^2 = 2ab
mul(3,ksm(2,mod-2),t2);  // reg[t2] = 2ab/2 = ab
cout<<"f "<<t2<<'\n';    // 输出答案 ab
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 30;

ll mod;
inline ll ksm(ll a, ll b) {
    ll res = 1ll, base = a;
    while (b) {
        if (b&1) res=res*base%mod;
        base=base*base%mod;
        b>>=1ll;
    }
    return res;
}
inline void add(int x, int y, int z) { cout << "+ " << x << ' ' << y << ' ' << z << '\n'; }
int zp, op;
inline void r0(int x) { cout << "+ " << zp << ' ' << zp << ' ' << x << '\n'; }
inline void r1(int x) { cout << "+ " << op << ' ' << zp << ' ' << x << '\n'; }

int t5;
inline void mul(int x, ll y, int pos) {//用二进制倍增把 reg[x] 乘上常数 y（y 是编译期已知标量），结果放 pos
    r0(pos);//pos = 0
    if (y == 0) return;
    if (y == 1) add(x, zp, pos);
    else {
        add(x, zp, t5);//t5 = x
        r0(x);//x=0
        while (y) {//倍增累加：x = x + y*(原x)
            if (y&1) add(x, t5, x);
            add(t5, t5, t5);
            y >>= 1;
        }
        add(x, zp, pos);//pos 继承 x 的值
    }
}

array<ll,N> fac,ifac;
inline ll C(int n, int m) { return fac[n]*ifac[m]%mod*ifac[n-m]%mod; }

int d;
array<array<ll,N>, N> mt, rmt;
array<ll,N> vl;
inline void gauss() {
    for (int j = 0; j <= d; j++) {
        for (int i = j; i <= d; i++) if (mt[i][j]) { swap(mt[i], mt[j]); break; }
        for (int i = j+1; i <= d; i++) {
            if (!mt[i][j]) continue;
            ll val = mt[i][j]*ksm(mt[j][j], mod-2ll)%mod;
            for (int x = 0; x <= d+1; x++)
                mt[i][x] = (mt[i][x]-mt[j][x]*val%mod+mod)%mod;
        }
    }
    for (int i = d; i >= 0; i--) {
        vl[i] = mt[i][d+1];
        for (int j = i+1; j <= d; j++)
            vl[i] = (vl[i]-vl[j]*mt[i][j]%mod+mod)%mod;
        vl[i] = vl[i]*ksm(mt[i][i], mod-2ll)%mod;
    }
}

int t2, t, t3;
inline void sqr(int x) {
    if (d == 2) { cout << "^ " << x << ' ' << x << '\n'; return; }//d=2 时机器直接支持平方
    r0(t2); add(x, t2, t2); r0(x);
    for (int i = 0; i <= d; i++) {
        r0(t);
        add(t2, zp, t);//t = t2 + (i 次位移)
        for (int j = 1; j <= i; j++) add(t, op, t);
        cout << "^ " << t << ' ' << t << '\n';//t = t^2
        mul(t, vl[i], t3);
        add(x, t3, x);//x += vl[i]*t
    }
}
inline void sub(int a, int b) { mul(b, mod-1, t2); add(a, t2, a); }

int main() {
    fast;
    cin >> d >> mod; fac[0] = 1ll;
    for (int i = 1; i <= d; i++) fac[i] = fac[i-1]*i%mod;
    ifac[d] = ksm(fac[d], mod-2ll);
    for (int i = d-1; i >= 0; i--) ifac[i] = ifac[i+1]*(i+1)%mod;
    int now = 4997; zp = 5000; op = 4555; t = 4998; t2 = 3666; t3 = 1145; t5 = 1737;
    for (int i = 31; i >= 0; i--) {
        if ((mod-1)>>i&1) {
            for (int j = 0; j < i; j++) add(now, now, now);
            add(now, zp, zp);//累加进 zp（zp成为1,2,...）
            now--;
        }
    }
    for (int i = now+1; i <= 4997; i++) r1(i);
    for (int j = 0; j <= d; j++) {
        for (int i = 0; i <= d; i++) mt[j][i] = C(d,j)*ksm(i,d-j)%mod;
        mt[j][d+1] = j == 2 ? 1 : 0;
    }
    gauss(); add(1,2,3); sqr(3); sqr(1); sqr(2); sub(3,1); sub(3,2);
    mul(3, ksm(2ll,mod-2ll), t2);
    cout << "f " << t2 << '\n';
    return 0;
}