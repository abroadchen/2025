//
// Created by Psy.C on 2025/10/15.
//
/*
*常量 N 定义为100005，表示数组最大容量
n 存储元素个数
a[N] 存储序列元素的数组，初始化为空
 *
*快速读取整数的函数：
x 存储数值，y 存储符号（正负）
跳过非数字字符，处理负号
使用位运算加速数字转换：(x << 3) + (x << 1) 等价于 x * 10
c ^ '0' 用于将字符转为数字
返回带符号的数值
 *
*快速输出整数的递归函数：
如果是负数，先输出负号，再递归输出绝对值
递归输出高位数字
输出当前位数字
 *
*核心求解函数，给定前两项x,y，计算需要修改的元素个数：
k 存储公比，p 存储期望值，cnt 计数需要修改的元素
如果x不为0，计算公比 k = y/x
遍历整个序列，最多检查到2个不匹配就停止（剪枝优化）
如果当前期望值等于实际值，更新下一个期望值
否则增加修改计数
返回需要修改的元素个数
 *
*读取元素个数n
读取所有序列元素
分别尝试三种情况作为等比数列的前两项：
(a[1], a[2]) 作为前两项
(a[2], a[3]) 作为前两项
(a[1], a[3]) 作为前两项
取三种情况中需要修改元素最少的结果输出
 *
 *
*枚举几种可能的等比数列起始模式
对每种模式，计算需要修改多少个元素才能符合等比数列规律
选择修改次数最少的方案
时间复杂度为O(n)，空间复杂度为O(n)
 *
 *
 */
#include <algorithm>
#include <cstdio>
using namespace std;

typedef long long ll;
typedef long double ld;
#define rep(i,a,b) for(register ll i=(a);i<=(b);++i)

const int N = 1e5+5;

ll n, a[N]={};

ll read() {
    ll x(0), y(1); char c = getchar();
    while (c < '0' || c > '9') { if (c == '-') y = -y; c = getchar(); }
    while (c >= '0' && c <= '9') { x = (x << 3) + (x << 1) + (c ^ '0'); c = getchar(); }
    return x * y;
}

void write(ll x) {
    if (x < 0) { putchar('-'); write(-x); return; }
    if (x > 9) write(x/10);
    putchar(x%10 + '0');
}



ll solve(ld x, ld y) {
    ld k(0), p = x; ll cnt(0);
    if (x) k = y / x;
    rep(i,1,n) {
        if (cnt >= 2) break;
        if (p == a[i]) p *= k;
        else cnt++;
    }
    return cnt;
}



int main() {
    n = read();
    rep(i,1,n) a[i] = read();
    write(min({solve(a[1],a[2]), solve(a[2], a[3]),
    solve(a[1], a[3])}));
    return 0;
}