//
// Created by Psy.C on 2025/12/1.
//
/*
*n：数组长度
m：元素值的范围（1到m）
k：最多可以删除的元素数量
*对于每个元素a，将其在原数组中的位置i添加到v[a]中
这样v[i]就存储了所有值为i的元素的位置
 *
*res：结果，最长连续子序列长度
x：值为i的元素个数
t：当前窗口中包含的元素个数
c：当前窗口中需要删除的元素个数
y：窗口左边界指针
 *
*时间复杂度：O(n)
空间复杂度：O(n)
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 111111
using namespace std;

vector<int> v[N];//存储所有值为i的元素在原数组中的位置（索引）

int main() {
    fast;
    int n, m, k; cin >> n >> m >> k;
    for (int i = 1, a; i <= n; ++i) {
        cin >> a;
        v[a].push_back(i);
    }
    int res = 1;
    for (int i = 1; i <= m; ++i) {//历所有可能的元素值（1到m）
        const int x = static_cast<int>(v[i].size());
        int t = 1, c = 0, y = 0;
        for (int j = 1; j < x; ++j) {//对值为i的元素位置序列应用滑动窗口
            t++;
            c += v[i][j] - v[i][j-1] - 1;//计算相邻两个相同值元素之间需要删除的元素个数
            while (c > k) {//如果删除的元素超过k个，就移动左边界缩小窗口
                t--;
                c -= v[i][y+1] - v[i][y] - 1;
                y++;
            }
            if (res < t) res = t;
        }
    }
    cout << res << '\n';
    return 0;
}