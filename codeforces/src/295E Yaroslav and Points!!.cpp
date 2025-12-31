//
// Created by Psy.C on 2025/12/31.
//
/**
* t：操作类型（1为更新，2为查询）
p, d：用于更新操作的参数
l, r：用于查询操作的范围
 *hv：离散化后的值数组
 *二分查找函数，用于在离散化数组中查找值的位置
 *mark参数控制返回策略：1表示如果找到则返回下一个位置，2表示返回当前位置
 *线段树节点：num为区间内元素个数，sum为元素和，ans为答案（逆序对相关）
 *
*更新父节点信息
rt.ans的计算公式：左边元素个数×右边元素和 - 右边元素个数×左边元素和 + 左右子树的ans
 *构建线段树，叶子节点初始化为原始数组的值
 *更新线段树：op=1为添加元素，op=0为删除元素
 *查询区间[l,r]的统计信息
 *
 *读入n个元素，同时构建离散化数组val
 *读入m个操作，1为更新操作（位置p增加d），2为查询操作（查询值在[l,r]范围内的元素）
 *对所有出现的值进行离散化处理，去重后存入hv数组
 *初始化线段树
 *更新操作先删除旧值再添加新值；查询操作直接查询区间并输出ans值
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100005
using namespace std;

struct node { int t, p, d; ll l, r; } q[N];

ll hv[N<<1];
int bs(const ll m, const int mark, const int len) {
    int l = 0, r = len + 1;
    while (r - l > 1) {
        const int mid = (l + r) >> 1;
        if (hv[mid] <= m) l = mid; else r = mid;
    }
    if (hv[l] == m) return l;
    if (mark == 1) return l + 1;
    return l;
}

struct node2 { int num; ll sum, ans; } tr[N<<3];

void push_up(node2& rt, const node2& ls, const node2& rs) {
    rt.num = ls.num + rs.num;
    rt.sum = ls.sum + rs.sum;
    rt.ans = ls.num * rs.sum - rs.num * ls.sum + ls.ans + rs.ans;
}

int idx = 1, pos[N], n, aa[N];
void build(const int rt, const int L, const int R) {
    if (L == R) {
        tr[rt].num = 0; tr[rt].sum = tr[rt].ans = 0;
        if (idx <= n && L == pos[idx]) {
            tr[rt].num = 1;
            tr[rt].sum = aa[idx];
            tr[rt].ans = 0;
            idx++;
        }
        return;
    }
    const int mid = (L + R) >> 1;
    build(rt<<1, L, mid); build(rt<<1|1,mid+1, R);
    push_up(tr[rt], tr[rt<<1], tr[rt<<1|1]);
}

void update(const int rt, const int L, const int R, const int x, const int op, const int val) {
    if (L == R) {
        if (op == 1) {
            tr[rt].num = 1; tr[rt].sum = val; tr[rt].ans = 0;
        } else {
            tr[rt].num = 0; tr[rt].sum = tr[rt].ans = 0;
        }
        return;
    }
    const int mid = (L + R) >> 1;
    if (x <= mid) update(rt<<1, L, mid, x, op, val);
    else update(rt<<1|1, mid+1, R, x, op, val);
    push_up(tr[rt], tr[rt<<1], tr[rt<<1|1]);
}

node2 query(const int rt, const int L, const int R, const int l, const int r) {
    if (l <= L && R <= r) return tr[rt];
    node2 t{};
    const int mid = (L + R) >> 1;
    if (r <= mid) t = query(rt<<1, L, mid, l, r);
    else if (l > mid) t = query(rt<<1|1, mid+1, R, l, r);
    else {
        const node2 a = query(rt<<1, L, mid, l, mid);
        const node2 b = query(rt<<1|1, mid+1, R, mid+1, r);
        push_up(t, a, b);
    }
    return t;
}

int main() {
    fast;
    int m, cnt = -1; cin >> n;
    ll a[N], val[N<<1], l, r;
    for (int i = 1, v; i <= n; ++i) {
        cin >> v;
        a[i] = v; aa[i] = v; val[++cnt] = v;
    }
    cin >> m;
    for (int i = 1, t, p, d; i <= m; ++i) {
        cin >> t;
        if (t == 1) {
            cin >> p >> d;
            q[i].t = t; q[i].p = p; q[i].d = d;
            aa[p] += d; val[++cnt] = aa[p];
        } else {
            cin >> l >> r;
            q[i].t = t; q[i].l = l; q[i].r = r;
        }
    }
    sort(val, val + cnt + 1);
    int nn = 0; hv[++nn] = val[0];
    for (int i = 1; i <= cnt; ++i) if (val[i] != val[i - 1]) {
        hv[++nn] = val[i];
    }
    for (int i = 1; i <= n; ++i) aa[i] = static_cast<int>(a[i]);
    sort(aa + 1, aa + n + 1);
    for (int i = 1; i <= n; ++i) pos[i] = bs(aa[i], 2, nn);
    build(1, 1, nn);
    for (int i = 1, x, y; i <= m; ++i) {
        if (q[i].t == 1) {
            x = bs(a[q[i].p], 2, nn);
            update(1, 1, nn, x, 0, 1);
            a[q[i].p] += q[i].d;
            x = bs(a[q[i].p], 2, nn);
            update(1, 1, nn, x, 1, static_cast<int>(a[q[i].p]));
        } else {
            x = bs(q[i].l, 1, nn);
            y = bs(q[i].r, 2, nn);
            if (x > nn || y < 1 || x > y) cout << "0\n";
            else cout << query(1, 1, nn, x, y).ans << '\n';
        }
    }
    return 0;
}