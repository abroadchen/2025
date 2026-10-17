//
// Created by Psy.C on 2026/10/16.
//
/**
从高位（i=1）到低位扫描，维护 inv = 当前所有确定的前缀位置两数相等的概率（即前面各位 a[i] 恰好等于 b[i] 的概率乘积）。一旦某位分出大小，之前相等的概率作为权重乘上本位的贡献加入 ans。
inv 初始为 1（一位都还没看，必相等）

情况 A：a[i] 和 b[i] 都已知（非 0）‍
若相等：continue，位置继续，inv 不变（仍相等概率 1）。
若 a[i] > b[i]：本位置第一个数更大，那么前缀相等的概率 inv 就全部贡献给"ans"（无需再乘概率，因为这两值已经确定且 a>b）；累加后 break（后面不用看了）。
若 a[i] < b[i]：直接 break，不贡献（因为 a 更小，不满足条件）。
第二个 break 在 if (a[i]>b[i]) 里，但 a[i]<b[i] 也会走到 break（因为 a[i]!=b[i] 进入分支，若不大于则小于，直接 break 不累加）。所以只要已知位不同就停。

情况 B：a[i]、b[i] 都未知（都为 0）‍
两未知：各自在 1..m 随机。a>b 的概率计算。候选对：a,b 独立的 m×m 组合。
新增贡献：m*(m-1)/2 / (m*m) 是 a>b 的概率（有序对中 a>b 的有 C(m,2)=m(m-1)/2 个），再乘前缀相等概率 inv。
代码写 m*(m-1) * ksm(m*m*2 % mod, mod-2) —— 即 m*(m-1) / (2*m*m) = (m-1)/(2m)，正是 P(a>b | 两者独立均匀)。
贡献 = (m-1)/(2m) * inv，模意义用乘法逆元 ksm(m*m*2, mod-2) 表示分母 2m² 的逆。
更新 inv：当前位置 a[i]==b[i] 的概率。两者都取到同一个值的概率 = m / (m*m) = 1/m（a 取某值，b 取相同值的概率为 1/m）。故 inv *= 1/m，即 inv * ksm(m, mod-2)。
情况 C：a[i] 未知（=0），b[i] 已知
a 未知、b=b[i] 已知。a 在 1..m 随机。
a > b[i] 的概率 = (m - b[i]) / m（a 取 b[i]+1 .. m 共 m-b[i] 个）。
贡献 = (m-b[i])/m * inv。
inv 更新：a[i]==b[i] 的概率 = a 恰好取到 b[i] 的概率 = 1/m。故 inv *= 1/m。
情况 D：a[i] 已知，b[i] 未知（=0）‍
a=a[i] 已知、b 未知。b 在 1..m 随机。
a > b 的概率 = (a[i]-1)/m（b 取 1..a[i]-1 共 a[i]-1 个）。
贡献 = (a[i]-1)/m * inv。
inv 更新：b[i]==a[i] 概率 = 1/m。inv *= 1/m。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
#define ll long long
using namespace std;

constexpr int N = 1e5+5, mod = 1e9+7;

ll ksm(ll x, int y) {
    ll res = 1;
    while (y) {
        if (y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}
int n, a[N], b[N];
ll m, inv(1), ans;
int main() {
    fast;
    cin >> n >> m;
    rep(i,1,n) cin >> a[i];
    rep(i,1,n) cin >> b[i];
    rep(i,1,n) {
        if (a[i]&&b[i]) {
            if (a[i] == b[i]) continue;
            if (a[i] > b[i]) ans = (ans+inv)%mod;
            break;
        }
        if (!a[i] && !b[i]) {
            ans = (ans+m*(m-1)%mod*ksm(m*m*2%mod, mod-2)%mod*inv%mod)%mod;
            inv = inv*ksm(m, mod-2)%mod;
        } else if (!a[i]) {
            inv = inv*ksm(m, mod-2)%mod;
            ans = (ans+(m-b[i])*inv%mod)%mod;
        } else {
            inv = inv*ksm(m, mod-2)%mod;
            ans = (ans+(a[i]-1)*inv%mod)%mod;
        }
    }
    cout << ans;
    return 0;
}