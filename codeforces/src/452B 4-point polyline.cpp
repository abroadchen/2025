//
// Created by Psy.C on 2026/2/10.
//
/**
d1 = get(0,0,n,m)*2 + get(0,0,n,0)
d1 = 2*(n² + m²) + n² = 3n² + 2m²

d2 = get(0,0,n,m) + get(0,0,n,m-1)*2
d2 = (n² + m²) + 2*(n² + (m-1)²)
d2 = n² + m² + 2n² + 2(m² - 2m + 1)
d2 = 3n² + 3m² - 4m + 2

时间复杂度：O(1)，只进行常数次计算
空间复杂度：O(1)，只使用固定数量的变量
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int get(const int x1, const int y1, const int x2, const int y2) {
    return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
}

int n, m, x1, x2, x3, x4, y11, y2, y3, y4;//四个点

int main() {
    fast;
    cin >> n >> m;
    bool flag = false;
    //标准化处理：确保n ≥ m，如果交换过则flag=true
    if (m > n) { swap(n, m); flag = true; }
    if (m == 0) {//退化为线段
        x1 = 1, x2 = n, x3 = 0, x4 = n - 1;//x轴上
        y11 = y2 = y3 = y4 = 0;
    } else {
        const int d1 = get(0, 0, n, m)*2 + get(0, 0, n, 0),
        d2 = get(0, 0, n, m) + get(0, 0, n, m-1)*2;
        if (d1 > d2) {
            x1 = 0, y11 = 0;
            x2 = n, y2 = m;
            x3 = 0, y3 = m;
            x4 = n, y4 = 0;
        } else {
            x1 = 0, y11 = 1;
            x2 = n, y2 = m;
            x3 = 0, y3 = 0;
            x4 = n, y4 = m - 1;
        }
    }
    if (flag) {//恢复坐标：如果之前交换过n和m，则交换坐标轴
        swap(x1, y11); swap(x2, y2);
        swap(x3, y3); swap(x4, y4);
    }
    cout << x1 << ' ' << y11 << '\n' << x2 << ' ' << y2 << '\n' <<
        x3 << ' ' << y3 << '\n' << x4 << ' ' << y4 << '\n';
    return 0;
}