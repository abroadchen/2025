//
// Created by Psy.C on 2026/10/10.
//
/**
把原数组 a 的值离散化为排名（1..不同的值个数）。原数组相同值 → 相同离散值。这是为了后续按"相同值"分组
把原序列中连续相同的值合并成一段（一个 node）：

st：段在原序列的起始位置
sz：该段的值（离散化后的值）
len：该段长度
h：段编号
这样得到 cnt 段，且相邻两段的 sz 一定不同（因为连续相同已被合并）
优先队列 pq 按 len 大者优先（因为是小顶堆 + 反号排序，实际是长度大的先出），长度相同按 st 大者（靠后）先出。即优先处理"最长、最靠右"的段
用 pre / nxt 维护段序列的双向链表——但这链表存的是"段编号的原顺序"，节点顺序即原序列段顺序
每次从堆顶取"当前最长段"，ans++，然后：

若该段已被标记 f（已并移除），ans-- 并跳过
否则标记 f[x.h] = 1，调用 get(x.h) 做合并
若当前段 x 的左右邻段 pre[x] 和 nxt[x] 的值相同（sz 相等）：说明从原序列看，pre[x] 段的右侧 nxt[x] 段本来被 x 隔开、但它们值相等。此时做"合并"——把 nxt[x] 并入 pre[x]（长度相加），从链表移除 nxt[x]，并把合并后的 pre[x] 重新入堆。f[nxt[x]]=1 标记。
这一步的意义：删除 x 段后，左右同值的段会连在一起，按题意可能需要再次合并。
否则（左右值不同）：直接从链表里移除当前段 x
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 2e5+5;

struct node {
    int sz, h, st, len;
    friend bool operator<(const node& x, const node& y) {
        return x.len == y.len ? x.st > y.st : x.len < y.len;
    }
} q[N];

int pre[N], nxt[N];
bool f[N];
priority_queue<node> pq;
void get(int x) {
    if (q[pre[x]].sz == q[nxt[x]].sz) {
        f[nxt[x]] = 1;
        q[pre[x]].len += q[nxt[x]].len;
        pq.push(q[pre[x]]);
        nxt[pre[x]] = nxt[nxt[x]];
        pre[nxt[nxt[x]]] = pre[x];
    } else {
        nxt[pre[x]] = nxt[x];
        pre[nxt[x]] = pre[x];
    }
}

int n, a[N], b[N], cnt, ans;
signed main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i], b[i] = a[i];
    sort(b+1, b+1+n);
    for (int i = 1; i <= n; ++i)
        a[i] = lower_bound(b+1, b+1+n, a[i]) - b;
    for (int i = 1; i <= n; ) {
        int u = a[i]; q[++cnt].st = i; q[cnt].sz = a[i];
        while (i <= n && a[i] == u) q[cnt].len++, i++;
        q[cnt].h = cnt;
        pq.push(q[cnt]);
    }
    for (int i = 1; i < cnt; ++i) nxt[i] = i+1;
    for (int i = 2; i <= cnt; ++i) pre[i] = i-1;
    while (!pq.empty()) {
        ans++;
        auto x = pq.top(); pq.pop();
        if (f[x.h]) { ans--; continue; }
        f[x.h] = 1;
        get(x.h);
    }
    cout << ans;
    return 0;
}