//
// Created by Psy.C on 2025/9/27.
//时间复杂度约为O(nlog(m) + mlog(m))，空间复杂度为O(m)。

#include <algorithm>
#include <ios>
#include <iostream>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
using namespace std;

const int N = 1e5+5;
int n, m, pos[N], ans[N];

struct Rect {
    int xl, xr, yl, yr, z, i;//矩形的左边界(xl)、右边界(xr)、下边界(yl)、上边界(yr)、深度(z)和索引(i)
} a[N];//存储所有矩形

struct Point {
    int x, y, i;
} po[N];//存储所有点

struct KDT {//高效处理二维空间查询
    Rect t[N*4];//节点数组
    void Pull(int p) { t[p].z = min(t[p*2].z, t[p*2+1].z); }//向上更新函数，将子节点的信息合并到父节点，这里更新z值为子节点z的最小值
    void Build(int p, int l=1, int r=m, bool axis=0) {//节点索引p、区间左右端点l和r、分割轴向axis(0为x轴，1为y轴)
        if (l == r) {//如果区间只有一个点
            t[p].xl = t[p].xr = po[l].x;//将叶子节点的边界设为该点的x坐标
            t[p].yl = t[p].yr = po[l].y;
            t[p].z = po[l].i;//将叶子节点的z值设为该点的索引
            return;
        }
        int mid = (l + r) / 2;
        nth_element(po+l, po + mid, po + r + 1, [&](Point p1, Point p2) {
            return (axis ? p1.y < p2.y : p1.x < p2.x);
        });//按照当前轴向(axis)对点进行分割，使po[mid]左边的点都小于它，右边的点都大于它
        Build(p*2, l, mid, !axis), Build(p*2+1, mid + 1, r, !axis);//递归构建左右子树，并切换轴向
        t[p].xl = min(t[p*2].xl, t[p*2+1].xl);//更新当前节点的左边界为子节点左边界最小值
        t[p].xr = max(t[p*2].xr, t[p*2+1].xr);
        t[p].yl = min(t[p*2].yl, t[p*2+1].yl);
        t[p].yr = max(t[p*2].yr, t[p*2+1].yr);
        Pull(p);//向上更新当前节点的z值
    }
    void Del(int p, int x, int l=1, int r=m) {//节点索引p、要删除的点在po数组中的位置x
        if (l == r) { t[p].z = m + 1; return; }//如果到达叶子节点，将z值设为m+1表示已被删除，然后返回
        int mid = (l + r) / 2;
        if (x <= mid) Del(p*2, x, l, mid);//如果要删除的点在左半区间，则递归删除左子树
        else Del(p*2+1, x, mid + 1, r);
        Pull(p);
    }
    void Query(int p, const Rect& x, int& res) {//查找被矩形x覆盖的最深深度的点，结果保存在res中
        if (t[p].z >= res || t[p].xl > x.xr || t[p].xr < x.xl ||
            t[p].yl > x.yr || t[p].yr < x.yl) return;//如果当前节点的z值不优于当前最优解，或者当前节点表示的区域与查询矩形不相交，则返回
        if (x.xl <= t[p].xl && t[p].xr <= x.xr &&
            x.yl <= t[p].yl && t[p].yr <= x.yr) {//如果当前节点表示的区域完全包含在查询矩形内
            res = t[p].z;//更新最优解
            return;
        }//优先查询z值较小的子树，然后再查询另一个子树
        if (t[p*2].z <= t[p*2+1].z) Query(p*2, x, res), Query(p*2+1, x, res);
        else Query(p*2+1, x, res), Query(p*2, x, res);
    }
} kdt;

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    rep(i, 1, n) {//循环读入n个矩形的信息
        cin >> a[i].xl >> a[i].xr >> a[i].yl >> a[i].yr >> a[i].z;
        a[i].i = i;
    }
    sort(a + 1, a+n+1, [](Rect a, Rect b) {
        return a.z < b.z;
    });
    cin >> m;
    rep(i, 1, m) cin >> po[i].x >> po[i].y, po[i].i = i;//循环读入m个点的坐标，并设置点的索引
    kdt.Build(1);//构建K-D树，从根节点开始
    rep(i, 1, m) pos[po[i].i] = i;//记录每个点在po数组中的位置，pos[j]表示索引为j的点在po数组中的位置
    rep(i, 1, n) {
        int j = m + 1;//初始化查询结果j为m+1，表示未找到
        kdt.Query(1, a[i], j);//查询被矩形a[i]覆盖的最深深度的点，结果保存在j中
        if (j <= m) {//如果找到了有效的点（索引不超过m）
            ans[j] = a[i].i;//记录这个点被第a[i].i个矩形覆盖
            kdt.Del(1, pos[j]);//从K-D树中删除这个点，防止被后续的矩形再次覆盖
        }
    }
    rep(i, 1, m) cout << ans[i] << '\n';
    return 0;
}