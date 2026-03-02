//
// Created by Psy.C on 2026/3/2.
//
/**

双层循环：遍历所有可能的倍数i和对应的值v[i][j]
剩余值计算：y = x - v[i][j]
完全匹配：如果y=0，说明找到了一个值正好等于x，答案为i
提前终止：如果y<0，由于数组已排序，后续值更大，可跳出

遍历剩余倍数：k从1到m-i（保证总倍数不超过m）
二分查找：在v[k]中查找值y
lower_bound：返回第一个≥y的元素位置
精确匹配验证：确认找到的值确实等于y
更新答案：如果找到配对，更新ans为i+k（使用的倍数之和）

时间复杂度约为O(q × m × n × log(n))
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int inf = 0x3f3f3f3f;
int n, m;
vector<int> v[21];//各种倍数
int main() {
    fast;
    cin >> n >> m;//n个数字，每个数字可以取1到m倍
    for (int i = 0, x; i < n; ++i) {
        cin >> x;
        for (int j = 1; j <= m; ++j)
            v[j].push_back(x*j);//1到m倍添加到对应的v[j]中
    }
    for (int i = 1; i <= m; ++i) ranges::sort(v[i]);
    int q; cin >> q;
    while (q--) {
        int x; cin >> x;
        int ans = inf;
        if (x == 0) { cout << "0\n"; continue; }
        for (int i = 1; i <= m; ++i)
            for (int j = 0; j < v[i].size(); ++j) {
                int y = x - v[i][j];
                if (y == 0) { ans = min(ans, i); break; }
                if (y < 0) break;
                for (int k = 1; k <= m-i; ++k) {
                    int p = lower_bound(v[k].begin(), v[k].end(), y) - v[k].begin();
                    if (p < v[k].size() && v[k][p] == y)
                        ans = min(ans, i+k);
                }
            }
        cout << (ans == inf ? -1 : ans) << '\n';
    }
    return 0;
}