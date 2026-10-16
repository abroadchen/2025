//
// Created by Psy.C on 2026/10/16.
//
/**
n：总参赛人数（通常为 2 的幂）。
a、b：两个人的初始编号（代表最初所在的叶子位置）
关键运算 x/2 + x%2 = ⌈x/2⌉

若 x 为偶数：x/2 + 0 = x/2。
若 x 为奇数：x/2 + 1 = (x+1)/2，即向上取整。
这正是"编号向上走到父节点"的规则：在满二叉树里，节点 x 的父节点编号是 ⌈x/2⌉。

每一轮：

a、b 都跳到各自的父节点；
轮数 s++；
参赛人数 n 右移一位（人数减半）。
循环持续到 a == b，即两人第一次进入同一个节点（相遇）
若循环结束时 n != 1：说明两人在决赛之前就已经相遇，输出相遇的轮数 s。
若循环结束时 n == 1：说明两人一直不相遇，直到只剩下 1 人（即决赛才相遇），输出 "Final!"。
逻辑对应：如果两人一路都分在不同半区，就只能到决赛（最后一轮，n 减到 1）才碰上，此时输出 Final!；否则在中间某一轮就碰上了，输出轮数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int n, a, b, s;
int main() {
    fast;
    cin >> n >> a >> b;
    while (a != b) {
        a = a/2+a%2; b = b/2+b%2;
        s++;
        n>>=1;
    }
    if (n != 1) cout << s << '\n';
    else cout << "Final!" << '\n';
    return 0;
}