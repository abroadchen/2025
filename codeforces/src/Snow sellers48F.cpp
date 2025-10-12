//
// Created by Psy.C on 2025/10/12.
//
/*
*定义常量N为500010，表示最大数据规模
定义数组：
w[N]：每种物品的重量
c[N]：每种物品的初始数量
a[N]：每天每种物品的消耗量
day：当前天数
ans：累计的整数部分答案
dot：累计的小数部分答案
 *
*快速选择函数，用于在区间[l,r]内选择能满足需求s的最优方案：

mid：中间位置索引（右移一位相当于除以2）
i, j：双指针，用于分区操作
m：中间元素在当前天的可用数量（初始数量 - 天数×每日消耗）
v：中间元素的重量
 *
*递归基础情况：当区间只有一个元素时：

计算需要的数量：m * s
将整数部分加到ans
将小数部分加到dot
1ll确保进行64位运算，避免溢出
1./v确保进行浮点数运算
 *
*分区操作（类似快速排序的分区）：

左指针寻找不符合条件的元素：(可用数量) * v < w[i] * m
右指针寻找不符合条件的元素：(可用数量) * v > w[i] * m
交换不符合条件的元素
继续移动指针
 *
*确保j至少为l，然后计算左侧分区的总量：

cnt：左侧所有物品的可用数量总和
sum：左侧所有物品的重量总和
 *
*根据左侧总量决定递归方向：

如果左侧重量总和≥需求s，则在左侧继续查找
否则，将左侧全部计入答案，并在右侧查找剩余需求
 *
*对每一天进行计算：

调用快速选择函数处理当天的需求
将小数部分的整数部分加到答案
保留小数部分供后续使用
 *
*使用sprintf格式化小数部分
b+1跳过字符串的第一个字符（通常是'0'），直接输出小数点及后面的部分
输出整数部分和小数部分
算法的时间复杂度约为O(nm)，比朴素的O(nm*log(m))排序方法更高效
 */
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
const int N = 500010;
int w[N], c[N], a[N], day;
ll ans;
double dot;

void qs(int l, int r, int s) {
    int mid = (l + r) >> 1;
    int i = l, j = r, m = c[mid] - day * a[mid], v = w[mid];
    if (l == r) {
        ll sum = m * 1ll * s;
        ans += sum / v;
        dot += (sum % v) * 1. / v;
        return;
    }
    while (i <= j) {
        while ((c[i] - day * a[i]) * 1ll * v < w[i] * 1ll * m) i++;
        while ((c[j] - day * a[j]) * 1ll * v > w[j] * 1ll * m) j--;
        if (i <= j) {
            swap(c[i], c[j]);
            swap(w[i], w[j]);
            swap(a[i], a[j]);
            i++, j--;
        }
    }
    j = max(j, l);
    ll sum(0), cnt(0);
    for (int k = l; k <= j; ++k) {
        cnt += c[k] - day * a[k];
        sum += w[k];
    }
    if (sum >= s) qs(l, j, s);
    else {
        ans += cnt;
        qs(j + 1, r, s - sum);
    }
}

int main() {
    int i, n, m, s;
    while (~scanf("%d%d%d", &n, &m, &s)) {
        for (i = 1; i <= m; ++i) scanf("%d", &w[i]);
        for (i = 1; i <= m; ++i) scanf("%d", &c[i]);
        for (i = 1; i <= m; ++i) scanf("%d", &a[i]);
        ans = 0; dot = 0;
        for (day = 0; day < n; ++day) {
            qs(1, m, s);
            ans += (int)dot;
            dot -= (int)dot;
        }
        char b[20];
        sprintf(b, "%.15lf", dot);
        printf("%lld%s\n", ans, b + 1);
    }
    return 0;
}