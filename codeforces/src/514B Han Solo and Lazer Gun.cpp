//
// Created by Psy.C on 2026/2/28.
//
/**
n：点的数量
x0, y00：固定参考点的坐标
x, y：当前读入的点的坐标
st：存储斜率的集合（使用set自动去重和排序）

如果y00 - y == 0（水平线，斜率为无穷大）：
插入特殊值20000.代表水平线
如果x0 - x == 0（垂直线，斜率为0）：
插入特殊值30000.代表垂直线
否则计算并插入正常斜率：
1.*(x0-x)/(y00-y)：计算两点连线相对于y轴的斜率倒数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, x0, y00, x, y;
set<double> st;
int main() {
    fast;
    cin >> n >> x0 >> y00;
    while (n--) {
        cin >> x >> y;
        if (y00 - y == 0 && x0 - x == 0) continue;//当前点与参考点重合
        if (y00 - y == 0) st.insert(20000.);
        else if (x0 - x == 0) st.insert(30000.);
        else st.insert(1.*(x0-x)/(y00-y));
    }
    cout << st.size() << '\n';
    return 0;
}