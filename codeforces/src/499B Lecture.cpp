//
// Created by Psy.C on 2026/2/23.
//
/**
n：待查询的单词数量
m：映射关系的数量
mp：存储单词到缩写的映射关系
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, m;
map<string, string> mp;
string v, k;
int main() {
    fast;
    cin >> n >> m; mp.clear();
    for (int i = 0; i < m; ++i) {
        cin >> v >> k;
        mp[v] = k;
    }
    for (int i = 0; i < n; ++i) {
        cin >> v;
        const auto it = mp.find(v);//当前单词v是否存在于映射表中
        if (string s1 = mp[v], s2 = it->first; s2.size() <= s1.size())
            cout << s2 << ' ';
        else cout << s1 << ' ';
    }
    cout << '\n';
    return 0;
}