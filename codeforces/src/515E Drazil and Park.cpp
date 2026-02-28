//
// Created by Psy.C on 2026/2/28.
//
/**
mx1：区间内s1的最大值
mx2：区间内s2的最大值
ans：区间内s1[i] + s2[j]的最大值（i < j）
t[M]：线段树数组
合并左右子树信息
p.mx1：左右子树mx1的最大值
p.mx2：左右子树mx2的最大值
p.ans：跨左右子树的最大值（左子树mx1 + 右子树mx2）
建立线段树
叶节点：直接赋值s1[l]和s2[l]
非叶节点：递归建立左右子树，然后合并
区间查询函数
如果完全包含，直接返回节点信息
如果跨越中点，合并左右查询结果
否则查询对应子区间

读入n和m
读入距离数组d和高度数组h
复制数组以处理环形情况
dis[i]：前缀距离和
s1[i] = 2*h[i] - dis[i]
s2[i] = 2*h[i] + dis[i]

对于每个查询(a, b)：
l = b+1, r = a-1：查询区间
如果l > r，说明跨越了环，r += n
查询区间[l, r]内的最大值
输出结果
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+1, M = 8e5+1;
constexpr ll inf = 0x3f3f3f3f3f3f3f3f;
struct node {
    ll mx1 = -inf, mx2 = -inf, ans = -inf;
} t[M];

void push_up(node& p, const node &l, const node &r) {
    p.mx1 = max(l.mx1, r.mx1);
    p.mx2 = max(l.mx2, r.mx2);
    p.ans = max(max(l.ans, r.ans), l.mx1 + r.mx2);
}

ll s1[N], s2[N];
void build(const int p, const int l, const int r) {
    if (l == r) {
        t[p].mx1 = s1[l]; t[p].mx2 = s2[l];
        t[p].ans = -inf;
        return;
    }
    const int mid = (l + r) >> 1;
    build(p<<1, l, mid); build(p<<1|1, mid+1, r);
    push_up(t[p], t[p<<1], t[p<<1|1]);
}

node query(const int p, const int l, const int r, const int L, const int R) {
    if (l <= L && R <= r) return t[p];
    const int mid = (L + R) >> 1;
    if (l <= mid && r > mid) {
        node res;
        push_up(res, query(p<<1, l, r, L, mid), query(p<<1|1, l, r, mid+1, R));
        return res;
    }
    if (l <= mid) return query(p<<1, l, r, L, mid);
    return query(p<<1|1, l, r, mid+1, R);
}

int n, m;
ll d[N], h[N], dis[N];
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) { cin >> d[i]; d[n+i] = d[i]; }
    for (int i = 1; i <= n; ++i) { cin >> h[i]; h[n+i] = h[i]; }
    for (int i = 1; i <= 2*n; ++i) {
        dis[i] = dis[i-1] + d[i-1];
        s1[i] = 2ll*h[i] - dis[i];
        s2[i] = 2ll*h[i] + dis[i];
    }
    build(1, 1, 2*n);
    for (int i = 1, a, b; i <= m; ++i) {
        cin >> a >> b;
        int l = b+1, r = a-1;
        if (l > r) r += n;
        const auto x = query(1, l, r, 1, 2*n);
        cout << x.ans << '\n';
    }
    return 0;
}