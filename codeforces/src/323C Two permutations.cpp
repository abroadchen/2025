//
// Created by Psy.C on 2026/1/8.
//
/**
* m：查询次数
s1[N], s2[N]：两个输入序列
pos[N]：位置映射数组
rt[N]：可持久化线段树的根节点数组
 *
 *读入s1数组，建立值到位置的映射      记录s1[i]在序列中的位置
 *根据s2[i]在s1中的位置建立映射
 *
 *构建n个版本的线段树，每个版本在前一版本基础上插入a[i]
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1000010
#define ls(x) tr[x].l//简化左子树访问
#define rs(x) tr[x].r
#define sum(x) tr[x].sum//简化节点值访问
#define tr(x) tr[x]//简化节点访问
using namespace std;

struct sgt { int l, r, sum; } tr[N<<5];//左子树、右子树、区间和

int tot, a[N];//节点计数器，用于分配新节点ID  a[N]：辅助数组
int build(const int l, const int r) {
    const int p = ++tot;
    if (l == r) { sum(p) = a[l]; return p; }
    const int mid = (l + r) >> 1;
    ls(p) = build(l, mid); rs(p) = build(mid + 1, r);
    return p;
}

//在历史版本基础上插入新元素
int insert(const int cur, const int l, const int r, const int pos) {
    const int p = ++tot;
    tr(p) = tr(cur); sum(p) = sum(cur) + 1;//复制当前节点  更新区间和
    if (l == r) return p;
    if (const int mid = (l + r) >> 1; pos <= mid) ls(p) = insert(ls(cur), l, mid, pos);
    else rs(p) = insert(rs(cur), mid + 1, r, pos);
    return p;
}

//查询区间[L,R]的和
int query(const int cur, const int l, const int r, const int L, const int R) {
    if (l >= L && r <= R) return sum(cur);
    const int mid = (l + r) >> 1; int val = 0;
    if (L <= mid) val += query(ls(cur), l, mid, L, R);
    if (R > mid) val += query(rs(cur), mid + 1, r, L, R);
    return val;
}

int n, ans;
int f(const int x) { return ((x - 1 + ans) % n) + 1; }//动态调整查询参数，使用ans作为偏移量

int main() {
    fast;
    int m, s1[N], s2[N], pos[N], rt[N]; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> s1[i], pos[s1[i]] = i;
    for (int i = 1; i <= n; ++i) cin >> s2[i], a[pos[s2[i]]] = i;
    rt[0] = build(1, n);
    for (int i = 1; i <= n; ++i) rt[i] = insert(rt[i-1], 1, n, a[i]);
    cin >> m;
    while (m--) {
        int a1, b, c, d; cin >> a1 >> b >> c >> d;
        const int l1 = min(f(a1), f(b)), r1 = max(f(a1), f(b)),
        l2 = min(f(c), f(d)), r2 = max(f(c), f(d));
        ans = query(rt[r1], 1, n, l2, r2) -
            query(rt[l1-1], 1, n, l2, r2);
        cout << ans << '\n';
        ans++;//更新全局答案，用于下一次查询的动态调整
    }
    return 0;
}