//
// Created by Psy.C on 2026/10/20.
//
/**
s：输入字符串。
flg：合法性标志，初始为 1。
a、b、c：分别统计三种字符出现的个数
对 'a'：如果在此之前已经出现过 b 或 c（即 b || c 为真），则标记 flg=0 并 break。→ 所有 a 必须出现在最前面。
对 'b'：如果前面还没有 a（!a），或已经出现过 c（c），则不合法。→ b 必须出现在一些 a 之后、所有 c 之前。
对 'c'：如果前面没有 a 或没有 b，则不合法。→ c 必须出现在 a 和 b 都出现之后。
换句话说，这个检查强制要求字符串必须按全 a 段 → 全 b 段 → 全 c 段的顺序出现，一旦乱序（如 a 后面又出现 a 但中间已有 b/c、b 后面又出现 b 但中间已有 c 等）就判为不合法
if (a == 0 || b == 0) flg = 0;：至少要有 a 和 b（都非 0），否则不合法。
最终判定：只有当 flg 为真、且 c == a || c == b 时输出 YES，否则 NO。
即最终合法条件为：

字符串按 "a...b...c" 顺序分段（无乱序）；
a、b 至少出现一次；
c 的个数等于 a 的个数，或等于 b 的个数（c==a || c==b）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

string s;
int main() {
    fast;
    cin >> s;
    int flg = 1, a = 0, b = 0, c = 0;
    for (char i : s) {
        if (i == 'a') {
            if (b || c) { flg = 0; break; }
            a++;
        }
        if (i == 'b') {
            if (!a || c) { flg = 0; break; }
            b++;
        }
        if (i == 'c') {
            if (!a || !b) { flg = 0; break; }
            c++;
        }
    }
    if (a == 0 || b == 0) flg = 0;
    if ((c == a || c == b) && flg) cout << "YES\n"; else cout << "NO\n";
    return 0;
}