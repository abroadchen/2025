//
// Created by Psy.C on 2026/9/29.
//
/**
str：给定的 n 个字典单词（count() 统计某个具体串出现的次数）。
st：每次查一个模式时，由 dfs 枚举出的全部无通配符字符串集合（unordered_set 自动去重）。
mp：记忆化，记录某模式串的答案
对当前串 s：找到第一个 ?。
分支1：删除该 ?（等价于替换成"空"）。
分支2：把该 ? 替换成 'a'、'b'、'c'、'd'、'e' 五个字符之一。
每个分支递归继续处理剩余 ?。
当一个串里不再有 ? 时（cnt==0），把它插入 st 集合。
结果：st 中就是该模式所有可能的"具体串"（已去重）。
注意：这里按字符遍历，实际上每轮递归只处理遇到的第一个 ? 并展开——但由于对每一分支都继续递归，最终会穷举所有 ? 的组合（删或替换成某字符）。cnt 只在叶子（无 ?）时累加，实际 cnt 的作用是判断当前串是否已无 ?
对每个查询模式 s：
若缓存中没有（mp[s]==0，而 0 被用作"未计算"标记），则：
清空 st，调用 dfs(s) 生成所有无 ? 具体串。
对每个具体串 it，在字典 str 中用 count(it) 统计出现次数（multiset 支持多个相同词），累加到 ans。
输出 ans；将结果写入缓存：ans==0 存成 -1（因为 0 保留作"未计算"标记），否则存 ans。
若缓存已有，直接按 -1→0 的映射输出

mp 用 -1 表示"答案实际为 0"，用 0 表示"还没算过"、用正数表示真实答案。
这样能避免重复的模式查询重复做 DFS 展开（通配符枚举是指数级的，缓存可大幅加速
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

unordered_set<string> st;
void dfs(const string& s) noexcept {
    string b;
    int i, j, cnt = 0, lens = s.length();
    for (i = 0; i < lens; ++i) {
        if (s[i] == '?') {
            cnt++;
            b = s; b.erase(i, 1);
            dfs(b);
            b = s;
            for (j = 'a'; j <= 'e'; ++j) {
                b[i] = j;
                dfs(b);
            }
        }
    }
    if (!cnt) st.insert(s);
}

string t, s;
multiset<string> str;
int ans;
unordered_map<string, int> mp;
int main() {
    fast;
    int n, m, i; cin >> n >> m;
    for (i = 1; i <= n; ++i) {
        cin >> t;
        str.insert(t);
    }
    for (i = 1; i <= m; ++i) {
        st.clear(); ans = 0; cin >> s;
        if (mp[s] == 0) {
            dfs(s);
            for (const auto& it : st)
                ans += str.count(it);
            cout << ans << '\n';
            mp[s] = ans == 0 ? -1 : ans;
        }
        else cout << (mp[s] == -1 ? 0 : mp[s]) << '\n';
    }
    return 0;
}