//
// Created by Psy.C on 2026/2/7.
//
/**
计算两个向量的叉积：(x,y) × (p.x,p.y)
结果为正：第二个向量在第一个向量的逆时针方向
结果为负：第二个向量在第一个向量的顺时针方向
结果为零：两向量共线

len: 当前子多边形的长度
l, r: 子多边形的左右端点
k: 子多边形[l,r]内的分割点
条件: (p[r]-p[l])*(p[k]-p[l]) > 0 确保三角形(l,k,r)是有效的
转移: dp[l][r] += dp[l][k] * dp[k][r]（相乘得到组合数）
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 203
#define mod 1000000007
using namespace std;

struct node {
    int x, y;
    node() = default;
    node(const int x, const int y) : x(x), y(y) {}
    //平行四边形的有符号面积
    ll operator*(const node p) const {
        return 1ll*x*p.y - 1ll*y*p.x;
    }
    node operator-(const node p) const {
        return {x - p.x, y - p.y};
    }
} p[N];

int main() {
    fast;
    int n; cin >> n;
    for (int i = 1, x, y; i <= n; ++i) {
        cin >> x >> y;
        p[i] = {x, y};//读取坐标并存储在数组p中
    }
    ll sum = 0, dp[N][N]{};
    for (int i = 2; i < n; ++i) sum += (p[i]-p[1])*(p[i+1]-p[1]);
    //多边形是逆时针方向 → 反转使其变为顺时针
    if (sum > 0) reverse(p + 1, p + n + 1);
    for (int i = 1; i < n; ++i) dp[i][i+1] = 1;//连接相邻顶点的线段有1种方式
    for (int len = 2; len < n; ++len)
        for (int l = 1, r = len+1; r <= n; ++l, ++r)
            for (int k = l; k <= r; ++k)
                if ((p[r]-p[l])*(p[k]-p[l]) > 0)
                    dp[l][r] = (dp[l][r] + dp[l][k]*dp[k][r]%mod) % mod;
    cout << dp[1][n] << '\n';//完整多边形的三角剖分数目
    return 0;
}