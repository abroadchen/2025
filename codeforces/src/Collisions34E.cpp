//
// Created by Psy.C on 2025/9/22.
//

#include <algorithm>
#include <cstdio>
#define rep(i,a,b) for(long i=(a);i<=(b);++i)
using namespace std;
typedef double db;
const db eps = 1e-9;
const int N = 15;
int n, m[N], ord[N], mins;// n:物体数量, m[]:质量数组, ord[]:排序索引数组, mins:最小时间索引
db t, x[N], v[N], ct, mct, tmp;// t:总时间, x[]:位置数组, v[]:速度数组, ct:当前时间, mct:最小碰撞时间, tmp:临时变量

bool cmp(int i, int j) { return x[i] < x[j]; }// 比较函数，根据位置坐标排序

int main() {
    scanf("%d %lf", &n, &t);
    rep (i, 1, n) scanf("%lf %lf %d", &x[i], &v[i], &m[i]);
    rep (i, 1, n) ord[i] = i;// 初始化排序数组，ord[i] = i
    sort(ord + 1, ord + 1 + n, cmp);

    ct = 0;// 初始化当前时间为0
    while (ct < t) {// 当前时间小于总时间时继续模拟
        mct = t - ct;// 初始化最小碰撞时间为剩余时间
        mins = 0;// 初始化最小时间索引为0
        for (int i = 1; i < n; ++i) {// 遍历相邻物体对
            if (v[ord[i]] - v[ord[i + 1]] < eps) continue;// 如果前一个物体速度不大于后一个物体，跳过
            tmp = (x[ord[i + 1]] - x[ord[i]]) / (v[ord[i]] - v[ord[i + 1]]);// 计算碰撞时间
            if (tmp < -eps) continue;// 如果时间为负，跳过
            if (tmp < mct) {// 如果找到更小的正碰撞时间
                mct = tmp;
                mins = i;
            }
        }

        rep (i, 1, n) x[i] += v[i] * mct;// 根据速度和时间更新所有物体位置
        ct += mct;// 更新当前时间
        if (mins != 0) {// 如果发生了碰撞
            int i = mins;// 获取碰撞物体索引
            db v1 = v[ord[i]], v2 = v[ord[i + 1]];// 获取碰撞前速度
            int m1 = m[ord[i]], m2 = m[ord[i + 1]];// 获取质量
            v[ord[i]] = ((m1 - m2) * v1 + 2 * m2 * v2) / (m1 + m2);// 根据动量守恒和能量守恒计算碰撞后速度
            v[ord[i + 1]] = ((m2 - m1) * v2 + 2 * m1 * v1) / (m1 + m2);
        }
    }
    rep (i, 1, n) printf("%.12lf\n", x[i]);
    return 0;
}