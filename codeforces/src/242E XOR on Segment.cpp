//
// Created by Psy.C on 2025/12/15.
//
/*
*lz 数组存储懒惰标记（异或操作值）
sum[i][x] 存储第 x 个节点中所有数字第 i 位为 1 的总数量
N<<2|3 相当于 4*N + 3，确保线段树有足够的空间
 *
*向上更新函数：将左右子节点的信息合并到当前节点
对每一位统计其在左右子树中的出现次数之和
*构建线段树函数
如果是叶子节点，则计算每个位上的值并保存
否则递归构建左右子树后向上更新
*修改函数：对区间 [l,r] 执行异或操作 p
更新懒惰标记
如果 p 的第 i 位为 1，则翻转该位的计数（原来是 1 变成 0，原来是 0 变成 1）
*下传懒惰标记函数
将当前节点的懒惰标记传递给左右子节点
清空当前节点的懒惰标记
*区间更新函数：对区间 [ql,qr] 中的所有元素执行异或操作 p
如果完全覆盖当前区间，直接修改并返回
否则先下传懒惰标记，然后递归处理左右子区间，最后向上更新
*查询函数：返回区间 [ql,qr] 内所有元素的和
如果完全覆盖当前区间，根据各二进制位的数量计算结果
否则先下传懒惰标记，然后递归查询左右子区间并累加结果
 *
*若操作类型为 1：输入查询区间 [l,r] 并输出结果
否则：输入更新区间 [l,r] 和异或值 x，执行区间更新
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100000
#define M 21
using namespace std;

int a[N+5], n;
struct node {
    ll lz[N<<2|3], sum[M+1][N<<2|3];
#define ls(x) x<<1
#define rs(x) (x<<1|1)
    void up(const ll x) {
        for (int i = 0; i <= M; ++i)
            sum[i][x] = sum[i][ls(x)] + sum[i][rs(x)];
    }
    void build(int *t, const int x=1, const int l=1, const int r=n) {
        if (l == r) {
            for (int i = 0; i <= M; ++i)
                sum[i][x] = t[l] >> i & 1;
            return;
        }
        const int mid = (l + r) >> 1;
        build(t, ls(x), l, mid); build(t, rs(x), mid+1, r);
        up(x);
    }
    void modify(const int x, const int l, const int r, const ll p) {
        lz[x] ^= p;
        for (int i = 0; i <= M; ++i) if ((p>>i)&1) {
            sum[i][x] = r - l + 1 - sum[i][x];//表示在这个区间中，第 i 位为 0 的元素个数
        }
    }
    void down(const int x, const int l, const int r) {
        const ll mid = (l + r) >> 1;
        modify(ls(x), l, static_cast<int>(mid), lz[x]);
        modify(rs(x), static_cast<int>(mid)+1,  r, lz[x]);
        lz[x] = 0;
    }
    void update(const int ql, const int qr, const ll p, const int l=1, const int r=n, const int x=1) {
        if (ql <= l && qr >= r) { modify(x, l, r, p); return; }
        if (lz[x]) down(x, l, r);
        const ll mid = (l + r) >> 1;
        if (ql <= mid) update(ql, qr, p, l, static_cast<int>(mid), ls(x));
        if (qr > mid) update(ql, qr, p, static_cast<int>(mid)+1, r, rs(x));
        up(x);
    }
    ll query(const int ql, const int qr, const int l=1, const int r=n, const int x=1) {
        if (ql <= l && qr >= r) {
            ll res = 0;
            for (int i = 0; i <= M; ++i)
                res += sum[i][x] << i;
            return res;
        }
        if (lz[x]) down(x, l, r);
        ll res = 0;
        const ll mid = (l + r) >> 1;
        if (ql <= mid) res += query(ql, qr, l, static_cast<int>(mid), ls(x));
        if (qr > mid) res += query(ql, qr, static_cast<int>(mid)+1, r, rs(x));
        return res;
    }
} tr;



int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    tr.build(a);
    int m; cin >> m;
    for (int i = 1; i <= m; ++i) {
        int op, l, r;
        cin >> op;
        if (op == 1) {
            cin >> l >> r;
            cout << tr.query(l, r) << "\n";
        } else {
            ll x;
            cin >> l >> r >> x;
            tr.update(l, r, x);
        }
    }
    return 0;
}