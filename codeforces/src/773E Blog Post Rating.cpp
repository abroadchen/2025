//
// Created by Psy.C on 2026/9/9.
//
/**
N = 2e6+10：数组大小。
inf = 1e6（1000000）：坐标偏移量。
f[N] 是一整块数组，int *fa = f + N/2：让指针 fa 指向数组中部，从而让 fa[i] 支持下标为负的访问（i 从 -inf 到 +inf）。这是为了处理「位置可以取负坐标」的题目需求
标准并查集 find（带路径压缩）。fa[x] 是 x 的"父亲/指向"，用于找到 x 所属集合的代表元素
vis 同样做指针偏移，支持负下标，标记某个位置"是否已被占用/访问过"。
p、r 是维护 mex 的两把"游标"。p 指向当前 mex 候选，r 是个计数器/另一种游标

初始化：每个坐标的并查集父亲指向自己（每个位置独立、未占用）。
读入 n 次操作；每次读入目标位置 x，然后 x = find(x)：用并查集找到 x 所在集合的代表——即「当前未被占用的最近可用位置」
占用位置 x（标记 vis[x]）。
关键合并：把 x 并到 fa[x-1]，即 fa[x] 指向 fa[x-1]。这实现了一个「每个根指向它左边下一个可用空位」的链表：一旦 x 被占用，下次 find 会顺链找到 x 左边最近的未占用位置
若这次的 x 正好等于当前 mex 候选 p（即刚好把 mex 那一位占掉），则 mex 会上移，r++（把"mex 推进量"记一笔）
若 x < p（占用了一个在 p 左边、可能影响 mex 轨迹的位置）：r++。
特殊分支：p + r == 1 且 !vis[p] 时 p--（边界修正）。
否则 p--; r--（两个游标联动回退）
每次输出当前答案：p + i - r。这里 i 是已处理的操作数（即已有 i 个位置被插入），p - r 是修正后的 mex 基准，组合成"当前最小未出现正整数"
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 2e6+10, inf = 1e6;
int f[N], *fa = f + N/2;
int find(int x) {
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}

int n, p, r;
bool v[N], *vis = v + N/2;
int main() {
    fast;
    for (int i = -inf; i <= inf; ++i) fa[i] = i;
    cin >> n;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x; x = find(x);
        vis[x] = true;
        fa[x] = fa[x-1];
        if (x == p) r++;
        else if (x < p) {
            r++;
            if (p + r == 1) {
                if (!vis[p]) p--;
            } else {
                p--; r--;
            }
        }
        cout << p + i - r << '\n';
    }
    return 0;
}