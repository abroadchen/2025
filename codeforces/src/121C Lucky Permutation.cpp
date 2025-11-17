//
// Created by Psy.C on 2025/11/17.
//
/*
*定义递归函数C，用于计算[a,b]范围内幸运数字(只包含4和7的数字)的个数
如果a>b，返回0(递归终止条件)
否则返回1(当前数字a)加上以a10+4和a10+7为前缀的幸运数字个数
 *
*定义递归函数ok，用于判断x是否为幸运数字
如果x为0，返回true(递归终止条件)
否则检查最后一位是否为4或7，并且去掉最后一位后仍然是幸运数字
 *
 *k减1(转换为0索引)
 *初始化阶乘数组：f[0]=1，然后计算1!到13!的值
 *如果n≤13且n!≤k，说明不存在第k个排列，输出-1并退出
 *计算[0,n]范围内幸运数字个数并减1，初始化答案
 *从13到0的循环，用于构造第k个排列
 *计算k除以i!的商，初始化计数器cnt为-1
 *找到第x个未被使用的数字：递增cnt，如果m[cnt]为false(!m[++cnt]为true)，则x减1
 *标记数字cnt为已使用
*计算t=cnt-13+n
如果t>0且n-i是幸运数字，则加上(ok(t)-1)
 *更新k为k对i!取模的结果
 *
 *
*x -= !m[++cnt] 的作用
当数字cnt未被使用时：x -= 1，表示找到了一个可用数字
当数字cnt已被使用时：x -= 0，相当于x不变，继续寻找
 *
*k / (n-1)! 就告诉我们应该选择第几个数字
k % (n-1)! 成为下一位的新k值
 *
 *
 */
#include <iostream>
using namespace std;

typedef long long ll;
const int N = 20;
ll f[N];//用于存储阶乘值
bool m[N];//标记数字是否已被使用

int C(ll a, ll b) {
    if (a > b) return 0;
    return 1 + C(a * 10 + 4, b) + C(a * 10 + 7, b);
}
int ok(ll x) {
    return x == 0 || (x % 10 == 4 || x % 10 == 7) &&
        ok(x / 10);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, k; cin >> n >> k; k--;
    f[0] = 1;
    for (int i = 1; i <= 13; ++i) f[i] = f[i - 1] * i;
    if (n <= 13 && f[n] <= k) { cout << -1; return 0; }

    int ans = C(0, n) - 1;//排除数字 0
    for (int i = 13, x, cnt, t; i >= 0; --i) {
        x = k / f[i]; cnt = -1;//计算需要跳过的已使用数字个数
        while (x >= 0) x -= !m[++cnt];
        m[cnt] = 1;
        t = cnt - 13 + n;//将基于数组索引的cnt值转换为实际有意义的数值
        if (t > 0) { if (ok(n - i)) ans += ok(t) - 1; }
        k %= f[i];
    }
    cout << ans;
    return 0;
}