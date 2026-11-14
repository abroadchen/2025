//
// Created by Psy.C on 2026/11/14.
//

/**
真正学会的起点..
a[i]：第 i 个顶点的剩余可接边数（即原始度数需求，将在构造中递减）。
id[]：按度数从大到小排序的顶点编号（iota 填 1..n 后 sort 按 a[x] 降序）。
G[i]：存顶点 i 的邻居（最终树的边）。
d：已经接的边数（最终应等于 n−1）。
n：顶点个数
iota(id+1, id+n+1, 1) 的意思是：从 id[1] 开始，依次给 id[1]、id[2] … id[n] 填入 1、2、3 … n，即把 id 数组初始化为递增的编号序列 {1,2,...,n}
把顶点按需求度数 a 从高到低排列，得到顺序 id[1] ≥ id[2] ≥ …。
按降序顺序，id[i]（剩余度数需求最多的）要接到某个已有顶点上。

a[id[i]]==0：如果当前顶点剩余度数已经是 0（没有余量再给它加边），就不可能再合理地接到树上 → NO。
常规情况 a[id[i-1]] > 0：直接把当前最大剩余度的顶点 id[i-1] 和 id[i] 之间连一条边。两边各 --（都消耗一个度数槽），记录边，d++。因为数组已按度数降序，id[i-1] 是当前剩余度数里排在前面的最大者，接它最安全。
备用情况 a[id[i-1]] == 0：排在前面的顶点已没度数空间，则在它之前的顶点 id[j] (j<i-1) 里找一个还有正剩余度数的连边。若找到就接上并 --；若全都为 0（f 保持 1）→ NO。d += (i==n) 是处理最后一个顶点若其接的是"上一批"时的边数累计细节
输出 YES＋总边数 d（应为 n−1），再换行输出 n-1，随后逐条输出树边
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= (n); i++)
using namespace std;

constexpr int N = 505;

int n, a[N], id[N], d;
vector<int> G[N];
int main() {
    fast;
    cin >> n;
    rep(i,n) cin >> a[i];
    iota(id+1, id+n+1, 1);
    sort(id+1, id+n+1, [](int x, int y) {
        return a[x] > a[y];
    });
    for (int i = 2; i <= n; i++) {
        if (a[id[i]] == 0) { cout << "NO"; return 0; }
        if (a[id[i-1]] > 0) {
            a[id[i-1]]--; a[id[i]]--; G[id[i-1]].push_back(id[i]);
            d++;
        } else {
            d += i == n;
            bool f = 1;
            rep(j,i-1) if (a[id[j]] > 0) {
                a[id[j]]--; a[id[i]]--; G[id[j]].push_back(id[i]); f = 0;
                break;
            }
            if (f) { cout << "NO"; return 0; }
        }
    }
    cout << "YES " << d << '\n' << n-1;
    rep(i,n) for (int j : G[i]) cout << '\n' << i << ' ' << j;
    return 0;
}