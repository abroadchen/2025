//
// Created by Psy.C on 2026/11/14.
//

/**
真正学会的起点..
递归二分，直到深度达到 k 或区间只剩单点。
把"终止时区间长度"记录下来：len[0] 存第一个长度，len[1] 存第二个不同的长度（通常分治后只会出现两种长度，比如 2^a 与 2^a-1 之类的相邻两档）。
cnt[长度]++ 统计每种长度区间的个数
p 是模数；用标准线性递推求 1..p-1 的模逆元。
sum[i] = Σ inv[j]（调和数前缀和的模意义版本）
若 l==0 或 r==0 直接返回 0。
否则结果 = l·r/2 减去一串 (sum[r+i]-sum[i]) 的和。
这里的 sum[r+i]-sum[i] 正是 Σ_{j=i+1}^{i+r} inv[j]（调和数区间和），累加 i=1..l。
用到的组合系数：

len*(len-1)/2 = C(len,2)，再乘 cnt[长度]（该长度的区间数），配 inv[4]（即 1/4）。
cnt*(cnt-1)/2 = 两区间组合，乘 get(同长度) 或 get(跨长度)。
总的形式是：对同类长度区间内部 + 不同长度区间之间做某种加权求和，权重来自 get()
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 1e5+10;

int k;
ll len[2], cnt[N];
void build(int l, int r, int dep) {
    if (dep == k || l == r) {
        if (!len[0]) len[0] = r - l + 1;
        if (r-l+1 != len[0] && !len[1]) len[1] = r - l + 1;
        cnt[r-l+1]++;
        return;
    }
    int mid = (l+r)>>1;
    build(l, mid, dep+1); build(mid+1, r, dep+1);
}

ll p, inv[N], sum[N];
ll get(ll l , ll r) {
    ll res = l*r%p*inv[2]%p;
    if (!l || !r) return 0ll;
    rep(i,l) res = ((res-sum[r+i]+sum[i])%p+p)%p;
    return res;
}

int n;
int main() {
    fast;
    cin >> n >> k >> p; inv[1] = 1;
    for (int i = 2; i < N; i++) inv[i] = (p-p/i)*inv[p%i]%p;
    rep(i,n) sum[i] = (sum[i-1]+inv[i])%p;
    build(1, n, 1);
    ll ans = len[0]*(len[0]-1ll)%p*cnt[len[0]]%p*inv[4]%p;
    (ans += len[1]*(len[1]-1ll)%p*cnt[len[1]]%p*inv[4]%p) %= p;
    (ans += cnt[len[0]]*(cnt[len[0]]-1ll)%p*inv[2]%p*get(len[0],len[0])%p) %= p;
    (ans += cnt[len[1]]*(cnt[len[1]]-1ll)%p*inv[2]%p*get(len[1],len[1])%p) %= p;
    (ans += cnt[len[1]]*cnt[len[0]]%p*get(len[0],len[1])%p) %= p;
    cout << ans << '\n';
    return 0;
}