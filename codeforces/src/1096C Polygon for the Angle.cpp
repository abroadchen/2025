//
// Created by Psy.C on 2026/11/18.
//

/**
真正学会的起点..
多组测试，每组读入内角度数 ang
条件 (x*N - N) % ang == 0

N=180，所以 (x*180-180) = 180(x-1)。
这来自内角公式：正 n 边形内角 = 180(n-2)/n。
代码设定：ang = 180(x-1) / n，即 ang·n = 180(x-1)。
翻转思路：把 x 当作边数 n，解出 n = 180(x-1)/ang。
整除条件判断 180(x-1) 是否被 ang 整除——若整除说明存在整数边数。
算出 n

n = 180(x-1)/ang，这是满足角度的候选边数。
但这里有个重要的合法性约束：x 作为试探的正多边形边数必须 ≥ 3，且从图形几何角度，实际要满足某些下界条件。
条件 n > x

判断算出的边数 n 是否大于试探值 x。
这是关键的"合法性 + 唯一性"过滤。
输出并跳出

找到第一个满足 n > x 的 x，输出 n，终止该用例。
这个试探过程利用内角公式的逆向变换，从小到大依次找 x，当第一次出现"能整除且 n>x"时就认为得到了最小边数 n。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 180;

int T, ang, x, n;
int main() {
    fast;
    cin >> T;
    while (T--) {
        cin >> ang; x = 2;
        while (1) {
            if ((x*N-N)%ang == 0) {
                n = (x*N-N)/ang;
                if (n > x) { cout << (x*N-N)/ang << '\n'; break; }
            }
            x++;
        }
    }
    return 0;
}