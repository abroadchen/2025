//
// Created by Psy.C on 2026/11/2.
//

/**
真正学会的起点..
普通链式哈希表，val 存键、tot 存出现次数。
定义 mp[15]：15 个独立的哈希表，分别对应数字长度 1-15
p[i] = 10^i mod k，用于拼接时计算进位模。
lg[i] 记录 a[i] 的位数
mp[i] 存的是：把 a[j] 当作拼接后的前段、并需在其后面补 i 位时，该前段对 k 的模值 a[j]%k * p[i] % k（即前段乘以
10
i
10
i
 ）。
这样按"后续位数 i"建立索引
拼接 X·a[i]（X 是前段、长度为 m）可被 k 整除 ⟺ (X*10^m + a[i]) mod k == 0 ⟺ X*10^m ≡ (-a[i]) mod k。
t 即所需 X*10^m mod k 的值。
用 mp[lg[i]].find(t) 数出满足条件的前段 X 个数。
若 i 自身拼接 a[i] 也成立，需减掉一对（题目若要求 i≠j）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1;i<=n;i++)
#define ll long long
using namespace std;

constexpr int N = 2e5+5, mod = 1e4+7;

struct ham {
    int head[N]{}, nxt[N]{}, cnt;
    ll val[N]{}, tot[N]{};
    ham() {
        cnt = 0;
        memset(head, 0, sizeof(head));
        memset(nxt, 0, sizeof(nxt));
        memset(val, 0, sizeof(val));
        memset(tot, 0, sizeof(tot));
    }
    void insert(ll x) {
        ll k = x % mod;
        for (int i = head[k]; i; i = nxt[i])
            if (val[i] == x) { tot[i]++; return; }
        nxt[++cnt] = head[k]; head[k] = cnt;
        val[cnt] = x; tot[cnt] = 1;
    }
    ll find(ll x) const {
        ll k = x % mod;
        for (int i = head[k]; i; i = nxt[i])
            if (val[i] == x) return tot[i];
        return 0;
    }
} mp[15];

ll n, k, p[20], a[N], lg[N];
int main() {
    fast;
    cin >> n >> k; p[0] = 1;
    rep(i,10) p[i] = p[i-1]*10%k;
    rep(i,n) {
        cin >> a[i];
        ll t = a[i];
        while (t) { lg[i]++; t /= 10; }
    }
    rep(i,10) rep(j,n) mp[i].insert(a[j]%k*p[i]%k);//数字 a[j] 后拼接 i 个 0(即作为"前段尾部")
    ll t, ans = 0;
    rep(i,n) {
        t = ((k-a[i])%k+k)%k;//后段 a[i] 需要的"前段补零后的模"
        ans += mp[lg[i]].find(t);//在对应位数哈希表中查找
        if ((a[i]%k*p[lg[i]]%k+a[i]%k)%k == 0) ans--;//排除 i==j 自身
    }
    cout << ans << '\n';
    return 0;
}