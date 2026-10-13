//
// Created by Psy.C on 2026/10/13.
//
/**
bs[ch] 中第 i 位为 1 ⟺ s[i] == ch。
注意是 1-based：位置 1..len
设模式串 y[1..m]（m = strlen(y+1)）。

匹配位置 p 要求：对每个偏移 i-1（i=1..m），都有 s[p + (i-1)] == y[i]。
也就是：bs[y[i]] 在位置 p+i-1 上是 1。
等价于把 bs[y[i]] 右移 i-1 位后（即 bs[y[i]] >> (i-1)），其第 p 位应为 1。
对所有 i 做按位与，得到的 t[p] == 1 ⟺ y 从位置 p 开始完全匹配
循环结束后，t 中为 1 的第 p 位表示：s[p..p+m-1] == y，即匹配起始位置 p。

区间统计与去重

要统计匹配在 [l, r] 内的次数，且匹配必须完全落在 [l,r] 内：

首先 t >> l：把 [l, ...] 之前的都移掉；
其次要和 t >> (r - m + 2) 相减。
解释：一段匹配从 p 开始，长度 m，需 p ≥ l 且 p + m - 1 ≤ r，即 p ∈ [l, r-m+1]。

(t >> l).count() = 匹配位置 ≥ l 的个数（起始位置 ≥ l）。
(t >> (r-m+2)).count() = 匹配位置 ≥ r-m+2 的个数，即起始位置 > r-m+1 的个数。
两者相减 = 起始位置在 [l, r-m+1] 内的匹配数 = 落在区间内的匹配次数

每个字符一个 bitset，位运算都是整块 N/64 字长。
查询：O(m · N/64)（对模式串每个字符做一次按位与）。
修改：O(1)
 */
#include <bits/stdc++.h>
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
using namespace std;

constexpr int N = 1e5+5, M = 30;

char s[N], c[1], y[N];
bitset<N> bs[M], t;
int main() {
    scanf("%s", s + 1);
    rep(i,1,strlen(s+1)) bs[s[i]-'a'].set(i, 1);
    int q; scanf("%d", &q);
    while (q--) {
        int op, l, r; scanf("%d", &op);
        if (op == 1) {
            scanf("%d%s", &l, c);
            bs[s[l]-'a'].set(l, 0);//旧字符位置 l 清零
            bs[c[0]-'a'].set(l, 1);//新字符位置 l 置 1
            s[l] = c[0];//同步更新字符数组
        } else {
            scanf("%d%d%s", &l, &r, y+1); t.set();//初始全 1
            rep(i,1,strlen(y+1))
                t &= bs[y[i]-'a']>>(i-1);
            cout << max(0, (int)(t>>l).count() -
                (int)(t>>(r-strlen(y+1)+2)).count()) << '\n';
        }
    }
    return 0;
}