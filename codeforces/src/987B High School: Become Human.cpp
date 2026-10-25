//
// Created by Psy.C on 2026/10/25.
//

/**
真正学会的起点..
x, y：两个输入数值。
ans：最终差值（带符号的含义在逻辑里体现）。
flg(1)：符号标志，初始为 +1，用于记录是否交换过 x,y
情况 A：x == y

ans = 0，输出 =（相等）。
情况 B：x >= 3 && y >= 3（两者都 ≥3）‍

ans = y - x。
此时若 y > x 则 ans > 0 输出 >；若 y < x 则 ans < 0 输出 <。
也就是说：当两者都 ≥3 时，比较规则就是普通数值比较（谁大谁赢）。
情况 C：x <= 2 && y <= 2（两者都 ≤2）‍

ans = x - y。
这里恰好反过来了：数值小（x 更小）反而 ans>0 输出 >。
即在 1-2 这一档里，较小的数赢。
比如 x=1,y=2 → ans=1-2=-1 → 输出 <……等下，ans=-1<0 输出 <，意味着 x<y? 让我核对——等一下，ans = x-y，若 x=1,y=2, ans=-1, 输出 <，意思是 x 声称比 y 小 → 赢。这里输出的 < 是指"玩家应用的比较基准"。所以 1 和 2 比较时数值小的一方 win。
情况 D：一边 ≤2、一边 ≥3（跨界）
进入这个分支说明 (x≤2, y≥3) 或 (x≥3, y≤2)，即两边跨越了 2 和 3 的分界。
先保证有序 x ≤ y（若 x>y 则交换并记录 flg=-1）。
若小的一方 x == 2：ans = y - 4。
此时判据：若 y > 4 则 ans>0 输出 >（对应原始的比较基准）；若 y < 4 则 <；若 y==4 则 ans=0 输出 =。
否则（即 x == 1）‍：ans = -1，恒输出 <（无论 y 多大，1 输）
若 ans != 0：看 ans * flg 的符号。flg 记录是否交换过。
flg=+1（没交换）：ans>0 → '>'，ans<0 → '<'。
flg=-1（交换过，即原始输入是 x>y，我们交换成 x≤y）：符号取反，ans*flg>0 → '>'。
若 ans == 0：输出 =。
注意：这里的 >/< 不是对 x 与 y 的数值直接比较，而是这套特殊规则下的"判定结果"（谁强谁弱）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int x, y, ans, flg(1);
int main() {
    fast;
    cin >> x >> y;
    if (x == y) ans = 0;
    else if (x >= 3 && y >= 3) ans = y - x;
    else if (x <= 2 && y <= 2) ans = x - y;
    else {
        if (x > y) swap(x, y), flg = -1;
        if (x == 2) ans = y - 4; else ans = -1;
    }
    if (ans) cout << (ans*flg>0 ? '>' : '<') << '\n'; else cout << "=\n";
    return 0;
}