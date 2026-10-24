//
// Created by Psy.C on 2026/10/24.
//

/**
真正学会的起点..
M=26 个字母。
ha[i][j]：字符串 s[1..i] 中，字母 j 出现位置的哈希（第 j 维独立做前缀哈希）。
f[i]：base 的 i 次幂（用于前缀哈希差分）。
nxt[i][j]：从位置 i 往后，字母 j 下一次出现的位置（预处理后缀）
对每个字母 j，独立维护"该字母出现情况"的前缀哈希 ha[i][j]：若 s[i] 就是字母 j，则在哈希值里贡献 1，否则贡献 0。这样 ha 相当于 26 个独立的 01 串哈希
把 pos[j]（字母 j 的位置标记）初始化为 n+1，是一个"哨兵值 / 无穷大位置"：
n+1 比字符串任何合法位置（1..n）都大，表示"该字母目前没有出现过 / 位置视为不存在"
pos[j] 记录从当前 i 往右看，字母 j 最近出现的位置。
从右往左扫描，nxt[i][j] 存"位置 i 及之后，字母 j 下一次出现的位置"
计算子串 [l, r] 中字母 al 的哈希值（对 ha 在第 al 维做区间差分）
p = nxt[x][al]：在子串 x 的范围内，字母 al 第一次出现的位置。
if (p > x+len-1) return true;：若字母 al 在 x 子串中根本没出现（第一次出现位置超出范围），那么两边都应为 0 次，直接返回 true（相等）。
若 al 在 x 子串中出现，则 p += y-x 对应到 y 子串的同一相对位置。
关键优化：比较的是两段子串中字母 al 的哈希。x 子串直接用其字母 al 哈希 get(x, x+len-1, al)；而 y 子串的"字母 al 哈希"用 get(y, y+len-1, s[p]-'a')。
这里的技巧：由于两子串要"能重新排列成相同"，等价于每个字母出现次数相同。考虑哈希，比较"x 段中字母 al 的出现哈希"与"y 段中字母 ？"——这里借用了字母的"相对位置哈希" 来快速比较两个区间的同一字符集分布
ok 对 26 个字母逐个调用 solve，只要有一个字母分布不等就返回 false。
全部相等 → 两段子串字符多重集相同 → 可重新排列成相同 → YES
读入长度 n、询问数 m、字符串 s（前加空格使下标从 1 开始），预处理。
每次询问两个子串起点 x、y（下标从1起），长度 len，调用 ok 判断，输出 YES/NO
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ull unsigned long long
using namespace std;

constexpr int N = 2e5+1e2, mod = 1e9-2, base = 2333333, M = 26;
ull f[N], ha[N][M];
int n, pos[M], nxt[N][M];
string s;
void init() {
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        f[i] = f[i-1]*base%mod;
        for (int j = 0; j < M; j++)
            ha[i][j] = (ha[i-1][j]*base+(s[i]==char(j+'a')))%mod;
    }
    for (int &p : pos) p = n+1;
    for (int i = n; i >= 1; i--) {
        pos[s[i]-'a'] = i;
        for (int j = 0; j < M; j++) nxt[i][j] = pos[j];
    }
}
ull get(int l, int r, int al) { return (ha[r][al] - ha[l-1][al]*f[r-l+1]%mod+mod)%mod; }

bool solve(int x, int y, int len, int al) {
    int p = nxt[x][al];
    if (p > x+len-1) return true;
    p += y-x;
    return get(x, x+len-1, al) == get(y, y+len-1, s[p]-'a');
}
bool ok(int x, int y, int len) {
    for (int j = 0; j < M; j++)
        if (!solve(x, y, len, j)) return false;
    return true;
}

int m;
int main() {
    fast;
    cin >> n >> m >> s; s = " " + s; init();
    while (m--) {
        int x, y, len; cin >> x >> y >> len;
        if (ok(x, y, len)) cout << "YES\n"; else cout << "NO\n";
    }
    return 0;
}