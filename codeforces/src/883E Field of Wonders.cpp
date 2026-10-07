//
// Created by Psy.C on 2026/10/7.
//
/**
len：模式串 a 长度。
a：模板字符串，其中 * 是通配符（可以匹配 任意一个不在模板字母表里的字母），其余位置是固定字母。
m：字符串个数，b[1..m] 是待匹配的字符串。
N=1200, M=200, B=M/2：预留数组大小（这里 B 未真正使用为二分，只是常量；st 大小 B，实际当字母桶用）
bk[u]=1 表示字母 u（1..26）在模板的非通配位置出现过。这个集合限制了"通配符 * 不能匹配这些字母"——因为题面通常规定 * 只能匹配没在模板中出现的字母
对每个串 b[i]，遍历所有通配符位置 j，取该位置的字母 u。
st[u]++：统计"在所有候选串中，某个字母 u 出现在通配位的次数"（后面用于判断通配符能匹配字母的范围）。
若 u 是模板中出现的禁用字母（bk[u]），则 b[i] 非法，标记 bk2[i]=1
对每个串 b[i]，模板固定字母位置必须与 b[i] 对应字符完全一致，否则非法
cnt = 所有合法（固定位置匹配、通配位不用禁用字母）的串个数。
对每个合法串 b[i]，记录它在通配位上出现的字母 u（ss[i][u]++)
ss2[i] = 使用了字母 i 作为通配位字母的合法串个数
对每个字母 i：若它在任何候选串的通配位出现过（st[i]），并且每个合法串都在通配位用过它（ss2[i]==cnt），则这个字母 i 满足"是每个合法解中都必然出现的通配字母"。
统计这样的字母个数输出
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1200, M = 200, B = M/2;
int len, m, bk[M], bk2[M*10], st[B], cnt, ss[M*10][N/10], ss2[B];
string a, b[N];
int main() {
    fast;
    cin >> len >> a >> m;
    for (int i = 1; i <= m; ++i) cin >> b[i];
    for (int i = 0; i < len; ++i) {
        if (a[i] != '*') {
            int u = a[i] - 'a' + 1; bk[u] = 1;
        }
    }
    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j < len; ++j) {
            if (a[j] == '*') {
                int u = b[i][j] - 'a' + 1;
                st[u]++;
                if (bk[u]) { bk2[i] = 1; break; }
            }
        }
    }
    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j < len; ++j) {
            if (a[j] != '*') {
                if (b[i][j] != a[j]) { bk2[i] = 1; break; }
            }
        }
    }
    for (int i = 1; i <= m; ++i)
        if (!bk2[i]) cnt++;
    for (int i = 1; i <= m; ++i) {
        if (!bk2[i]) {
            for (int j = 0; j < len; ++j)
                if (a[j] == '*') {
                    int u = b[i][j] - 'a' + 1;
                    ss[i][u]++;
                }
        }
    }
    for (int i = 1; i <= 26; ++i)
        for (int j = 1; j <= m; ++j)
            if (!bk2[j]) {
                if (ss[j][i] >= 1) ss2[i]++;
            }
    int sum = 0;
    for (int i = 1; i <= 26; ++i)
        if (st[i]) {
            if (ss2[i] == cnt) sum++;
        }
    cout << sum << '\n';
    return 0;
}