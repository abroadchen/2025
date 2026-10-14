//
// Created by Psy.C on 2026/10/14.
//
/**
n：目标编号（用户输入，找第 n 个符合条件的数）。
num：计数器，记录已找到多少个符合条件的数
作用：计算整数 x 的各位数字之和（数位和）。
循环逻辑：每次取 i%10（当前个位数字）累加到 sum，然后 i/=10 去掉个位，直到 i 变为 0。
例如 get(1234) = 1+2+3+4 = 10。
注意「i >= 1」的判断：由于 int 被宏替换为 long long，x 始终为正数时循环正常结束
cin >> n：读入 n。
for (int i = 1; ; ++i)：无限循环从 1 开始逐个枚举正整数 i（没有终止条件）。
对每个 i，调用 get(i) 求数位和，若等于 10：
num++ 计数器 +1；
若 num == n（已经找到第 n 个），执行 return cout << i, 0;——输出当前的 i 并结束程序（逗号表达式：先 cout << i 输出，再返回 0
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

inline int get(int x) {
    int sum = 0;
    for (int i = x; i >= 1; i/=10)
        sum += i%10;
    return sum;
}

int n, num;
signed main() {
    fast;
    cin >> n;
    for (int i = 1; ; ++i) {
        if (get(i) == 10) {
            num++;
            if (num == n)
                return cout << i, 0;
        }
    }
    return 0;
}