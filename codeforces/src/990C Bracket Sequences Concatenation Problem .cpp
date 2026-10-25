//
// Created by Psy.C on 2026/10/25.
//

/**
真正学会的起点..
N：数组上限（串长上限量级）。
ans：最终配对答案。
L[i]：记录左半可用串的数量，L[l] 表示"剩余 l 个未匹配左括号的、可作为左半的有效串"个数。
R[i]：记录右半可用串的数量，R[r] 表示"剩余 r 个未匹配右括号的、可作为右半的有效串"个数
len = 串长度；l = 未匹配左括号数（初始0）；r = 未匹配右括号数（初始0）
遇到 (：l++（多一个未匹配左括号）。
遇到 )：
若有未匹配左括号 (l>0)：配对，l--。
否则（没有可配对的左括号）：这个右括号"沦落"为无法匹配的，r++。
最终：l = 剩余未匹配的左括号数，r = 剩下的无法匹配的右括号数
若一个串同时有剩余未匹配左括号和剩余无法匹配右括号（如 )(），这种串无论放在哪边都无法参与合法拼接，直接丢弃，不计数
若 l==0 && r==0：这个串本身就是合法括号序列
关键：把当前串同时记入 L[l] 和 R[r]。
记入 L[l]：作为"左半"候选，它剩余 l 个 (。
记入 R[r]：作为"右半"候选，它剩余 r 个 )。
注意：每个串同时进入两个数组（当 l 或 r 为 0 也能进入，因为可作为对应半边）。
这样做的巧妙处：一个完全匹配的串（l=0,r=0）会同时进入 L[0] 和 R[0]，所以 (i,i) 自拼接也会被计入（因为 R[0] 里有它，L[0] 里有它）
第一步 ans *= ans：此处 ans 当前值是"完全匹配的串的个数 c"。c*c 是这些串两两配对：因为完全匹配串可以当左半也可以当右半，任意两个（含自身）拼接都合法，所以这部分贡献 c * c（有序对计数，含 (i,i)）。
第二步：
遍历 i 从 1 到 N-10：
ans += L[i]*R[i]：左半剩余 i 个 ( 的串有 L[i] 个，右半剩余 i 个 ) 的串有 R[i] 个。因为左串的 i 个 ( 会被右串的 i 个 ) 抵消 → 拼接合法。有序配对数是 L[i]*R[i]。
累加所有 i 的贡献。
输出 ans
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 3e5+10;

ll ans, L[N], R[N];
void check(char s[]) {
    ll len = strlen(s), l = 0, r = 0;
    for (ll i = 0; i < len; i++) {
        if (s[i] == '(') l++;
        else if (l) l--;
        else r++;
    }
    if (l&&r) return;
    if (!l&&!r) ans++;
    L[l]++, R[r]++;
}

ll n;
char s[N];
int main() {
    fast;
    cin >> n;
    for (ll i = 0; i < n; i++) { cin >> s; check(s); }
    ans *= ans;
    for (ll i = 1; i <= N-10; i++) ans += L[i]*R[i];
    cout << ans << '\n';
    return 0;
}