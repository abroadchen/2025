//
// Created by Psy.C on 2026/2/4.
//
/**
* N：坐标范围上限
M：分块阈值，约等于√N ≈ 317
 *
*小块情况
已有点：(x, y1) 和 (x, y2)
寻找：(x+d, y1) 和 (x+d, y2)，其中 d = y2 - y1
大块情况
已有点：(x, yy) 和 (xx, yy)
寻找：(x, yy+d) 和 (xx, yy+d)，其中 d = xx - x
 *
*小块处理
时间复杂度：O(size²) × 每次查找O(log n)
总复杂度：O(∑ size² × log n)，其中∑ size ≤ n
大块处理
大块数量：最多n/M个（因为总点数为n）
每个大块与其他点配对：O((n-size) × size)
总复杂度：O(n²/M)
总体复杂度
通过分块平衡，总体复杂度约为 O(n√n log n)

(x, v[x][j]) ────── (?)
         │              │
         │              │
    (x, v[x][i]) ────── (?)

(?) ────────────────── (?)
    │                      │
    │                      │
(x,yy) ────────────────── (xx,yy)

 */
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100010
#define M static_cast<int>(sqrt(N+.0)+1)
#define rep(i,n) for (int i=0; i<n; ++i)
using namespace std;

vector<int> v[N];//N个vector，v[i]存储x坐标为i的所有点的y坐标
inline bool find(const int x, const int y) {//点(x,y)是否存在
    if (x >= N) return false;
    return ranges::binary_search(v[x], y);
}

int main() {
    fast;
    int n; cin >> n;
    rep(i,n) {
        int x, y; cin >> x >> y;
        v[x].push_back(y);//按x坐标分组 将y坐标添加到x坐标的vector中
    }
    ///遍历v数组中的每个vector
    ///对每个vector进行排序
    for (auto& i : v) ranges::sort(i);//对每个x坐标对应的y坐标排序
    ll ans = 0;//矩形数量
    rep(x,N) {//遍历每个x坐标
        if (v[x].size() < M) {//x坐标对应的点数量是否小于分块阈值M
            //枚举x坐标内的所有点对
            rep(i,v[x].size()) for (int j = i + 1; j < v[x].size(); ++j) {
                if (const int d = v[x][j] - v[x][i];
                    find(x + d, v[x][i]) && find(x + d, v[x][j])) ++ans;
            }
        } else {
            ///遍历更大的x坐标 遍历xx坐标的所有点
            for (int xx = x + 1; xx < N; ++xx) rep(i,v[xx].size()) {
                ///yy是当前y坐标，d是x距离
                if (int yy = v[xx][i], d = xx - x;
                    find(x, yy) && find(x, yy + d) && find(xx, yy + d)) ++ans;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}