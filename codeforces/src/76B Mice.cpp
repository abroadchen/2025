//
// Created by Psy.C on 2025/11/5.
//
/*
*使用字符缓存 cc[1<<21] 实现批量读取。
当缓冲区耗尽时重新加载数据。
如果仍然为空，则返回 EOF
*定义常量：N为最大节点数（100005），inf为无穷大值（约10亿）
创建大小为2^21字节的字符数组cc作为输入缓冲区
指针uu和vv初始化指向cc，用于实现快速输入
*获取第一个字符并跳过非数字字符
处理负号标记
使用位运算高效地将字符串转换为整数
如果是负数则返回相反数
*buf是输出缓冲区，buf1用于临时存储数字字符
flush函数将缓冲区内容写入标准输出
write函数将整数转换为字符串并写入缓冲区，支持添加分隔符

buf[]: 输出缓冲区。
buf1[]: 存储单个数字的逆序表示。
cnt: 当前输出缓冲的位置索引。
cnt2: 构造数字字符串的辅助索引。
flush(): 将缓冲内容一次性写出。
write(x, ch):
将整数 x 写入缓冲区，并可选地附加一个字符 ch。
支持负数处理。
缓冲满时自动刷新。


 *
*声明变量：n(点数)、m(特殊点数)、ans(答案)
数组x存储n个点坐标，y存储m个特殊点坐标，t存储每个特殊点的最小距离
读取n和m，忽略接下来两个无用数值，初始化ans为n
*读取n个点的坐标存入数组x
设置边界条件：y[0]为负无穷，y[m+1]为正无穷
将数组t所有元素初始化为无穷大
读取m个特殊点坐标存入数组y
 *
*对每个点x[i]，使用二分查找找到其在特殊点中的位置p
计算到左右相邻特殊点的距离u和v
根据距离规则确定该点应该分配给哪个特殊点
如果该特殊点还没有被分配或可以被当前点更优地服务，则减少答案计数
更新该特殊点的最小距离
 *
 *如果左距离小于右距离，或者相等且左边的那个特殊点还未分配或正好匹配这个距离，
 *则优先考虑左边那个特殊点
 *如果这个特殊点尚未被占用，或刚好能被当前点更优地服务，
 *则减少一次无效计数（即有一个普通点不会成为最近邻）
 *更新该特殊点的最小可达距离
 *
*u: 当前点到左边最近特殊点的距离。
v: 当前点到右边最近特殊点的距离。
 *
*(0|48) = 48 → ASCII字符'0'
(1|48) = 49 → ASCII字符'1'
(2|48) = 50 → ASCII字符'2'
...
(9|48) = 57 → ASCII字符'9'
所以 (x%10)|48 的作用是将数字0-9转换为其对应的ASCII字符'0'-'9'
 *
 *
*-t 的补码等于 ~(t-1)
或者说：~(t-1) = -t
 */
#include <algorithm>
#include <cstdio>
#include <cstring>
#define getchar() (uu==vv&&(vv=(uu=cc)+fread(cc,1,1<<21,stdin),uu==vv)?EOF:*uu++)
using namespace std;

const int N = 100005, inf = 0x3f3f3f3f;
char cc[1<<21], *uu = cc, *vv = cc;
int read() {
    char ch = getchar(); int t(0); bool f(0);
    while (ch<'0' || ch>'9') { if (ch == EOF) return EOF; if (ch == '-') f = 1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { t = (t<<1)+(t<<3)+(ch&15); ch = getchar(); }
    if (f) return ~(t-1);
    return t;
}


char buf[1<<21], buf1[20]; int cnt(-1), cnt2;
void flush() { fwrite(buf, 1, cnt + 1, stdout); cnt = -1; }
void write(int x, char ch=-1) {
    if (x < 0) buf[++cnt] = 45, x = -x;
    do { buf1[++cnt2] = (x%10)|48; } while (x/=10);
    do { buf[++cnt] = buf1[cnt2]; } while (--cnt2);
    if (ch != -1) buf[++cnt] = ch;
    if (cnt > 1 << 20) flush();
}

int n, m, ans, x[N], y[N], t[N];

int main() {
    n = read(); m = read(); read(), read(); ans = n;
    for (int i = 1; i <= n; ++i) x[i] = read();
    y[0] = -inf, y[m + 1] = inf;
    memset(t, inf, sizeof(t));
    for (int i = 1; i <= m; ++i) y[i] = read();
    for (int i = 1; i <= n; ++i) {
        int p = lower_bound(y, y + m + 2, x[i]) - y,
        u = x[i] - y[p - 1], v = y[p] - x[i];
        if (u < v || (u == min(u, v)&&
            (t[p-1] == u || t[p-1] == inf))) --p;
        if (t[p] == inf || t[p] == min(u, v)) --ans;
        t[p] = min(t[p], min(u, v));
    }
    write(ans); flush();
    return 0;
}