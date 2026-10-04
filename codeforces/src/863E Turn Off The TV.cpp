//
// Created by Psy.C on 2026/10/4.
//
/**
M = 1e7+5：动态开点树的节点池上限（因为用到才建，最多节点数有限）。
struct node：每个节点存：
ls, rs：左右子节点下标（未建时为 0）。
val：该区间的最小值。
tag：懒惰标记（区间整体加了多少）。
所有节点放在全局数组 a[] 中，cnt 记录已用节点数。
注意：ls/rs 为 0 时表示该子节点尚未创建，这是动态开点的核心
push_up：父节点 val = 左右孩子 val 的较小值。
tg（给某个节点整体加 v）：更新该节点的 val 和 tag。
push_down：把节点上的懒惰标记下传给左右孩子；注意没判孩子是否存在，因为调用处会确保孩子已创建。
这里 push_up 读取 a[a[k].ls].val，要求两个孩子都已存在——因为动态开点在分裂时总会新建左右节点，所以叶子/已分裂节点孩子一定存在
add(1, 1, INF, x, y, v)：给区间 [x,y] 整体加 v。
完全覆盖则打标记返回。
否则：
若当前节点还没有孩子（叶子或未分裂），则动态创建左右孩子（a[k].ls = ++cnt, a[k].rs = ++cnt）。
下推标记（把标记传给新孩子）。
递归左右加，最后 push_up 更新最小值。
这就是"动态开点"：只有访问到某段时才会创建其节点，从而用较少的节点覆盖 1e9 范围
查询 [x,y] 的最小值。
完全覆盖直接返回 val。
否则同样动态创建孩子（保证查询到未建段时有节点可用）、下推标记、递归，返回两半的最小值
第一遍：读入所有 n 个区间，并把每个区间 [l[i]+1, r[i]+1] 整体 +1（表示该区间覆盖范围计数 +1）。+1 是把下标偏移（可能是题目约定左闭右开或 0-index 与 1-index 的转换）。
第二遍：对每个区间查它覆盖范围内的最小值。若 ≥ 2，说明该区间内每个点至少被覆盖了 2 次——即该区间被至少另一个区间完全覆盖（覆盖次数 ≥2）‍，此时输出编号 i 并结束。
若全部查完都没有，输出 -1

动态开点：每次操作创建 O(log INF) 节点，总节点数 ≤ O(n log INF)，在 M=1e7 内。
每次 add/query 为 O(log INF) ≈ O(30)。
总复杂度 O(n log INF)，但空间用动态开点压到了 M 内
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 2e5+5, M = 1e7+5, inf = 2e9, INF = 1e9+20;
struct node { int ls, rs, val, tag; } a[M];

void push_up(int k) { a[k].val = min(a[a[k].ls].val, a[a[k].rs].val); }
void tg(int k, int l, int r, int v) {
    a[k].val = a[k].val + v;
    a[k].tag = a[k].tag + v;
}
void push_down(int k, int l, int r) {
    if (!a[k].tag) return;
    int mid = (l+r)>>1;
    tg(a[k].ls, l, mid, a[k].tag);
    tg(a[k].rs, mid+1, r, a[k].tag);
    a[k].tag = 0;
}

int cnt = 1;
void add(int k, int l, int r, int x, int y, int v) {
    if (x <= l && r <= y) { tg(k, l, r, v); return; }
    int mid = (l+r)>>1;
    if (!a[k].ls && !a[k].rs) a[k].ls = ++cnt, a[k].rs = ++cnt;
    push_down(k, l, r);
    if (x <= mid) add(a[k].ls, l, mid, x, y, v);
    if (mid < y) add(a[k].rs, mid+1, r, x, y, v);
    push_up(k);
}

int query(int k, int l, int r, int x, int y) {
    if (x <= l && r <= y) return a[k].val;
    int mid = (l+r)>>1, ans = inf;
    if (!a[k].ls && !a[k].rs) a[k].ls = ++cnt, a[k].rs = ++cnt;
    push_down(k, l, r);
    if (x <= mid) ans = min(ans, query(a[k].ls, l, mid, x, y));
    if (mid < y) ans = min(ans, query(a[k].rs, mid+1, r, x, y));
    return ans;
}

int l[N], r[N];
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> l[i] >> r[i];
        add(1, 1, INF, l[i]+1, r[i]+1, 1);
    }
    for (int i = 1; i <= n; ++i) {
        if (query(1, 1, INF, l[i]+1, r[i]+1) >= 2) {
            cout << i << '\n';
            return 0;
        }
    }
    cout << "-1\n";
    return 0;
}