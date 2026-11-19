//
// Created by Psy.C on 2026/11/19.
//

/**
真正学会的起点..
标准的 O(n log n) SA 倍增实现，返回 {sa, rk, ht}
base/sigma：字符集范围，用于计数排序的桶大小。
第一次按单字符桶排得到初始 sa，再由相邻后缀首字符是否相等赋初值 rk（第一关键字排名）。
注意 rk 用"是否与前一个 sa 的后缀相同"来决定是否 +1，使 rk 值域变成 [1, 不同字符种数]
倍增 k：每轮按 (第一关键字=rk[i], 第二关键字=rk[i+k]) 排序。
sec 先放第二关键字为空的后缀（位置 > n-k），然后按sa顺序取 sa[i]-k 生成第二关键字序列。
计数排序（稳定）由第二关键字序列配合 rk 桶排重建 sa。
用上一轮 lst 判断 (rk1, rk2) 是否完全相同来赋新 rk（pair 比较）。
rk[sa[n]] == n 表示所有排名已唯一，提前退出
经典性质：ht[rk[i]] = LCP(后缀i, 排在它前一个的后缀)。
利用"排名相邻的 LCP ≥ h-1"的性质（if(h)--h）使总复杂度 O(n)。
用于后面 a[i] 的 min 传递
支持清空只需把版本号 T+1（惰性清空，O(1)），避免 O(n) 重建。
add/qry：标准 BIT，但只在"当前版本"的节点上读写。
三个 BIT t1,t2,t3 分别存：(和)、(个数)、(位置和)，服务于两种 handle 统计
对右半边：a[sa[i]] = 从 mid+1 到 i 的 ht 的最小值 = "以 sa[i] 开头的后缀在 [mid+1..i] 这段内与相邻后缀的 LCP 下界"（即该起点后缀的某个"限制长度"）。
对左半边：a[sa[i]] = 从 i 到 mid 的 ht 最小值。
s1 存左边起点的位置（从 mid 往 l），s2 存右边起点的位置
对询问 [l,r]（其左端点 l 在 y 侧），a[l] 是该起点的 LCP 限制。
求出分界点 p = min(r, max(l-1, r+1-a[l]))，把区间按 a[l] 的限制切成两段，各自用差分容斥（{...,-1,id} 与 {...,1,id}）挂进 v1/v2。
v1 记录 a[l] 值本身（min 在内部），v2 记录 r 值（min 在 r 附近）
把 x 侧的位置也放进事件列表（id=0 是插入点，非查询）
按第一维（位置/下标）排序，保证扫描顺序。u[3]（id）作为次级排序确保插入点先处理
扫描 v1（按下标排序）：插入 x 侧点（按 a[i] 位置加入 BIT），对查询累计贡献 t1.qry(i)（值 ≤ i 的和）加上"值 > i 的个数 × i"——即 min(a[pos], i) 的求和，乘差分系数 t[2]
扫描 v2：按 a[i]+i（r 相关键）插入，查询时用三个 BIT 组合出 min(r, pos+... ) 型贡献，同样乘差分系数。
两个 handle 求和就是跨 mid 询问的完整贡献。
先递归左右，再处理跨 mid 的询问。总体复杂度 O(n log² n) 级别。
字符串后移一格让下标 1-based。
lk[l]：以 l 为左端点的询问列表，用于分治时快速取到询问。
ans[i] 初始化为 r-l+1（长度 1 的子串），分治在其上累加更长子串贡献


① sec[i]
第 i 个待排序的后缀起点位置（i 从 n-1 倒着走到 0）。
② rk[sec[i]]
这个后缀目前的第1关键字（即其 rank 值，一个桶编号）。
③ cnt[rk[sec[i]]]
cnt 经过前缀和后，cnt[r] 表示"第1关键字 ≤ r 的后缀的总个数"。
所以 cnt[rk[sec[i]]] 表示：第1关键字值和 sec[i] 相等（或更小）的后缀总个数——这个数正好可作为该桶的"尾部下标"。
④ sa[ ... ] --
cnt[桶号]-- 是先取用 cnt[桶号] 的当前值，再把它 减 1。
作用：让同一桶里的元素从桶的尾部往头部依次填入。
⑤ = sec[i]
把这个后缀的起点位置写进 sa 的第 cnt 个位置。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define int long long
#define vi vector<int>
using namespace std;

constexpr int N = 2e5+10, M = 4e5+10, inf = 1.1e18;
array<vi,3> build(int n, char *s) {
    int base = *min_element(s+1,s+n+1);
    int sigma = *max_element(s+1,s+n+1)-base+1;
    vi cnt(max(sigma,n+1)), sa(n+1), rk(n+1);
    rep(i,n) ++cnt[s[i]-base];
    rep(i,sigma-1) cnt[i] += cnt[i-1];
    rep(i,n) sa[cnt[s[i]-base]--] = i;
    rep(i,n) rk[sa[i]] = rk[sa[i-1]] + (i==1||s[sa[i]]!=s[sa[i-1]]);
    for (int k = 1; k < n; k *= 2) {
        vi sec;
        for (int i = n-k+1; i <= n; i++) sec.emplace_back(i);
        rep(i,n) if (sa[i] > k) sec.emplace_back(sa[i]-k);
        ranges::fill(cnt, 0);
        rep(i,n) ++cnt[rk[i]];
        rep(i,n) cnt[i] += cnt[i-1];
        for (int i = n-1; ~i; i--) sa[cnt[rk[sec[i]]]--] = sec[i];
        auto lst = rk;
        rep(i,n) rk[sa[i]] = rk[sa[i-1]]+(i==1||lst[sa[i]]!=lst[sa[i-1]]||
            (sa[i]<=n-k?lst[sa[i]+k]:0)!=(sa[i-1]<=n-k?lst[sa[i-1]+k]:0));
        if (rk[sa[n]] == n) break;
    }
    vi ht(n+1);
    for (int i = 1, h = 0; i <= n; i++) {
        if (rk[i] == 1) continue;
        if (h) --h;
        int j = sa[rk[i]-1];
        while (h <= n-max(i,j) && s[i+h] == s[j+h]) ++h;
        ht[rk[i]] = h;
    }
    return {sa,rk,ht};
}

int n;
struct BIT {
    int T, t[M], w[M];
    void clear() { ++T; }
    void add(int i, int x) {
        for (++i; i <= 2*n+1; i += i&-i) {
            if (t[i] != T) t[i] = T, w[i] = x; else w[i] += x;
        }
    }
    int qry(int i) {
        int ans = 0;
        for (++i; i; i -= i&-i)
            if (t[i] == T) ans += w[i];
        return ans;
    }
} t1, t2, t3;

int a[N], ql[N], qr[N], ans[N];
vi sa, ht, lk[N];
void solve(int l, int r) {
    if (l == r) return;
    int mid = (l+r)>>1;
    solve(l,mid); solve(mid+1,r);
    vi s1, s2;
    for (int i = mid+1; i <= r; i++) {
        a[sa[i]] = min(i==mid+1?inf:a[sa[i-1]], ht[i]);
        s2.emplace_back(sa[i]);
    }
    for (int i = mid; i >= l; i--) {
        a[sa[i]] = min(i==mid?inf:a[sa[i+1]], ht[i+1]);
        s1.emplace_back(sa[i]);
    }
    auto handle = [&](vi x, vi y) {
        vector<array<int,4>> v1,v2;
        for (auto l : y) for (auto id : lk[l]) {
            assert(ql[id] == l);
            int r = qr[id], p = min(r,max(l-1,r+1-a[l]));
            if (l <= p) {
                v1.push_back({l-1,a[l],-1,id});
                v1.push_back({p,a[l],1,id});
            }
            if (p < r) {
                v2.push_back({r,r,1,id});
                v2.push_back({p,r,-1,id});
            }
        }
        for (auto i : x) {
            v1.push_back({i,a[i],0,0});
            v2.push_back({i,a[i],0,0});
        }
        ranges::sort(v1, [&](auto u, auto v) {
            return u[0] != v[0] ? u[0] < v[0] : u[3] < v[3];
        });
        ranges::sort(v2, [&](auto u, auto v) {
            return u[0] != v[0] ? u[0] < v[0] : u[3] < v[3];
        });
        t1.clear(); t2.clear();
        for (auto t : v1) {
            int id = t[3];
            if (!id) {
                int i = t[0]; t1.add(a[i],a[i]); t2.add(a[i],1);
            } else {
                int i = t[1]; ans[id] += (t1.qry(i)+(t2.qry(2*n)-t2.qry(i))*i)*t[2];
            }
        }
        t1.clear(); t2.clear(); t3.clear();
        for (auto t : v2) {
            int id = t[3];
            if (!id) {
                int i = t[0]; t1.add(a[i]+i,a[i]); t2.add(a[i]+i,1); t3.add(a[i]+i,i);
            } else {
                int i = t[1]; ans[id] += (t1.qry(i+1)+(t2.qry(2*n)-t2.qry(i+1))*(i+1)-(t3.qry(2*n)-t3.qry(i+1)))*t[2];
            }
        }
    };
    handle(s1, s2); handle(s2, s1);
}

char s[N];
int q;
vi rk;
void out() {
    cin >> s; n = strlen(s);
    for (int i = n; i; --i) s[i] = s[i-1];
    cin >> q;
    auto t = build(n,s);
    sa = t[0], rk = t[1], ht = t[2];
    for (int i = 1, l, r; i <= q; i++) {
        cin >> l >> r; ql[i] = l, qr[i] = r; lk[l].emplace_back(i);
        ans[i] = r-l+1;
    }
    solve(1,n);
    rep(i,q) cout << ans[i] << '\n';
}


signed main() {
    fast;
    out();
    return 0;
}