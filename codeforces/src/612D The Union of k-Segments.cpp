//
// Created by Psy.C on 2026/3/24.
//
/**
n: 区间数量
k: 需要覆盖的区间数
v: 事件数组，存储区间的开始和结束点
ans: 结果数组，存储k-覆盖区间的左右端点
将每个区间转换为两个事件：
{l, -1}: 在位置l开始的事件，-1表示开始
{r, 1}: 在位置r结束的事件，1表示结束
按照位置排序，如果位置相同，结束事件(1)排在开始事件(-1)前面

cnt: 当前覆盖层数
扫描每个事件点：
如果是开始事件(v[i].second == -1)：
cnt++: 增加覆盖层数
如果刚好达到k层覆盖，记录当前位置（k-覆盖区间开始）
如果是结束事件(v[i].second == 1)：
如果当前正好是k层覆盖，记录当前位置（k-覆盖区间结束）
cnt--: 减少覆盖层数
输出k-覆盖区间的数量（ans中每两个元素构成一个区间）
每两个元素输出一行，表示一个k-覆盖区间
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ii pair<int, int>
using namespace std;

ll n, k;
vector<ii> v;
vector<int> ans;
int main() {
    fast;
    cin >> n >> k;
    for (int i = 1, l, r; i <= n; ++i) {
        cin >> l >> r;
        v.push_back({l, -1});
        v.push_back({r, 1});
    }
    ranges::sort(v);
    for (int i = 0, cnt = 0; i < v.size(); ++i) {
        if (v[i].second == -1) {
            cnt++;
            if (cnt == k) ans.push_back(v[i].first);
        } else {
            if (cnt == k) ans.push_back(v[i].first);
            cnt--;
        }
    }
    cout << ans.size()/2 << '\n';
    for (int i = 0; i < ans.size(); i += 2)
        cout << ans[i] << ' ' << ans[i+1] << '\n';
    return 0;
}