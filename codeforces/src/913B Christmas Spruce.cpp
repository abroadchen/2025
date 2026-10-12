//
// Created by Psy.C on 2026/10/12.
//
/**
读入一棵树（父节点数组建树），节点编号 1..n。
对每个节点调用 check(i)，若任意一个节点不通过则输出 "No"，全部通过则输出 "Yes"。
check(o) 判定节点 o 是否满足条件：若 o 不是叶子，则其至少有 3 个叶子孩子
tr[i]：树节点。
id：节点编号。
fa：父节点（root 的 fa 可能为 0 或未设）。
k：该节点的孩子个数。
kid[N]：孩子编号数组
x.k == 0（叶子节点）‍：返回 true（叶子总是合法的）。
x.k < 3（非叶子但孩子数 < 3）‍：返回 false。说明"非叶子节点必须有足够多的孩子"。
否则（k ≥ 3）：统计有多少个孩子是叶子（即 tr[kid[i]].k == 0，该孩子没有孩子），记 cnt。若叶子孩子数 ≥ 3 返回 true，否则 false。
所以 check 的含义是：每个非叶子节点必须至少有 ≥3 个孩子，且其中至少 3 个是叶子
从 i=2 开始读每个节点的父节点 tr[i].fa，并把 i 挂到父节点的孩子列表里（kid 数组，k 递增）。
注意：根节点是节点 1（因为输入从 i=2 才开始，1 没被读为任何人的孩子，即根）。
然后遍历所有节点，只要 check(i) 为假就输出 "No" 并退出；都通过则输出 "Yes"
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e3+1;

struct node { int id, fa, k, kid[N]; } tr[N];

bool check(int o) {
    node x = tr[o];
    if (x.k == 0) return 1;
    if (x.k < 3) return 0;
    int cnt = 0;
    for (int i = 1; i <= x.k; ++i)
        if (tr[x.kid[i]].k == 0) cnt++;
    return cnt >= 3;
}

int main() {
    fast;
    int n; cin >> n;
    for (int i = 2; i <= n; ++i) {
        cin >> tr[i].fa;
        tr[tr[i].fa].kid[++tr[tr[i].fa].k] = i;
    }
    for (int i = 1; i <= n; ++i)
        if (!check(i)) { cout << "No"; return 0; }
    cout << "Yes";
    return 0;
}