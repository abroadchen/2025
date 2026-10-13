//
// Created by Psy.C on 2026/10/13.
//
/**
N 约为操作数规模；inf = 0x3f3f3f3f（约 10.7 亿）作为权值域上界。
每个线段树节点记录：区间 [l, r]、左右儿子指针 ls/rs、节点区间元素个数 sum。开 N*100 是因为可持久化每次插入沿树深新增节点，需预留足够空间
可持久化核心：tr[++cnt] = tr[k] 先复制旧节点，再把 k 指向新下标，然后只递归更新路径上的一个儿子，另一个儿子仍共享旧节点。这样每次更新只新建 O(log W) 个节点，形成一条"版本链"。

v 可正可负：+1 表示把位置 p 的计数加 1，-1 表示减 1
标准权值线段树区间求和：求下标落在 [l, r] 范围内的元素个数。这里 tr[k].l/tr[k].r 是节点存的实际区间
用 map<string,int> 把操作里的字符串 key（人名等）映射成整数 id，供线段树下标使用
维护两个可持久化结构：

rt[i]：以 key(id) 为下标、存该 key 当前的值 → 用于查询某 key 的值。
rt2[i]：以 值(val) 为下标、存每个值出现的次数 → 用于做"小于某值共有多少个"的排名查询。
每次操作在 i 上新建版本，rt[i]/rt2[i] 默认先继承 i-1 的版本
给 key 赋值：若原来有值就用 +val-pre 修正成 val，并同步在 rt2 上把旧值次数 -1、新值次数 +1；若无旧值则直接插入
删除 key：把该 key 的值减成 0，同时该值在 rt2 中的计数 -1。若本身没值（pre==0）则什么都不做
查询 key 的"名次"：先取该 key 当前值 pre；若值为 0 输出 -1；否则在 rt2 中查值在 [1, pre-1] 区间共多少个（即严格小于 pre 的元素个数）。fflush(stdout) 用于及时输出
撤销最近 x 次操作：直接把第 i 个版本的根指针指向 i-x-1 时刻的版本（回滚 x+1 步，回退到"当前这步还没执行"之前的状态）。这正是可持久化的价值——任何历史版本都能被直接引用，撤销即时 O(1)
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5+1e2, inf = 0x3f3f3f3f;

struct node { int l, r, ls, rs, sum; } tr[N*100];

int cnt;
void update(int &k, int l, int r, int p, int v) {
    //复制旧节点 当前引用指向新节点 区间计数加 v
    tr[++cnt] = tr[k],  k = cnt, tr[k].sum += v, tr[k].l = l, tr[k].r = r;
    if (l == r) return;//叶节点
    int mid = (l+r)>>1;
    if (p <= mid) update(tr[k].ls, l, mid, p, v);//递归左儿子
    else update(tr[k].rs, mid+1, r, p, v);
}
int query(int k, int l, int r) {
    if (tr[k].l > r || tr[k].r < l) return 0;
    if (tr[k].l >= l && tr[k].r <= r) return tr[k].sum;
    return query(tr[k].ls, l, r) + query(tr[k].rs, l, r);//部分相交 → 递归
}

map<string, int> mp;
int tot;
int get(const string& s) {
    if (!mp.contains(s)) mp[s] = ++tot;
    return mp[s];
}

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}
template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}

int n, rt[N], rt2[N];
int main() {
    rd(n);
    for (int i = 1; i <= n; ++i) {
        rt[i] = rt[i-1], rt2[i] = rt2[i-1];
        string s, s2; cin >> s;
        if (s == "set") {
            cin >> s2;
            int val, id = get(s2); rd(val);
            int pre = query(rt[i], id, id);//当前 key 的旧值
            if (pre) {//已有旧值 → 把旧值改掉
                update(rt[i], 1, inf, id, val-pre);
                update(rt2[i], 1, inf, pre, -1);//旧值出现次数 -1
                update(rt2[i], 1, inf, val, 1);//新值出现次数 +1
            } else {//无旧值 → 新增
                update(rt[i], 1, inf, id, val);
                update(rt2[i], 1, inf, val, 1);
            }
        } else if (s == "remove") {
            cin >> s2;
            int id = get(s2), pre = query(rt[i], id, id);
            if (!pre) continue;//本来就没值 → 跳过
            update(rt[i], 1, inf, id, -pre);//key 的值清 0
            update(rt2[i], 1, inf, pre, -1);
        } else if (s == "query") {
            cin >> s2;
            int id = get(s2), pre = query(rt[i], id, id);
            if (!pre) puts("-1");//无值 → 输出 -1
            else write(query(rt2[i], 1, pre-1)), putchar('\n');//输出严格小于该值的个数
            fflush(stdout);
        } else if (s == "undo") {
            int x; rd(x);
            rt[i] = rt[i-x-1], rt2[i] = rt2[i-x-1];
        }
    }
    return 0;
}