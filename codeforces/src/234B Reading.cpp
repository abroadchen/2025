//
// Created by Psy.C on 2025/12/12.
//

#include <iostream>
#include <algorithm>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int,int>
using namespace std;


int main() {
    freopen("input.txt", "r", stdin);//从文件读取输入
    freopen("output.txt", "w", stdout);//向文件写入输出
    fast;
    int n, k; cin>>n>>k;
    vector<ii> v;
    for (int i = 1, j; i <= n; ++i) {
        cin >> j;
        v.emplace_back(j, i);
    }
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());
    cout << v[k-1].first << '\n';//输出第k大的元素的值（即排序后第k个元素的第一个分量）
    for (int i = 0; i < k; ++i)
        cout << v[i].second << ' ';//输出前k个元素的原始位置（即每个pair的第二个分量）
    cout << '\n';
    return 0;
}