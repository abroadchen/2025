//
// Created by Psy.C on 2026/11/13.
//

/**
真正学会的起点..
pll 返回的 first = 满足条件的数字个数，second = 这些数字的数值之和（模意义下）。
d 是一个10 位位图（第 i 位=1 表示数字 i 已经出现过）。
数一遍"已出现的数字种类数"：
若超过 k → 返回 {0,0}（不可行）。
否则返回 {1,0}（可行，这里是供边界用的计数标记）
标准快速幂，用于计算 10^{len-1}，即某一位的位权（十进制下第 len 位的权值）
len：当前还剩多少位要填。
f：是否仍在填前导 0（f=1 表示还没出现过任何非零数字，前面都是前导零）。
st：已用数字的位图状态（10 位）。
返回值 pll：这一子树下满足条件的数字个数 和 数值之和。
注：N=1100 是状态位图范围（2^10=1024），足够装下 10 位状态
每个位从 0 填到 top。
若当前是前导 0（i==0 && f），数字集不变（st 不更新），f 仍为 1。
否则把 i 加入 st：st | (1<<i)，f 置 0。
每个子状态返回 (fst, snd)：fst 为数量，snd 为低位已有数字组成的数值和。
累加时：
res.first += fst（数量累加）；
res.second = snd（低位和）+ i × 10^{len-1} × fst（本位的数值贡献）
把上界 D 按十进制逐位拆入 a[]，a[1] 是最低位。
调用 dfs，只取 .second（总和）
用前缀和思想：[l,r] 的答案 = get(r) - get(l-1)（模意义下加 mod 取正）。
即统计不超过 r 的所有满足条件的数之和，减去不超过 l-1 的，得到区间内之和
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define pll pair<ll, ll>
using namespace std;

constexpr int N = 1100, mod = 998244353;

int k;
pll check(ll d) {
    int num = 0;
    for (int i = 0; i <= 9; i++) if (d&(1<<i)) {
        num++;
        if (num > k) return {0,0};
    }
    return {1,0};
}
ll ksm(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b&1) res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}

pll dp[20][2][N];
ll a[100];
pll dfs(ll b, ll len, int f, ll st, int lim) {
    pll res = {0,0};
    if (!check(st).first) return {0,0};//状态已超 k → 剪枝
    if (!len) return check(st);//填完所有位 → 返回计数(总和中加自身由上层处理)
    if (!lim && dp[len][f][st].first != -1) return dp[len][f][st];//记忆化
    int top = b-1;//位码上限（十进制 top=9）
    if (lim) top = a[len];//受上界约束时，取当前位可填的最大值
    for (ll i = 0; i <= top; i++) {
        if (i == 0 && f) {
            auto [fst, snd] = dfs(b,len-1,1,st,lim&&(i==top));
            res.first += fst; res.first %= mod;
            res.second = (res.second+snd+(fst*i%mod)*ksm(10,len-1)%mod)%mod;
        } else {
            auto [fst, snd] = dfs(b,len-1,0,st|(1<<i),lim&&(i==top));
            res.first += fst; res.first %= mod;
            res.second = (res.second+snd+(fst*i%mod)*ksm(10,len-1)%mod)%mod;
        }
    }
    if (!lim) dp[len][f][st] = res;
    return res;
}

ll get(ll b, ll d) {
    int res = 0;
    while (d) {
        a[++res] = d%b;
        d/=b;
    }
    return dfs(b,res,1,0,1).second;
}


int main() {
    fast;
    for (auto &i : dp)
        for (auto &j : i)
            for (auto &p : j) p = {-1,-1};
    ll b = 10, l, r; cin >> l >> r >> k;
    cout << (get(b,r)+mod-get(b,l-1))%mod << '\n';
    return 0;
}