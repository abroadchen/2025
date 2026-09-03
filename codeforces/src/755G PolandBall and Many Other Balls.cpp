//
// Created by Psy.C on 2026/9/2.
//
/**
mod 998244353 常用 NTT 模数（质数，998244353 = 119×2²³ + 1）
pN 1<<16 = 65536 NTT 数组最大长度
N 1<<15 = 32768 阶乘数组最大长度

x >> 31: 取 x 的符号位（int 是 32 位）
  如果 x >= 0: x>>31 = 0 → 0 & mod = 0 → x += 0 → x 不变
  如果 x < 0:  x>>31 = -1 (全1) → -1 & mod = mod → x += mod → x 变正
把 x 从 [-mod, mod] 范围拉回 [0, mod) 。

Pow(3, mod-2): 3 在 mod 下的乘法逆元（因为 mod 是质数，逆元 = a^(mod-2)）
Pow(G, (mod-1)/(mid<<1)): 计算单位根 ω
pn 当前 NTT 的数组长度（必须是 2 的幂）
rev[pN] 位反转数组 （蝴蝶操作用）
G 原根 = 3（mod 998244353 的一个原根）
iG G 的逆元 = Pow(3, mod-2)

G = 3 是 mod 998244353 的原根，意味着:
  3^1, 3^2, 3^3, ..., 3^(mod-1) ≡ 1 (mod mod)
  遍历了 mod 的所有非零剩余类
ω_n = G^((mod-1)/n) 是 n 次单位根（模 mod 意义下）

up2(n) ：向上取到最近的 2 的幂
revn() ：预计算位反转表
rev[i] = 把 i 的二进制位反转后的索引
i=0: 000 → 000 → rev[0]=0
  i=1: 001 → 100 → rev[1]=4
  i=2: 010 → 010 → rev[2]=2
  i=3: 011 → 110 → rev[3]=6
  i=4: 100 → 001 → rev[4]=1
  i=5: 101 → 101 → rev[5]=5
  i=6: 110 → 011 → rev[6]=3
  i=7: 111 → 111 → rev[7]=7
NTT 蝴蝶操作需要把元素按"位反转序"排列，才能自底向上地合并
p 多项式数组（长度必须是 2 的幂）
t false = 正变换， true = 逆变换
只在 i < rev[i] 时交换，避免重复交换。

外层 ：枚举区间长度的一半。从长度 2 开始（mid=1），逐步翻倍到 pn。
中层 ：
- wn ：当前层的 单位根 。正变换用 G，逆变换用 iG
- i ：遍历所有长度为 mid<<1 的块
内层 ：在每个块内做蝴蝶操作。
- j ：块内左半部分的索引
- w ：当前累积的单位根（从 1 开始，每次乘 wn）
- (mid|i) 等价于 i + mid （因为 mid 和 i 不重叠，i 是 mid 的偶数倍）

蝴蝶变换 ：
x = p[j]            // 左值
y = p[j+mid] * w    // 右值乘以单位根
新 p[j]    = (x + y) mod mod
新 p[j+mid] = (x - y) mod mod

逆变换的归一化
逆 NTT 需要除以 pn （因为正变换做了 pn 次累加）。用费马小定理：除法 = 乘以逆元。

fac[i] i 的阶乘 ：i!
dfac[i] 下降阶乘 ：m×(m-1)×...×(m-i+1)
ifac[i] fac[i] 的逆元
idfac[i] dfac[i] 的逆元
a[pN] , b[pN] 多项式数组（NTT 卷积用）
pw 2 的幂（累乘，初始 1）

- ++n ：n 加 1（多项式次数上限调整）
- pn = up2(n<<1) ：NTT 数组长度 ≥ 2n（卷积后长度 = deg(a) + deg(b)）
- revn() ：预计算位反转表
fac fac[i+1] = (i+1) × fac[i] (i+1)!
dfac dfac[i+1] = (m-i) × dfac[i] m 的 i+1 次下降阶乘

构建逆元（从大到小倒推）
ifac[n-1] = 1/(n-1)!  → 用快速幂算一次
ifac[n-2] = 1/(n-2)! = n-1/(n-1)! = (n-1) × ifac[n-1]
ifac[n-3] = 1/(n-3)! = n-2/(n-2)! = (n-2) × ifac[n-2]
...
只要算出最大的那个逆元，就能 O(n) 倒推出所有小的
idfac[k-1] = 1/(m × ... × (m-k+2)) = (m-k+1) × idfac[k]

构建多项式 A 和 B
b[i] = (1/i!)² × 2ⁱ
pw 是 2ⁱ:
  初始 pw = 1 = 2⁰
  i=0: pw = 1, 然后 pw = 2×1 - mod ≡ 2 = 2¹
  i=1: pw = 2, 然后 pw = 4 - mod ≡ 4 = 2²
  ...
a[i] = ifac[i] × idfac[i]  （正数）
如果 i 是奇数: a[i] = -a[i]  （变成负数，后面 fmod 转回正的）
a[i] = (-1)ⁱ × (1/i!) × (1/dfac[i])
     = (-1)ⁱ / (i! × P(m, i))

- 点值相乘 ： C[k] = A[k] × B[k] （O(pn)）
- 逆 NTT ：把 C 从点值表示转回系数表示 → a 现在是 A×B 的卷积结果
- cle(a) ：调用宏 cle(p) = fill(a+n, a+pn, 0) ，把 [n, pn) 范围清零（卷积可能产生超出范围的垃圾值）
之前构建 A 和 B 时除了 fac[i] 和 dfac[i] （用的是逆元），现在乘回来。
从 i=1 开始输出（i=0 跳过），每个值后面跟空格。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define R(i,n) for(int i=0; i<n; ++i)
#define L(i,n) for(int i=n-1; i>=0; --i)
#define cle(p) fill((p)+n,(p)+pn,0)//清空数组 [n, pn) 范围
#define ll long long
using namespace std;

constexpr int mod = 998244353, pN = 1<<16, N = 1<<15;
void fmod(int &x) { x += x>>31&mod; }
int Pow(int a, int x, int res = 1) {
    for (; x; x>>=1, a=1ll*a*a%mod)
        (x&1)&&(res=1ll*res*a%mod);//如果最低位是 1 → res *= a （乘上当前的 a）
    return res;
}

int pn, rev[pN], iG = Pow(3, mod-2), G = 3;
void ntt(int *p, bool t) {
    R(i,pn) if (i < rev[i]) swap(p[i], p[rev[i]]);
    for (int mid = 1; mid < pn; mid <<= 1)
        for (int wn = Pow(t?iG:G, (mod-1)/(mid<<1)), i = 0; i < pn; i += mid<<1)
            for (int j = i, w = 1, x, y; j < (mid|i); ++j, w=1ll*w*wn%mod)
                x = p[j], y = 1ll*p[mid|j]*w%mod, fmod(p[j]+=y-mod), fmod(p[mid|j]=x-y);
    if (t) {
        int in = Pow(pn, mod-2);
        R(i,pn) p[i] = 1ll*in*p[i]%mod;
    }
}

int up2(int n) { return 1<<int(ceil(log2(n))); }
void revn() {
    R(i,pn) rev[i] = (rev[i>>1]>>1)|((i&1)*(pn>>1));
}

int m, n, fac[N], dfac[N], ifac[N], idfac[N], b[pN], a[pN], pw=1;
int main() {
    fast;
    cin >> m >> n; ++n; pn = up2(n<<1); revn();
    fac[0] = dfac[0] = 1;
    R(i,n-1) fac[i+1] = (1ll+i)*fac[i]%mod;
    R(i,min(n-1,m)) dfac[i+1] = 1ll*(m-i)*dfac[i]%mod;
    ifac[n-1] = Pow(fac[n-1], mod-2);
    idfac[min(n-1,m)] = Pow(dfac[min(n-1, m)], mod-2);
    L(i,n-1) ifac[i] = (1ll+i)*ifac[i+1]%mod;
    L(i,min(n-1,m)) idfac[i] = 1ll*(m-i)*idfac[i+1]%mod;
    R(i,n) b[i] = 1ll*ifac[i]*ifac[i]%mod*pw%mod, fmod(pw=(pw<<1)-mod),
        a[i] = 1ll*ifac[i]*idfac[i]%mod, (i&1)&&(fmod(a[i]=-a[i]), true);
    ntt(a, false), ntt(b, false);//把 A 和 B 从 系数表示 转成 点值表示 。
    R(i,pn) a[i] = 1ll*a[i]*b[i]%mod; ntt(a, true), cle(a);
    R(i,n) a[i] = 1ll*a[i]*fac[i]%mod*dfac[i]%mod;
    R(i,n) if (i) cout << a[i] << ' ';
    cout << '\n';
    return 0;
}