//
// Created by Psy.C on 2026/9/24.
//
/**
读 n，然后两次 gets 读入字符串（第一行可能是空白/空行，用第二次 gets 拿真正的字符串；这种写法较简陋，实际推荐 scanf 读字符串）
对周期 len，把字符串分成若干"位置模 len 相同"的组（i, i+len, i+2len, ...）。
每组内：所有位置上的字符必须能统一成一个值（一致才匹配）。
c 记录该组当前确定的字符。
若 c 和 str[j] 都是非 ? 且不相等 → 返回 false（冲突）。
若 str[j] 非 ? → 用 str[j] 更新 c。
? 不算冲突，可任意匹配。
所有组都通过 → check 为 true（此 len 是合法周期）。
复杂度每 check O(n)，但配合下方因子筛可接受
v[0]、v[1]：记录字符串中是否出现过 V 和 K
情况 1：没有任何 V/K（全是 ?）
若字符串全是 ?，则任意长度 len 都是合法周期 → 输出 1..n 全部。
情况 2：有 V 或 K
a[i]：标记 i 是否已是合法周期（已作为答案）。
枚举每个未被标记的 i：
若 !a[i] 且 check(i) 为 true（i 是合法周期）：
则所有 i 的倍数 j（i, 2i, 3i, ...）也都是合法周期（周期缩短为因子，匹配关系仍成立）→ 把它们全部标记进 a，统计计数。
这一步用倍数枚举把"一旦确认最小合法周期 i，所有倍数直接标记"的优化，避免对每个 len 都调耗时 check。
最后输出 res（合法周期个数）和所有合法周期。
说明：这里的 a[] 数组在每次 solve 后会被清成 false（结尾循环里 a[i] = false），但注意它是全局数组，且未被本轮标记的位置可能残留——不过清理逻辑基本自洽
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 5e5+1;

int n;
char str[N];
inline void init() { scanf("%d", &n); gets(str); gets(str); }

inline bool check(int len) {
    for (int i = 0; i < len; ++i) {
        char c = str[i];
        for (int j = i+len; j < n; j += len) {
            if (c != '?' && str[j] != '?' && c != str[j])
                return false;
            if (str[j] != '?')  c = str[j];
        }
    }
    return true;
}

bool v[3], a[N];
inline void solve() {
    v[0] = v[1] = false;
    for (int i = 0; i < n; ++i) {
        switch (str[i]) {
            case 'V': v[0] = true; break;
            case 'K': v[1] = true; break;
        }
    }
    if (!v[0] && !v[1]) {
        printf("%d\n", n);
        for (int i = 1; i <= n; ++i)
            printf("%d%c", i, i==n ? '\n' : ' ');
        return;
    }
    int res = 0;
    for (int i = 1; i <= n; ++i)
        if (!a[i] && check(i))
            for (int j = i; j <= n; j += i)
                res += !a[j], a[j] = true;
    printf("%d\n", res);
    for (int i = 1; i <= n; ++i)
        if (a[i]) {
            printf("%d ", i);
            a[i] = false;
        }
    putchar('\n');
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        init(); solve();
    }
    return 0;
}