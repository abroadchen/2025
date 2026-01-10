//
// Created by Psy.C on 2026/1/10.
//
/**
* 定义 node 结构体：
int x{}, y{}：坐标，初始化为0
bitset<N> bs：大小为N的位集
d[N]：创建 node 类型数组，大小为N
*定义 node2 结构体：
len：距离的平方
a, b：两个点的索引
ld[3000*3000+7]：创建 node2 类型数组，大小足够存储所有点对
 *
*计算两点间距离的平方
参数 a, b：点的索引
返回 (x差)² + (y差)²
 *
*两层循环生成所有点对（避免重复）
ld[cnt].len = dist2(i, j)：计算并存储距离平方
ld[cnt].a = i; ld[cnt].b = j：存储点的索引
cnt++：计数器递增
 *
 *按距离平方降序排列（从大到小）
 *rep(i,cnt)：遍历所有按距离排序的点对
*(d[ld[i].a].bs & d[ld[i].b].bs).any()：
&：按位与操作，找出两个位集的交集
.any()：检查是否有任何位为 true
这是在检查点 ld[i].a 和 ld[i].b 是否都与某个共同点相连
 *ans = sqrt(ld[i].len) / 2：计算距离的一半
*d[ld[i].a].bs[ld[i].b] = true：在点a的连接列表中标记点b
d[ld[i].b].bs[ld[i].a] = true：在点b的连接列表中标记点a
 *
 *fixed：设置浮点数输出格式为定点表示
 */
#include <algorithm>
#include <iostream>
#include <bitset>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 3007
#define rep(i,n) for (int i=0; i<(n); ++i)
using namespace std;

struct node {
    int x{}, y{};
    bitset<N> bs;
} d[N];
struct node2 { int len, a, b; } ld[3000*3000+7];

int dist2(const int a, const int b) {
    return (d[a].x - d[b].x) * (d[a].x - d[b].x) +
        (d[a].y - d[b].y) * (d[a].y - d[b].y);
}

int main() {
    fast;
    int n, cnt = 0; cin >> n;
    rep(i,n) cin >> d[i].x >> d[i].y;
    rep(i,n) for (int j = i + 1; j < n; ++j) {
        ld[cnt].len = dist2(i, j);
        ld[cnt].a = i; ld[cnt].b = j;
        cnt++;
    }
    sort(ld, ld + cnt, [](const node2 a, const node2 b) {
        return a.len > b.len;
    });
    double ans = 0;
    rep(i,cnt) {
        if ((d[ld[i].a].bs & d[ld[i].b].bs).any()) {
            ans = sqrt(ld[i].len) / 2;
            break;
        }
        d[ld[i].a].bs[ld[i].b] = true;
        d[ld[i].b].bs[ld[i].a] = true;
    }
    cout << fixed << ans << '\n';
    return 0;
}