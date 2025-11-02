//
// Created by Psy.C on 2025/11/2.
//
/*
*mx: x的最大值
mn: y的最大值
w: 权重阈值
x, y: 变量，用于遍历
cnt(0): 计数器，初始化为0
ans1, ans2: 存储最终答案的x和y值
q: 用于存储比值的double变量
m1, m2: 两个map容器，用于统计不同比值的出现次数
 *
*定义函数solve，用于将整数k的各位数字反转
例如：solve(123)返回321，solve(1200)返回21
算法原理：通过取余和整除操作逐位提取数字并构建反转后的数字
 *
*遍历x从1到mx
计算每个x与其数字反转后的数的比值：x/reverse(x)
将这个比值作为键存储在map m1中，并统计每个比值出现的次数
 *
*如果当前计数cnt小于权重w：
y递增
计算y的反转数与y的比值：reverse(y)/y
在m1中查找该比值对应的计数，并加到cnt上
将该比值记录到m2中
 *
*如果cnt大于等于w：
如果当前x*y更小或者ans1还未被赋值，则更新答案
计算x与其反转数的比值
从cnt中减去m2中该比值的计数
在m1中减少该比值的计数
x递减
 *
*如果ans1仍为0，说明没有找到满足条件的解，输出-1
否则输出找到的最优解ans1和ans2
 *
 */
#include <map>
#include <iostream>
using namespace std;

int mx, mn, w, x, y, cnt(0), ans1, ans2;
double q;
map<double, int> m1, m2;

int solve(int k) {
    int p(0);
    while (k > 0) {
        p = p * 10 + (k % 10);
        k /= 10;
    }
    return p;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> mx >> mn >> w;
    for (x = 1; x <= mx; ++x) {
        q = (double)(x * 1.0 / solve(x));
        m1[q]++;
    }
    x = mx; y = 0;
    while (y <= mn && x >= 1) {
        if (cnt < w) {
            y++;
            q = (double)((solve(y) * 1.0) / y);
            cnt += m1[q];
            m2[q]++;
        } else {
            if (ans1 * ans2 > x * y || ans1 == 0) {
                ans1 = x;
                ans2 = y;
            }
            q = (double)((x * 1.0) / solve(x));
            cnt -= m2[q];
            m1[q]--;
            x--;
        }
    }
    if (ans1 == 0) cout << -1;
    else cout << ans1 << " " << ans2;
    return 0;
}