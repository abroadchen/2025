//
// Created by Psy.C on 2025/11/16.
//
/*
 *c[]：数字0-9的7段显示器编码（二进制表示）
*a[N]：存储数字字符串
b：当前得分
s：临时得分
n：字符串长度的一半
t：对称位置索引
 *c[a]&c[b]：两个数字的共同点亮段
 *cnt(a,b)：两个数字的相似度（共同点亮的段数）
 *
*从后往前遍历每个位置i
t是对称位置：如果i在后半部分则对应前半部分，反之亦然
 *
*尝试将位置i的数字从a[i]+1到9
计算改变后的得分变化：
b：当前总得分
cnt(a[t], j)：新数字j与对称位置的相似度
cnt(a[t], a[i])：原数字与对称位置的相似度
如果改变后得分增加，则找到更优解
*找到位置i的最优数字j后
贪心地优化后面所有位置：
对每个位置k，尝试数字0-9
选择能使总得分增加的最优数字
 *输出优化后的字符串
*如果当前位置没有更好的选择，将其设为8
更新总得分
 *
 */
#include <cstdio>
#include <cstring>
#define rep(i,a,b) for(int i=(a);i<=int(b);i++)
#define per(i,a,b) for(int i=(a);i>=int(b);i--)
#define cnt(a,b) __builtin_popcount(c[a]&c[b])
using namespace std;

const int c[] = {119, 36, 93, 109, 46, 107, 123, 37, 127, 111},
N = 200009;
char a[N];
int b, s, n, t;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%s", a + 1); n = strlen(a + 1) / 2;
    rep(i,1,2*n) a[i] -= '0';//将字符转换为数字
    per(i,2*n,1) {
        t = i > n ? i - n : i + n;
        rep(j,a[i]+1,9) if (b + cnt(a[t], j) - cnt(a[t], a[i]) > 0) {
            s = b + cnt(a[t], j) - cnt(a[t], a[i]); a[i] = j;
            rep(k,i+1,2*n) {
                t = k > n ? k - n : k + n;
                rep(l,0,9) if (s - cnt(a[t], a[k]) + cnt(a[t], l) > 0) {
                    s += -cnt(a[t], a[k]) + cnt(a[t], l);
                    a[k] = l;
                    break;
                }
            }
            rep(k,1,2*n) putchar(a[k] + '0');
            return 0;
        }
        b += cnt(a[t], 8) - cnt(a[t], a[i]);
        a[i] = 8;
    }
    puts("-1");
    return 0;
}