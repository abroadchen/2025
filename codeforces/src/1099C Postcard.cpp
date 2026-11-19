//
// Created by Psy.C on 2026/11/19.
//

/**
真正学会的起点..
a*：可让字母 a 出现 0 次或任意多次（* 前字母可留可删可重复）。
a?：可让字母 a 出现 0 次或 1 次（? 前字母可留可删）
每读到字母 c，看它后面跟的是 *、? 还是直接是下个字母/结尾：
跟 * → st[i]=true（可重复/可删），并标记 f=1（表示出现过 *），i 跳过 2 位。
跟 ? → y[i]=true（可删） ，i 跳过 2 位。
否则 → 该字母固定保留，i 前进 1 位。
结果：
b：所有字母本体。
st：对应字母是否带 *。
y：对应字母是否带 ?。
f：全局是否出现过 *。
所以 n = b.size() 是保留所有字母（每个 *\/? 后缀只算一个字母、默认它自身先保留 1 份）时的总长度。
情况 A：n < k（现有字母不够，需要加长）

要变长，只有 * 能让字母多重复。逻辑：
若没有 * → 无法增加字符，直接 Impossible。
否则找到第一个 * 字母 b[sp]，用它多补 k-n+1 个（原来算 1 个，现在共 k-n+1 份，使总数从 n 到 k）。
情况 B：n == k（刚好够）
每个字母正好各保留 1 份，直接输出全部。
情况 C：n > k（太多，需要删减）
从 0 到 n 扫描，只有带 * 或带 ? 的字母可以被删（普通固定字母不能删）。
每删一个 m--，直到删够 m 个；其余固定保留。
若扫完还 m>0（即可选删的字母不够），说明删不满 k 个 → Impossible。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 0; i < n; i++)
using namespace std;

string s, ans;
int k, len, n;
bool f;
vector<char> b;
vector<bool> st, y;
int main() {
    fast;
    cin >> s >> k; len = s.size();
    int i = 0;
    while (i < len) {
        if (isalpha(s[i])) {
            char c = s[i];
            bool ss = 0, q = 0;
            if (i+1 < len) {
                if (s[i+1] == '*') { ss = 1; f = 1; i += 2; }
                else if (s[i+1] == '?') { q = 1; i += 2; }
                else i += 1;
            } else i += 1;
            b.push_back(c); st.push_back(ss); y.push_back(q);
        } else i += 1;
    }
    n = b.size();
    if (n < k) {
        if (!f) { cout << "Impossible\n"; return 0; }
        int sp = -1;
        rep(j,n) if (st[j]) { sp = j; break; }
        rep(j,sp) ans += b[j];
        ans.append(k-n+1,b[sp]);
        for (int j = sp+1; j < n; j++) ans += b[j];
    } else if (n == k) {
        for (char c : b) ans += c;
    } else {
        int m = n - k;
        rep(j,n) {
            if (m > 0 && (st[j]||y[j])) m--;
            else ans += b[j];
        }
        if (m > 0) { cout << "Impossible\n"; return 0; }
    }
    cout << ans << '\n';
    return 0;
}