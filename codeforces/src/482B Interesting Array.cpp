//
// Created by Psy.C on 2026/2/17.
//
/**
时间复杂度：O(m log n)
空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+6;

int laz[N<<2], tr[N<<2];
inline void pushdown(const int rt) {
    laz[rt<<1] |= laz[rt];//根节点rt的懒惰标记传递给左右子节点
    laz[rt<<1|1] |= laz[rt];
    tr[rt<<1] |= laz[rt];//传递标记
    tr[rt<<1|1] |= laz[rt];
    laz[rt] = 0;
}

inline void push_up(const int rt) {//合并到父节点
    tr[rt] = tr[rt<<1] & tr[rt<<1|1];
}

void update(const int L, const int R, const int l, const int r, const int rt, const int val) {
    if (L <= l && R >= r) {
        tr[rt] |= val; laz[rt] |= val; return;//直接应用懒惰标记并返回
    }
    if (laz[rt]) pushdown(rt);//下推懒惰标记，递归更新左右子树
    const int mid = (l + r) >> 1;
    if (L <= mid) update(L, R, l, mid, rt<<1, val);
    if (R > mid) update(L, R, mid+1, r, rt<<1|1, val);
    push_up(rt);//合并结果
}

int query(const int L, const int R, const int l, const int r, const int rt) {
    if (L <= l && R >= r) return tr[rt];
    if (laz[rt]) pushdown(rt);
    const int mid = (l + r) >> 1;
    int res = (1<<31)-1;
    if (L <= mid) res &= query(L, R, l, mid, rt<<1);//合并查询结果
    if (R > mid) res &= query(L, R, mid+1, r, rt<<1|1);
    return res;
}

int n, m, l[N], r[N], val[N];

int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> l[i] >> r[i] >> val[i];
        update(l[i], r[i], 1, n, 1, val[i]);
    }
    int flag = 0;
    for (int i = 1; i <= m; ++i) {
        if (query(l[i], r[i], 1, n, 1) != val[i]) {//不等于期望值，则标记失败
            flag = 1; break;
        }
    }
    if (flag) cout << "NO\n";
    else {
        cout << "YES\n";
        for (int i = 1; i <= n; ++i) {
            if (i != 1) cout << ' ';
            cout << query(i, i, 1, n, 1);
        }
        cout << '\n';
    }
    return 0;
}