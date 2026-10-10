//
// Created by Psy.C on 2026/10/10.
//
/**
选一个特殊的大质数 mod（形如 lcm(n,2^k)+1，保证能用 2^k 次根做 NTT，且 mod 足够大）；
找该质数的原根 g；
用 NTT（快速数论变换）辅助做 CZT（Chirp z-Transform），把"循环/移位卷积"线性化，从而解出分母多项式对应的系数；
最后得到一个多项式\递推系数 a[]，再通过差分 + 二次方程还原出若干组整数解
mul: 模意义下乘法，用长 double 逼近 a*b/mod 的商来做"蒙哥马利式"防爆 long long：(ll)((ld)a*b/mod) 是商的整数近似，a*b - 商*mod 对 2^64 以内安全，+mod)%mod 归一
inf=12000：解的数值上界（判定整数解时用，a[i]>6000 表示减 mod）。
N=1e5: 系数上限；M=100：质因数个数上限；B=262144=2^18: NTT 最大长度。
n: 数组长度（输入）；tn=2n-1：循环到线性化需要的长度；len：向上取整到 2 的幂
① get_mod()：构造"友好的"大质数
目标：找一个质数 mod，且 mod-1 能被 len（2 的幂）‍整除——这样模 mod 下存在 len 次单位根，能做长度 len 的 NTT。
取 mod = k·lcm(n,len)+1：则 (mod-1) 同时被 n 和 len 整除，保证 n 次根、len 次根都存在（CZT 和 NTT 都需要）。
从 lcm+1 起，逐次 +lcm，并做试除质数判定，找到第一个质数为止。inf 保证模数足够大以免答案被模坏
② get_g()：找原根
原根判定定理：g 是 mod 的原根 ⇔ 对 mod-1 的每个质因子 p，g^((mod-1)/p) ≠ 1 (mod mod)。
这里 tg[] 存的是 (mod-1)/每个质因子，逐一验证 i^tg[j]==1 是否成立；不成立（都非1）则该 i 是原根。从小到大枚举找最小原根
③ NTT（数论变换）
wn/iwn：预存的 len 次单位根（原根幂）及其逆；w 是临时的单位根指针；r[] 是位反转表；inv 是 len 的逆元（做逆变换时乘）
标准迭代式 NTT。o==wn 正向、o==iwn 逆向（逆向末尾乘 inv）。st 每层减半对应单位根的次方步进。
注意 w=o 在每块 k 重置为根表头，配合 w+=st 取该层需要的根
④ CZT（Chirp z 变换，线性化循环卷积）
把一个"循环卷积/循环移位"的系数关系化成一个普通卷积（用 NTT 完成），用于求递推系数
pg 是 chirp 序列：pg[i] = g^((mod-1)/n·i)，即 n 次单位根（g^{(mod-1)/n}）的幂——本质是一个 n 阶展开。

c2[i] = i(i-1)/2 mod n，c2[i+1] = (c2[i]+i)%n 递推得到（三角形数 mod n）；ic2[i] 是其在模 n 下的相反数（n-c2[i]）。这是 CZT 中的"平方指数"，用于把"卷积里的移位 i+j" 改写为 (i+j)^2 - i^2 - j^2 形式
核心公式（Chirp trick）：

循环卷积的移位 i 等价于：先乘 w^{-i²/2}，普通卷积，再乘 w^{-i²/2}
即一个循环线性移位的卷积可通过三次普通卷积（NTT）完成，复杂度 O(n log n)。

函数作用：给定数组 t[]（长度 n），返回其"循环卷积于固定核后的结果"t[]。具体用于后面求解方程时把循环差分算子线性化

b[N]: 输入数组 b；
c[N]: 输入的右端/目标数组 c；
vc[N]: c 的循环差分（c[i]-c[i-1] 循环意义下）；
vb[N]: b 的变换（乘 mod-2 = -1 并翻转）；
a[N]: 待求的递推/卷积系数；
s[N]: a 的前缀和，用于还原最终解
读 n，构造质数 mod、原根 g。
ig=g^{-1}、inv=len^{-1}（NTT逆用）、ninv=n^{-1}
位反转预处理（r[i] 是 i 的二进制按位反转）
预计算三套单位根：wn（正根）、iwn（逆根）、pg（n 阶 chirp 核）
c2[i] = triangular(i) mod n；ic2 为其模 n 负元
读入 b[0..n-1]，读 c0 作为 c[0]，其余 c[i] 取模
vc = 循环意义下 c 的差分序列（vc[i]=c[i]-c[i-1]，下标循环）。czt(vc) 把它做 Chirp 变换——这一步实际是在"傅里叶域"里表达差分算子，用于消去递推分母
vb = 取 -b 并把非 0 下标"翻转"（b[n-i]），再做 CZT。这是把分母对应的循环卷积核也变到变换域。
数学上，这段在做"循环卷积方程"的频域相除。方程形如（推测）：

a �tension (循环卷积) b = c 的某个差分形式
两边同时 CZT（等价于离散傅里叶变换 + chirp 定位），于是在变换域里除法：A(f) = Vc(f)/Vb(f)
在变换域做除法得到 a，reverse(a+1,a+n) 是逆 CZT 需要的次序调整（与普通 IDFT 的 index 反转对应），再做 czt 逆变换回时域，乘 ninv 完成归一。
现在 a[1..n-1] 就是求得的递推/卷积系数（近似某个"格林函数/冲激响应"）
把系数转回有符号整数（a[i]>6000 视为 a[i]-mod，因为 mod≈>12000 一半），再算前缀和 s[i]（因为差分被求过，解要用积分/前缀和还原）
⑥ 用二次方程还原整数解
计算两组量：sum = Σ(s[i]-b[i])，psum = Σ(s[i]-b[i])²。
含义：设解为 x[i]=a0 + s[i]（a0 是待定常数项），希望满足某种二次约束（形如 Σx[i]=某值 且 Σx[i]²-c0=0）。利用 x=a0+s 带入后得到关于 a0 的一元二次方程，sum/psum 是方程的系数
判别式 delta = sum² - n(psum - c0)，这正是消元后得到的关于 a0 的二次方程的判别式（系数来自上面两式的组合，c0 是二次方程的常数项目标）
这一整段就是在解二元一次关系回推 a0：
二次方程两根 a0 = (-sum ± sqrt(delta)) / n（推导自 sum·x + n·a0·… 的组合）。
要求 delta 是完全平方数（sd²==delta），且分子被 n 整除，才得到整数 a0。
根据两个根是否都整数，输出 2、1 或 0 组解。每组解 x[i] = a0 + s[i]
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ld long double
using namespace std;

ll mod;
ll mul(ll& a, ll& b) { return (a*b-(ll)((ld)a*b/mod)*mod+mod)%mod; }
ll ksm(ll x, ll p) {
    ll res = 1;
    while (p) {
        if (p&1) res=mul(res,x);
        x=mul(x,x);
        p>>=1;
    }
    return res;
}
ll gcd(ll a, ll b) {
    ll r;
    while (b) r=a%b, a=b, b=r;
    return a;
}

const int inf = 1e4+2e3, N = 1e5, M = 100, B = 262144;
ll tn, n, len(1);
void get_mod() {
    tn = 2*n-1;
    while (len < tn) len<<=1;//len = ≥2n-1 的最小2的幂
    ll lcm(n*len/gcd(n,len)); mod = lcm+1;
    while (mod <= inf) mod += lcm;
    bool flg;
    while (1) {
        flg = 1;
        for (int i = 2; 1ll*i*i <= mod; ++i)
            if (mod%i == 0) { flg = 0; break; }
        if (flg) return;//找到质数
        mod += lcm;//尝试下一个 lcm+1k
    }
}

ll tg[M], g;
int cnt;
void get_g() {
    bool flg;
    ll t(mod-1);
    for (int i = 2; 1ll*i*i < mod; ++i) {//分解 mod-1
        if (t%i == 0) tg[cnt++] = (mod-1)/i;//记录 (mod-1)/i 这一因子
        while (t%i == 0) t/=i;
    }
    if (t > 1) tg[cnt++] = (mod-1)/t;//剩下的最大质因子
    for (ll i = 2; ; ++i) {//枚举候选原根
        flg = 1;
        for (int j = 0; j < cnt; ++j)
            if (ksm(i, tg[j]) == 1) { flg = 0; break; }//若 i^(因子)==1 则非原根
        if (flg) { g = i; return; }
    }
}

ll wn[B]{1}, *w, iwn[B]{1}, inv;
int r[B];
void ntt(ll *t, ll *o = wn) {
    for (int i = 0; i < len; ++i)
        if (i < r[i]) swap(t[i], t[r[i]]);//位反转重排
    for (int i = 1, j = 2, st = len>>1; i < len; i<<=1, j<<=1, st>>=1) {
        //蝶形运算，st 是当前单位根步长
        for (int k = 0; k < len; k += j) {
            w = o;
            for (int l = k; l < k+i; ++l, w += st) {
                ll tmp(mul(t[l+i], *w));//乘单位根
                t[l+i] = t[l] - tmp;
                if (t[l+i] < 0) t[l+i] += mod;
                t[l] += tmp;
                if (t[l] >= mod) t[l] -= mod;
            }
        }
    }
    if (o == iwn) {//逆变换最后乘 1/len
        for (int i = 0; i < len; ++i)
            t[i] = mul(t[i], inv);
    }
}

ll t0[B], pg[N]{1}, t1[B];
int c2[N<<1], ic2[N];
void czt(ll *t) {
    for (int i = 0; i < tn; ++i) t0[i] = pg[c2[i]];
    for (int i = 0; i < n; ++i) t1[n-1-i] = mul(pg[ic2[i]], t[i]);
    ntt(t0); ntt(t1);
    for (int i = 0; i < len; ++i) t1[i] = mul(t1[i], t0[i]);
    ntt(t1, iwn);
    for (int i = 0; i < n; ++i) t[i] = mul(pg[ic2[i]], t1[n-1+i]);
    for (int i = tn; i < len; ++i) t0[i] = 0;
    for (int i = n; i < len; ++i) t1[i] = 0;
}

ll ig, ninv, b[N], c[N], vc[N], vb[N], a[N], s[N];
int main() {
    fast;
    cin >> n; get_mod(); get_g();
    ig = ksm(g, mod-2); inv = ksm(len, mod-2); ninv = ksm(n, mod-2);
    for (int i = 0; i < len; ++i) r[i] = (r[i>>1]|((i&1)?len:0))>>1;//位反转表
    ll tmp = ksm(g, (mod-1)/len);
    for (int i = 1; i < len; ++i) wn[i] = mul(wn[i-1], tmp);//len 次单位根
    tmp = ksm(ig, (mod-1)/len);
    for (int i = 1; i < len; ++i) iwn[i] = mul(iwn[i-1], tmp);//单位根的逆
    tmp = ksm(g, (mod-1)/n);
    for (int i = 1; i < n; ++i) pg[i] = mul(pg[i-1], tmp);//n 次单位根（chirp核）
    for (int i = 0; i < tn; ++i) c2[i+1] = (c2[i]+i)%n;//三角形数 mod n
    for (int i = 0; i < n; ++i) ic2[i] = c2[i]?n-c2[i]:c2[i];//相反数
    for (int i = 0; i < n; ++i) cin >> b[i];
    ll c0; cin >> c0; c[0] = c0%mod;
    for (int i = 1; i < n; ++i) { cin >> tmp; c[i] = tmp%mod; }
    for (int i = 1; i < n; ++i) {//循环差分 (c[i]-c[i-1])
        tmp = c[i] - c[i-1]; vc[i] = tmp<0?tmp+mod:tmp;
    }
    //闭环差分
    tmp = c[0] - c[n-1]; vc[0] = tmp<0?tmp+mod:tmp; czt(vc); tmp = mod-2;
    for (int i = 1; i < n; ++i) vb[i] = mul(tmp, b[n-i]);//vb[i]=(-1)*b[n-i] (翻转)
    vb[0] = mul(tmp, b[0]); czt(vb);
    for (int i = 0; i < n; ++i) {
        tmp = ksm(vb[i], mod-2);//求 vb[i] 的逆（频域相除）
        a[i] = mul(vc[i], tmp);//变换域：a = vc / vb
    }
    //逆变换前的频率重排
    reverse(a+1, a+n); czt(a);
    for (int i = 0; i < n; ++i) a[i] = mul(a[i], ninv);//最终除以 n（逆 CZT 归一）
    for (int i = 1; i < n; ++i) {
        tmp = a[i] > 6000 ? a[i] - mod : a[i];//若超过6000认为是负值（从mod减回）
        s[i] = s[i-1] + tmp;//前缀和，逐步还原
    }
    ll sum(0), psum(0);
    for (int i = 0; i < n; ++i) {
        tmp = s[i] - b[i];
        sum += tmp, psum += tmp*tmp;
    }
    ll delta(sum*sum-n*(psum-c0)), a0;
    if (delta > 0) {
        ll sd((ll)(sqrt(delta)+0.5));//delta 的整数平方根
        if (sd*sd != delta) { cout << "0"; return 0; }//非完全平方 → 无整数解
        tmp = -sum - sd;
        if (tmp%n == 0) {//检查整除性，得一个 a0
            a0 = tmp/n, tmp = -sum + sd;
            if (tmp%n == 0) {//两个根都整
                cout << "2\n";//输出两组解
                for (int i = 0; i < n; ++i) cout << a0+s[i] << ' ';
                cout << '\n';
                a0 = tmp/n;
                for (int i = 0; i < n; ++i) cout << a0+s[i] << ' ';
            } else {
                cout << "1\n";//只有一个整根
                for (int i = 0; i < n; ++i) cout << a0+s[i] << ' ';
            }
        } else {
            tmp = -sum + sd;
            if (tmp%n == 0) {
                cout << "1\n";
                a0 = tmp/n;
                for (int i = 0; i < n; ++i) cout << a0+s[i] << ' ';
            } else cout << "0";//两根都不整 → 无解
        }
    } else if (delta == 0) {
        if (sum%n == 0) {//判别式为0，单根
            cout << "1\n";
            a0 = -sum/n;
            for (int i = 0; i < n; ++i) cout << a0+s[i] << ' ';
        } else cout << "0";
    } else cout << "0";//delta<0 无实根
    return 0;
}