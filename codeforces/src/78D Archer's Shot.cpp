//
// Created by Psy.C on 2025/11/5.
//
/*
*内层循环：不断减小j，直到满足条件
条件：x + 0.75*j² ≤ z（即x + 0.75*j² ≤ k²）
这是在寻找满足不等式的最大j值
 *
 */
#include <cstdio>
using namespace std;

typedef long long ll;
int i, j, k, w;
ll ans;
double x, z;

int main() {
    scanf("%d", &k); z = (double)k*k;//圆的半径平方
    for (i = 1, j = k; i <= k; ++i) {
        x = (double)i*1.5+1.0; x *= x;//将坐标进行了缩放和平移
        for (; x + (double)0.75*j*j > z && j >= 0; --j);
        if (j < 0) break;
        if (j >= i) ans += i;
        else if (j == i - 1) ans += i - 1;
        else {
            if (i % 2 == 1) ans += ((j + 1) / 2) * 2;
            else ans += (j / 2) * 2 + 1;
        }
    }
    ans *= 6;//只计算了1/6的部分
    ans++;
    printf("%lld\n", ans);
    return 0;
}