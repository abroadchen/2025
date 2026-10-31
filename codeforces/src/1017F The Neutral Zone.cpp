//
// Created by Psy.C on 2026/10/31.
//

/**
真正学会的起点..
N：小质数数组容量（1.8 万，够存 1.8e4 以内的质数并用于分段筛）
st[]：标记合数（true = 已筛掉）；
pri[]：从小到大存质数，cnt 记录质数个数；
euler(n)：欧拉筛，筛出 [2, n] 内所有质数。
核心逻辑（线性筛）：

外层 i 逐个枚举；
若 i 未被标记，说明它是质数，记入 pri；
内层用质数 pri[j] 去生成合数 i*pri[j]，并标记；
关键剪枝：if (i % pri[j] == 0) break; —— 每个合数只由它的最小质因子筛一次，保证 O(n) 线性复杂度
A,B,C,D：四次多项式系数；
o：上限（筛的最大范围）；
ans：最终答案
计算 f(x)=A·x³+B·x²+C·x+D。转成 ui 处理自然溢出
前半段：勒让德公式计算
n
!
n! 中质因子
p
p 的指数：
ν
p
(
n
!
)
=
⌊
n
p
⌋
+
⌊
n
p
2
⌋
+
⋯
ν
p
​
 (n!)=⌊
p
n
​
 ⌋+⌊
p
2

n
​
 ⌋+⋯
实现方式：t 从 n 开始反复除以 p 累加，直到 t < p。
后半段：res * f(p)，即该质数对整个答案的贡献。
对小于等于
o
o
​
  的质数，指数可能 >1，必须用这个完整公式
读入 o 和四个系数；bl = √o；筛出 [2, bl] 内的所有小质数
对每个 ≤ √o 的小质数 p，累加 calc(o, p)（含完整勒让德指数）
这一步就覆盖了所有小于等于
o
o
​
  的质数
逐段处理区间 [l, r]（每段长度约 bl）
把 st[] 当作本段区间的合数标记（下标 i-l+1 把绝对位置映射到段内），先全部清为 false
对每个小质数 pri[i]，找出它在本段 [l,r] 内的所有倍数 j*pri[i]（j 从「不小于 l 的最小倍数」到「不大于 r 的最大倍数」），把它们标记为合数。(l+p-1)/p 是上取整，保证 j*p ≥ l
段内未被标记的下标 i 即为质数，累加其贡献 calc(o, i)。

关键优化：大于
o
o
​
  的质数不可能在
o
!
o! 中出现平方及更高次幂（因为
p
2
>
o
p
2
 >o），所以勒让德公式里只有第一项
⌊
o
/
p
⌋
=
1
⌊o/p⌋=1，即 calc(o,p) = 1·f(p) = f(p)。代码里没有特判、统一调用 calc 也正确，因为 while(t>=p) 只执行一次
移到下一段
输出累加结果
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for (int i=j; i<=k; i++)
#define ui unsigned int
using namespace std;

constexpr int N = 1.8e4+10, M = 3e8+10;

namespace sieve {
    bool st[N]; int pri[N], cnt;
    void euler(int n) {
        rep(i,2,n) {
            if (!st[i]) { st[i] = true; pri[++cnt] = i; }
            rep(j,1,cnt) {
                if (pri[j]*i > n) break;
                st[i*pri[j]] = true;
                if (i%pri[j] == 0) break;
            }
        }
    }
}

int A, B, C, D, o;
ui ans;
namespace core {
    ui f(ui x) { return (ui)A*x*x*x+B*x*x+C*x+D; }
    ui calc(ui n, ui p) {
        ui res = 0, t = n;
        while (t >= p) { t /= p; res += t; }
        return res*f(p);
    }
    void solve() {
        cin >> o >> A >> B >> C >> D;
        int bl = (int)sqrt(o);
        sieve::euler(bl);
        rep(i,1,sieve::cnt) ans += calc(o, sieve::pri[i]);
        int l = bl + 1, r;
        while (l <= o) {
            r = min(l+bl-1, o);
            rep(i,l,r) sieve::st[i-l+1] = false;
            rep(i,1,sieve::cnt) rep(j,(l+sieve::pri[i]-1)/sieve::pri[i], r/sieve::pri[i])
                sieve::st[j*sieve::pri[i]-l+1] = true;
            rep(i,l,r) if (!sieve::st[i-l+1]) ans += calc(o, i);
            l = r + 1;
        }
        cout << ans << '\n';
    }
}


int main() {
    fast;
    int T = 1;
    while (T--) core::solve();
    return 0;
}