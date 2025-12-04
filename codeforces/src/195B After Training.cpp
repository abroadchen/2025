//
// Created by Psy.C on 2025/12/3.
//
/*
*mid = (m - 1) >> 1: 计算(m-1)除以2的结果（即m的中间位置），使用右移运算符实现整数除法
cur = 0: 当前步数计数器，初始化为0
k = n: 循环计数器，初始化为n
 *
*如果m是奇数：
如果当前步数cur是奇数，则从mid中减去cur
如果当前步数cur是偶数，则向mid加上cur
*如果m是偶数：
如果当前步数cur是奇数，则向mid加上cur
如果当前步数cur是偶数，则从mid中减去cur
 *
*检查mid是否等于m-1（即到达了末尾位置）
如果是，则重置：
将mid重新设置为中间位置(m-1)>>1
将当前步数cur重置为0
 *
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, m; cin>>n>>m;
    int mid = (m - 1) >> 1, cur = 0, k = n;
    while (k--) {//先使用k的当前值判断条件，然后k减1
        if (m % 2) {
            if (cur % 2) mid -= cur;
            else mid += cur;
        } else {
            if (cur % 2) mid += cur;
            else mid -= cur;
        }
        cout << mid + 1 << '\n';//输出从1开始的索引
        cur++;//当前步数计数器加1
        if (mid == m - 1) { mid = (m - 1) >> 1; cur = 0; }
    }
    return 0;
}