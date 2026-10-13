//
// Created by Psy.C on 2026/10/12.
//
/**
关键性质（query 剪枝的根基）：

若整个区间的 gcd(d) 能被 x 整除（d % x == 0），则该区间内每一个元素都能被 x 整除，即区间内不存在 %x!=0 的数，可整段跳过。
这是因为任何数 a_i 都是它所在区间 gcd 的倍数，若 x | gcd(区间) 则 x | 每个 a_i
cnt 是全局计数器，目标只关心 cnt 是否 >1，所以 cnt>1 时立即剪枝，复杂度降下来。
对每个与查询区间重叠且gcd 不被 d 整除的节点，向下递归；一旦某节点 gcd 能被 d 整除则整段跳过。
到达叶子 l==r 说明这个单点值 %d != 0，cnt++
区间内"不被 x 整除"的元素数超过 1 个 → NO，否则 YES

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ls (rt<<1)
#define rs (rt<<1|1)
using namespace std;

constexpr int N = 5e5+5;

int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }

int tr[N<<2];
void push_up(int rt) { tr[rt] = gcd(tr[ls], tr[rs]); }
void build(int rt, int l, int r) {
    if (l == r) { cin >> tr[rt]; return; }
    int mid = (l+r)>>1;
    build(ls, l, mid); build(rs, mid+1, r);
    push_up(rt);
}

//标准的单点改 + 向上更新 gcd，O(log n)
void modify(int x, int rt, int l, int r, int val) {
    if (l == r) { tr[rt] = val; return; }
    int mid = (l+r)>>1;
    if (x <= mid) modify(x, ls, l, mid, val);
    else modify(x, rs, mid+1, r, val);
    push_up(rt);
}

int cnt;
void query(int x, int y, int rt, int l, int r, int d) {
    if (cnt > 1) return;
    if (l == r) { ++cnt; return; }
    int mid = (l+r)>>1;
    if (x <= mid && tr[ls]%d) query(x, y, ls, l, mid, d);
    if (mid < y && tr[rs]%d) query(x, y, rs, mid+1, r, d);
}

int n, q;
int main() {
    fast;
    cin >> n; build(1, 1, n);
    for (cin >> q; q--; ) {
        int op; cin >> op;
        if (op == 1) {
            int l, r, x; cin >> l >> r >> x;
            cnt = 0, query(l, r, 1, 1, n, x);
            cout << (cnt > 1 ? "NO" : "YES") << '\n';
        } else {
            int x, k; cin >> x >> k;
            modify(x, 1, 1, n, k);
        }
    }
    return 0;
}