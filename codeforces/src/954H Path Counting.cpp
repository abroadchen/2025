//
// Created by Psy.C on 2026/10/19.
//
/**
pre 是前缀积，suf 是后缀积，ns 是 suf 的逆元（用于快速做"除以某后缀积"）
主循环把
k
k 分成两个区域处理，
k
=
i
+
j
k=i+j 是核心（i、j 是某种配对的两端下标）。当
k
≤
2
n
k≤2n 时，预先用前缀和
s
[
i
]
=
∑
n
s
[
t
]
⋅
n
s
[
k
−
t
]
s[i]=∑ns[t]⋅ns[k−t] 加速若干求和。

内层对每个
i
i（1..n-1）‍ 算出 j = k-2i，然后分情况叠加
每个 i 对某个 ans[j]（即
j
=
k
−
2
i
j=k−2i）累加贡献，贡献分两部分：

一个组合系数
(
a
i
(
a
i
−
1
)
/
2
)
(a
i
​
 (a
i
​
 −1)/2)·后缀积平方·一段前缀和快速区间求和；
一项 suf[i]*ns[i+j]。
这两个分支对应计数问题里"两条路径在 i 处会合 / 分离"的贡献分解，属于格点路径 / 配对方案数的容斥式处理

读入
n
−
1
n−1 个权值
a
i
a
i
​
 ，构建前缀积 pre、后缀积 suf、后缀积逆元 ns；
以
k
=
i
+
j
k=i+j 为主键做分块枚举（
k
≤
2
n
k≤2n 时用前缀和 s 加速区间求和）；
对每个
i
i，利用 $(a_i(a_i-1)/2)·佐积·逆元·区间求和归纳并累加到ans[j]`；
最终输出
2
n
−
2
2n−2 个 ans[i]，每个都是 mod 1e9+7 下的方案/权值计数。
整体复杂度接近
O
(
n
2
)
O(n
2
 )（k 有
O
(
n
)
O(n) 档、每档遍历
O
(
n
)
O(n) 个 i），常数偏大但 N=5005 可过
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
#define per(i,j,k) for(int i=(j), i##_end_=(k); i>=i##_end_; --i)
#define int long long
using namespace std;

constexpr int N = 5005, mod = 1e9+7;

int ksm(int a, int b) {
    int res = 1;
    while (b) {
        if (b&1) res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}

int n, a[N], pre[N], suf[N], ns[N], s[N], ans[N<<1];
signed main() {
    fast;
    cin >> n;
    rep(i,1,n-1) cin >> a[i]; pre[0] = 1;
    rep(i,1,n-1) pre[i] = pre[i-1]*a[i]%mod;
    suf[n] = ns[n] = 1;
    per(i,n-1,1) suf[i] = suf[i+1]*a[i]%mod, ns[i] = ksm(suf[i], mod-2);
    rep(k,3,4*n-4) {
        if (k <= 2*n) {
            s[0] = 0;
            rep(i,1,n) {
                int j = k - i;
                if (1 <= j && j <= n) s[i] = (s[i-1]+ns[i]*ns[j]%mod)%mod;
                else s[i] = s[i-1];
            }
        }
        rep(i,1,n-1) {
            int j = k - 2*i;
            if (j < 1 || j > 2*n - 2) continue;
            int x = i+j-min(n-i,j-1), y = k - x, ret = 0;
            //利用前缀和 s[y]-s[x-1] 快速算一段 a[i]*(a[i]-1)/2 * suf^2 的贡献
            if (k <= 2*n && x <= y && x <= n && y <= n && x >= 1) {
                ret = (s[y] - s[x-1] + mod)%mod;
                ret = (a[i]*(a[i]-1)/2)%mod*suf[i+1]%mod*suf[i+1]%mod*ret%mod;
            }
            //i+j<=n 时附加一项
            if (i+j <= n) ret = (ret+suf[i]*ns[i+j]%mod)%mod;
            ans[j] = (ans[j]+ret*pre[i-1]%mod)%mod;
        }
    }
    rep(i,1,2*n-2) cout << ans[i] << ' ';
    return 0;
}