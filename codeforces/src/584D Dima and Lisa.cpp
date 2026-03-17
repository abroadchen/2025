//
// Created by Psy.C on 2026/3/17.
//
/**
素数判断函数
特殊处理2和3（直接返回true）
对于其他数，从2遍历到√x，检查是否有因子
如果有因子则返回false，否则返回true

n：输入的正整数
k：存储找到的素数
m：剩余的部分
i：循环变量
如果n是素数，直接输出1个素数n
如果n-2是素数，输出2和n-2（根据哥德巴赫猜想的变体）
如果n-4是素数，输出2, 2, n-4（即n = 2+2+(n-4)）

步骤1：找最大的接近n的素数
从n-3开始向前搜索，直到n-300或1
找到最大的素数k
步骤2：处理剩余部分m = n - k
如果m也是素数：输出2个素数（m和k）
否则：将m分解为两个素数之和（根据哥德巴赫猜想）

时间复杂度：
素数判断：O(√n)
主算法：O(300 × √n) ≈ O(√n)
空间复杂度：
O(1)，只使用常数个变量

弱哥德巴赫猜想（已证明）：任何大于7的奇数都可以表示为三个奇素数之和
强哥德巴赫猜想（未证明）：任何大于2的偶数都可以表示为两个素数之和

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

bool ok(int x) {
    if (x == 2 || x == 3) return true;
    for (int i = 2; i <= sqrt(x); ++i)
        if (x % i == 0) return false;
    return true;
}

int n, k, m, i;
int main() {
    fast;
    cin >> n;
    if (ok(n)) cout << "1\n" << n << '\n';
    else if (ok(n-2)) cout << "2\n2 " << n-2 << '\n';
    else if (ok(n-4)) cout << "3\n2 2 " << n-4 << '\n';
    else {
        for (i = n - 3; i >= n - 300 && i >= 1; --i)
            if (ok(i)) { k = i; break; }
        m = n - i;
        if (ok(m)) cout << "2\n" << m << ' ' << k;
        else {
            for (i = 2; i <= m; ++i)
                if (ok(i) && ok(m - i)) {
                    cout << "3\n" << i << ' ' << m-i << ' ' << k << '\n';
                    break;
                }
        }
    }
    return 0;
}