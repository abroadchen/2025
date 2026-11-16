//
// Created by Psy.C on 2026/11/16.
//

/**
真正学会的起点..
每个节点存：tag（懒惰标记，区间整体加的量）、val（区间最小值）。
apply：区间整体加 v，则 tag 和 val 都加 v（最小值也整体平移）
合并（push-up）：父节点 val = 左右孩子 val 的最小值
初始化 tr 为 2n-1 个节点。这是"节点数 ≤ 2n"的整数组布局，用编号连续的数组承载
pull：用左右孩子更新父节点。左孩子是 x+1，右孩子是 z
push：把当前节点 tag 下传给左右孩子并清零。
关键：左右孩子的位置如何由 x 推出：
左孩子 x+1（紧挨着）。
右孩子 z = x + ((y-l+1)<<1)，即 x + 2*(左区间长度)。
因为布局按"左子树区间元素个数在数组上连续排布"，右孩子起点 = 当前 x + 左子树节点数（一个区间长度为 len 的子树占 2*len-1 个节点，但这里是看叶子数的 2 倍偏移）。
这是"堆式无关、按区间连续存储"的紧凑非递归线段树，好处是内存刚好 2n-1，适合 n=1e6
叶子 val = -l（即 -下标）。
父节点由 pull 取两子树 val 的 min。
叶子为 -l 的含义：这个"初值数组"实际上存的是 b[i] = -i。结合 apply 区间加，整套结构维护的是某个"数组在区间上累积加偏移"后的逐点值，并支持区间最小值查询。这常对应"贪心/模拟某个光标在某区间加或减，求序列某前缀/某点的值"
用给定数组 v 作为叶子初值，可选的第二建树方案（本代码没用它）
标准区间加，遇到完全覆盖则 apply（打 tag / 直接改值），否则 push 原 tag 再下放递归、最后 pull 回更新最小值。
外层封装 modify(l, r, ...) 从根 (0,0,n-1) 开始。
注意 n-1：这里 build(0,0,N) 传的是 N，而 n 由构造函数 sgt tr(N+1) 传 n = N+1，所以 modify 里范围是 [0, n-1] = [0, N]。所以区间上界用到 N
点查询 / 区间查询，返回 node（含 val 最小值）。
外层 query(l,r) 从根调用
+ t d：[t, N] 区间加 d。同时记录 a[q] = {t, d} 供撤销用。

- i：取回第 i 次 +（下标从 0），对其区间 [t, N] 加 -d，即撤销。

查询 t：输出
query(t,t).val - query(0,t-1).val + 1

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ii pair<int, int>
using namespace std;

constexpr int N = 1e6;

struct sgt {
    struct node {
        ll tag = 0, val = 0;
        void apply(int l, int r, ll v) { tag += v; val += v; }
    };
    vector<node> tr;
    int n;
    node uni(const node &l, const node &r) {
        node res;
        res.val = min(l.val, r.val);
        return res;
    }
    sgt(int n) : n(n) { tr.resize((n<<1)-1); }
    void pull(int x, int z) { tr[x] = uni(tr[x+1], tr[z]); }
    void push(int x, int l, int r) {
        int y = (l+r)>>1, z = x+((y-l+1)<<1);
        if (tr[x].tag) {
            tr[x+1].apply(l,y,tr[x].tag);
            tr[z].apply(y+1,r,tr[x].tag);
            tr[x].tag = 0;
        }
    }
    void build(int x, int l, int r) {
        if (l != r) {
            int y = (l+r)>>1, z = x+((y-l+1)<<1);
            build(x+1,l,y); build(z,y+1,r); pull(x,z);
        } else tr[x].val = -l;
    }
    template<typename T>
    void build(int x, int l, int r, const vector<T> &v) {
        if (l == r) tr[x].apply(l,r,v[l]);
        else {
            int y = (l+r)>>1, z = x+((y-l+1)<<1);
            build(x+1,l,y,v); build(z,y+1,r,v); pull(x,z);
        }
    }
    template<typename T>
    void build(const vector<T> &v) { build(0,0,n-1,v); }
    template<typename... T>
    void modify(int x, int l, int r, int L, int R, const T&... v) {
        if (l == L && r == R) tr[x].apply(l,r,v...);
        else {
            int y = (l+r)>>1, z = x+((y-l+1)<<1);
            push(x,l,r);
            if (R <= y) modify(x+1,l,y,L,R,v...);
            else if (L > y) modify(z,y+1,r,L,R,v...);
            else {
                modify(x+1,l,y,L,y,v...);
                modify(z,y+1,r,y+1,R,v...);
            }
            pull(x,z);
        }
    }
    template<typename... T>
    void modify(int l, int r, const T&... v) { modify(0,0,n-1,l,r,v...); }
    node query(int x, int l, int r, int L, int R) {
        if (l == L && r == R) return tr[x];
        int y = (l + r) >> 1, z = x + ((y - l + 1) << 1);
        push(x, l, r);
        if (R <= y) return query(x + 1, l, y, L, R);
        if (L > y) return query(z, y + 1, r, L, R);
        return uni(query(x + 1, l, y, L, y), query(z, y + 1, r, y + 1, R));
    }
    node query(int l, int r) { return query(0,0,n-1,l,r); }
};

int main() {
    fast;
    sgt tr(N+1); tr.build(0,0,N);
    int T; cin >> T;
    vector<ii> a(T);
    for (int q = 0; q < T; ++q) {
        string s; cin >> s;
        if (s == "+") {
            int t, d; cin >> t >> d;
            a[q] = {t,d};
            tr.modify(t,N,d);
        } else if (s == "-") {
            int i; cin >> i; --i;
            int t = a[i].first, d = a[i].second;
            tr.modify(t,N,-d);
        } else {
            int t; cin >> t;
            cout << tr.query(t,t).val-tr.query(0,t-1).val+1 << '\n';
        }
    }
    return 0;
}