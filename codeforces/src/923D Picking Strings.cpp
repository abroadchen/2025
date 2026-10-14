//
// Created by Psy.C on 2026/10/14.
//
/**
sb[i]：s 前缀里非 'A' 字符的数量（即 B、C 等其它字符总数——处理成"非A"）。
sa[i]：s 前缀里 'A' 的数量。
对 t 同样建立 tb、ta。
这两个前缀数组便于 O(1) 取任意区间 [l, r] 的"A 个数"与"非 A 个数"
s 的 [a,b] 区间 vs t 的 [c,d] 区间
非A字符的个数奇偶性必须一致（对应 db % 2 == 1 判失败——非A个数的奇偶必须匹配）。
S全长满足 的 A 数量条件（Sa≥Ta）与 %3 的模长判断（对应 'A' 个数需要考虑合并成非A字符的损耗 pd 项）。
最后特殊特判："若 s 区间全为 A，而 t 有非A，且两者A相关量相等"时判定失败（防止错误匹配）

条件 1：db < 0
意思是 t 的非A数比 s 的非A数多时为 db>0；若 db<0 说明 t 的非A比 s 少——即 t 比 s 少了若干非A字符。而变换只能减少字符（合并/删除），不能凭空增加非A字符，所以 s→t 若 t 的非A更少，理论上应允许；db<0 反而表示 t 里非A更少，这在"目标是 t"的视角下 s 更多是有可能的——但代码把它判为失败，说明方向是从 s 变到 t，要求操作后非A个数不增，即 db>=0。若 t 非A比 s 还少（db<0，s 需删掉非A，而普通规则非A不能减），故失败
条件 2：Sa < Ta
Sa 是 s 区间末尾可删除的 'A' 的数量（决定了"能从末尾删掉多少个 A"的上限），Ta 是 t 区间需要的 A 相关量。
若 s 能删的 A（Sa）‍少于 t 要求的 A 量（Ta），说明末尾的 A 不够删，无法对齐 → 失败。
即：s 末尾的 A 必须足够多，才能删到和 t 匹配
条件 3：db % 2 == 1（非A个数差为奇数）‍
变换中每次操作（合并两个非A、或把 A 变成...) 非A个数的变化是偶数。所以 s 与 t 的非A个数差（db）必须是偶数才能相互转化。若差是奇数，永远无法消掉 → 失败
条件 4：A 差模 3 的修正 + 非A差要足够抵消

Sa - Ta = s 末尾可删 A 与 t 所需 A 之间的差。若差 >0 且是 3 的倍数，说明这些多余的 A 可以3 个 A 合并成一个非A（操作规则中 3 个 A 可变出一个非A字符），从而把多余 A 转成非A补账。
pd 标记"Sa − Ta 是不是 3 的倍数"（%3>0 则 pd=1，表示 差不是 3 的倍数，此时需要额外消耗非A）。
db - pd*2：当差不是 3 的倍数时，需要从非A数里额外地扣除 2 个来"补"这个余数。若扣除后 db 变负，说明非A数不够补 → 失败。
即：s 里多余 A 若不能刚好评成 3 的倍数去补差，就得用额外非A去凑，凑不动就失败
条件 5：全A特判
s 区间全为 A（非A数为 0）+ db != 0（t 有非A）+ Sa == Ta（两者 A 相关量相等）。

s 全是 A、不含非A，但 t 里有非A字符（db≠0）。此时 s 无法凭空产生 t 里的非A字符（只有 A，没有非A可操作）。即使 Sa==Ta 看着对齐，也无法生成非A → 特殊判失败。
这是对"无中生有非A"的兜底特判
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e5+5;
inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

char s[N], t[N];
int n, sa[N], sb[N], m, ta[N], tb[N], q;
int main() {
    scanf("%s", s+1); n = strlen(s+1);
    for (int i = 1; i <= n; ++i) {
        sb[i] = sb[i-1] + (s[i] != 'A');
        if (s[i] == 'A') sa[i] = sa[i-1] + 1;
    }
    scanf("%s", t+1); m = strlen(t+1);
    for (int i = 1; i <= m; ++i) {
        tb[i] = tb[i-1] + (t[i] != 'A');
        if (t[i] == 'A') ta[i] = ta[i-1] + 1;
    }
    q = rd();
    while (q--) {
        int a = rd(), b = rd(), c = rd(), d = rd(), f = 1;
        int db = tb[d] - tb[c-1] - (sb[b] - sb[a-1]);//两区间"非A"个数之差
        int Sa = min(b-a+1, sa[b]), Ta = min(d-c+1, ta[d]);
        if (db < 0 || Sa < Ta || db % 2 == 1) f = 0;
        bool pd = (Sa - Ta)%3 > 0;
        if (db - pd*2 < 0) f = 0;
        if (sb[b] - sb[a-1] == 0 && db && Sa == Ta) f = 0;
        printf("%d", f);
    }
    return 0;
}