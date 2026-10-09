//
// Created by Psy.C on 2026/10/9.
//
/**
fac[i] = i!。
inv[i] = (i!)^{-1} mod p（费马小定理快速幂求逆元）。
用于计算多重集排列数：
(
剩余总长
)
!
∏
j
(
c
n
t
j
!
)
∏
j
​
 (cnt
j
​
 !)
(剩余总长)!
​
由 a 这个字符串里的字符（作为多重集）生成的所有全排列中，字典序不大于 s 的有多少个
多重集康托展开（counting lexicographic rankings）‍：

t[c]：当前剩余未使用的各字符出现次数。
对每个位置 i：
计算分母
∏
c
n
t
j
!
∏cnt
j
​
 ! 的逆元 tp。
对每个比 s[i] 小的字符 j（还有剩余的情况下）：若把 j 放在当前位置，则剩余
l
−
i
−
1
l−i−1 个位置是多重集全排列，数量为
(
l
−
i
−
1
)
!
(
c
n
t
j
−
1
)
!
∏
k
≠
j
c
n
t
k
!
(cnt
j
​
 −1)!∏
k

=j
​
 cnt
k
​
 !
(l−i−1)!
​

即代码里 fac[l-i-1] · tp · cnt_j! · inv[cnt_j-1]（当 cnt_j>1 时），若 cnt_j=1 则分母少一个 cnt_j!，直接 fac[l-i-1]·tp。
累加所有比 s[i] 小的可放置字符贡献 = "以更小前缀开头的排列数"。
然后消耗掉 s[i]（t[ch]--）。若 ch 已用完则说明 s 不是合法排列，提前终止。
结果 ans = 字典序 ≤ s 的所有不同排列个数
calc(b) - calc(a) - 1 = 字典序严格在 (a, b] 开区间内（不含 a 本身）的排列个数。
即「所有字典序 ≤ b 的」减去「所有字典序 ≤ a 的」，再减 1（去掉 a 自身），得到严格介于 a 与 b 之间的排列数量。
取模后输出（保证非负）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e6, mod = 1e9+7;

ll ksm(ll a, ll b) {
    ll ans = 1;
    while (b) {
        if (b&1) ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}

ll fac[N+7], inv[N+7];
void init() {
    fac[0] = inv[1] = 1;
    for (int i = 1; i <= N; ++i) fac[i] = fac[i-1]*i%mod;
    for (int i = 1; i <= N; ++i) inv[i] = ksm(fac[i], mod-2);
}

int t[27], l;
char a[N+7], b[N+7];
ll calc(const char *s) {
    ll ans = 0; memset(t, 0, sizeof(t));
    for (int i = 0; i < l; ++i) t[a[i]-'a']++;//统计 a 中每个字符个数
    for (int i = 0; i < l; ++i) {
        int ch = s[i]-'a';
        ll tp = 1;
        for (int j = 0; j < 26; ++j)
            if (t[j]) tp=tp*fac[t[j]]%mod;//tp = ∏ cnt_j!
        tp = ksm(tp, mod-2);//逆元 → 1/∏cnt_j!
        for (int j = 0; j < ch; ++j) {
            if (t[j]) {
                if (t[j] > 1) ans=(ans+fac[l-i-1]*tp%mod*fac[t[j]]%mod*inv[t[j]-1]%mod)%mod;
                else ans=(ans+fac[l-i-1]*tp%mod)%mod;
            }
        }
        if (t[ch] <= 0) break;//字符 ch 已用完 → s 不可能是合法排列，停止
        t[ch]--;
    }
    return ans;
}

int main() {
    fast;
    cin >> a >> b; l = strlen(a); init();
    cout << (calc(b)-calc(a)-1+mod)%mod << '\n';
    return 0;
}