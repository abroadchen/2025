//
// Created by Psy.C on 2026/3/23.
//
/**
i：当前考虑的起始顶点
it：当前扩展的结束顶点，从2开始
这个循环遍历每个可能的起始顶点
寻找从顶点i开始的最大扇形区域，使其面积不超过总面积的一半。
记录从顶点i出发形成的三角形个数
使用叉积计算新三角形的有向面积并累加到s
cross(d[it] - d[i], d[nxt(it)] - d[i])计算三角形(i, it, nxt(it))的面积
如果当前扇形面积恰好等于总面积的一半，计数器cp加1
A存储的是前缀面积和，即所有中间状态面积的累加
v存储当前扇形内所有顶点坐标的累加和
将结束位置向前推进一个顶点

从总答案中减去当前顶点i对应的所有三角形面积的贡献
乘以2是因为叉积计算的是平行四边形面积，实际三角形面积是其一半
从当前扇形面积s中移除三角形(i, i+1, it)
v - d[i]*cnt得到除了顶点i外其他顶点坐标的和
cross2(d[i+1] - d[i], v - d[i]*cnt)计算多个三角形面积和的简化公式
从A中减去相应的面积贡献
减少当前扇形包含的三角形数量
从向量v中移除顶点i+1的坐标

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ull unsigned long long
using namespace std;
constexpr int N = 5e5+5, mod = 1e9+7;

struct node {
    ll x, y;
    node operator+(const node &o) const { return {x + o.x, y + o.y}; }
    node operator-(const node &o) const { return {x - o.x, y - o.y}; }
    node operator*(const int &o) const { return {x * o, y * o}; }
} d[N];///多边形顶点

inline ll cross(const node& a, const node& b) { return a.x * b.y - a.y * b.x; }
inline int cross2(const node& a, const node& b) {
    return (a.x%mod*(b.y%mod) - a.y%mod*(b.x%mod) + 1ll*mod*mod)%mod;
}
int n;///多边形顶点数量
inline int nxt(int x) { return x%n + 1; }///获取下一个顶点索引的函数（循环）

ull S, s;///S:多边形总面积，s:当前三角形面积
int ans;
int main() {
    fast;
    cin >> n;
    for (int i = n; i; --i) cin >> d[i].x >> d[i].y;//逆序读入多边形顶点坐标
    for (int i = 2; i < n; ++i) S += cross(d[i] - d[1], d[i+1] - d[1]);
    ans = S%mod*(n*(n-3ll)/2%mod)%mod; d[n+1] = d[1], d[0] = d[n];//设置边界条件，使数组循环
    node v = d[2];//初始化向量v为第二个点
    int cnt = 1, A = 0, cp = 0;
    for (int i = 1, it = 2; i <= n; ++i) {
        //扩展当前三角形直到面积不超过总面积的一半
        while (s + cross(d[it] - d[i], d[nxt(it)] - d[i]) <= S/2) {
            ++cnt;
            s += cross(d[it] - d[i], d[nxt(it)] - d[i]);
            if (s<<1 == S) ++cp; A = (A + s)%mod;
            v = v + d[nxt(it)]; it = nxt(it);//移动到下一个顶点
        }
        ans = (ans - 1ll*(2*A%mod)+mod)%mod;
        s -= cross(d[i+1] - d[i], d[it] - d[i]);
        A = (A - cross2(d[i+1] - d[i], v - d[i]*cnt)+mod)%mod;
        --cnt;
        v = v - d[i+1];
    }
    ans = (ans + cp*(S/2%mod))%mod;
    cout << ans << '\n';
    return 0;
}