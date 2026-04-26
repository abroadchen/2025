//
// Created by Psy.C on 2026/4/25.
//
/**
x1 = a[1] + a[2]
x2 = a[2] + a[3]
x3 = a[1] + a[3]
x1 + x2 + x3 = (a[1]+a[2]) + (a[2]+a[3]) + (a[1]+a[3]) = 2*(a[1]+a[2]+a[3])
所以 (x1+x2+x3)/2 = a[1]+a[2]+a[3]
因此：
a[1] = (a[1]+a[2]+a[3]) - (a[2]+a[3]) = (x1+x2+x3)/2 - x2
a[2] = (a[1]+a[2]+a[3]) - (a[1]+a[3]) = (x1+x2+x3)/2 - x3
a[3] = (a[1]+a[2]+a[3]) - (a[1]+a[2]) = (x1+x2+x3)/2 - x1
已知 a[i] 和 a[i] + a[i+1] = x
所以 a[i+1] = x - a[i]
使用 ! 标记输出答案
输出完整的数组

初始查询：3次（确定前3项）
后续查询：n-3次（每项一个查询）
总计：n次查询
这是最优解，因为要确定n个未知数至少需要n个方程

缓冲区行为改变
不使用fast：endl 会自动刷新缓冲区
使用fast：取消了自动刷新机制，只使用 '\n' 不会刷新
输入输出顺序混乱
fast 解除了标准输入输出流的绑定
导致程序可能在发送询问前就尝试读取响应
5. 为什么手动fflush仍然不够
即使使用 fflush(stdout)：
在fast模式下，C++流和C流的缓冲区管理可能不一致
可能导致输出顺序和预期不符
cout << "? " << x << " " << y << '\n';
cout.flush();  // 显式刷新
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 5007;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int a[N];
int main() {
    int n = rd();
    cout << "? " << 1 << ' ' << 2 << '\n'; fflush(stdout);
    int x1 = rd();
    cout << "? " << 2 << ' ' << 3 << '\n'; fflush(stdout);
    int x2 = rd();
    cout << "? " << 1 << ' ' << 3 << '\n'; fflush(stdout);
    int x3 = rd();
    a[1] = (x1 + x2 + x3)/2 - x2;
    a[2] = (x1 + x2 + x3)/2 - x3;
    a[3] = (x1 + x2 + x3)/2 - x1;
    for (int i = 3; i <= n-1; ++i) {
        cout << "? " << i << ' ' << i + 1 << '\n'; fflush(stdout);
        int x = rd(); a[i+1] = x - a[i];
    }
    cout << "! ";
    for (int i = 1; i <= n; ++i) cout << a[i] << ' ';
    return 0;
}