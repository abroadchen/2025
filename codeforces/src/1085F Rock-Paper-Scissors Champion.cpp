//
// Created by Psy.C on 2026/11/15.
//

/**
真正学会的起点..
tr[c][x]：阵营 c 在位置 x 上有没有元素（0/1），用 BIT 维护每个阵营的位置分布，支持单点加减与区间求和
4 棵 BIT，tr[1..3] 分别对应 R/P/S
L[t]：t 输给的阵营（能赢 t 的）
W[t]：t 赢的阵营
t=R(1): L=2(P)，W=3(S)。P 胜 R ✓，R 胜 S ✓。
t=P(2): L=3(S)，W=1(R)。S 胜 P ✓，P 胜 R ✓。
t=S(3): L=1(R)，W=2(P)。R 胜 S ✓，S 胜 P ✓。
st[c] 保存阵营 c 出现的位置（有序）

t 能"赢"的，只能是那些没被能赢 t 的那一方覆盖的…… 更准确地说，这里统计的是 t 阵营中，"能作为获胜对里获胜那一方"的位置数，且要排除掉被 L[t]（能赢 t 的阵营）在区间上"压制"的情况。
提取出两个"夹在 L 和 W 之间的位置区间"：

[ls+1, wn]：介于最左边的 L 和最左边的 W 之间
[wn+1... ls-1] 即 [wn, ls-1]：介于最右的 W 和最右的 L 之间
tt = 阵营 t 落在这两个夹逼区间内的数量；减去重叠后，st[t].size() - tt = t 阵营中不在这两个压制区间内的数——这些就是能贡献获胜的位置数。

直觉：阵营 t 的位置若被"既能被 L 压、又有 W 可赢"的部分包围，则不计数；只有那些能稳定获胜的位置才返回。具体正确性依赖题目对"配对/获胜"的几何定义（大概是"两两匹配，求能赢的最大对数或计数"）。
每个查询是单点替换字符：从旧阵营 BIT/set 删、新阵营 BIT/set 插，然后重新对三个阵营各调一次 gt() 求和输出
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= n; i++)
#define ll long long
using namespace std;

constexpr int N = 1e6+10;

int low_bit(int x) { return x&-x; }

ll tr[4][N], n;
void add(ll c, ll x, ll v) { for (ll i = x; i <= n; i += low_bit(i)) tr[c][i] += v; }
ll sum(ll c, ll x) {
    ll r = 0;
    for (ll i = x; i; i -= low_bit(i)) r += tr[c][i];
    return r;
}
ll query(ll c, ll l, ll r) {
    if (l > r) return 0;
    return sum(c,r) - sum(c,l-1);
}

set<ll> st[4];
ll L[] = {-1,2,3,1}, W[] = {-1,3,1,2};
ll gt(ll t) {
    ll c1 = st[L[t]].size();//能打过 t 的阵营的数量
    if (!c1) return st[t].size();//该阵营为空 → 输入 t 全部算获胜
    ll c2 = st[W[t]].size();//t 能赢的阵营的数量
    if (!c2) return 0;//t 赢的阵营空 → t 无获胜
    ll l1 = 1, r1 = 0, l2 = 1, r2 = 0;
    ll ls = *st[L[t]].begin(), wn = *st[W[t]].begin();
    if (wn > ls) { l1 = ls + 1; r1 = wn; }
    ls = *st[L[t]].rbegin(), wn = *st[W[t]].rbegin();
    if (wn < ls) { l2 = wn; r2 = ls - 1; }
    ll tt = query(t, l1, r1) + query(t, l2, r2);
    ll l = max(l1, l2), r = min(r1, r2);
    if (l <= r) tt -= query(t, l, r);//去掉两区间重叠部分
    return st[t].size() - tt;
}

ll get(char c) {
    if (c == 'R') return 1;
    if (c == 'P') return 2;
    return 3;
}

ll q, res;
string s;
int main() {
    fast;
    cin >> n >> q >> s; s = " " + s;
    rep(i,n) { ll c = get(s[i]); st[c].insert(i); add(c,i,1); }
    rep(i,3) res += gt(i);
    cout << res << '\n';//初始答案
    rep(i,q) {
        ll x; char c; cin >> x >> c;
        ll cc = get(s[x]), tt = get(c);
        if (cc != tt) {
            st[cc].erase(x); add(cc, x, -1);//从旧阵营移除
            st[tt].insert(x); add(tt, x, 1);//加入新阵营
            s[x] = c;
        }
        res = 0;
        rep(j,3) res += gt(j);//重算总量
        cout << res << '\n';
    }
    return 0;
}