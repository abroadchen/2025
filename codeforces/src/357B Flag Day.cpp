//
// Created by Psy.C on 2026/1/18.
//
///c存储每个元素的颜色(初始化为0)，a临时存储每次操作的三个元素
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, m; cin >> n >> m;
    int c[123456]={}, a[3];
    for (int i = 0; i < m; ++i) {
        cin >> a[0] >> a[1] >> a[2];//操作涉及的三个元素编号
        if (i == 0) {//第一次操作
            c[a[0]] = 1;//第一个元素分配颜色1
            c[a[1]] = 2;//第二个元素分配颜色2
            c[a[2]] = 3;//第三个元素分配颜色3
        } else {
            if (c[a[0]] != 0) {//第一个元素已经有颜色
                c[a[1]] = c[a[0]] + 1;//第二个元素颜色=第一个元素颜色+1
                c[a[2]] = c[a[0]] + 2;
                if (c[a[1]] > 3) c[a[1]] -= 3;//颜色超过3，循环回到1-3范围内
                if (c[a[2]] > 3) c[a[2]] -= 3;
            } else if (c[a[1]] != 0) {
                c[a[0]] = c[a[1]] + 1;
                c[a[2]] = c[a[1]] + 2;
                if (c[a[0]] > 3) c[a[0]] -= 3;//颜色循环调整
                if (c[a[2]] > 3) c[a[2]] -= 3;
            } else if (c[a[2]] != 0) {
                c[a[0]] = c[a[2]] + 1;
                c[a[1]] = c[a[2]] + 2;
                if (c[a[0]] > 3) c[a[0]] -= 3;
                if (c[a[1]] > 3) c[a[1]] -= 3;
            } else {//三个元素都没有颜色
                c[a[0]] = 1;
                c[a[1]] = 2;
                c[a[2]] = 3;
            }
        }
    }
    for (int i = 1; i < n; ++i) cout << c[i] << ' ';
    cout << c[n] << '\n';
    return 0;
}