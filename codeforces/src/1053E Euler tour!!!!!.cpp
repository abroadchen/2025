//
// Created by Psy.C on 2026/11/8.
//

/**
真正学会的起点..
vis[x]：标记数字 x 是否已被"使用/出现"。
now：get() 从它开始找空闲数字（贪心、单调递增，只用递增就不需重置）。
n：数字种类数。
int pre[N], suf[N];      // 链表：每个位置的前驱/后继
int a[N];                // 数组本体，0 表示待填
int nxt[N], m;           // nxt[i]：位置 i 处数字的"下一次出现"位置
m = 2n − 1 是数组总长度
任何一处发现不可能时，立即输出 no 并终止进程
作用：当需要"凭空"填入一个新数字时，从 now 开始找第一个没被用过的编号。
因为 now 单调递增，整体分配是 O(m)。
now > n 意味着允许的数字编号不够用，直接 no
把双向链表中 闭区间 [l, r] 整体摘掉：让 l 的前驱直接连到 r 的后继。
被摘除的节点在后续遍历中不可见，表示这些位置已经被消费/确定，不再参与外层处理。
对应"边界已经匹配完毕、内部也已填完"的块被整体移除
这是在已确定的部分里做局部的同类合并/回填，让块的边界更"干净"。
第一个 while：当三个相邻位置分别是 0, x, x 时，说明该数字 x 已在两侧出现，把中间那个 0 也回填成 x，删除中间那两项，向前回退指针。
三种形态统一化简为：0 X X → X X X？不——它把 0 填成 a[suf[suf[x]]]（即右侧 X），并 del 掉两条（原 suf[x]、suf[suf[x]]）。
第二个 while：对称地把 X X 0 中的 0 填成 X X 再合并。
x = pre[pre[x]] 回退两个位置再次尝试，保证可以连锁合并。
目的：消除搜索边界的零散残留，让块边界对齐，是原版算法效率的一部分优化
[l,r] 的节点数若为奇数则直接无解（块的匹配结构要求偶数个节点——左右配对，内部成对）
i 从左向右扫链表中还存在的节点；若位置 i 处的数字还有下一次出现 nxt[i]，说明 i 是某个匹配块的左边界。
若 nxt[i] > r 则下一个匹配点在块外 → 交错/越界 → no。
递归处理左边界和下一次出现之间的内部块：solve(suf[i], pre[nxt[i]])。
内部处理完就 del 掉 (suf[i], nxt[i]]（内部 + 右边界），nxt[i] 指向再下一次出现继续处理
n1 = 块内已填的数字个数；n2 = 块内节点总数（++n2）。
n2 = (n2 >> 1) + 1 表示块内"最多能容纳的数字种类数上界"（匹配成对的估算）。
存在性检查：已定数字数 > 可容纳上界 → 无解。
剩余可补数量 n2 -= n1，用 get() 分配新数字逐空填上。
若还不够填则 get() 里 now > n 会 out()
块内仍未填的空位全部填成 rt（外层块左边界字母/数字）‍，从而闭合外层块。
rt = a[pre[l]]，即当前块在链表中前一个位置已有的数字（就是"上一层"的字母）
对块内每个剩下的节点执行 merge，把零散同类合并、收尾对齐。

n==1：只有一个数字，m=1，直接 yes 输出 1。
读入数组，0 表示待填。
相邻位置不能出现相同的非零数字（否则无法构成合法的嵌套匹配）。
首尾若都已确定但不同 → 必然冲突 → no。
首尾合并：a[1] = a[m] = a[1]|a[m]——若一端为 0 则继承另一端的值，若都非零则已保证相等，用 a[1]|a[m]
构造哨兵式链表：0、1..m、m+1，每个节点前后相连。
pre[0]=0 让最左侧前驱指向自身（哨兵），方便链表边界判断
从右往左扫：vis[a[i]] 记录数字 a[i] 当前已知的最近一次出现（初始为 0 = 右哨兵）。
nxt[i] = vis[a[i]]：位置 i 处数字的下一次出现就是之前记录的那个位置。
然后更新 vis[a[i]] = i。
结果：nxt[i] 指向同一个数字在 i 右侧最近一次出现的位置（0 表示没有）
对整个数组 [1, m] 调用递归求解。
若中途没 out()，说明可解，输出 yes 及构造出的完整数组。


suf[tl] = tr
→ 让左邻居 tl 的后继直接指向右邻居 tr（跳过 l..r 整段）。

pre[tr] = tl
→ 让右邻居 tr 的前驱直接指向左邻居 tl
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e6+5;

inline void out() { cout << "no\n", exit(0); }

int vis[N], now = 1, n;
inline int get() {
    while (vis[now]) ++now;//跳过已被占用的数字
    if (now > n) out();
    vis[now] = 1;
    return now;
}

int pre[N], suf[N];
inline void del(int l, int r) {
    int tl = pre[l], tr = suf[r];
    suf[tl] = tr, pre[tr] = tl;
}

int a[N];
inline void merge(int l, int r, int &x) {
    while (x > l && suf[suf[x]] && suf[suf[x]] <= r && !a[x] && a[suf[x]] && a[suf[suf[x]]])
        a[x] = a[suf[suf[x]]], del(suf[x], suf[suf[x]]), x = pre[pre[x]];
    while (x > l && suf[suf[x]] && suf[suf[x]] <= r && a[x] && a[suf[x]] && !a[suf[suf[x]]])
        a[suf[suf[x]]] = a[x], del(suf[x], suf[suf[x]]), x = pre[pre[x]];
}

int nxt[N];
inline void solve(int l, int r) {
    if (r-l&1) out();
    for (int i = l; i <= r; i = suf[i]) while (nxt[i]) {
        if (nxt[i] > r) out();//该数字的下次出现越出当前块 → 不合法
        solve(suf[i], pre[nxt[i]]);//递归处理 i 与下一次出现 (nxt[i]) 之间的内部
        del(suf[i], nxt[i]);//该块内部处理完毕，摘除 (i, nxt[i]] 区间
        nxt[i] = nxt[nxt[i]];//跳到该数字的"再下一次"出现
    }
    int n1 = 0, n2 = 0, rt = a[pre[l]];
    for (int i = l; i <= r; i = suf[i]) n1 += a[i] > 0, ++n2;
    n2 = (n2>>1) + 1;
    if (n1 > n2) out();
    n2 -= n1;
    for (int i = l; i <= r && n2; i = suf[i])
        if (!a[i]) a[i] = get(), --n2;
    for (int i = l; i <= r; i = suf[i]) merge(l-1, r, i);
    for (int i = l; i <= r; i = suf[i]) if (!a[i]) a[i] = rt;
}

int m;
int main() {
    fast;
    cin >> n;
    if (n == 1) return cout << "yes\n1", 0;
    m = (n<<1) - 1;
    for (int i = 1; i <= m; ++i) cin >> a[i];
    for (int i = 2; i <= m; ++i)
        if (a[i] && a[i-1] && a[i] == a[i-1]) out();
    if (a[1] && a[m] && a[1] != a[m]) out();
    a[1] = a[m] = a[1]|a[m];
    for (int i = 0; i <= m+1; ++i) pre[i] = i-1, suf[i] = i+1;
    pre[0] = 0;
    for (int i = m; i >= 1; --i)
        if (a[i]) nxt[i] = vis[a[i]], vis[a[i]] = i;
    solve(1, m); cout << "yes\n";
    for (int i = 1; i <= m; ++i) cout << a[i] << ' ';
    return 0;
}