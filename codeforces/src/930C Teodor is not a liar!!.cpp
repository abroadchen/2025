//
// Created by Psy.C on 2026/10/16.
//
/**
sum[x]：节点区间内元素当前总"和"（这里其实是每个点的初值累加，因为每次区间加都 +1）。
len[x]：节点覆盖的区间长度（元素个数）。
tag[x]：懒惰标记，记录该节点区间被整体加了多少
把区间长度和总和往上传
区间内每个元素都 +t，所以总和增加 len*t
把标记分给两个孩子并清空自己。
节点区间长度 = 区间元素个数；sum 默认 0（全局默认）
标准的区间更新 + 懒标记下放
下放懒标记后向对应子树走
对每个位置单点查询，得到 a[i] = 该位置被区间加覆盖的次数
读入 m（操作次数）、n（数组长度）。
n 次区间操作 [l,r] 各 +1。
最后 get(n) 计算答案

upper_bound 找到第一个 > 当前值的位置，替换它；找不到就追加。
用 upper_bound（而不是 lower_bound）意味着相等元素可以并列，即求的是最长不下降（非严格递增）子序列。
正向扫得到 L[i] = 以位置 i 结尾的最长不下降子序列长度。
反向扫（i 从 n 到 1，同时用反向的单调性）得到 R[i] = 从位置 i 开始（含 i）的向后最长不下降子序列长度——注意反向贪心处理的是"在原数组中从 i 往右"的部分，所以 R[i] 表示以 i 为左端的最长不下降子序列长度
L[i]：以 i 结尾的最长不下降子序列。
R[i]：以 i 开头的最长不下降子序列。
两段在位置 i 处相接，-1 是因为 i 本身被算了两次
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e5+5;

struct sgt {
    int sum[N<<2], len[N<<2], tag[N<<2];

    void push_up(int x) {
        len[x] = len[x<<1] + len[x<<1|1];
        sum[x] = sum[x<<1] + sum[x<<1|1];
    }
    void apply(int x, int t) {
        tag[x] += t;
        sum[x] += len[x]*t;
    }
    void push_down(int x) {
        apply(x<<1, tag[x]);
        apply(x<<1|1, tag[x]);
        tag[x] = 0;
    }
    void build(int x, int l, int r) {
        len[x] = r - l + 1;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(x<<1, l, mid); build(x<<1|1, mid+1, r);
        push_up(x);
    }
    void modify(int x, int l, int r, int L, int R, int v) {
        if (L <= l && r <= R) { apply(x, v); return; }
        push_down(x);
        int mid = (l + r) >> 1;
        if (L <= mid) modify(x<<1, l, mid, L, R, v);
        if (R > mid) modify(x<<1|1, mid+1, r, L, R, v);
        push_up(x);
    }
    int query(int x, int l, int r, int p) {
        if (l == r) return sum[x];
        push_down(x);
        int mid = (l + r) >> 1;
        if (p <= mid) return  query(x<<1, l, mid, p);
        return query(x<<1|1, mid+1, r, p);
    }
#define build(n) seg.build(1,1,n)
#define modify(n,l,r) seg.modify(1,1,n,l,r,1)
#define query(n,p) seg.query(1,1,n,p)
} seg;

int a[N];
void init(int n) { for (int i = 1; i <= n; ++i) a[i] = query(n,i); }

int L[N], R[N];
int get(int n) {
    init(n);
    vector<int> cur;
    for (int i = 1; i <= n; ++i) {
        int p = upper_bound(cur.begin(), cur.end(), a[i]) - cur.begin();
        if (p == cur.size()) cur.push_back(a[i]); else cur[p] = a[i];
        L[i] = p+1;
    }
    cur.clear();
    for (int i = n; i >= 1; --i) {
        int p = upper_bound(cur.begin(), cur.end(), a[i]) - cur.begin();
        if (p == cur.size()) cur.push_back(a[i]); else cur[p] = a[i];
        R[i] = p+1;
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) ans = max(ans, L[i]+R[i]-1);
    return ans;
}

int main() {
    fast;
    int m, n; cin >> m >> n; build(n);
    for (int l, r; m; m--) cin >> l >> r, modify(n,l,r);
    cout << get(n);
    return 0;
}