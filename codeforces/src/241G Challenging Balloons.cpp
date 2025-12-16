//
// Created by Psy.C on 2025/12/14.
//
/*
*const vector<ii>& a：点坐标的引用（不可修改）
const int l：限制参数l
返回类型为double
*c：累积结果值，初始为0
r：double类型的向量，大小与输入向量相同，用于存储半径值
s：int类型的向量，作为栈使用
 *
 *初始化第i个点的半径为其y坐标值
*内层循环优化半径：
遍历栈s中的元素，最多l个
t：从栈顶开始向前取元素的索引
计算新的半径值：基于两点间距离和前一点半径的几何关系
取较小值作为当前点半径
*维护单调栈：
当栈不为空且栈顶元素对应的半径小于等于当前半径时
弹出栈顶元素
保持栈中半径值的单调递增性质
 *将当前索引压入栈中
 *将当前点半径累加到总和中
 *返回累积结果值
 *
*比较使用不同l参数调用函数f的结果
如果结果不同则返回true，否则返回false
 *
*x坐标：从300000开始，间隔600递增
y坐标：从300开始递减到1
 *设置最后一个点为(1000000, 1000000)
 *
 *r[i] = min(r[i], (dx²)/(4*r[j]))
 *
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int,int>
using namespace std;

double f(const vector<ii>& a, const int l) {
    double c = 0;
    vector<double> r(a.size());
    vector<int> s;
    for (int i = 0; i < static_cast<int>(a.size()); ++i) {
        r[i] = a[i].second;
        for (int j = 0; j < min(static_cast<int>(s.size()), l); ++j) {
            const double t = s[s.size() - j - 1];
            r[i] = min(r[i], pow(a[i].first -
                a[static_cast<int>(t)].first, 2) / r[static_cast<int>(t)] / 4);
        }
        while (!s.empty() && r[s.back()] <= r[i]) s.pop_back();
        s.emplace_back(i);
        c += r[i];
    }
    return c;
}

bool ok(const vector<ii>& a) { return f(a, static_cast<int>(a.size())) != f(a, 300); }


int main() {
    fast;
    vector<ii> a(302); a[0] = {1, 1e6};
    for (int i = 1; i <= 300; ++i) a[i] = {3e5+i*600, 300 - i + 1};
    a[301] = {1e6, 1e6};
    if (ok(a)) {
        cout << "302\n";
        for (const auto& p : a) cout << p.first << ' ' << p.second << '\n';
    } else cout << "Wrong Answer!\n";
    return 0;
}