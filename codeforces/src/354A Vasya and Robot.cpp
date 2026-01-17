//
// Created by Psy.C on 2026/1/16.
//
/**
 *
*n: 数组长度
l: 左侧操作成本
r: 右侧操作成本
ql: 左移操作成本
qr: 右移操作成本
a[N]: 存储输入数组
 *
*初始化ans为一种极端情况的成本
a[n-1] * r: 所有元素都按右侧成本处理
(n - 1) * qr: n-1次右侧移动操作
 *
*声明临时变量t（当前成本）和d（差值）
t = a[i] * l + (a[n - 1] - a[i]) * r;: 计算前i+1个元素用左侧成本，剩余元素用右侧成本的总成本
 *
*n1 = i + 1: 左侧元素个数
n2 = n - n1: 右侧元素个数
d = n2 - n1: 两侧元素个数的差值
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
using namespace std;


int main() {
    fast;
    int n, l, r, ql, qr, a[N]; cin >> n >> l >> r >> ql >> qr;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];// 读入当前元素
        if (i != 0) a[i] += a[i - 1];//构建前缀和数组
    }
    int ans = a[n - 1] * r + (n - 1) * qr;
    for (int i = 0, t, d; i < n; ++i) {
        t = a[i] * l + (a[n - 1] - a[i]) * r;
        const int n1 = i + 1, n2 = n - n1; d = n2 - n1;
        if (abs(d) > 1) {
            if (d > 0) {//右侧多于左侧
                d--;//调整差值
                t += d * qr;//增加右侧移动成本
            }
            if (d < 0) {
                d++;
                t += -d * ql;
            }
        }
        ans = ans < t ? ans : t;
    }
    cout << ans << '\n';
    return 0;
}