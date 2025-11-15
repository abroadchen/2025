//
// Created by Psy.C on 2025/11/15.
//
/*
*定义print函数，用于打印一个9位数字（不足9位前面补0）
a[9]：存储数字的每一位
第一个循环：将数字n分解为9位，从低位到高位存储在a[8]到a[0]中
第二个循环：按顺序输出每一位数字
例如：print(123)会输出：000000123
 *
 *flag = false：标记是否找到解
 *ub = min(x, z-1)：计算上界
 *
*step = 10^9 % z 表示10^9除以z的余数
在循环中，res实际上是(i * 10^9) % z的值
寻找最小的i使得(i * 10^9) % z在范围(0, z-y)内
 *
*模z意义下，最多只需要检查z个不同的值就能找到所有可能的余数。
如果 step = 1000000000 % z 与 z 互质，那么序列： 0, step, 2step, 3step, ..., (z-1)*step (mod z)
将遍历 {0, 1, 2, ..., z-1} 的所有值（只是顺序不同）
 *
*如果 res < z - y，这意味着：
res 的值必须在区间 [1, z-y-1] 内（结合前面的 res != 0 条件）
 */
#include <iostream>
#define inf 1000000000
using namespace std;

int x, y, z;

void print(int n) {
    int a[9];
    for (int i = 8; i >= 0; --i) { a[i] = n % 10; n /= 10; }
    for (int i = 0; i <= 8; ++i) cout << a[i];
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin>>x>>y>>z;
    if (y + 1 >= z) cout << 2;
    else {
        int step = inf % z; bool flag = false;
        int ub = min(x, z - 1);
        for (int i = 0, res = 0; i <= ub; ++i, res += step) {
            if (res >= z) res -= z;
            if (res != 0 && res < z - y) {
                flag = true;
                cout << 1 << ' ';//输出1和空格
                print(i);//（格式化为9位）
                break;
            }
        }
        if (!flag) cout << 2;
    }
    return 0;
}