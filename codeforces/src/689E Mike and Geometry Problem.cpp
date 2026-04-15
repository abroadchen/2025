//
// Created by Psy.C on 2026/4/15.
//
/**
pos：事件发生的位置（区间端点）
pre：区间另一个端点
f：事件类型（1=区间开始，0=区间结束）
排序规则：按位置升序，若位置相同则开始事件优先

输入：n个区间和选择k个的要求
事件创建：每个区间[l,r]生成开始事件(l,r,1)和结束事件(r,l,0)
排序：按扫描线顺序排列所有事件

num：当前活跃区间数量
t：上一个关键时间点
区间开始事件：
如果活跃区间不足k个，直接增加
否则，在增加前先结算当前段的贡献
区间结束事件：
如果活跃区间不足k个，直接减少
否则，先结算当前段的贡献，再减少

扫描线思想：从左到右扫描区间端点
组合数学：在每个时间段，如果有num个活跃区间，从中选k个的方案数是C(num,k)
贡献计算：时间段长度 × 选k个区间的方案数

排序：O(n log n)
扫描：O(n)
总体：O(n log n)

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+5, mod = 1e9+7;

struct edge {
    int pos, pre, f;
    bool operator<(const edge& o) const {
        if (pos == o.pos) return f > o.f;
        return pos < o.pos;
    }
} p[N<<1];

ll ksm(ll a, ll n) {
    ll ans = 1;
    while (n) {
        if (n&1) ans = ans*a%mod;
        a = a*a%mod;
        n >>= 1;
    }
    return ans;
}

ll fac[N];
ll C(int n, int m) {
    return fac[n]*ksm(fac[m], mod-2)%mod*ksm(fac[n-m], mod-2)%mod;
}

int n, k;
int main() {
    fast;
    fac[0] = 1;
    for (int i = 1; i <= N-5; ++i) fac[i] = fac[i-1]*i%mod;
    cin >> n >> k;
    for (int i = 0, l, r; i < n; ++i) {
        cin >> l >> r;
        p[i<<1] = {l, r, 1};
        p[i<<1|1] = {r, l, 0};
    }
    sort(p, p+2*n);
    ll ans = 0;
    for (int i = 0, num = 0, t = 0; i < 2*n; ++i) {
        if (p[i].f) {
            if (num < k) { num++; t = p[i].pos; }
            else {
                ans = (ans+(ll)(p[i].pos-t)*C(num, k)%mod)%mod;
                t = p[i].pos;
                num++;
            }
        } else {
            if (num < k) num--;
            else {
                ans = (ans+(ll)(p[i].pos-t+1)*C(num, k)%mod)%mod;
                t = p[i].pos + 1;
                num--;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}