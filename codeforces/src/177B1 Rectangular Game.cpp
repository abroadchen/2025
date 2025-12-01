//
// Created by Psy.C on 2025/11/30.
//
/*
*循环查找k的奇数因子，从3开始到√k
i += 2确保只检查奇数
一旦找到因子就立即返回该因子（这是最小的奇质因数）
 *
*t: 输入的数值
f: 因子，初始化为1
ans: 答案累加器，初始化为0
 *
 *将t除以因子f，相当于进行因式分解的一步
 *将当前的t值加到答案中
*调用fac(t)获取t的最小因子，并将其赋值给f
如果f不为0（即t不是质数），继续循环
如果f为0（即t是质数），退出循环
 *
*当循环终止时，是因为fac(t)返回了0（意味着t变成了质数）。在这个时候：
最后一个质因子没有被处理
我们需要把这个最终的质数加入到总和中
但由于fac(t)返回0，循环退出了，没有把它加进去
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

inline int fac(const int k) {
    if (k <= 2) return 0;//1和2没有真因数
    if ((k & 1) == 0) return 2;//如果k是偶数，返回2（最小质因数）
    for (int i = 3; i * i <= k; i += 2) if (k % i == 0) return i;
    return 0;
}

int main() {
    fast;
    int t, f(1), ans(0); cin>>t;
    do {
        t /= f;
        ans += t;
    } while ((f = fac(t)));
    cout << ans + 1 << '\n';
    return 0;
}