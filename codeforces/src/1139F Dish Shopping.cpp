//
// Created by Psy.C on 2026/11/27.
//

/**
真正学会的起点..
N 是点的最大数量上限
T[2] 是两棵树状数组（BIT），数组实际大小开到 N<<2（4 倍），用于离散化后的值域
upd：单点更新，向右累加。
qry：前缀和查询（用 p &= p-1 技巧），返回 [1, p] 的累加和
vt（vector of tuple）：存了事件，第一维是数值 x（p 或 s 或 X），第二维是类型标记 -1/0/1，第三维是下标。
每个点的 p 记为插入事件（-1），s 记为删除事件（1），查询记为 0。
v 存的是需要离散化的关键值：b±p 和 X±Y，用于把 BIT 的下标压缩
按第一维（数值）排序后扫描，保证单调处理
遇到点（o 非 0）就在两棵 BIT 中把对应的离散化位置插入/删除。
遇到查询（o == 0）就用两棵 BIT 的差得到答案：前缀和(X+Y) − 前缀和(Y−X)

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1;i<=n;++i)
using namespace std;

constexpr int N = 1e5+5;

struct BIT {
    int t[N<<2];
    void upd(int p, int x) { for (; p < N<<2; p += p&-p) t[p] += x; }
    int qry(int p, int s=0) {
        for (; p; p &= p-1) s += t[p];
        return s;
    }
} T[2];
vector<int> v;
#define val(x) lower_bound(v.begin(), v.end(), x)-v.begin()+1//把真实数值映射为 1 起始的离散下标

int n, m, p[N], s[N], b[N], X[N], Y[N], ans[N];
vector<tuple<int,int,int>> vt;
int main() {
    fast;
    cin >> n >> m;
    rep(i,n) cin >> p[i], vt.emplace_back(p[i],-1,i);
    rep(i,n) cin >> s[i], vt.emplace_back(s[i],1,i);
    rep(i,n) cin >> b[i], v.push_back(b[i]+p[i]), v.push_back(b[i]-p[i]+1);
    rep(i,m) cin >> X[i], vt.emplace_back(X[i],0,i);
    rep(i,m) cin >> Y[i], v.push_back(X[i]+Y[i]), v.push_back(Y[i]-X[i]);
    ranges::sort(vt), ranges::sort(v);
    for (auto [x,o,i] : vt) {
        if (o) T[0].upd(val(b[i]+p[i]),-o), T[1].upd(val(b[i]-p[i]+1),-o);
        else ans[i] = T[0].qry(val(X[i]+Y[i]))-T[1].qry(val(Y[i]-X[i]));
    }
    rep(i,m) cout << ans[i] << ' ';
    return 0;
}