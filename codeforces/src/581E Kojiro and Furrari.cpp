//
// Created by Psy.C on 2026/3/16.
//
/**
v[i] 存储第i类事件的位置
f[i][j] 表示从位置v[i][j]到终点的累积费用
时间复杂度：O(n log n + m log n)
空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+5;
vector<int> v[3];//不同类型的
ll f[3][N];//3×N的费用数组
int s;//间隔参数
///第i类中从位置x开始的费用
int get(int i, int x) {
    int j = ranges::lower_bound(v[i], x) - v[i].begin();//x在v[i]中的插入位置
    return f[i][j] + max(v[i][j] - x - s, 0);//累积费用 + 当前段费用
}

int e, n, m;
int main() {
    fast;
    cin >> e >> s >> n >> m;//e:边界值，s:间隔，n:事件数，m:查询数
    for (int i = 1, t, x; i <= n; ++i) {
        cin >> t >> x;//t:类型(0,1,2)，x:位置
        if (x >= e) continue;//位置超出边界
        for (int j = 0; j < t; ++j) v[j].push_back(x);//x添加到对应类型的向量中
    }
    for (int i = 0; i < 3; ++i) {
        v[i].push_back(e);//每个向量末尾添加边界值
        ranges::sort(v[i]);
        int sz = v[i].size() - 1;//有效元素个数 减去边界值e，得到原始元素个数
        for (int j = sz - 1; j >= 0; --j)//sz-1 是原始元素的最大索引
            f[i][j] = f[i][j+1] + max(v[i][j+1] - v[i][j] - s, 0);
    }
    for (int i = 1, x; i <= m; ++i) {
        cin >> x;//查询位置
        if (get(0, x)) cout << "-1 -1\n";//第0类有问题
        else cout << get(1, x) << ' ' << get(2, x) - get(1, x) << '\n';//费用差值
    }
    return 0;
}