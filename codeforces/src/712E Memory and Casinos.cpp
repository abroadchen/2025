//
// Created by Psy.C on 2026/4/20.
//
/**
A[rt]：节点rt维护的累积乘积
B[rt]：节点rt维护的复合函数值
叶子节点更新
A[rt] = B[rt] = (1.-val)/val
这里val是概率p，存储的是(1-p)/p的值
非叶子节点合并
A[rt] = A[ls] * A[rs]：左右子树A值的乘积
B[rt] = B[ls] + A[ls] * B[rs]：复合函数的合并
完全包含区间：直接返回节点信息
完全在左子树：递归查询左子树
完全在右子树：递归查询右子树
跨越中点：合并左右子树结果

读入数组长度n和查询次数q
对每个位置，计算概率a/b并更新到线段树
操作1：单点更新，将位置pos的概率更新为a/b
操作2：区间查询，查询[l,r]区间的结果
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+7;

#define ls rt<<1
#define rs rt<<1|1
#define mid ((l+r)>>1)
double A[N<<2], B[N<<2];
void update(int rt, int l, int r, int pos, double val) {
    if (l == r) { A[rt] = B[rt] = (1.-val)/val; return; }
    if (pos <= mid) update(ls, l, mid, pos, val);
    else update(rs, mid+1, r, pos, val);
    A[rt] = A[ls]*A[rs], B[rt] = B[ls]+A[ls]*B[rs];
}

#define dd pair<double,double>
dd query(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) return {A[rt], B[rt]};
    if (R <= mid) return query(ls, l, mid, L, R);
    if (L > mid) return query(rs, mid+1, r, L, R);
    if (L <= mid && R > mid) {
        auto al = query(ls, l, mid, L, R),
        ar = query(rs, mid+1, r, L, R);
        return {al.first*ar.first, al.second+al.first*ar.second};
    }
}

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) (x*=10) += ch&15;
    if (f) x = -x;
}

int n, q;
int main() {
    fast;
    rd(n), rd(q);
    for (int i = 1; i <= n; ++i) {
        double a, b; rd(a), rd(b);
        update(1, 1, n, i, a/b);
    }
    while (q--) {
        int op; rd(op);
        if (op == 1) {
            int pos; double a, b; rd(pos), rd(a), rd(b);
            update(1, 1, n, pos, a/b);
        } else {
            int l, r; rd(l), rd(r);
            auto ans = query(1, 1, n, l, r);
            printf("%.12lf\n", ans.second <= 2e15 ? 1./(1.+ans.second) : 0);
        }
    }
    return 0;
}