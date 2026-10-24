//
// Created by Psy.C on 2026/10/24.
//

/**
真正学会的起点..
v2[x]：表示"这个数 x 是否已经在给定集合 / 已访问"（初值 1=未给定，0=给定，见下）。也可看作点是否存在且未访问。
v1[x]：互补遍历的访问标记。
all = (1<<n)-1：所有位全 1 的数（即 2^n - 1）
典型的"补图 SOS 遍历"套路：
tp==2：从"给定数字"出发，把 v2[x] 置 1（标记访问），然后跳到 all^x（补集，按位取反的数）‍去走 v1 那套。
tp==1：从补集出发，标记 v1[x]，然后：
先调 dfs(x,2)（回到原数字侧）。
然后枚举 x 的每一个 最高位（set bit）‍，逐个尝试去掉某一位 x^(s&-s)，再递归 dfs（这是遍历"比 x 在某一位上少一比特的子集"→ 即所有子集，形成 SOS 遍历）。
关键：v2[x] 初值 1，只有给定数字设成 0。外层主循环对每个 !v2[i]（给定且在 v2 中未访问）触发 dfs，统计分量数 ans
读入 n，all=全1数字。
v2 全置 1（默认"未给定/已处理"），v1 全 0。
读入 m 个给定数字 x，把 v2[x]=0（标记为"给定点、待访问"）。
外层：对每个仍是 0（未访问的给定点）‍，ans 加一，然后从它触发一次完整 dfs（把与它连通的所有点都标记掉）。
最终 ans = 给定集合中互不连通的连通分量数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1<<22;

bool v1[N], v2[N];
int all;
inline void dfs(int x, int tp) {
    if (tp == 2) {
        if (v2[x]) return;
        v2[x] = 1, dfs(all^x, 1);
    } else {
        if (v1[x]) return;
        v1[x] = 1, dfs(x, 2);
        int s = x;
        while (s) dfs(x^(s&-s), 1), s ^= s&-s;
    }
}

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

int n, m, x, ans;
int main() {
    fast;
    read(n); all = (1<<n)-1;
    for (int i = 0; i < 1<<n; ++i) v1[i] = 0, v2[i] = 1;
    read(m);
    while (m--) read(x), v2[x] = 0;
    for (int i = 0; i < 1<<n; ++i)
        if (!v2[i]) ++ans, dfs(i, 2);
    cout << ans << '\n';
    return 0;
}