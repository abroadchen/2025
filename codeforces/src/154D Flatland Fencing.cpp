//
// Created by Psy.C on 2025/11/24.
//
/*
*x1: 起始位置
x2: 目标位置
a, b: 每次移动的最小和最大距离范围
d: 起点到终点的距离
dir: 方向标志（1表示正向，-1表示反向）
 *当移动范围都在负数区间时，通过对称变换将问题转换为正数范围处理，简化后续逻辑
 *
 *res默认为平局 pos获胜位置 flag是否先手获胜
 *
*d / (a + b) - 整除运算
计算距离d中有多少个完整的(a+b)周期
这里的(a+b)代表两个玩家一轮的总移动范围
(d / (a + b)) * (a + b) - 完整周期的总距离
计算所有完整周期累积的移动距离
 *从目标点x2开始，根据方向和完整周期数回推实际应移动到的位置
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0); \
    cin.tie(nullptr); cout.tie(nullptr)
using namespace std;

int main() {
    fast;
    int x1, x2, a, b; cin >> x1 >> x2 >> a >> b;
    int d = x2 - x1, dir = 1;
    if (a <= 0 && b <= 0) {
        const int t = a; a = -b; b = -t;
        d = -d; dir = -1;
    }
    string res = "DRAW"; int pos = 0; bool flag = false;
    if (a <= 0) {
        if (d >= a && d <= b) {//正好在一次移动的范围内
            res = "FIRST"; pos = x2; flag = true;//可以直接一步移动到目标位置
        }
    } else {
        if (d >= 0) {//只允许正向移动
            if (d % (a + b) == 0) res = "SECOND";
            else if (d % (a + b) >= a && d % (a + b) <= b) {
                res = "FIRST";
                pos = x2 - dir * (d / (a + b)) * (a + b);
                flag = true;
            }
            // 否则保持默认的DRAW结果
        }
        // 如果d < 0，也保持默认的DRAW结果
    }
    cout << res << '\n';
    if (flag) cout << pos << '\n';
    return 0;
}