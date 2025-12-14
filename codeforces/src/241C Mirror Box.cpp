//
// Created by Psy.C on 2025/12/14.
//
/*
*hl, hr：左右两侧镜子的高度
n：传感器的数量
t[N], f[N]：数组用于存储顶部和底部镜子上每个位置对应的传感器ID
val[M]：每个传感器的分值
flag[M]：布尔数组用于标记已访问的传感器
 *
*读取每个传感器的信息：分值、位置（T表示顶部，F表示底部）和范围[l,r]
将范围内每个位置映射到相应的传感器ID
 *
 *奇数次反射情况的模拟
*根据镜面几何关系计算总的路径长度
计算每段的长度和初始位置
des：目标指示器（1表示底部，0表示顶部）
test：当前路径的累计得分
 *
*模拟光束在镜子间的反弹过程
在每次反弹时，检查该位置是否有传感器
确保同一传感器不会被击中两次
累计击中传感器的得分
 *
*偶数次反射情况的模拟：
类似的过程但起始条件不同
这覆盖了光束初始方向的两种可能性
 *
 */
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
#define M 105
#define db double
#define len 100000
#define H 100.
using namespace std;


int main() {
    fast;
    int hl, hr, n; cin >> hl >> hr >> n;
    int t[N] = {0}, f[N] = {0}, val[M];
    bool flag[M];
    for (int i = 1, l, r; i <= n; ++i) {
        char str[10];
        cin >> val[i] >> str >> l >> r;
        if (str[0] == 'F') for (int j = l; j <= r; ++j) f[j] = i;
        else for (int j = l; j <= r; ++j) t[j] = i;
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        db tmp = 0;
        if (i&1) tmp += hl/H + (i-1) + hr/H;
        else tmp += hl/H + (i-1) + (H-hr)/H;
        db l = len / tmp, pos = l * hl / H;
        int des = 1, test = 0;
        memset(flag, false, sizeof(flag));
        for (int j = 1; j <= i; ++j) {
            if (des) {
                if (f[static_cast<int>(floor(pos))] == 0 &&
                    f[static_cast<int>(ceil(pos))] == 0) {
                    test = -1; break;
                }
                const int id = f[static_cast<int>(floor(pos))];
                if (flag[id]) { test = -1; break; }
                flag[id] = true; test += val[id];
            } else {
                if (t[static_cast<int>(floor(pos))] == 0 &&
                    t[static_cast<int>(ceil(pos))] == 0) {
                    test = -1; break;
                }
                const int id = t[static_cast<int>(floor(pos))];
                if (flag[id]) { test = -1; break; }
                flag[id] = true; test += val[id];
            }
            pos += l;
            des = 1 - des;
        }
        ans = max(ans, test); tmp = 0;
        if (i & 1) tmp += (H - hl) / H + (i-1) + (H - hr) / H;
        else tmp += (H - hl) / H + (i-1) + hr / H;
        l = len / tmp; pos = l * (H - hl) / H; des = 0; test = 0;
        memset(flag, false, sizeof(flag));
        for (int j = 1; j <= i; ++j) {
            if (des) {
                if (f[static_cast<int>(floor(pos))] == 0 &&
                    f[static_cast<int>(ceil(pos))] == 0) {
                    test = -1; break;
                }
                const int id = f[static_cast<int>(floor(pos))];
                if (flag[id]) { test = -1; break; }
                flag[id] = true; test += val[id];
            } else {
                if (t[static_cast<int>(floor(pos))] == 0 &&
                    t[static_cast<int>(ceil(pos))] == 0) {
                    test = -1; break;
                }
                int id = t[static_cast<int>(floor(pos))];
                if (flag[id]) { test = -1; break; }
                flag[id] = true; test += val[id];
            }
            des = 1 - des;
            pos += l;
        }
        ans = max(ans, test);
    }
    cout << ans << '\n';
    return 0;
}