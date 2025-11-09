//
// Created by Psy.C on 2025/11/8.
//
/*
 *point: 使用复数表示二维点，实部为x坐标，虚部为y坐标
 *
*重排函数，将点集按极角顺序排列：
找到y坐标最小的点（如果y相同则选x坐标最小的点）
将该点旋转到向量开头
这确保了点集以最下-left点开始，为闵可夫斯基和做准备
 *
*计算两个向量的叉积：
使用复数运算：conj(a) * b的虚部就是向量a和b的叉积
叉积可用于判断向量的相对方向
 *
*重载+运算符，计算两个凸包的闵可夫斯基和：
对两个点集重新排序
在每个点集末尾添加前两个点（便于处理边界情况）
 *
*闵可夫斯基和的核心算法：
使用双指针技术遍历两个凸包
将当前点的和加入结果
计算两条边的叉积决定前进方向：
如果叉积≥0，推进p的指针
如果叉积≤0，推进q的指针
这样可以按逆时针顺序生成闵可夫斯基和的边界
 *
*声明三个点集数组a[3]
读取三个凸包的顶点数据
*计算三个凸包的闵可夫斯基和
s存储结果凸包，n为其顶点数
 *对每个查询点(x,y)，将其坐标乘以3存储在p中
*使用二分查找判断点是否在凸包内：
初始化左右边界
检查点是否在凸包的扇形范围外，如果是则输出"NO"
*二分查找确定点所在的三角形扇区：
寻找相邻两个顶点s[l]和s[r]，使得点p位于它们与s[0]形成的扇区内
*验证二分查找结果
通过检查点p是否在边s[l]→s[r]的左侧来判断是否在凸包内
 *
*时间复杂度：

预处理（计算闵可夫斯基和）：O(n₁+n₂+n₃)
单次查询：O(log n)
总体：O(n+q log n)
 *
 *
 */
#include <cassert>
#include <complex>
#include <iostream>
#include <vector>
#include <algorithm>
#define sz(x) ((int)(x).size())
using namespace std;

typedef long long ll;
typedef complex<ll> point;
typedef vector<point> vp;

void reorder(vp& x) {
    int n = x.size(), idx(0);
    for (int i = 0; i < n; ++i) {
        if (x[i].imag() < x[idx].imag()) idx = i;
        else if (x[i].imag() == x[idx].imag() &&
            x[i].real() < x[idx].real()) idx = i;
    }
    rotate(x.begin(), x.begin() + idx, x.end());
}

ll cross(point a, point b) { return (conj(a) * b).imag(); }

vp operator+(vp p, vp q) {
    vp x; reorder(p); reorder(q);
    p.push_back(p[0]); p.push_back(p[1]);
    q.push_back(q[0]);q.push_back(q[1]);
    int i(0), j(0);
    while (i < sz(p) - 2 || j < sz(q) - 2) {
        x.push_back({p[i] + q[j]});
        ll cr = cross(p[i + 1] - p[i], q[j + 1] - q[j]);
        if (cr >= 0) i++;
        if (cr <= 0) j++;
    }
    return x;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    vp a[3];
    for (auto& x : a) {
        int n; cin >> n;
        for (int i = 0; i < n; ++i) {
            int u, v; cin >> u >> v;
            x.push_back(point(u, v));
        }
    }
    vp s = a[0] + a[1] + a[2]; int n = s.size();
    int q; cin >> q;
    while (q--) {
        int x, y; cin >> x >> y;
        point p(x, y); p *= 3;
        int l(1), r(n - 1);
        if (cross(s[l] - s[0], p - s[0]) < 0 ||
            cross(s[r] - s[0], p - s[0]) > 0) {
            cout << "NO\n"; continue;
        }
        while (l + 1 < r) {
            int mid = (l + r + 1) >> 1;
            if (cross(s[mid] - s[0], p - s[0]) >= 0) l = mid;
            else r = mid;
        }
        assert(l + 1 == r);
        assert(cross(s[l] - s[0], p - s[0]) >= 0 &&
            cross(s[r] - s[0], p - s[0]) <= 0);
        cross(s[r] - s[l], p - s[l]) >= 0 ? cout << "YES\n" : cout << "NO\n";
    }
    return 0;
}