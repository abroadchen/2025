//
// Created by Psy.C on 2026/9/24.
//
/**
a[char][len][mod][i]：四维数组。
第一维：字符类型（0-3，对应 A/T/G/C）。
第二维：len（周期长度，1..10）。
第三维：pos % len（位置对周期取模，0..len-1）。
第四维：BIT 的下标 i。
含义：每种 (字符, 周期长度, 位置模) 各自维护一棵树状数组，统计"哪些位置属于这一类"
add(i, pos, t, f)：在位置 i 处加上 f。
因为是"位置 i 会以所有可能的周期分类"出现，所以对所有 k=1..10 都在对应 a[t][k][pos%k][i] 上加 f。
即：一个点同时属于"周期长度 k = 1..10"的各自分类，都要更新。这就是为什么内层 for k 循环 1..M。
sum(i, pos, t, len)：在给定 (字符、len、pos%len) 对应的那棵 BIT 上做前缀和查询。
query(x, y, pos, t, len)：区间 [x, y] 内、(字符 t、周期 len、位置模 pos%len) 的个数 = 前缀 y − 前缀 x-1
把 4 种碱基字符映射成 0-3 的整数
对字符串每个位置 i（BIT 下标用 i+1），在对应 (字符、各周期取模) 上加 1。
注意这里调用 add(i+1, i, ...)：BIT 下标是 i+1，而 pos 传入 i 用于计算 pos % k
操作 1：点修改
把位置 b（1-based）的字符从 s[b-1] 改成 ch[0]。
先在原字符的所有周期分类上 -1，再在新字符的所有周期分类上 +1。
复杂度单次 O(M · log N)。
操作 2：区间周期模式匹配查询
ch 是长度为 len 的模式串。
目标：统计区间 [b, c] 内，"第 i 个模式字符 ch[i] 应当对应原串的哪个位置"。
对齐方式：模式串在 s 上从位置 b 开始周期重复（pos % len 匹配）：位置 b 对应模式第 0 位，位置 b+1 对应第 1 位……即模式位置 i 对应的原串位置 p 满足 (p - b) % len == i，也就是 p % len == (i + b) % len。
因此对每个 i，查询 [b, c] 内、字符 = h[ch[i]]、周期 len、模 = (i+b-1)%len 的个数，累加即可。
单次查询复杂度 O(len · log N)
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1e5+5, M = 10;

int low_bit(int x) { return x&-x; }

int a[4][M+1][M][N];
void add(int i, int pos, int t, int f) {
    for (; i < N; i += low_bit(i))
        for (int k = 1; k <= M; ++k)
            a[t][k][pos%k][i] += f;
}
int sum(int i, int pos, int t, int len) {
    int s = 0;
    for (; i > 0; s += a[t][len][pos][i], i -= low_bit(i)) {}
    return s;
}
int query(int x, int y, int pos, int t, int len) {
    return sum(y, pos, t, len) - sum(x-1, pos, t, len);
}

int h[100];
char ch[111];
int main() {
    h['A'] = 0, h['T'] = 1, h['G'] = 2, h['C'] = 3;
    string s; cin >> s;
    for (int i = 0; i < s.size(); ++i)
        add(i+1, i, h[s[i]], 1);
    int q, a, b, c; scanf("%d", &q);
    while (q--) {
        scanf("%d", &a);
        if (a == 1) {
            scanf("%d %s", &b, ch);
            add(b, b-1, h[s[b-1]], -1);
            add(b, b-1, h[ch[0]], 1);
            s[b-1] = ch[0];
        } else {
            scanf("%d %d %s", &b, &c, ch);
            int len = strlen(ch), ans = 0;
            for (int i = 0; i < len; ++i)
                ans += query(b, c, (i+b-1)%len, h[ch[i]], len);
            printf("%d\n", ans);
        }
    }
    return 0;
}