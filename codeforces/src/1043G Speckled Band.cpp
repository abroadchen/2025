//
// Created by Psy.C on 2026/11/6.
//

/**
真正学会的起点..
v1/v2 是字符串 前缀哈希，pw是bs的幂，模两个质数 m1、m2 → 双哈希防碰撞。
check 比较两个子串是否相等（O(1)），get 取哈希对——供二分检查用。
标准倍增后缀数组，第一关键字 rk[x]，第二 rk[x+k]（越界看作 0）。
rk[] 为排名，sa[] 为后缀排序
getL：从左端往左能匹配多长（比较 a[x-md+1..x] 与 a[y-md+1..y]）。
getR：从 x 往右能匹配多长（比较 a[x..x+md-1] 与 a[y..y+md-1]）。
用双哈希二分，O(log n) 每段。
对每个界点 i*len，比较它左右两侧是否"以 len 为周期重复"（getL+getR 的长度相消）。
若 l1+l2-1 ≥ len → 存在周期 len，则把该片段的中点区间写入数组
f[l]：位置 l 所在的"以周期 p 重复片段"的右端点l+2p-1。
g[l]：左端点 l-2p+1。
语义：f[l] 表示从 l 起向右至少重复到哪；g[l] 表示向左延伸到哪——表示 l 处的字符属于某个周期≥某长度的"重复结构"
用于后面 query(1,1,n,l,r) <= r 判"N 次方"。
sum[26][N] 前缀字符计数：chk|=i[r]-i[l-1]>=2。若区间内每种字符都只出现 ≤1 次（无重复）→ 输出 -1（非周期串）。

枚举 len 判断整段是否可由更小周期拼成：
若成立 → 输出 1（区间本身是某种更高次方幂）。

f[l]<=r || g[r]>=l：l 位于某个内嵌整周期片段且该片段延伸覆盖 r，或 g 同理 → 输出 2。

半周期搜索（启发式）
这一步是近似 LCP / "几乎整周期"的二分偏置检查，用来判定 2 次方幂。
命中 → 输出 2。
3 次方判定（弱周期）
任一成立 → 输出 3。

兜底 → 输出 4
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= n; i++)
#define ll unsigned long long
#define ii pair<ll,ll>
#define mid ((l+r)>>1)
using namespace std;

constexpr int N = 2e5+5, inf = 1e9+7, bs = 1313113, m1 = 998244353, m2 = 147744151;

ll pw1[N], pw2[N], v1[N], v2[N];
inline bool check(int p1, int p2, int len) {
    ll t1 = (v1[p1+len-1]-v1[p1-1]*pw1[len]%m1+m1)%m1;
    ll t2 = (v1[p2+len-1]-v1[p2-1]*pw1[len]%m1+m1)%m1;
    if (t1 != t2) return false;
    t1 = (v2[p1+len-1]-v2[p1-1]*pw2[len]%m2+m2)%m2;
    t2 = (v2[p2+len-1]-v2[p2-1]*pw2[len]%m2+m2)%m2;
    if (t1 != t2) return false;
    return true;
}
inline ii get(int p1, int len) {
    ll t1 = (v1[p1+len-1]-v1[p1-1]*pw1[len]%m1+m1)%m1;
    ll t2 = (v2[p1+len-1]-v2[p1-1]*pw2[len]%m2+m2)%m2;
    return {t1, t2};
}

int n, sa[N<<1], rk[N<<1], rk2[N<<1];
char a[N];
inline void SA() {
    if (n == 1) return void(sa[1]=rk[1]=1);
    rep(i,n) sa[i] = i, rk[i] = a[i];
    for (int k = 1; k <= n; k <<= 1) {
        sort(sa+1,sa+1+n,[&](int x, int y) {
            return make_pair(rk[x], rk[x+k]) < make_pair(rk[y], rk[y+k]);
        });
        rk2[sa[1]] = 1;
        int now = 1;
        rep(i,n) rk2[sa[i]] = (make_pair(rk[sa[i-1]], rk[sa[i-1]+k]) ==
            make_pair(rk[sa[i]], rk[sa[i]+k]) ? now : ++now);
        rep(i,n) rk[i] = rk2[i];
    }
}

inline int getL(int x, int y) {
    int len = y - x, l = 1, r = len, res = 0;
    while (l <= r) {
        if (check(x-mid+1,y-mid+1,mid)) res = mid, l = mid+1;
        else r = mid-1;
    }
    return res;
}
inline int getR(int x, int y) {
    int len = y - x, l = 1, r = min(len,n-y+1), res = 0;
    while (l <= r) {
        if (check(x,y,mid)) res = mid, l = mid+1;
        else r = mid-1;
    }
    return res;
}

int f[N];
struct node {
    int t[N<<2];
    void modify(int x, int l, int r, int L, int R, int p) {
        if (t[x] == r-l+1) return;
        if (l == r) { t[x] = 1; f[l] = l+p*2-1; return; }
        if (mid >= L) modify(x<<1, l, mid, L, R, p);
        if (mid < R) modify(x<<1|1, mid+1, r, L, R, p);
        t[x] = t[x<<1] + t[x<<1|1];
    }
} F;

int t[N<<2];
void build(int x, int l, int r) {
    if (l == r) return void(t[x]=f[l]);
    build(x<<1, l, mid); build(x<<1|1, mid+1, r);
    t[x] = min(t[x<<1], t[x<<1|1]);
}
int query(int x, int l, int r, int L, int R) {
    if (L <= l && r <= R) return t[x];
    int res = inf;
    if (mid >= L) res = query(x<<1, l, mid, L, R);
    if (mid < R) res = min(res, query(x<<1|1, mid+1, r, L, R));
    return res;
}

int g[N];
struct node2 {
    int t[N<<2];
    void modify(int x, int l, int r, int L, int R, int p) {
        if (t[x] == r-l+1) return;
        if (l == r) { t[x] = 1; g[l] = l-p*2+1; return; }
        if (mid >= L) modify(x<<1, l, mid, L, R, p);
        if (mid < R) modify(x<<1|1, mid+1, r, L, R, p);
        t[x] = t[x<<1] + t[x<<1|1];
    }
} G;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int sum[26][N], q;
int main() {
    fast;
    n = rd(); scanf("%s", a+1); SA(); pw1[0] = pw2[0] = 1;
    rep(i,n) {
        f[i] = inf, g[i] = -inf;
        pw1[i] = pw1[i-1]*bs%m1; pw2[i] = pw2[i-1]*bs%m2;
        v1[i] = (v1[i-1]*bs+a[i])%m1; v2[i] = (v2[i-1]*bs+a[i])%m2;
        for (auto &j : sum) j[i] = j[i-1];
        sum[a[i]-'a'][i]++;
    }
    rep(len,n) for (int i = 2; i*len <= n; i++) {
        int l1 = getL((i-1)*len, i*len), l2 = getR((i-1)*len, i*len);
        if (l1+l2-1 >= len) {
            int L = (i-1)*len-l1+1, R = (i-1)*len+l2-len;
            F.modify(1,1,n,L,R,len);
            L += len*2-1; R += len*2-1;
            G.modify(1,1,n,L,R,len);
        }
    }
    build(1,1,n);
    q = rd();
    while (q--) {
        int l = rd(), r = rd(), chk = 0;
        for (auto &i : sum) chk |= i[r]-i[l-1]>=2;
        if (!chk) { cout << "-1\n"; continue; }
        chk = 0;
        for (int len = 1; len*len <= r-l+1; len++)
            if ((r-l+1)%len == 0) {
                if (check(l,l+len,r-l+1-len)) { chk = 1; break; }
                int Len = (r-l+1)/len;
                if (Len < r-l+1 && check(l,l+Len,r-l+1-Len)) { chk = 1; break; }
            }
        if (chk) { cout << "1\n"; continue; }
        int ok = f[l] <= r || g[r] >= l;
        if (ok) { cout << "2\n"; continue; }
        const int B = min(400, r-l+1);
        for (int len = 1; len*2 <= B; len++)
            if (check(l,r-len+1,len)) { ok = 1; break; }
        if (!ok) {
            for (int i = max(1,rk[l]-B); i <= min(n,rk[l]+B); i++) {
                if (sa[i] <= l || sa[i] > r) continue;
                if (check(l,sa[i],r-sa[i]+1)) { ok = 1; break; }
            }
        }
        if (ok) { cout << "2\n"; continue; }
        if (query(1,1,n,l,r) <= r || sum[a[l]-'a'][r]-sum[a[l]-'a'][l] ||
            sum[a[r]-'a'][r-1]-sum[a[r]-'a'][l-1]) {
            cout << "3\n"; continue;
        }
        cout << "4\n";
    }
    return 0;
}