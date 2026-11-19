//
// Created by Psy.C on 2026/11/19.
//

/**
真正学会的起点..
叶子存该位置的数组值；
内部节点存左右子树 gcd；
单点更新后，沿路径向上重算 gcd
完全覆盖则直接返回节点 gcd；
否则递归两半求出的 gcd 再合并（初值 0，gcd(0,x)=x）
标准类欧几里得递归：
a<0：把 a 抬成非负（同时减掉多出的常数项）。
a==0：化简为常数项 (b/c)×(lim+1)。
a>=c 或 b>=c：拆出整数部分（(a/c)*(lim)(lim+1)/2 与 (b/c)*(lim+1)），把 a,b 取模后递归。
否则（0<a,b<c）利用对称式 lim*m - init(...) 反转参数递归——这就是类欧的"交换"技巧，使规模快速缩小。
典型 O(log) 类欧几里得求和
C++ 的 / 对负数向零取整，这里实现向下取整：负数且不能整除时多减 1。
统计满足条件 a*u + b*v <= c（u∈[0,l1], v∈[0,l2]）的整数对 (u,v) 数量。
拆成：u 直接取时的贡献 l1+1，v 的贡献 (cd+1)*l2，再用类欧 init 精确补上 v 部分的计数。
这是题目里"统计某个 gcd g 的出现次数时所需的不等式计数"
统计 min(b/a,c) 相关的一个多项式计数（min(i, b/a) 的累积），用于快速算单值贡献的整段块。
第一段：单 gcd 值 g 自己贡献 co 块。
第二段：双 pointer（l, r）枚 gcd 值，维护 sum（加权前缀和）和 sb（计数前缀和），对能合成的不同 gcd 组合用 oc 计数（类欧统计满足不等式限制的 case）。
返回 gcd 值 ≤ lim 的子区间数量。这是二分判定用的核心函数
每插入位置 i 的值 x 后（单点更新线段树），向左二分跳段：
找"以 y 为左端点、i 为右端点"的一段里 gcd 相同的最左边界，把这段长度 z-y+1 加进 b[gcd]。
因为 gcd 随左端点变化是"分段恒定"的，用二分+区间 gcd 一次跳过整段。这样 O(n log n log V) 统计出所有子区间 gcd 的出现次数存入 b
sb：gcd 值出现次数的前缀和；
sum：gcd 值加权（×值）前缀和，供 calc 用
res = n(n+1)/2 × (n(n+1)/2 + 1)/2 是"所有子区间 gcd 构成的序列"（长度为 n(n+1)/2）的总长 × (总长+1)/2，用于定位中位数在第几个。
在 gcd 值域上 [1, (C-5)*n(n+1)/2] 二分 ans：若 calc(mid)+1 <= (res+1)/2（gcd ≤ mid 的个数足够覆盖中位位置）则中位数解 ≤ mid，否则在更大值域找。最终 ans 即中位 gcd 值
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
#define ll long long
using namespace std;

constexpr int N = 1e5+4e4, M = 5e4+10, C = 1e5+5;

namespace sgt {
    int t[N];
    void upd(int x, int l, int r, int pos, int v) {
        if (l == r) { t[x] = v; return; }
        int mid = (l+r)>>1;
        if (pos <= mid) upd(x<<1,l,mid,pos,v);
        else upd(x<<1|1,mid+1,r,pos,v);
        t[x] = __gcd(t[x<<1], t[x<<1|1]);
    }
    int qry(int x, int l, int r, int L, int R) {
        if (L <= l && r <= R) return t[x];
        int ret = 0, mid = (l+r)>>1;
        if (L <= mid) ret = __gcd(ret, qry(x<<1,l,mid,L,R));
        if (mid < R) ret = __gcd(ret, qry(x<<1|1,mid+1,r,L,R));
        return ret;
    }
}

namespace Ju {
    ll init(ll lim, ll a, ll b, ll c) {
        if (a < 0) {
            ll pl = -((a+1)/c-1);
            return init(lim,a+pl*c,b,c)-pl*lim*(lim+1)/2;
        }
        if (a == 0) return (lim+1)*(b/c);
        if (a >= c || b >= c)
            return init(lim,a%c,b%c,c)+(a/c)*lim*(lim+1)/2+(b/c)*(lim+1);
        ll m = (a*lim+b)/c;
        return lim*m-init(m-1,c,c-b-1,a);
    }
    ll div(ll x, ll y) {
        if (x >= 0) return x/y;
        return x%y?x/y-1:x/y;
    }
    ll oc(ll a, ll b, ll l1, ll l2, ll c) {
        if (l1 < 0 || l2 < 0 || c < 0) return 0;
        l1 = min(l1, c/a);
        ll ret = l1+1, cd = min(max(div(c-b*l2,a),-1ll),l1);
        ret += (cd+1)*l2; ret += init(l1,-a,c,b);
        if (cd > -1) ret -= init(cd,-a,c,b);
        return ret;
    }
    ll co(ll a, ll b, ll c) {
        ll num = b/a;
        if (num > c) return c*(c+1)/2;
        return (c-num)*num+num*(num+1)/2;
    }
}

ll b[C], sb[C], sum[C];
ll calc(ll lim) {
    ll ret = 0;
    for (int i = 1; i <= C-5; ++i)
        if (b[i]) ret += Ju::co(i,lim-1,b[i]);
    for (int l = 1, r = 1; l < C-5; ++l) {
        if (!b[l]) continue;
        if (l < r) ret += b[l]*(sb[r-1]-sb[l]);
        for (; r <= C-5 && sum[r]-sum[l] < lim; ++r)
            if (l!=r && b[r]) ret += Ju::oc(l,r,b[l]-1,b[r]-1,lim-1-(sum[r-1]-sum[l])-l-r);
        if (r <= C-5) {
            if (l!=r && b[r]) ret += Ju::oc(l,r,b[l]-1,b[r]-1,lim-1-(sum[r-1]-sum[l])-l-r);
        }
    }
    return ret;
}

int n, pre[C];
int main() {
    fast;
    cin >> n;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        int y = i; sgt::upd(1,1,n,i,x);
        while (y) {
            int z = y;
            for (int l = 1, r = y, mid=(l+r)>>1; l <= r; mid=(l+r)>>1) {
                if (sgt::qry(1,1,n,mid,i)==sgt::qry(1,1,n,y,i))
                    y = mid, r = mid-1;
                else l = mid+1;
            }
            b[sgt::qry(1,1,n,y,i)] += z-y+1;
            --y;
        }
    }
    rep(i,C-5) { sb[i] = sb[i-1] + b[i]; sum[i] = sum[i-1] + b[i]*i; }
    int p = 0;
    rep(i,C-5) if (b[i]) { pre[i] = p; p = i; }
    ll res = (ll)n*(n+1)/2, ans = 0;
    res = res*(res+1)/2;
    for (ll l = 1, r = (ll)(C-5)*n*(n+1)/2, mid = (l+r)>>1; l <= r; mid = (l+r)>>1) {
        if (calc(mid)+1 <= (res+1)/2) ans = mid, l = mid+1;
        else r = mid-1;
    }
    cout << ans;
    return 0;
}