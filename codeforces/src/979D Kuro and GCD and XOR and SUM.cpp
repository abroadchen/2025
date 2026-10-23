//
// Created by Psy.C on 2026/10/23.
//

/**
真正学会的起点..
t[p] 是一个 Trie 节点，c[0]、c[1] 是左右孩子（对应二进制位 0/1），v 是该子树中所有数的最小值
分根策略：代码维护 p[d] —— 每个除数 d 对应一棵单独的 Trie 根。所有能被 d 整除的 x 都插入 p[d] 这棵 Trie
从最高位 bit 20 到 bit 0 逐位插入 x 的二进制位。
每个经过的节点（含根）都 v = min(v, x)，即保存"该子树中出现过的最小值"
目标是找集合中使 x xor y 最大、且满足 x+y <= s 的数 y。
若根的最小值 v 已使 x+v > s，则无解，返回 -1。
贪心走位：想最大化 xor，应该优先让异或位为 1，即优先走 -x>>i&1（与 x 该位相反）的分支；但前提是该分支存在且 x + 该分支最小值 <= s（保证有可行解满足和约束）。
若不行，退回走与 x 同位的分支。
最终到达叶子，返回该叶子保存的最小值 t[p].v，即为满足条件且 xor 最大化的最优数（返回的是该分支的最小值，贪心保证 xor 最大）
操作 1 x：把 x 插入集合。枚举 x 的所有因子 j（及对称因子 x/j），把 x 插入到 p[j] 和 p[x/j] 两棵 Trie（即所有能整除 x 的除数的 Trie）。用 b[x] 去重，确保 x 只插入一次。
操作 2 x k s：查询。
若 x % k != 0，即 x 不是 k 的倍数——由于要查的 y 必须满足 x+y 相关约束，而这里直接输出 -1（因为问题要求 x 与结果同余/相关，这里特判 x 不能被 k 整除则无解…… 实际是查询逻辑中 x % k ? -1 是题目自身要求，即当 x 不能被 k 整除时直接无解）。
否则在 p[k]（所有能被 k 整除的数集合的 Trie）上 get(x, s, p[k])，求满足 x+y<=s 且 x xor y 最大的 y，输出之

-（按位取反，一元）‍ 优先级最高，最先计算；
>>（右移，二元）‍ 优先级其次；
&（按位与，二元）‍ 优先级最低，最后计算
-x >> i & 1 提取的是 x 的第 i 位取反后的值（即 1 - (x 的第 i 位)）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e5+5, M = 3e7+5, inf = 1e9;

struct node { int v, c[2]; } t[M];

int o;
void init(int x, int r) {
    t[r].v = min(t[r].v, x);
    for (int i = 20, p = r; i >= 0; --i) {
        if (t[p].c[x>>i&1]) p = t[p].c[x>>i&1], t[p].v = min(t[p].v, x);
        else p = t[p].c[x>>i&1] = ++o, t[p].v = x;
    }
}
int get(int x, int s, int r) {
    if (x + t[r].v > s) return -1;
    int q = 0, p = r;
    for (int i = 20; i >= 0; --i) {
        if (t[p].c[~x>>i&1] && x+t[t[p].c[~x>>i&1]].v <= s) p = t[p].c[~x>>i&1];
        else p = t[p].c[x>>i&1];
    }
    return t[p].v;
}

int p[N], n;
bool b[N];
int main() {
    fast;
    //为每个可能的除数 i 预分配一个根节点，初始最小值为 inf（表示空）
    for (int i = 1; i <= N-5; ++i) t[p[i]=++o].v = inf;
    cin >> n;
    for (int i = 0, o, x, k, s; i < n; ++i) {
        cin >> o >> x;
        if (o&1) {
            if (!b[x]) {
                b[x] = 1;
                for (int j = 1; j*j <= x; ++j) if (!(x%j)) {
                    init(x, p[j]);
                    if (j*j != x) init(x, p[x/j]);
                }
            }
        }
        else cin >> k >> s, cout << (x%k ? -1 : get(x, s, p[k])) << '\n';
    }
    return 0;
}