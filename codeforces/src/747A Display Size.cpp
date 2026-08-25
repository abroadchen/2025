//
// Created by Psy.C on 2026/8/25.
//
/**
- a ：存储 [ o bj ec tO bj ec t ] n 的 较小因数 （或等于平方根的因数）。
- b ：存储 [ o bj ec tO bj ec t ] a 的 配对因数 （即 [ o bj ec tO bj ec t ] n / a ，较大或等于平方根的因数）。
初始化为 0 是为了防止变量未初始化导致的未定义行为（即使正整数 [ o bj ec tO bj ec t ] n 必有因数，养成好习惯）
- 初始化： int i = 1 ，从 [ o bj ec tO bj ec t ] 1 开始遍历（ [ o bj ec tO bj ec t ] 1 是所有正整数的因数）。
- 循环条件： i * i <= n ，等价于 [ o bj ec tO bj ec t ] i ≤ n ​ ：
- 用 i*i （整数运算）代替 i <= sqrt(n) （浮点运算）， 避免浮点精度误差 ，且整数运算更高效。
- 原理：因数是成对的，若 [ o bj ec tO bj ec t ] i 是 [ o bj ec tO bj ec t ] n 的因数，则 [ o bj ec tO bj ec t ] n / i 也是 [ o bj ec tO bj ec t ] n 的因数，且 [ o bj ec tO bj ec t ] i ≤ n ​ 时， [ o bj ec tO bj ec t ] n / i ≥ n ​ ，因此只需遍历到 [ o bj ec tO bj ec t ] n ​ 即可找到所有因数对。
- 迭代： ++i ，每次 [ o bj ec tO bj ec t ] i 加1，遍历下一个可能的因数

- n % i == 0 ：判断 [ o bj ec tO bj ec t ] i 是否为 [ o bj ec tO bj ec t ] n 的因数（若 [ o bj ec tO bj ec t ] n 除以 [ o bj ec tO bj ec t ] i 的余数为 [ o bj ec tO bj ec t ] 0 ，则 [ o bj ec tO bj ec t ] i 能整除 [ o bj ec tO bj ec t ] n ，是 [ o bj ec tO bj ec t ] n 的因数）。
- 若满足条件：
- a = i ：将当前因数 [ o bj ec tO bj ec t ] i 存入 [ o bj ec tO bj ec t ] a （因为 [ o bj ec tO bj ec t ] i ≤ n ​ ，所以 [ o bj ec tO bj ec t ] a 是较小的或等于平方根的因数）。
- b = n / i ：将 [ o bj ec tO bj ec t ] n 除以 [ o bj ec tO bj ec t ] i 的商存入 [ o bj ec tO bj ec t ] b ，这个商也是 [ o bj ec tO bj ec t ] n 的因数，且 [ o bj ec tO bj ec t ] b ≥ n ​ （因为 [ o bj ec tO bj ec t ] i ≤ n ​ ，所以 [ o bj ec tO bj ec t ] n / i ≥ n ​ ）。
- 循环会遍历所有可能的 [ o bj ec tO bj ec t ] i ，因此 [ o bj ec tO bj ec t ] a 和 [ o bj ec tO bj ec t ] b 最终存储的是 最接近 [ o bj ec tO bj ec t ] n ​ 的一对因数 （因为 [ o bj ec tO bj ec t ] i 最大取到 [ o bj ec tO bj ec t ] n ​ ，此时 [ o bj ec tO bj ec t ] a 、 [ o bj ec tO bj ec t ] b 最接近 [ o bj ec tO bj ec t ] n ​ ）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int main() {
    fast;
    int n;
    //当输入流结束（如用户按 Ctrl+Z 、或读取到文件末尾）， cin 的状态变为 false ，循环终止
    while (cin >> n) {
        int a = 0, b = 0;
        for (int i = 1; i * i <= n; ++i) {
            if (n % i == 0) { a = i; b = n / i; }
        }
        cout << a << ' ' << b << '\n';
    }
    return 0;
}