//
// Created by Psy.C on 2026/5/9.
//
/**
n为物品数量，a,b为两种属性，s1,s2为总和，sa,sb为子集和，f为DP数组，ans为答案
f[mask][sum] 表示在mask表示的物品集合下，第一种资源使用sum时第二种资源能获得的最大值
时间复杂度为O(n * 2^n * sum)，空间复杂度为O(2^n * sum)

(1 << (i-1))：将数字1左移(i-1)位，创建一个只有第(i-1)位为1的掩码
j | (1 << (i-1))：将状态j的第(i-1)位置为1，表示在集合中添加第i个物品
f[j][k]：当前状态，j表示物品集合的二进制表示，k表示第一种资源的使用量
f[j|(1<<(i-1))][k+x]：转移到的新状态，在原集合j中加入物品i后，第一种资源使用量变为k+x
x = min(a[i], sa[j])：加入物品i后第一种资源的增量
y = min(b[i], sb[j])：加入物品i后第二种资源的增量

(1<<n)-1：所有位都是1的数，表示包含所有n个物品的集合
f[(1<<n)-1][i]：在所有物品都被选择的情况下，第一种资源使用i时，第二种资源的最大收益
s1-i：第一种资源的剩余量
s2-f[(1<<n)-1][i]：第二种资源的剩余量

scanf("\n") 会跳过所有的空白字符，包括：
空格
制表符（\t）
换行符（\n）
回车符（\r）
一直读取直到遇到第一个非空白字符为止（但不读取该字符）
getchar() 读取下一个字符（包括空白字符）
由于前一步已经跳过了所有空白字符，现在读取的就是紧随空白字符之后的第一个有效字符
将这个字符存储到变量 ch 中
scanf(" %c", &ch);  // 注意%前面有个空格，会自动跳过空白字符
while((ch=getchar())==' ' || ch=='\n' || ch=='\t');  // 跳过空白字符
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int inf = 0x3f3f3f3f;
template<class T>
T rd(T x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}
template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}

int low_bit(int x) { return x & -x; }

int n, a[20], b[20], s1, s2, sa[1<<16], sb[1<<16], f[1<<16][150], ans = inf;
char ch;
int main() {
    n = rd(9);
    for (int i = 1; i <= n; ++i) {
        scanf("\n"); ch = getchar();
        a[i] = rd(9), b[i] = rd(9);
        s1 += a[i], s2 += b[i];
        if (ch == 'R') sa[1<<(i-1)] = 1;//设置sa的对应位
        else sb[1<<(i-1)] = 1;
    }
    memset(f, -1, sizeof(f)); f[0][0] = 0;
    for (int i = 0; i <= (1<<n)-1; ++i)
        sa[i] = sa[i^low_bit(i)] + sa[low_bit(i)], sb[i] = sb[i^low_bit(i)] + sb[low_bit(i)];
    for (int j = 0; j <= (1<<n)-1; ++j)//枚举所有状态
        for (int k = 0; k <= 120; ++k) {//枚举第一维的值
            if (f[j][k] == -1) continue;//状态不可达
            for (int i = 1; i <= n; ++i) {//尝试添加第i个物品
                if (j&(1<<(i-1))) continue;//第i位已经在集合中
                int x = min(a[i], sa[j]), y = min(b[i], sb[j]);
                f[j|(1<<(i-1))][k+x] = max(f[j|(1<<(i-1))][k+x], f[j][k] + y);
            }
        }
    for (int i = 0; i <= 120; ++i)
        if (~f[(1<<n)-1][i]) ans = min(ans, max(s1-i, s2-f[(1<<n)-1][i]));
    write(ans + n), putchar('\n');
    return 0;
}