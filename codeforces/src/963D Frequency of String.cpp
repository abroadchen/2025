//
// Created by Psy.C on 2026/10/21.
//
/**
s：已给的文本串（从下标 1 起存）；t：每次查询的模式串。
n、q、k、m 分别为文本长度、查询次数、目标子串起始位参数、模式串长度。
b[26]：26 个 bitset，每个记录字母在 s 中的每个位置是否出现。
cur：当前匹配位置集。
v：存放匹配起点
读入文本串 s（1-based），n 为长度；读入查询数 q。
初始化 26 个 bitset 全 0。
对文本每个位置 i，把字母 s[i] 对应 bitset 的第 i 位设为 1（flip(i) 在此场景等价于置 1，因为初始为 0）
每个查询：读 k，读入模式串 t（1-based），m 为 t 长度。
初始化 cur 全 1（set()）。
核心匹配：对模式串第 j 个字符（从 1 到 m），把该字符在文本中的出现 bitset 左移 (m-j) 位后与 cur 做与运算。
一个关键技巧：模式串第 j 位在文本中的起点 p，需满足 s[p+j-1] == t[j]，即 p+(j-1) 是字符 t[j] 的出现位，等价于 p 在 b[t[j]] << (j-1) 中为 1。
但这里左移 m-j 而非 j-1，为的是让匹配"以结束点对齐"——理解：把所有字符的对齐基准统一到模式串结尾。左移 m-j 使得最终 cur 中为 1 的位置表示能与整个模式串匹配的结束位置（end position）。这样 cur 上每个 1 就是一个完整匹配的结束下标。
这样做的意义：找到所有匹配（的结束位置）后，再结合 k 求"最短覆盖 k 个匹配的窗口"
遍历 cur 中所有为 1 的位（_Find_first / _Find_next），收集到 v（即所有匹配结束位置，v 天然递增序）。
sz 为匹配个数，ans 初值 inf。
对每个 j 从 k-1 到 sz-1：计算 v[j] - v[j-k+1] + m。
v[j] 是第 j 个匹配的结束位置，v[j-k+1] 是往前数第 k 个匹配的结束位置。
v[j] - v[j-k+1]：这 k 个匹配中首末结束位置的跨度；加上 m 后 = 覆盖这 k 个（连续取 k 个）匹配的子串长度（从第一个匹配的起始到最后一个匹配的结束）。
对所有滑动窗口取最小，即"覆盖至少 k 个匹配的最短子串长度"。
若 ans 仍为 inf（找不到 k 个匹配），输出 -1；否则输出 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
using namespace std;

constexpr int N = 2e5+50, inf = 0x3f3f3f3f;
inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}
template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}

char s[N], t[N];
int n, q, k, m;
bitset<N> b[26], cur;
vector<int> v;
int main() {
    fast;
    scanf("%s", s+1), n = strlen(s+1), q = rd();
    rep(i,0,25) b[i].reset();
    rep(i,1,n) b[s[i]-'a'].flip(i);
    rep(i,1,q) {
        k = rd(), scanf("%s", t+1), m = strlen(t+1), cur.set(), v.clear();
        rep(j,1,m) cur &= (b[t[j]-'a']<<(m-j));
        for (int p = cur._Find_first(); p != N; p = cur._Find_next(p))
            v.emplace_back(p);
        int sz = v.size(), ans = inf;
        rep(j,k-1,sz-1) ans = min(ans, v[j]-v[j-k+1]+m);
        if (ans == inf) write(-1), putchar('\n');
        else write(ans), putchar('\n');
    }
    return 0;
}