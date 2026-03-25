//
// Created by Psy.C on 2026/3/25.
//
/**
a,b为目标点，c数组存储待处理点
x为临时变量，x1为距离a的距离，x2为其他点到a的距离
遍历所有可能的点（包括虚拟点0）
O(n²)，需要双重循环遍历所有点对

外层循环：枚举可能的选择点 i（0到n）
内层循环：对每个选择点，检查其他点的条件
约束条件：只有当 dis(c[j], a) > dis(c[i], a) 时才考虑点 c[j]
目标函数：最小化 max(dis(c[j], b)) + dis(c[i], a)

x1 = dis(c[i], a)：选择点到a的距离
x = max(dis(c[j], b))：满足条件的点到b的最大距离
总目标：x + x1，即两部分距离的和
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+5;
constexpr ll inf = ~0ull>>1;//最大值的一半

struct node { ll x, y; } a, b, c[N];

ll dis(node u, node v) {
    return (u.x-v.x)*(u.x-v.x)+(u.y-v.y)*(u.y-v.y);
}
int n;
int main() {
    fast;
    cin >> n >> a.x >> a.y >> b.x >> b.y;
    for (int i = 1; i <= n; ++i) cin >> c[i].x >> c[i].y;
    ll x, x1, x2, res = inf;
    for (int i = 0; i <= n; ++i) {//遍历所有可能的点（包括虚拟点0）
        x = 0; x1 = dis(c[i], a);//第i个点到目标点a的距离平方
        if (i == 0) x1 = 0;//i为0（虚拟点），距离设为0
        for (int j = 1; j <= n; ++j) {//遍历所有待处理点
            if (i == j) continue;//跳过自己
            x2 = dis(c[j], a);//第j个点到a的距离平方
            if (x2 <= x1) continue;//第j个点到a的距离小于等于第i个点到a的距离
            x = max(dis(c[j], b), x);//更新x为第j个点到b的距离的最大值
        }
        res = min(res, x + x1);//x+x1的最小值
    }
    cout << res << '\n';
    return 0;
}