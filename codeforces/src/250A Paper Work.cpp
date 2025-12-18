//
// Created by Psy.C on 2025/12/17.
//
/*
*如果负数个数是奇数，加1变为偶数（因为每两个负数组成一对）
除以2得到需要的分割段数
如果没有负数，至少需要1段
输出分割段数
 *
*c: 当前段中负数计数
d: 当前段长度计数
g: 已输出段的总长度
遍历数组：
遇到负数则c加1
每个元素都使d加1
当当前段找到2个负数且还需要分割更多段时：
输出当前段长度
更新总计数器
重置计数器，继续下一段
当找到最后一对负数时停止
输出最后一段的长度(a-g)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 105
using namespace std;


int main() {
    fast;
    int a; cin>>a;
    int m[N], cnt = 0;
    for (int i = 0; i < a; ++i) {
        cin>>m[i];
        if (m[i] < 0) cnt++;
    }
    if (cnt % 2 == 1) cnt++;
    cnt /= 2;
    if (cnt == 0) cnt = 1;
    cout << cnt << '\n';
    int c = 0, d = 0, g = 0;
    for (int i = 0; i < a; ++i) {
        if (m[i] < 0) c++;
        d++;
        if (c == 2 && cnt > 1) {
            cout << d << ' ';
            g += d;
            d = 0, c = 0;
            cnt--;
        } else if (c == 2 && cnt == 1) break;
    }
    cout << a - g;
    return 0;
}