//
// Created by Psy.C on 2025/12/8.
//
/*
*用于标记数字x中出现的数字（0-9）
d[i]为true表示数字i在x中出现过
*当n不为0时循环
n%10：获取n的个位数字
d[n%10] = true：标记这个数字在n中出现过
n /= 10：去掉n的个位数字
逗号运算符依次执行两个操作
 *
*判断数字n是否包含数字x中的任意一个数字：
当n不为0时循环
n%10：获取n的个位数字
if (d[n%10])：检查这个数字是否在x中出现过
如果出现过，返回true
n /= 10：去掉n的个位数字
如果遍历完所有位数都没找到，返回false
 *
*t = 1：因子候选，从1开始
cnt = 0：计数器，记录满足条件的因子个数
当t * t < x时循环（只需检查到√x）
if (x % t == 0)：如果t是x的因子
if (ok(t)) ++cnt：如果t包含x中的数字，计数器加1
if (ok(x / t)) ++cnt：如果x/t包含x中的数字，计数器加1
++t：检查下一个候选因子
 *
 *时间复杂度为O(√n)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

bool d[10] = {false};
void init(int n) { while (n != 0) d[n%10] = true, n /= 10; }
bool ok(int n) {
    while (n != 0) {
        if (d[n%10]) return true;
        n /= 10;
    }
    return false;
}

int main() {
    fast;
    int x; cin >> x; init(x);
    int t = 1, cnt = 0;
    while (t * t < x) {
        if (x % t == 0) {
            if (ok(t)) ++cnt;
            if (ok(x / t)) ++cnt;
        }
        ++t;
    }
    if (t * t == x && ok(t)) ++cnt;
    cout << cnt << '\n';
    return 0;
}