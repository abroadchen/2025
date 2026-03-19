//
// Created by Psy.C on 2026/3/18.
//
/**
N = 1e5: 数组最大容量
M = 29: 二进制位数（支持最大到2^29的数）
b[M+1]: 线性基数组，存储基底向量
laz: 懒惰标记，用于区间更新
st: 单点值
init(): 初始化函数，清空所有值
get(): 获取线性基中非零向量的个数（即线性基的秩）
add(): 向线性基中添加元素x
从高位到低位尝试插入
如果第i位为1且该位已有基底，则x异或该基底
如果该位没有基底，则插入x
合并两个线性基
将两个节点的线性基向量全部添加到新节点
添加两个节点的st值异或结果
设置ans的st为o的st
tr[N<<3]: 线段树数组
ans: 临时结果节点
build(): 构建线段树
l, r: 当前区间范围
st: 当前线段树节点编号
如果是叶子节点，读入值
否则递归构建左右子树
用左右子树合并结果更新当前节点
懒惰标记下传
如果当前节点有懒惰标记
将标记传递给左右子节点
清空当前节点的懒惰标记
区间异或更新
l, r: 当前区间
st: 当前节点编号
L, R: 目标区间
d: 异或值
如果当前区间完全包含在目标区间内，打懒惰标记
否则下传懒惰标记，递归更新左右子树
更新当前节点的线性基
区间查询
如果当前区间完全在查询区间内，合并到结果中
否则下传懒惰标记，递归查询左右子树
更新当前节点的线性基

操作1：区间[l,r]异或d
操作2：查询区间[l,r]的线性基，输出可异或出的不同值的个数（2^线性基大小）
时间复杂度：单次操作O(log²n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5, M = 29;

struct node {
    int b[M+1], laz, st;
    void init() {
        memset(b, 0, sizeof(b));
        laz = 0; st = 0;
    }
    int get() const {
        int ans = 0;
        for (int i = 0; i <= M; ++i)
            if (b[i]) ans++;
        return ans;
    }
    void add(int x) {
        for (int i = M; i >= 0; --i)
            if (x>>i&1) {
                if (b[i]) x ^= b[i];
                else { b[i] = x; break; }
            }
    }
    node operator+(const node& o) const {
        node ans; ans.init();
        for (int i = 0; i <= M; ++i) {
            ans.add(b[i]);
            ans.add(o.b[i]);
        }
        ans.add(st ^ o.st);
        ans.st = o.st;
        return ans;
    }
} tr[N<<3], ans;

void build(int l, int r, int st) {
    tr[st].init();
    if (l == r) { cin >> tr[st].st; return; }
    int mid = (l + r) >> 1;
    build(l, mid, st<<1); build(mid+1, r, st<<1|1);
    tr[st] = tr[st<<1] + tr[st<<1|1];
}

void pushdown(int st) {
    if (tr[st].laz) {
        tr[st<<1].laz ^= tr[st].laz; tr[st<<1].st ^= tr[st].laz;
        tr[st<<1|1].laz ^= tr[st].laz; tr[st<<1|1].st ^= tr[st].laz;
        tr[st].laz = 0;
    }
}

void update(int l, int r, int st, int L, int R, int d) {
    if (l >= L && r <= R) {
        tr[st].laz ^= d; tr[st].st ^= d;
        return;
    }
    pushdown(st);
    int mid = (l + r) >> 1;
    if (L <= mid) update(l, mid, st<<1, L, R, d);
    if (R > mid) update(mid+1, r, st<<1|1, L, R, d);
    tr[st] = tr[st<<1] + tr[st<<1|1];
}

void query(int l, int r, int st, int L, int R) {
    if (l >= L && r <= R) { ans = ans + tr[st]; return; }
    pushdown(st);
    int mid = (l + r) >> 1;
    if (L <= mid) query(l, mid, st<<1, L, R);
    if (R > mid) query(mid+1, r, st<<1|1, L, R);
    tr[st] = tr[st<<1] + tr[st<<1|1];
}

int n, q, op, l, r, d;
int main() {
    fast;
    cin >> n >> q; build(1, n, 1);
    while (q--) {
        cin >> op >> l >> r;
        if (op == 1) {
            cin >> d;
            update(1, n, 1, l, r, d);
        } else {
            ans.init();
            query(1, n, 1, l, r);
            cout << (1<<ans.get()) << '\n';
        }
    }
    return 0;
}