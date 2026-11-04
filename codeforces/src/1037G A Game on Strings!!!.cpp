//
// Created by Psy.C on 2026/11/4.
//

/**
真正学会的起点..
M = 26：小写字母数量。
nxt[i][c]：位置 i 及之后，字符 c 下一次出现的位置（不存在则为 n+1）。
pre[i][c]：位置 i 及之前，字符 c 最后一次出现的位置（无则为 0）。
val[r]：以 r 结尾的前缀区间的某种代表性 SG 值。
fl[r][c]、fr[l][c]：缓存的区间 SG 结果
空区间：l > r 返回 0（SG 值为 0 的是必败态）。
计算 mex（minimum excluded，最小未出现非负整数）：
枚举字符 c，若该字符在 [l, r] 内出现（nxt[l][c] <= r），说明可以走到某个后续状态。
每个走步的 SG 值用 fr[l][c] ^ val[nxt[l][c]] ^ val[pre[r][c]] ^ fl[r][c] 这个异或组合计算出来，标记到 bitset。
最后返回第一个未标记的 i，即 mex。
这里的博弈本质上是"[green Hackenbush / 异或游戏]"型的区间棋子游戏，val 前缀数组用于把 get 的 O(n) 计算转成 O(1) 组合
每个位置复制上一位置的 pre，再更新当前字符的最后出现位置为 i。即 pre[i][c] = 前缀 [1..i] 中 c 的最后位置
从右往左：nxt[i][c] = 后缀 [i..n] 中 c 的第一次出现位置。边界均设为 n+1（表示不存在）。
v[j] = j：初始化一个字符下标向量（后面用于排序）
lst = 字符 s[r] 在 r 之前最后一次出现的位置。
val[r] = val[lst] ^ get(lst+1, r-1)：用前缀异或特性，借助上次同字符位置递推 val，避免 O(n²) 计算
按各字符在前缀 [1..r] 中最后一个出现位置从大到小排序 26 个字符。这决定了下一次 get 调用时哪些区间已可复用
fl[r][c] = get(pre[r][c]+1, r)：计算并从 pre[r][c]+1 到 r 的区间 SG，缓存到 fl[r][c]（供 get 复用，用排序保证按需缓存）。
当 s[r+1] 这个字符在 [j, r] 内时，把 get(j, r) 结果缓存到 fr[j][c]，供后续右侧查询复用。
关键优化点：get 里用到的 fl、fr、nxt l]、val 等都是预计算缓存，使得原本需要反复递归的区间 SG 变为 O(1) 组合查询
每次输入区间 [l, r]，调用 get(l, r) 得到 SG 值。
SG ≠ 0 → 先手（Alice）必胜，否则 Bob 胜（Sprague-Grundy 定理
*/
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5+10, M = 26;

int nxt[N][M], fl[N][M], fr[N][M], val[N], pre[N][M];
int get(int l, int r) {
    if (l > r) return 0;
    bitset<32> b;
    for (int c = 0; c < M; c++) if (nxt[l][c] <= r)
        b[fr[l][c]^val[nxt[l][c]]^val[pre[r][c]]^fl[r][c]] = 1;
    for (int i = 0; ; i++) if (!b[i]) return i;
}

char s[N];
int m, n;
vector<int> v(M);
int main() {
    scanf("%s%d", s+1, &m); n = strlen(s+1);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < M; j++) pre[i][j] = pre[i-1][j];
        pre[i][s[i]-'a'] = i;
    }
    for (int j = 0; j < M; j++) nxt[n+1][j] = n+1, v[j] = j;
    for (int i = n; i >= 1; i--) {
        for (int j = 0; j < M; j++) nxt[i][j] = nxt[i+1][j];
        nxt[i][s[i]-'a'] = i;
    }
    for (int r = 1; r <= n; r++) {
        int lst = pre[r-1][s[r]-'a'];
        val[r] = val[lst]^get(lst+1,r-1);
        ranges::sort(v,[&](int x, int y) {
            return pre[r][x] > pre[r][y];
        });
        for (auto c : v) fl[r][c] = get(pre[r][c]+1, r);
        if (r != n) for (int c = s[r+1]-'a', j=r; j > pre[r][c]; j--)
            fr[j][c] = get(j, r);
    }
    for (int i = 1, l, r; i <= m; i++)
        scanf("%d%d", &l, &r), printf(get(l,r)?"Alice\n":"Bob\n");
    return 0;
}