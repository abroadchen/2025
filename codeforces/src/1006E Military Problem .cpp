//
// Created by Psy.C on 2026/10/28.
//

/**
真正学会的起点..
fa：父节点编号。
in：DFS 进入该节点的时间戳（该节点在 DFS 序中的位置）。
out：离开该节点时累计的 DFS 时间戳（子树最后一个节点的位置，即子树区间的右端点）。
son：小顶堆，存儿子节点编号（保证儿子按编号从小到大被访问，DFS 序确定、可复现，这是查询 k 的关键——同一棵树必须每一次都按同一顺序遍历，否则查询结果不稳定）
tr[ord].in = ++cnt;：进入节点 ord，时间戳自增，in 记录它是 DFS 序第几个。
a[cnt] = ord;：数组 a 记下"第 cnt 个是节点 ord"，即建立 DFS 序 ↔ 节点的映射。
while (!son.empty())：依次弹出小顶堆顶（最小编号儿子），递归 dfs，弹出一个就 pop 掉确保每个儿子都遍历。
因为用小顶堆，儿子按编号升序遍历，顺序稳定。
tr[ord].out = cnt;：所有子树都访问完后，cnt 是这棵子树最后一个节点的时间戳，存入 out。
关键性质：经过 DFS，节点 u 的子树在 DFS 序中占据连续区间 [in[u], out[u]]。out[u]-in[u]+1 即子树大小
外层 while (cin >> n >> q)：处理多组测试数据（读入 n、q，读到 EOF 结束）。

建树：tr[1].fa = 0（根），读入每个节点 i (i≥2) 的父节点 fa，并把它 push 进父节点的小顶堆。

cnt=0; dfs(1);：从根开始做 DFS，得到每个节点的 in、out 及 DFS 序数组 a
子树大小 = out - in + 1，若 k-1 > out - in（即 k > 子树大小），节点不足，输出 -1。
否则，子树 DFS 序区间为 [in,u],[out,u]，第 k 个节点的时间戳是 in + k - 1，对应节点为 a[in+k-1]，直接输出。
每组数据结束后 delete[] tr 释放内存（注意：若 n 为 0，new 的数组大小 n+1，delete 也安全）

建树 + DFS：O(n log n)（每个儿子入堆/出堆 log 代价）。
每次查询：O(1)（直接取 a[in+k-1]）。
总复杂度约 O(n log n + q)，多组数据累加
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 2e5+5;

struct node {
    int fa, in, out;
    priority_queue<int, vector<int>, greater<>> son;
} *tr;

int cnt, a[N];
void dfs(int ord) {
    tr[ord].in = ++cnt;
    a[cnt] = ord;
    while (!tr[ord].son.empty()) {
        dfs(tr[ord].son.top());
        tr[ord].son.pop();
    }
    tr[ord].out = cnt;
}

int n, q, u, k;
int main() {
    fast;
    while (cin >> n >> q) {
        tr = new node[n+1]; tr[1].fa = 0;
        for (int i = 2; i <= n; i++) {
            cin >> tr[i].fa;
            tr[tr[i].fa].son.push(i);
        }
        cnt = 0;
        dfs(1);
        while (q--) {
            cin >> u >> k;
            if (k-1 > tr[u].out-tr[u].in) cout << "-1\n";
            else cout << a[tr[u].in+k-1] << '\n';
        }
        delete[] tr;
    }
    return 0;
}