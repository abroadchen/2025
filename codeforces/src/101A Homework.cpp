//
// Created by Psy.C on 2025/11/12.
//
/*
*创建无序映射mp，用于统计每个字符的出现频次
遍历字符串s中的每个字符x，将其频次加1
*将映射mp转换为pair向量v
按照字符频次升序排序（使用lambda表达式）
 *
*如果某个字符的频次≤剩余的n：
减少不同字符计数len
从n中减去该字符的频次
在映射中标记该字符为-1（表示要删除）
 *
*输出剩余的不同字符数量
遍历原字符串，只输出未被标记删除的字符

unordered_map不支持排序操作
 */
#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>
#define sz(x) ((int)(x).size())
using namespace std;

int main() {

    cin.tie(nullptr)->sync_with_stdio(false);

    string s; int n;
    cin >> s >> n;
    unordered_map<char, int> mp;
    for (auto& x : s) mp[x]++;
    vector<pair<char, int>> v(mp.begin(), mp.end());
    sort(v.begin(), v.end(), [](auto& a, auto& b) {
        return a.second < b.second;
    });

    int len = sz(mp);
    for (auto x : v) {
        if (x.second <= n) {
            len--;
            n -= x.second;
            mp[x.first] = -1;
        }
    }
    cout << len << '\n';
    for (auto& x : s) if (mp[x] != -1) cout << x;
    cout << '\n';
    return 0;
}