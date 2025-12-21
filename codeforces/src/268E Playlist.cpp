//
// Created by Psy.C on 2025/12/21.
//时间复杂度是O(n log n)

#include <iomanip>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 50005
#define eps 1e-9
using namespace std;

struct node { double l, p; } e[N];//长度l和概率p

int main() {
    fast;
    int n; cin >> n; double ans = 0;
    for (int i = 0; i < n; ++i) {
        cin >> e[i].l >> e[i].p;
        e[i].p /= 100.;//将百分比转换为小数
        ans += e[i].l;//累加所有长度作为基础答案
    }
    sort(e, e + n, [](const node a, const node b) {//得到最大的总期望值
        return a.l * a.p * (1 - b.p) - b.l * b.p * (1 - a.p) > eps;
    });
    double t = 0;//累积期望值
    for (int i = 0; i < n; ++i) {
        ans += t * (1 - e[i].p);//累加前面项目的期望值乘以当前项目不被选中的概率
        t += e[i].l * e[i].p;//更新累积期望值(当前项目被选中的期望长度)
    }
    cout << fixed << setprecision(9) << ans << '\n';
    return 0;
}