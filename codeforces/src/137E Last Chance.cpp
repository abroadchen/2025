//
// Created by Psy.C on 2025/11/20.
//
/*
 *条件s[l]：当当前字符不为'\0'时继续
 *!strchr(v, s[l])：如果字符不是元音字母
 *记录非元音字符的位置：x[n] = l
 *在y数组中找到第一个满足y[mid] + 2 >= y[n]的位置
 *更新最大长度i：如果n-R>=i，则i = n-R+1
 *维护y数组的单调性：如果前一个元素大于当前元素，则更新当前元素
 *非元音字符计数加1
 *
 *如果字符串总长度小于L，则L = l（调整窗口大小）
*滑动窗口遍历：
i：窗口起始位置
条件：窗口不超出字符串范围
 *如果当前R指向的位置小于窗口起始位置，则R前进
 *如果剩余元素不足，则跳出循环
 *如果第一个非元音字符在窗口外，则跳过
 *如果第m个非元音字符在窗口内，则计数器c加1
 */
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 204800;
char s[N], v[] = "AEIOUaeiou";
int l, x[N], n, y[N], L, R, m, i, c;

int main() {
    gets(s);
    for (; s[l]; ++l) if (!strchr(v, s[l])) {
        x[n] = l; y[n] = l - n * 3;
        for (L = -1, R = n; L + 1 < R;)
            y[m=(L+R)/2]+2 >= y[n] ? R = m : L = m;
        if (n - R >= i) i = n - R + 1;
        if (n && y[n-1] > y[n]) y[n] = y[n-1];
        ++n;
    }
    L = (m=i)-- * 3;
    if (l < L) L = l;
    for (i = R = 0; i + L <= l; ++i) {
        if (x[R] < i) R++;
        if (R + m == n) break;
        if (x[R] >= i + L) continue;
        if (x[R + m] < i + L) ++c;
    }
    L ? printf("%d %d\n", L, c) : puts("No solution");
    return 0;
}