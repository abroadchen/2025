//
// Created by Psy.C on 2026/11/1.
//

/**
真正学会的起点..
a[] 长度 2n，每个区间存两个点。
每个点有：id（所属区间编号）、x（读到/给到的坐标）、v（离散化后的值）
cmp 按 x 排序。
离散化：相同 x 的给同一个 v（编号），不同才 ++p 新编号。
num[v] 记录编号 v 对应的原始坐标 x（用于后面取最大值）。
之后 sort(a+1, a+1+(n<<1), cmp2) 按 (id, v) 归序，把同一区间的两个端点放在一起——cmp2 先比 id，id 相同比 v
p 个不同坐标各自为独立集合
对第 i 个区间的两个端点做并查集找根 s1, s2。
特判无解：两端所在集合都已被置 fa=0（都删过）→ 输出 -1。
若两段相同、或至少一段已被删（fa=0，find 返回 0）→ 该区间"闭合"，取二者 num 较大者计入 ans，并把该集合删除（fa[s1]=fa[s2]=0）。
否则（两段都还活着且不同）→ 合并：把较小的集合并入较大的集合（fa[s1]=s2），并累计一个 num 值
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=(n); ++i)
using namespace std;

constexpr int N = 1e6+10;
struct node { int id, x, v; } a[N<<1];
bool cmp(node x, node y) { return x.x < y.x; }
bool cmp2(node x, node y) { return x.id == y.id ? x.v < y.v : x.id < y.id; }

int fa[N<<1];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, p, num[N<<1], ans;
int main() {
    fast;
    n = rd();
    //第 i 个区间的第一端点 第 i 个区间的第二端点 同一个 id=i
    rep(i,n) a[(i<<1)-1].x = rd(), a[i<<1].x = rd(), a[(i<<1)-1].id = a[i<<1].id = i;
    sort(a+1, a+1+(n<<1), cmp);
    a[0].x = a[1].x + 1;
    rep(i,n<<1) a[i].v = a[i].x == a[i-1].x ? p : ++p, num[a[i].v] = a[i].x;
    sort(a+1, a+1+(n<<1), cmp2);
    rep(i,p) fa[i] = i;
    rep(i,n) {
        int s1 = find(a[(i<<1)-1].v), s2 = find(a[i<<1].v);
        if (!s1 && !s2) { cout << "-1\n"; return 0; }
        if (s1 == s2 || !s1 || !s2) {
            ans = max(ans, max(num[s1], num[s2]));
            fa[s1] = fa[s2] = 0;
        } else {
            if (s1 > s2) swap(s1, s2);
            ans = max(ans, num[s1]);
            fa[s1] = s2;
        }
    }
    cout << ans << '\n';
    return 0;
}