//
// Created by Psy.C on 2026/9/7.
//
/**
N=55：二进制位最多 55 位（long long 范围）。
M=1e4+5：树节点数组上限。
节点字段：
l, r：该节点表示的区间 [l, r]。
val：该节点自己那一层的值（n2[u] 是否为 0 → 0/1）。
num：该区间的中点（也是这个节点本身对应数字，即把区间按二叉树从下到上编号）。
sum：子树内所有 val 的总和。
ch：左孩子下标。
注意：这棵树只有左孩子 ch，没有右孩子——因为它是"向右连续堆叠"的特殊二叉树

if (cnt == tot || l > r) return 0; 终止条件：层数达到 tot，或区间非法。
u = ++cnt：节点编号 cnt 从 1 递增。
记录区间 [l, r]。
val = n2[u] ? 0 : 1：取当前层的二进制位（n2[u]），取反（0→1，1→0）作为 val。
num = (l+r)>>1：区间中点。
只建左孩子：ch = build(l, mid-1)——递归到左半边区间。
sum = 左孩子.sum * 2 + val

若节点区间被查询区间完全覆盖，直接返回该子树和 sum。
l > r 返回 0。
累加自己那一位：若自己 num 落在查询区间内，加上 val。
若查询区间延伸到 num 左侧，递归左孩子查 [l, min(num-1, r)]。
若查询区间延伸到 num 右侧，把区间平移：[l-num, r-num]（受 [1, r-num] 约束）再查左孩子。
这里体现了这棵树的"自相似"性：右半侧的查询会被"平移映射"回左孩子（因为树向右是按某种比例扩展的），因此始终只需要向左递归。这正是 sum*2 的成因（右半侧是左半侧的"复制+平移"）。

tp = n = rd()：读入 n；若 n=0 输出 "0" 结束。

二进制分解：while(tp>0) n2[++tot]=tp%2, tp/=2;

把 n 从低位到高位存进 n2[1..tot]。例如 n=5(101₂) → n2[1]=1,n2[2]=0,n2[3]=1。
计算总大小 s：


 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

constexpr int N = 55, M = 1e4+5;
struct node { int l, r, val, num, sum, ch; } t[M];

int cnt, tot, n2[N];
inline int build(int l, int r) {
    if (cnt == tot || l > r) return 0;
    int u = ++cnt;
    t[u].l = l, t[u].r = r;
    t[u].val = n2[u] ? 0 : 1, t[u].num = (l+r)>>1;
    t[u].ch = build(l, ((l+r)>>1)-1);
    t[u].sum = t[t[u].ch].sum*2 + t[u].val;
    return u;
}

inline int query(int i, int l, int r) {
    if (t[i].l >= l && t[i].r <= r) return t[i].sum;
    if (l > r) return 0;
    int ans = 0;
    if (t[i].num >= l && t[i].num <= r) ans = t[i].val;
    if (l < t[i].num) ans += query(t[i].ch, l, min(t[i].num-1, r));
    if (r > t[i].num) {
        int ll = max((long long)1, l-t[i].num), rr = r - t[i].num;
        ans += query(t[i].ch, ll, rr);
    }
    return ans;
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int tp, n, s, x, y, ql, qr, ans;
signed main() {
    fast;
    tp = n = rd();
    if (!n) { cout << "0\n"; return 0; }
    while (tp > 0) { n2[++tot] = tp%2, tp /= 2; }
    s = x = tot, y = 1;
    while (x > 1) { s = ((x-1)*2+1)*y + s - x*y, x -= 1, y *= 2; }
    ql = rd(), qr = rd(); build(1, s);
    ans = qr - ql + 1, ans -= query(1, ql, qr);//减去区间内 sum（取反后的 1 的个数）
    cout << ans << '\n';
    return 0;
}