//
// Created by Psy.C on 2026/10/14.
//
/**
n：本组输入的字符串个数；m：每个字符串的长度。
s[N]：原样读入的 n 个字符串。
st（set<string>）：自动去重并按字典序排序。
cnt[i]：记录"第 i 个位置出现 # 的次数"
每轮先清空 st 与 cnt（多组测试，互不影响）。
读入 n 个串到 s[]，同时全部插入 st 去重。
memset(cnt,0,...) 已清零，但注意 cnt 只用前 m 个位置
遍历去重后的每个字符串（st 中的每个元素）。
对每个位置 i，若该字符是 #，则 cnt[i]++。
结果：cnt[i] = 在去重后的字符串集合里，第 i 位是 # 的字符串个数
遍历 0..m-1 每个位置：只要任意位置上 cnt[i] > 1（即有两个及以上"去重后"的字符串在该位都以 # 开头/占位），就判 flg = false，提前退出。
全部位置 cnt[i] ≤ 1 才输出 "Yes"，否则 "No"
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e2;

int n, m, cnt[N];
set<string> st;
string s[N], t;
int main() {
    fast;
    while (cin >> n >> m) {
        st.clear(); memset(cnt, 0, sizeof cnt);
        for (int i = 0; i < n; ++i) { cin >> s[i]; st.insert(s[i]); }
        for (const auto& it : st) {
            t = it;
            int len = t.length();
            for (int i = 0; i < len; ++i)
                if (t[i] == '#') ++cnt[i];
        }
        bool flg = true;
        for (int i = 0; i < m; ++i)
            if (cnt[i] > 1) {
                flg = false; break;
            }
        if (flg) cout << "Yes\n"; else cout << "No\n";
    }
    return 0;
}