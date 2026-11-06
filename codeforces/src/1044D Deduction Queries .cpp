//
// Created by Psy.C on 2026/11/6.
//

/**
真正学会的起点..
fa[x] 父节点，val[x] = x 到其父的异或值。
find 返回 (根, 从 x 到根的累计异或)。
注意这里无路径压缩（plain 版本），链可能较长；但 merge 有按秩合并。
若根不同：把秩小的根接到秩大的根。
权校准：val[x]=c^vx^vy（使合并后保持两节点异或关系为 c
坐标离散化

用 mp[坐标] = 节点编号 把区间端点 l-1 和 r 离散化。
每个坐标对应并查集一个节点，节点的值 = 差分前缀异或：mp[k] 代表"位置 k 的差分值位置"。
操作 1（赋值 [l,r] 异或 x）

就是修改差分数组：在 l-1 与 r 之间建立一条异或权为 x 的边（merge）。
意义：xor[l..r] = x ⇔ pre[r] ^ pre[l-1] = x（前缀异或差分），所以连边 (l-1, r, x)。
操作 2（查询 [l,r] 的异或）

若 l-1、r 已在同一集合（same）→ 连通，则 pre[r] ^ pre[l-1] 可由两节点到根异或值相异或求得。
若不在同一集合 → 无法确定 → 输出 -1（在线强制 ans=1 用于下次解码）。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;

constexpr int N = 4e5+5;

int fa[N], val[N];
ii find(int x) {
    int res = 0;
    while (x != fa[x]) res ^= val[x], x = fa[x];
    return {x, res};
}

int rk[N];
void merge(int a, int b, int c) {
    auto [x, vx] = find(a);
    auto [y, vy] = find(b);
    if (x == y) return;//已连通
    if (rk[x] > rk[y]) swap(x, y), swap(vx, vy);
    c ^= vx^vy;
    fa[x] = y, rk[y] += rk[x];
    val[x] = c;//x 到 y 的异或权
}

bool same(int a, int b) {
    auto [x, vx] = find(a);
    auto [y, vy] = find(b);
    return x == y;
}

int q, ans, n;
map<int, int> mp;
int main() {
    fast;
    cin >> q;
    for (int i = 1, t; i <= q; i++) {
        cin >> t;
        if (t == 1) {
            int l, r, x; cin >> l >> r >> x;
            l ^= ans, r ^= ans, x ^= ans;//在线解码（ans 是上一次答案）
            if (l > r) swap(l, r);
            if (!mp[l-1]) mp[l-1] = ++n, fa[n] = n, rk[n] = 1;
            if (!mp[r]) mp[r] = ++n, fa[n] = n, rk[n] = 1;
            merge(mp[l-1], mp[r], x);
        } else {
            int l, r; cin >> l >> r;
            l ^= ans, r ^= ans;
            if (l > r) swap(l, r);
            if (!mp[l-1] || !mp[r] || !same(mp[l-1], mp[r])) {
                cout << -1 << '\n'; ans = 1;
            } else {
                ans = find(mp[l-1]).second, ans ^= find(mp[r]).second;//异或差
                cout << ans << '\n';
            }
        }
    }
    return 0;
}