//
// Created by Psy.C on 2026/2/13.
//

#include <algorithm>
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;

int n;//数组长度
vector<ii> v;//{值, 原始位置}
vector<int> ind;//相等元素位置

int main() {
    fast;
    cin >> n;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        v.emplace_back(x, i);
    }
    ranges::sort(v);
    int cnt = 0;
    for (int i = 0; i < n-1; ++i) {
        if (v[i].first == v[i+1].first) {
            ++cnt;//相等元素对的数量
            ind.push_back(i);//存储相等元素的位置索引
            ind.push_back(i+1);
        }
    }
    if (cnt < 2) cout << "NO\n";//少于2对
    else {
        cout << "YES\n";
        for (int i = 0; i < n; ++i) cout << v[i].second << ' ';
        cout << '\n';
        swap(v[ind[0]], v[ind[1]]);//交换相等元素的位置生成不同的排列
        for (int i = 0; i < n; ++i) cout << v[i].second << ' ';
        cout << '\n';
        swap(v[ind[2]], v[ind[3]]);
        for (int i = 0; i < n; ++i) cout << v[i].second << ' ';
        cout << '\n';
    }
    return 0;
}