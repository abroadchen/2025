//
// Created by Psy.C on 2025/10/31.
//
/*
 *
 *p1-p4是四个参数，a和b是区间端点，t是临时变量
 */
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;
ll p1, p2, p3, p4, a, b, t;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin >> p1 >> p2 >> p3 >> p4 >> a >> b;
    t = min({p1, p2, p3, p4});
    b = min(b, t - 1);//确保了b不会超过(t-1)
    cout << max(0ll, b - a + 1) << endl;//确保结果不为负数
    return 0;
}