//
// Created by Psy.C on 2026/9/17.
//
/**
now：当前节点编号；l、r：当前子树允许的键值范围（开区间 (l, r)）。
若 now == -1 递归返回（空孩子）。
判断条件是以 BST 性质从根一路"合法路径"走下来的节点才算有效：
根节点第一次调用范围是 (-1, inf+1)，即整个值域，恒有效。
往左孩子走：新的上限更新为 min(r, a[now]) → 左子树所有值必须小于父节点值，且继续受祖先约束 → dfs(ls[now], l, min(r, a[now]))。
往右孩子走：新的下限更新为 max(l, a[now]) → 右子树所有值必须大于父节点值 → dfs(rs[now], max(l, a[now]), r)。
只有当 l < a[now] < r 时，说明这个节点在从根出发、遵守所有祖先 BST 约束的"合法路径"上，标记 mp[a[now]] = true。

读入每个节点的键值、左孩子、右孩子。
hf[x] = true 表示编号 x 是某个节点的孩子，因此不可能作为根
根 = 没有被任何节点作为孩子引用的那个编号。
从根节点做一次合法路径 DFS，把所有"能通过 BST 约束合法到达"的键值标记进 mp。
然后遍历所有节点：如果该节点的 a[i] 没被标记进 mp → 说明这个键值没有任何一个合法节点持有（要么它在非法路径上，要么与原 BST 冲突），ans++。
输出 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5, inf = 1e9;
//a[i]=i 号节点的键值，ls[i]/rs[i]=左/右孩子节点编号
int a[N], ls[N], rs[N];
map<int, bool> mp;//记录"某个键值是否作为合法节点被访问到"
void dfs(int now, int l, int r) {
    if (now == -1) return;
    if (a[now] > l && a[now] < r) mp[a[now]] = true;
    dfs(ls[now], l, min(r, a[now]));
    dfs(rs[now], max(l, a[now]), r);
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

bool hf[N];
int main() {
    fast;
    int n = rd();
    for (int i = 1; i <= n; ++i) {
        a[i] = rd(), ls[i] = rd(), rs[i] = rd();
        if (ls[i] != -1) hf[ls[i]] = true;
        if (rs[i] != -1) hf[rs[i]] = true;
    }
    int rt = 0;
    for (int i = 1; i <= n; ++i)
        if (hf[i] == false) { rt = i; break; }
    dfs(rt, -1, inf+1);
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        if (mp[a[i]] == false) ans++;
    cout << ans << '\n';
    return 0;
}