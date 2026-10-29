//
// Created by Psy.C on 2026/10/29.
//

/**
真正学会的起点..
N=1e5+5：字符串长度上界。
M = (1<<6)-1 = 63：表示 6 种字母（a-f）全选的掩码（111111）。用 6-bit 位掩码表示字符集合
s[]：读入的原串。
n：串长（即 len）。
num[6]：原串中每种字母的出现次数：num[0]=a 的次数 … num[5]=f 的次数。
m：约束条数。
id：约束指定的位置（1 起始，代码里减 1 转 0 起始）。
t[i]：位置 i 允许的字符集掩码（6-bit）。未受约束时为全选 M。
z[M+10]：后缀统计辅助数组（临时）。
sum[N][M+10]：后缀子集计数表，sum[i][mask] = 从位置 i 到串尾，允许集是"mask 子集"的位置个数。
ss：临时求和变量。
v：输出的构造结果（按位置存放字符）
读入串 s，n=i=len=strlen(s)。
rep(i,len) 遍历原串，num[s[i]-'a']++ 统计 a-f 各自次数。这就是可以支配的字符库存
每组约束：给出位置 id 和允许的字符串 s。
t[id-1] |= 1<<(s[j]-'a')：把该位置允许集的对应 bit 置 1。因为可能多条约束针对同一位置，用按位或累计。
注意：t[] 初始为 0（全局），因此只有被约束的位置才非 0
任何 没有被 m 条约束覆盖 的位置，它的允许集默认是全选 M=63（所有 6 字符都允许）
per(i,n-1)：i 从 n-1 倒序到 0，维护后缀。
内层 j 从 1 到 M=63，遍历所有可能的 6-bit 掩码。
条件 (t[i]&j) == t[i]：表示位置 i 的允许集 t[i] 是 j 的子集（j 覆盖了 t[i] 的全部要求）。
若成立，则 z[j]++——因为位置 i 恰好"需要/允许"这些 j 所代表的字符（若 j 被选用，位置 i 可以满足）。
若 (t[i]&j) != t[i]，说明位置 i 要求了 j 未包含的字符，此位置不满足 j。
sum[i][j] = z[j]：把当前累计值存入 sum[i][j]。
含义：sum[i][mask] = 位置 i 到末尾、且其允许集是该 mask 子集的位置总数。它是判断"剩余字符够不够填充这些受限位置"的依据
flg=0：标记本轮是否成功放下一个字符。
rep(j,6)：遍历 6 种字符尝试放在位置 i。
tag=1：假设字符 j 可行。
if (!num[j] || (t[i]&(1<<j)) == 0) continue;：若字符 j 库存已空，或 不在位置 i 的允许集 t[i] 里，直接跳过。
num[j]--：临时扣掉一个 j，模拟在位置 i 放 j。
for k=1..M：检查所有掩码 k 是否还能被满足：
ss=0; rep(r,6) if (k&(1<<r)) ss += num[r];：ss = 当前所有"属于 k 的字符"的总剩余库存。
if (ss < sum[i+1][k]) { tag=0; break; }：如果位置 i+1 到末尾需要"允许集⊆k"的位置数 sum[i+1][k] 超过了全局属 k 的字符库存 ss，说明放 j 到位置 i 会导致后面填不满 → j 不可行，tag=0。
if (tag)：若所有 k 检查通过（放 j 后剩余全局都满足），则：
flg=1，v.push_back('a'+j) 记录该位置字符，并 break 结束本位置。
num[j]++：若 j 失败，恢复库存，试下一字符。
若整个 j 循环都没有放成功（!flg）→ 无法构造 → 输出 Impossible 并返回
把构造出的 v 逐字符输出，换行
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<n; i++)
#define per(i,n) for (int i=n; i>=0; i--)
using namespace std;

constexpr int N = 1e5+5, M = (1<<6)-1;

char s[N];
int n, len, num[6], m, id, t[N*10], z[M+10], sum[N][M+10], ss;
vector<char> v;
int main() {
    fast;
    cin >> s; n = len = strlen(s);
    rep(i,len) num[s[i]-'a']++;
    cin >> m;
    rep(i,m) {
        cin >> id >> s; len = strlen(s);
        rep(j,len) t[id-1] |= 1<<(s[j]-'a');
    }
    rep(i,n) if (!t[i]) t[i] = M;
    per(i,n-1) for (int j = 1; j <= M; j++) {
        if ((t[i]&j) == t[i]) z[j]++;
        sum[i][j] = z[j];
    }
    rep(i,n) {
        int flg = 0;
        rep(j,6) {
            int tag = 1;
            if (!num[j] || (t[i]&(1<<j)) == 0) continue;
            num[j]--;
            for (int k = 1; k <= M; k++) {
                ss = 0;
                rep(r,6) if (k&(1<<r)) ss += num[r];
                if (ss < sum[i+1][k]) { tag = 0; break; }
            }
            if (tag) { flg = 1; v.push_back('a'+j); break; }
            num[j]++;
        }
        if (!flg) return cout << "Impossible\n", 0;
    }
    for (char i : v) cout << i;
    cout << '\n';
    return 0;
}