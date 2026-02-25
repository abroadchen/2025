//
// Created by Psy.C on 2026/2/25.
//
/**
检查是否存在以x为值的映射关系
如果找到，则更新该映射关系的值为y
如果没有找到匹配的映射关系，则添加新的映射关系{x, y}
输出最终映射关系的数量
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int q;
string x, y;
vector<pair<string, string>> v;
int main() {
    fast;
    cin >> q;
    int i;
    while (q--) {
        cin >> x >> y;
        for (i = 0; i < v.size(); ++i) {
            if (v[i].second == x) {
                v[i].second = y;
                break;
            }
        }
        if (i == v.size())
            v.push_back({x, y});
    }
    cout << v.size() << '\n';
    for (i = 0; i < v.size(); ++i)
        cout << v[i].first << ' ' << v[i].second << '\n';
    return 0;
}