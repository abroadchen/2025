//
// Created by Psy.C on 2026/2/4.
//
/**
* n：顶点数，p：阈值
a：度数数组，a[i]表示顶点i的度数
mp：记录边的出现次数（处理重边）
 *
*对每个顶点i，使用二分查找找到最小的j，使得a[i] + a[j] ≥ p
n - j + 1是与顶点i配对满足条件的顶点数
 *
*时间复杂度：O(n log n)，主要是排序和二分查找的时间
空间复杂度：O(n)，用于存储度数数组和边的映射
 */
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    int n, p; cin >> n >> p;
    vector<int> a(n + 1); a.reserve(0);
    map<pair<int, int>, int> mp; mp.clear();
    for (int i = 1, x, y; i <= n; ++i) {
        cin >> x >> y;
        if (x > y) swap(x, y);//标准化边的方向（小编号→大编号）
        a[x]++; a[y]++; //更新两端顶点的度数
        mp[{x,y}]++;//记录每条边的出现次数
    }
    ll ans = 0;
    for (auto &[fst, snd] : mp) {//存在重边需要修正计数
        //两个顶点度数和≥p，但去掉这条边后度数和<p时，说明多算了1次
        if (a[fst.first] + a[fst.second] >= p &&
            a[fst.first] + a[fst.second] - snd < p) ans--;
    }
    sort(a.begin()+1, a.begin()+n+1);
    for (int i = 1; i <= n; ++i) {
        const int j = static_cast<int>(lower_bound(a.begin() + 1 + i, a.begin() + 1 + n,
            p - a[i]) - a.begin());
        ans += n - j + 1;
    }
    cout << ans << '\n';
    return 0;
}