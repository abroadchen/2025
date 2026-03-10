//
// Created by Psy.C on 2026/3/9.
//
/**
a, b, c：输入的三个字符串
fa[N], fb[N], fc[N]：统计每个字符串中各字母的频次

cb, cc：当前最优解中b和c字符串的使用次数
枚举使用b字符串的次数i：
检查是否可以使用i次b字符串（不超出a中的字符限制）
计算最多可以使用多少次c字符串（在剩余字符中）
更新最优解
tb：使用b的次数
tc：使用c的次数
flag：检查是否可以使用i次b字符串
如果fa[j] < fb[j]*i，说明字符j不够用，不能使用i次b

计算剩余字符数量：从a中减去已使用的字符
按字典序输出剩余的所有字符
时间复杂度：O(M×N)，其中M是最大枚举次数，N是字母表大小
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 26, M = 1e5+1, inf = 1e9;;
string a, b, c;
int fa[N], fb[N], fc[N];
int main() {
    fast;
    cin >> a >> b >> c;
    for (int i = 0; i < a.size(); ++i) ++fa[a[i] - 'a'];//转换为0-25的索引
    for (int i = 0; i < b.size(); ++i) ++fb[b[i] - 'a'];
    for (int i = 0; i < c.size(); ++i) ++fc[c[i] - 'a'];
    int cb = 0, cc = 0;
    for (int i = 0; i < M; ++i) {
        int tb = inf, tc = inf;
        bool flag = true;
        for (int j = 0; j < N; ++j)
            if (fb[j] != 0 && fa[j] < 1ll*fb[j]*i) {
                flag = false;
                break;
            }
        if (!flag) tb = 0; else tb = i;
        for (int j = 0; j < N; ++j)
            if (fc[j] != 0)
                tc = min(1ll*tc, max(0ll, (fa[j]-(1ll*fb[j]*tb))/fc[j]));
        if (tb + tc > cb + cc)
            cb = tb, cc = tc;
    }
    for (int i = 0; i < cb; ++i) cout << b;
    for (int i = 0; i < cc; ++i) cout << c;
    for (int i = 0; i < N; ++i) {
        fa[i] -= fb[i]*cb + fc[i]*cc;
        for (int j = 0; j < fa[i]; ++j)
            cout << char(i + 'a');
    }
    cout << '\n';
    return 0;
}